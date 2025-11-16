-- Окна №1 и №2
SHOW TRANSACTION ISOLATION LEVEL; -- Просмотр уровня изоляции транзакции

-- Окно №1
BEGIN; -- Начало транзакции

--Окно №2
BEGIN; -- Начало транзакции

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Окно №1
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии

--Окно №2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии

-- Выполнение команды UPDATE во втором окне зависает до введения команды COMMIT в первом окне (SCR 1)

-- Окно №1
COMMIT; -- Внесение изменений в базу

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- В окне 1 видны локальные изменения (рейтинг 4), в окне 2 - локальные изменения (рейтинг 3.6)

-- Окно №2
COMMIT; -- Внесение изменений в базу

-- В обоих окнах видны глобальные изменения (рейтинг 3.6), рейтинг 4 потерян. (SCR 2)

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга