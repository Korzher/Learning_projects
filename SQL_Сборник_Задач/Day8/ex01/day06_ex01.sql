INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER () AS id,
	   person_id,
       pizzeria_id,
       CASE
           WHEN order_count = 1 THEN 10.5
           WHEN order_count = 2 THEN 22
           ELSE 30 
       END AS discount
FROM (
  	SELECT
  		person_order.person_id,
  		menu.pizzeria_id,
  		COUNT (*) AS order_count
  	FROM person_order
  	JOIN menu ON person_order.menu_id = menu.id
  	GROUP BY person_id, pizzeria_id
 ) AS order_counts;