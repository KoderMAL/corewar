.name "try"
.comment"try"

live:
live %4
live %-1
ld %0, r16
zjmp %10
xor r1, r2, r3
zjmp %100
ld %0, r2
or r1, r2, r3
zjmp %10

