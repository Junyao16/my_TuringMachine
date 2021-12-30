; This program is to caculate the gcd of two positive integers.
; Input: a string of 1^m 0 1^n, in which m and n represent the two positive integers.
; Output: a string of 1^n, in which n represents the gcd of two input numbers.

; First, copy the first integer to tape 1 and the second integer to tape 2
; We change to state c0, when we meet a '1'.
; When copying, we stay in state c0 until we meet a '0'.
; We change to state c1, when we meet a '0'.
; We change to state c2, when we meet a '1' after '0' and stay in state c2 until meet '_'.
; We change to c3 when we meet a '_' then we begin to process the two integers.

; Then we begin to caculate the gcd.
; We look through the two integers and cross out the same number of  '1's of the smaller integer in the larger integer.
; We repeatedly do this until the number of '1's on the two tapes are the same.
; Copy the '1's on the tape 1 to tape 0 and the turing machine halts.

; How to cross out?
; First, we move head 1 and head 2 to the beginning of notnull symbols on the tapes.
; Then we compare the number of '1's of the two tape.
; Go back to the beginning of the two tapes and cross out the '1's of the tape with more '1's.
; Then go to the beginning of the two tapes and start comparasion again.




; halt_reject,halt_finished: caculation finished


#Q = {0,halt_reject,halt_finished,c0,c1,c2,c3,reject,look_for_beginning,beginning,finished,back1,back2,look_for_beginning1}

#S = {0,1}

#G = {0,1,_}

#q0 = 0

#B = _

#F = {halt_reject,halt_finished}

#N = 3

; 0: start state
0 0__ ___ r** reject
0 1__ _1_ rr* c0
0 ___ ___ *** reject

; c0: meet a '1'
c0 0__ ___ r** c1
c0 1__ _1_ rr* c0
c0 ___ ___ *** reject

; c1: finished copying the first integer
c1 0__ ___ r** reject
c1 1__ __1 r*r c2
c1 ___ ___ *** reject

; c2: meet a '1' after '0'
c2 0__ ___ r** reject
c2 1__ __1 r*r c2
c2 ___ ___ *** c3

; c3: finished copying the second integer
c3 0__ ___ r** reject
c3 1__ ___ r** reject
c3 ___ ___ lll look_for_beginning


; reject: illegal input
reject 0__ ___ r** reject
reject 1__ ___ r** reject
reject ___ ___ *** halt_reject

; look_for_beginning: looking for the first notnull symbol of tape 1 and 2
look_for_beginning _11 _11 *ll look_for_beginning
look_for_beginning _1_ _1_ *l* look_for_beginning
look_for_beginning __1 __1 **l look_for_beginning
look_for_beginning ___ ___ *rr beginning

; beginning: at the beginning of tape1 and tape2
beginning _11 _11 *rr beginning
beginning _1_ _1_ *ll back1
beginning __1 __1 *ll back2
beginning ___ ___ *ll finished

; back1: tape1 is longer, cross out
back1 _11 __1 *ll back1
back1 ___ ___ *rr look_for_beginning1

; back2: tape2 is longer, corss out 
back2 _11 _1_ *ll back2
back2 ___ ___ *rr look_for_beginning1

; look_for_beginning1
look_for_beginning1 _1_ _1_ **r look_for_beginning1
look_for_beginning1 __1 __1 *r* look_for_beginning1
look_for_beginning1 _11 _11 *** beginning

; finished: finished caculation, need to copy the answer to tape1
finished _11 1__ rll finished
finished ___ ___ *** halt_finished








