WITH people as (SELECT *
                From person)
                
SELECT p2.name as person_name1,
	   p1.name AS person_name2,
       p1.address as common_address
FROM people p1
INNER JOIN people p2
	on p1.address = p2.address
    AND p1.id < p2.id
ORDER by person_name1, person_name2, common_address