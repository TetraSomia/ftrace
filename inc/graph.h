/*
** graph.h for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Apr 20 19:50:35 2017 Arthur Josso
** Last update Fri Apr 21 00:38:11 2017 Arthur Josso
*/

#pragma once

#include <stdint.h>
#include "core.h"
#include "misc.h"

#define MAX_GRAPH_FILENAME_LENGTH	(64)

typedef struct s_link_node t_link_node;
typedef struct s_graph_node t_graph_node;

typedef enum
  {
    NODE_SYSCALL,
    NODE_FUNC,
    NODE_DYN_FUNC
  } t_node_type;

struct s_link_node
{
  t_graph_node	*func;
  uint64_t     	nb_call;
  t_link_node	*next;
};

struct s_graph_node
{
  t_node_type	type;
  const char	*name;
  t_link_node	*call;
  t_graph_node	*next;
};

extern t_graph_node *graph;

typedef struct
{
  t_node_type	type;
  const char	*color;
} t_type_properties;

void	graph_add_node(t_node_type type, const char *name);
void	graph_clear();
void	graph_generate();
