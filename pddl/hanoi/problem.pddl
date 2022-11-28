(define (problem problem_name)
    (:domain hanoi)
    (:objects
        peg1 peg2 peg3 d1 d2 d3 d4 d5 d6
    )

    (:init
        (lager peg1 d1)
        (lager peg1 d2)
        (lager peg1 d3)
        (lager peg1 d4)
        (lager peg1 d5)
        (lager peg1 d6)

        (lager peg2 d1)
        (lager peg2 d2)
        (lager peg2 d3)
        (lager peg2 d4)
        (lager peg2 d5)
        (lager peg2 d6)

        (lager peg3 d1)
        (lager peg3 d2)
        (lager peg3 d3)
        (lager peg3 d4)
        (lager peg3 d5)
        (lager peg3 d6)

        (lager d2 d1)

        (lager d3 d1)
        (lager d3 d2)

        (lager d4 d1)
        (lager d4 d2)
        (lager d4 d3)

        (lager d5 d1)
        (lager d5 d2)
        (lager d5 d3)
        (lager d5 d4)

        (lager d6 d1)
        (lager d6 d2)
        (lager d6 d3)
        (lager d6 d4)
        (lager d6 d5)

        (clear peg2)
        (clear peg3)
        (clear d1)

        (on d6 peg1)
        (on d5 d6)
        (on d4 d5)
        (on d3 d4)
        (on d2 d3)
        (on d1 d2)
    )

    (:goal
        (and
            (on d6 peg3)
            (on d5 d6)
            (on d4 d5)
            (on d3 d4)
            (on d2 d3)
            (on d1 d2)
        )
    )

)