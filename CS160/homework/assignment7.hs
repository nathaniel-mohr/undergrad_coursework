--adds one to every element of a list
addOne :: [Int] -> [Int]
addOne xs = map (+2) xs





--float changed to char representing letter grade equivalent
rawGradeToLetter :: Float -> Char
rawGradeToLetter grade | grade >= 90.0     = 'A' 
                       | grade >= 80.0     = 'B'
                       | grade >= 70.0     = 'C'
                       | grade >= 60.0     = 'D'
                       | otherwise         = 'F'

--list of floats changed to list of char representing letter grade equivalent
convertRawsToLetters :: [Float] -> [Char]
convertRawsToLetters grades = map rawGradeToLetter grades





--list of floats representing ounces changed to list of floats representing cups
ouncesToCups :: [Float] -> [Float] 
ouncesToCups oz = map (* 0.125) oz

--conversion of ounces to glasses
ouncesToGlass :: Float -> Float
ouncesToGlass ounces = ounces / 8

--list of floats representing ounces changed to list of floats representing glasses
glassOfWater :: [Float] -> [Float]
glassOfWater ounces = map (ouncesToGlass) ounces

--determines if number of ounces consumed is greater than 8 glasses
hydrated :: Float -> String
hydrated ounces | (ouncesToGlass ounces) > 8  =    "Hydrated"
                | otherwise                   =    "Not hydrated"

--determines how many glasses are needed to be hydrated based on ounces consumed
waterNeeded :: Float -> Float
waterNeeded ounces = 8 - (ouncesToGlass ounces) 

