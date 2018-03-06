.name "Splish-Splosh"
.comment "Dan's first try at making a champion."
		
# FORK block which zjmps on live and fork
		ld %509, r9 #to make first zjmp work
		ld %508, r8
		fork %:block2
		live %999999
		st r1, 29 #  :heartlive #modify to the heart live
		st r1, 9 # :startlive  #modify + to get to the :start live
start:	fork %:heartlive
startlive:		live %42
		ld %0, r7
		zjmp %:start
heartlive: 	live %42
		ld %0, r7 #to make the second zjmp work with the pc from start/fork
		zjmp %:heartlive
# end for FORK block

block2:
				st r1, 16 #:boilerplate #live of boilerplate
				ld :boilerplate, r1
				ld 9, r2 #boilerplate 2 minus 1
boilerplate:	live %-89999999999999999999
boilerplate2:	zjmp %-5
				sti r1, r9, r10
				sti r2, r8, r10
				ld %0, r7
				zjmp %497
