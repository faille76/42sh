/*
** my_tab_len.c for tab len in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:27:36 2016 Frederic ODDOU
** Last update Sat Apr 30 21:33:35 2016 oddou_f
*/

#include <stdlib.h>

int		my_tab_len(char		**tab)
{
  int		i;

  i = 0;
  if (tab == NULL)
    return (-1);
  while (tab[i] != NULL)
    i++;
  return (i);
}
