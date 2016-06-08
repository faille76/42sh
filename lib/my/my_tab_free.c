/*
** my_tab_free.c for tab free in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:45:18 2016 Frederic ODDOU
** Last update Sat Apr 16 11:45:18 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include "my.h"

bool		my_tab_free(char	**tab)
{
  int		i;

  i = 0;
  if (tab == NULL)
    return (false);
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
  return (true);
}
