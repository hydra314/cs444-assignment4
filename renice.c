#include "types.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
   if(argc == 3){
      int val = renice(atoi(argv[1]), atoi(argv[2]));
      if(val == 0)
         printf(2, "Changed nice value of process with pid %d to %d\n", atoi(argv[2]), atoi(argv[1]));
      else if(val == 1)
         printf(2, "Nice value out of bounds\n");
      else if(val == 2)
         printf(2, "Invalid process ID\n");
   }
   exit();
}