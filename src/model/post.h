/* 
 * File:   post.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 * Brief: Probably the most important data flowing in this project are posts.
 * this file defines the data structure of posts.
 *
 * Created on September 15, 2016, 4:32 AM
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

