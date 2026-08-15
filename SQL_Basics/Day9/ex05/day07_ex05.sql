SELECT DISTINCT person.name
FROM person_order
JOIN person ON person.id = person_order.person_id
ORDER BY person.name;