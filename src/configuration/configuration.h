/*
   File:   configuration.h
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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <config.h>
#include "system.h"
#include <jansson.h>
#include "argument.h"
#include "string_type.h"
#include "user.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct _shill_configuration
  {
    string base_url;
    user u;
  };

  typedef struct _shill_configuration shill_configuration;

  void configuration_initialize ();
  void configuration_parse ();
  void configuration_create ();
  void configuration_save_user ();
  void configuration_check_user();
  string _configuration_get_file_path ();

  shill_configuration configuration;


#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATION_H */
