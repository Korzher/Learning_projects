SELECT pizzeria.name
FROM pizzeria
WHERE id NOT IN (SELECT person_visits.pizzeria_id
                 FROM person_visits);

SELECT pizzeria.name
FROM pizzeria
WHERE NOT EXISTS (SELECT person_visits.pizzeria_id
                 FROM person_visits
                 WHERE pizzeria.id = person_visits.pizzeria_id)