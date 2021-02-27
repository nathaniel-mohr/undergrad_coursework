-- Group members:
--  * Nathaniel Mohr, 932583202
--
-- Grading notes: 15pts total
--  * 2pts checkExpr
--  * 4pts checkCmd
--  * 1pt checkBlock
--  * 1pt checkDef
--  * 2pts expr
--  * 5pts cmd
--  * + extra credit (typically 1-5pts)
--
-- Supporting files:
--
--  * MiniLogo.hs -- Defines the syntax of MiniLogo, pretty printing functions,
--    and the environment types that you'll need to implement the semantics.
--    Also includes functions to generate example MiniLogo programs to test with.
--
--  * Render.hs -- Defines the Point and Line types used in the semantics, plus
--    code for rendering the semantics of MiniLogo programs in HTML5.
--
module HW5 where

import MiniLogo
import Render


-- Note: in this file, we're placing the AST argument as the *last* argument in
-- each function, rather than the first argument. Although this makes the
-- semantic domains less obvious, it's good FP style since it promotes partial
-- application and can make some of your definitions a bit simpler.


-- Some functions from the Prelude that may be helpful on this assignment:
--
--   all :: (a -> Bool) -> [a] -> Bool
--     Returns true if the function returns true for every element in the list.
--
--   elem :: Eq a => a -> [a] -> Bool
--     Returns true if the first argument is contained as an element in the list.


-- This comment is defining some MiniLogo expressions used in doctests.
--
-- $setup
-- >>> let exprXY = Mul (Ref "y") (Add (Lit 3) (Ref "x"))
-- >>> let exprXZ = Add (Mul (Ref "x") (Lit 4)) (Ref "z")


--
-- * Static checker
--


-- | Statically check that a MiniLogo program is well formed. This function
--   builds up the map 'ms' that contains the defined macros and their arity
--   (i.e. the number of arguments they require), then checks all of the macro
--   definitions, and finally checks the main macro.
--
--   >>> check (xboxes 5 3)
--   True
--
--   >>> check (Program [line,xbox] [])
--   False
--
check :: Prog -> Bool
check (Program defs main) =
    all (checkDef arities) defs && checkBlock arities [] main
  where 
    entry (Define m ps _) = (m, length ps)
    arities = map entry defs



-- | Statically check that an expression is well formed by checking that there
--   are no unbound variables. This function receives as an argument a list of
--   all of the variables that are declared in the scope of the expression.
--
--   >>> checkExpr ["x"] (Ref "x")
--   True
--
--   >>> checkExpr ["y"] (Ref "x")
--   False
--
--   >>> checkExpr ["x","y"] exprXY
--   True
--
--   >>> checkExpr ["x","y"] exprXZ
--   False
--
checkExpr :: [Var] -> Expr -> Bool
checkExpr _ (Lit _)    = True
checkExpr v (Ref a)    = elem a v
checkExpr v (Add x y)  = checkExpr v x && checkExpr v y 
checkExpr v (Mul x y)  = checkExpr v x && checkExpr v y

