/* 
 * File:   service.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 18, 2016, 10:47 PM
 */

#ifndef SERVICE_H
#define SERVICE_H

#include "../model/post.h"
#include "../model/post_collection.h"

#ifdef __cplusplus
extern "C" {
#endif

    post_collection get_posts();
    post get_post(unsigned long id);


#ifdef __cplusplus
}
#endif

#endif /* SERVICE_H */

