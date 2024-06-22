#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

void get_control_param(void){ 
  long time_dumy;

  /* set up the system control parameters */
  ctl.max_time_step = 100000;   /* max time step */
  ctl.mat_size = 400;         /* system size = n X n squared lattice */
  ctl.concentration = 1.0;  /* initial concentration probability */
  ctl.theta = 9;
  ctl.kappa = 6;
  
  ctl.shift = ctl.mat_size+8;

  /* set a "seed" for random number generator */
  sys.random_seed = (long *)calloc(1, sizeof(long)); 
  *sys.random_seed=-time(&time_dumy); /* set seed for random numbers */

}
