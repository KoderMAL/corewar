.name    "try"
.comment "I'm trying ASM"

live:
live %4
add r16, r4, r3
zjmp %:live
# avec live %1 et le zjmp
#01 00 00 00 01 (09 ff fb)
# avec live %4 et le zjmp
#01 00 00 00 04 (09 ff fb)
# sans le zjmp
#(01 00 00 00 04)
# avec le add r3,r4,r3 qui est sense modifier le carry
#01 00 00 00 04 
#04 54 03 04 03
#09 ff f6
# avec add r2, r4, r3
#01 00 00 00 04
#04 54 02 04 03
#09 ff f6)
# avec fork
