with dates AS (SELECT generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day'::interval))

SELECT generate_series AS missing_date
FROM dates
LEFT JOIN (SELECT visit_date
           FROM person_visits
           WHERE person_visits.person_id = 1 OR person_visits.person_id = 2) AS pv
ON pv.visit_date = dates.generate_series
WHERE pv.visit_date IS NULL
ORDER BY missing_date