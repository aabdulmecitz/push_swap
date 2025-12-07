# push_swap

# Push Swap - Argument Parsing Documentation

## Overview
The push_swap program now supports flexible argument parsing for integer values:

1. **Separate arguments**: `./push_swap 1 2 3 4 5`
2. **Space-separated in quotes**: `./push_swap "1 2 3 4 5"`  
3. **Mixed format**: `./push_swap "1 2 3" 4 5 "6 7"`

## Features Implemented

### Flexible Input Parsing
- ✅ Parse space-separated numbers from single arguments
- ✅ Handle tab-separated numbers
- ✅ Mix separate arguments with quoted space-separated values
- ✅ Accumulate all numbers into a single stack correctly

### Input Validation
- ✅ INT_MAX (2147483647) and INT_MIN (-2147483648) boundary checks
- ✅ Overflow detection for numbers exceeding INT_MAX/INT_MIN
- ✅ Invalid character detection (letters, floats, hex, etc.)
- ✅ Duplicate value detection and rejection
- ✅ Explicit `+` sign rejection
- ✅ Double signs rejection (`--`, `++`)

## Usage Examples

### Example 1: Space-Separated Numbers
```bash
./push_swap "43 5 6 2 1"
# Output: Stack A: 43 5 6 2 1
```

### Example 2: Multiple Quoted Arguments
```bash
./push_swap "10 20 30" "40 50 60"
# Output: Stack A: 10 20 30 40 50 60
```

### Example 3: Mixed Arguments
```bash
./push_swap "1 2 3" 4 5 "6 7"
# Output: Stack A: 1 2 3 4 5 6 7
```

### Example 4: Negative Numbers
```bash
./push_swap "-5 10 -15 20 -25"
# Output: Stack A: -5 10 -15 20 -25
```

### Example 5: INT_MAX/INT_MIN
```bash
./push_swap "2147483647 -2147483648 100"
# Output: Stack A: 2147483647 -2147483648 100
```

## Error Handling

### Examples That Produce Errors

```bash
# Duplicate values
./push_swap "1 2 1 3"
# Output: Error

# Invalid characters
./push_swap "1 2 a 3"
# Output: Error

# Overflow
./push_swap "2147483648"
# Output: Error

# Explicit positive sign
./push_swap "+42"
# Output: Error

# Double signs
./push_swap "--42"
# Output: Error
```

## Test Coverage

### Edge Cases Tested (51 total tests)
- ✅ Valid inputs with various formats
- ✅ INT_MAX/INT_MIN boundaries and overflows
- ✅ Invalid characters and formats
- ✅ Duplicate value detection
- ✅ Empty/no arguments
- ✅ Whitespace variations
- ✅ Sign variations
- ✅ Combined edge cases

**All tests passing: 51/51 ✓**

## Implementation Details

### Modified Files
1. **init.c**
   - Added `count_numbers()`: Counts valid numbers in a string
   - Added `parse_space_separated()`: Parses space-separated numbers
   - Updated `fill_temp_stack()`: Handles both formats transparently
   - Added `ft_strlen()`: String length utility

2. **gc.c**
   - Removed duplicate `ft_strlen()` definition

3. **push_swap.h**
   - Added function declarations for new parsing functions

### Key Algorithms

**count_numbers()**: 
- Detects individual numbers separated by whitespace
- Validates signs appear only at number start
- Returns count of numbers or -1 for invalid input

**parse_space_separated()**:
- Parses individual numbers from space-separated string
- Accumulates into existing linked list
- Maintains proper prev/next pointers for doubly-linked list

**fill_temp_stack()**:
- Routes to appropriate parser based on input format
- Handles multiple arguments sequentially
- Maintains proper list accumulation
