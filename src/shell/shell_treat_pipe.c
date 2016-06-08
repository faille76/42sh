/*
** shell_treat_pipe.c for treat pipe in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 10:18:46 2016 Frederic ODDOU
** Last update Sun May 22 15:49:25 2016 oddou_f
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

static void		shell_treat_pipe_commands(t_shell	*shell,
						  t_pipe	*pipe)
{
  shell->write = true;
  shell->last_return = 0;
  shell_signal(false);
  if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
    shell->last_return = b_exec(shell, pipe);
  else if ((pipe->path = shell_get_path(shell, pipe->av[0])) != NULL)
    {
      execve(pipe->path, pipe->av, shell->ae);
      if (errno == ENOEXEC)
	{
	  fprintf(stdout, ERROR_FORMAT, pipe->av[0]);
  	  fprintf(stdout, ERROR_NOEXEC);
	}
      else
	fprintf(stdout, ERROR_ALLOW, pipe->av[0]);
      shell->last_return = EXIT_FAILURE;
    }
  else
    {
      shell->last_return = EXIT_FAILURE;
      fprintf(stderr, ERROR_NOTFOUND, pipe->av[0]);
    }
  shell_close(shell, shell->last_return);
}

static pid_t		shell_treat_commands(t_shell	*shell,
					     t_pipe	*pipe,
					     pid_t	pgid)
{
  if ((pipe->pid = fork()) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "fork");
      shell_close(shell, EXIT_FAILURE);
    }
  if (pipe->pid != 0)
    {
      if (pipe->prev == NULL)
	pgid = pipe->pid;
      setpgid(pipe->pid, pgid);
      if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
	shell->last_return = b_exec(shell, pipe);
    }
  if (pipe->pid == 0)
    {
      shell_signal(false);
      if (shell_dup(shell, pipe) == false)
	shell_close(shell, EXIT_FAILURE);
      if (pipe->next)
	close(pipe->next->fd[FD_IN]);
      shell_treat_pipe_commands(shell, pipe);
    }
  return (pgid);
}

static void		shell_treat_pipe_suspend(t_shell	*shell,
						 t_list		*list,
						 t_pipe		*pipe,
						 int		status)
{
  if (pipe != NULL || pipe->av == NULL || pipe->av[0] == NULL)
    return ;
  if (WIFSTOPPED(status) || list->background == true)
    {
      shell->jobs = utils_jobs_add_right(shell->jobs,
					 strdup(pipe->av[0]),
					 pipe->pid);
      if (shell->jobs != NULL)
	{
	  if (list->background == true)
	    printf("[%d] %d\n", shell->jobs->id, shell->jobs->pid);
	  else
	    printf(MESS_SUSPENDED, shell->jobs->id,
		   shell->jobs->pid, shell->jobs->name);
	}
    }
}

pid_t			shell_treat_pipe_do(t_shell	*shell,
					    t_pipe	*pipe)
{
  pid_t			pgid;

  pgid = 0;
  while (pipe != NULL)
    {
      shell_pipe_open(shell, pipe);
      if (pipe->commands->index_delim == ID_PARENTHESE)
        shell->last_return = shell_treat_parenthese(shell, pipe);
      else if (utils_commands_to_tab(shell, pipe) == true)
	pgid = shell_treat_commands(shell, pipe, pgid);
      else
	shell->last_return = EXIT_FAILURE;
      shell_pipe_close(pipe);
      pipe = pipe->next;
    }
  return (pgid);
}

void			shell_treat_pipe_wait(t_shell	*shell,
					      t_list	*list,
					      t_pipe	*pipe,
					      pid_t	pgid)
{
  int			status;

  shell_change_tgrp(pgid);
  while (pipe != NULL)
    {
      status = 0;
      if (list->background == true)
	waitpid(-pgid, &status, WNOHANG | WUNTRACED);
      else
	waitpid(-pgid, &status, WUNTRACED);
      shell->last_return = shell_wait_status(status);
      shell_treat_pipe_suspend(shell, list, pipe, status);
      pipe = pipe->next;
    }
  shell_change_tgrp(shell->pid.pgid);
}
