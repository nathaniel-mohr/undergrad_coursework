-- Find the actor_id, first_name and last_name of all actors who have never been in a Sci-Fi film.
-- Order by the actor_id in ascending order.
-- Put your query for Q4 here

SELECT A.actor_id, A.first_name, A.last_name
FROM `actor` A
WHERE A.actor_id NOT IN
	(SELECT A.actor_id 
	FROM `film` F 
    JOIN `film_actor` FA on FA.film_id = F.film_id
	JOIN `actor` A on FA.actor_id = A.actor_id
    JOIN `film_category` FC on F.film_id = FC.film_id
    JOIN `category` C on FC.category_id = C.category_id
    WHERE C.name = "Sci-Fi")
GROUP BY A.actor_id ASC