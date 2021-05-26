-- Find the actor_id first_name, last_name and total_combined_film_length 
-- of Sci-Fi films for every actor.
-- That is the result should list the actor ids, names of all of the actors(even if an actor has not been in any Sci-Fi films) 
-- and the total length of Sci-Fi films they have been in.
-- Look at the category table to figure out how to filter data for Sci-Fi films.
-- Order your results by the actor_id in descending order.
-- Put query for Q3 here

SELECT A.actor_id, A.first_name, A.last_name, SUM(CASE WHEN C.name="Sci-Fi" THEN F.length ELSE 0 END) AS total_combined_film_length
FROM `actor` A
JOIN `film_actor` FA ON FA.actor_id = A.actor_id
JOIN `film` F ON F.film_id = FA.film_id
JOIN `film_category` FC ON FC.film_id = F.film_id
JOIN `category` C on C.category_id = FC.category_id
GROUP BY A.actor_id DESC