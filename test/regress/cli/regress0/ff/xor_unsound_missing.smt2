; REQUIRES: cocoa
; EXPECT: sat
; XOR compilation strategy
; unsound because of a missing bit-constraint.
(set-info :smt-lib-version 2.6)
(set-info :category "crafted")
(set-logic QF_FF)
(declare-fun f0 () (_ FiniteField 11))
(declare-fun f1 () (_ FiniteField 11))
(declare-fun f2 () (_ FiniteField 11))
(declare-fun f3 () (_ FiniteField 11))
(declare-fun sum () (_ FiniteField 11))
(declare-fun d0 () (_ FiniteField 11))
(declare-fun d1 () (_ FiniteField 11))
(declare-fun d2 () (_ FiniteField 11))
(declare-fun b0 () Bool)
(declare-fun b1 () Bool)
(declare-fun b2 () Bool)
(declare-fun b3 () Bool)
(define-fun b_to_f ((b Bool)) (_ FiniteField 11) (ite b #f1m11 #f0m11))
(define-fun f_to_b ((f (_ FiniteField 11))) Bool (not (= f #f0m11)))
(define-fun is_bit ((f (_ FiniteField 11))) Bool (or (= f #f0m11) (= f #f1m11)))
(declare-fun m () (_ FiniteField 11))
(declare-fun is_zero () (_ FiniteField 11))
(assert (not (=>
  (and (is_bit f0)
       (is_bit f1)
       (is_bit f2)
       (is_bit f3)
       (= (ff.add f0 f1 f2 f3) sum)
       (= (ff.add d0 (ff.mul #f2m11 d1) (ff.mul #f4m11 d2)) sum)
       (is_bit d0)
       (is_bit d1)
       ; (is_bit d2) this is missing
       )
  (= (f_to_b d0) (xor (f_to_b f0) (f_to_b f1) (f_to_b f2) (f_to_b f3)))
)))
(check-sat)
