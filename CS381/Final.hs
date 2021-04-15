module Final where

data Reg = A | B
    deriving(Eq, Show)

data Expr 
    = Lit Int
    | Ref Reg
    | Add Expr Expr
    deriving(Eq, Show)

data Stmt
    = Assign Reg Expr
    | Swap
    | IfElse Stmt Stmt
    deriving(Eq, Show)

data Prog
    = Seq Stmt Prog
    | End
    deriving(Eq, Show)

example :: Prog
example = Seq (Assign A (Lit 2))
          (Seq (Assign B (Add (Ref A) (Lit 3)))
          (Seq (IfElse Swap (Assign B (Add (Ref A) (Ref B))))
          End))

type Value = (Reg, Int)
type Env = [Value]

start :: Env
start = [(A, 0), (B, 0)]

expr :: Env -> Expr -> Int
expr _ (Lit i)   = i
expr e (Ref r)   = case (lookup r e) of
                   Just x -> x
expr e (Add a b) = (expr e a) + (expr e b)

stmt :: Env -> Stmt -> Env
stmt e (Assign A x) = [(A, expr e x), (B, expr e (Ref B))]
stmt e (Assign B x) = [(A, expr e (Ref A)), (B, expr e x)]
stmt e (Swap)       = [(A, expr e (Ref B)), (B, expr e (Ref A))]
stmt e (IfElse a b) = case (first < second) of
                          True  -> stmt e a
                          False -> stmt e b
                      where 
                          first = expr e (Ref A)
                          second = expr e (Ref B)