/*
** b_alias.c for set in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 12:44:31 2016 Frederic ODDOU
** Last update Fri Jun  3 23:03:19 2016 oddou_f
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"
#include "my.h"

static void		tab_view(char				**tab)
{
  int			i;
  int			len;

  i = 0;
  len = my_tab_len(tab);
  if (len > 1)
    printf("'");
  while (tab[i] != NULL)
    {
      printf("%s", tab[i]);
      if (tab[i + 1] != NULL)
	printf(" ");
      i++;
    }
  if (len > 1)
    printf("'");
}

static void		b_alias_view(t_shell			*shell)
{
  t_alias		*alias;

  alias = shell->alias;
  while (alias != NULL && alias->next != NULL)
    alias = alias->next;
  while (alias != NULL)
    {
      printf("alias ");
      tab_view(alias->av_origin);
      printf("=");
      tab_view(alias->av_to);
      printf("\n");
      alias = alias->prev;
    }
}

static int		b_alias_treat(char			**av,
				      t_shell			*shell)
{
  char			**tab_to;

  if (utils_special_alias_set(shell, &av[1]) == false)
    {
      tab_to = my_str_to_wordtab(av[2], ' ');
      tab_to = utils_alias_replace(shell, tab_to, true);
      shell->alias = utils_alias_add_left(shell->alias,
					  my_str_to_wordtab(av[1], ' '),
					  tab_to);
    }
  return (EXIT_SUCCESS);
}

int			b_alias(int				ac,
				char				**av,
				t_shell				*shell)
{
  if (ac > 2)
    return (b_alias_treat(av, shell));
  else
    {
      if (shell->write)
	b_alias_view(shell);
    }
  return (EXIT_FAILURE);
}
