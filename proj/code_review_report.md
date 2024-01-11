# Code Review Report Y66

## Introduction

We utilized different branches for different parts of the project and the review the integration of those branches into the "master" branch using pullrequests. This report aims to explain our process and its overall impact on the project.

## Code Review Process


### Branching Strategy

We chose to divide the project into smaller "tickets" and divide these tickets amoung the group. This meant different parts of the code were being worked on at the same time. To not cause conflicts we decided to create different branches of each new part of the project, and only when complete and functional was it going to be added into the "master" branch. This allowed us to not have to worry about messing something up or ruining something for each other. It allowed us to easily test, experiment and switch bewteen working on different parts of the project easily.

### Pull Requests for Formalization

Before the completed and functional code was added into the "master" branch it had to be reviewed and double-checked by someone who has not written it to make sure it does not conflict with existing code. Otherwise, we could easily be creating new bugs and errors or overwrite code. It also ensures our code is of the highest quality, not only because someone else has to understand it but also because unnecessary code hopefully gets caught before deployment. To do this we utilized pull requests which then someone else in the project, most often our designated tech-lead, could review.

### Tech Lead 

As meantioned, we had a designated member of the team take on the role as the tech-lead or tech-support. This meant, among other things, being responsible for thoroughly reviewing all pull requests. The reason we chose to have a designated person for reviewing pull requests is because the whole process simplifies greatly. Instead of having to find another member of the team to review your code, each member could simply open a pull request and be done with it. Then the tech-lead would see that a new pull request had been opened and review it. This made collaborating and working on the project a whole lot easier as well as elevating the overall quality of the code since now the tech-lead has a broad overview of the entire code and is more capable of making sure all parts of the code are working together as they should and that everyone in the team is working together in the same direction. This ensured our code was of the highest quality and promoted a more smooth and efficient work enviroment. When the tech-lead himself would initiate a pull request another member of the team that had not worked on it would review it.

### Code Review Protocol

During our code review process, we loosely used [this](https://github.com/IOOPM-UU/ioopm15/blob/master/extramaterial/kodgranskningsprotokoll.pdf) code review protocol. We used it in the sense of giving us a good idea of what to look for but we did not use it for every review as a checklist.

## Reflection on Code Review

### Consequences of Code Reviews

Implementing this stategy of reviewing all code going into the "master" branch proved to be suprisingly beneficial. It helped us working as a lager group on different parts of the code without having to step on each others toes, while still being able to write on the latest version of our projects code. This created an efficient and collaborative work enviroment as well as ensuring the highest quality code.

### GitHub

GitHub's simple and straightforward UI have been crucial in this process, greatly simplifying the entire process. Without it this whole process of initiating pull request would most likely not be worth the effort. Furthermore, GitHubs colorful differentials viewer was equally crucial since it easily allowed us to view and understand what changes and modifications have been made. This all made the review process smooth and efficent.

### Pull Request Iterations

The frequency of pushing back pull request or changing them has been minimal. This is a testament to how effective this stategy has been. The reason for this is that it promotes higher quality code as well as only adding code into the "master" branch when fully complete.

### Project Statistics

- **Number of Pull Requests Made:** 13

- **Average Time Pull Requests Were Open:** Approximately 10 hours 

## Project Reflection And Conclusion

If we would restart the project again tomorrow, not much of our work process would change, apart from our planning and coordination regarding the integration aspects of the project. This proved to be a task which required great effort unbeknownst to us, alas if we had better coordination and planning many things would have fallen in place. The stategy of branches, pull request, and a tech-lead were in our opinion greatly beneficial to our workflow and promoted a collaborative and efficient environment within the team. Another thing we might want to look at is refining the code review protocol since we feel like we did not utilize it to its fullest potential. We would look into modifyng it to better fit our project, code, and team.

In conclusion, our code review process of branches, pull request, and a tech-lead has played a vital part in our project and is certainly going to influence our future project practices.

