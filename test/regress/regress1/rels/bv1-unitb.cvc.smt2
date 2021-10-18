; EXPECT: unsat
(set-option :incremental false)
(set-logic ALL)
(declare-datatypes ((unitb 0)) (((ub (data (_ BitVec 1))))))

(declare-fun x () (Set (Tuple (_ BitVec 1) unitb (_ BitVec 1))))
(declare-fun y () (Set (Tuple (_ BitVec 1) unitb (_ BitVec 1))))
(declare-fun a () (_ BitVec 1))
(declare-fun b () (_ BitVec 1))
(declare-fun c () (_ BitVec 1))
(declare-fun d () (_ BitVec 1))
(declare-fun e () (_ BitVec 1))
(declare-fun u () unitb)
(assert (not (= b c)))
(assert (member (tuple a u b) x))
(assert (member (tuple a u c) x))
(assert (member (tuple d u a) y))
(assert (not (member (tuple a u u a) (join x y))))
(check-sat)
