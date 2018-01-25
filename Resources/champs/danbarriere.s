.name "Barriere"
.comment "Envoie des torpilles a l'avant et se protege avec des barrieres a l'avant et a l'arriere"

# On bombarde derriere notre programme

arriere_live:
		sti	r4, %:arriere, r3
#add	r3, r5, r3
		and	r6, %0, r6
		zjmp	%:arriere_live
		
arriere:	ld	%-5, r5
		ld	%1024,r4

