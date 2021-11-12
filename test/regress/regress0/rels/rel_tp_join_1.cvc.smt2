; EXPECT: unsat
(set-option :incremental false)
(set-logic ALL)

(declare-fun x () (Set (Tuple Int Int)))
(declare-fun y () (Set (Tuple Int Int)))
(declare-fun z () (Set (Tuple Int Int)))
(declare-fun r () (Set (Tuple Int Int)))
(declare-fun b () (Tuple Int Int))
(assert (= b (tuple 1 7)))
(declare-fun c () (Tuple Int Int))
(assert (= c (tuple 2 3)))
(assert (set.member b x))
(assert (set.member c x))
(declare-fun d () (Tuple Int Int))
(assert (= d (tuple 7 3)))
(declare-fun e () (Tuple Int Int))
(assert (= e (tuple 4 7)))
(assert (set.member d y))
(assert (set.member e y))
(assert (set.member (tuple 3 4) z))
(declare-fun a () (Tuple Int Int))
(assert (= a (tuple 4 1)))
(assert (= r (rel.join (rel.join x y) z)))
(assert (not (set.member a (rel.transpose r))))
(check-sat)
