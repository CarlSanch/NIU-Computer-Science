# CSCI 466 Assignment 10 (Spring 2021)

MariaDB in C++ (100 pts)


The Task
For this assignment, you will be writing a C/C++ program that prints reports on the books found in the henrybooks database from
our MariaDB server.


Requirements
Your program will show a menu with three options for reports to show. The user will choose an option, and your program will use
the MariaDB C API to run the necessary queries, displaying the results, neatly formatted, in the terminal.
1 Book List: For each book, print the title, the author(s), and the cost. Do not assume that a book will be written by a single
author. Use a subquery to accomplish this. Sort the authors for each book based on their Sequence.
2 Author Search: Prompt the user for the name of an Author. Print a report showing all books by authors whose first or last
names match the user-supplied name.
For each of the books found, show a line in your output with the book code, the title, the name of the author that matched
your search, and the price. Then, indented below the original line, show individual lines for each branch, each showing how
many copies of the current book are on hand at the branch (or a single line indicating that it is out of stock everywhere if no
branches have any available). Branches should be displayed as their name and address and not as their numerical identifiers.
The branch with the most copies available should come first, but when multiple branches have the same number of copies
of the book available, the branch with the lowest branch ID should come first among them.

An example is shown below:


Which author? Rowling
BookCode Title Author Price
======== ========================================== ================= =======
2226 Harry Potter and the Prisoner of Azakaban Rowling, J.K. $13.96
- 3 available at Henry Downtown (16 Riverview)
- 2 available at Henry Brentwood (Brentwood Mall)
- 1 available at Henry Eastshore (Eastshore Mall)
7443 Harry Potter and the Goblet of Fire Rowling, J.K. $18.16
- 1 available at Henry Eastshore (Eastshore Mall)


3 Title Search: Same as the author search in feature 2, but search by title instead of by author. For the author field, use the
first author for the book only (by sequence number).


Which book (title)? Black House
BookCode Title Author Price
======== ========================================== ================= =======
9611 Black House King, Stephen $18.81
- 10 available at Henry Downtown (16 Riverview)


There should also be an option to quit. After performing whichever option is chosen (obviously except for the one to quit), your
program should show the menu again and allow the user to choose a new option to run.


Notes
▶ The grading for this will be done by compiling and running this program on turing and/or hopper. If your program does not
compile and run properly on turing and hopper, you will not receive credit, so make sure to test it there.

▶ If your program needs any flags other than the ones used in the examples of gcc/g++ in the slides in order to compile, you
need to let us know when you submit.

▶ Don’t forget to document your code.

▶ It is not a requirement that every feature be implemented with a single query. You can break the tasks down into smaller
queries if you find it makes solving the problem easier.

▶ As always, you should be submitting your own work. Do not try to cheat or plagiarize other people’s programs.


What to turn in?
Submit, through Blackboard, the following:

▶ Your C++ source code, in a file called books.cc.

▶ Any other source code or header files your program needs in order to compile.

Schema for henrybooks

For your convenience, I have included information on the schema of henrybooks below:
Table Field Type Null Key Default Extra

Author AuthorNum decimal(2,0) NO PRI NULL

AuthorLast char(12) YES NULL

AuthorFirst char(10) YES NULL

Book BookCode char(4) NO PRI NULL

Title char(40) YES NULL

PublisherCode char(3) YES NULL

Type char(3) YES NULL

Price decimal(8,2) YES NULL

Paperback char(1) YES NULL

Branch BranchNum decimal(2,0) NO PRI NULL

BranchName char(50) YES NULL

BranchLocation char(50) YES NULL

NumEmployees decimal(2,0) YES NULL

Inventory BookCode char(4) NO PRI

BranchNum decimal(2,0) NO PRI 0

OnHand decimal(2,0) YES NULL

Publisher PublisherCode char(3) NO PRI NULL

PublisherName char(25) YES NULL

City char(20) YES NULL

Wrote BookCode char(4) NO PRI

AuthorNum decimal(2,0) NO PRI 0

Sequence decimal(2,0) YES NULL

