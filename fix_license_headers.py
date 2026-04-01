#!/usr/bin/env python3
"""
Script to normalize ssX license headers in source files.

This script:
1. Removes duplicate AI-TRAINING-OPT-OUT blocks
2. Fixes malformed comment starts (e.g., /*******/* AI-TRAINING)
3. Normalizes whitespace between header blocks
4. Ensures consistent header formatting
"""

import os
import re
from pathlib import Path

# Pattern to match malformed comment start followed by AI-TRAINING-OPT-OUT
# e.g., /************************************************************/* AI-TRAINING-OPT-OUT
MALFORMED_START_PATTERN = re.compile(
    r'^/\*{10,}\s*/\*\s*AI-TRAINING-OPT-OUT:',
    re.MULTILINE
)

# Pattern to find the START of an AI-TRAINING-OPT-OUT block (at the beginning of a line)
AI_TRAINING_START_PATTERN = re.compile(r'^/\*\s*AI-TRAINING-OPT-OUT:', re.MULTILINE)

def fix_duplicate_headers(filepath):
    """Fix duplicate AI-TRAINING-OPT-OUT blocks in a file."""
    # Try different encodings
    content = None
    for encoding in ['utf-8', 'latin-1', 'cp1252']:
        try:
            with open(filepath, 'r', encoding=encoding) as f:
                content = f.read()
            break
        except UnicodeDecodeError:
            continue
    
    if content is None:
        print(f"Error: Could not read {filepath}")
        return False
    
    original_content = content
    
    # Check if this file has the malformed pattern
    if MALFORMED_START_PATTERN.search(content):
        # Remove the malformed line (the /*****/ followed by /* AI-TRAINING-OPT-OUT on same line)
        content = MALFORMED_START_PATTERN.sub('', content)
        # Clean up any resulting double empty lines
        content = re.sub(r'\n{3,}', '\n\n', content)
    
    # Find all occurrences of the start of AI-TRAINING-OPT-OUT blocks
    matches = list(AI_TRAINING_START_PATTERN.finditer(content))
    
    if len(matches) > 1:
        # Multiple AI-TRAINING-OPT-OUT blocks found - need to remove duplicates
        # Keep the first one, remove subsequent ones
        
        # Find where the first block ends (at the closing */)
        first_start = matches[0].start()
        
        # Find all closing */ in the header area (first 2000 chars should be enough)
        header_area = content[:min(2000, len(content))]
        closing_pattern = re.compile(r'\*/')
        closing_matches = list(closing_pattern.finditer(header_area))
        
        # Find the first closing that comes after the first AI-TRAINING-OPT-OUT start
        first_block_end = None
        for closing in closing_matches:
            if closing.start() > first_start:
                first_block_end = closing.end()
                break
        
        if first_block_end:
            # We need to remove content from after first_block_end up to the second block start
            if len(matches) > 1:
                second_start = matches[1].start()
                
                # Find the closing */ for the second block
                second_block_end = None
                for closing in closing_matches:
                    if closing.start() > second_start:
                        second_block_end = closing.end()
                        break
                
                if second_block_end:
                    # Remove the duplicate block
                    content = content[:first_block_end] + '\n\n' + content[second_block_end:]
    
    # Normalize multiple empty lines to double empty lines
    content = re.sub(r'\n{4,}', '\n\n', content)
    
    if content != original_content:
        try:
            # Write back with utf-8 encoding (replacing problematic chars)
            with open(filepath, 'w', encoding='utf-8', errors='replace') as f:
                f.write(content)
            print(f"Fixed: {filepath}")
            return True
        except Exception as e:
            print(f"Error writing {filepath}: {e}")
            return False
    
    return False

def main():
    base_dir = Path("/home/haplessidiot/Documents/ssX")
    
    # Get all files in the target directories
    target_dirs = ["Xi", "Xext", "dix", "hw"]
    
    fixed_count = 0
    total_scanned = 0
    
    for dir_name in target_dirs:
        dir_path = base_dir / dir_name
        if not dir_path.exists():
            continue
            
        for filepath in dir_path.rglob("*.c"):
            total_scanned += 1
            if fix_duplicate_headers(filepath):
                fixed_count += 1
                
        for filepath in dir_path.rglob("*.h"):
            total_scanned += 1
            if fix_duplicate_headers(filepath):
                fixed_count += 1
    
    print(f"\nTotal files scanned: {total_scanned}")
    print(f"Total files fixed: {fixed_count}")

if __name__ == "__main__":
    main()
