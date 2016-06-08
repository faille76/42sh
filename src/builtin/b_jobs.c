/*
** b_jobs.c for env in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:40:11 2016 Frederic ODDOU
** Last update Sat May 21 12:01:58 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"

int			b_jobs(int			ac,
			       char			**av,
			       t_shell			*shell)
{
  t_jobs		*jobs;

  if (!shell->write)
    return (EXIT_SUCCESS);
  jobs = utils_jobs_go_back(shell->jobs);
  while (jobs != NULL)
    {
      printf("[%u]\t%s\n", jobs->id, jobs->name);
      jobs = jobs->next;
    }
  (void)ac;
  (void)av;
  return (EXIT_SUCCESS);
}
