#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "rand.h"

int 
sys_nice(void)
{
  int new_nice;
  char *program;
  argint(0, &new_nice);
  argptr(1, &program, sizeof program);
  return nice(new_nice, program);
}

int
sys_renice(void)
{
  int pid, new_nice;
  argint(0, &new_nice);
  argint(1, &pid);
  return renice(new_nice, pid);
}

int
random(void)
{
  srand(uptime());
  return rand();
}

int 
sys_random(void)
{
  return random();
}

int
sys_fork(void)
{
  return fork();
}

#ifdef GETPPID
int
sys_getppid(void)
{
    int ppid = 1;

    if (myproc()->parent) {
        ppid = myproc()->parent->pid;
    }
    return ppid;
}
#endif

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
getpid(void)
{
  return myproc()->pid;
}

int
sys_getpid(void)
{
  return getpid();
  // return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_kdebug(void)
{
    extern uint debugState;

    int tof = FALSE;

    if (argint(0, &tof) < 0)
        return -1;
    debugState = tof;
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_uptime(void)
{
  // uint xticks;

  // acquire(&tickslock);
  // xticks = ticks;
  // release(&tickslock);
  // return xticks;
  return uptime();
}