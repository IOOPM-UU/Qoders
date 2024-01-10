# Design Report Y68

<!--In the file proj/design_report.md, describe the design of the system at a high level. The purpose of this document is to serve as a starting point for someone that wants to understand the implementation. You must also describe all deviations from the full specification. For every feature X that you do not deliver, explain why you do not deliver it, how the feature could be integrated in the future in your system, and sketch the high-level design.

Together with the actual code, this file will be used by the examiner to convince him/herself that you pass Y68.


Är det här vi ska skrive ex. att vi har en extra hjälp function "get_meta_deta()" och varför vi la till den?
    (Hade kunnat ha static och på så sätt ej ändra h-file men vi använder även i tests.c så måste vara public)
-->
### Design explained
In the project for the IOOPM course, we've developed a memory management library that fundamentally changes how we handle memory in C. Instead of relying on the usual malloc() and calloc(), we've introduced allocate() and allocate_array() functions, as well as functions deallocate() instead of the traditional free(). These are also useful because they kick off each object with a reference count of zero, which is central to our approach.

We're using the "reference count" to track how many pointers are pointing to each object we implement. This is super helpful in managing memory more safely and efficiently. Plus, we've got a destructor system in place which lets each object get a destructor that runs right before its memory is freed.

Another part of our design is about handling the freeing of big data structures without crashing the system. We've implemented a cascading free system, where you can set limits on how many objects get freed at once. It's purpose is to avoid overloading the memory during large clean-ups.

We've also been really focused on keeping the memory overhead low. The goal is to use only a bit more memory than traditional methods, and we're balancing the reference counting and destructors to make this happen, all while keeping our code clean and easy to understand.

Overall, it's a project that tackles the common issues in manual memory management, like leaks and segmentation faults, and provides a more structured and less error-prone method for C programmers. 

<!-- ## TODO: You must also describe all deviations from the full specification. --> 
Retain deallocate double pointers
get_metadata


30-50h total amount of wor



