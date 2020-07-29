.name "CASIMIR"
.comment "GLOUBIBOULGA"

	ld %880, r2
	ld %16778753, r3
	ld %4, r4
	ld %72618000, r5
	ld %269090801, r6
	st r1, 6
	live %456
	fork %:live
	add r16, r16, r16
	zjmp %:forknikator
live:
live2:
forknikator:
protect1:
	st r1, 6
	live %789
	st r2, -129
	st r3, -130
	st r4, -131
	st r5, -132
	st r6, r5
	st r16, r4
	st r16, r3
	st r16, r2
protect2:
	st r1, 6
	live %212
	st r2, -219
	st r3, -220
	st r4, -221
	st r5, -222
	st r6, -223
	st r16, -224
	st r16, -225
	st r16, -226
	add r16, r16, r16
	zjmp %:protect2
