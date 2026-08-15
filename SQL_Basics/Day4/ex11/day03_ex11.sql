UPDATE menu
SET price = CAST(price * 0.9 AS INT)
WHERE pizza_name = 'greek pizza'