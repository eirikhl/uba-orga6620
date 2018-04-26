#/bin/bash

# Empty file test
printf "\n"
printf "Archivo de testeo\n\n"

printf "test solo C"
printf "\ntest 1: le  faltan filas a la matriz, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/meFaltanFilas 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meFaltanFilas $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 1"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 2: tiene muchas mas filas de las que se procesan, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/meSobranFilas 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meSobranFilas $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 2"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 3: le falta una columna en la fila 3, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/meFaltaUnaColumnaEnLaFila3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meFaltaUnaColumnaEnLaFila3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 3"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 4: exceso de columna en la fila 3, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/excesoDeColumnaEnLaFila3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/excesoDeColumnaEnLaFila3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 4"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 5: trasponer una matriz simple\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/matrizSimple > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 5"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 6: muchos espacios entre elementos de la matriz, ignoralos\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/conMuchosEspacios > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 6"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 7: se le ingresa un un caracter no valido como elemnto, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matricesDePrueba/conUnElementoInvalido 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/conUnElementoInvalido $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 7"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 8: guardar la matriz en un archivo\n"

salidaDelPrograma="archivoAuxi1"
./tp1 -o $salidaDelPrograma - matricesDePrueba/matrizSimple
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 8"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 9: matrix1 dada por el curso\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matrices/matrix1 > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix1 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 9"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 10: matrix2 dada por el curso, faltan una columna en la fila 3\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matrices/matrix2 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix2 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 10"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 11: matrix3 dada por el curso, elemento no valido\n"

salidaDelPrograma="archivoAuxi1"
./tp1 - matrices/matrix3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 11"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 12: matrix4 \n"

salidaDelPrograma="archivoAuxi1"
./tp1 -o $salidaDelPrograma - matricesDePrueba/matrix4
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix4 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 12"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "============================================================\n\n"
printf "test de C + MIPS\n\n"

printf "\ntest 1: le  faltan filas a la matriz, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/meFaltanFilas 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meFaltanFilas $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 1"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 2: tiene muchas mas filas de las que se procesan, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/meSobranFilas 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meSobranFilas $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 2"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 3: le falta una columna en la fila 3, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/meFaltaUnaColumnaEnLaFila3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/meFaltaUnaColumnaEnLaFila3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 3"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 4: exceso de columna en la fila 3, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/excesoDeColumnaEnLaFila3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/excesoDeColumnaEnLaFila3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 4"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 5: trasponer una matriz simple\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/matrizSimple > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 5"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 6: muchos espacios entre elementos de la matriz, ignoralos\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/conMuchosEspacios > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 6"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 7: se le ingresa un un caracter no valido como elemnto, informar error\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matricesDePrueba/conUnElementoInvalido 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/conUnElementoInvalido $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 7"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 8: guardar la matriz en un archivo\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS -o $salidaDelPrograma - matricesDePrueba/matrizSimple
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrizSimple $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 8"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo


printf "\ntest 9: matrix1 dada por el curso\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matrices/matrix1 > $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix1 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 9"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 10: matrix2 dada por el curso, faltan una columna en la fila 3\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matrices/matrix2 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix2 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 10"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 11: matrix3 dada por el curso, elemento no valido\n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS - matrices/matrix3 2> $salidaDelPrograma
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix3 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 11"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo

printf "\ntest 12: matrix4 \n"

salidaDelPrograma="archivoAuxi1"
./tp1-MIPS -o $salidaDelPrograma - matricesDePrueba/matrix4
auxiSalidaArchivo="archivoAuxi2"
diff test-salidas-correctas/matrix4 $salidaDelPrograma > $auxiSalidaArchivo

if [ -s $auxiSalidaArchivo ]; then
	echo "Error en el Test 12"
elif [ -f $ENTRADA ]; then
	echo "test exitoso"
fi
rm $salidaDelPrograma
rm $auxiSalidaArchivo
