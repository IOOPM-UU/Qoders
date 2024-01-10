# Code Quality Report Y65


<!--
####Tankar/frågor/TODO:
- code example up to date?
- ett till code example?
- prestanda
-->


## Introduction

In the development of our project a key pioint we focused on was writing high quality code with focus on readability, maintainability, correctness, performance, and testability. This report aims to delve deeper into these aspects and explain how it affected the project as a whole.

## Code Quality Criteria
With the standrad for high quality code set by achievment Y65 these are the criteria we have followed:
<!-- FIXME: Måste lägga till prestanda-->
<!-- FIXME: vilken coding style -->
1. **Readability:**
   - We followed the **GNU coding standard** throughout the project to ensure consistensy and readabilty.
   - **Clear variable and function names** have been chosen to enhance reaability.
   - **Code comments** were also utilized to explain more complex section of the code.

2. **Maintainability:**
   - We structured the code in a modular manner to simplify understanding the code as well as modifying and maintaining.
   - We used clear seperation between functions to make the code easier to understand not only to enhance maintainability but also to simplify our work process during the project implementation.
   - The code is also thoroughly review and well documentated.

3. **Correctness:**
   - All functions have been thoroughly tested to ensure to code behaves as expected.
   - Edge cases and memory leaks have also been thoroughly tested.

4. **Performance**
   - TODO:

5. **Testability:**
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
- Proper initialization of the memory sturcture in the return statement is made to simplify the usability of the code.
- Clear names for varibles have been chosen to ensure readability, maintainability, and correctness.

### Example 2: Helper function (`get_meta_data` function)
```c
meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}
```
- The `get_meta_data` function is just a simple return statement but help a tremendous amount with readibilty and understanding of the code. 
- The logic used in the system becomes alot clearer and easier to work with, aiding ongoing development and maintenance.

- Even though the function does in and of itself it has been added to enhance the readability and ease understanding of other parts of the code.
- It aids in readability, maintainability, correctness, and testability since it simplifys the rest of the code as well as tests.


## Tools and Additional points
We have when writing our code adhered to the **GNU coding standard** using the **astyle** tool. This helps to automatically format our code correctly and uniformaly. This has helped us during the project to keep the code readabile and easy to understand, making our work process more efficient.

<!-- FIXME: behövs dessa två?-->
- The global variables `cascade_limit`, `list_delayed_frees`, `counter`, and `check` are used to ...
- The `cleanup` function provides an explicit way to change the global variable `check` for specific cleanup purposes.



## Conclusion
In conclusion, we belive our code adheres to the Y65 standards. We have explain our process, design choices, and provided example to showcase our code is of the highest quality.