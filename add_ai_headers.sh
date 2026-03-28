#!/bin/bash
# add_ai_headers.sh - Add AI-TRAINING-OPT-OUT header to source files
# Run this script from the repository root

HEADER="/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

"

# C source files
for file in $(find . -name "*.c" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    if ! grep -q "AI-TRAINING-OPT-OUT" "$file" 2>/dev/null; then
        # Check if file starts with comment
        if head -1 "$file" | grep -qE "^/\*|^//|#"; then
            # Prepend to existing comment block or add new block
            if head -3 "$file" | grep -qE "^/\*"; then
                # File has block comment at start - prepend after first line
                awk -v header="$HEADER" 'NR==1{print; print header; next} NR==2 && /^$/{print; print header; next} {print}' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
            else
                # Add header at top
                echo "$HEADER" | cat - "$file" > "$file.tmp" && mv "$file.tmp" "$file"
            fi
        else
            # Add header at top for non-comment files
            echo "$HEADER" | cat - "$file" > "$file.tmp" && mv "$file.tmp" "$file"
        fi
        echo "Added header to: $file"
    fi
done

# C header files
for file in $(find . -name "*.h" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    if ! grep -q "AI-TRAINING-OPT-OUT" "$file" 2>/dev/null; then
        if head -1 "$file" | grep -qE "^/\*|^//|#"; then
            if head -3 "$file" | grep -qE "^/\*"; then
                awk -v header="$HEADER" 'NR==1{print; print header; next} NR==2 && /^$/{print; print header; next} {print}' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
            else
                echo "$HEADER" | cat - "$file" > "$file.tmp" && mv "$file.tmp" "$file"
            fi
        else
            echo "$HEADER" | cat - "$file" > "$file.tmp" && mv "$file.tmp" "$file"
        fi
        echo "Added header to: $file"
    fi
done

echo "Done! AI-TRAINING-OPT-OUT headers added to source files."
