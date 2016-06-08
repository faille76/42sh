/*
** enum.h for enum in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Apr 25 23:01:53 2016 Frederic ODDOU
** Last update Sat May 14 23:27:00 2016 oddou_f
*/

#pragma once

typedef enum		e_pipe_fd
  {
    FD_IN		= 0,
    FD_OUT		= 1
  }			t_pipe_fd;

typedef enum		e_parser_redirect
  {
    RED_RIGHT		= 0,
    RED_TWO_RIGHT	= 1,
    RED_LEFT		= 2,
    RED_TWO_LEFT	= 3
  }			t_parser_redirect;

typedef enum		e_id_delimit
  {
    ID_WITHOUT		= -1,
    ID_SPACE		= 0,
    ID_TAB		= 1,
    ID_DOUBLE_QUOTE	= 2,
    ID_SIMPLE_QUOTE	= 3,
    ID_BACK_QUOTE	= 4,
    ID_PARENTHESE	= 5,
    ID_REDIRECTION	= 6,
    ID_DOUBLE_RIGHT	= 7,
    ID_RIGHT		= 8,
    ID_DOUBLE_LEFT	= 9,
    ID_LEFT		= 10,
    ID_OR		= 11,
    ID_AND		= 12,
    ID_SEP		= 13,
    ID_PIPE		= 14,
    ID_BACKGROUND	= 15
  }			t_id_delimit;

typedef enum		e_parser_delimit
  {
    D_NORMAL		= 0,
    D_DELIM		= 1,
    D_GET		= 2,
    D_SEPARATOR		= 3
  }			t_parser_delimit;