-- | Statically check that a command is well formed by: (1) checking whether
--   all expressions it contains are well formed, (2) checking whether every
--   macro that is called has been defined, and (3) checking whether every
--   macro is called with the correct number of arguments. The first argument
--   to this function is a map containing the declared macros as keys and the
--   number of arguments they expect (their "arity") as values.
--
--   >>> checkCmd [] ["x","y"] (Move exprXY exprXZ)
--   False
--
--   >>> checkCmd [] ["x","y","z"] (Move exprXY exprXZ)
--   True
--
--   >>> checkCmd [] [] (Call "foo" [Lit 2, Lit 3])
--   False
--
--   >>> checkCmd [("f",2)] [] (Call "f" [Lit 2, Lit 3])
--   True
--
--   >>> checkCmd [("f",2)] [] (Call "f" [Lit 2, Lit 3, Lit 4])
--   False
--
--   >>> checkCmd [("f",2)] ["x","y","z"] (Call "f" [exprXZ, exprXY])
--   True
--
--   >>> checkCmd [("f",2)] ["x","y"] (Call "f" [exprXZ, exprXY])
--   False
--
--   >>> checkCmd [] [] (For "z" (Lit 1) (Lit 100) [Move (Ref "z") (Ref "z")])
--   True
--
--   >>> checkCmd [] [] (For "z" (Lit 1) (Lit 100) [Pen Up, Call "f" [Ref "z"]])
--   False
--
--   >>> checkCmd [("f",1)] [] (For "z" (Lit 1) (Lit 100) [Pen Up, Call "f" [Ref "z"]])
--   True
--
--   >>> checkCmd [("f",1)] [] (For "z" (Lit 1) (Lit 100) [Pen Up, Call "f" [exprXZ]])
--   False
--
--   >>> checkCmd [("f",1)] ["x"] (For "z" (Lit 1) (Lit 100) [Pen Up, Call "f" [exprXZ]])
--   True
--
--   >>> checkCmd [("f",1)] ["x"] (For "z" (Lit 1) (Lit 100) [Pen Up, Call "f" [exprXY]])
--   False
--
--   >>> checkCmd [("f",1)] ["x"] (For "z" exprXY (Lit 100) [Pen Up, Call "f" [exprXZ]])
--   False
--
--   >>> checkCmd [("f",1)] ["x"] (For "z" (Lit 1) exprXY [Pen Up, Call "f" [exprXZ]])
--   False
--
--   >>> checkCmd [("f",1)] ["x","y"] (For "z" exprXY exprXY [Pen Up, Call "f" [exprXZ]])
--   True
--
checkCmd :: Map Macro Int -> [Var] -> Cmd -> Bool
checkCmd _  _  (Pen _)       = True
checkCmd _  vs (Move x y)    = p && q
                               where 
                                   p = checkExpr vs x
                                   q = checkExpr vs y
checkCmd ms vs (Call m v)    = p && q
                               where
                                   p = elem (m, length v) ms
                                   q = all (checkExpr vs) v 
checkCmd m  vs (For v x y b) = p && q && r
                               where
                                   p = checkExpr vs x
                                   q = checkExpr vs y
                                   r = all (checkCmd m (vs ++ [v])) b



-- | Statically check whether all of the commands in a block are well formed.
--
--   >>> checkBlock [] [] []
--   True
--
--   >>> checkBlock [] ["x","y"] [Pen Up, Move exprXY exprXZ, Pen Down]
--   False
--
--   >>> checkBlock [] ["x","y","z"] [Pen Up, Move exprXY exprXZ, Pen Down]
--   True

--   >>> checkBlock [] ["x","y"] [Pen Up, Call "f" [exprXY], Pen Down]
--   False
--
--   >>> checkBlock [("f",2)] ["x","y"] [Pen Up, Call "f" [exprXY], Pen Down]
--   False
--
--   >>> checkBlock [("f",2)] ["x","y"] [Pen Up, Call "f" [exprXY,exprXZ], Pen Down]
--   False
--
--   >>> checkBlock [("f",2)] ["x","y","z"] [Pen Up, Call "f" [exprXY,exprXZ], Pen Down]
--   True
--
checkBlock :: Map Macro Int -> [Var] -> Block -> Bool
checkBlock m v b = all (checkCmd m v) b



-- | Check whether a macro definition is well formed.
--
--   >>> checkDef [] (Define "f" [] [Pen Down, Move (Lit 2) (Lit 3), Pen Up])
--   True
--
--   >>> checkDef [] (Define "f" [] [Pen Down, Move exprXY exprXZ, Pen Up])
--   False
--
--   >>> checkDef [] (Define "f" ["x","y","z"] [Pen Down, Move exprXY exprXZ, Pen Up])
--   True
--
--   >>> checkDef [] (Define "f" ["x","y","z"] [Pen Down, Call "g" [exprXY,exprXZ], Pen Up])
--   False
--
--   >>> checkDef [("g",3)] (Define "f" ["x","y","z"] [Pen Down, Call "g" [exprXY,exprXZ], Pen Up])
--   False
--
--   >>> checkDef [("g",3)] (Define "f" ["x","y","z"] [Pen Down, Call "g" [exprXY,exprXZ,exprXY], Pen Up])
--   True
--
checkDef :: Map Macro Int -> Def -> Bool
checkDef f (Define _ p b) = checkBlock f p b



