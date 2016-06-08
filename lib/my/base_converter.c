/*
** base_converter.c for base_converter in /lib/my/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Tue May 31 22:50:43 2016 Frederic ODDOU
** Last update Tue May 31 22:58:31 2016 Frederic ODDOU
*/

static int	my_pow(int nbr, int pwr)
{
  int		i;
  int		res;

  i = 0;
  res = 1;
  while (i < pwr)
    {
      res = res * nbr;
      i++;
    }
  return (res);
}

int		base_converter(char *nb, int base)
{
  int		i;
  int		pwr;
  int		res;

  res = i = pwr = 0;
  while (nb[i] != '\0')
    i++;
  i--;
  while (i >= 0)
    {
      res += (nb[i] - '0') * my_pow(base, pwr);
      pwr++;
      i--;
    }
  return (res);
}
