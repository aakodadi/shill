/*
   File:   post.c
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

#include "post.h"

void
post_initialize (post *p)
{
  p->id = -1L;
  p->body.len = -1L;
  p->body.s = NULL;
  p->t.created_at = 0;
  p->t.updated_at = 0;
}

void
post_destroy (post *p)
{
  p->id = -1L;

  if (p->body.len != -1L)
    {
      string_destroy (&p->body);
    }

  p->t.created_at = 0;
  p->t.updated_at = 0;
}

post
post_deserialize (string post_json)
{
  post result;
  json_t *json_root, *json_id, *json_body, *json_created_at, *json_updated_at,
          *json_user, *json_username, *json_name, *json_email;
  json_error_t json_error;

  json_root = json_loads (post_json.s, 0, &json_error);

  if (!json_root)
    {
      error (EXIT_FAILURE, 0,
             _ ("%d:%d: cannot parse json content: %s"),
             json_error.line,
             json_error.column,
             json_error.text);
    }

  if (!json_is_object (json_root))
    {
      json_decref (json_root);
      error (EXIT_FAILURE, 0,
             _ ("cannot parse json content: \
expected root element to be a json object: %s"),
             post_json.s);
    }


  json_id = json_object_get (json_root, "id");
  json_body = json_object_get (json_root, "body");
  json_created_at = json_object_get (json_root, "created_at");
  json_updated_at = json_object_get (json_root, "updated_at");
  json_user = json_object_get (json_root, "user");

  post_initialize (&result);
  if (json_is_integer (json_id))
    {
      result.id = json_integer_value (json_id);
    }

  if (json_is_string (json_body))
    {
      result.body = string_create (json_string_value (json_body));
    }

  if (json_is_integer (json_created_at))
    {
      result.t.created_at = json_integer_value (json_created_at);
    }

  if (json_is_integer (json_updated_at))
    {
      result.t.updated_at = json_integer_value (json_updated_at);
    }

  user_initialize (&result.u);
  if (json_is_object (json_user))
    {
      json_username = json_object_get (json_user, "username");
      json_email = json_object_get (json_user, "email");
      json_name = json_object_get (json_user, "name");

      if (json_is_string (json_username))
        {
          result.u.username = string_create (json_string_value (json_username));
        }
      if (json_is_string (json_email))
        {
          result.u.email = string_create (json_string_value (json_email));
        }
      if (json_is_string (json_name))
        {
          result.u.name = string_create (json_string_value (json_name));
        }
    }

  json_decref (json_root);

  return result;
}

string
post_serialize (post p)
{
  string result;

  json_t *json_root = NULL, *json_body = NULL, *json_post = NULL;

  if (p.body.len != -1L)
    {
      json_body = json_pack ("s", p.body.s);
    }

  json_root = json_object ();
  json_post = json_object ();

  if (json_body != NULL)
    {
      json_object_set (json_post, "body", json_body);
    }

  json_object_set (json_root, "post", json_post);

  result = string_create (json_dumps (json_root, JSON_COMPACT));

  json_decref (json_root);

  return result;
}
