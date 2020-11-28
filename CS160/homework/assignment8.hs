-- Compare first element with last element.
-- if equal then compare second element with second to last element
--      if first half of word is equal to the reverse of the second half then true
--       (if the length is even then it is the first part before the middle letter and the part after the middle letter)
--             else false
-- if not equal then return false

palindrome :: String -> Bool
palindrome [] = True
palindrome [x] = True
palindrome word | head word == last word && (head word == last word) == palindrome (tail (init word))  = True
                | otherwise = False




-- non recursive palindrome
pal :: String -> Bool
pal word | even (length word)        = palEven word
         | odd (length word)         = palOdd word
         | otherwise                 = error "Empty String"

palOdd :: String -> Bool
palOdd word | take (div (length word) 2) word == reverse (tail (drop (div (length word) 2) word))  = True
            | otherwise                                                                            = False

palEven :: String -> Bool
palEven word | take (div (length word) 2) word == reverse (drop (div (length word) 2) word)  = True
             | otherwise                                                                     = False
