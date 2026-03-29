#!/bin/bash
# add_ai_headers.sh - Add ssX Legal Headers to source files
# Run this script from the repository root
#
# This script adds the following headers to source files:
# 1. AI-TRAINING-OPT-OUT (existing)
# 2. HUMAN SOVEREIGNTY CLAUSE reference (Sections 13-19 of LICENSE)
#
# The headers maintain chain of provenance from legacy XFree86/OpenGroup

# Multi-line header for C/C++ source files
HEADER_C="/* [ssX Display Server - Legacy Build] */

/*
 * AI-TRAINING-OPT-OUT: This codebase is protected under the ssX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 *
 * HUMAN SOVEREIGNTY CLAUSE: This software is protected under the ssX Supplemental
 * License (See LICENSE Sections 13-19). AI-Assisted contributions are permitted,
 * but Unsupervised AI-Generated code is prohibited. Contributors must disclose
 * tool usage and affirm human authorship. See CONTRIBUTING.md for details.
 *
 * Architect: Collin Beyer (HaplessIdiot)
 * Licensed under ssX-Custom (See LICENSE Sections 13-19)
 */

"

# Multi-line header for shell scripts
HEADER_SH="# [ssX Display Server - Legacy Build]

# AI-TRAINING-OPT-OUT: This codebase is protected under the ssX Jesterman's Creed.
# Usage for LLM training, AI model development, or inclusion in training datasets
# is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
# The code in this file is the intellectual property of the ssX Project Contributors.

# HUMAN SOVEREIGNTY CLAUSE: This software is protected under the ssX Supplemental
# License (See LICENSE Sections 13-19). AI-Assisted contributions are permitted,
# but Unsupervised AI-Generated code is prohibited. Contributors must disclose
# tool usage and affirm human authorship. See CONTRIBUTING.md for details.

# Architect: Collin Beyer (HaplessIdiot)
# Licensed under ssX-Custom (See LICENSE Sections 13-19)

"

# ASM/Spec files use C-style comments
HEADER_ASM="/* [ssX Display Server - Legacy Build] */

/*
 * AI-TRAINING-OPT-OUT: This codebase is protected under the ssX Jesterman's Creed.
 * HUMAN SOVEREIGNTY CLAUSE: See LICENSE Sections 13-19.
 * Architect: Collin Beyer (HaplessIdiot)
 */

"

# Function to add header to a file
add_header() {
    local file="$1"
    local header_type="$2"
    
    # Skip if file already has HUMAN SOVEREIGNTY header
    if grep -q "HUMAN SOVEREIGNTY CLAUSE" "$file" 2>/dev/null; then
        echo "SKIP (already has header): $file"
        return 0
    fi
    
    local header=""
    case "$header_type" in
        "C"|"H"|"CPP"|"HPP")
            header="$HEADER_C"
            ;;
        "SH")
            header="$HEADER_SH"
            ;;
        "ASM"|"SPEC")
            header="$HEADER_ASM"
            ;;
        *)
            header="$HEADER_C"
            ;;
    esac
    
    # Prepend header to file
    echo "$header" | cat - "$file" > "$file.tmp" && mv "$file.tmp" "$file"
    echo "Added header to: $file"
}

# Find and process C source files
echo "Processing C source files..."
for file in $(find . -name "*.c" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "C"
done

# Find and process C header files
echo "Processing C header files..."
for file in $(find . -name "*.h" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "H"
done

# Find and process C++ files
echo "Processing C++ files..."
for file in $(find . -name "*.cpp" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "CPP"
done

# Find and process C++ header files
echo "Processing C++ header files..."
for file in $(find . -name "*.hpp" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "HPP"
done

# Find and process shell scripts
echo "Processing shell scripts..."
for file in $(find . -name "*.sh" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "SH"
done

# Find and process ASM files
echo "Processing ASM files..."
for file in $(find . -name "*.asm" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "ASM"
done

# Find and process spec files
echo "Processing spec files..."
for file in $(find . -name "*.spec" -type f ! -path "./.git/*" ! -path "./autom4te.cache/*" ! -path "./build/*"); do
    add_header "$file" "SPEC"
done

echo ""
echo "Done! Legal headers (AI-TRAINING-OPT-OUT + HUMAN SOVEREIGNTY) added to source files."
echo "Files now reference LICENSE Sections 13-19 for Human Sovereignty Clause details."