/*
** b_setenv.c for setenv in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:46:15 2016 Frederic ODDOU
** Last update Sun May 08 23:43:07 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

static bool		b_env_norme(char		*av1)
{
  int			i;

  i = -1;
  while (av1[++i] != '\0')
    {
      if ((av1[i] >= 0 && av1[i] <= 47) || (av1[i] >= 58 && av1[i] <= 64) ||
	  (av1[i] >= 91 && av1[i] <= 94) || av1[i] == 96 || av1[i] >= 123)
	return (false);
    }
  return (true);
}

static int		b_setenv_fill(t_shell		*shell,
				      char		**av,
				      char		*str,
				      int		len)
{
  memset(str, '\0', len);
  strcat(str, av[1]);
  strcat(str, "=");
  if (av[2] != NULL)
    strcat(str, av[2]);
  if (!strcmp(av[1], "PATH"))
    {
      my_tab_free(shell->path);
      shell->path = my_str_to_wordtab(av[2], ':');
    }
  return (EXIT_SUCCESS);
}

static int		b_setenv_find(int		len,
				      char		**av,
				      t_shell		*shell)
{
  char			*str;
  int			id;

  if ((str = b_findenv(shell->ae, av[1])) == NULL)
    {
      if ((str = malloc(sizeof(char) * len)) == NULL)
	return (ERROR_FATAL);
      if ((shell->ae = my_tab_realloc(shell->ae, str)) == NULL)
	return (ERROR_FATAL);
      return (b_setenv_fill(shell, av, str, len));
    }
  else
    {
      id = b_get_id_env(shell->ae, av[1]);
      if ((shell->ae[id] = realloc(shell->ae[id], sizeof(char) * len)) == NULL)
	return (ERROR_FATAL);
      return (b_setenv_fill(shell, av, shell->ae[id], len));
    }
  return (EXIT_SUCCESS);
}

static int		b_setenv_treat(char			**av,
				       t_shell			*shell)
{
  int			len;

  if (b_env_norme(av[1]) == false)
    {
      if (shell->write)
	printf("setenv: Variable name must contain alphanumeric characters.\n");
      return (EXIT_FAILURE);
    }
  len = strlen(av[1]) + ((av[2] != NULL) ? strlen(av[2]) : 0) + 2;
  return (b_setenv_find(len, av, shell));
}

int			b_setenv(int				ac,
				 char				**av,
				 t_shell			*shell)
{
  if (ac == 1)
    return (b_env(ac, av, shell));
  else if (ac >= 4)
    {
      if (shell->write)
	fprintf(stdout, TOO_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  return (b_setenv_treat(av, shell));
}
