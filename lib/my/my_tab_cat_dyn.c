/*
** my_tab_cat_dyn.c for tab cat in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May 19 12:13:16 2016 Frederic ODDOU
** Last update Thu May 19 12:50:06 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>

void			my_tab_cat_dyn(char		**tab1,
				       char		**tab2)
{
  int			i;
  int			j;

  i = 0;
  j = 0;
  while (tab1[i] != NULL)
    i++;
  while (tab2[j] != NULL)
    tab1[i++] = strdup(tab2[j++]);
  tab1[i] = NULL;
}
