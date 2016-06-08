/*
** my_tabn_cmp.c for my_tabn_cmp in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 22:46:22 2016 Frederic ODDOU
** Last update Wed May 18 22:47:39 2016 oddou_f
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool			my_tabn_cmp(char	**tab1,
				    char	**tab2,
				    int		n)
{
  int			i;

  i = 0;
  while (tab1[i] != NULL && tab2[i] != NULL && i < n)
    {
      if (strcmp(tab1[i], tab2[i]))
	return (false);
      i++;
    }
  if (i < n)
    return (false);
  return (true);
}
