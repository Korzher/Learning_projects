SELECT order_date, person.name || ' (age:' || person.age || ')' AS person_information
FROM person_order JOIN person
ON person.id = person_order.person_id
ORDER BY order_date asc, person_information asc