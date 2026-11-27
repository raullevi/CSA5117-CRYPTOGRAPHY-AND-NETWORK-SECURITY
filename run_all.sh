#!/usr/bin/env bash
# run_all.sh - Automated build and execution harness for all 40 CNS programs
set -e

GREEN='[0;32m'
BLUE='[0;34m'
YELLOW='[1;33m'
NC='[0m'

echo -e "${BLUE}======================================================================${NC}"
echo -e "${BLUE}  SIMATS CSA5117 - CRYPTOGRAPHY & NETWORK SECURITY (40 PROGRAMS)     ${NC}"
echo -e "${BLUE}  Student: Rakul K (192525143)                                       ${NC}"
echo -e "${BLUE}======================================================================${NC}
"

PASS_COUNT=0
TOTAL=40

for dir in Prog*/; do
    dir=${dir%/}
    c_file=$(find "$dir" -name "*.c" | head -n 1)
    bin_file="$dir/bin_test"

    if [ -f "$c_file" ]; then
        echo -e "${YELLOW}[+] Compiling & Running: $dir ($c_file)...${NC}"
        clang -Wall -Wextra -O2 "$c_file" -o "$bin_file" -lm
        "$bin_file" > /dev/null
        rm -f "$bin_file"
        echo -e "${GREEN}    -> PASSED!${NC}"
        PASS_COUNT=$((PASS_COUNT + 1))
    fi
done

echo -e "
${GREEN}======================================================================${NC}"
echo -e "${GREEN}  ALL $PASS_COUNT / $TOTAL PROGRAMS COMPILED & EXECUTED SUCCESSFULLY!${NC}"
echo -e "${GREEN}======================================================================${NC}"
