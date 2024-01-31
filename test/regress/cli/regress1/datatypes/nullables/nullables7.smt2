(set-logic HO_ALL)
(set-info :status sat)
(set-option :produce-models true)
(declare-fun a () (Nullable Bool))
(declare-fun b () (Nullable Bool))
(declare-fun c () (Nullable Bool))
(declare-fun x () (Nullable Int))
(declare-fun y () (Nullable Int))
(declare-fun z () (Nullable Int))
(declare-fun f (Int Int) Int)
(assert (distinct a b c))
(assert (distinct x y z))
(assert (= y (nullable.some 5)))
(assert (= z ((_ nullable.lift f) x y)))
(assert (= (f (nullable.val x) (nullable.val y)) (nullable.val z)))
(check-sat)