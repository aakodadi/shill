/*
   File:   user.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014 Free Software
   Foundation, Inc.

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

#ifndef USER_H
#define USER_H

#include <config.h>
#include "system.h"
#include "timestamp.h"
#include "string_type.h"
#include <jansson.h>


#ifdef __cplusplus
extern "C"
{
#endif

  struct _user
  {
    unsigned long id;
    timestamp t;
    string username;
    string email;
    string name;
    string password;
    string password_confirmation;
    string auth_token;
  };

  typedef struct _user user;

  void user_initialize (user *u);
  void user_destroy (user *u);
  user user_deserialize (string user_json);
  string user_serialize (user u);


#ifdef __cplusplus
}
#endif

#endif /* USER_H */
