.name "Peanutbutter"
.comment "Don't mix"

	ld %72399550, r2
	st r2, :first

first:
	xor %3133016936, r1, r1
	zjmp %3000

load:
    ld %33554431, r2
    ld %4278976576, r3
    ld %42991616, r4
    ld %269025351, r6
    ld %64, r7
    ld %64, r8
    ld %384, r9

store:
    sti r2, %44, r7
    sti r3, %42, r7
    sti r4, %40, r7
    sti r5, %38, r7
    sti r6, %34, r7
    sti r1, %15, r7
    add r7, r8, r7
    fork %:store

jump:
    ld %0, r16
    zjmp %54

fork:
#    live %-1
 #   fork %64
#    ld %0, r16
 #   zjmp %:fork
