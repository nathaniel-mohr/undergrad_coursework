-- Find the film_title of all films which feature both KIRSTEN PALTROW and WARREN NOLTE
-- Order the results by film_title in descending order.


SELECT F.title as film_title
FROM `film` F
JOIN 
    (SELECT F.film_id
    FROM `film` F 
    JOIN `film_actor` FA ON F.film_id = FA.film_id
    JOIN `actor` A ON FA.actor_id = A.actor_id
    WHERE A.first_name = "KIRSTEN" AND A.last_name="PALTROW")
AS KP ON F.film_id = KP.film_id
JOIN 
    (SELECT F.film_id
    FROM `film` F 
    JOIN `film_actor` FA ON F.film_id = FA.film_id
    JOIN `actor` A ON FA.actor_id = A.actor_id
    WHERE A.first_name = "WARREN" AND A.last_name="NOLTE")
AS WN ON F.film_id = WN.film_id
ORDER BY F.title DESC