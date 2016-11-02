/* 
 * File:   repository.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 15, 2016, 8:39 AM
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

