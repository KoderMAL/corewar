.name	"Hop"
.comment	"hiphop"

head: 	
		st r1, 6
		live %234		
		st r1, 6
		live %234
		st r1, 6
		live %234

rm:		ld %0, r16
		zjmp %:code

lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
lfork %0
	
		ld	%511, r2
		ld	%510, r3
		ld	%509, r4
		ld	%507, r6
		ld	%506, r5
		ld	%505, r7
		ld	%504, r8
		ld	56, r15 #zhop2 -1
		ld	:asthop, r10
		ld	26, r11 #sthop2 -1
		ld  25, r12 #zhop -2
		ld	:azhop, r13 #
		ld	%0, r16

asthop:	sti r10, r2, r16
asthop2:	sti r11, r3, r16
azhop:	sti r12, r4, r16
		sti r13, r5, r16
		sti r15, r7, r16
azhop2:	zjmp %450
	
		ld	%511, r2
		ld	%510, r3
		ld	%509, r4
		ld	%507, r6
		ld	%506, r5
		ld	%505, r7
		ld	%504, r8
		ld	56, r15 #zhop2 -1
		ld	:asthop, r10
		ld	26, r11 #sthop2 -1
		ld  25, r12 #zhop -2
		ld	:azhop, r13 #
		ld	%0, r16

asthop:	sti r10, r2, r16
asthop2:	sti r11, r3, r16
azhop:	sti r12, r4, r16
		sti r13, r5, r16
		sti r15, r7, r16
azhop2:	zjmp %470
	live %234
		live %234
		live %234
		live %234
		live %234
		live %234
		live %234
		live %234

code:	
		st r16, :rm
		st r1, 6
ll:		live %954
		st r9, :code
		ld	%511, r2
		ld	%510, r3
		ld	%509, r4
		ld	%507, r6
		ld	%506, r5
		ld	%505, r7
		ld	%504, r8
		ld	56, r15 #zhop2 -1
		ld	:sthop, r10
		ld	26, r11 #sthop2 -1
		ld  25, r12 #zhop -2
		ld	:zhop, r13 #
		ld	%0, r16

sthop:	sti r10, r2, r16
sthop2:	sti r11, r3, r16
zhop:	sti r12, r4, r16
		sti r13, r5, r16
		sti r15, r7, r16
zhop2:	zjmp %470
