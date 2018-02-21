.name "Splish-Splosh"
.comment "Dan's first try at making a champion."
		
# FORK block which zjmps on live and fork
		ld %0, r7 #to make first zjmp work
		ld %15, r4
		fork %:block2
		st r1, 12
		st r1, 45 #modify + to get to the :live1
start:	fork %:heart
		zjmp %:start
heart: 	live %42
		ld %0, r7 #to make the second zjmp work with the pc from start/fork
		zjmp %:heart
# end for FORK block

block2:  ld %9999, r2

loop:	add r3,r4,r3
		sti r2,r3,%11
live1:	live %42
		ld %0, r7
		zjmp %:loop

