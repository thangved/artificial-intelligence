
(define (domain hanoi)

    (:requirements :strips)

    (:predicates
        (clear ?x)
        (on ?x ?y)
        (lager ?x ?y)
    )

    (:action move
        :parameters (?disc ?from ?to)
        :precondition (and (lager ?to ?disc) (on ?disc ?from) (clear ?disc) (clear ?to))
        :effect (and (clear ?from) (on ?disc ?to) (not (on ?disc ?from)) (not (clear ?to)))
    )

)