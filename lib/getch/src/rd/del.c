/*
** del.c for del in /lib/getch/src/rd/
**
** Made by Frederic ODDOU
** Login   <login_x@epitech.eu>
**
** Started on  Wed May 25 14:44:32 2016 Frederic ODDOU
** Last update Sat Jun  4 18:11:06 2016 Frederic ODDOU
*/

#include "rd.h"

int     		rd_del(t_rd *rd, int key)
{
  (void)key;
  rd_rm_char(RD_LINE, rd->curs);
  rd_disp(rd);
  return (0);
}
