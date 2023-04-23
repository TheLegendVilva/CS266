-- 1. List the titles of all movies directed by ‘Yash Chopra’
SELECT Mov_Title
FROM Movies as m
JOIN Director as d
ON m.Dir_id = d.Dir_id
WHERE d.Dir_Name = 'Yash Chopra';

-- 2. Find the movie names where one or more actors acted in two or more movies
SELECT Mov_Title
FROM Movies as m
JOIN Movie_Cast as mc ON m.Mov_id = mc.Mov_id
GROUP BY Mov_Title

HAVING COUNT(DISTINCT Male_Lead) >= 2
OR COUNT(DISTINCT Female_Lead) >= 2;

-- 3. List all actors who acted in a movie before 2000 and in a movie after 2015
SELECT DISTINCT Act_Name
FROM Actor as a
JOIN Movie_Cast as mc ON a.Act_id = mc.Male_Lead OR a.Act_id = mc.Female_Lead
JOIN Movies as m ON mc.Mov_id = m.Mov_id
WHERE m.Mov_Year < 2000 AND m.Mov_Year > 2015;

-- 4. Find the title of movies and number of stars for each movie that has at least
one rating
SELECT Mov_Title, Rev_Stars
FROM as Movies m
JOIN as Rating r ON m.Mov_id = r.Mov_id;
-- 5. Find the highest number of stars
SELECT MAX(Max_Stars) Max_Stars_from_all from (Select Mov_Title, MAX(Rev_Stars) AS
Max_Stars
FROM Movies as m
JOIN Rating as r ON m.Mov_id = r.Mov_id
GROUP BY Mov_Title
ORDER BY Mov_Title);
-- 6. Update rating of all movies directed by ‘Rajkumar Hirani’ to 5
UPDATE Rating
SET Rev_Stars = 5
WHERE Mov_id IN (SELECT Mov_id FROM Movies WHERE Dir_id = (SELECT Dir_id FROM Director
WHERE Dir_Name = 'Rajkumar Hirani'));
-- 7. List the name of the movies who has same lead male actor and are rated above 4
stars
WITH c_movies AS (
SELECT DISTINCT m1.Mov_id, COUNT(DISTINCT r.Rev_Stars) AS num_stars
FROM Movie_Cast as m1
JOIN Movie_Cast as m2 ON m1.Male_Lead = m2.Male_Lead AND m1.Mov_id <> m2.Mov_id
JOIN Movies as m ON m1.Mov_id = m.Mov_id AND m2.Mov_id = m.Mov_id
JOIN Rating as r ON m.Mov_id = r.Mov_id
WHERE r.Rev_Stars > 4
GROUP BY m1.Mov_id
HAVING COUNT(DISTINCT r.Rev_Stars) > 0
)
SELECT 'Movie ID: ' || c_movies.Mov_id || ', Number of Stars: ' || c_movies.num_stars
AS output
FROM c_movies;