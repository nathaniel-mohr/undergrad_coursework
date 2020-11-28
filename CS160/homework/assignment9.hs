swapPass :: (Ord a) => [a] -> [a]
swapPass [x] = [x]
swapPass (x:y:xs)
    | x > y      = y : swapPass(x:xs)
    | otherwise  = x : swapPass(y:xs)

loopOverAll :: (Ord a) => [a] -> Int -> [a]
loopOverAll xs numberOfElements
  | numberOfElements == (length xs)  = xs
  | otherwise                        = loopOverAll (swapPass xs) (numberOfElements+1)

bubbleSort :: (Ord a) => [a] -> [a]
bubbleSort listOfNumbers 
    | null listOfNumbers == True   = listOfNumbers
    | otherwise                    = loopOverAll listOfNumbers 0