--
-- * Semantics of MiniLogo
--

-- | The state of the pen, which includes whether it is up or down and its
--   current location.
type State = (Mode, Point)

-- | The initial state of the pen.
initPen :: State
initPen = (Up, (0,0))


-- | Run a MiniLogo program by:
--    1. Statically checking for errors. If it fails the check, stop here.
--    2. Run the semantics to produce a bunch of lines.
--    3. Pass those lines to the renderer.
--
--   Once your checker and semantic function are working, you should be
--   able to apply 'draw' to a MiniLogo program, then load the file
--   MiniLogo.html in your browswer to view the rendered image.
draw :: Prog -> IO ()
draw p | check p   = toHTML (prog p)
       | otherwise = putStrLn "failed static check :-("


-- ** Semantic functions

-- In this section, we're assuming we already ran the static checker. This
-- means that you can use the 'getOrFail' function to lookup entries in either
-- the variable environment or macro environment, and you can use the 'setAll'
-- function to add arguments to an environment without first checking that you
-- have the correct number.
--
-- Remember that in this assignment we're making the AST type the last argument
-- in each function to support a nicer functional programming style, even
-- though this obfuscates the semantic domains a bit. The semantic domain of
-- each syntactic category is listed below for reference and then briefly
-- explained.
--
-- Semantic domains:
--   * Expr:  Env -> Int
--   * Cmd:   Macros -> Env -> State -> (State, [Line])
--   * Block: Macros -> Env -> State -> (State, [Line])
--   * Prog:  [Line]
--
-- The semantics of expressions requires only the variable environment, and
-- this environment is read-only since expressions cannot change the values of
-- variables.

-- In addition to the variable environment, the semantics of commands and
-- blocks also takes a macro environment (Macros), which stores macro
-- definitions. The macro environment maps macro names to a pair
-- '(Pars,Block)', where the first element of the pair is the list of
-- parameters that the macro declares, and second element is the body of the
-- macro. You will have to use the macro environment in the semantics of
-- commands to implement macro calls.
--
-- Unlike in Homework 4, commands may now produce an arbitrary number of lines
-- (not just 0 or 1) because of macro calls and for loops. So, the semantic
-- domain of commands now produces a list of lines rather than a 'Maybe Line'.
--
-- Programs are run on initially empty environments and a well-defined initial
-- pen state (Up,(0,0)), so the semantic function doesn't take any arguments
-- besides the program itself. We also return only the lines drawn by the
-- program as a result since we no longer care about the pen state once the
-- program has completely finished running.



-- | Semantics of expressions.
--
--   >>> let env = [("x",3),("y",4)]
--
--   >>> expr env (Mul (Ref "y") (Add (Lit 5) (Ref "x")))
--   32
--
--   >>> expr env (Add (Mul (Ref "x") (Lit 5)) (Mul (Lit 6) (Ref "y")))
--   39
--
expr :: Env -> Expr -> Int
expr _ (Lit a) = a
expr a (Ref x) = getOrFail x a
expr a (Add f g) = expr a f + expr a g
expr a (Mul f g) = expr a f * expr a g



