; EXPECT: sat
(set-logic ALL)
(set-option :incremental false)
(declare-datatypes ((nat 0)(list 0)(tree 0)) (((succ (pred nat)) (zero))((cons (car tree) (cdr list)) (null))((node (children list)) (leaf (data nat)))))
(declare-fun x1 () nat)
(declare-fun x2 () list)
(declare-fun x3 () tree)
(check-sat-assuming ( (not (let ((_let_1 (leaf zero))) (let ((_let_2 (node x2))) (let ((_let_3 (ite ((_ is node) _let_2) (children _let_2) null))) (let ((_let_4 (ite ((_ is cons) _let_3) (car _let_3) _let_1))) (let ((_let_5 (ite ((_ is node) _let_4) (children _let_4) null))) (let ((_let_6 (node null))) (let ((_let_7 (ite ((_ is node) x3) (children x3) null))) (let ((_let_8 (node (cons (node _let_7) x2)))) (let ((_let_9 (cons x3 (ite ((_ is node) _let_8) (children _let_8) null)))) (let ((_let_10 (ite ((_ is cons) _let_7) (car _let_7) _let_1))) (let ((_let_11 (ite ((_ is node) _let_10) (children _let_10) null))) (let ((_let_12 (ite ((_ is cons) _let_11) (cdr _let_11) null))) (let ((_let_13 (ite ((_ is cons) _let_12) (car _let_12) _let_1))) (let ((_let_14 (ite ((_ is node) _let_13) (children _let_13) null))) (let ((_let_15 (ite ((_ is cons) _let_14) (cdr _let_14) null))) (let ((_let_16 (ite ((_ is cons) _let_15) (cdr _let_15) null))) (let ((_let_17 (ite ((_ is cons) _let_16) (cdr _let_16) null))) (let ((_let_18 (ite ((_ is cons) _let_17) (cdr _let_17) null))) (let ((_let_19 (cons (ite ((_ is cons) _let_18) (car _let_18) _let_1) (cons (ite ((_ is cons) _let_9) (car _let_9) _let_1) (cons (leaf (succ (ite ((_ is leaf) _let_6) (data _let_6) zero))) (ite ((_ is cons) _let_5) (cdr _let_5) null)))))) (let ((_let_20 (ite ((_ is cons) _let_19) (cdr _let_19) null))) (let ((_let_21 (ite ((_ is cons) _let_20) (cdr _let_20) null))) (let ((_let_22 (ite ((_ is cons) _let_21) (car _let_21) _let_1))) (let ((_let_23 (ite ((_ is node) _let_22) (children _let_22) null))) (let ((_let_24 (ite ((_ is cons) _let_23) (cdr _let_23) null))) (let ((_let_25 (ite ((_ is cons) _let_24) (cdr _let_24) null))) (let ((_let_26 (node (ite ((_ is cons) _let_25) (cdr _let_25) null)))) (let ((_let_27 (ite ((_ is leaf) _let_26) (data _let_26) zero))) (not ((_ is zero) (ite ((_ is succ) _let_27) (pred _let_27) zero))))))))))))))))))))))))))))))) ))