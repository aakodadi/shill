/*
   File:   post.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
   Brief: Probably the most important data flowing in this project are posts.
   this file defines the data structure of posts.

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

#ifndef POST_H
#define POST_H

#include <config.h>
#include "system.h"
#include "string_type.h"
#include "user.h"
#include "timestamp.h"
#include <jansson.h>


#ifdef __cplusplus
extern "C"
{
#endif

  struct _post
  {
    unsigned long id;
    timestamp t;
    string body;
    user u;
  };

  typedef struct _post post;

  void post_initialize (post *p);
  void post_destroy (post *p);
  post post_deserialize (string post_json);
  string post_serialize (post p);

#ifdef __cplusplus
}
#endif

#endif /* POST_H */
