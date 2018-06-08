#include <mips/regdef.h>

#Argumentos de la funcion
#define VALIDATE_ARG3  			44
#define VALIDATE_ARG2  			40
#define VALIDATE_ARG1  			36
#define VALIDATE_ARG0			32

#tamanio Stack
#define VALIDATE_TS				32

#SRA
#define VALIDATE_RA  			24
#define VALIDATE_FP				20
#define VALIDATE_GP				16

#LTA
#define VALIDATE_J				8
#define VALIDATE_CONT_MATRIZ 	4
#define VALIDATE_I 				0

	.text
	.align	2
	.globl	transponer
	.ent	transponer
transponer:
	.frame  	$fp ,VALIDATE_TS , ra
	.set 		noreorder
	.cpload t9
	.set		reorder
	subu		sp , sp ,VALIDATE_TS
	.cprestore 	VALIDATE_GP
	sw			ra ,VALIDATE_RA(sp)
	sw			$fp ,VALIDATE_FP(sp)
	sw			gp ,VALIDATE_GP(sp)

	sw			a0	,VALIDATE_ARG0(sp)
	sw			a1	,VALIDATE_ARG1(sp)
	sw			a2	,VALIDATE_ARG2(sp)
	sw			a3	,VALIDATE_ARG3(sp)

	move		$fp , sp

	sw 			zero,VALIDATE_I($fp)
	sw 			zero,VALIDATE_CONT_MATRIZ($fp)
	sw			zero,VALIDATE_J($fp)
forPrincipal:
	lw 			t0,VALIDATE_I($fp)
	lw			t1,VALIDATE_ARG1($fp)
	bge			t0,t1,transponerMipsFin

	sw			zero,VALIDATE_J($fp)

forSecundario:
	lw			t0,VALIDATE_J($fp)
	lw			t1,VALIDATE_ARG0($fp)
	bge			t0,t1,salirDeForPrincipal

	lw	 		t0,VALIDATE_ARG1($fp)
	lw			t1,VALIDATE_J($fp)
	sll			t1,t1,3
	mul			t1,t1,t0
	lw			t0,VALIDATE_I($fp)
	sll			t0,t0,3
	addu		t1,t0,t1
	lw			t0,VALIDATE_ARG2($fp)
	addu		t1,t1,t0
	lw			t3,0(t1)
	lw			t4,4(t1)

	lw			t0,VALIDATE_CONT_MATRIZ($fp)
	sll			t0,t0,3
	lw			t1,VALIDATE_ARG3($fp)
	addu		t0,t1,t0

	sw			t3,0(t0)
	sw			t4,4(t0)
	lw			t0,VALIDATE_CONT_MATRIZ($fp)
	addu		t0,t0,1
	sw			t0,VALIDATE_CONT_MATRIZ($fp)

	lw			t0,VALIDATE_J($fp)
	addu		t0,t0,1
	sw			t0,VALIDATE_J($fp)
	b			forSecundario

salirDeForPrincipal:
	lw			t0,VALIDATE_I($fp)
	addu		t0,t0,1
	sw			t0,VALIDATE_I($fp)
	b			forPrincipal

transponerMipsFin:
	li			v0,1
	lw			ra ,VALIDATE_RA($fp)
	lw			gp ,VALIDATE_GP($fp)
	lw			$fp ,VALIDATE_FP($fp)
	addu		sp,sp,VALIDATE_TS
	j 			ra
.end transponer
