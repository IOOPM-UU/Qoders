# Code Review Report Y66
In the file proj/code_review_report.md, your should explain how you have used pull requests (PRs) and continuous reviewing of code that goes into "master". 
    (pr example: pointers, alex tech ansvar dubbelkollar)

If you want to, you can use this code review protocol Links to an external site. for the individual code reviews. (You don't have to submit any review protocols.)

Together with the actual pull request log on GitHub, this file should convince the examiner that you pass Y66.

---

## Introduction

We utilized diffrent branches for diffrent parts of the project and the review the integration of those branches into the "master" branch using pullrequests. This report aims to expalin our process and its overall impact on the project.

## Code Review Process

### Branching Strategy

We chose to divide the project into smaller "tickets" and divide these tickets amoung the group. This meant diffrent parts of the code were being worked on at the same time. To not cause conflicts we decided to create diffrent branches of each new part of the project and only when complete and functionall was it going to be added into the "master" branch. This allowed us to not have to worry about messing something up or ruining something for each other. It allowed us to easlity test, exeriment and switch bewteen working on diffrent parts of the projct easily.

### Pull Requests for Formalization

Before the complete and functional code was added into the "master" branch it had to be review and double-check by someone who has not written it to make sure it does not conflict with existing code. Otherwise, we could easily be creating new bugs and errors or overwrite code. It also ensures our code is of the highest quality, not only because someone else has to understand it but also because unnecessary code get pointed out. To do this we utilized pull request which the someone else in the project, most often our designated tech-lead, could review.

### Tech Lead 

As meantioned, we had a designated member of the team take on the role as the tech-leach or tech-support. This meant, among other things, being responsible for thouroly reviewing all pull requests. The reason we chose to have a desinated perosn for reviewing pull request is because the whole process simplifies greatly. Instead of having to find another member of the team to review your code, each member could simply open a pull request and be done with it. Then the tech-lead would see that a new pull request has been opened and review it. This made collaborating and working on the project a whole lot easier as well as elevating the overall quality of the code since now the tech-lead has a broad overview of the entire code and is more capable of making sure all parts of the code are working togher as they should and that everyone in the team is working together in the same direction. This ensured our code was of the highest quality and promoted a more smooth and efficient work enviroment. When the tech-lead himself would initiate a pull request another member of the team that had not worked on it would review it.

### Code Review Protocol

During our code review process,we loosly used [this](https://github.com/IOOPM-UU/ioopm15/blob/master/extramaterial/kodgranskningsprotokoll.pdf) code review protocol. We used it in the sense of giving us a good idea of what to look for but we did not use it for every review as a checklist.

## Reflection on Code Review

### Consequences of Code Reviews

Implementing this stategy of review all code going into the "master" branch proved to be suårisingly benefisial. It helped us working as a lager group on diffrent parts of the code without having to step on each others toes, while still being able to write on the latest version of ours projects code. This ensured an efficient and collaborative work enviroment as well as ensuring the highest quality code.

### GitHub

GitHub simple and straightforward UI have been crucial in this process, greatly simplifing the entire process. Without it this whole prcoess of initiating pull request would most likely be worth the effort. Furthermore, GitHubs diffrentials viewer was equally crucial since it easily allowed us to view and understand what changes and modifications have been made. This all made the review process a smooth and efficent way to work.

### Pull Request Iterations

The frequency of pushing back pull request or changing them has been minimal. This is a testament to how effective this stategy has been. The reason for this is that it promotes higher quality code as well as only adding code into the "master" branch when fully complete.

### Project Statistics

<!-- FIXME -->
- **Number of Pull Requests Made:** ...
- **Average Time Pull Requests Were Open:** ...
- **Consistency in Code Review Process:** ... <!--Explain if there was uniformity in the team's adherence to the PR and code review process --> <!--tvek om detta ska fortfarande vara med-->

## Project Reflection

If we would restart the project again tomorrow, not much of our work process would change. The stategy of branches, pull request, and a tech-lead were in our opinion greatly benefitial to our workflow and promoted a collaborative and efficent enviroment within the team. The only thing we might would want to look at refining is the code review protocol since we feel like we did not utilize it to its fullest potensial. We would look into modifing it to better fit our project, code, and team.

In conclusion, our code review process of branches, pull request, and a tech-lead has played a vital part of our project and is certently going to influence our future project practices.