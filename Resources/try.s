.name    "try"
.comment "I'm trying ASM"

live:
live %4
zjmp %:live

# avec live %1
#01 00 00 00 01 09 ff fb
# avec live %4
#01 00 00 00 04 09 ff fb
# sans le zjmp
#01 00 00 00 04
# avec 2 zjmp d'affilee
#01 00 00 00 04 09 ff fb 09 ff f8
