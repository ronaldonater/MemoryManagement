# Custom Memory Manager

This repository contains C++ code (`Source.cpp`) and a corresponding header file (`CustomMemoryManager.h`) to simulate a custom memory manager. The program demonstrates various memory allocation strategies (best-fit, first-fit, next-fit, and worst-fit) by allocating memory blocks to processes based on their sizes.

## Files Included

### `Source.cpp`

- **Main Program Logic**: This file contains the main logic of the program.
- **Functions**:
  - `initializeData()`: Initialize processes and memory blocks with user-defined sizes.
  - `displayStatus()`: Display the status of processes, blocks, their IDs, sizes, and statuses.
  - Memory allocation functions:
    - `customBestFit()`
    - `customFirstFit()`
    - `customNextFit()`
    - `customWorstFit()`
  - `resetData()`: Reset processes and blocks data for further simulations.

### `CustomMemoryManager.h`

- **Structs**: `CustomProcess` and `CustomBlock` defining process and block attributes.
- **Constructor & Reset Functions**: Initialization and resetting functions for processes and blocks.

## How to Use

1. **Compile and Run:**
   - Compile `Source.cpp` in your preferred C++ compiler.
   - Execute the compiled program.

2. **Input:**
   - Enter the number of processes and memory partitions.
   - Provide sizes for processes and memory blocks as prompted.

3. **Output:**
   - The program will simulate various memory allocation strategies (best-fit, first-fit, next-fit, worst-fit) and display the allocated blocks for processes, waste, and memory status.

## Code Structure

- `Source.cpp` contains the main logic to simulate memory allocation strategies and display the status of processes and memory blocks.
- `CustomMemoryManager.h` defines structs for processes and memory blocks, along with initialization and resetting functions.

## Note

- Ensure valid input for process and block sizes to simulate memory allocation accurately.
