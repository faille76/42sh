/*
** shell_list.c for shell list in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  8 15:17:14 2016 Frederic ODDOU
** Last update Sun May 22 14:24:43 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"

static void		shell_list_desactive(t_list	*list,
					     short	id_sep)
{
  while (list != NULL && list->type_separator == id_sep)
    {
      list->treat = false;
      list = list->next;
    }
}

bool			shell_list_treat(t_shell	*shell)
{
  t_list		*list;
  pid_t			pgid;

  list = shell->list;
  while (list != NULL)
    {
      if (list->treat == true)
	{
	  pgid = shell_treat_pipe_do(shell, list->pipe);
	  shell_treat_pipe_wait(shell, list, list->pipe, pgid);
	  if (shell->last_return != EXIT_SUCCESS)
	    shell_list_desactive(list->next, ID_AND);
	  else
	    shell_list_desactive(list->next, ID_OR);
	}
      list = list->next;
    }
  return (true);
}
