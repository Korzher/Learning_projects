SELECT person.name as name
FROM person_order 
LEFT JOIN person
ON person.id = person_order.person_id
LEFT JOIN menu
on person_order.menu_id = menu.id
WHERE (person.address = 'Moscow' OR person.address = 'Samara') 
	and (menu.pizza_name = 'pepperoni pizza' OR menu.pizza_name = 'mushroom pizza') 
    AND person.gender = 'male'
ORDER by name desc