SELECT pizzeria.name, pizzeria.rating
FROM pizzeria
LEFT JOIN person_visits
ON pizzeria.id = person_visits.pizzeria_id
WHERE person_visits.person_id IS NULL