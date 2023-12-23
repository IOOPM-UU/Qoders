# Test Report

In the file proj/test_report.md, explain how you are testing your project on three levels:

- #### Unit testing
The unit testing was essentially our first step in starting the project, we initially used test-based driven programming and created simple but useful tests in doing so. Before you want to venture into the complex parts of managing all the different aspects and systems in this project you want to ensure that the basics are working as intended. You do not want to find out too late that your object seemingly did not do what it was supposed to do. You do not want to find out that a function used to allocate and save data actually did not do that without giving segmentation faults. 

More practically explained, we used CUnit to perform our tests and our own functions that had already been tested. 
- #### Integration testing
Nyttjandet av systemet? Hur gör vi detta automatiskt? Hur visar vi det här utan ett genomförande IRL? 
- #### Regression testing
Regression = ???

Also explain how you have automated these things. 

Include a graphical overview of the code coverage. You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct.

You do not need to have tests of the demo code. It is presumed to have been properly tested in assignment 2. (But if you do find new bugs in the demo code, you should mention that.)

List your 6 most nasty bugs by linking to their issue pages on GitHub.
1. 
2. 
3. 
4. 
5. 
6. 
This file, together with the GitHub issue log, should convince the examiner that you pass Y69.



"graphical overview of the code coverage"? (**Fixar detta i Powerpoint på enklaste sätt tänker jag, vi matar in värden i excel och gör nått diagram som vi lägger in i PP /M**)

Viktiga saker:
    gcov
        "You should make every effort to get 100% code and branch coverage. For every statement or branch that you have not tested, you must include a motivation for why that is and an argument for why the untested code/branch is correct."