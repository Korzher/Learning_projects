WITH currency_rates AS (
    SELECT 
        COALESCE(u.name, 'not defined') AS name,
        COALESCE(u.lastname, 'not defined') AS lastname,
        c.name AS currency_name,
        b.money,
        COALESCE(
            -- Ближайший курс ДО даты баланса
            (
                SELECT rate_to_usd
                FROM currency c2 
                WHERE c2.id = b.currency_id 
                AND c2.updated < b.updated
                ORDER BY c2.updated DESC 
                LIMIT 1
            ),
            -- Ближайший курс ПОСЛЕ даты баланса (если в прошлом нет)
            (
                SELECT rate_to_usd
                FROM currency c3 
                WHERE c3.id = b.currency_id 
                AND c3.updated > b.updated
                ORDER BY c3.updated ASC 
                LIMIT 1
            )
        ) AS rate_to_usd
    FROM balance b
	--Остаются только те записи баланса, для которых есть валюта
    INNER JOIN (
        SELECT DISTINCT id, name 
        FROM currency
    ) c ON c.id = b.currency_id
	--Имя в кавычках потому что user зарезервированное слово
	--без них он не поймет, что это таблица
    LEFT JOIN "user" u ON u.id = b.user_id
)
SELECT 
    name,
    lastname,
    currency_name,
    (money * rate_to_usd) AS currency_in_usd
FROM currency_rates
ORDER BY name DESC, lastname ASC, currency_name ASC;