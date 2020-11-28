add :: Int -> Int -> Int
add a b = a + b

sub :: Int -> Int -> Int
sub a b = a - b

mult :: Int -> Int-> Int
mult a b = a * b

square :: Int -> Int
square a = a * a

f1 :: Int -> Int -> Int
f1 a b = sub (add a b) 5

f2 :: Int -> Int -> Int
f2 a b = mult (sub a b) (-1)

f3 :: Int -> Int
f3 a = mult (square a) (-1)

f4 :: Int -> Int -> Int
f4 a b = mult (sub (square a) b) (-1)

f5 :: Int -> Int
f5 a = add (add (mult (square a) 2) (mult 3 a)) 5

f6 :: Int -> Int
f6 a = mult (square a) (square a)
