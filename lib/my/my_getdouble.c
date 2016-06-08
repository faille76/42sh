/*
** my_getdouble.c for my in /home/josso/rendu/gfx/gfx_raytracer1
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Feb 18 11:04:51 2016 Arthur Josso
** Last update Wed May 25 14:39:56 2016 Arthur Josso
*/

#include "my.h"

static int      get_part_nb(char *s)
{
  int           len;
  int           ret;
  long          mult;

  ret = 0;
  len = -1;
  mult = 1;
  while (s && s[++len]);
  len--;
  while (len >= 0 && s[len] != '-')
    {
      ret += mult * (s[len] - '0');
      mult *= 10;
      len--;
    }
  if (len == 0 && s[len] == '-')
    ret *= -1;
  return (ret);
}

static int      is_nbr(char c, char neg)
{
  if (c >= '0' && c <= '9')
    return (1);
  else if (neg == 0 && c == '-')
    return (1);
  else
    return (0);
}

static double   get_whole_part(char *s, int *i)
{
  char          buff[DOUBLE_SIZE];
  double        ret;

  *i = 0;
  while (s[*i] && s[*i] != '.' && *i < DOUBLE_SIZE)
    {
      if (!is_nbr(s[*i], *i))
	{
	  *i = -1;
	  return (0);
	}
      buff[*i] = s[*i];
      (*i)++;
    }
  if (*i == DOUBLE_SIZE)
    {
      *i = -1;
      return (0);
    }
  buff[*i] = '\0';
  ret = (double)get_part_nb(buff);
  if (!s[*i] || !s[*i + 1])
    *i = -1;
  return (ret);
}

static double   get_decimal_part(char *s, int *i)
{
  char          buff[DOUBLE_SIZE];
  double        ret;

  *i = 0;
  while (s[*i] && *i < DOUBLE_SIZE)
    {
      if (!is_nbr(s[*i], -1))
	{
	  *i = -1;
	  return (0);
	}
      buff[*i] = s[*i];
      (*i)++;
    }
  if (*i == DOUBLE_SIZE)
    {
      *i = -1;
      return (0);
    }
  buff[*i] = '\0';
  ret = (double)get_part_nb(buff);
  return (ret);
}

double          get_double(char *s)
{
  int           i;
  int           mult;
  double        ret;
  double        dec;
  int           div;

  if (!is_float(s))
    return (0);
  if (!s || !s[0])
    return (0);
  ret = get_whole_part(s, &i);
  if (i == -1)
    return (ret);
  dec = get_decimal_part(s + i + 1, &i);
  if (i == -1)
    return (ret);
  div = 10;
  mult = 1;
  while (mult++ < i)
    div *= 10;
  ret += s[0] != '-' ? dec / div : -dec / div;
  return (ret);
}
