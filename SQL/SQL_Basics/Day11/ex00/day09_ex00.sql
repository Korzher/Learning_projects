create table person_audit
( id bigint primary key ,
  name varchar not null,
  age integer not null default 10,
  gender varchar default 'female' not null ,
  address varchar,
  created timestamp with time zone not null default CURRENT_TIMESTAMP,
  type_event char(1) default 'I' not null CHECK (type_event IN ('I', 'U', 'D')),
  row_id bigint not null
  );

CREATE SEQUENCE person_audit_id_seq START 1;

CREATE FUNCTION fnc_trg_person_insert_audit()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO person_audit (id, name, age, gender, address, row_id)
    VALUES (
        nextval('person_audit_id_seq'),
        NEW.name,
        NEW.age,
        NEW.gender,
        NEW.address,
        NEW.id
    );
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_insert_audit
AFTER INSERT ON person
FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');

-- Проверка срабатывания триггера 
SELECT * FROM person_audit ORDER BY created;