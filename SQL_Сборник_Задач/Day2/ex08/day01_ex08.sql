SELECT order_date, person.name || ' (age:' || person.age || ')' AS person_information
FROM (SELECT order_date, person_id AS id
      FROM person_order) AS person_order_natural NATURAL JOIN person
ORDER BY order_date asc, person_information asc