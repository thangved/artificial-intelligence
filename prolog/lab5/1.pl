:- style_check(-singleton).

luythua(X, 0, 1).
luythua(1, N, Y) :-
    Y is 1.
luythua(X, 1, Y) :-
    Y is X.
luythua(X, N, Y) :-
    N > 1,
    N1 is N - 1,
    luythua(X, N1, Y1),
    Y is Y1 * X.

inform(X, Y):-
    write(['Chuyen 1 dia tu cot ', X, ' sang cot ', Y]),
    nl.

hanoi(N):-
    move(N,left, center, right).
move(0,_,_,_):- ! .
move(N, A, B, C):-
    M is N-1,
    move(M, A, C, B),
    inform(A, B),
    move(M, C, B, A).
