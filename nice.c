#include "types.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
   if(argc == 3){
      nice(atoi(argv[1]), argv[2]);
   }
   exit();
}