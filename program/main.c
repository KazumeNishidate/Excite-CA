#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "rw.h"
#include "prototypes.h"

/* based on the RWCA-2d uder cyclic boundary condition */
int main(void){

  open_files();
  get_control_param();
  init_mem();

  set_init_conf();
  set_bc(sys.mat0);
  mk_copy(sys.mat0, sys.mat1);  /* sys.mat0  => sys.mat1 */  
  for(sys.time_step=0;sys.time_step<ctl.max_time_step;sys.time_step++){
    egg_disp();
    excite();
    set_bc(sys.mat1);
    mk_copy(sys.mat1, sys.mat0);  /* sys.mat1  => sys.mat0 */
    //    usleep(1000);
  }
  /*-------- end of RWCA moving step -------*/
  return 0;
}

