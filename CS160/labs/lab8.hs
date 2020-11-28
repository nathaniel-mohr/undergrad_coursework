f :: Int -> Int
f x = 4 * x

g :: Int -> Int
g y = y + 2

add 0 = 0
add n = 1 + add(n-1)

length' [] = 0
length' (x:xs) = 1 + length' (xs)

last' [x] = x
last' (x:xs) = last'(xs)

reverse' [] = []
reverse' (x:xs) = reverse'(xs) ++ [x] 

find' x []                 = False
find' x (y:ys) | x == y    = True
               | otherwise = find' x ys

smallest :: [Float] -> Float
smallest [x]    = x
smallest (x:xs) = min x (smallest xs)


type Minute = Int
type Hour = Int
type Time = (Hour, Minute)

timeToMinutes :: Time -> Minute
timeToMinutes (h, m) = (h * 60) + m

minutesToTime :: Minute -> Time
minutesToTime m = ((div m 60), (mod m 60))

wakeUp :: Time -> Time -> Time
wakeUp (h, m) (h', m') = minutesToTime(timeToMinutes(h, m) - timeToMinutes(h', m'))

validMinute :: Minute -> Bool
validMinute m | 0 <= m && m <= 59   = True
              | otherwise           = False

validHour :: Hour -> Bool
validHour h | 0 <= h && h <= 23     = True
            | otherwise             = False

validTime :: Time -> Bool
validTime (h,m) | validMinute m && validHour h  = True
                | otherwise                     = False
