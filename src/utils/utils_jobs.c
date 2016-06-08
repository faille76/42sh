/*
** utils_jobs.c for jobs in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat May 21 11:27:04 2016 Frederic ODDOU
** Last update Sat May 21 12:25:47 2016 oddou_f
*/

#include <stdlib.h>
#include <signal.h>
#include "shell.h"

void			utils_jobs_delete_elem(t_shell		*shell,
					       t_jobs		*jobs)
{
  if (jobs->prev != NULL)
    jobs->prev->next = jobs->next;
  else
    shell->jobs = jobs->next;
  if (jobs->next != NULL)
    jobs->next->prev = jobs->prev;
  if (jobs->name != NULL)
    free(jobs->name);
  free(jobs);
}

void			utils_jobs_delete_list(t_shell		*shell,
					       t_jobs		*jobs)
{
  t_jobs		*tmp;

  while (jobs != NULL)
    {
      tmp = jobs;
      jobs = jobs->next;
      utils_jobs_delete_elem(shell, tmp);
    }
}

t_jobs			*utils_jobs_go_back(t_jobs		*jobs)
{
  while (jobs != NULL && jobs->prev != NULL)
    jobs = jobs->prev;
  return (jobs);
}

t_jobs			*utils_jobs_go_end(t_jobs		*jobs)
{
  while (jobs != NULL && jobs->next != NULL)
    jobs = jobs->next;
  return (jobs);
}

t_jobs			*utils_jobs_add_right(t_jobs		*jobs,
					      char		*name,
					      pid_t		pid)
{
  t_jobs		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->prev = jobs;
  new->next = NULL;
  new->name = name;
  new->pid = pid;
  new->id = 1;
  if (jobs != NULL)
    {
      new->id = jobs->id + 1;
      jobs->next = new;
    }
  return (new);
}
