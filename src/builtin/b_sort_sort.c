/*
** b_sort_sort.c for sort in /home/josso/rendu/psu/PSU_2015_42sh
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed May 25 18:19:43 2016 Arthur Josso
** Last update Wed May 25 18:44:39 2016 Arthur Josso
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "builtin_sort.h"

static bool	have_to_swap(t_tab	*tab,
			     int	i)
{
  if (tab->flag & F_N)
    {
      if (tab->tmp_f[i] > tab->tmp_f[i + 1])
	return (true);
    }
  else if (strcmp(tab->tmp_s[i], tab->tmp_s[i + 1]) > 0)
    return (true);
  return (false);
}

static void	swap(t_tab	*tab,
		     int	i)
{
  char		*tmp_s;
  float		tmp_f;

  if (tab->flag & F_N)
    {
      tmp_f = tab->tmp_f[i];
      tab->tmp_f[i] = tab->tmp_f[i + 1];
      tab->tmp_f[i + 1] = tmp_f;
    }
  else
    {
      tmp_s = tab->tmp_s[i];
      tab->tmp_s[i] = tab->tmp_s[i + 1];
      tab->tmp_s[i + 1] = tmp_s;
    }
  tmp_s = tab->tab[i];
  tab->tab[i] = tab->tab[i + 1];
  tab->tab[i + 1] = tmp_s;
}

void	sort_tab(t_tab	*tab)
{
  bool	sorted;
  int	i;

  sorted = false;
  while (!sorted)
    {
      sorted = true;
      i = 0;
      while (i < tab->size - 1)
	{
	  if (have_to_swap(tab, i))
	    {
	      swap(tab, i);
	      sorted = false;
	    }
	  i++;
	}
    }
}
