#!/usr/bin/env python3
"""
Fix license headers where Copyright text appears outside comment blocks.

This script fixes files where the MIT license/Copyright text is outside
the C comment markers, causing compiler errors.
"""

import os
import re
from pathlib import Path

# Pattern to find lines starting with "Copyright" that are NOT inside a comment block
# These are at the start of a line without preceding /*
COPYRIGHT_UNCOMMENTED = re.compile(
    r'^(\s*)\*?\s*(Copyright [0-9]+)',
    re.MULTILINE
)

# Pattern to find the end of a license block (before /* $XFree86 or similar)
LICENSE_END_PATTERN = re.compile(
    r'(Open Group[^)]*\))\s*\n(\s*)/\s*\*[\$\%]',
    re.MULTILINE
)


def fix_license_comment_blocks(filepath):
    """Fix license blocks that are not wrapped in C comments."""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return False
    
    original_content = content
    
    # Check if 'Copyright' appears at the start of a line (uncommented)
    lines = content.split('\n')
    fixed = False
    
    # Find segments that need fixing
    i = 0
    new_lines = []
    in_uncommented_block = False
    block_start_idx = -1
    
    while i < len(lines):
        line = lines[i]
        
        # Check if this line starts with "Copyright" without being in a comment
        if re.match(r'^(\s*)*?\s*(Copyright [0-9]+)', line):
            # This is the start of an uncommented copyright block
            in_uncommented_block = True
            block_start_idx = len(new_lines)
            # Add the opening comment marker
            indent = re.match(r'^(\s*)', line).group(1)
            new_lines.append(f'{indent}/*')
            # Add the copyright line with proper comment syntax
            new_lines.append(line)
            fixed = True
            i += 1
            continue
        
        if in_uncommented_block:
            # Check if we've reached the end of the copyright block
            # This is typically the line with "$XFree86" or "$Xorg" or "#$"
            if line.strip().startswith('/* $') or line.strip().startswith('/* $'):
                # Add closing comment marker
                indent = re.match(r'^(\s*)', line).group(1)
                new_lines.append(f'{indent}*/')
                in_uncommented_block = False
            
            # Add the current line
            new_lines.append(line)
            i += 1
            continue
        
        new_lines.append(line)
        i += 1
    
    # Handle case where file ends while still in uncommented block
    if in_uncommented_block:
        new_lines.append(' */')
    
    if fixed:
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
    
    # Find all .h and .c files with the issue
    target_dirs = ["include", "Xi", "Xext", "dix"]
    
    total_fixed = 0
    
    for dir_name in target_dirs:
        dir_path = base_dir / dir_name
        if not dir_path.exists():
            continue
        
        for ext in ["*.h", "*.c"]:
            for filepath in dir_path.rglob(ext):
                if fix_license_comment_blocks(filepath):
                    total_fixed += 1
    
    print(f"\nTotal files with fixed license comment blocks: {total_fixed}")


if __name__ == "__main__":
    main()