-- | Semantics of commands.
--
--   >>> let vs = [("x",3),("y",4)]
--   >>> let Define _ ps b = line
--   >>> let ms = [("m1",([],[])),("line",(ps,b)),("m2",([],[]))]
--   
--   >>> cmd [] [] (Up,(2,3)) (Pen Down)
--   ((Down,(2,3)),[])
--
--   >>> cmd [] [] (Down,(2,3)) (Pen Up)
--   ((Up,(2,3)),[])
--
--   >>> cmd [] vs (Up,(2,3)) (Move (Ref "y") (Add (Ref "x") (Lit 2)))
--   ((Up,(4,5)),[])
--
--   >>> cmd [] vs (Down,(2,3)) (Move (Ref "y") (Add (Ref "x") (Lit 2)))
--   ((Down,(4,5)),[((2,3),(4,5))])
--
--   >>> cmd ms vs (Up,(0,0)) (Call "m1" [])
--   ((Up,(0,0)),[])
--
--   >>> cmd ms vs (Down,(0,0)) (Call "line" [Ref "x", Ref "y", Add (Ref "x") (Lit 2), Add (Ref "y") (Lit 3)])
--   ((Down,(5,7)),[((3,4),(5,7))])
--
--   >>> cmd [] vs (Down,(0,0)) (For "i" (Lit 1) (Ref "x") [])
--   ((Down,(0,0)),[])
--
--   >>> cmd ms vs (Down,(0,0)) (For "i" (Lit 1) (Ref "y") [Move (Ref "i") (Ref "i")])
--   ((Down,(4,4)),[((0,0),(1,1)),((1,1),(2,2)),((2,2),(3,3)),((3,3),(4,4))])
--
--   >>> cmd ms vs (Down,(0,0)) (For "i" (Ref "x") (Lit 1) [Call "line" [Ref "i", Ref "i", Mul (Ref "x") (Ref "i"), Mul (Ref "y") (Ref "i")]])
--   ((Down,(3,4)),[((3,3),(9,12)),((2,2),(6,8)),((1,1),(3,4))])
--
cmd :: Macros -> Env -> State -> Cmd -> (State, [Line])
cmd defs env state@(pen,pos) c = case c of

    Pen Up   -> ((Up, pos), [])
    Pen Down -> ((Down, pos), [])

    Move xExp yExp -> if pen == Down 
                         then ((pen, newPos), [((pos), newPos)]) 
                      else  ((pen, newPos), [])
                      where
                          newPos = (expr env xExp, expr env yExp)
    Call macro args -> let parsBlock = getOrFail macro defs
                       in let pars = fst parsBlock
                              body = snd parsBlock
                       in let callEnv = setAll pars (map (expr env) args) env
                       in block defs callEnv state body
                      
    For v fromExp toExp body ->

      let from = expr env fromExp
          to   = expr env toExp
          ixs  = if from <= to then [from .. to] else reverse [to .. from]

          -- This helper function runs the body of the loop once, with the loop
          -- index set to the given integer. You just need to study the code
          -- and fill in the undefined part that runs the body of the loop.
          loopStep :: (State, [Line]) -> Int -> (State, [Line])
          loopStep (s, ls) i =
            let (s', ls') = block defs (set v i env) s body
            in (s', ls ++ ls')

      in foldl loopStep (state, []) ixs



-- | Semantics of blocks.
--
--   >>> block [] [] (Down,(0,0)) []
--   ((Down,(0,0)),[])
--
--   >>> block [] [] (Down,(0,0)) [Pen Down, Pen Up, Pen Up, Move (Lit 2) (Lit 3)]
--   ((Up,(2,3)),[])
--
--   >>> block [] [] (Down,(0,0)) [Pen Up, Move (Lit 2) (Lit 3), Pen Down, Move (Lit 4) (Lit 5), Move (Lit 6) (Lit 7)]
--   ((Down,(6,7)),[((2,3),(4,5)),((4,5),(6,7))])
-- 
block :: Macros -> Env -> State -> Block -> (State, [Line])
block defs env state = go state []
  where
    go s ls []     = (s,ls)
    go s ls (c:cs) = let (s',ls') = cmd defs env s c
                     in go s' (ls ++ ls') cs



-- | Semantic function for programs.
prog :: Prog -> [Line]
prog (Program defs main) = snd $ block (map entry defs) [] initPen main
  where
    entry (Define m ps b) = (m, (ps,b))


--
-- * Amazing picture (extra credit)
--

