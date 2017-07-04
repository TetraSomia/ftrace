/*
** branching.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed Apr 19 14:59:56 2017 Arthur Josso
** Last update Tue Jul  4 11:14:49 2017 Arthur Josso
*/

#include "core.h"

static const t_branch_data branching_data[] =
  {
    {SYSCALL, test_syscall, (t_exec_func)exec_syscall},
    {CALL, test_call, exec_call},
    {RET, test_ret, exec_ret},
    {NONE, NULL, NULL}
  };

void	find_branch(const t_regs *regs, const t_regs *old_regs)
{
  t_branch_type	type;

  type = FIRST_TYPE;
  while (type != NONE)
    {
      if ((branching_data[type].test_func)(regs, old_regs))
	{
	  (branching_data[type].exec_func)(regs, old_regs);
	  return;
	}
      type++;
    }
}
