# Code Review Report Y66
In the file proj/code_review_report.md, your should explain how you have used pull requests (PRs) and continuous reviewing of code that goes into "master". 
    (pr example: pointers, alex tech ansvar dubbelkollar)

If you want to, you can use this code review protocol Links to an external site. for the individual code reviews. (You don't have to submit any review protocols.)

Together with the actual pull request log on GitHub, this file should convince the examiner that you pass Y66.

---

## Introduction

In the development of our project we utilized pull requests as well as using diffrent branches for diffrent part of the project. We also utilized continuous reviewing of code that integrates into the "master" branch. This report aims to provide insights into our code review process, highlighting the use of pull requests, the incorporation of a code review protocol, and the overall impact on the project's quality and collaboration.

## Code Review Process

### Branching Strategy

Throughout the project, we have employed a branching strategy, working with branches or forks derived from the "master" branch. Whether using branches in a shared repository or personal forks in private repositories, this strategy allowed us to work on different aspects of the project concurrently,as well as easily switching between working on diffrent parts of the project. This allowed us to easily test, experiement, and work on diffrent parts without having to worry about some other parts of the system.

### Pull Requests for Formalization

Before any code is committed to the "master" branch, a code review is mandatory. Pull Requests serve as a formalized process to facilitate this review. This involves having another team member, who did not write the code, most often our designated tech lead, thoroughly review it before merging. This process ensures quality assurance, encourages shared responsibility for correctness, promotes better code writing practices, and elevates project knowledge among team members.

### Tech Lead 

A crucial step in our process and what made this stategy actually reliable and easy, is the designated tech lead responsible for overseeing the technical aspects of the prject. This made collaborating and working on the projects code a lot easier since there was one person having a broader view of the project and allowed the rest to focus more on a smaller part of the project. This created highrer quality code while still makeing sure diffrent parts were compatible with eachother and working with eachother as they should.
A team member could work on a part of the project in their own branch and then initiate a pull request into the "master" branch when done. The tech lead would then review the code to ensure high-quality standards and prevent any adverse impacts on existing code. If the tech lead was the one to initiate a pull request, another team member would independently reviews the code.

### Code Review Protocol

In our code review process, we loosly used a code review protocol to aid in the reviewing procress. We used [this one](https://github.com/IOOPM-UU/ioopm15/blob/master/extramaterial/kodgranskningsprotokoll.pdf).

## Reflection on Code Review

### Consequences of Code Reviews

Implementing code reviews before committing code has proven to be highly beneficial. It served as a crucial step in our development workflow, ensuring code quality, preventing errors, and incentivizes a collaborative environment.

### GitHub Diffs Support

GitHub's colorful differentials have been invaluable in visually understanding code changes. The visual representation aids in quickly understanding the modifications made, making the review process more efficient and reducing the chances of overseeing something.

### Pull Request Iterations

The frequency of pushing back pull requests for changes has been minimal. This is a testament to the effectiveness of our code review process, where issues are identified and addressed before code is merged into the "master" branch.

### Project Statistics

<!-- FIXME -->
- **Number of Pull Requests Made:** ...
- **Average Time Pull Requests Were Open:** ...
- **Consistency in Code Review Process:** ... <!--Explain if there was uniformity in the team's adherence to the PR and code review process --> <!--tvek om detta ska fortfarande vara med-->

## Project Reflection

If we were to restart the project tomorrow, the aspects we would use agian include the use of branches for different components of the project and the double-check process by the tech lead with pull requests. These elements have significantly contributed to maintaining code quality and preventing errors and bugs. However, we would maybe consider refining the code review protocol since we did not consistently use it. We could have made it more closely align with our project's specific needs. 

In conclusion, our code review process has played a vital role in ensuring the quality of our project codebase. The lessons learned from this experience will undoubtedly influence our future development practices, emphasizing the importance of disciplined code reviews in real-world scenarios.