-- | A MiniLogo program that draws your amazing picture.
amazing :: Prog
amazing = Program [line,hi,box,xbox,steps]
    [ 
      -- Head
      Call "line" [Lit 32, Lit 20, Lit 38, Lit 20],
      Call "line" [Lit 30, Lit 22, Lit 30, Lit 30],
      Call "line" [Lit 40, Lit 22, Lit 40, Lit 30],
      Call "line" [Lit 32, Lit 20, Lit 30, Lit 22],
      Call "line" [Lit 38, Lit 20, Lit 40, Lit 22],

      -- Hair
      For "j" (Lit 0) (Lit 2) 
          [For "i" (Lit 0) (Add (Lit 9) (Mul (Lit (-2)) (Ref "j")))
              [Call "xbox" [Add (Add (Lit 30) (Ref "i")) (Ref "j"), Add (Lit 30) (Ref "j"), Lit 1, Lit 1]]],

      -- Eyes
      Call "box" [Lit 32, Lit 26, Lit 2, Lit 2],
      Call "xbox" [Lit 33, Lit 26, Lit 1, Lit 1],
      Call "box" [Lit 36, Lit 26, Lit 2, Lit 2],
      Call "xbox" [Lit 37, Lit 26, Lit 1, Lit 1],

      -- Mouth
      Call "line" [Lit 32, Lit 23, Lit 33, Lit 22],
      Call "line" [Lit 38, Lit 23, Lit 37, Lit 22],
      Call "line" [Lit 33, Lit 22, Lit 37, Lit 22],

      -- THE HEAPHONES
      Call "line" [Lit 30, Lit 25, Lit 29, Lit 26],
      Call "line" [Lit 29, Lit 26, Lit 29, Lit 28],
      Call "line" [Lit 29, Lit 28, Lit 30, Lit 29],
      Call "line" [Lit 29, Lit 27, Lit 28, Lit 29],
      Call "line" [Lit 28, Lit 29, Lit 31, Lit 34],
      Call "line" [Lit 31, Lit 34, Lit 39, Lit 34],
      Call "line" [Lit 39, Lit 34, Lit 42, Lit 29],
      Call "line" [Lit 42, Lit 29, Lit 41, Lit 27],
      Call "line" [Lit 41, Lit 26, Lit 40, Lit 25],
      Call "line" [Lit 41, Lit 26, Lit 41, Lit 28],
      Call "line" [Lit 41, Lit 28, Lit 40, Lit 29],
      Call "line" [Lit 41, Lit 26, Lit 38, Lit 21],
      Call "xbox" [Lit 37, Lit 20, Lit 1, Lit 1],

      Call "hi" [Lit 44, Lit 25],

      -- C
      Call "line" [Lit 34, Lit 7, Lit 34, Lit 6],
      Call "line" [Lit 34, Lit 6, Lit 33, Lit 5],
      Call "line" [Lit 28, Lit 5, Lit 33, Lit 5],
      Call "line" [Lit 28, Lit 5, Lit 27, Lit 6],
      Call "line" [Lit 27, Lit 6, Lit 27, Lit 14],
      Call "line" [Lit 27, Lit 14, Lit 28, Lit 15],
      Call "line" [Lit 28, Lit 15, Lit 33, Lit 15],
      Call "line" [Lit 34, Lit 13, Lit 34, Lit 14],
      Call "line" [Lit 34, Lit 14, Lit 33, Lit 15],

      -- S
      Call "line" [Lit 44, Lit 13, Lit 44, Lit 14],
      Call "line" [Lit 44, Lit 14, Lit 43, Lit 15],
      Call "line" [Lit 43, Lit 15, Lit 38, Lit 15],
      Call "line" [Lit 38, Lit 15, Lit 37, Lit 14],
      Call "line" [Lit 37, Lit 14, Lit 37, Lit 11],
      Call "line" [Lit 37, Lit 11, Lit 38, Lit 10],
      Call "line" [Lit 38, Lit 10, Lit 43, Lit 10],
      Call "line" [Lit 43, Lit 10, Lit 44, Lit 9],
      Call "line" [Lit 44, Lit 9, Lit 44, Lit 6],
      Call "line" [Lit 44, Lit 6, Lit 43, Lit 5],
      Call "line" [Lit 43, Lit 5, Lit 38, Lit 5],
      Call "line" [Lit 38, Lit 5, Lit 37, Lit 6],
      Call "line" [Lit 37, Lit 6, Lit 37, Lit 7]
    ]

