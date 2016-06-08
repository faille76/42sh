/*
** get_next_line.c for get_next_line in /home/alies/rendu/CPE_2015_getnextline
**
** Made by Arnaud Alies
** Login   <alies_a@epitech.net>
**
** Started on  Thu Dec 17 13:44:58 2015 Arnaud Alies
** Last update Sat May 28 15:39:28 2016 Frederic ODDOU
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

static int	append_next(char	**next,
			    int		*next_size,
			    const char	*buff,
			    const int	buff_size)
{
  char		*res;
  int		x;

  if ((res = malloc(sizeof(char) * (buff_size + *next_size + 1))) == NULL)
    return (1);
  x = 0;
  while (x < *next_size)
    {
      res[x] = (*next)[x];
      x += 1;
    }
  x = 0;
  while (x < buff_size)
    {
      res[*next_size] = buff[x];
      *next_size += 1;
      x += 1;
    }
  res[*next_size] = '\0';
  if (*next != NULL)
    free(*next);
  *next = res;
  return (0);
}

static char	*dump_next(char		**next,
			   int 		*next_size,
			   int 		x)
{
  char		*res;
  char		*new_next;
  int		size;

  size = *next_size - x;
  if ((new_next = malloc(sizeof(char) * (size))) == NULL)
    return (NULL);
  if ((res = malloc(sizeof(char) * (x + 1))) == NULL)
    return (NULL);
  *next_size = 0;
  while (*next_size < x)
    {
      res[*next_size] = (*next)[*next_size];
      *next_size += 1;
    }
  res[*next_size - 1] = '\0';
  *next_size = 0;
  while (*next_size < size)
    {
      new_next[*next_size] = (*next)[x + *next_size];
      *next_size += 1;
    }
  free(*next);
  *next = new_next;
  return (res);
}

static int	is_line(int		set)
{
  static int	is_line = 1;

  if (set == -1)
    is_line = 0;
  if (set == 1)
    is_line = 1;
  return (is_line);
}

static char	*get_line(char 		**next,
			  int 		*next_size)
{
  int		x;

  x = 0;
  while (x < *next_size)
    {
      if ((*next)[x] == '\n')
	{
	  is_line((*next)[x] == '\n' ? 1 : -1);
	  return (dump_next(next, next_size, x + 1));
	}
      x += 1;
    }
  return (NULL);
}

char		*get_next_line(const int fd, char **next, int *size)
{
  char		buff[READ_SIZE];
  int		r;
  char		*res;

  if (fd < 0)
    return (NULL);
  while ((res = get_line(next, size)) == NULL)
    {
      if ((r = read(fd, buff, READ_SIZE)) == -1)
	return (NULL);
      if (append_next(next, size, buff, r))
	return (NULL);
      if (r <= 0)
	{
	  if (*size > 0)
	    {
	      *size += 1;
	      return (dump_next(next, size, *size));
	    }
	  return (NULL);
	}
    }
  return (res);
}
