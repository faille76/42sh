/*
** utils_special_alias.c for special alias in /src/utils/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Sun May 29 22:32:00 2016 Frederic ODDOU
** Last update Sun Jun  5 17:51:12 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "utils.h"

static char		*g_special_alias[] =
  {
    "cwdcmd",
    "precmd",
    "postcmd",
    NULL
  };

static short		utils_special_alias_find(char		*name)
{
  short			id;

  id = 0;
  while (g_special_alias[id] != NULL)
    {
      if (!strcmp(g_special_alias[id], name))
	return (id);
      id++;
    }
  return (NOT_FOUND);
}

bool			utils_special_alias_set(t_shell		*shell,
						char		**av)
{
  char			*reponse[2];
  t_locales		*loc;

  if (utils_special_alias_find(av[0]) != NOT_FOUND)
    {
      if ((loc = utils_locales_find_elem(av[0], shell->locales)) != NULL)
	{
	  if (loc->value != NULL)
	    free(loc->value);
	  loc->value = strdup(av[1]);
	}
      else
	{
	  if ((reponse[0] = strdup(av[0])) == NULL)
	    return (false);
  	  if ((reponse[1] = strdup(av[1])) == NULL)
	    {
	      free(reponse[0]);
	      return (false);
	    }
	  shell->locales = utils_locales_add_left(reponse, shell->locales);
	}
      return (true);
    }
  return (false);
}

bool			utils_special_alias_execute(t_shell	*shell,
						    char	*name)
{
  t_commands		*tmp_commands;
  t_list		*tmp_list;
  int			tmp_last_return;
  short			id;
  t_locales		*loc;

  if ((id = utils_special_alias_find(name)) != NOT_FOUND &&
      (loc = utils_locales_find_elem(name, shell->locales)) != NULL)
    {
      tmp_commands = shell->commands;
      tmp_list = shell->list;
      tmp_last_return = shell->last_return;
      shell->commands = NULL;
      shell->list = NULL;
      shell_step(shell, strdup(loc->value));
      shell->commands = tmp_commands;
      shell->list = tmp_list;
      shell->last_return = tmp_last_return;
      return (true);
    }
  return (false);
}
