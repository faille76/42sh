/*
** b_which.c for which in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 14:44:42 2016 Frederic ODDOU
** Last update Sat Apr 15 21:28:42 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"

static int		b_which_treat(char			**av,
				      t_shell			*shell)
{
  char			*str;
  int			i;
  bool			find;

  if (!shell->write)
    return (EXIT_SUCCESS);
  i = 1;
  find = true;
  while (av[i] != NULL)
    {
      if (b_is_builtin(av[i]) != NOT_BUILTIN)
	printf(IS_BUILTIN, av[i]);
      else if ((str = shell_get_path(shell, av[i])) != NULL)
	{
	  printf("%s\n", str);
	  free(str);
	}
      else
	{
	  fprintf(stderr, ERROR_NOTFOUND, av[i]);
	  find = false;
	}
      i++;
    }
  return (find ? EXIT_SUCCESS : EXIT_FAILURE);
}

int			b_which(int				ac,
				char				**av,
				t_shell				*shell)
{
  if (ac < 2)
    {
      if (shell->write)
	fprintf(stdout, FEW_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  return (b_which_treat(av, shell));
}
