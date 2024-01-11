# Test Report 

In this section we talk about the different forms of testing we chose to apply, statistics regaring the efficiency of the tests and bugs we encountered.

#### Unit testing
The unit testing was essentially our first step in starting the project, we initially used test-based driven programming and created simple but useful tests in doing so. Before you want to venture into the complex parts of managing all the different aspects and systems in this project you want to ensure that the basics are working as intended. You do not want to find out too late that your object seemingly did not do what it was supposed to do. You do not want to find out that a function used to allocate and save data actually did not do that without giving segmentation faults. 

More practically explained, we used CUnit to perform our tests and our own functions that had already been tested. All of this has been automated using Makefile, which has allowed us to enter new tests as new needs arose and categorized them appropriately to be able to be specific in what we want to control. 

#### Integration testing
Since we misjudged the amount of time the integration part of the project would take, we have not been able to write any tests that test the whole system working together all at once. We do however have tests that build on eachother. For example the test `test_allocate` uses `allocate`, `deallocate`, `retain`, and `release`. These tests work sort of like integration test in the sense they test multiple parts of the system together.

#### Regression testing
We have performed our regression testing simply by being vigilant in making sure to test all the functions we modify, i.e. if we optimize a function or do any form of change to it then we will re-run tests in order to quickly catch new possible bugs. If we have made changes to a part of the code that is used in many places then all of those new test cases will be selected for regression testing. 

### Code Coverage
Code coverage of tests:
98.25% of 114 lines.

This means our tests cover 98.25% of all code we have implemented. Only 2 out of 114 lines of code are not reach which are two lines it should not reach. Those two lines are for a check in the code in the form of an if-statement which if enters prints a message and crashes the program. This means if we have it in our tests to go into this if-statement our tests would crash. This would means we could not continue testing which is why we can not have it in our tests.

We can not by this metric alone conclude that our tests are near perfect but we can feel confident they serve their purpose.

### 6 Most Nasty Bugs
Our 6 most nasty bugs (with links to their issue page on GitHub):
1. [Stack padding issue](https://github.com/IOOPM-UU/Qoders/issues/13)
We got complex problems with pointers not pointing to the correct memory adress having to do with the built in stack padding in the C-language. Still unsure if this is the true underlying problem but nontheless it took a very long time to figure out a solution and was a real headache to solve which is why it's ranked number 1.
2. [Wrong start point to memory](https://github.com/IOOPM-UU/Qoders/issues/12)
The way we returned newly allocated memory made it so that when something was writen into the memory it would overwrite the meta data. This bug should be number 1 but is only at number 2 because we caught it before it caused too many problems.
3. [Deallocate: Destructors not in use, do not work. Objects possibly not freed](https://github.com/IOOPM-UU/Qoders/issues/7)
The deallocate did not work as expected. It did not utilize the objects destructers, leaving the objects to become a source of memory leaks. 
4. [cleanup() iter used after free](https://github.com/IOOPM-UU/Qoders/issues/15)
The `cleanup` function somehow removed a link from a list while the iterator still was in use, resulting in invalid reads.
5. [remove_from_list() leaks memory when deallocating memory out of order](https://github.com/IOOPM-UU/Qoders/issues/18)
We were getting invalid read/error originating from the function `remove_from_list` which cause memory to leak. 
6. [Memory leak](https://github.com/IOOPM-UU/Qoders/issues/9)
Due to problems posibly originating from the way we either store or deallocate the objects, resulting in memory not being freed.