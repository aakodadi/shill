/*
   File:   post_collection.h
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

#ifndef POST_COLLECTION_H
#define POST_COLLECTION_H

#include <config.h>
#include "system.h"
#include "string_type.h"
#include "post.h"
#include <jansson.h>

#ifdef __cplusplus
extern "C"
{
#endif

  struct _post_collection
  {
    post* p;
    unsigned long len;
  };

  typedef struct _post_collection post_collection;

  void post_collection_initialize (post_collection *pc);
  void post_collection_destroy (post_collection *pc);
  post_collection post_collection_deserialize (string pc_json);


#ifdef __cplusplus
}
#endif

#endif /* POST_COLLECTION_H */
