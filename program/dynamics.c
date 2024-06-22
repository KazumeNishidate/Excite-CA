#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

void excite()
{
  int i, j, ii, jj, x, cnt, nn;
  int shift = ctl.shift;
  int theta = ctl.theta, kappa = ctl.kappa;
  
  for (i = 4; i < ctl.mat_size+4; i++){
    for (j = 4; j < ctl.mat_size+4; j++){
      
      x = sys.mat0[i*shift+j];

      if(x>0) {
	x += 1;
	x = x % kappa;
      } else {  // x == 0
	cnt = 0;
	for(ii=-4;ii<5;ii++){
	  for(jj=-4;jj<5;jj++){
	    if(ii==-4 && jj==-4) continue;  // nw and nw corners
	    if(ii==-4 && jj==-3) continue;
	    if(ii==-4 && jj== 4) continue;
	    if(ii==-4 && jj== 3) continue;	  
	    if(ii==-3 && jj==-4) continue;
	    if(ii==-3 && jj== 4) continue;
	    
	    if(ii== 4 && jj==-4) continue;  // sw and se corners
	    if(ii== 4 && jj==-3) continue;
	    if(ii== 4 && jj== 4) continue;
	    if(ii== 4 && jj== 3) continue;
	    if(ii== 3 && jj==-4) continue;
	    if(ii== 3 && jj==-4) continue;
	    if(ii== 0 && jj== 0) continue;
	    nn = sys.mat0[(i+ii)*shift+(j+jj)];
	    if(nn==1 ) {
	      cnt++;
	    }
	    if(cnt >= theta){
	      x = 1;
	      break;
	    }	    
	  }
	  if(cnt >= theta){
	    break;
	  }
	}
      }
      sys.mat1[i*shift+j] = x;
    }
  }

  
}

void set_bc(int *cell)
{
  int i, j;
  int shift = ctl.shift;
  int size  = ctl.mat_size;
  
  // corner adjustment 1
  for(i=0;i<4;i++){
    // corner adjust 1    
    cell[         i ] = cell[ shift*(size+1) - (8-i) ]; 
    cell[   shift+i ] = cell[ shift*(size+2) - (8-i) ];
    cell[ shift*2+i ] = cell[ shift*(size+3) - (8-i) ];
    cell[ shift*3+i ] = cell[ shift*(size+4) - (8-i) ];    
    
    // corner adjust 2    
    cell[         size+(4+i) ] = cell[    shift*size +(4+i) ]; 
    cell[   shift+size+(4+i) ] = cell[ shift*(size+1)+(4+i) ];
    cell[ shift*2+size+(4+i) ] = cell[ shift*(size+2)+(4+i) ];
    cell[ shift*3+size+(4+i) ] = cell[ shift*(size+3)+(4+i) ];

    // corner adjust 3
    cell[ (size+4)*(shift+1)+i   ] = cell[ shift*4+(4+i) ];
    cell[ (size+5)*(shift+1)+i-1 ] = cell[ shift*5+(4+i) ];
    cell[ (size+6)*(shift+1)+i-2 ] = cell[ shift*6+(4+i) ];
    cell[ (size+7)*(shift+1)+i-3 ] = cell[ shift*7+(4+i) ];        

    // corner adjust 4
    cell[ (size+4)*(shift)+i   ] = cell[ shift*4+size+i ];
    cell[ (size+5)*(shift)+i   ] = cell[ shift*5+size+i ];
    cell[ (size+6)*(shift)+i   ] = cell[ shift*6+size+i ];
    cell[ (size+7)*(shift)+i   ] = cell[ shift*7+size+i ];        
  }
  // border adjustment 1
  for(i=0;i<size;i++){
    cell[            4+i  ] = cell[ shift*size     + (4+i) ];
    cell[ shift   + (4+i) ] = cell[ shift*(size+1) + (4+i) ];
    cell[ shift*2 + (4+i) ] = cell[ shift*(size+2) + (4+i) ];
    cell[ shift*3 + (4+i) ] = cell[ shift*(size+3) + (4+i) ];
  }
  // border adjustment 2  
  for(i=0;i<4;i++){
    for(j=0;j<size;j++){
      cell[ shift*(4+j)+i ] = cell[ shift*(4+j) +size + i ];
      cell[ shift*(4+j)+size+4+i ] = cell[ shift*(4+j) + (4+i) ];
    }    
  }
  // border adjustment 3    
  for(i=0;i<size;i++){  
    cell[ (size+4)*(shift)+4+i ]    = cell[ shift*4+(4+i) ];
    cell[ (size+4)*(shift+1)+8+i ]  = cell[ shift*5+(4+i) ];
    cell[ (size+4)*(shift+2)+12+i ] = cell[ shift*6+(4+i) ];
    cell[ (size+4)*(shift+3)+16+i ] = cell[ shift*7+(4+i) ];    
  }
  
}

void mk_copy(int *original, int *copy)
{
  int i, j;

  for(i=0; i<ctl.mat_size+8; i++){
    for(j=0; j<ctl.mat_size+8; j++){
      *(copy+ctl.shift*i+j)  = *(original+ctl.shift*i+j);
    }
  }
}

