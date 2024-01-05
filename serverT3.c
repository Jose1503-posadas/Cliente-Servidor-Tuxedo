#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <userlog.h>
#include <fml32.h>
#include <atmi.h>  
#include <math.h>
#include "bib_T3.fml.h"

tpsvrinit(int argc, char *argv[]) {
    userlog ("Iniciando serverT3");
    return 0;
}

/* servicio para obtener datos de calcular área del triangulo equilatero */
void servCalcAreaTriaEqu(TPSVCINFO * rqst) {
    float base;
    float altura;
    float area;
    FBFR32* fbfr = (FBFR32*)rqst->data;
   
    userlog("Servicio servCalcAreaTriaEqu invocado.");
   
    /* Obtener campos FML del buffer de entrada */
    /*Base*/
    if (Fget32(fbfr, BASE, 0, (char *)&base, 0) < 0) {
        userlog("No se leyó el radio");
        tpreturn(TPFAIL, 0, (char *) fbfr, 0L, 0);
    }
    /*altura*/  
    if (Fget32(fbfr, ALTURA, 0, (char *)&altura, 0) < 0) {
        userlog("No se leyó el radio");
        tpreturn(TPFAIL, 0, (char *) fbfr, 0L, 0);
    }
    userlog("Base: [%f]", base);
    userlog("Altura: [%f]", altura);

    /* Calculo del area triangulo equilatero Area=(b*h)/2 */
    area = (base * altura)/2;

    /* Insertar el área en el buffer FML */
    Fadd32(fbfr, AREA, (char *)&area, 0);
    userlog("El area del triangulo equilatero es: [%f]", area);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}

/* Servicio para calcular la distancia entre dos puntos de 3D*/
void servCalcDistDosPtos(TPSVCINFO * rqst) {
   float x1;
   float y1;
   float z1;
   float x2;
   float y2;
   float z2;
   float distancia;
   FBFR32 * fbfr = (FBFR32*)rqst->data;

   userlog ("Servicio servCalcDistDosPtos invocado.");

   /* Obtener campos FML del buffer de entrada */
   /*Punto 1*/
   if (Fget32(fbfr, X1, 0, (char *)&x1, 0) < 0) {
      userlog("No se leyo la constante A");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   if (Fget32(fbfr, Y1, 0, (char *)&y1, 0) < 0) {
      userlog("No se leyo la constante B");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   if (Fget32(fbfr, Z1, 0, (char *)&z1, 0) < 0) {
      userlog("No se leyo la constante C");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   /*Punto 2*/
   if (Fget32(fbfr, X2, 0, (char *)&x2, 0) < 0) {
      userlog("No se leyo la constante A");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   if (Fget32(fbfr, Y2, 0, (char *)&y2, 0) < 0) {
      userlog("No se leyo la constante B");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   if (Fget32(fbfr, Z2, 0, (char *)&z2, 0) < 0) {
      userlog("No se leyo la constante C");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   userlog("X1: [%f]", x1);
   userlog("Y1: [%f]", y1);
   userlog("Z1: [%f]", z1);
   userlog("x2: [%f]", x2);
   userlog("Y2: [%f]", y2);
   userlog("z2: [%f]", z2);

   /* Calcular la distancia entre 2 puntos*/
    distancia = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
    //distancia = 10;
    /* Insertar las raices calculadas en el buffer  FML*/
    Fadd32(fbfr, DISTAN, (char *)&distancia, 0);
    userlog("La distancia entre los dos puntoses: [%f]\n", distancia);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);

}


/* Servicio Calcular producto cruz*/
void servCalcProdCruz(TPSVCINFO *rqst) {
   float ax;
   float ay;
   float bx;
   float by;
   float pCruz;
   FBFR32 *fbfr = (FBFR32 *)rqst->data;

   userlog ("Servicio servCalcProdPunto invocado.");
  
   /* Obtener los campos FML del buffer de entrada */
   if (Fget32(fbfr, AX, 0, (char *)&ax, 0) < 0) {
      userlog("No se leyo ax");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, AY, 0, (char *)&ay, 0) < 0) {
      userlog("No se leyo ay"); 
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, BX, 0, (char *)&bx, 0) < 0) {
      userlog("No se leyo bx");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, BY, 0, (char *)&by, 0) < 0) {
      userlog("No se leyo by");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   userlog("AX: [%f]", ax);
   userlog("AY: [%f]", ay);
   userlog("BX: [%f]", bx);
   userlog("BY: [%f]", by);

   /* Realizar producto punto */
   pCruz = (ax * by) - (ay * bx);

   // Agregar el resultado del producto punto al buffer FML
   Fadd32(fbfr, PCRUZ, (char *)&pCruz, 0);
   userlog("Resultado del producto cruz: [%f]", pCruz);

   tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}
