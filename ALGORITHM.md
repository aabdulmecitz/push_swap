# Turkish Sorting Algorithm Implementation

## Overview
The Turkish algorithm (also known as the Turk algorithm) is an efficient sorting strategy for the push_swap problem that uses cost calculation to optimize element placement.

## Key Components

### Structures Added (in push_swap.h)

#### `t_cost` - Cost Calculation Structure
```c
typedef struct s_cost
{
    int cost_a;         // Cost to move element in stack A
    int cost_b;         // Cost to move element in stack B
    int total_cost;     // Total combined cost
    int direction_a;    // Direction for A: 1 (forward/ra), -1 (backward/rra)
    int direction_b;    // Direction for B: 1 (forward/rb), -1 (backward/rrb)
}   t_cost;
```

#### `t_target` - Target Position Structure
```c
typedef struct s_target
{
    int index;          // Element index
    int cost;           // Movement cost
    int target_pos_a;   // Target position in stack A
    int target_pos_b;   // Target position in stack B
    t_cost move_cost;   // Associated movement cost
}   t_target;
```

## Algorithm Functions

### 1. `get_stack_size(t_node *stack)`
- Counts total elements in a stack
- Returns the size as integer

### 2. `get_position(t_node *stack, int value)`
- Finds the position of an element with a specific value
- Returns position index (0-based), or -1 if not found

### 3. `find_target_position(t_node *stack_a, int value)`
- Determines where an element from stack B should go in stack A
- Uses index-based matching to find the optimal insertion position
- Returns the position index in stack A

### 4. `calculate_rotation_cost(int position, int stack_size)` [Internal]
- Calculates the minimum rotations needed to reach a position
- Considers both forward (ra/rb) and backward (rra/rrb) rotations
- Returns the minimum cost (lowest number of moves)

### 5. `get_rotation_direction(int position, int stack_size)` [Internal]
- Determines optimal rotation direction
- Returns 1 for forward rotation, -1 for backward rotation

### 6. `calculate_cost(t_node *stack_a, t_node *stack_b, int b_index)`
- Calculates total cost to move an element from B to its target position in A
- Considers:
  - Position in stack B
  - Target position in stack A
  - Rotation directions for both stacks
  - Optimization when both stacks rotate same direction (use rr/rrr)
- Returns complete cost structure

### 7. `apply_rotation(t_node **stack_a, t_node **stack_b, t_cost cost)` [Internal]
- Executes the calculated rotations
- Optimizes by using combined operations (rr/rrr) when both stacks rotate same direction
- Applies remaining individual rotations

### 8. `sort_stacks(t_node **stack_a, t_node **stack_b, t_gc *gc)`
- Main sorting algorithm
- Strategy:
  1. Push all but 3 elements from A to B
  2. Sort remaining 3 in A using sort_three()
  3. For each element in B:
     - Calculate cost for all elements
     - Find element with minimum cost
     - Rotate B to bring that element to top
     - Apply optimal rotation for both stacks
     - Push element back to A
  4. Final rotation to place smallest element at top

## Algorithm Complexity

- **Time Complexity**: O(n²) for cost calculation phase
- **Space Complexity**: O(n) for stack storage
- **Move Efficiency**: Typically 5-6n moves for random input

## Cost Calculation Strategy

When moving an element from B to A:

1. Calculate individual costs:
   - `cost_a` = min rotations to target position
   - `cost_b` = min rotations to bring element to top

2. Determine optimal total cost:
   - If same direction: `total = max(cost_a, cost_b)` (use combined rr/rrr)
   - If different directions: `total = cost_a + cost_b` (sequential moves)

3. Select cheapest element to move based on total_cost

## Integration

The algorithm integrates with existing operations:
- Uses `ra`, `rb`, `rr` for forward rotations
- Uses `rra`, `rrb`, `rrr` for backward rotations
- Uses `pa`, `pb` for push operations
- Uses `sa`, `sb`, `ss` for swap operations when needed

## Files Modified

- `includes/push_swap.h` - Added structures and function declarations
- `src/turk_sort.c` - Main algorithm implementation
- `src/push_swap.c` - Integrated sort_stacks() call
- `Makefile` - Added turk_sort.c and related files to compilation
