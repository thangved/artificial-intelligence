person(marcus).

pompeian(marcus).

roman(X) :- pompeian(X).

ruler(ceasar).

trytoasassin(X, Y) :-
    roman(X),
    not(loyal(X, Y)),
    ruler(Y).

not(loyal(marcus, ceasar)).