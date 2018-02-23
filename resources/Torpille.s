.name "Torpille"
.comment "by sebc"

	xor	r4,r4,r4
debut:
	fork	%:debut2
	st	r1, 6
ld1:	live	%0
	fork	%:debut2
	# process qui dit live pour T1
	st	r1, 20
	ld	%-10, r2
	ld	%1, r3
live1:	live	%4
	add	r2, r3, r2
	zjmp	%:live1b
	xor	r4, r4, r4
	zjmp	%:live1
live1b:	fork	%:debut2
	ld	%-10, r2
	xor	r4, r4, r4
	zjmp	%:live1

debut2:
	st	r1, 6
ld2:	live	%0
	fork	%:debut
	# process qui dit live pour T2
	st	r1, 20
	ld	%-10, r2
	ld	%1, r3

live2:	live	%4
	add	r2, r3, r2
	zjmp	%:live2b
	xor	r4, r4, r4
	zjmp	%:live2

live2b:	fork	%:debut
	ld	%-10, r2
	xor	r4, r4, r4
	zjmp	%:live2

