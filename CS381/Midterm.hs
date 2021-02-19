module Midterm where
import  Prelude hiding(flip)
data Sentence 
    = NV Noun Verb
    | NVN Noun Verb Noun
    | IfThen Sentence Sentence
    deriving(Eq, Show)

data Noun
    = AN Adjective Noun
    | AND Noun Noun
    | People
    | Avocados
    deriving(Eq, Show)

data Adjective
    = AA Adjective Adjective
    | Big
    | Tasty
    deriving(Eq, Show)

data Verb
    = Eat
    | Exist
    deriving(Eq, Show)

s :: Sentence
s = IfThen (NV People Exist) (NVN People Eat (AN (AA Big Tasty) Avocados))


type Prog = [Cmd]
data Cmd = Grab | Release | Reach Int deriving(Eq, Show)

data Claw = Open | Closed  deriving(Eq, Show)-- state of the claw, either open or closed
type Arm = (Int, Claw)     -- state of the arm: arm position and claw state

cmd :: Cmd -> Arm -> Maybe Arm
cmd Grab    (i, c)   | c == Closed = Nothing
                     | otherwise   = Just (i, Closed)
cmd Release (i,c)    | c == Open   = Nothing
                     | otherwise   = Just(i, Open)
cmd (Reach x) (y, c) | x+y < 0     = Nothing
                     | otherwise   = Just (x+y, c)

prog :: Prog -> Arm -> Maybe Arm
prog [] a    = Just a
prog (h:t) a = case (cmd h a) of Nothing -> Nothing
                                 Just a' -> prog t a'

data Shape
    = Circle Int
    | Rectangle Int Int
    | Scale Int Shape
    deriving(Eq, Show)

area :: Shape -> Float
area = undefined

flip   :: (a -> b -> c) -> b -> a -> c
flip = undefined