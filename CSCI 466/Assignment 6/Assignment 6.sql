drop table Dog;
drop table Visit;

create table Dog (dog_id int NOT NULL AUTO_INCREMENT, breed varchar (40) NOT NULL, name varchar (40) NOT NULL, weight int NOT NULL, PRIMARY KEY(dog_id));

insert into Dog (breed, name) values ("shihtzu", "manchas");
insert into Dog (breed, name) values ("shihtzu", "lukas");
insert into Dog (breed, name) values ("german shephard", "vincent");
insert into Dog (breed, name) values ("maltese", "jay");
insert into Dog (breed, name) values ("labrador", "leila");

create table Visit (visit_id int NOT NULL AUTO_INCREMENT, dog_id int NOT NULL, visit_date DATE NOT NULL, PRIMARY KEY(visit_id), FOREIGN KEY (dog_id) REFERENCES Dog(dog_id));

insert into Visit (dog_id, visit_date) values (2, "2020-06-21");
insert into Visit (dog_id, visit_date) values (1, "2020-07-11");
insert into Visit (dog_id, visit_date) values (2, "2020-08-04");
insert into Visit (dog_id, visit_date) values (1, "2020-09-09");
insert into Visit (dog_id, visit_date) values (5, "2020-10-29");
insert into Visit (dog_id, visit_date) values (3, "2020-11-20");
insert into Visit (dog_id, visit_date) values (4, "2020-12-10");
insert into Visit (dog_id, visit_date) values (4, "2021-01-26");
insert into Visit (dog_id, visit_date) values (5, "2021-02-11");

describe Visit;

select * from Visit;

alter table Visit add visit_bill int NOT NULL;

update Visit set visit_bill = 200 where visit_id = 1;
update Visit set visit_bill = 324 where visit_id = 2;
update Visit set visit_bill = 120 where visit_id = 3;
update Visit set visit_bill = 80 where visit_id = 4;
update Visit set visit_bill = 1278 where visit_id = 5;
update Visit set visit_bill = 98 where visit_id = 6;
update Visit set visit_bill = 248 where visit_id = 7;
update Visit set visit_bill = 439 where visit_id = 8;
update Visit set visit_bill = 80 where visit_id = 9;

select * from Visit;
