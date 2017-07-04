/*
** signal.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Sat Apr 22 16:01:36 2017 Arthur Josso
** Last update Sun Apr 23 14:08:53 2017 Arthur Josso
*/

#include <signal.h>
#include <sys/wait.h>
#include "core.h"

static const t_sig_data sig_tab[] =
  {
    NEW_SIGNAL_NAME(SIGWINCH),
    NEW_SIGNAL_NAME(SIGABRT),
    NEW_SIGNAL_NAME(SIGALRM),
    NEW_SIGNAL_NAME(SIGBUS),
    NEW_SIGNAL_NAME(SIGCHLD),
    NEW_SIGNAL_NAME(SIGCONT),
    NEW_SIGNAL_NAME(SIGFPE),
    NEW_SIGNAL_NAME(SIGHUP),
    NEW_SIGNAL_NAME(SIGILL),
    NEW_SIGNAL_NAME(SIGINT),
    NEW_SIGNAL_NAME(SIGKILL),
    NEW_SIGNAL_NAME(SIGPIPE),
    NEW_SIGNAL_NAME(SIGQUIT),
    NEW_SIGNAL_NAME(SIGSEGV),
    NEW_SIGNAL_NAME(SIGSTOP),
    NEW_SIGNAL_NAME(SIGTERM),
    NEW_SIGNAL_NAME(SIGTSTP),
    NEW_SIGNAL_NAME(SIGTTIN),
    NEW_SIGNAL_NAME(SIGTTOU),
    NEW_SIGNAL_NAME(SIGUSR1),
    NEW_SIGNAL_NAME(SIGUSR2),
    NEW_SIGNAL_NAME(SIGPOLL),
    NEW_SIGNAL_NAME(SIGPROF),
    NEW_SIGNAL_NAME(SIGSYS),
    NEW_SIGNAL_NAME(SIGURG),
    NEW_SIGNAL_NAME(SIGVTALRM),
    NEW_SIGNAL_NAME(SIGXCPU),
    NEW_SIGNAL_NAME(SIGXFSZ),
    NEW_SIGNAL_NAME(END_OF_SIG_LIST),
  };

int	check_for_sig(int status)
{
  int	i;

  if (WIFSTOPPED(status))
    {
      i = 0;
      while (sig_tab[i].sig != END_OF_SIG_LIST)
	{
	  if (WSTOPSIG(status) == sig_tab[i].sig)
	    {
	      print_data("Received signal %s\n", sig_tab[i].name);
	      return (WSTOPSIG(status));
	    }
	  i++;
	}
    }
  return (0);
}
