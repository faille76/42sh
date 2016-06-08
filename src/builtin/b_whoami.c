/*
** b_whoami.c for whoami in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Thu Jun  2 10:40:53 2016 Frederic ODDOU
** Last update Thu Jun  2 10:45:40 2016 Frederic ODDOU
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "shell.h"

int			b_whoami(int			ac,
				 char			**av,
				 t_shell		*shell)
{
  struct passwd		*pwd;

  (void)ac;
  (void)av;
  if ((pwd = getpwuid(geteuid())) == NULL)
    {
      if (!shell->write)
	fprintf(stderr, ERROR_FUNCTION, "getpwuid");
      return (EXIT_FAILURE);
    }
  if (!shell->write)
    printf("%s\n", pwd->pw_name);
  return (EXIT_SUCCESS);
}
