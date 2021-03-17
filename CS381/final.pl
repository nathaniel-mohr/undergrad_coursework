plays(alicia, piano).
plays(bjork, flute).
plays(bjork, piano).
plays(jimi, guitar).
plays(miles, trumpet).
plays(norah, guitar).
plays(norah, piano).
plays(yoyo, cello).

instrument(What) :- plays(_, What).

strings(X) :- plays(X, cello). 
strings(X) :- plays(X, guitar).

multi(X) :- plays(X, A), plays(X, B), A \= B.

duet(X, Y) :- plays(X, piano), plays(Y, I), I \= piano, X \= Y.