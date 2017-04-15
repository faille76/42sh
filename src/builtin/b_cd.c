/*
** b_cd.c for cd in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 15:27:56 2016 Frederic ODDOU
** Last update Fri Jun  3 23:04:41 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"
#include "utils.h"

static void		b_cd_env(t_shell		*shell,
				 char			*oldpwd)
{
  char			*av[4];
  char			pwd[4096];

  shell->oldpwd = strdup(oldpwd);
  av[0] = "setenv";
  av[1] = "OLDPWD";
  av[2] = shell->oldpwd;
  av[3] = NULL;
  b_setenv(3, av, shell);
  if (getcwd(pwd, 4096) == NULL)
    strcpy(pwd, "/");
  av[1] = "PWD";
  av[2] = pwd;
  b_setenv(3, av, shell);
}

static int		b_cd_goto(char			*directory,
				  t_shell		*shell)
{
  char			oldpwd[4096];

  if (directory == NULL)
    return (EXIT_FAILURE);
  if (getcwd(oldpwd, 4096) == NULL)
    strcpy(oldpwd, "/");
  if (chdir(directory) == -1)
    {
      if (shell->write)
	{
	  if (errno == EACCES)
	    fprintf(stdout, NO_PERMIT, directory);
	  else if (errno == ENOTDIR)
	    fprintf(stdout, NO_FOLDER, directory);
	  else
	    fprintf(stdout, ERROR_NOFILE, directory);
	}
      return (EXIT_FAILURE);
    }
  free(shell->oldpwd);
  b_cd_env(shell, oldpwd);
  if (!shell->write)
    utils_special_alias_execute(shell, "cwdcmd");
  return (EXIT_SUCCESS);
}

int			b_cd(int			ac,
			     char			**av,
			     t_shell			*shell)
{
  if (ac > 2)
    {
      if (shell->write)
	fprintf(stdout, TOO_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  else if (ac == 1)
    return (b_cd_goto(b_getenv(shell->ae, "HOME"), shell));
  else
    {
      if (!strcmp(av[1], "-"))
	return (b_cd_goto(shell->oldpwd, shell));
      else
	return (b_cd_goto(av[1], shell));
    }
}
