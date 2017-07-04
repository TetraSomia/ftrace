/*
** branching_exec.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed Apr 19 15:21:56 2017 Arthur Josso
** Last update Tue Jul  4 11:12:00 2017 Arthur Josso
*/

#include <stdio.h>
#include <sys/ptrace.h>
#include "core.h"
#include "elf_reader.h"
#include "func_stack.h"
#include "graph.h"

static const t_param_order param_order[] =
  {
    {14, "rdi"},
    {13, "rsi"},
    {12, "rdx"},
    {7, "r10"},
    {9, "r8"},
    {8, "r9"}
  };

void		exec_syscall(const t_regs *regs, const t_regs *old_regs,
			     bool void_return)
{
  uint8_t	nb_param;
  uint8_t	param;
  uint16_t	n_syscall;
  t_reg		return_value;

  return_value = regs->name.rax;
  n_syscall = old_regs->name.rax;
  nb_param = g_sc64[n_syscall].nb_param;
  print_data("Syscall %s(", g_sc64[n_syscall].name);
  param = 0;
  while (param < nb_param)
    {
      print_data("0x%lx", old_regs->list[param_order[param].id]);
      if (param < nb_param - 1)
        print_data(", ");
      param++;
    }
  if (void_return)
    print_data(") = ?\n");
  else
    print_data(") = 0x%lx\n", return_value);
  graph_add_node(NODE_SYSCALL, g_sc64[n_syscall].name);
}

void		exec_call(const t_regs *regs, const t_regs *old_regs)
{
  t_address    	addr;
  const char	*name;
  bool		isDyn;

  (void)old_regs;
  isDyn = true;
  addr = regs->name.rip;
  name = get_sym_name(addr);
  if (name == NULL)
      name = get_dynsym_name(addr);
  else
    isDyn = false;
  if (name != NULL)
    print_data("Entering function %s at 0x%lx\n", name, addr);
  else
    print_data("Entering func_0x%lX@a.out\n", addr);
  graph_add_node(isDyn ? NODE_DYN_FUNC : NODE_FUNC, name);
  stack_push_func(addr, old_regs->name.rip, name);
}

void		exec_ret(const t_regs *regs, const t_regs *old_regs)
{
  t_address	addr;
  const char	*name;

  (void)regs;
  (void)old_regs;
  addr = stack_pop_func();
  if (addr == 0)
    return;
  name = get_sym_name(addr);
  if (name == NULL)
    name = get_dynsym_name(addr);
  if (name != NULL)
    print_data("Leaving function %s\n", name);
  else
    print_data("Leaving func_0x%lX@a.out\n", addr);
}
