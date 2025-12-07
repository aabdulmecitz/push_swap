#!/bin/bash

# Edge case tester for push_swap (bash version)
# Quick manual testing of edge cases

EXECUTABLE="./push_swap"
PASSED=0
FAILED=0

# Colors and styling
RED='\033[91m'
GREEN='\033[92m'
YELLOW='\033[93m'
BLUE='\033[94m'
CYAN='\033[96m'
BOLD='\033[1m'
DIM='\033[2m'
NC='\033[0m' # No Color

# Test counter for formatting
TEST_NUM=0

run_test() {
    local name=$1
    local args=$2
    local should_fail=$3
    
    TEST_NUM=$((TEST_NUM + 1))
    
    output=$($EXECUTABLE $args 2>&1)
    exit_code=$?
    
    # Check if output contains "Error"
    has_error=0
    if echo "$output" | grep -q "Error"; then
        has_error=1
    fi
    
    if [ $exit_code -ne 0 ] || [ $has_error -eq 1 ]; then
        # Command failed
        if [ "$should_fail" = "true" ]; then
            echo -e "  ${GREEN}${BOLD}✓${NC} ${DIM}${name}${NC}"
            ((PASSED++))
        else
            echo -e "  ${RED}${BOLD}✗${NC} ${DIM}${name}${NC}"
            echo -e "    ${RED}Expected success, got error${NC}"
            ((FAILED++))
        fi
    else
        # Command succeeded
        if [ "$should_fail" = "true" ]; then
            echo -e "  ${RED}${BOLD}✗${NC} ${DIM}${name}${NC}"
            echo -e "    ${RED}Expected error, but passed${NC}"
            ((FAILED++))
        else
            echo -e "  ${GREEN}${BOLD}✓${NC} ${DIM}${name}${NC}"
            ((PASSED++))
        fi
    fi
}

echo -e "\n${CYAN}${BOLD}════════════════════════════════════════════════════════════════${NC}"
echo -e "${CYAN}${BOLD}  🧪  PUSH_SWAP EDGE CASE TESTER (Bash)${NC}"
echo -e "${CYAN}${BOLD}════════════════════════════════════════════════════════════════${NC}\n"

echo -e "${CYAN}${BOLD}📋 VALID CASES${NC}"
run_test "Single element" "42" "false"
run_test "Two elements sorted" "1 2" "false"
run_test "Two elements unsorted" "2 1" "false"
run_test "Negative numbers" "-5 -3 -1" "false"
run_test "INT_MAX" "2147483647" "false"
run_test "INT_MIN" "-2147483648" "false"

echo -e "\n${CYAN}${BOLD}⚠️  INT_MAX/INT_MIN BOUNDARY TESTS${NC}"
run_test "INT_MAX overflow" "2147483648" "true"
run_test "INT_MIN underflow" "-2147483649" "true"
run_test "Large number" "999999999999" "true"

echo -e "\n${CYAN}${BOLD}🚫 INVALID CHARACTERS${NC}"
run_test "Letter 'a'" "a" "true"
run_test "Float" "3.14" "true"
run_test "Special char" "42 ! 43" "true"
run_test "Hex notation" "0x2A" "true"

echo -e "\n${CYAN}${BOLD}± SIGN TESTS${NC}"
run_test "Explicit positive (+42)" "+42" "true"
run_test "Double minus (--42)" "--42" "true"
run_test "Double plus (++42)" "++42" "true"

echo -e "\n${CYAN}${BOLD}🔄 DUPLICATES${NC}"
run_test "Two same values" "1 1" "true"
run_test "Three with duplicate" "1 2 1" "true"
run_test "Duplicate zeros" "0 0" "true"

echo -e "\n${CYAN}${BOLD}📭 EDGE CASES${NC}"
run_test "No arguments" "" "true"

echo -e "\n${CYAN}${BOLD}════════════════════════════════════════════════════════════════${NC}"
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}${BOLD}  ✓ ALL TESTS PASSED!${NC}"
    echo -e "${GREEN}  Total: $PASSED passed${NC}"
else
    echo -e "${GREEN}${BOLD}  Passed: $PASSED${NC}"
    echo -e "${RED}${BOLD}  Failed: $FAILED${NC}"
fi
echo -e "${CYAN}${BOLD}════════════════════════════════════════════════════════════════${NC}\n"
