; COMMAND-LINE: -q
; EXPECT: sat
(set-logic ALL)
(set-info :status sat)
(declare-fun a () Int)
(declare-fun b () Int)
(declare-fun c () Int)
(declare-fun d () Int)
(declare-fun e () Int)
(declare-fun f () Int)
(declare-fun g () Int)
(assert (> 0 (* a (mod 0 b))))
(assert (or (and (> (* b d) (* 2 (+ g c))) (= g (- c)) (> (+ e c) 0)) (> f 0)))
(check-sat)
