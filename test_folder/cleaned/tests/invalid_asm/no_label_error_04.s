.name "Death"
.comment "Fork"
	
	st	r1, :l3
	st	r1, :l4 # Error ocure because he can't find the label after the string below
l3:	live	%1
"test"
l4:	zjmp	%:l1
