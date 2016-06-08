/*
** b_export.c for export in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May 23 15:35:37 2016 Frederic ODDOU
** Last update Sun Jun  5 17:35:51 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "utils.h"
#include "builtin.h"

static int		b_export_treat(char			**av,
				       t_shell			*shell)
{
  char			*reponse[2];
  char			*av_set[4];

  reponse[0] = NULL;
  reponse[1] = NULL;
  if (utils_tab_fusion(av, reponse))
    {
      av_set[0] = "setenv";
      av_set[1] = reponse[0];
      av_set[2] = reponse[1];
      av_set[3] = NULL;
      b_setenv(3, av_set, shell);
      free(reponse[0]);
      free(reponse[1]);
      return (EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

int			b_export(int				ac,
				 char				**av,
				 t_shell			*shell)
{
  (void)ac;
  if (utils_if_fusion(&av[1]) == true)
    return (b_export_treat(&av[1], shell));
  else
    {
      if (shell->write)
	fprintf(stdout, "[Usage] export name=value\n");
    }
  return (EXIT_FAILURE);
}
