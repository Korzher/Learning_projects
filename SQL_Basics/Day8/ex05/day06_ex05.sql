COMMENT ON TABLE person_discounts IS 
'Персональные скидки клиентов, основанные на истории заказов.';

COMMENT ON COLUMN person_discounts.id IS 
'Идентификатор записи.';

COMMENT ON COLUMN person_discounts.person_id IS 
'Внешний ключ клиента. Не может быть NULL';

COMMENT ON COLUMN person_discounts.pizzeria_id IS 
'Внешний ключ пиццерии. Не может быть NULL.';

COMMENT ON COLUMN person_discounts.discount IS 
'Размер скидки клиента в диапазоне от 0 до 100 процентов. Рассчитывается автоматически, значение по умолчанию - 0.';