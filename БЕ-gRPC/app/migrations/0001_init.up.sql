-- +migrate Up
-- +migrate StatementBegin
CREATE TABLE IF NOT EXISTS address_table (
    id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    country VARCHAR(50) NOT NULL,
    city VARCHAR(59) NOT NULL,
    street VARCHAR(50) NOT NULL
);

CREATE UNIQUE INDEX IF NOT EXISTS idx_unique_address
ON address_table(country, city, street);

CREATE TABLE IF NOT EXISTS client_table (
    id UUID PRIMARY KEY,
    client_name VARCHAR(50) NOT NULL,
    client_surname VARCHAR(50) NOT NULL,
    birthday DATE NOT NULL,
    gender VARCHAR(1) NOT NULL,
    registration_date TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP,
    address_id UUID NOT NULL, 
    CONSTRAINT fk_client_address 
        FOREIGN KEY (address_id)
        REFERENCES address_table(id)
);

CREATE TABLE IF NOT EXISTS image_table (
    id UUID PRIMARY KEY,
    image BYTEA NOT NULL
);

CREATE TABLE IF NOT EXISTS supplier_table (
    id UUID PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    address_id UUID NOT NULL, 
    CONSTRAINT fk_supplier_address 
        FOREIGN KEY (address_id)
        REFERENCES address_table(id),
    phone_number VARCHAR(20) NOT NULL DEFAULT ''
);

CREATE TABLE IF NOT EXISTS product_table (
    id UUID PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    category VARCHAR(50) NOT NULL,
    price BIGINT NOT NULL,
    available_stock INT NOT NULL CHECK (available_stock >= 0),
    last_update_date TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP,
    supplier_id UUID NOT NULL,
        CONSTRAINT fk_supplier_id 
        FOREIGN KEY (supplier_id)
        REFERENCES supplier_table(id),
    image_id UUID NULL,
        CONSTRAINT fk_image_id 
        FOREIGN KEY (image_id)
        REFERENCES image_table(id)
);

INSERT INTO address_table (id, country, city, street) 
VALUES ('660f8400-e29b-41d4-a716-446655440011', 'Russia', 'Moscow', 'Tverskaya')
ON CONFLICT DO NOTHING;

INSERT INTO supplier_table (id, name, address_id, phone_number)
VALUES ('550e8400-e29b-41d4-a716-446655440000', 'Tech Wholesale', '660f8400-e29b-41d4-a716-446655440011', '+70001112233')
ON CONFLICT DO NOTHING;

INSERT INTO product_table (id, name, category, price, available_stock, supplier_id, last_update_date)
VALUES ('770e8400-e29b-41d4-a716-446655440022', 'Laptop Air', 'Laptops', 120000, 10, '550e8400-e29b-41d4-a716-446655440000', NOW())
ON CONFLICT DO NOTHING;

INSERT INTO client_table (id, client_name, client_surname, birthday, gender, address_id, registration_date)
VALUES (
    '880e8400-e29b-41d4-a716-446655440099', 
    'Ivan', 
    'Petrov', 
    '1990-01-15', 
    'M', 
    '660f8400-e29b-41d4-a716-446655440011', 
    NOW()
)
ON CONFLICT DO NOTHING;
-- +migrate StatementEnd


