/*
** shell_pipe.c for shell in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri May  6 12:29:25 2016 Frederic ODDOU
** Last update Fri May 13 20:33:34 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

void			shell_pipe_close(t_pipe			*pipe)
{
  if (pipe->fd[FD_OUT] > STDOUT_FILENO)
    close(pipe->fd[FD_OUT]);
  pipe->fd[FD_OUT] = STDOUT_FILENO;
  if (pipe->fd[FD_IN] > STDIN_FILENO)
    close(pipe->fd[FD_IN]);
  pipe->fd[FD_IN] = STDIN_FILENO;
}

void			shell_pipe_open(t_shell			*shell,
					t_pipe			*mypipe)
{
  int			fd[2];

  if (mypipe->next)
    {
      if ((pipe(fd)) == -1)
	{
	  fprintf(stderr, ERROR_FUNCTION, "pipe");
	  shell_close(shell, EXIT_FAILURE);
	}
      mypipe->next->fd[FD_IN] = fd[0];
      mypipe->fd[FD_OUT] = fd[1];
    }
}
