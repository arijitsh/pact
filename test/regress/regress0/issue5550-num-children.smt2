; EXPECT: sat
(set-logic UFC)
(declare-sort a 0)
(declare-fun b () a)
(assert (not (_ fmf.card a 1)))
(check-sat)
