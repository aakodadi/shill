/*
   File:   repository.h
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

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <config.h>
#include "system.h"
#include "string_type.h"
#include "configuration.h"
#include <stdarg.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /*
   * Because we don't want the services to deal with urls,
   * these enumerations are used to tell the repository which element
   * or elements we are requesting.
   * The repository would request the right url according to the _target
   * passed.
   */
  enum _target
  {
    TARGET_POST,
    TARGET_POSTS,
    TARGET_REGISTER,
    TARGET_LOGIN,
    TARGET_LOGOUT,
  };

  typedef enum _target target;

  /*
   * the last argument to repository_get must be a long pinter
   * in order to contain the http status code
   */
  string repository_get (target t, ...);
  /*
   * the last argument to repository_post/repository_delete
   * must be a string data containing the data to post/delete
   */
  /*
   * the second last argument to repository_post/repository_delete
   * must be a long pinter in order to contain the http status code
   */
  string repository_post (target t, ...);
  string repository_delete (target t, ...);

  string _build_path (target t, va_list vl);
  string _build_post_path (unsigned long id);
  string _build_posts_path ();
  string _build_register_path ();
  string _build_login_path ();
  string _build_logout_path ();
  string _build_url (string path);
  string _get (string url, long *http_code);
  string _delete (string url, long *http_code, string data);
  string _post (string url, long *http_code, string data);

  size_t _curl_callback (void *ptr, size_t size, size_t nmemb, string* s);



#ifdef __cplusplus
}
#endif

#endif /* REPOSITORY_H */
