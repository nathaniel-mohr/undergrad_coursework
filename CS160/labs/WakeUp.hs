-- using integers to represent time as minutes
wakeUpM :: Int -> Int -> Int
wakeUpM leave duration = leave - duration

-- using floating point numbers to represnet time as hours
wakeUpH :: Float -> Float -> Float
wakeUpH leave duration = leave - duration

-- using pairs of integers to represent time as hours and minutes--
-- wakeUpWrong :: (Int,Int) -> (Int,Int) -> (Int,Int)
-- type Time = (Int,Int)

type Minute = Int
type Hour   = Int
type Time   = (Hour,Minute)

wakeUpNaive :: Time -> Time -> Time
wakeUpNaive (h,m) (h',m') = (h-h',m-m')

-- wakeUp (h,m) (h',m') = if m'>m then (h-h'-1,60+m-m') else (h-h',m-m')

wakeUp :: Time -> Time -> Time
wakeUp (h,m) (h',m') | m' > m    = (h - h' - 1, 60 + m - m')
                     | otherwise = (h - h' , m - m')

timeToMinutes :: Time -> Minute
timeToMinutes (h,m) = (h * 60) + m

minutesToTime :: Minute -> Time
minutesToTime m = ((div m 60), (mod m 60))
