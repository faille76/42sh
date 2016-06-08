/*
** shell_background.c for background in /src/shell/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 18:08:34 2016 Frederic ODDOU
** Last update Sat Jun  4 00:27:54 2016 Frederic ODDOU
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"

void			shell_background(t_shell	*shell)
{
  t_jobs		*jobs;
  t_jobs		*tmp;
  int			status;

  jobs = shell->jobs;
  while (jobs != NULL)
    {
      status = 0;
      if (waitpid(jobs->pid, &status, WNOHANG))
	{
	  tmp = jobs;
	  printf("[%d]\t+ Done\t%s\n", jobs->id, jobs->name);
          shell->last_return = shell_wait_status(status);
	  jobs = jobs->next;
	  if (tmp == shell->jobs)
	    shell->jobs = shell->jobs->next;
	  utils_jobs_delete_elem(shell, tmp);
	}
      if (jobs != NULL)
	jobs = jobs->next;
    }
}
