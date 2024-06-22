#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/****
 set the initial configuration of the system
****/
void set_init_conf()
{
  int i, j;
  int shift =  ctl.shift;
  double pp    = ctl.concentration;
  double kappa = ctl.kappa;

  for (i = 4; i < ctl.mat_size+4; i++){
    for (j = 4; j < ctl.mat_size+4; j++){
      sys.mat0[shift*i+j] = (int)(ran1()+pp)* (int)(ran1()*kappa+1);
    }  
  }

}

void open_files(void)
{
  if((fpout = fopen("../files/out","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
}

void init_mem(void){
  int *mat_mem0, *mat_mem1, *mat_mem2;
  int n;
  
  n = ctl.mat_size+8;

  mat_mem0 = (int *)calloc(n*n, sizeof(int)); 
  mat_mem1 = (int *)calloc(n*n, sizeof(int)); 
  mat_mem2 = (int *)calloc(n*n, sizeof(int)); 
  sys.mat0 = mat_mem0;
  sys.mat1 = mat_mem1;
  sys.mat2 = mat_mem2;
}

void show_matrix(int *field){
  int i, j;

  for(i=0; i<ctl.mat_size+8; i++){
    for(j=0; j<ctl.mat_size+8; j++){
      printf(" %2d",field[(ctl.mat_size+8)*i+j]);
    }
    printf("\n");
  }
  printf("\n");


  //  for(i=2; i<ctl.mat_size+2; i++){
  //     for(j=2; j<ctl.mat_size+2; j++){
  //      printf(" %2d",field[(ctl.mat_size+4)*i+j]);
  //    }
  //    printf("\n");
  //  }
  printf("\n");

}

void print_matrix(int *field){
  int i, j;

  for(i=0; i<ctl.mat_size+8; i++){
    for(j=0; j<ctl.mat_size+8; j++){
      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
    }
    fprintf(fpout,"\n");
  }
  fprintf(fpout,"\n");


  //  for(i=2; i<ctl.mat_size+2; i++){
  //    for(j=2; j<ctl.mat_size+2; j++){
  //      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
  //    }
  //    fprintf(fpout,"\n");
  //  }
  fprintf(fpout,"\n");

}

