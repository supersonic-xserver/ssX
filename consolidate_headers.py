#!/usr/bin/env python3
"""
Consolidate license headers in ssX source files.

This script replaces complex, malformed license headers with a clean,
concise header that includes:
1. AI-TRAINING-OPT-OUT block
2. Simple MIT/X11 license reference  
3. ssX project credit
"""

import os
import re
from pathlib import Path

# Simple consolidated header template
HEADER_TEMPLATE = """\
/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

"""

# Pattern to find start of bad header section (after initial comment blocks)
BAD_HEADER_START = re.compile(
    r'^/\*\s*AI-TRAINING-OPT-OUT:.*?\*/\s*\n',
    re.MULTILINE | re.DOTALL
)

# Alternative pattern - find Copyright that appears after AI-TRAINING blocks
AFTER_AI_BLOCK = re.compile(
    r'\*/\s*\n\s*\n\s*\*?\(\s*\n\s*Copyright',
    re.MULTILINE
)


def find_header_end(lines, start_idx=0):
    """Find where the header ends (before #ifndef or first actual code)."""
    for i in range(start_idx, len(lines)):
        line = lines[i].strip()
        # Header ends before these markers
        if line.startswith('#ifndef') or line.startswith('#define') or line.startswith('#include'):
            if i > start_idx:
                return i
        if line.startswith('typedef ') or line.startswith('struct ') or line.startswith('enum '):
            if i > start_idx:
                return i
    return start_idx


def has_bad_header(lines):
    """Check if file has problematic license header."""
    # Check for pattern of uncommented Copyright
    for i, line in enumerate(lines[:30]):  # Only check first 30 lines
        if re.match(r'^/\*$', line) and i + 1 < len(lines):
            # Check if next line starts with Copyright without proper comment
            next_line = lines[i + 1].strip()
            if next_line.startswith('Copyright') and not next_line.startswith('/*'):
                return True
    return False


def consolidate_header(filepath):
    """Replace bad header with clean consolidated header."""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return False
    
    original_content = content
    lines = content.split('\n')
    
    # Check if this file has the bad header pattern
    has_bad = False
    header_end = 0
    
    # Find where actual code starts
    for i, line in enumerate(lines[:50]):
        stripped = line.strip()
        if stripped.startswith('#ifndef') or stripped.startswith('#ifdefine'):
            header_end = i
            has_bad = True
            break
        if stripped.startswith('typedef ') or stripped.startswith('struct _') or stripped.startswith('extern '):
            if i > 15:  # Only if we're past potential header
                header_end = i
                has_bad = True
                break
    
    if not has_bad:
        return False
    
    # If header end found, replace from start with new header
    if header_end > 0:
        # Find indent level from existing content
        indent = ''
        new_lines = [HEADER_TEMPLATE]
        
        # Add rest of file after header
        for line in lines[header_end:]:
            new_lines.append(line)
        
        content = '\n'.join(new_lines)
        
        try:
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
    
    # Primary target is the include directory - that's where build errors are
    target_dirs = ["include"]
    
    total_fixed = 0
    
    for dir_name in target_dirs:
        dir_path = base_dir / dir_name
        if not dir_path.exists():
            continue
        
        for ext in ["*.h"]:
            for filepath in dir_path.rglob(ext):
                if consolidate_header(filepath):
                    total_fixed += 1
    
    print(f"\nTotal files fixed: {total_fixed}")


if __name__ == "__main__":
    main()