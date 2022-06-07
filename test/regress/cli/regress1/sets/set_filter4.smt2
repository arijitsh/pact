(set-logic HO_ALL)
(set-info :status unsat)
(declare-fun A () (Set Int))
(declare-fun B () (Set Int))
(declare-fun element () Int)
(declare-fun p (Int) Bool)
(assert (= B (set.filter p A)))
(assert (p element))
(assert (not (set.member element A)))
(assert (set.member element B))
(check-sat)
