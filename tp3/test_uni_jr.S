addi $t1, $zero, 12
addi $t2, $t1, 0
beq $t1, $t2, label
jr $t2
label: nop
jalr $t1, $t2
j end
nop
nop
nop
end:

