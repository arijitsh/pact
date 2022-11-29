; COMMAND-LINE: --nl-ext=full
; EXPECT: unsat
; DISABLE-TESTER: unsat-core
(set-logic UFNIA)
(set-info :status unsat)
(set-info :source |Benchmarks from the paper: "Extending Sledgehammer with SMT Solvers" by Jasmin Blanchette, Sascha Bohme, and Lawrence C. Paulson, CADE 2011.  Translated to SMT2 by Andrew Reynolds and Morgan Deters.|)
(set-info :smt-lib-version 2.6)
(set-info :category "industrial")
(declare-sort S1 0)
(declare-sort S2 0)
(declare-sort S3 0)
(declare-sort S4 0)
(declare-sort S5 0)
(declare-sort S6 0)
(declare-sort S7 0)
(declare-sort S8 0)
(declare-sort S9 0)
(declare-sort S10 0)
(declare-sort S11 0)
(declare-sort S12 0)
(declare-sort S13 0)
(declare-sort S14 0)
(declare-sort S15 0)
(declare-sort S16 0)
(declare-sort S17 0)
(declare-sort S18 0)
(declare-sort S19 0)
(declare-sort S20 0)
(declare-sort S21 0)
(declare-sort S22 0)
(declare-sort S23 0)
(declare-sort S24 0)
(declare-sort S25 0)
(declare-sort S26 0)
(declare-sort S27 0)
(declare-sort S28 0)
(declare-sort S29 0)
(declare-sort S30 0)
(declare-sort S31 0)
(declare-sort S32 0)
(declare-sort S33 0)
(declare-sort S34 0)
(declare-sort S35 0)
(declare-sort S36 0)
(declare-sort S37 0)
(declare-sort S38 0)
(declare-sort S39 0)
(declare-sort S40 0)
(declare-sort S41 0)
(declare-sort S42 0)
(declare-sort S43 0)
(declare-sort S44 0)
(declare-sort S45 0)
(declare-sort S46 0)
(declare-sort S47 0)
(declare-sort S48 0)
(declare-sort S49 0)
(declare-sort S50 0)
(declare-sort S51 0)
(declare-sort S52 0)
(declare-sort S53 0)
(declare-sort S54 0)
(declare-sort S55 0)
(declare-sort S56 0)
(declare-sort S57 0)
(declare-sort S58 0)
(declare-sort S59 0)
(declare-sort S60 0)
(declare-sort S61 0)
(declare-sort S62 0)
(declare-sort S63 0)
(declare-sort S64 0)
(declare-sort S65 0)
(declare-sort S66 0)
(declare-sort S67 0)
(declare-sort S68 0)
(declare-sort S69 0)
(declare-sort S70 0)
(declare-sort S71 0)
(declare-sort S72 0)
(declare-sort S73 0)
(declare-sort S74 0)
(declare-sort S75 0)
(declare-sort S76 0)
(declare-sort S77 0)
(declare-sort S78 0)
(declare-sort S79 0)
(declare-sort S80 0)
(declare-sort S81 0)
(declare-sort S82 0)
(declare-sort S83 0)
(declare-sort S84 0)
(declare-sort S85 0)
(declare-sort S86 0)
(declare-sort S87 0)
(declare-sort S88 0)
(declare-sort S89 0)
(declare-sort S90 0)
(declare-sort S91 0)
(declare-sort S92 0)
(declare-sort S93 0)
(declare-fun f1 () S1)
(declare-fun f2 () S1)
(declare-fun f3 (Int) S1)
(declare-fun f4 () Int)
(declare-fun f5 () Int)
(declare-fun f6 (S2 S3) Int)
(declare-fun f7 () S2)
(declare-fun f8 (S4 Int) S3)
(declare-fun f9 (S5 Int) S4)
(declare-fun f10 () S5)
(declare-fun f11 (S6 S3) S1)
(declare-fun f12 (S7 S8) S1)
(declare-fun f13 (S10 S9) S8)
(declare-fun f14 (S11 S9) S10)
(declare-fun f15 () S11)
(declare-fun f16 (S12 S13) S1)
(declare-fun f17 (S15 S14) S13)
(declare-fun f18 (S16 S14) S15)
(declare-fun f19 () S16)
(declare-fun f20 (S17 S14) S1)
(declare-fun f21 (S18 S3) S14)
(declare-fun f22 (S19 Int) S18)
(declare-fun f23 () S19)
(declare-fun f24 (S20 S21) S1)
(declare-fun f25 (S23 S22) S21)
(declare-fun f26 (S24 S22) S23)
(declare-fun f27 () S24)
(declare-fun f28 (S25 S22) S1)
(declare-fun f29 (S26 Int) S22)
(declare-fun f30 (S27 S3) S26)
(declare-fun f31 () S27)
(declare-fun f32 (S28 S9) S1)
(declare-fun f33 (S29 S3) S9)
(declare-fun f34 (S30 S3) S29)
(declare-fun f35 () S30)
(declare-fun f36 (S31 Int) S1)
(declare-fun f37 (S32 Int) S31)
(declare-fun f38 (S6) S32)
(declare-fun f39 (S3 S6) S1)
(declare-fun f40 (S33 S9) S28)
(declare-fun f41 (S7) S33)
(declare-fun f42 (S8 S7) S1)
(declare-fun f43 (S34 S14) S17)
(declare-fun f44 (S12) S34)
(declare-fun f45 (S13 S12) S1)
(declare-fun f46 (S35 S22) S25)
(declare-fun f47 (S20) S35)
(declare-fun f48 (S21 S20) S1)
(declare-fun f49 (S36 Int) S6)
(declare-fun f50 (S17) S36)
(declare-fun f51 (S14 S17) S1)
(declare-fun f52 (S37 S3) S31)
(declare-fun f53 (S25) S37)
(declare-fun f54 (S22 S25) S1)
(declare-fun f55 (S38 S3) S6)
(declare-fun f56 (S28) S38)
(declare-fun f57 (S9 S28) S1)
(declare-fun f58 (S39 S36) S28)
(declare-fun f59 (S31) S39)
(declare-fun f60 (S40 S38) S20)
(declare-fun f61 (S6) S40)
(declare-fun f62 (S41 S9) S7)
(declare-fun f63 (S42 S43) S1)
(declare-fun f64 (S8 S8) S42)
(declare-fun f65 (S44 S41) S43)
(declare-fun f66 (S28) S44)
(declare-fun f67 (S45 S14) S12)
(declare-fun f68 (S46 S47) S1)
(declare-fun f69 (S13 S13) S46)
(declare-fun f70 (S48 S45) S47)
(declare-fun f71 (S17) S48)
(declare-fun f72 (S49 S22) S20)
(declare-fun f73 (S50 S51) S1)
(declare-fun f74 (S21 S21) S50)
(declare-fun f75 (S52 S49) S51)
(declare-fun f76 (S25) S52)
(declare-fun f77 (S53 S3) S28)
(declare-fun f78 (S54 S53) S7)
(declare-fun f79 (S6) S54)
(declare-fun f80 (S55 Int) S28)
(declare-fun f81 (S56 S55) S12)
(declare-fun f82 (S31) S56)
(declare-fun f83 (S6) S1)
(declare-fun f84 (S7) S1)
(declare-fun f85 (S12) S1)
(declare-fun f86 (S20) S1)
(declare-fun f87 (S28) S1)
(declare-fun f88 (S6) S1)
(declare-fun f89 (S7) S1)
(declare-fun f90 (S12) S1)
(declare-fun f91 (S20) S1)
(declare-fun f92 (S28) S1)
(declare-fun f93 (S6) S32)
(declare-fun f94 (S7) S33)
(declare-fun f95 (S12) S34)
(declare-fun f96 (S17) S36)
(declare-fun f97 (S20) S35)
(declare-fun f98 (S25) S37)
(declare-fun f99 (S28) S38)
(declare-fun f100 (S57 S58) S1)
(declare-fun f101 (S59 S59) S57)
(declare-fun f102 (S9 Int) S59)
(declare-fun f103 (S7 S6) S58)
(declare-fun f104 (S60 S61) S1)
(declare-fun f105 (S62 S62) S60)
(declare-fun f106 (S14 Int) S62)
(declare-fun f107 (S12 S6) S61)
(declare-fun f108 (S63 S64) S1)
(declare-fun f109 (S65 S65) S63)
(declare-fun f110 (S22 Int) S65)
(declare-fun f111 (S20 S6) S64)
(declare-fun f112 (S66 S6) S20)
(declare-fun f113 (S28) S66)
(declare-fun f114 (S67 S68) S1)
(declare-fun f115 (S69 S69) S67)
(declare-fun f116 (Int S9) S69)
(declare-fun f117 (S6 S7) S68)
(declare-fun f118 (S70 S71) S1)
(declare-fun f119 (S72 S72) S70)
(declare-fun f120 (Int S14) S72)
(declare-fun f121 (S6 S12) S71)
(declare-fun f122 (S73 S74) S1)
(declare-fun f123 (S75 S75) S73)
(declare-fun f124 (Int S22) S75)
(declare-fun f125 (S6 S20) S74)
(declare-fun f126 (S76 S28) S12)
(declare-fun f127 (S6) S76)
(declare-fun f128 (S77 S6) S28)
(declare-fun f129 (S6) S77)
(declare-fun f130 (S78 S7) S43)
(declare-fun f131 (S7) S78)
(declare-fun f132 (S79 S12) S47)
(declare-fun f133 (S12) S79)
(declare-fun f134 (S80 S20) S51)
(declare-fun f135 (S20) S80)
(declare-fun f136 (S81 S28) S7)
(declare-fun f137 (S28) S81)
(declare-fun f138 (S82) S6)
(declare-fun f139 (S83 S84) Int)
(declare-fun f140 () S83)
(declare-fun f141 (S82 Int) S84)
(declare-fun f142 (S85) S7)
(declare-fun f143 (S85 S9) S84)
(declare-fun f144 (S86) S12)
(declare-fun f145 (S86 S14) S84)
(declare-fun f146 (S87) S20)
(declare-fun f147 (S87 S22) S84)
(declare-fun f148 (S88) S28)
(declare-fun f149 (S88 S3) S84)
(declare-fun f150 (S89 S6) S6)
(declare-fun f151 (S82) S89)
(declare-fun f152 (S90 S7) S7)
(declare-fun f153 (S85) S90)
(declare-fun f154 (S91 S12) S12)
(declare-fun f155 (S86) S91)
(declare-fun f156 (S92 S20) S20)
(declare-fun f157 (S87) S92)
(declare-fun f158 (S93 S28) S28)
(declare-fun f159 (S88) S93)
(declare-fun f160 (S31 S6) S1)
(declare-fun f161 (Int S31) S1)
(declare-fun f162 (S17 S12) S1)
(declare-fun f163 (S25 S20) S1)
(declare-fun f164 (S7 S43) S1)
(declare-fun f165 (S12 S47) S1)
(declare-fun f166 (S20 S51) S1)
(declare-fun f167 (S28 S7) S1)
(declare-fun f168 (S6 S28) S1)
(declare-fun f169 () S82)
(assert (not (= f1 f2)))
(assert (not (= (f3 (* f4 f5)) f1)))
(assert (= (f3 f4) f1))
(assert (= (f3 f5) f1))
(assert (forall ((?v0 Int)) (= (= (f3 ?v0) f1) (exists ((?v1 Int) (?v2 Int)) (= (f6 f7 (f8 (f9 f10 ?v1) ?v2)) ?v0)))))
(assert (forall ((?v0 Int) (?v1 Int) (?v2 Int) (?v3 Int)) (= (* (f6 f7 (f8 (f9 f10 ?v0) ?v1)) (f6 f7 (f8 (f9 f10 ?v2) ?v3))) (f6 f7 (f8 (f9 f10 (+ (* ?v0 ?v2) (* ?v1 ?v3))) (- (* ?v0 ?v3) (* ?v1 ?v2)))))))
(assert (forall ((?v0 S6)) (= (forall ((?v1 S3)) (= (f11 ?v0 ?v1) f1)) (forall ((?v1 Int) (?v2 Int)) (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S7)) (= (forall ((?v1 S8)) (= (f12 ?v0 ?v1) f1)) (forall ((?v1 S9) (?v2 S9)) (= (f12 ?v0 (f13 (f14 f15 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S12)) (= (forall ((?v1 S13)) (= (f16 ?v0 ?v1) f1)) (forall ((?v1 S14) (?v2 S14)) (= (f16 ?v0 (f17 (f18 f19 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S17)) (= (forall ((?v1 S14)) (= (f20 ?v0 ?v1) f1)) (forall ((?v1 Int) (?v2 S3)) (= (f20 ?v0 (f21 (f22 f23 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S20)) (= (forall ((?v1 S21)) (= (f24 ?v0 ?v1) f1)) (forall ((?v1 S22) (?v2 S22)) (= (f24 ?v0 (f25 (f26 f27 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S25)) (= (forall ((?v1 S22)) (= (f28 ?v0 ?v1) f1)) (forall ((?v1 S3) (?v2 Int)) (= (f28 ?v0 (f29 (f30 f31 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S28)) (= (forall ((?v1 S9)) (= (f32 ?v0 ?v1) f1)) (forall ((?v1 S3) (?v2 S3)) (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 Int) (?v1 Int) (?v2 Int) (?v3 Int)) (= (= (f8 (f9 f10 ?v0) ?v1) (f8 (f9 f10 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 S9) (?v1 S9) (?v2 S9) (?v3 S9)) (= (= (f13 (f14 f15 ?v0) ?v1) (f13 (f14 f15 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 S14) (?v1 S14) (?v2 S14) (?v3 S14)) (= (= (f17 (f18 f19 ?v0) ?v1) (f17 (f18 f19 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 Int) (?v1 S3) (?v2 Int) (?v3 S3)) (= (= (f21 (f22 f23 ?v0) ?v1) (f21 (f22 f23 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 S22) (?v1 S22) (?v2 S22) (?v3 S22)) (= (= (f25 (f26 f27 ?v0) ?v1) (f25 (f26 f27 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 S3) (?v1 Int) (?v2 S3) (?v3 Int)) (= (= (f29 (f30 f31 ?v0) ?v1) (f29 (f30 f31 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 S3) (?v1 S3) (?v2 S3) (?v3 S3)) (= (= (f33 (f34 f35 ?v0) ?v1) (f33 (f34 f35 ?v2) ?v3)) (and (= ?v0 ?v2) (= ?v1 ?v3)))))
(assert (forall ((?v0 Int) (?v1 Int) (?v2 Int) (?v3 Int)) (=> (= (f8 (f9 f10 ?v0) ?v1) (f8 (f9 f10 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S9) (?v1 S9) (?v2 S9) (?v3 S9)) (=> (= (f13 (f14 f15 ?v0) ?v1) (f13 (f14 f15 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S14) (?v1 S14) (?v2 S14) (?v3 S14)) (=> (= (f17 (f18 f19 ?v0) ?v1) (f17 (f18 f19 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 Int) (?v1 S3) (?v2 Int) (?v3 S3)) (=> (= (f21 (f22 f23 ?v0) ?v1) (f21 (f22 f23 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S22) (?v1 S22) (?v2 S22) (?v3 S22)) (=> (= (f25 (f26 f27 ?v0) ?v1) (f25 (f26 f27 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S3) (?v1 Int) (?v2 S3) (?v3 Int)) (=> (= (f29 (f30 f31 ?v0) ?v1) (f29 (f30 f31 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S3) (?v1 S3) (?v2 S3) (?v3 S3)) (=> (= (f33 (f34 f35 ?v0) ?v1) (f33 (f34 f35 ?v2) ?v3)) (=> (=> (= ?v0 ?v2) (=> (= ?v1 ?v3) false)) false))))
(assert (forall ((?v0 S6) (?v1 Int) (?v2 Int)) (= (= (f36 (f37 (f38 ?v0) ?v1) ?v2) f1) (= (f39 (f8 (f9 f10 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S7) (?v1 S9) (?v2 S9)) (= (= (f32 (f40 (f41 ?v0) ?v1) ?v2) f1) (= (f42 (f13 (f14 f15 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S12) (?v1 S14) (?v2 S14)) (= (= (f20 (f43 (f44 ?v0) ?v1) ?v2) f1) (= (f45 (f17 (f18 f19 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S20) (?v1 S22) (?v2 S22)) (= (= (f28 (f46 (f47 ?v0) ?v1) ?v2) f1) (= (f48 (f25 (f26 f27 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S17) (?v1 Int) (?v2 S3)) (= (= (f11 (f49 (f50 ?v0) ?v1) ?v2) f1) (= (f51 (f21 (f22 f23 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S25) (?v1 S3) (?v2 Int)) (= (= (f36 (f52 (f53 ?v0) ?v1) ?v2) f1) (= (f54 (f29 (f30 f31 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S28) (?v1 S3) (?v2 S3)) (= (= (f11 (f55 (f56 ?v0) ?v1) ?v2) f1) (= (f57 (f33 (f34 f35 ?v1) ?v2) ?v0) f1))))
(assert (forall ((?v0 S31) (?v1 Int) (?v2 Int) (?v3 Int) (?v4 S36)) (let ((?v_0 (f9 f10 ?v1))) (=> (= (f36 ?v0 ?v1) f1) (=> (= (f39 (f8 (f9 f10 ?v2) ?v3) (f49 ?v4 ?v1)) f1) (= (f57 (f33 (f34 f35 (f8 ?v_0 ?v2)) (f8 ?v_0 ?v3)) (f58 (f59 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S6) (?v1 S3) (?v2 Int) (?v3 Int) (?v4 S38)) (let ((?v_0 (f30 f31 ?v1))) (=> (= (f11 ?v0 ?v1) f1) (=> (= (f39 (f8 (f9 f10 ?v2) ?v3) (f55 ?v4 ?v1)) f1) (= (f48 (f25 (f26 f27 (f29 ?v_0 ?v2)) (f29 ?v_0 ?v3)) (f60 (f61 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S28) (?v1 S9) (?v2 S9) (?v3 S9) (?v4 S41)) (let ((?v_0 (f14 f15 ?v1))) (=> (= (f32 ?v0 ?v1) f1) (=> (= (f42 (f13 (f14 f15 ?v2) ?v3) (f62 ?v4 ?v1)) f1) (= (f63 (f64 (f13 ?v_0 ?v2) (f13 ?v_0 ?v3)) (f65 (f66 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S17) (?v1 S14) (?v2 S14) (?v3 S14) (?v4 S45)) (let ((?v_0 (f18 f19 ?v1))) (=> (= (f20 ?v0 ?v1) f1) (=> (= (f45 (f17 (f18 f19 ?v2) ?v3) (f67 ?v4 ?v1)) f1) (= (f68 (f69 (f17 ?v_0 ?v2) (f17 ?v_0 ?v3)) (f70 (f71 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S25) (?v1 S22) (?v2 S22) (?v3 S22) (?v4 S49)) (let ((?v_0 (f26 f27 ?v1))) (=> (= (f28 ?v0 ?v1) f1) (=> (= (f48 (f25 (f26 f27 ?v2) ?v3) (f72 ?v4 ?v1)) f1) (= (f73 (f74 (f25 ?v_0 ?v2) (f25 ?v_0 ?v3)) (f75 (f76 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S6) (?v1 S3) (?v2 S3) (?v3 S3) (?v4 S53)) (let ((?v_0 (f34 f35 ?v1))) (=> (= (f11 ?v0 ?v1) f1) (=> (= (f57 (f33 (f34 f35 ?v2) ?v3) (f77 ?v4 ?v1)) f1) (= (f42 (f13 (f14 f15 (f33 ?v_0 ?v2)) (f33 ?v_0 ?v3)) (f78 (f79 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S31) (?v1 Int) (?v2 S3) (?v3 S3) (?v4 S55)) (let ((?v_0 (f22 f23 ?v1))) (=> (= (f36 ?v0 ?v1) f1) (=> (= (f57 (f33 (f34 f35 ?v2) ?v3) (f80 ?v4 ?v1)) f1) (= (f45 (f17 (f18 f19 (f21 ?v_0 ?v2)) (f21 ?v_0 ?v3)) (f81 (f82 ?v0) ?v4)) f1))))))
(assert (forall ((?v0 S6)) (= (= (f83 ?v0) f1) (forall ((?v1 Int)) (= (f39 (f8 (f9 f10 ?v1) ?v1) ?v0) f1)))))
(assert (forall ((?v0 S7)) (= (= (f84 ?v0) f1) (forall ((?v1 S9)) (= (f42 (f13 (f14 f15 ?v1) ?v1) ?v0) f1)))))
(assert (forall ((?v0 S12)) (= (= (f85 ?v0) f1) (forall ((?v1 S14)) (= (f45 (f17 (f18 f19 ?v1) ?v1) ?v0) f1)))))
(assert (forall ((?v0 S20)) (= (= (f86 ?v0) f1) (forall ((?v1 S22)) (= (f48 (f25 (f26 f27 ?v1) ?v1) ?v0) f1)))))
(assert (forall ((?v0 S28)) (= (= (f87 ?v0) f1) (forall ((?v1 S3)) (= (f57 (f33 (f34 f35 ?v1) ?v1) ?v0) f1)))))
(assert (forall ((?v0 S6)) (= (= (f88 ?v0) f1) (forall ((?v1 Int)) (not (= (f39 (f8 (f9 f10 ?v1) ?v1) ?v0) f1))))))
(assert (forall ((?v0 S7)) (= (= (f89 ?v0) f1) (forall ((?v1 S9)) (not (= (f42 (f13 (f14 f15 ?v1) ?v1) ?v0) f1))))))
(assert (forall ((?v0 S12)) (= (= (f90 ?v0) f1) (forall ((?v1 S14)) (not (= (f45 (f17 (f18 f19 ?v1) ?v1) ?v0) f1))))))
(assert (forall ((?v0 S20)) (= (= (f91 ?v0) f1) (forall ((?v1 S22)) (not (= (f48 (f25 (f26 f27 ?v1) ?v1) ?v0) f1))))))
(assert (forall ((?v0 S28)) (= (= (f92 ?v0) f1) (forall ((?v1 S3)) (not (= (f57 (f33 (f34 f35 ?v1) ?v1) ?v0) f1))))))
(assert (forall ((?v0 S6)) (= (exists ((?v1 S3)) (= (f11 ?v0 ?v1) f1)) (exists ((?v1 Int) (?v2 Int)) (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S7)) (= (exists ((?v1 S8)) (= (f12 ?v0 ?v1) f1)) (exists ((?v1 S9) (?v2 S9)) (= (f12 ?v0 (f13 (f14 f15 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S12)) (= (exists ((?v1 S13)) (= (f16 ?v0 ?v1) f1)) (exists ((?v1 S14) (?v2 S14)) (= (f16 ?v0 (f17 (f18 f19 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S17)) (= (exists ((?v1 S14)) (= (f20 ?v0 ?v1) f1)) (exists ((?v1 Int) (?v2 S3)) (= (f20 ?v0 (f21 (f22 f23 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S20)) (= (exists ((?v1 S21)) (= (f24 ?v0 ?v1) f1)) (exists ((?v1 S22) (?v2 S22)) (= (f24 ?v0 (f25 (f26 f27 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S25)) (= (exists ((?v1 S22)) (= (f28 ?v0 ?v1) f1)) (exists ((?v1 S3) (?v2 Int)) (= (f28 ?v0 (f29 (f30 f31 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S28)) (= (exists ((?v1 S9)) (= (f32 ?v0 ?v1) f1)) (exists ((?v1 S3) (?v2 S3)) (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1)))))
(assert (forall ((?v0 S8)) (=> (forall ((?v1 S9) (?v2 S3) (?v3 Int) (?v4 Int)) (=> (= ?v0 (f13 (f14 f15 ?v1) (f33 (f34 f35 ?v2) (f8 (f9 f10 ?v3) ?v4)))) false)) false)))
(assert (forall ((?v0 S13)) (=> (forall ((?v1 S14) (?v2 Int) (?v3 Int) (?v4 Int)) (=> (= ?v0 (f17 (f18 f19 ?v1) (f21 (f22 f23 ?v2) (f8 (f9 f10 ?v3) ?v4)))) false)) false)))
(assert (forall ((?v0 S7) (?v1 S8)) (=> (forall ((?v2 S9) (?v3 S3) (?v4 Int) (?v5 Int)) (= (f12 ?v0 (f13 (f14 f15 ?v2) (f33 (f34 f35 ?v3) (f8 (f9 f10 ?v4) ?v5)))) f1)) (= (f12 ?v0 ?v1) f1))))
(assert (forall ((?v0 S12) (?v1 S13)) (=> (forall ((?v2 S14) (?v3 Int) (?v4 Int) (?v5 Int)) (= (f16 ?v0 (f17 (f18 f19 ?v2) (f21 (f22 f23 ?v3) (f8 (f9 f10 ?v4) ?v5)))) f1)) (= (f16 ?v0 ?v1) f1))))
(assert (forall ((?v0 S9)) (=> (forall ((?v1 S3) (?v2 Int) (?v3 Int)) (=> (= ?v0 (f33 (f34 f35 ?v1) (f8 (f9 f10 ?v2) ?v3))) false)) false)))
(assert (forall ((?v0 S13)) (=> (forall ((?v1 S14) (?v2 Int) (?v3 S3)) (=> (= ?v0 (f17 (f18 f19 ?v1) (f21 (f22 f23 ?v2) ?v3))) false)) false)))
(assert (forall ((?v0 S14)) (=> (forall ((?v1 Int) (?v2 Int) (?v3 Int)) (=> (= ?v0 (f21 (f22 f23 ?v1) (f8 (f9 f10 ?v2) ?v3))) false)) false)))
(assert (forall ((?v0 S21)) (=> (forall ((?v1 S22) (?v2 S3) (?v3 Int)) (=> (= ?v0 (f25 (f26 f27 ?v1) (f29 (f30 f31 ?v2) ?v3))) false)) false)))
(assert (forall ((?v0 S8)) (=> (forall ((?v1 S9) (?v2 S3) (?v3 S3)) (=> (= ?v0 (f13 (f14 f15 ?v1) (f33 (f34 f35 ?v2) ?v3))) false)) false)))
(assert (forall ((?v0 S28) (?v1 S9)) (=> (forall ((?v2 S3) (?v3 Int) (?v4 Int)) (= (f32 ?v0 (f33 (f34 f35 ?v2) (f8 (f9 f10 ?v3) ?v4))) f1)) (= (f32 ?v0 ?v1) f1))))
(assert (forall ((?v0 S12) (?v1 S13)) (=> (forall ((?v2 S14) (?v3 Int) (?v4 S3)) (= (f16 ?v0 (f17 (f18 f19 ?v2) (f21 (f22 f23 ?v3) ?v4))) f1)) (= (f16 ?v0 ?v1) f1))))
(assert (forall ((?v0 S17) (?v1 S14)) (=> (forall ((?v2 Int) (?v3 Int) (?v4 Int)) (= (f20 ?v0 (f21 (f22 f23 ?v2) (f8 (f9 f10 ?v3) ?v4))) f1)) (= (f20 ?v0 ?v1) f1))))
(assert (forall ((?v0 S20) (?v1 S21)) (=> (forall ((?v2 S22) (?v3 S3) (?v4 Int)) (= (f24 ?v0 (f25 (f26 f27 ?v2) (f29 (f30 f31 ?v3) ?v4))) f1)) (= (f24 ?v0 ?v1) f1))))
(assert (forall ((?v0 S7) (?v1 S8)) (=> (forall ((?v2 S9) (?v3 S3) (?v4 S3)) (= (f12 ?v0 (f13 (f14 f15 ?v2) (f33 (f34 f35 ?v3) ?v4))) f1)) (= (f12 ?v0 ?v1) f1))))
(assert (forall ((?v0 S3)) (=> (forall ((?v1 Int) (?v2 Int)) (=> (= ?v0 (f8 (f9 f10 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S8)) (=> (forall ((?v1 S9) (?v2 S9)) (=> (= ?v0 (f13 (f14 f15 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S13)) (=> (forall ((?v1 S14) (?v2 S14)) (=> (= ?v0 (f17 (f18 f19 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S14)) (=> (forall ((?v1 Int) (?v2 S3)) (=> (= ?v0 (f21 (f22 f23 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S21)) (=> (forall ((?v1 S22) (?v2 S22)) (=> (= ?v0 (f25 (f26 f27 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S22)) (=> (forall ((?v1 S3) (?v2 Int)) (=> (= ?v0 (f29 (f30 f31 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S9)) (=> (forall ((?v1 S3) (?v2 S3)) (=> (= ?v0 (f33 (f34 f35 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S3)) (=> (forall ((?v1 Int) (?v2 Int)) (=> (= ?v0 (f8 (f9 f10 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S8)) (=> (forall ((?v1 S9) (?v2 S9)) (=> (= ?v0 (f13 (f14 f15 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S13)) (=> (forall ((?v1 S14) (?v2 S14)) (=> (= ?v0 (f17 (f18 f19 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S14)) (=> (forall ((?v1 Int) (?v2 S3)) (=> (= ?v0 (f21 (f22 f23 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S21)) (=> (forall ((?v1 S22) (?v2 S22)) (=> (= ?v0 (f25 (f26 f27 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S22)) (=> (forall ((?v1 S3) (?v2 Int)) (=> (= ?v0 (f29 (f30 f31 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S9)) (=> (forall ((?v1 S3) (?v2 S3)) (=> (= ?v0 (f33 (f34 f35 ?v1) ?v2)) false)) false)))
(assert (forall ((?v0 S6) (?v1 Int) (?v2 Int)) (=> (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1) (= (f36 (f37 (f93 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S7) (?v1 S9) (?v2 S9)) (=> (= (f12 ?v0 (f13 (f14 f15 ?v1) ?v2)) f1) (= (f32 (f40 (f94 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S12) (?v1 S14) (?v2 S14)) (=> (= (f16 ?v0 (f17 (f18 f19 ?v1) ?v2)) f1) (= (f20 (f43 (f95 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S17) (?v1 Int) (?v2 S3)) (=> (= (f20 ?v0 (f21 (f22 f23 ?v1) ?v2)) f1) (= (f11 (f49 (f96 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S20) (?v1 S22) (?v2 S22)) (=> (= (f24 ?v0 (f25 (f26 f27 ?v1) ?v2)) f1) (= (f28 (f46 (f97 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S25) (?v1 S3) (?v2 Int)) (=> (= (f28 ?v0 (f29 (f30 f31 ?v1) ?v2)) f1) (= (f36 (f52 (f98 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S28) (?v1 S3) (?v2 S3)) (=> (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1) (= (f11 (f55 (f99 ?v0) ?v1) ?v2) f1))))
(assert (forall ((?v0 S9) (?v1 Int) (?v2 S9) (?v3 Int) (?v4 S7) (?v5 S6)) (= (= (f100 (f101 (f102 ?v0 ?v1) (f102 ?v2 ?v3)) (f103 ?v4 ?v5)) f1) (or (= (f42 (f13 (f14 f15 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f39 (f8 (f9 f10 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 S14) (?v1 Int) (?v2 S14) (?v3 Int) (?v4 S12) (?v5 S6)) (= (= (f104 (f105 (f106 ?v0 ?v1) (f106 ?v2 ?v3)) (f107 ?v4 ?v5)) f1) (or (= (f45 (f17 (f18 f19 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f39 (f8 (f9 f10 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 S22) (?v1 Int) (?v2 S22) (?v3 Int) (?v4 S20) (?v5 S6)) (= (= (f108 (f109 (f110 ?v0 ?v1) (f110 ?v2 ?v3)) (f111 ?v4 ?v5)) f1) (or (= (f48 (f25 (f26 f27 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f39 (f8 (f9 f10 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 S3) (?v1 Int) (?v2 S3) (?v3 Int) (?v4 S28) (?v5 S6)) (= (= (f48 (f25 (f26 f27 (f29 (f30 f31 ?v0) ?v1)) (f29 (f30 f31 ?v2) ?v3)) (f112 (f113 ?v4) ?v5)) f1) (or (= (f57 (f33 (f34 f35 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f39 (f8 (f9 f10 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 Int) (?v1 S9) (?v2 Int) (?v3 S9) (?v4 S6) (?v5 S7)) (= (= (f114 (f115 (f116 ?v0 ?v1) (f116 ?v2 ?v3)) (f117 ?v4 ?v5)) f1) (or (= (f39 (f8 (f9 f10 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f42 (f13 (f14 f15 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 Int) (?v1 S14) (?v2 Int) (?v3 S14) (?v4 S6) (?v5 S12)) (= (= (f118 (f119 (f120 ?v0 ?v1) (f120 ?v2 ?v3)) (f121 ?v4 ?v5)) f1) (or (= (f39 (f8 (f9 f10 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f45 (f17 (f18 f19 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 Int) (?v1 S22) (?v2 Int) (?v3 S22) (?v4 S6) (?v5 S20)) (= (= (f122 (f123 (f124 ?v0 ?v1) (f124 ?v2 ?v3)) (f125 ?v4 ?v5)) f1) (or (= (f39 (f8 (f9 f10 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f48 (f25 (f26 f27 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 Int) (?v1 S3) (?v2 Int) (?v3 S3) (?v4 S6) (?v5 S28)) (= (= (f45 (f17 (f18 f19 (f21 (f22 f23 ?v0) ?v1)) (f21 (f22 f23 ?v2) ?v3)) (f126 (f127 ?v4) ?v5)) f1) (or (= (f39 (f8 (f9 f10 ?v0) ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f57 (f33 (f34 f35 ?v1) ?v3) ?v5) f1))))))
(assert (forall ((?v0 Int) (?v1 Int) (?v2 Int) (?v3 Int) (?v4 S6) (?v5 S6)) (let ((?v_0 (f9 f10 ?v0))) (= (= (f57 (f33 (f34 f35 (f8 ?v_0 ?v1)) (f8 (f9 f10 ?v2) ?v3)) (f128 (f129 ?v4) ?v5)) f1) (or (= (f39 (f8 ?v_0 ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f39 (f8 (f9 f10 ?v1) ?v3) ?v5) f1)))))))
(assert (forall ((?v0 S9) (?v1 S9) (?v2 S9) (?v3 S9) (?v4 S7) (?v5 S7)) (let ((?v_0 (f14 f15 ?v0))) (= (= (f63 (f64 (f13 ?v_0 ?v1) (f13 (f14 f15 ?v2) ?v3)) (f130 (f131 ?v4) ?v5)) f1) (or (= (f42 (f13 ?v_0 ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f42 (f13 (f14 f15 ?v1) ?v3) ?v5) f1)))))))
(assert (forall ((?v0 S14) (?v1 S14) (?v2 S14) (?v3 S14) (?v4 S12) (?v5 S12)) (let ((?v_0 (f18 f19 ?v0))) (= (= (f68 (f69 (f17 ?v_0 ?v1) (f17 (f18 f19 ?v2) ?v3)) (f132 (f133 ?v4) ?v5)) f1) (or (= (f45 (f17 ?v_0 ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f45 (f17 (f18 f19 ?v1) ?v3) ?v5) f1)))))))
(assert (forall ((?v0 S22) (?v1 S22) (?v2 S22) (?v3 S22) (?v4 S20) (?v5 S20)) (let ((?v_0 (f26 f27 ?v0))) (= (= (f73 (f74 (f25 ?v_0 ?v1) (f25 (f26 f27 ?v2) ?v3)) (f134 (f135 ?v4) ?v5)) f1) (or (= (f48 (f25 ?v_0 ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f48 (f25 (f26 f27 ?v1) ?v3) ?v5) f1)))))))
(assert (forall ((?v0 S3) (?v1 S3) (?v2 S3) (?v3 S3) (?v4 S28) (?v5 S28)) (let ((?v_0 (f34 f35 ?v0))) (= (= (f42 (f13 (f14 f15 (f33 ?v_0 ?v1)) (f33 (f34 f35 ?v2) ?v3)) (f136 (f137 ?v4) ?v5)) f1) (or (= (f57 (f33 ?v_0 ?v2) ?v4) f1) (and (= ?v0 ?v2) (= (f57 (f33 (f34 f35 ?v1) ?v3) ?v5) f1)))))))
(assert (forall ((?v0 S6) (?v1 Int) (?v2 Int)) (= (= (f36 (f37 (f93 ?v0) ?v1) ?v2) f1) (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S28) (?v1 S3) (?v2 S3)) (= (= (f11 (f55 (f99 ?v0) ?v1) ?v2) f1) (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S6) (?v1 Int) (?v2 Int)) (=> (= (f36 (f37 (f93 ?v0) ?v1) ?v2) f1) (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S7) (?v1 S9) (?v2 S9)) (=> (= (f32 (f40 (f94 ?v0) ?v1) ?v2) f1) (= (f12 ?v0 (f13 (f14 f15 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S12) (?v1 S14) (?v2 S14)) (=> (= (f20 (f43 (f95 ?v0) ?v1) ?v2) f1) (= (f16 ?v0 (f17 (f18 f19 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S17) (?v1 Int) (?v2 S3)) (=> (= (f11 (f49 (f96 ?v0) ?v1) ?v2) f1) (= (f20 ?v0 (f21 (f22 f23 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S20) (?v1 S22) (?v2 S22)) (=> (= (f28 (f46 (f97 ?v0) ?v1) ?v2) f1) (= (f24 ?v0 (f25 (f26 f27 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S25) (?v1 S3) (?v2 Int)) (=> (= (f36 (f52 (f98 ?v0) ?v1) ?v2) f1) (= (f28 ?v0 (f29 (f30 f31 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S28) (?v1 S3) (?v2 S3)) (=> (= (f11 (f55 (f99 ?v0) ?v1) ?v2) f1) (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1))))
(assert (forall ((?v0 S6) (?v1 Int) (?v2 Int)) (=> (= (f36 (f37 (f93 ?v0) ?v1) ?v2) f1) (=> (=> (= (f11 ?v0 (f8 (f9 f10 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S7) (?v1 S9) (?v2 S9)) (=> (= (f32 (f40 (f94 ?v0) ?v1) ?v2) f1) (=> (=> (= (f12 ?v0 (f13 (f14 f15 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S12) (?v1 S14) (?v2 S14)) (=> (= (f20 (f43 (f95 ?v0) ?v1) ?v2) f1) (=> (=> (= (f16 ?v0 (f17 (f18 f19 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S17) (?v1 Int) (?v2 S3)) (=> (= (f11 (f49 (f96 ?v0) ?v1) ?v2) f1) (=> (=> (= (f20 ?v0 (f21 (f22 f23 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S20) (?v1 S22) (?v2 S22)) (=> (= (f28 (f46 (f97 ?v0) ?v1) ?v2) f1) (=> (=> (= (f24 ?v0 (f25 (f26 f27 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S25) (?v1 S3) (?v2 Int)) (=> (= (f36 (f52 (f98 ?v0) ?v1) ?v2) f1) (=> (=> (= (f28 ?v0 (f29 (f30 f31 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 S28) (?v1 S3) (?v2 S3)) (=> (= (f11 (f55 (f99 ?v0) ?v1) ?v2) f1) (=> (=> (= (f32 ?v0 (f33 (f34 f35 ?v1) ?v2)) f1) false) false))))
(assert (forall ((?v0 Int) (?v1 Int) (?v2 S82)) (= (= (f39 (f8 (f9 f10 ?v0) ?v1) (f138 ?v2)) f1) (< (f139 f140 (f141 ?v2 ?v0)) (f139 f140 (f141 ?v2 ?v1))))))
(assert (forall ((?v0 S9) (?v1 S9) (?v2 S85)) (= (= (f42 (f13 (f14 f15 ?v0) ?v1) (f142 ?v2)) f1) (< (f139 f140 (f143 ?v2 ?v0)) (f139 f140 (f143 ?v2 ?v1))))))
(assert (forall ((?v0 S14) (?v1 S14) (?v2 S86)) (= (= (f45 (f17 (f18 f19 ?v0) ?v1) (f144 ?v2)) f1) (< (f139 f140 (f145 ?v2 ?v0)) (f139 f140 (f145 ?v2 ?v1))))))
(assert (forall ((?v0 S22) (?v1 S22) (?v2 S87)) (= (= (f48 (f25 (f26 f27 ?v0) ?v1) (f146 ?v2)) f1) (< (f139 f140 (f147 ?v2 ?v0)) (f139 f140 (f147 ?v2 ?v1))))))
(assert (forall ((?v0 S3) (?v1 S3) (?v2 S88)) (= (= (f57 (f33 (f34 f35 ?v0) ?v1) (f148 ?v2)) f1) (< (f139 f140 (f149 ?v2 ?v0)) (f139 f140 (f149 ?v2 ?v1))))))
(assert (forall ((?v0 S82) (?v1 Int) (?v2 Int) (?v3 S6)) (=> (< (f139 f140 (f141 ?v0 ?v1)) (f139 f140 (f141 ?v0 ?v2))) (= (f39 (f8 (f9 f10 ?v1) ?v2) (f150 (f151 ?v0) ?v3)) f1))))
(assert (forall ((?v0 S85) (?v1 S9) (?v2 S9) (?v3 S7)) (=> (< (f139 f140 (f143 ?v0 ?v1)) (f139 f140 (f143 ?v0 ?v2))) (= (f42 (f13 (f14 f15 ?v1) ?v2) (f152 (f153 ?v0) ?v3)) f1))))
(assert (forall ((?v0 S86) (?v1 S14) (?v2 S14) (?v3 S12)) (=> (< (f139 f140 (f145 ?v0 ?v1)) (f139 f140 (f145 ?v0 ?v2))) (= (f45 (f17 (f18 f19 ?v1) ?v2) (f154 (f155 ?v0) ?v3)) f1))))
(assert (forall ((?v0 S87) (?v1 S22) (?v2 S22) (?v3 S20)) (=> (< (f139 f140 (f147 ?v0 ?v1)) (f139 f140 (f147 ?v0 ?v2))) (= (f48 (f25 (f26 f27 ?v1) ?v2) (f156 (f157 ?v0) ?v3)) f1))))
(assert (forall ((?v0 S88) (?v1 S3) (?v2 S3) (?v3 S28)) (=> (< (f139 f140 (f149 ?v0 ?v1)) (f139 f140 (f149 ?v0 ?v2))) (= (f57 (f33 (f34 f35 ?v1) ?v2) (f158 (f159 ?v0) ?v3)) f1))))
(assert (forall ((?v0 S82) (?v1 Int) (?v2 Int) (?v3 S6)) (let ((?v_0 (f8 (f9 f10 ?v1) ?v2))) (=> (<= (f139 f140 (f141 ?v0 ?v1)) (f139 f140 (f141 ?v0 ?v2))) (=> (= (f39 ?v_0 ?v3) f1) (= (f39 ?v_0 (f150 (f151 ?v0) ?v3)) f1))))))
(assert (forall ((?v0 S85) (?v1 S9) (?v2 S9) (?v3 S7)) (let ((?v_0 (f13 (f14 f15 ?v1) ?v2))) (=> (<= (f139 f140 (f143 ?v0 ?v1)) (f139 f140 (f143 ?v0 ?v2))) (=> (= (f42 ?v_0 ?v3) f1) (= (f42 ?v_0 (f152 (f153 ?v0) ?v3)) f1))))))
(assert (forall ((?v0 S86) (?v1 S14) (?v2 S14) (?v3 S12)) (let ((?v_0 (f17 (f18 f19 ?v1) ?v2))) (=> (<= (f139 f140 (f145 ?v0 ?v1)) (f139 f140 (f145 ?v0 ?v2))) (=> (= (f45 ?v_0 ?v3) f1) (= (f45 ?v_0 (f154 (f155 ?v0) ?v3)) f1))))))
(assert (forall ((?v0 S87) (?v1 S22) (?v2 S22) (?v3 S20)) (let ((?v_0 (f25 (f26 f27 ?v1) ?v2))) (=> (<= (f139 f140 (f147 ?v0 ?v1)) (f139 f140 (f147 ?v0 ?v2))) (=> (= (f48 ?v_0 ?v3) f1) (= (f48 ?v_0 (f156 (f157 ?v0) ?v3)) f1))))))
(assert (forall ((?v0 S88) (?v1 S3) (?v2 S3) (?v3 S28)) (let ((?v_0 (f33 (f34 f35 ?v1) ?v2))) (=> (<= (f139 f140 (f149 ?v0 ?v1)) (f139 f140 (f149 ?v0 ?v2))) (=> (= (f57 ?v_0 ?v3) f1) (= (f57 ?v_0 (f158 (f159 ?v0) ?v3)) f1))))))
(assert (forall ((?v0 S31) (?v1 S6)) (= (= (f160 ?v0 ?v1) f1) (forall ((?v2 Int)) (=> (= (f161 ?v2 ?v0) f1) (forall ((?v3 Int)) (=> (= (f161 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f39 (f8 (f9 f10 ?v2) ?v3) ?v1) f1) (= (f39 (f8 (f9 f10 ?v3) ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S17) (?v1 S12)) (= (= (f162 ?v0 ?v1) f1) (forall ((?v2 S14)) (=> (= (f51 ?v2 ?v0) f1) (forall ((?v3 S14)) (=> (= (f51 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f45 (f17 (f18 f19 ?v2) ?v3) ?v1) f1) (= (f45 (f17 (f18 f19 ?v3) ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S25) (?v1 S20)) (= (= (f163 ?v0 ?v1) f1) (forall ((?v2 S22)) (=> (= (f54 ?v2 ?v0) f1) (forall ((?v3 S22)) (=> (= (f54 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f48 (f25 (f26 f27 ?v2) ?v3) ?v1) f1) (= (f48 (f25 (f26 f27 ?v3) ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S7) (?v1 S43)) (= (= (f164 ?v0 ?v1) f1) (forall ((?v2 S8)) (=> (= (f42 ?v2 ?v0) f1) (forall ((?v3 S8)) (=> (= (f42 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f63 (f64 ?v2 ?v3) ?v1) f1) (= (f63 (f64 ?v3 ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S12) (?v1 S47)) (= (= (f165 ?v0 ?v1) f1) (forall ((?v2 S13)) (=> (= (f45 ?v2 ?v0) f1) (forall ((?v3 S13)) (=> (= (f45 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f68 (f69 ?v2 ?v3) ?v1) f1) (= (f68 (f69 ?v3 ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S20) (?v1 S51)) (= (= (f166 ?v0 ?v1) f1) (forall ((?v2 S21)) (=> (= (f48 ?v2 ?v0) f1) (forall ((?v3 S21)) (=> (= (f48 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f73 (f74 ?v2 ?v3) ?v1) f1) (= (f73 (f74 ?v3 ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S28) (?v1 S7)) (= (= (f167 ?v0 ?v1) f1) (forall ((?v2 S9)) (=> (= (f57 ?v2 ?v0) f1) (forall ((?v3 S9)) (=> (= (f57 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f42 (f13 (f14 f15 ?v2) ?v3) ?v1) f1) (= (f42 (f13 (f14 f15 ?v3) ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S6) (?v1 S28)) (= (= (f168 ?v0 ?v1) f1) (forall ((?v2 S3)) (=> (= (f39 ?v2 ?v0) f1) (forall ((?v3 S3)) (=> (= (f39 ?v3 ?v0) f1) (=> (not (= ?v2 ?v3)) (or (= (f57 (f33 (f34 f35 ?v2) ?v3) ?v1) f1) (= (f57 (f33 (f34 f35 ?v3) ?v2) ?v1) f1))))))))))
(assert (forall ((?v0 S84)) (= (f141 f169 (f139 f140 ?v0)) ?v0)))
(assert (forall ((?v0 Int)) (=> (<= 0 ?v0) (= (f139 f140 (f141 f169 ?v0)) ?v0))))
(assert (forall ((?v0 Int)) (=> (< ?v0 0) (= (f139 f140 (f141 f169 ?v0)) 0))))
(check-sat)
(exit)
