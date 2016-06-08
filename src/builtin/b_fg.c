/*
** b_jobs.c for env in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:40:11 2016 Frederic ODDOU
** Last update Sun May 22 15:42:35 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "shell.h"
#include "utils.h"
#include "my.h"

static int		b_fg_treat(t_shell		*shell,
				   t_jobs		*jobs)
{
  int			status;

  status = 0;
  shell->last_return = EXIT_SUCCESS;
  if (!shell->write)
    {
      shell_change_tgrp(getpgid(jobs->pid));
      kill(-jobs->pid, SIGCONT);
      waitpid(-jobs->pid, &status, WUNTRACED);
      shell->last_return = shell_wait_status(status);
      if (!WIFSTOPPED(status))
	utils_jobs_delete_elem(shell, jobs);
      shell_change_tgrp(shell->pid.pgid);
    }
  return (shell->last_return);
}

int			b_fg(int			ac,
			     char			**av,
			     t_shell			*shell)
{
  t_jobs		*jobs;
  unsigned int		id;

  jobs = utils_jobs_go_back(shell->jobs);
  if (ac > 1)
    {
      id = my_atoi(av[1]);
      while (jobs != NULL && jobs->id != id)
	jobs = jobs->next;
    }
  if (jobs == NULL)
    {
      if (shell->write)
	fprintf(stderr, "Jobs not found.\n");
      return (EXIT_FAILURE);
    }
  return (b_fg_treat(shell, jobs));
}
