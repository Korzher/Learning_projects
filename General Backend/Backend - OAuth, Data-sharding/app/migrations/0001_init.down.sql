-- +migrate Down
-- +migrate StatementBegin
DROP TABLE IF EXISTS product_table;
DROP TABLE IF EXISTS supplier_table;
DROP TABLE IF EXISTS client_table;
DROP TABLE IF EXISTS address_table;
-- +migrate StatementEnd