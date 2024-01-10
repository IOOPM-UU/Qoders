# Test Report 

<!-- In the file proj/test_report.md, explain how you are testing your project on three levels: -->
###Tests

#### Unit testing
The unit testing was essentially our first step in starting the project, we initially used test-based driven programming and created simple but useful tests in doing so. Before you want to venture into the complex parts of managing all the different aspects and systems in this project you want to ensure that the basics are working as intended. You do not want to find out too late that your object seemingly did not do what it was supposed to do. You do not want to find out that a function used to allocate and save data actually did not do that without giving segmentation faults. 

More practically explained, we used CUnit to perform our tests and our own functions that had already been tested. All of this has been automated using Makefile, which has allowed us to enter new tests as new needs arose and categorized them appropriately to be able to be specific in what we want to control. 

#### Integration testing
<!-- TODO: -->
Since we misjudged the amount of time the integration part of the project we 

We did not have proper understanding for how the implementation would practically be done as we saw it as a future problem, we believed integration and the demo would be easier to solve and in doing that we ended up hitting a bottle neck where our performance did not match the sprints expectation, this in turn created a bottle neck which stopped us from integrating because we simply did not have the proper code to do so. 


#### Regression testing
We have performed our regression testing simply by being vigilant in making sure to test all functions we modify, i.e. if we optimize a function or do any form of change to it then we will re-run tests in order to quickly catch new possible bugs. If we have made changes to a part of the code that is used in many places than all of those new test cases will be selected for regression testing. 

### Code Coverage
<!-- TODO: -->

<!-- number of line and % -->

<!-- Include a graphical overview of the code coverage. You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct. -->

<!-- List your 6 most nasty bugs by linking to their issue pages on GitHub. -->
Our 6 most nasty bugs (with links to their issue page on GitHub):
1. [Stack padding issue](https://github.com/IOOPM-UU/Qoders/issues/13)
We got complex problems with pointers not pointing to the correct memory adress having to do with the built in stack padding in the C-language. Still unsure if this is the true underlying problem but non the less it took a very long time to figure out a solution and was a real headache to solve which is why it is at number 1.
2. [Wrong start point to memory](https://github.com/IOOPM-UU/Qoders/issues/12)
The way we returned newly allocated memory made it so that when something was writen into the memory it would overwrite the meta data. This bug should be number 1 but is only at number 2 because we caught it before it cause to many problems.
3. [Deallocate: Destructors not in use, do not work. Objects possibly not freed](https://github.com/IOOPM-UU/Qoders/issues/7)
The deallocate did not work as expected. It did not utilize the objects destructers, leaving the objects to become a source of memory leaks. 
<!-- FIXME: -->
4. [remove_from_list() invalid reads](https://github.com/IOOPM-UU/Qoders/issues/16)
We were getting a lot of invalid read originating from the function `remove_from_list` 
5. [cleanup() iter used after free](https://github.com/IOOPM-UU/Qoders/issues/15)
The `cleanup` function somehow removed a link from a list while the iterator still was in use, resulting in invalid reads.
6. [Memory leak](https://github.com/IOOPM-UU/Qoders/issues/9)
Due to problems posibly originating from the way we either store or deallocate the objects, resulting in memory not being freed.

<!-- Viktiga saker:
    gcov
        "You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct." -->