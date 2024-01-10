# Design Report Y68

### Design explained
In the project for the IOOPM course, we've developed a memory management library that fundamentally changes how we handle memory in C. Instead of relying on the usual malloc() and calloc(), we've introduced allocate() and allocate_array() functions, as well as functions deallocate() instead of the traditional free(). These are also useful because they kick off each object with a reference count of zero, which is central to our approach.

We're using the "reference count" to track how many pointers are pointing to each object we implement. This is super helpful in managing memory more safely and efficiently. Plus, we've got a destructor system in place which lets each object get a destructor that runs right before its memory is freed.

Another part of our design is about handling the freeing of big data structures without crashing the system. We've implemented a cascading free system, where you can set limits on how many objects get freed at once. It's purpose is to avoid overloading the memory during large clean-ups.

We've also been really focused on keeping the memory overhead low. The goal is to use only a bit more memory than traditional methods, and we're balancing the reference counting and destructors to make this happen, all while keeping our code clean and easy to understand.

Overall, it's a project that tackles the common issues in manual memory management, like leaks and segmentation faults, and provides a more structured and less error-prone method for C programmers. 

- Double pointers in release() & deallocate()
kort sagt tillåter det oss att använda CU_ASSERT_PTR_NULL(c);
We used double pointers in deallocate() and release() so that when we test we can see if the pointer becomes NULL as well, in that way we ensure ourselves that the original pointer is set to NULL when we free the memory. This helps us remove dangling pointers. What this does essentially is that it allows us to use CU_ASSERT_PTR_NULL(c); in our test cases. 
- get_metadata()
We implemented the function get_metadata() because an issue we stumbled upon was that the way we returned newly allocated memory made it so that when something was writen into the memory it would overwrite the meta data. Because of this we had to create this helper function.

### Features Missing
<!-- ## TODO: For every feature X that you do not deliver, explain why you do not deliver it, how the feature could be integrated in the future in your system, and sketch the high-level design. --> 
One feature we are missing with this project is the Destructor() function, this feature was not delivered because of issues regarding time resources and miscalculations regarding difficulty of integration and said function. One way of integration would be the following: 

1. Define the struct and its representation 
- We need to define the struct and what it contains.
- We do this by creating a function that generates a string representation of this struct. 
2. Generating the Struct representation
- This function will iterate through each element of the struct and keep a count of consecutives elements of the same type. 
- When the type changes, it appends the count and type symbol to the string.
3. Parsing the string representation
- Create a function that parse the generated string.
- Each digit tells the function the count, each type symbol tells it what type to expect. 
- When a pointer type is encountered the function keeps track of how many and where in the iteration the pointers are. 
4. Freeing memory of pointers.
- When the parsing function identifies pointer types it translates the information to actual pointers in the struct using a mechanism to access the pointers inside the struct. Using for example a parallel array or similar data structure that stores references to these pointers. 
- When a pointer is identified we use deallocate() to free its memory. 
5. Integration with the project.
- We integrate it by making sure its called whenever a struct is no longer needed.
- It is important to ensure that the function is only called once per pointer in order to avoid double frees. 
