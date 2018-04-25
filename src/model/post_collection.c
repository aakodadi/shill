/*
   File:   post_collection.c
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

#include "post_collection.h"

void
post_collection_initialize (post_collection *pc)
{
  pc->len = -1L;
  pc->p = NULL;
}

void
post_collection_destroy (post_collection *pc)
{
  unsigned long i_post;

  if (pc->len != -1L)
    {
      for (i_post = 0; i_post < pc->len; i_post++)
        {
          post_destroy (&pc->p[i_post]);
        }
      free (pc->p);
    }
  pc->len = -1L;
  pc->p = NULL;
}

post_collection
post_collection_deserialize (string pc_json)
{
  post_collection result;
  unsigned long i_post;
  json_t *json_root, *json_post, *json_id, *json_body, *json_created_at,
          *json_updated_at, *json_user, *json_username, *json_name,
          *json_email;
  json_error_t json_error;

  json_root = json_loads (pc_json.s, 0, &json_error);

  if (!json_root)
    {
      error (EXIT_FAILURE, 0,
             _ ("%d:%d: cannot parse json content: %s"),
             json_error.line,
             json_error.column,
             json_error.text);
    }

  if (!json_is_array (json_root))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("cannot parse json content: \
expected root element to be a json array: %s"),
             pc_json.s);
    }

  result.len = json_array_size (json_root);
  result.p = malloc (result.len * sizeof (post));

  for (i_post = 0; i_post < result.len; i_post++)
    {
      json_post = json_array_get (json_root, i_post);

      if (!json_is_object (json_post))
        {
          json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("cannot parse json content: \
expected elements in root to be json objects: %s"),
             pc_json.s);
        }

      json_id = json_object_get (json_post, "id");
      json_body = json_object_get (json_post, "body");
      json_created_at = json_object_get (json_post, "created_at");
      json_updated_at = json_object_get (json_post, "updated_at");
      json_user = json_object_get (json_post, "user");

      if (json_is_integer (json_id))
        {
          result.p[i_post].id = json_integer_value (json_id);
        }

      if (json_is_string (json_body))
        {
          result.p[i_post].body = string_create (json_string_value (json_body));
        }

      if (json_is_integer (json_created_at))
        {
          result.p[i_post].t.created_at = json_integer_value (json_created_at);
        }

      if (json_is_integer (json_updated_at))
        {
          result.p[i_post].t.updated_at = json_integer_value (json_updated_at);
        }

      user_initialize (&result.p[i_post].u);
      if (json_is_object (json_user))
        {
          json_username = json_object_get (json_user, "username");
          json_email = json_object_get (json_user, "email");
          json_name = json_object_get (json_user, "name");

          if (json_is_string (json_username))
            {
              result.p[i_post].u.username = string_create (json_string_value (json_username));
            }
          if (json_is_string (json_email))
            {
              result.p[i_post].u.email = string_create (json_string_value (json_email));
            }
          if (json_is_string (json_name))
            {
              result.p[i_post].u.name = string_create (json_string_value (json_name));
            }
        }
    }

  json_decref (json_root);

  return result;
}
