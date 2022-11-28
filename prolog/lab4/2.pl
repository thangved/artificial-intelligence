food(chicken).
food(apple).
food(X) :-
    eat(Y, X),
    alive(Y).

eat(bill, peanut).
alive(bill).

eat(john, X) :- food(X).

eat(sue, X) :- eat(bill, X).