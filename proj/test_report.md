# Test Report 

<!-- In the file proj/test_report.md, explain how you are testing your project on three levels: -->
###Tests

#### Unit testing
The unit testing was essentially our first step in starting the project, we initially used test-based driven programming and created simple but useful tests in doing so. Before you want to venture into the complex parts of managing all the different aspects and systems in this project you want to ensure that the basics are working as intended. You do not want to find out too late that your object seemingly did not do what it was supposed to do. You do not want to find out that a function used to allocate and save data actually did not do that without giving segmentation faults. 

More practically explained, we used CUnit to perform our tests and our own functions that had already been tested. All of this has been automated using Makefile, which has allowed us to enter new tests as new needs arose and categorized them appropriately to be able to be specific in what we want to control. 

#### Integration testing
<!-- TODO: -->
<!-- Nyttjandet av systemet? Hur gör vi detta automatiskt? Hur visar vi det här utan ett genomförande IRL? Automatisering? -->

#### Regression testing
We have performed our regression testing simply by being vigilant in making sure to test all functions we modify, i.e. if we optimize a function or do any form of change to it then we will re-run tests in order to quickly catch new possible bugs. If we have made changes to a part of the code that is used in many places than all of those new test cases will be selected for regression testing. 
<!-- TODO?: Automation? -->

### Code Coverage
<!-- TODO: -->
<!-- _Nummer i excel -> Skapa diagram -> Lägg in bild här + presenation_ -->

<!-- Include a graphical overview of the code coverage. You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct. -->

<!-- List your 6 most nasty bugs by linking to their issue pages on GitHub. -->
1. 
2. 
3. 
4. 
5. 
6. 
<!-- This file, together with the GitHub issue log, should convince the examiner that you pass Y69.

Viktiga saker:
    gcov
        "You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct." -->