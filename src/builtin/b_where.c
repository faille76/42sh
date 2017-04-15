/*
** b_which.c for which in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 14:44:42 2016 Frederic ODDOU
** Last update Sat Apr 15 21:27:51 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"
#include "builtin.h"

static bool		shell_check_access(char		*str)
{
  if (access(str, X_OK) == 0)
    return (true);
  else if (errno == ENOTDIR)
    fprintf(stderr, ERROR_NOTFOLDER, str);
  return (false);
}

static int		b_where_treat_find(t_shell	*shell,
					   char		*name)
{
  int			i;
  int			find;
  int			len;
  char			*str;

  i = find = 0;
  len = strlen(name);
  str = NULL;
  while (shell->path[i] != NULL)
    {
      len = strlen(name) + strlen(shell->path[i]) + 2;
      if ((str = realloc(str, sizeof(char) * len)) == NULL)
	return (EXIT_FAILURE);
      memset(str, '\0', len);
      strcat(str, shell->path[i]);
      strcat(str, "/");
      strcat(str, name);
      if (shell_check_access(str))
	find += printf("%s\n", str);
      i++;
    }
  if (str != NULL)
    free(str);
  return (find ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int		b_where_treat(char			**av,
				      t_shell			*shell)
{
  int			i;
  bool			find;

  if (!shell->write)
    return (EXIT_SUCCESS);
  i = 1;
  find = true;
  while (av[i] != NULL)
    {
      if (b_is_builtin(av[i]) != NOT_BUILTIN)
	printf(IS_BUILTIN_W, av[i]);
      if (b_where_treat_find(shell, av[i]) == EXIT_FAILURE)
	find = false;
      i++;
    }
  return (find ? EXIT_SUCCESS : EXIT_FAILURE);
}

int			b_where(int				ac,
				char				**av,
				t_shell				*shell)
{
  if (ac < 2)
    {
      if (shell->write)
	fprintf(stdout, FEW_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  return (b_where_treat(av, shell));
}
