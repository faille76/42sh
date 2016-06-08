/*
** my_str_realloc.c for strrealloc in /lib/my/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Wed Jun  1 12:56:35 2016 Frederic ODDOU
** Last update Wed Jun  1 13:37:19 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <string.h>

char			*my_str_realloc(char			*s1,
					char			*s2)
{
  size_t		len;

  if (s1 == NULL)
    {
      if ((s1 = malloc(sizeof(char))) == NULL)
	return (NULL);
      *s1 = '\0';
    }
  if (s2 == NULL)
    return (s1);
  len = strlen(s1) + strlen(s2);
  s1 = realloc(s1, sizeof(char) * (len + 1));
  s1 = strcat(s1, s2);
  return (s1);
}
