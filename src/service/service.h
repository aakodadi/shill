/*
   File:   service.h
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

#ifndef SERVICE_H
#define SERVICE_H

#include <config.h>
#include "system.h"
#include "post.h"
#include "post_collection.h"
#include "user.h"
#include "repository.h"

#ifdef __cplusplus
extern "C"
{
#endif

  post_collection service_get_posts ();
  post service_get_post (unsigned long id);
  user service_register (user u);
  user service_login (user u);
  post service_post (post p);


#ifdef __cplusplus
}
#endif

#endif /* SERVICE_H */
