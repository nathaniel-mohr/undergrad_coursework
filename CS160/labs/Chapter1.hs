module Chapter1 where


import Data.List ( (\\) )


----------------------------------------------------------------------
-- REPRESENTATIONS
----------------------------------------------------------------------

type Pos = (Float,Float)

home :: Pos
home = (3.0,4.5)

pebbles :: [Pos]
pebbles = [(9,8), (6,8.5), home]


----------------------------------------------------------------------
-- OPERATIONS ON POSITIONS
----------------------------------------------------------------------

moveRightBy :: Float -> Pos -> Pos
moveRightBy n (x,y) = (x+n,y)

-- Computing the Euclidean distance between two point on a grid
--
distance :: Pos -> Pos -> Float
distance (x1,y1) (x2,y2) = sqrt ((x2-x1)^2 + (y2-y1)^2)

-- Finding the smallesrt element in a list
--
smallest :: [Float] -> Float
smallest [x]    = x
smallest (x:xs) = min x (smallest xs)

-- Finding the closest pebble in a list
--
closestTo :: Pos -> [Pos] -> Pos
closestTo c ps = let d = smallest [distance c p | p <- ps]
                  in head [p | p <- ps, distance c p == d]


----------------------------------------------------------------------
-- OPERATIONS FOR FOLLOWING PEBBLES
----------------------------------------------------------------------

findHome1 :: Pos -> [Pos] -> Pos
findHome1 c ps | c==home   = home
               | otherwise = findHome1 (closestTo c ps) ps

findHome1T :: Pos -> [Pos] -> [Pos]
findHome1T c ps | c==home   = [home]
               | otherwise = c:findHome1T (closestTo c ps) ps


findHome2 :: Pos -> [Pos] -> Pos
findHome2 c ps | c==home   = home
               | otherwise = findHome2 (closestTo c [p | p <- ps, p/=c]) ps

findHome2T :: Pos -> [Pos] -> [Pos]
findHome2T c ps | c==home   = [home]
                | otherwise = c:findHome2T (closestTo c [p | p <- ps, p/=c]) ps


findHome3 :: Pos -> [Pos] -> Pos
findHome3 c ps | c==home   = home
               | otherwise = findHome3 (closestTo c ps) (ps \\ [c])
