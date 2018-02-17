.name "Splish-Splosh"
.comment "Dan's first try at making a champion."

		lld %0, r7
	#	ld %1, r6
	#	lld 10, r7
		zjmp %-120
		st r1, 12
start:	fork %:heart
	#	zjmp %:start
heart: 	live %42
		ld %0, r7
	#	zjmp %:start
