/*
** func_stack.h for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed Apr 19 20:04:48 2017 Arthur Josso
** Last update Thu Apr 20 20:29:57 2017 Arthur Josso
*/

#pragma once

#include "misc.h"

typedef struct s_stack_node t_stack_node;

struct s_stack_node
{
  t_address    	addr;
  t_address    	rip;
  const char	*name;
  t_stack_node	*next;
};

t_address      	stack_pop_func();
t_address	stack_get_rip();
void		stack_clear();
void            stack_push_func(t_address addr, t_address rip,
                                const char *name);
const char	*stack_get_named_caller();
