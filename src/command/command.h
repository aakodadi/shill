/*
   File:   command.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014, 2018 Free
   Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <config.h>
#include "system.h"
#include "service.h"
#include "argument.h"
#include "configuration.h"
#include "user.h"

#ifdef __cplusplus
extern "C"
{
#endif

  enum _command
  {
    COMMAND_FEED,
    COMMAND_POST,
    COMMAND_COMMENT,
    COMMAND_LOGIN,
    COMMAND_REGISTER,
    COMMAND_CONFIGURE
  };

  typedef enum _command command;

  void commande_execute ();

  command _command_get_form_argument ();
  void _command_feed ();
  void _command_post ();
  void _command_login ();
  void _command_register ();
  void _command_configure ();


#ifdef __cplusplus
}
#endif

#endif /* COMMAND_H */
