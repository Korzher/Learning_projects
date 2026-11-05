DROP TRIGGER IF EXISTS trg_person_insert_audit ON person;
DROP TRIGGER IF EXISTS trg_person_update_audit ON person;
DROP TRIGGER IF EXISTS trg_person_delete_audit ON person;
DROP FUNCTION IF EXISTS fnc_trg_person_insert_audit();
DROP FUNCTION IF EXISTS fnc_trg_person_update_audit();
DROP FUNCTION IF EXISTS fnc_trg_person_delete_audit();

TRUNCATE TABLE person_audit;

CREATE FUNCTION fnc_trg_person_audit()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO person_audit (id, name, age, gender, address, row_id, type_event)
        VALUES (
            nextval('person_audit_id_seq'),
            NEW.name,
            NEW.age,
            NEW.gender,
            NEW.address,
            NEW.id,
            'I'
        );
        RETURN NEW;
        
    ELSIF TG_OP = 'UPDATE' THEN
        INSERT INTO person_audit (id, name, age, gender, address, row_id, type_event)
        VALUES (
            nextval('person_audit_id_seq'),
            OLD.name,
            OLD.age,
            OLD.gender,
            OLD.address,
            OLD.id,
            'U'
        );
        RETURN NEW;
        
    ELSIF TG_OP = 'DELETE' THEN
        INSERT INTO person_audit (id, name, age, gender, address, row_id, type_event)
        VALUES (
            nextval('person_audit_id_seq'),
            OLD.name, 
            OLD.age,
            OLD.gender,
            OLD.address,
            OLD.id,
            'D'
        );
        RETURN OLD;
    END IF;
    
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_audit
AFTER INSERT OR UPDATE OR DELETE ON person
FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');

UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;

DELETE FROM person WHERE id = 10;

-- Проверка срабатывания триггера 
SELECT * FROM person_audit ORDER BY created;