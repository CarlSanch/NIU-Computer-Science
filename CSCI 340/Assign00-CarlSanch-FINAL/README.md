CSCI 340.3					Assignment00                        				Spring 2020
                  
<h2>Introduction to Git/GitHub (5 points)</h2>

For this computer assignment, you will ***not*** have to write any code.

You will only have to check out the code from the Git repository and make a few changes to `assignment00.cc`:

**Programming Notes:**

1) Create an account at [GitHub (https://github.com/join)](https://github.com/join), once created please enter information about GitHub account in the [class user database](https://forms.office.com/Pages/ResponsePage.aspx?id=kDOH6hyMMUKnmWtaAjWy5nN-1DF_VyVAmx8JZxllOldURDY0QzdIM1dITDVSRkpSVlFKSjNLWTkyQy4u).

*Helpful Git & GitHub Guides:*

* GitHub Guide: [Hello World](https://guides.github.com/activities/hello-world/)
* [2-Pager of Git Commands](https://education.github.com/git-cheat-sheet-education.pdf)
* [List of Git Tutorials](https://help.github.com/articles/good-resources-for-learning-git-and-github/)

2) You will be emailed a link to a GitHub Classroom for this assignment, copy the link to a browser to accept assignment. It will look something like this:

`https://classroom.github.com/<multi-digit code>`

Once you click on link you will be taken to a page that asks if you want to accept this assignment, ***read*** the message you want to make sure that it says something like the following:

>Accepting this assignment will give you access to the csci340-3-spring2020-assignment00-yOURgITHUBuSERnAME repository in the @NIU-CS-DataStructures organization on GitHub.

The key thing you want to look for is that your ***GitHub login*** is after the dash in specified repository. In general you should be prompted to login via the upper right-hand side sign in button. If you are using a shared computer (i.e. lab computer) the browser may cache someone else's login name.  You can address this by clearing browser cache and making sure you are logged into github in another tab in the same browser. If you still have problems let your ***instructor*** and ***TA*** know ASAP. **DO NOT ACCEPT ASSIGNMENT IF LOGIN NAME IS WRONG!!!!**

After you accept, you will be taken to a page that has something like the following:

>You are ready to go!<br><br>
You may receive an invitation to join @NIU-CS-DataStructures via email invitation on your behalf. No further action is necessary.
<br>
Your assignment has been created here: https://github.com/NIU-CS-DataStructures/csci340-3-spring2020-assignment00-yOURgITHUBuSERnAME [this is not a real link - it will fail if clicked].

3) Depending on where you do your development you can either click on link and work from your browser or use command line tools as demonstrated in class. Either way you will need eventually to generate a local repository on either turing.cs.niu.edu or hopper.cs.niu.edu in order to test your programs.

4) You will then complete the assignment as follows:

* You will add the following doc-box comment, commit to your local repository, you will then push the change to the remote repository. The comment will be modified to reflect your name, ZId, and section number (e.g. CSCI 340-3) This should be at the top of every file you modify this semester, failure to include this comment may result in a lower grade on assignment.

```c++
/* 	Your Name
	Your ZId
	Your Course and Section Number
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/
```

* You will then add the code below as the first line of code within `main` routine of the file `assignment00.cc`, you will then commit this change to your local repository, followed by a push the change to the remote repository.

```c++
cut << "Data Structures are Important!!" << endl;   // Yes, I know there is a typo!!!
```

* You will then create a `Makefile` for this assignment, you will generate a Makefile that compiles and builds an executable named *assignment00.exe*. The makefile must produce `assignment00.exe` by simply executing the command `make`.

* You will now add the Makefile to your local repository, commit changes and push to remote repository.

* You will execute `make` command, correct any compiler errors, commit changes and push to remote repository.

This semester you will need to make at least ***three commits*** to your local repository and ***three pushes*** to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final ***push*** to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

When your program is ready for grading, ***commit*** and ***push*** your local repository to remote git classroom repository and follow _**Assignment Submission Instructions**_.
