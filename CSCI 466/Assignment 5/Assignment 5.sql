\t assignment5.out

use BabyName;

show tables;

describe BabyName;

select distinct year from BabyName where name = 'Carlos' limit 50;

select distinct(year) from BabyName where first_name = 'Carlos' case when (sex) = 'M' then 'Chad' else 'Pat' end limit 50;

select first_name, max (popularity_count) popularity_count from ( select first_name, count(*) as popularity_count from BabyName group by sex, name where year = '1984' ) limit 50;

select count(distinct name) from BabyName group by place;

select name, count, year from BabyName where name = 'Carlos' order by name limit 50;

select count(distinct name) from BabyName where year = '1974';

select count(*) from BabyName;

select count(*) from BabyName where year = '1962';

\t

exit