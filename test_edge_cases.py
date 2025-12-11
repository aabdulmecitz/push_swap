#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Edge case tester for push_swap
Tests: INT_MIN/MAX overflow, invalid characters, duplicates, empty input, etc.
"""

import subprocess
import sys
import random
from typing import List, Tuple

# ANSI color codes
class Colors:
    RESET = '\033[0m'
    BOLD = '\033[1m'
    DIM = '\033[2m'
    
    # Text colors
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    
    # Background colors
    BG_RED = '\033[101m'
    BG_GREEN = '\033[102m'
    BG_YELLOW = '\033[103m'
    BG_BLUE = '\033[104m'
    
    # Text styles
    SUCCESS = f'{GREEN}{BOLD}'
    FAILURE = f'{RED}{BOLD}'
    WARNING = f'{YELLOW}{BOLD}'
    INFO = f'{BLUE}{BOLD}'
    SECTION = f'{CYAN}{BOLD}'

class EdgeCaseTester:
    def __init__(self, executable: str = "./push_swap"):
        self.executable = executable
        self.passed = 0
        self.failed = 0
        self.test_cases: List[Tuple[str, str, bool]] = []
        
    def add_test(self, name: str, args: str, should_error: bool = False):
        """Add a test case: (test_name, args_to_pass, should_produce_error)"""
        self.test_cases.append((name, args, should_error))
    
    def run_test(self, name: str, args: str, should_error: bool) -> bool:
        """Run a single test and return True if it passes"""
        try:
            # Split args properly for subprocess
            cmd = [self.executable] + args.split()
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=2)
            
            error_output = result.returncode != 0 or "Error" in result.stderr
            
            if should_error:
                success = error_output
                if success:
                    status = f"{Colors.SUCCESS}✓ PASS{Colors.RESET}"
                    print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
                else:
                    status = f"{Colors.FAILURE}✗ FAIL{Colors.RESET}"
                    print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
                    print(f"    {Colors.RED}Expected error, but passed{Colors.RESET}")
            else:
                success = result.returncode == 0 and "Error" not in result.stderr
                if success:
                    status = f"{Colors.SUCCESS}✓ PASS{Colors.RESET}"
                    print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
                else:
                    status = f"{Colors.FAILURE}✗ FAIL{Colors.RESET}"
                    print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
                    print(f"    {Colors.RED}Expected success, got error{Colors.RESET}")
                    if result.stderr:
                        print(f"    {Colors.DIM}stderr: {result.stderr.strip()}{Colors.RESET}")
            
            return success
            
        except subprocess.TimeoutExpired:
            status = f"{Colors.FAILURE}✗ TIMEOUT{Colors.RESET}"
            print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
            return False
        except Exception as e:
            status = f"{Colors.FAILURE}✗ ERROR{Colors.RESET}"
            print(f"  {status} {Colors.DIM}{name}{Colors.RESET}")
            print(f"    {Colors.RED}{str(e)}{Colors.RESET}")
            return False
    
    def run_all_tests(self):
        """Run all tests and print summary"""
        print(f"\n{Colors.SECTION}{'='*70}")
        print(f"  🧪  PUSH_SWAP EDGE CASE TESTER")
        print(f"{'='*70}{Colors.RESET}\n")
        
        for name, args, should_error in self.test_cases:
            if self.run_test(name, args, should_error):
                self.passed += 1
            else:
                self.failed += 1
        
        print(f"\n{Colors.SECTION}{'='*70}{Colors.RESET}")
        
        if self.failed == 0:
            print(f"{Colors.SUCCESS}  ✓ ALL TESTS PASSED!{Colors.RESET}")
            print(f"{Colors.GREEN}  Total: {self.passed} passed{Colors.RESET}")
        else:
            print(f"{Colors.SUCCESS}  Passed: {self.passed}{Colors.RESET}")
            print(f"{Colors.FAILURE}  Failed: {self.failed}{Colors.RESET}")
        
        print(f"{Colors.SECTION}{'='*70}{Colors.RESET}\n")
        
        return self.failed == 0

def setup_tests() -> EdgeCaseTester:
    """Setup all edge case tests"""
    tester = EdgeCaseTester()
    
    # ============ VALID CASES ============
    print(f"{Colors.SECTION}📋 VALID CASES{Colors.RESET}")
    tester.add_test("Single element", "42", should_error=False)
    tester.add_test("Two elements (sorted)", "1 2", should_error=False)
    tester.add_test("Two elements (unsorted)", "2 1", should_error=False)
    tester.add_test("Three elements", "3 1 2", should_error=False)
    tester.add_test("Already sorted", "1 2 3 4 5", should_error=False)
    tester.add_test("Reverse sorted", "5 4 3 2 1", should_error=False)
    tester.add_test("Negative numbers", "-5 -3 -1", should_error=False)
    tester.add_test("Mixed positive/negative", "-100 0 100", should_error=False)
    tester.add_test("Large valid numbers", "2147483646 2147483645", should_error=False)
    tester.add_test("Small valid numbers", "-2147483647 -2147483646", should_error=False)
    
    # ============ INT_MAX/INT_MIN OVERFLOW ============
    print(f"\n{Colors.SECTION}⚠️  INT_MAX/INT_MIN BOUNDARY TESTS{Colors.RESET}")
    tester.add_test("INT_MAX (2147483647)", "2147483647", should_error=False)
    tester.add_test("INT_MIN (-2147483648)", "-2147483648", should_error=False)
    tester.add_test("INT_MAX overflow (2147483648)", "2147483648", should_error=True)
    tester.add_test("INT_MIN underflow (-2147483649)", "-2147483649", should_error=True)
    tester.add_test("Large overflow (999999999999)", "999999999999", should_error=True)
    tester.add_test("Negative large overflow (-999999999999)", "-999999999999", should_error=True)
    tester.add_test("Mixed with overflow", "42 2147483648", should_error=True)
    tester.add_test("Multiple overflows", "2147483648 2147483649", should_error=True)
    
    # ============ INVALID CHARACTERS ============
    print(f"\n{Colors.SECTION}🚫 INVALID CHARACTERS{Colors.RESET}")
    tester.add_test("Letter 'a'", "a", should_error=True)
    tester.add_test("Float notation", "3.14", should_error=True)
    tester.add_test("Special char '!'", "!", should_error=True)
    tester.add_test("Special char '#'", "1 # 2", should_error=True)
    tester.add_test("Space in number", "1 2 3 4 5", should_error=False)  # This is valid
    tester.add_test("Tab separated", "1\t2\t3", should_error=False)  # This is valid
    tester.add_test("Mix valid and invalid", "1 2 abc 3", should_error=True)
    tester.add_test("Plus sign (explicit positive)", "+42", should_error=True)
    tester.add_test("Double minus", "--42", should_error=True)
    tester.add_test("Double plus", "++42", should_error=True)
    tester.add_test("Hex notation", "0x2A", should_error=True)
    tester.add_test("Scientific notation", "1e5", should_error=True)
    tester.add_test("Unicode characters", "42 π", should_error=True)
    
    # ============ DUPLICATE VALUES ============
    print(f"\n{Colors.SECTION}🔄 DUPLICATE VALUES{Colors.RESET}")
    tester.add_test("Two duplicates", "1 1", should_error=True)
    tester.add_test("Three with duplicate", "1 2 1", should_error=True)
    tester.add_test("All same value", "5 5 5 5", should_error=True)
    tester.add_test("Multiple duplicates mixed", "1 2 1 3 2", should_error=True)
    tester.add_test("Duplicate zeros", "0 0", should_error=True)
    tester.add_test("Duplicate negatives", "-5 -5", should_error=True)
    
    # ============ EMPTY/NO ARGUMENTS ============
    print(f"\n{Colors.SECTION}📭 EMPTY/NO ARGUMENTS{Colors.RESET}")
    tester.add_test("No arguments", "", should_error=True)
    
    # ============ WHITESPACE EDGE CASES ============
    print(f"\n{Colors.SECTION}⎵  WHITESPACE EDGE CASES{Colors.RESET}")
    tester.add_test("Leading spaces", "  42", should_error=False)
    tester.add_test("Trailing spaces", "42  ", should_error=False)
    tester.add_test("Multiple spaces between", "1    2    3", should_error=False)
    tester.add_test("Mixed spaces and tabs", "1  \t  2", should_error=False)
    
    # ============ SIGN TESTS ============
    print(f"\n{Colors.SECTION}± SIGN VARIATIONS{Colors.RESET}")
    tester.add_test("Negative single digit", "-5", should_error=False)
    tester.add_test("Negative large", "-2147483647", should_error=False)
    tester.add_test("Zero", "0", should_error=False)
    tester.add_test("Negative zero (edge)", "-0", should_error=False)
    tester.add_test("Multiple negatives", "-1 -2 -3", should_error=False)
    
    # ============ COMBINED EDGE CASES ============
    print(f"\n{Colors.SECTION}🎯 COMBINED EDGE CASES{Colors.RESET}")
    tester.add_test("INT_MAX with negative", "2147483647 -1", should_error=False)
    tester.add_test("INT_MIN with INT_MAX", "-2147483648 2147483647", should_error=False)
    tester.add_test("Overflow with valid", "2147483648 42", should_error=True)
    tester.add_test("Invalid char with overflow", "2147483648 abc", should_error=True)

    # ============ RANDOMIZED SIZE CASES ============
    print(f"\n{Colors.SECTION}🎲 RANDOMIZED SIZE CASES{Colors.RESET}")
    random.seed(42)
    rand_100 = list(range(1, 101))
    random.shuffle(rand_100)
    rand_500 = list(range(1, 501))
    random.shuffle(rand_500)
    tester.add_test("Random 100 numbers", " ".join(map(str, rand_100)), should_error=False)
    tester.add_test("Random 500 numbers", " ".join(map(str, rand_500)), should_error=False)
    
    return tester

if __name__ == "__main__":
    if len(sys.argv) > 1:
        tester = EdgeCaseTester(sys.argv[1])
    else:
        tester = EdgeCaseTester()
    
    tester = setup_tests()
    success = tester.run_all_tests()
    sys.exit(0 if success else 1)
