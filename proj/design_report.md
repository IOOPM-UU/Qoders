# Design Report Y68

### Design explained
In the project for the IOOPM course, we've developed a memory management library that fundamentally changes how we handle memory in C. Instead of relying on the usual malloc() and calloc(), we've introduced allocate() and allocate_array() functions, as well as functions deallocate() instead of the traditional free(). These are also useful because they kick off each object with a reference count of zero, which is central to our approach.

We're using the "reference count" to track how many pointers are pointing to each object we implement. This is super helpful in managing memory more safely and efficiently. Plus, we've got a destructor system in place which lets each object get a destructor that runs right before its memory is freed.

Another part of our design is about handling the freeing of big data structures without crashing the system. We've implemented a cascading free system, where you can set limits on how many objects get freed at once. It's purpose is to avoid overloading the memory during large clean-ups.

We've also been really focused on keeping the memory overhead low. The goal is to use only a bit more memory than traditional methods, and we're balancing the reference counting and destructors to make this happen, all while keeping our code clean and easy to understand.

Overall, it's a project that tackles the common issues in manual memory management, like leaks and segmentation faults, and provides a more structured and less error-prone method for C programmers. 

### Central functions and data structures 

From the previous section, "Design explained" we outlined that our program utilizes various tools in order for us to to achieve a functional memory management program. While each part plays its roll, there are some that stand out as particular central: 

allocate(): 
This funtion serve as an important tool that intilializes each object with a reference count of zero, allowing us to start the tracking of object references. It makes use of malloc() to allocate the memory, sets metadata, and returns a pointer to the allocated memory. It checks for instantiation needs and triggers the casacading free function when needed.

allocate_array(): 
Similiar to allocate(), this function intilializes objects with a reference count of zero and allows us to track object references. This function uses calloc() to allocate the memory, sets up metadata, includes a pointer to a destructor and returns a pointer to the allocated memory. The pointer to a destructor allows users - if needed - to specify a custom destructor for the cleanup function.

deallocate(): 
Counterpart to the traditional 'free()', used to deallocate memory previously allocated by either allocate() or allocate_array(). Takes into consideration the reference count and will depending on the value either decrease or increase it by one. If the value is zero the object is freed.

For our datastructres we decided to use linked lists to store our delayed frees as well as the allocated objects. This was done because of the O(1) append. It also allows us to deallocate the entire lists in O(n) time, where `n` is the length of the list, when we use `cleanup` as opposed to a hashtable which would require a list of keys to be deallocated in parallel. The tradeoff of having only one datastructure to keep track of allocated objects is that deallocation also has a complexity of O(n), since the first allocation is not necesarilly the first deallocation. To summarize, the linked list gives us the ability to deallocate the entire object list in O(n) time, though the time complexity of a search is also O(n) since we must always start at the head. What is gained in code simplicitly is lost in performance. 

### Algorithms
- Remove_from_list()
The function checks if the list is empty, because if it is, no action needs to be taken. The function ignores invalid inputs (e.g. an item that doesn't exist in the list). Then creates an iterator that goes over the list until it finds the item to be removed or runs out of items in the list.
- Cleanup()
The function checks if the list is empty, like remove_from_list(), and does nothing if the list is empty. Then, a new list is created, called delete_list. The function then iterates over the list of created objects and put all objects who's pointer counter is less than 1 and puts them in delete_list. When the list has been fully iterated, all items in delete_list are free'd and the list is removed.
- Deallocate()
Deallocate checks if the object given has a pointer counter less than 1. If not, the function prints out an error message and performs a false assert. After that, the function executes remove_from_list() and frees the deallocated object, setting it's pointer to NULL so it can not be accessed again.
- Allocate()
Allocate starts by checking if a global bool, instantiate, is set to true. If it is, the function creates a new list for all objects and all delayed frees, and then sets instantiate to false. This ensures that an object list and delayed frees list is instantiated on the first call of allocate and never again. Then the function creates a new object by mallocing the size of the meta data plus the number of bytes specified to be allocated. The meta_data is given appropriate parameters and the newly created object is appended into the object list. 


### Design Deviations
- Double pointers in release() & deallocate()
We used double pointers in deallocate() and release() so that when we test we can see if the pointer becomes NULL as well, in that way we ensure ourselves that the original pointer is set to NULL when we free the memory. This helps us remove dangling pointers. What this does essentially is that it allows us to use CU_ASSERT_PTR_NULL(c); in our test cases. 

### Features Missing
#### Destructor 
One feature we are missing with this project is the default destructor() function, this feature was not delivered because of issues regarding time resources and miscalculations regarding difficulty of integration and said function. One way of integration would be the following, though note that due to us not having time to even attempt a start to this function our understanding is severely limited:

1. First the function would have to understand what exactly it is destroying. One suggestion that may work is to have the user submit a sort of code in the form of a string that the destructor will parse. So for example, in a struct that looks like this:
{
    char *name;
    char *desc;
    int price;
    ioopm_list_t *locations;
}
You would have to turn this into a string with information telling the destructor what type of object appears in what order. In this case, we could for example feed in a string that's something along the lines of "2si*" to say "2 strings, 1 int, and 1 pointer". Alternatively if it was for example 3 strings, then a pointer, then another string then an int like so:

{
    char *string;
    char *string2;
    char *string3;
    ioopm_list_t *pointer;
    char *string4;
    int integer;
}
The resulting string would be "3s*si". Of course you would design a parser to parse information like this, and the user would have to understand the formatting.

Alternatively, if we could figure out some way to find out exactly what each field holds for type of information, if it is even possible to do so, we could skip the whole parsing step and just jump straight into destroying our object.

2. Destroying the object
Once you've located all pointers for the memory, if you've used the former method to find the pointers, you would be able to enter those pointers through the destructor and for each pointer locate each of their pointers and then repeat until you reach the end and deallocate everything going backwards. 

If you used the latter method, we believe it might be possible to reach subsequent objects through the meta_data of each pointer, although this is something we would have to find out when implementing the default destructor.

#### Cascade_limit()
Another feature missing is the cascade_limit() function, its purpose is to ensure that when we are freeing memory there will be a limit that stops the deallocate() from cascading, I.e. it trying to free a million data points for example. With a cascade limit function we can feel confident that the program will not run for an exorbitant period of time. This will be achieved primarily by saving memory we want to free in another list, that will free once we have reset the cascade limit. This is done when we are allocating something new, because its important to know whether the object we want to allocate has fewer bytes than the total amount of bytes we have delayed.
