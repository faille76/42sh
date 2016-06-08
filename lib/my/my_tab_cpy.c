/*
** my_tab_cpy.c for tab cpy in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:29:08 2016 Frederic ODDOU
** Last update Fri Apr 29 23:09:25 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

char		**my_tab_cpy(char	**tab)
{
  char		**new;
  int		len;
  int		i;

  i = 0;
  if ((len = my_tab_len(tab)) == -1)
    return (NULL);
  if ((new = malloc(sizeof(char *) * (len + 1))) == NULL)
    return (NULL);
  while (i < len)
    {
      new[i] = strdup(tab[i]);
      i++;
    }
  new[i] = NULL;
  return (new);
}
