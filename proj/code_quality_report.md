# Code Quality Report Y65
# Qoders
==========
# Code Quality Report


---
####Tankar/frågor/TODO:
- "Usage of dynamic memory is well-documented, and deallocation is handled appropriately." Ska detta verkligen va med?
- Prestanda måste va med (varför koden är bra)
---


## Introduction
In the development of our project, we have prioritized writing code of high quality, focusing on aspects such as readability, maintainability, correctness, and testability. In this report, we will delve into the reasons behind our confidence in the quality of the code as well as elaborating on how these principles have been incorporated into our system. This report provides insights into the key implementaions made and how these align with the Y65 standards.

## Code Quality Criteria
To adhere to the Y65 standard, we have considered various criteria of code quality:
<!-- FIXME: Måste lägga till prestanda-->
1. **Readability:**
   - We have followed a consistent coding style throughout the project, promoting readability.
   - Meaningful variable and function names have been chosen to enhance understanding.
   - Code comments are utilized to explain more complex sections and highlight important considerations.

2. **Maintainability:**
   - The codebase is structured in a modular manner, with clear separation of functions.
   - Functions have been designed to be concise and focused, contributing to easier maintenance, as well as further implementations and modifications.
   - Usage of dynamic memory is well-documented, and deallocation is handled appropriately.

3. **Correctness:**
   - Careful attention has been paid to edge cases and potential errors in memory allocation and deallocation.
   - Functionality has been thoroughly tested, ensuring that the code behaves as expected in various scenarios.

4. **Testability:**
   - Test cases have been written to cover different usage scenarios, aiding in ongoing development and future modifications.

## Examples of Good Code Practices
To illustrate the application of these principles, let's examine some snippets from our code:

### Example 1: Memory Allocation (`allocate` function)
```c
obj *allocate(size_t bytes, function1_t destructor)
{
    // Implementation details...

    return new_object + sizeof(meta_data_t);
}
```
- The `allocate` function is well-structured, providing a clear interface for memory allocation.
- Proper initialization of metadata ensures correct tracking of references and garbage status.
- Clear variable and function name have been used to enhance understanding of the code.

### Example 2: Memory Deallocation (`deallocate` function)
```c
void deallocate(obj **c)
{
    // Implementation details...

    deallocate_counter++;
    free(m); // Ensure proper cleanup
    *c = NULL;
}
```
- The `deallocate` function handles memory deallocation based on reference counts and destructor availability as well as delayed frees and cascade limit conditions.
- It ensures correct cleanup only when the reference count drops to zero.
- Memory management contributes to a more robust and error-resistant design.

### Example 3: Helper function (`get_meta_data` function)
```c
meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}
```
- The `get_meta_data` function is just a simple return statement but help a tremendous amount with readibilty and understanding of the code. 
- The logic used in the system becomes alot clearer and easier to work with, aiding ongoing development and maintenance.



## Additional Considerations
<!-- FIXME: fråga till gruppen, Varför behövde vi global variables?-->
- The global variables `cascade_limit`, `list_delayed_frees`, `counter`, and `check` are used to ...
- The `cleanup` function provides an explicit way to change the global variable `check` for specific cleanup purposes.


## Code Standards and Tools
We have adhered to the **GNU coding standard**, which provides a set of guidelines for writing robust and maintainable code. We have utilized the **astyle** tool to automatically format our code uniformly.This has helped us during the project to understand new code more quickly and thoroughly, since we all would write code in the same style.

## Conclusion
In summary, our code quality is a result of a concerted effort to align with the Y65 standards. The provided examples showcase our efforts to achieve readability, maintainability, correctness, and testability. Through consistent application of coding standards and thoughtful design choices, we believe our codebase meets the high-quality criteria, achievement Y65, set for this project.