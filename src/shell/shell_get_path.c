/*
** shell_get_path.c for get path in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 12:43:01 2016 Frederic ODDOU
** Last update Mon May 16 17:22:20 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "shell.h"

static bool		shell_check_access(char		*str)
{
  if (access(str, X_OK) == 0)
    return (true);
  else if (errno == ENOTDIR)
    fprintf(stderr, ERROR_NOTFOLDER, str);
  return (false);
}

static char		*shell_find_program(t_shell	*shell,
					    char	*name)
{
  int			i;
  int			len;
  char			*str;

  i = 0;
  len = strlen(name);
  str = NULL;
  while (shell->path[i] != NULL)
    {
      len = strlen(name) + strlen(shell->path[i]) + 2;
      if ((str = realloc(str, sizeof(char) * len)) == NULL)
	return (NULL);
      if (memset(str, '\0', len) == NULL)
	return (NULL);
      if ((str = strcat(str, shell->path[i])) == NULL ||
	  (str = strcat(str, "/")) == NULL ||
	  (str = strcat(str, name)) == NULL)
	return (NULL);
      if (shell_check_access(str))
	return (str);
      i++;
    }
  if (str != NULL)
    free(str);
  return (NULL);
}

static char		*shell_get_path_dir(char	*name)
{
  char			*str;

  if ((str = malloc(sizeof(char) * (strlen(name) + 3))) == NULL)
    return (NULL);
  memset(str, '\0', strlen(name) + 3);
  strcat(str, "./");
  strcat(str, name);
  if (shell_check_access(str))
    return (str);
  free(str);
  return (NULL);
}

char			*shell_get_path(t_shell		*shell,
					char		*name)
{
  char			*str;

  if (name == NULL)
    return (NULL);
  if (strncmp(name, "./", 2) && strncmp(name, "/", 1))
    {
      if (strstr(name, "/") != NULL)
	return (shell_get_path_dir(name));
      else
	{
	  if (shell->path == NULL)
	    return (NULL);
	  if ((str = shell_find_program(shell, name)) != NULL)
	    return (str);
	}
    }
  else
    {
      if (shell_check_access(name))
	return (strdup(name));
    }
  return (NULL);
}
