/*
** my_str_to_wordtab.c for str to word tab in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:10:38 2016 Frederic ODDOU
** Last update Wed May 18 15:19:59 2016 oddou_f
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"

static char		**my_str_to_wordtab_fill(char		**tab,
					       char		*str,
					       char		c)
{
  int			i_str;
  int			i_tab;
  int			deb;

  deb = i_str = i_tab = 0;
  while (str[i_str] != '\0')
    {
      if ((c != ' ' && str[i_str] == c) ||
	  (c == ' ' && (str[i_str] == ' ' || str[i_str] == '\t')))
	{
	  tab[i_tab++] = strndup(&str[deb], i_str - deb);
	  deb = i_str + 1;
	}
      i_str++;
    }
  tab[i_tab++] = strndup(&str[deb], i_str - deb);
  tab[i_tab] = NULL;
  return (tab);
}

char			**my_str_to_wordtab(char		*str,
					    char		c)
{
  char			**tab;
  unsigned int		count;

  if (str == NULL)
    return (NULL);
  count = my_count_char(str, c);
  if (c == ' ')
    count += my_count_char(str, '\t');
  if ((tab = malloc(sizeof(char *) * (count + 2))) == NULL)
    return (NULL);
  return (my_str_to_wordtab_fill(tab, str, c));
}
