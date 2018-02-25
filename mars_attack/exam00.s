.name "Exam00"
.comment "La Purge"

fork %:code
ld %0, r2

topbarrier:
live: live %11111
st r2, -50
st r2, -59
st r2, -68
st r2, -77
st r2, -86
st r2, -95
st r2, -104
st r2, -113
st r2, -122
st r2, -131
st r2, -140
st r2, -149
st r2, -158
st r2, -167
st r2, -176
st r2, -185
st r2, -194
st r2, -203
st r2, -212
st r2, -221
st r2, -230
st r2, -239
st r2, -248
st r2, -257
st r2, -266
st r2, -275
st r2, -284
st r2, -293
zjmp %:topbarrier

code: st r1, -147

