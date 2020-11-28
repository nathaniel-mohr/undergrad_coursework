module Date where

daysInWeek :: Int
daysInWeek = 7

daysInMonth :: Int -> Int
daysInMonth m = daysInWeek * 4 * m

minutes :: Int -> Int
minutes x = 1440 * x
