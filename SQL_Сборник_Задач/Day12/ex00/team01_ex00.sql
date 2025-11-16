--Находим актуальный(последний) курс валют
WITH latest_currency_rates AS (
    SELECT 
        id,
        name,
        rate_to_usd,
        updated,
		-- ROW_NUMBER() Присваивает порядковый номер, в каждой группе, которую 
		--создал PARTITION BY, ORDER BY сортирует записи  от новых к старым в каждой группе
		--Запись с rn = 1 имеет актуальный курс валют
        ROW_NUMBER() OVER (PARTITION BY id ORDER BY updated DESC) as rn
    FROM currency
),
user_balances AS (
    SELECT 
        COALESCE(u.name, 'not defined') as name,
        COALESCE(u.lastname, 'not defined') as lastname,
        b.type,
        SUM(b.money) as volume,
        COALESCE(c.name, 'not defined') as currency_name,
        COALESCE(c.rate_to_usd, 1) as last_rate_to_usd,
        SUM(b.money) * COALESCE(c.rate_to_usd, 1) as total_volume_in_usd
    FROM balance b
    LEFT JOIN "user" u ON u.id = b.user_id
    LEFT JOIN latest_currency_rates c ON c.id = b.currency_id AND c.rn = 1
    GROUP BY u.name, u.lastname, b.type, c.name, c.rate_to_usd
)
SELECT 
    name,
    lastname,  
    type,
    volume,
    currency_name,
    last_rate_to_usd,
    total_volume_in_usd
FROM user_balances
ORDER BY name DESC, lastname ASC, type ASC;