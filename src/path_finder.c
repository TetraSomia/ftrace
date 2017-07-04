/*
** path_finder.c for lol in /home/tetra/rendu/psu/PSU_2016_ftrace
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Apr 17 19:25:11 2017 Arthur Josso
** Last update Mon Apr 17 19:53:05 2017 Arthur Josso
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "core.h"

static bool	file_exists(const char *path)
{
  struct stat	path_stat;

  if (stat(path, &path_stat) == -1)
    return (false);
  if (S_ISREG(path_stat.st_mode))
    return (true);
  return (false);
}

char	*find_path(const char *file)
{
  char	*paths;
  char	buff[4096];
  char	*tmp;
  char	*tok;

  if (strchr(file, '/') && file_exists(file))
    return (strdup(file));
  if ((paths = getenv("PATH")) == NULL)
    return (NULL);
  if ((paths = strdup(paths)) == NULL)
    return (NULL);
  tmp = paths;
  while ((tok = strsep(&tmp, ":")) != NULL)
    {
      strcpy(buff, tok);
      strcat(buff, "/");
      strcat(buff, file);
      if (file_exists(buff))
	break;
    }
  free(paths);
  if (tok == NULL)
    return (NULL);
  return (strdup(buff));
}
