(set-logic QF_BV)
(define-fun |def_B definitions| () Bool true)
(assert |def_B definitions|)
(set-info :status sat)
(check-sat)