.name "zorkeater"
.comment "I eat zork"

	ld %72399550, r2
	st r2, :first

four:
    ld %4, r3

base:
    ld %200, r4
    
first:
	xor %3133016936, r1, r1
	zjmp %300

loop:
    live %-1
    ld %1107727392, r6
    sti r6, :base, %:four
    add r4, r3, r4
    ld %0, r16
    zjmp %:loop

repeat:
    live %-1
    add r3, r4, r5
    zjmp %:repeat
