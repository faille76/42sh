/*
** b_sort_gentmp.c for sort in /home/josso/rendu/psu/PSU_2015_42sh
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed May 25 13:27:47 2016 Arthur Josso
** Last update Wed May 25 14:44:15 2016 Arthur Josso
*/

#include <stdlib.h>
#include "shell.h"
#include "builtin_sort.h"
#include "my.h"

static void	rm_npc(char	**tab)
{
  int		i;
  int		j;
  int		k;

  i = 0;
  while (tab[i])
    {
      j = 0;
      while (tab[i][j])
	{
	  if (tab[i][j] < ' ' || tab[i][j] > '~')
	    {
	      k = j;
	      while (tab[i][k])
		{
		  tab[i][k] = tab[i][k + 1];
		  k++;
		}
	    }
	  else
	    j++;
	}
      i++;
    }
}

static void	rm_uppercase(char	**tab)
{
  int		i;
  int		j;

  i = 0;
  while (tab[i])
    {
      j = 0;
      while (tab[i][j])
	{
	  if (tab[i][j] >= 'A' && tab[i][j] <= 'Z')
	    tab[i][j] = tab[i][j] - 'A' + 'a';
	  j++;
	}
      i++;
    }
}

int	gen_tmp(t_tab	*tab)
{
  int	i;

  tab->size = my_tab_len(tab->tab);
  if (tab->flag & F_N)
    {
      if ((tab->tmp_f = malloc(tab->size * sizeof(float))) == NULL)
	return (1);
      tab->tmp_s = NULL;
      i = -1;
      while (++i < tab->size)
	tab->tmp_f[i] = (float)get_double(tab->tab[i]);
      return (0);
    }
  else
    {
      if ((tab->tmp_s = my_tab_cpy(tab->tab)) == NULL)
	return (1);
      tab->tmp_f = NULL;
      if (tab->flag & F_I)
	rm_npc(tab->tmp_s);
      if (tab->flag & F_F)
	rm_uppercase(tab->tmp_s);
    }
  return (0);
}
