module quiz1 where

data Tree a
   = Nook a (Tree a)
   | Node (Tree a) (Tree a)
   | End
     deriving (Eq,Show)


ex1 :: Tree Int
ex1 = Nook 3 (Nook 4 (Node (Nook 2 End) (Node (Nook 5 End) End)))

ex2 :: Tree Int
ex2 = Node (Node (Nook 3 End) (Nook 4 (Nook 5 End))) (Node End End)

ex3 :: Tree String
ex3 = Nook "hey" (Nook "adora" End)

-- | Count the number of nooks in a tree.
--
--   >>> nooks End
--   0
--
--   >>> nooks ex1
--   4
--
--   >>> nooks ex2
--   3
-- 
--   >>> nooks ex3
--   2
--
nooks :: Tree a -> Int
nooks End = 0
nooks (Nook _ a) = 1 + (nooks a)
nooks (Node a b) = (nooks a) + (nooks b)

-- | Map a function over a tree, preserving its structure.
--
--   >>> mapTree (+10) ex1
--   Nook 13 (Nook 14 (Node (Nook 12 End) (Node (Nook 15 End) End)))
-- 
--   >>> mapTree odd ex2
--   Node (Node (Nook True End) (Nook False (Nook True End))) (Node End End)
--
--   >>> mapTree length ex3
--   Nook 3 (Nook 5 End)
--
mapTree :: (a -> b) -> Tree a -> Tree b
mapTree _ End = End
mapTree f (Nook a b) = Nook (f a) (mapTree f b)
mapTree f (Node a b) = Node (mapTree f a) (mapTree f b)
