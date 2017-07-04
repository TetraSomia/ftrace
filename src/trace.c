/*
** trace.c for lol in /home/tetra/rendu/psu/PSU_2016_strace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Apr  3 17:45:58 2017 Arthur Josso
** Last update Tue Jul  4 11:12:36 2017 Arthur Josso
*/

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "core.h"

pid_t pid;

static void	catch_sig(int signum)
{
  (void)signum;
}

void		trace_proc()
{
  t_regs	regs;
  t_regs	old_regs;
  int		status;
  int		send_sig;

  signal(SIGINT, catch_sig);
  send_sig = 0;
  bzero(&old_regs, sizeof(t_regs));
  while (true)
    {
      if (ptrace(PTRACE_SINGLESTEP, pid, NULL, send_sig) == -1)
	fat_err("ptrace");
      wait(&status);
      if (WIFEXITED(status) || WIFSIGNALED(status))
        break;
      send_sig = check_for_sig(status);
      if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
	fat_err("ptrace");
      find_branch(&regs, &old_regs);
      old_regs = regs;
    }
  if (WIFEXITED(status))
    exec_syscall(&regs, &old_regs, true);
}

void    fork_routine(char **args)
{
  int   status;

  if ((pid = fork()) < 0)
    fat_err("fork");
  if (pid == 0)
    {
      if (ptrace(PTRACE_TRACEME) == -1)
        fat_err("ptrace");
      ptrace(PTRACE_SETOPTIONS, 0, 0, PTRACE_O_TRACEEXIT);
      kill(getpid(), SIGSTOP);
      if (execv(args[0], args) == -1)
        fat_err("execvp");
      exit(1);
    }
  wait(&status);
}
