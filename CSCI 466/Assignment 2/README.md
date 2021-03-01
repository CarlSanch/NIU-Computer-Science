CSCI 466 Assignment 2 (Spring 2021)


Normalization (50 pts)


The Task


We discussed in class that a relational database designed in a poor way will allow for anomalies to occur. This
is undesirable, so we use normalization to prevent them. Several relations are provided below, along with
their functional dependencies. Answer the questions provided and fix what is broken. Perform only the
current step for each question, i.e. when fixing First Normal Form (1NF), fix only 1NF, leaving the Second
(2NF) and Third Normal Form (3NF) violations alone until the question that asks about them.


The Questions


For each of the below, part b refers to the results of part a , and part c refers to the results of part b –
any changes made during the previous steps should be considered in the steps that follow. Each question is
worth 12 points.

1 Company(EmpID, EmpName, EmpAddr, (ProjID, ProjName, MgrID, MgrName, HoursWorked))
Functional Dependencies:

• EmpID ⟶ EmpName, EmpAddr

• ProjID ⟶ ProjName, MgrID, MgrName

• EmpID, ProjID ⟶ HoursWorked

• MgrID ⟶ MgrName

a Is this relation in 1NF? If not, explain why not, then make the necessary changes to fix it.

b Is this relation in 2NF? If not, explain why not, then make the necessary changes to fix it.

c Is this relation in 3NF? If not, explain why not, then make the necessary changes to fix it.

2 StockExchange(Company, Symbol, HQ, Date, ClosePrice)
Functional Dependencies:

• Symbol, Date ⟶ Company, HQ, ClosePrice

• Symbol ⟶ Company, HQ

• Symbol ⟶ HQ

a Is this relation in 1NF? If not, explain why not, then make the necessary changes to fix it.

b Is this relation in 2NF? If not, explain why not, then make the necessary changes to fix it.

c Is this relation in 3NF? If not, explain why not, then make the necessary changes to fix it.

3 Property(id, county, lotNum, lotArea, price, taxRate, (datePaid, amount))

Functional Dependencies:

• id ⟶ county, lotNum, lotArea, price, taxRate

• lotArea ⟶ price

• county ⟶ taxRate

• id, datePaid ⟶ amount

a Is this relation in 1NF? If not, explain why not, then make the necessary changes to fix it.

b Is this relation in 2NF? If not, explain why not, then make the necessary changes to fix it.

c Is this relation in 3NF? If not, explain why not, then make the necessary changes to fix it.

1 Pharmacy(patient_id, patient_name, address, (Rx_num, trademark_name, generic_name, (filldate,
num_refills_left), num_refills))

Functional Dependencies:

• patient_id ⟶ patient_name, address

• patient_id, Rx_num ⟶ trademark_name, generic_name

• Rx_num ⟶ num_refills

• Rx_num, filldate ⟶ num_refills_left

a Is this relation in 1NF? If not, explain why not, then make the necessary changes to fix it.

b Is this relation in 2NF? If not, explain why not, then make the necessary changes to fix it.

c Is this relation in 3NF? If not, explain why not, then make the necessary changes to fix it.

What to turn in?
Answers to the questions should be submitted via Blackboard as a PDF with your name and section at the
top of each page.
