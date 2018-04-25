/*
   File:   repository.c
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

#include "repository.h"

string
repository_get (target t, ...)
{
  va_list vl;
  long *http_code;
  string path;
  string url;
  string result;
  va_start (vl, t);
  path = _build_path (t, vl);
  http_code = va_arg (vl, long*);
  va_end (vl);
  url = _build_url (path);
  result = _get (url, http_code);
  string_destroy (&path);
  string_destroy (&url);
  return result;
}

string
repository_post (target t, ...)
{
  va_list vl;
  string path;
  long *http_code;
  string url;
  string result;
  string data;
  va_start (vl, t);
  path = _build_path (t, vl);
  url = _build_url (path);
  http_code = va_arg (vl, long*);
  data = va_arg (vl, string);
  va_end (vl);
  result = _post (url, http_code, data);
  string_destroy (&path);
  string_destroy (&url);
  return result;
}

string
repository_delete (target t, ...)
{
  va_list vl;
  string path;
  long *http_code;
  string url;
  string result;
  string data;
  va_start (vl, t);
  path = _build_path (t, vl);
  url = _build_url (path);
  http_code = va_arg (vl, long*);
  data = va_arg (vl, string);
  va_end (vl);
  result = _delete (url, http_code, data);
  string_destroy (&path);
  string_destroy (&url);
  return result;
}

string
_build_path (target t, va_list vl)
{
  unsigned long id;
  switch (t)
    {
    case TARGET_POST:
      id = va_arg (vl, unsigned long);
      return _build_post_path (id);
    case TARGET_POSTS:
      return _build_posts_path ();
    case TARGET_REGISTER:
      return _build_register_path ();
    case TARGET_LOGIN:
      return _build_login_path ();
    case TARGET_LOGOUT:
      return _build_logout_path ();
    default:
      assert(0);
      break;
    }
}

string
_build_posts_path ()
{
  string path = string_create ("posts/");
  return path;
}

string
_build_post_path (unsigned long id)
{
  string path = string_create ("posts/");
  string tmp = string_from_unsigned_long (id);
  path = string_catd (&path, &tmp);
  return path;
}

string
_build_register_path ()
{
  string path = string_create ("users/");
  return path;
}

string
_build_login_path ()
{
  string path = string_create ("auth/");
  return path;
}

string
_build_logout_path ()
{
  string path = string_create ("auth/");
  return path;
}

string
_build_url (string path)
{
  string url = string_cat (configuration.base_url, path);
  return url;
}

string
_get (string url, long *http_code)
{
  string result;
  string auth_header;
  struct curl_slist *headers = NULL;

  string err_msg;
  int errnum;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init ();
  if (curl)
    {
      result = string_create ("");
      if (configuration.u.auth_token.len != -1L
          && configuration.u.username.len != -1L)
        {
          auth_header = string_createf ("Authorization: "
                                        "Token token=\"%s\", "
                                        "username=\"%s\"", configuration.u.auth_token.s,
                                        configuration.u.username.s);
          headers = curl_slist_append (headers, auth_header.s);
          curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headers);
        }
      curl_easy_setopt (curl, CURLOPT_URL, url.s);
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, _curl_callback);
      curl_easy_setopt (curl, CURLOPT_WRITEDATA, &result);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform (curl);
      /* Check for errors */
      if (res != CURLE_OK)
        {
          error (EXIT_FAILURE, errno,
                 _ ("unable to perform a request to the server: %s"),
                 curl_easy_strerror (res));
        }
      curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, http_code);

      /* always cleanup */
      curl_easy_cleanup (curl);
    }

  return result;
}

string
_delete (string url, long *http_code, string data)
{
  string result;
  string auth_header;
  struct curl_slist *headers = NULL;

  string err_msg;
  int errnum;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init ();
  if (curl)
    {
      result = string_create ("");
      if (configuration.u.auth_token.len != -1L
          && configuration.u.username.len != -1L)
        {
          auth_header = string_createf ("Authorization: "
                                        "Token token=\"%s\", "
                                        "username=\"%s\"", configuration.u.auth_token.s,
                                        configuration.u.username.s);

          headers = curl_slist_append (headers, auth_header.s);
        }
      headers = curl_slist_append (headers, "Content-Type: application/json");
      curl_easy_setopt (curl, CURLOPT_URL, url.s);
      curl_easy_setopt (curl, CURLOPT_POSTFIELDS, data.s);
      curl_easy_setopt (curl, CURLOPT_POSTFIELDSIZE, data.len);
      curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "DELETE");
      curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, _curl_callback);
      curl_easy_setopt (curl, CURLOPT_WRITEDATA, &result);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform (curl);
      /* Check for errors */
      if (res != CURLE_OK)
        {
          error (EXIT_FAILURE, errno,
                 _ ("unable to perform a request to the server: %s"),
                 curl_easy_strerror (res));
        }
      curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, http_code);

      /* always cleanup */
      curl_easy_cleanup (curl);
    }

  return result;
}

string
_post (string url, long *http_code, string data)
{
  string result;
  struct curl_slist *headers = NULL;
  string auth_header;

  string err_msg;
  int errnum;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init ();
  if (curl)
    {
      result = string_create ("");
      if (configuration.u.auth_token.len != -1L
          && configuration.u.username.len != -1L)
        {
          auth_header = string_createf ("Authorization: "
                                        "Token token=\"%s\", "
                                        "username=\"%s\"", configuration.u.auth_token.s,
                                        configuration.u.username.s);

          headers = curl_slist_append (headers, auth_header.s);
        }
      headers = curl_slist_append (headers, "Content-Type: application/json");
      curl_easy_setopt (curl, CURLOPT_URL, url.s);
      curl_easy_setopt (curl, CURLOPT_POSTFIELDS, data.s);
      curl_easy_setopt (curl, CURLOPT_POSTFIELDSIZE, data.len);
      curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, _curl_callback);
      curl_easy_setopt (curl, CURLOPT_WRITEDATA, &result);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform (curl);
      /* Check for errors */
      if (res != CURLE_OK)
        {
          error (EXIT_FAILURE, errno,
                 _ ("unable to perform a request to the server: %s"),
                 curl_easy_strerror (res));
        }
      curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, http_code);

      /* always cleanup */
      curl_easy_cleanup (curl);
    }

  return result;
}

size_t
_curl_callback (void *ptr, size_t size, size_t nmemb, string* s)
{
  string chunk = string_n_create (ptr, size * nmemb);
  *s = string_catd (s, &chunk);

  return size * nmemb;
}
