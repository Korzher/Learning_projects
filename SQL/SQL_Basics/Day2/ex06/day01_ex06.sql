SELECT visit_date AS action_date, name AS person_name
FROM person LEFT JOIN person_visits 
ON person.id = person_visits.person_id
INTERSECT
SELECT order_date AS action_date, name AS person_name
FROM person LEFT JOIN person_order
ON person.id = person_order.person_id
ORDER BY action_date ASC, person_name DESC