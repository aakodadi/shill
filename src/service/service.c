/*
   File:   service.c
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

#include "service.h"

post_collection
service_get_posts ()
{
  long http_code;
  string raw_result;
  post_collection result;
  raw_result = repository_get (TARGET_POSTS, &http_code);

  if (http_code == 401)
    {
      error (EXIT_FAILURE, 0, _ ("unauthorized to access posts"));
    }

  post_collection_initialize (&result);

  result = post_collection_deserialize (raw_result);

  string_destroy (&raw_result);

  return result;
}

post
service_get_post (unsigned long id)
{
  long http_code;
  string raw_result;
  post result;
  raw_result = repository_get (TARGET_POST, id, &http_code);

  result = post_deserialize (raw_result);

  return result;
}

post
service_post (post p)
{
  string post_data;
  long http_code;
  string raw_result;
  post result;

  if (http_code == 401)
    {
      error (EXIT_FAILURE, 0, _ ("unauthorized to post"));
    }

  post_data = post_serialize (p);

  raw_result = repository_post (TARGET_POSTS, &http_code, post_data);
  string_destroy (&post_data);

  result = post_deserialize (raw_result);

  return result;
}

user
service_register (user u)
{
  string post_data;
  long http_code;
  string raw_result;
  user result;

  post_data = user_serialize (u);

  raw_result = repository_post (TARGET_REGISTER, &http_code, post_data);
  string_destroy (&post_data);

  if (http_code == 422)
    {
      error (EXIT_FAILURE, 0, _ ("invalid user information"));
      // TODO: create a error model with parser and print the error here
    }

  result = user_deserialize (raw_result);

  return result;
}

user
service_login (user u)
{
  string post_data;
  long http_code;
  string raw_result;
  user result;

  post_data = user_serialize (u);

  raw_result = repository_post (TARGET_LOGIN, &http_code, post_data);
  string_destroy (&post_data);

  if (http_code == 401 || http_code == 422)
    {
      error (EXIT_FAILURE, 0, _ ("invalid login information"));
    }

  user_initialize (&result);
  result = user_deserialize (raw_result);

  return result;
}
