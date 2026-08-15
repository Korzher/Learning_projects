INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT new_ids.id, people.id, menu.id, DATE '2022-02-25'
FROM
  (SELECT 
     generate_series(
         (SELECT MAX(id) FROM person_order) + 1,
         (SELECT MAX(id) FROM person_order) + (SELECT COUNT(*) FROM person)
     ) AS id
  ) AS new_ids
  JOIN (
    SELECT id FROM person ORDER BY id
  ) AS people
    ON new_ids.id - (SELECT MAX(id) FROM person_order) = 
       (SELECT COUNT(*) FROM person WHERE id <= people.id)
  JOIN menu ON menu.pizza_name = 'greek pizza'