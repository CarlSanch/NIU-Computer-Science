CSCI 466 Assignment 3 (Spring 2021)
ER Diagram to Third Normal Form (100 pts)
Introduction
For this assignment, you will be converting the following ER diagram, which models the operational data for
a department store, to a set of relations that conform to Third Normal Form (3NF). Use the steps from the
slides that we went over in class. Make sure to indicate the primary keys by underlining them. Include a list
of which attributes are foreign keys, with the home relation of each foreign key indicated.
ER Diagram
Store
storeID
address
manager
City
cityName
state headquartersAddr
Product
productID
description
size
weight
color
Customer
customerName
address
email
Order
orderNum
date
is
located
in
(1,n)
(1,1)
is
stored
in
(1,n)
(1,n)
quantity
was
ordered
in (1,n) (1,n)
quantity
placed (1,1) (1,n) hold
(1,n)
(1,n)
quantity
Figure 1: This is the ER diagram. There may be some things that may seem weird. These may be errors
that were missed during the design phase, or they could be intentional. The purpose of this assignment is to
convert it, not to revise it.
What to turn in?
Submit a PDF file through Blackboard containing the relational schema for the database, including the
information required above.
