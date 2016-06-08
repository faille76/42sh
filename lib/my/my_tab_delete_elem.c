/*
** my_tab_delete_elem.c for my tab delete in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 16:46:21 2016 Frederic ODDOU
** Last update Thu May 05 14:39:37 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"

char		**my_tab_delete_elem(char	**tab,
				     char	*str)
{
  int		i;
  int		len;

  i = 0;
  if ((len = my_tab_len(tab)) == -1)
    return (NULL);
  while (tab[i] != NULL && tab[i] != str)
    i++;
  while (tab[i] != NULL)
    {
      tab[i] = tab[i + 1];
      i++;
    }
  tab[i] = NULL;
  free(str);
  tab = realloc(tab, sizeof(char *) * len);
  return (tab);
}
