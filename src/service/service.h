/* 
 * File:   service.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 18, 2016, 10:47 PM
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

