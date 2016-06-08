/*
** shell_wait_status.c for wait status in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 11 14:27:09 2016 Frederic ODDOU
** Last update Sat May 21 11:50:10 2016 oddou_f
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include "sig_mess.h"

int			shell_wait_status(int			status)
{
  if (WIFSIGNALED(status))
    {
      sig_display(status);
      return ((SCHAR_MAX + 1) + WTERMSIG(status));
    }
  else if (WIFEXITED(status))
    return (WEXITSTATUS(status));
  else if (WIFSTOPPED(status))
    return (WSTOPSIG(status));
  return (EXIT_SUCCESS);
}
