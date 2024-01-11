# Code Quality Report Y65

## Introduction

In the development of our project a key point we focused on was writing high quality code with focus on readability, maintainability, correctness, and testability. This report aims to dive deeper into these aspects and explain how it affected the project as a whole.

## Code Quality Criteria
With the standrad for high quality code set by achievment Y65 these are the criteria we have followed:
1. **Readability:**
   - We followed the **GNU coding standard** throughout the project to ensure consistensy and readabilty.
   - **Clear variable and function names** have been chosen to enhance reability.
   - **Code comments** were also utilized to explain more complex sections of the code.

2. **Maintainability:**
   - We structured the code in a modular manner to simplify understanding of the code as well as modifying and maintaining the code.
   - We used clear seperation between functions to make the code easier to understand and not only to enhance maintainability but also to simplify our work process during the project implementation.
   - The code is also thoroughly reviewed and well-documentated.

3. **Correctness:**
   - All functions have been thoroughly tested to ensure to code behaves as expected.
   - Edge cases and memory leaks have also been thoroughly tested.

4. **Testability:**
   - Test cases have been implemented to ensure code works as expected.
   - Helper functions have been implemented to aid in testing.


## Examples of Good Code Practices in our Code

### Example 1: Memory Allocation (`allocate` function)
```c
obj *allocate(size_t bytes, function1_t destructor)
{
    // Implementation details...

    return new_object + sizeof(meta_data_t);
}
```

- The function is well structured as to help the readability and maintainability of the code.
- Proper initialization of the memory structure in the return statement is made to simplify the usability of the code.
- Clear names for variables have been chosen to ensure readability, maintainability, and correctness.

### Example 2: Helper function (`get_meta_data` function)
```c
meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}
```
- Even though the function does in and of itself nothing special, it has been added to enhance the readability and ease understanding of other parts of the code.
- It aids in readability, maintainability, correctness, and testability since it simplifys the rest of the code as well as tests.

## Example 3: Header file
- The header file is fully documented aiding in understanding the code.
- Ensures maintainability, readability as well as testability.


## Tools and Additional points
We have when writing our code adhered to the **GNU coding standard** using the **astyle** tool. This helps to automatically format our code correctly and uniformaly. This has helped us during the project to keep the code readabile and easy to understand, making our work process more efficient.

## Conclusion
In conclusion, we belive our code adheres to the Y65 standards. We have explained our process, design choices, and provided examples to showcase our code is of the highest quality.