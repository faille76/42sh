/*
** utils_pipe.c for utils pipe in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 16:39:30 2016 Frederic ODDOU
** Last update Mon May 16 17:15:11 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"

void			utils_pipe_delete_command(t_pipe	*pipe,
						  t_commands	*commands)
{
  if (commands->prev != NULL)
    commands->prev->next = commands->next;
  else
    pipe->commands = commands->next;
  if (commands->next != NULL)
    commands->next->prev = commands->prev;
  if (commands->str != NULL)
    free(commands->str);
  free(commands);
}

void			utils_pipe_delete_list(t_pipe		*pipe)
{
  t_pipe		*tmp;

  while (pipe != NULL)
    {
      tmp = pipe;
      pipe = pipe->next;
      if (tmp->av != NULL)
	free(tmp->av);
      if (tmp->path != NULL)
	free(tmp->path);
      if (tmp->redi[RED_RIGHT] != NULL)
        free(tmp->redi[RED_RIGHT]);
      if (tmp->redi[RED_TWO_RIGHT] != NULL)
        free(tmp->redi[RED_TWO_RIGHT]);
      if (tmp->redi[RED_LEFT] != NULL)
        free(tmp->redi[RED_LEFT]);
      if (tmp->redi[RED_TWO_LEFT] != NULL)
	free(tmp->redi[RED_TWO_LEFT]);
      if (tmp->commands != NULL)
	utils_commands_delete_list(tmp->commands);
      free(tmp);
    }
}

void			utils_pipe_delete_elem(t_list		*list,
					       t_pipe		*pipe)
{
  if (pipe->prev != NULL)
    pipe->prev->next = pipe->next;
  else
    list->pipe = pipe->next;
  if (pipe->next != NULL)
    pipe->next->prev = pipe->prev;
  if (pipe->av != NULL)
    free(pipe->av);
  if (pipe->path != NULL)
    free(pipe->path);
  if (pipe->redi[RED_RIGHT] != NULL)
    free(pipe->redi[RED_RIGHT]);
  if (pipe->redi[RED_TWO_RIGHT] != NULL)
    free(pipe->redi[RED_TWO_RIGHT]);
  if (pipe->redi[RED_LEFT] != NULL)
    free(pipe->redi[RED_LEFT]);
  if (pipe->redi[RED_TWO_LEFT] != NULL)
    free(pipe->redi[RED_TWO_LEFT]);
  if (pipe->commands != NULL)
    utils_commands_delete_list(pipe->commands);
  free(pipe);
}

t_pipe			*utils_pipe_add_right(t_pipe		*pipe,
					      t_commands	*commands)
{
  t_pipe		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->prev = pipe;
  new->next = NULL;
  new->commands = commands;
  new->av = NULL;
  new->ac = 0;
  new->pid = 0;
  new->redi[RED_RIGHT] = new->redi[RED_TWO_RIGHT] = NULL;
  new->redi[RED_LEFT] = new->redi[RED_TWO_LEFT] = NULL;
  new->fd[FD_IN] = new->fd[FD_OUT] = -1;
  new->path = NULL;
  if (pipe != NULL)
    {
      if (pipe->next != NULL)
	{
	  new->next = pipe->next;
	  pipe->next->prev = new;
	}
      pipe->next = new;
    }
  return (new);
}

t_pipe			*utils_pipe_go_back(t_pipe		*pipe)
{
  while (pipe != NULL && pipe->prev != NULL)
    pipe = pipe->prev;
  return (pipe);
}
