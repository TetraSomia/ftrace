/*
** branching_test.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Apr 20 19:27:43 2017 Arthur Josso
** Last update Fri Apr 21 14:16:38 2017 Arthur Josso
*/

#include <sys/ptrace.h>
#include "core.h"
#include "func_stack.h"

static bool	is_next_inst(t_reg rip, t_reg tested_reg)
{
  if (tested_reg >= rip + MIN_BYTE_CALL_INST &&
      tested_reg <= rip + MAX_BYTE_CALL_INST)
    return (true);
  return (false);
}

bool	test_syscall(const t_regs *regs, const t_regs *old_regs)
{
  t_reg	rip_content;

  (void)regs;
  rip_content = ptrace(PTRACE_PEEKTEXT, pid, old_regs->name.rip, NULL);
  if ((rip_content & 0xFFFF) == SYSCALL_OPCODE)
    return (true);
  return (false);
}

bool	test_call(const t_regs *regs, const t_regs *old_regs)
{
  t_reg	rsp_content;

  rsp_content = ptrace(PTRACE_PEEKTEXT, pid, regs->name.rsp, NULL);
  if (is_next_inst(old_regs->name.rip, rsp_content) &&
      regs->name.rip < DYN_FUNC_MAPPING)
    return (true);
  return (false);
}

bool	test_ret(const t_regs *regs, const t_regs *old_regs)
{
  t_reg	call_rip;

  (void)old_regs;
  call_rip = stack_get_rip();
  if (call_rip == 0)
    return (false);
  if (is_next_inst(call_rip, regs->name.rip))
    return (true);
  return (false);
}
