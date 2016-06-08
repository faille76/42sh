/*
** shell_treat_backquotes.c for backquote in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 11 19:27:03 2016 Frederic ODDOU
** Last update Sat Jun  4 00:00:04 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "my.h"
#include "shell.h"
#include "utils.h"

static t_commands	*shell_fork_pere(t_pipe			*mypipe,
					 t_commands		*commands,
					 int			*fd)
{
  char			*str;
  int			size;
  char			*next;
  unsigned int		len;

  size = 0;
  if ((next = malloc(sizeof(char))) == NULL)
    return (NULL);
  next[0] = '\0';
  str = NULL;
  len = 0;
  while ((str = get_next_line(fd[0], &next, &size)) != NULL)
    {
      if ((len = len + strlen(str)) >= LIMIT_BUF_QUOTE)
	{
	  free(next);
	  close(fd[0]);
	  kill(mypipe->pid, SIGKILL);
	  return (commands);
	}
      commands = utils_commands_add_right(commands, str, ID_WITHOUT);
    }
  free(next);
  close(fd[0]);
  return (commands);
}

static t_commands	*shell_fork_backquotes(t_shell		*shell,
					       t_pipe		*mypipe,
					       t_commands	*commands)
{
  int			fd[2];

  if ((pipe(fd)) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "pipe");
      shell_close(shell, EXIT_FAILURE);
    }
  if ((mypipe->pid = fork()) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "fork");
      shell_close(shell, EXIT_FAILURE);
    }
  else if (mypipe->pid == 0)
    {
      close(fd[0]);
      shell->fd[FD_OUT] = fd[1];
      shell_step(shell, strdup(commands->str));
      shell_close(shell, shell->last_return);
    }
  close(fd[1]);
  return (shell_fork_pere(mypipe, commands, fd));
}

void			shell_treat_backquotes(t_shell		*shell,
					       t_pipe		*pipe)
{
  t_commands		*commands;
  t_commands		*tmp;
  t_commands		*tmp_next;

  commands = pipe->commands;
  while (commands != NULL)
    {
      if (commands->index_delim == ID_BACK_QUOTE)
	{
	  tmp = commands;
	  tmp_next = tmp->next;
	  commands = shell_fork_backquotes(shell, pipe, commands);
	  utils_pipe_delete_command(pipe, tmp);
	  commands = tmp_next;
	}
      else
	commands = commands->next;
    }
}
