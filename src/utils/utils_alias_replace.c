/*
** utils_alias_replace.c for alias replace in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 22:40:13 2016 Frederic ODDOU
** Last update Sun Jun  5 17:51:28 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"
#include "my.h"

static char		**utils_alias_change(t_alias		*alias,
					     char		**av)
{
  char			**new;
  int			len;

  len = my_tab_len(&av[my_tab_len(alias->av_origin)])
    + my_tab_len(alias->av_to);
  if ((new = malloc(sizeof(char *) * (len + 2))) == NULL)
    return (av);
  new[0] = NULL;
  my_tab_cat(new, alias->av_to);
  my_tab_cat(new, &av[my_tab_len(alias->av_origin)]);
  free(av);
  return (new);
}

static char		**utils_alias_change_force(t_alias	*alias,
						   char		**av)
{
  char			**new;
  int			len;

  len = my_tab_len(&av[my_tab_len(alias->av_origin)])
    + my_tab_len(alias->av_to);
  if ((new = malloc(sizeof(char *) * (len + 2))) == NULL)
    return (av);
  new[0] = NULL;
  my_tab_cat_dyn(new, alias->av_to);
  my_tab_cat_dyn(new, &av[my_tab_len(alias->av_origin)]);
  my_tab_free(av);
  return (new);
}

char			**utils_alias_replace(t_shell		*shell,
					      char		**av,
					      bool		press)
{
  t_alias		*alias;

  alias = shell->alias;
  while (alias != NULL)
    {
      if (my_tabn_cmp(alias->av_origin, av, my_tab_len(alias->av_origin)))
	{
	  if (press == true)
	    return (utils_alias_change_force(alias, av));
	  return (utils_alias_change(alias, av));
	}
      alias = alias->next;
    }
  return (av);
}
