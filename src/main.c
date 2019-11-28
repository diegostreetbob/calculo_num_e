/*//////////////////////////////////////////////////////////////////////////////
 *Cáculo del número e tanto en secuencial como en paralelo con openmp
//////////////////////////////////////////////////////////////////////////////*/
//Diego Martínez Guillén-dmartinez17@alu.ucam.edu
////////////////////////////////////////////////////////////////////////////////
////////////////////////////INCLUDES////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
/////////////////////////////MACROS/////////////////////////////////////////////
#define TERMINOS 10000
#define N_HILOS 12
/////////////////CABECERAS DE MÉTODOS Y FUNCIONES///////////////////////////////
double factorial(int n);//función recursiva
//////////////////////////////MAIN//////////////////////////////////////////////
int main()
{
  double e_sec=0.0f;
  double e_par=0.0f;
  double t_ini,t_fin;
  //MODO SECUENCIAL
  t_ini=omp_get_wtime();
  for(int i=0;i<TERMINOS;i++){
    e_sec+=(1/(factorial(i)));
  }
  t_fin=omp_get_wtime();
  printf("e en secuencial es %.11f y ha tardado %fs\n",e_sec,(t_fin-t_ini));
  //MODO PARALELO
  omp_set_num_threads(N_HILOS);
  t_ini=omp_get_wtime();
  #pragma omp parallel for reduction(+:e_par)
  for(int i=0;i<TERMINOS;i++){
    e_par+=(1/(factorial(i)));
  }
  t_fin=omp_get_wtime();
  printf("e en paralelo   es %.11f y ha tardado %fs",e_par,(t_fin-t_ini));
}
////////////////////////////////////////////////////////////////////////////////
double factorial(int n)
{
  double out;
  if((n==0)||(n==1)) return 1;
  out=factorial(n-1)*n;
  return out;
}
/*//////////////////////////////////////////////////////////////////////////////
 *e en secuencial es 2.71828182846 y ha tardado 0.226925s
 *e en paralelo   es 2.71828182846 y ha tardado 0.044947s
 *Mismo resultado que en calculadora, pero ojo hay que trabajar con docuble
//////////////////////////////////////////////////////////////////////////////*/