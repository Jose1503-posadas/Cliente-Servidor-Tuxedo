#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <userlog.h>
#include <fml32.h>
#include <atmi.h>  
#include "bib_T3.fml.h"

//Definicion de las funciones 
int cliCalcAreaTriaEqu(float val1, float val2, float val3, float val4, float val5, float val6,float *resultado);
int cliCalcDistDosPtos(float val1, float val2, float val3, float val4, float val5, float val6,float *resultado);
int cliCalcProdCruz(float val1, float val2, float val3, float val4, float val5, float val6, float *resultado);

//Tipo de dato para calcular el area del triangulo 
typedef int (*opera) (float val1, float val2, float val3, float val4, float val5, float val6,  float *resultado);

opera selecOperacion(int ivA_oper);


int main(int argc, char **argv){
   int Opc_oper;
   float val1;
   float val2;
   float val3;
   float val4;
   float val5;
   float val6;
   float resultado;
   opera obtOpera;

   if(argc!=8){
    printf("Modo de uso: 	            clienteT3 OPERACION Oper1 Oper2 Oper3 Oper4 Oper5 Oper6\n");
    printf("Ejemplos:\n");
    printf("Para Area triangulo equilatero: clienteT3     1     base altura   0     0     0     0  \n");
    printf("Para Distancia dos puntos3D:    clienteT3     2      x1    y1    z1    x2     y2    z2 \n");
    printf("Para Distancia dos puntos2D:    clienteT3     3      Ax    Ay    Bx    By     0      0 \n");    
    return -1;
   }
   
   Opc_oper = atoi(argv[1]);
   val1 = (float) atof(argv[2]);
   val2 = (float) atof(argv[3]);
   val3 = (float) atof(argv[4]);
   val4 = (float) atof(argv[5]);
   val5 = (float) atof(argv[6]);
   val6 = (float) atof(argv[7]);
 
   obtOpera = selecOperacion(Opc_oper);
   obtOpera(val1, val2, val3, val4, val5, val6, &resultado);
 
   printf("Resultado: %f \n", resultado);

   return 0;
}

opera selecOperacion(int ivA_oper){
    opera obtOpera;
    switch (ivA_oper){
	    case 1:
		obtOpera = cliCalcAreaTriaEqu;
		break;
	    case 2:
		obtOpera = cliCalcDistDosPtos;
		break;
	    case 3:
		obtOpera = cliCalcProdCruz;
		break;
	    default:
		break;
    }

    return obtOpera;
}

int cliCalcAreaTriaEqu(float val1, float val2, float val3, float val4, float val5, float val6,  float *resultado){
  int ivL_resLlamd;
  long lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, BASE, (char *)&val1, 0) < 0){
     printf ("Error insertando campo FML (BASE)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, ALTURA, (char *)&val2, 0) < 0){
     printf ("Error insertando campo FML (ALTURA)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  /* Invocamos servicio de calculo de area de un triangulo equilatero*/
  printf("Llamada al servicio 'servCalcAreaTriaEqu'\n");
  if(tpcall("servCalcAreaTriaEqu", (char *)fbfr, 0, (char **)&fbfr, (long*)&lvL_tamLongt, 0L) == -1) {
    printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
    printf("Liberamos el buffer y desconectamos de la aplicacion\n");
    tpfree((char *)fbfr);
    tpterm(); 
    return (0); 
}
  /* Lectura de resultados */
  if(Fget32(fbfr, AREA, 0, (char *)&fvL_recValor, 0) < 0){
  	userlog("No se leyo el resultado\n");
  	tpreturn (TPFAIL, 0, (char*)fbfr, 0L,0) ;
  }
  *resultado = fvL_recValor;
  printf("Liberamos buffer y desconectamos de la aplicación\n");
  tpfree((char *)fbfr);
  tpterm();
  return 0;
}

int cliCalcDistDosPtos(float val1, float val2, float val3, float val4, float val5, float val6,  float *resultado){
  int ivL_resLlamd;
  long lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, X1, (char *)&val1, 0) < 0){
     printf ("Error insertando campo FML (X1)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, Y1, (char *)&val2, 0) < 0){
     printf ("Error insertando campo FML (Y1)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, Z1, (char *)&val3, 0) < 0){
     printf ("Error insertando campo FML (Z1)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, X2, (char *)&val4, 0) < 0){
     printf ("Error insertando campo FML (X2)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, Y2, (char *)&val5, 0) < 0){
     printf ("Error insertando campo FML (Y2)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, Z2, (char *)&val6, 0) < 0){
     printf ("Error insertando campo FML (Z2)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  /* Invocamos el servicio para calcular el punto cruz */
  printf("Llamada al servicio 'servCalcDistDosPtos'\n");
  if (tpcall("servCalcDistDosPtos", (char *)fbfr, 0, (char **)&fbfr, (long*) &lvL_tamLongt, 0L) == -1) {
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      printf("Liberamos buffer y desconectamos de la aplicacion\n");
      tpfree((char *)fbfr);
      tpterm();
      return (0);
  }
  /* Lectura de resultados */
  if(Fget32(fbfr, DISTAN, 0, (char *)&fvL_recValor, 0) < 0) {
  userlog("No se leyo el resultado\n");
  tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
  }

  *resultado = fvL_recValor;

  printf("Liberamos buffer y desconectamos de la aplicación\n");
  tpfree((char*)fbfr);
  tpterm();
  return 0;  
}

int cliCalcProdCruz(float val1, float val2, float val3, float val4, float val5, float val6,  float *resultado) {
  int ivL_resLlamd;
  long lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, AX, (char *)&val1, 0) < 0){
     printf ("Error insertando campo FML (AX)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, AY, (char *)&val2, 0) < 0){
     printf ("Error insertando campo FML (AY)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, BX, (char *)&val3, 0) < 0){
     printf ("Error insertando campo FML (BX)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, BY, (char *)&val4, 0) < 0){
     printf ("Error insertando campo FML (BY)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }

  /* Invocamos el servicio de calculo de producto punto */
  printf("Llamada al servicio 'servCalcProdCruz'\n");
  if (tpcall("servCalcProdCruz", (char *)fbfr, 0, (char **)&fbfr, (long*) &lvL_tamLongt, 0L) == -1) {
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      printf("Liberamos buffer y desconectamos de la aplicacion\n");
      tpfree((char *)fbfr);
      tpterm();
      return (0);
  }
  /* Lectura de resultados */
  if(Fget32(fbfr, PCRUZ, 0, (char *)&fvL_recValor, 0) < 0) {
  userlog("No se leyo el resultado\n");
  tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
  }
  
  *resultado = fvL_recValor; 
  printf ("Liberamos Buffer y desconectamos de la aplicación\n");
  tpfree((char*)fbfr);
  tpterm();
  return 0;  
}
