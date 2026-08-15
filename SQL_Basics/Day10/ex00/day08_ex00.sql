-- Окно №1
BEGIN; -- Начало транзакции (Изменения не видны другим пользователям до подтверждения их внесения)
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга во втором окне (старый)

--Окно №1
COMMIT; -- Внесение изменений в базу

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга во втором окне (новый)