	addi $t1, $zero, 18
	subi $t1, $t1, 2
	j label
	addi $t2, $zero, 16
	beq $t1, $t2, other
	label:
	jr $t1
	other:
	subi $t1, $t1, 16
	subi $t2, $t2, 16
