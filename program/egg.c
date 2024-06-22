#include <eggx.h>
#include <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#define MYCOLOR IDL1_GRN_RED_BLU_WHT
#include "rw.h"
#include "prototypes.h"

#define X_MAX 800
#define Y_MAX 800

void egg_disp(void){
  static int cnt=0, win;
  int i, j, x;
  int c_r, c_g, c_b;
  int kappa = ctl.kappa;
  
  if(cnt==0){
    win=gopen(X_MAX,Y_MAX);
    layer(win,0,1);
  }
  gclr(win) ;
  
  for (i = 4; i < ctl.mat_size+4; i++){
    for (j = 4; j < ctl.mat_size+4; j++){
      x = sys.mat0[ctl.shift*i+j];
      if(x>0){
	makecolor(MYCOLOR,(double)kappa, 0.0, x, &c_r,&c_g,&c_b);
	newrgbcolor(win,c_r,c_g,c_b);    
	fillrect(win, i*2, j*2, 2, 2);
      }
    }
  }
  copylayer(win,1,0);
  cnt++;  
}
