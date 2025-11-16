SELECT person.name
FROM person 
WHERE person.gender = 'female'
  AND EXISTS (
    SELECT 1 
    FROM person_order
    JOIN menu ON person_order.menu_id = menu.id
    WHERE person_order.person_id = person.id 
      AND menu.pizza_name = 'pepperoni pizza'
  )
  AND EXISTS (
    SELECT 1 
    FROM person_order
    JOIN menu ON person_order.menu_id = menu.id
    WHERE person_order.person_id = person.id 
      AND menu.pizza_name = 'cheese pizza'
  )
ORDER BY person.name