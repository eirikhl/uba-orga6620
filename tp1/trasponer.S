#include <mips/regdef.h>

	.text
	.align	2
	.globl	trasponer
	.ent	trasponer
trasponer:

	.frame  	$fp ,48 , ra
	.set 		noreorder
	.cpload t9
	.set		reorder
	subu		sp , sp ,40
	.cprestore 	16
	sw			$fp ,32(sp)
	sw			ra ,36(sp)
	sw			gp ,40(sp)

	sw			a0 ,0(sp)
	sw			a1 ,4(sp)
	sw			a2 ,8(sp)
	sw			a3 ,12(sp)

	move		$fp , sp

	sw 			zero,16($fp)		#t0 int i=0
	sw 			zero,20($fp)		#int contadorMatrixSalida = 0;
	sw			zero,24($fp)
	#for(i = 0;i < columnas;i++){
forPrincipal:
	lw 			t0,16($fp)
	bge			t0,a1,trasponerMipsFin

	sw			zero,24($fp)		#int j = 0;

	#for(j = 0; j< filas; j++)
forSecundario:
	lw			t0,24($fp)
	bge			t0,a0,salirDeForPrincipal

	#salida[contadorMatrixSalida] = entrada[j*columnas+i];
	move 		t0,a1
	lw			t1,24($fp)
	sll			t1,t1,3
	mul			t1,t1,t0			#j*columnas
	lw			t0,16($fp)
	sll			t0,t0,3
	addu		t1,t0,t1			#j*columnas+i
	addu		t1,t1,a2
	lw			t3,(t1)				#entrada[j*columnas+i]
	lw			t4,4(t1)			#entrada[j*columnas+i]

	lw			t0,20($fp)
	sll			t0,t0,3				#contadorMatrixSalida
	addu		t0,a3,t0

	sw			t3,(t0)
	sw			t4,4(t0)			#salida[contadorMatrixSalida]
	lw			t0,20($fp)
	addu		t0,t0,1				#contadorMatrixSalida++;
	sw			t0,20($fp)

	lw			t0,24($fp)
	addu		t0,t0,1
	sw			t0,24($fp)
	b			forSecundario

salirDeForPrincipal:
	lw			t0,16($fp)
	addu		t0,t0,1
	sw			t0,16($fp)
	b			forPrincipal

trasponerMipsFin:
	li			v0,1
	lw			ra ,36($fp)
	lw			$fp ,32($fp)
	lw			gp ,40($fp)
	addu		sp,sp,48
	j 			ra
	.end	trasponer
