/*
** shell_treat_parenthese.c for shell_treat_parenthese in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 11 14:29:26 2016 Frederic ODDOU
** Last update Wed May 11 14:30:20 2016 oddou_f
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int			shell_treat_parenthese(t_shell		*shell,
					       t_pipe		*pipe)
{
  if ((pipe->pid = fork()) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "fork");
      shell_close(shell, EXIT_FAILURE);
    }
  else if (pipe->pid == 0)
    {
      if (pipe->fd[FD_IN] != -1)
	shell->fd[FD_IN] = pipe->fd[FD_IN];
      if (pipe->fd[FD_OUT] != -1)
	shell->fd[FD_OUT] = pipe->fd[FD_OUT];
      shell_step(shell, strdup(pipe->commands->str));
      shell_close(shell, shell->last_return);
    }
  return (EXIT_SUCCESS);
}
