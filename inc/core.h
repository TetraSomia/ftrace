/*
** core.h for lol in /home/tetra/rendu/psu/PSU_2016_strace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Apr  3 10:47:32 2017 Arthur Josso
** Last update Tue Jul  4 11:14:38 2017 Arthur Josso
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/user.h>
#include "misc.h"

#define SYSCALL_OPCODE		(0x050F)
#define BASIC_CALL_OPCODE	(0xE8)
#define DYN_FUNC_MAPPING	(0x10000000000)

typedef unsigned long t_reg;

typedef union
{
  struct user_regs_struct	name;
  t_reg				list[27];
} t_regs;

typedef struct
{
  uint8_t	nb_param;
  const char	*name;
} t_syscalls;

extern const t_syscalls g_sc64[];
extern pid_t pid;
extern char *binary_name;

/*
** Routines
*/

void	fork_routine(char **args);
void    trace_proc();

/*
** Signal handler
*/

#define NEW_SIGNAL_NAME(sig)	{sig, #sig}
#define END_OF_SIG_LIST		(-1)

typedef struct
{
  int		sig;
  const char	*name;
} t_sig_data;

int	check_for_sig(int status);

/*
** Branch type finder
*/

typedef enum
  {
    FIRST_TYPE = 0,
    SYSCALL = 0,
    CALL,
    RET,
    NONE
  } t_branch_type;

typedef bool	(*t_test_func)(const t_regs *regs, const t_regs *old_regs);
typedef void	(*t_exec_func)(const t_regs *regs, const t_regs *old_regs);

typedef struct
{
  t_branch_type	type;
  t_test_func	test_func;
  t_exec_func	exec_func;
} t_branch_data;

void	find_branch(const t_regs *regs, const t_regs *old_regs);

void	exec_syscall(const t_regs *regs, const t_regs *old_regs,
		     bool void_return);
void	exec_call(const t_regs *regs, const t_regs *old_regs);
void	exec_ret(const t_regs *regs, const t_regs *old_regs);

#define MIN_BYTE_CALL_INST	(2)
#define MAX_BYTE_CALL_INST	(7)

bool    test_syscall(const t_regs *regs, const t_regs *old_regs);
bool    test_call(const t_regs *regs, const t_regs *old_regs);
bool    test_ret(const t_regs *regs, const t_regs *old_regs);

/*
** Print
*/

typedef struct
{
  int		id;
  const char	*name;
} t_param_order;

void    save_params(const t_regs *regs);
void    print_args(t_reg return_value);

/*
** Parsing
*/

typedef unsigned char t_flag;
extern t_flag option_flags;

enum
  {
    VERBOSE = 0,
    GRAPH,
  };

#define RESETFLAG(f)	(option_flags &= ~(1 << f))
#define SETFLAG(f)	(option_flags |= 1 << f)
#define GETFLAG(f)	((option_flags >> f) & 1)

int	parse_options(int ac, char **av);

/*
** Path
*/

char    *find_path(const char *file);

/*
** Print
*/

void	print_data(const char *fmt, ...);
