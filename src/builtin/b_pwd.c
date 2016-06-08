/*
** b_pwd.c for pwd in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Thu Jun  2 10:46:15 2016 Frederic ODDOU
** Last update Fri Jun  3 23:37:46 2016 Frederic ODDOU
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int			b_pwd(int			ac,
			      char			**av,
			      t_shell			*shell)
{
  char			pwd[4096];

  (void)ac;
  (void)av;
  if (getcwd(pwd, 4096) == NULL)
    {
      if (shell->write)
	fprintf(stderr, ERROR_FUNCTION, "getcwd");
      return (EXIT_FAILURE);
    }
  if (shell->write)
    printf("%s\n", pwd);
  return (EXIT_SUCCESS);
}
