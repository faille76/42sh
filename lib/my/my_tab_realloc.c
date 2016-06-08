/*
** my_tab_realloc.c for realloc in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:53:13 2016 Frederic ODDOU
** Last update Thu May 05 14:26:26 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"

char		**my_tab_realloc(char	**tab,
				 char	*str)
{
  int		len;

  if ((len = my_tab_len(tab)) == -1)
    return (NULL);
  if ((tab = realloc(tab, sizeof(char *) * (len + 2))) == NULL)
    return (NULL);
  tab[len] = str;
  tab[len + 1] = NULL;
  return (tab);
}
