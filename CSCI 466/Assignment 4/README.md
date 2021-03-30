# CSCI 466 Assignment 4 (Spring 2021)

ER Diagram, Normalization, DDL (100 pts)


Introduction
For this assignment, you will be making another ER diagram modeling the operational data of the enterprise
described below. All entities, relationships, and attributes must be labeled, with cardinalities shown, and
identifiers marked appropriately. This time, you will also be converting the ER diagram into relations that
can be used to store the data. Additionally, you will be supplying SQL to add these relations to your database.


The enterprise

You have been hired by a stock exchange to implement a database to help them to run their operations.
As such, you are tasked with designing a database that could be used to run a (very much simplified) stock
market.


Requirements

1 Customers link one or more bank accounts to their account for the exchange. They can deposit money
to the exchange from those banks, or withdraw money from the exchange and send it to one of the
bank accounts. Any such bank transactions must be logged by the database.

2 Each stock has a symbol that uniquely identifies it on the exchange. A stock will also have the full
name of the company.

3 Once a customer buys some amount of stock, they “hold” shares of that on the exchange. They can
hold shares of many different stocks at the same time. They are able to sell the stocks they hold on the
exchange by placing orders.

4 Every time a stock is bought or sold, a record of the (exchange) transaction needs to be stored. This
record will include, at a minimum: which stock, how many shares, who bought it, who sold it, and
when.

5 Separately from the actual buy and sell transactions, the exchange will need to track limit orders. A limit
order is a request to buy or sell some amount of a stock if the price is better (i.e. lower when buying,
higher when selling) than a limit that the customer sets. An order is not fulfilled unless another order
is found that matches it. For example, an order to buy a share of the stock at $250 or less could match
an order to sell the stock at $250 or more. Since one of these orders could be asking for more shares
than the other side is, it will be necessary to keep track of partially-filled orders.

6 Customers can also place market orders. These are requests to buy or sell shares of a stock at the best
price possible right away. These orders need to be logged, and will match with the best available order
immediately.

7 Whenever an order to buy and an order to sell match, a transaction will occur, and the database must
store data on that transaction with the appropriate details. It must be able to track the transaction
back to both of the orders involved.

8 At any point in time, any placed order can be pending, partially filled, filled, or canceled. If an order is
canceled, it is necessary to know when the cancellation occurred.


Required Views

Though you are only tasked with designing the database, and are not responsible for writing the application
that would actually use this database, you do need to make sure that your database stores the data that would
be needed to generate the following:

1 A customer should be able to see all of the stock they own and how much of it.

2 A customer should be able to see all of the orders they’ve placed, and whether they’ve been filled yet
or not.

3 Information on orders placed should always be retained, but should be marked clearly as open (pending)
vs. filled (done). It should be possible to know what the most highly-priced buy limit order and the
lowest price sell limit order are at any point in time.

4 It should be possible to print a list of all transactions a customer has made and when. This should
include: how many shares the customer bought of which stock, for which price, and when.

5 Each transaction (whether involving the bank or involving stocks moving on the exchange) needs to be
logged in such a way that the total balance of money for a given customer can be known for any point
in time.

6 Customers should be able to view a profit and loss report that shows the gross average bought and sold
prices for each of their stocks.


What to turn in?

Submit, through Blackboard, the following:

• The ER diagram that you have designed. This should be in a common image format, or a PDF. It may
be hand drawn, but must be legible for credit to be awarded.

• A second page like the one from the first ER diagram assignment, with all of the entities, relationships
and attributes from the ER diagram listed and described.

• The relational schema resulting from your ER diagram, in the format discussed in lectures. Primary
keys need to be underlined, and foreign keys identified in a clear way.

• A text file, gamestonks.sql with valid SQL CREATE TABLE statements to create each of the relations for
your database. Do not forget the foreign key constraints.

