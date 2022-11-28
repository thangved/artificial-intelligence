men(john).
men(fred).
men(harry).

woman(mary).
woman(julie).
woman(susan).
woman(anne).

blonde(john).
blonde(susan).
blonde(julie).

dark(fred).
dark(harry).

brunette(mary).
brunette(anne).

rich(X) :- gold(X).

gold(fred).
gold(julie).

men(X),
woman(Y) :-
    like(X, Y),
    like(Y, X).

like(john, X) :-
    rich(X),
    blonde(X).

like(harry, X) :-
    rich(X).

like(fred, X) :-
    brunette(X).

like(mary, X) :-
    dark(X).

like(julie, X) :-
    dark(X),
    rich(X).

have(anne, house).
have(john, car).
