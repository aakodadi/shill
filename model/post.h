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

#include "timestamp.h"
#include "../type/string.h"


#ifdef __cplusplus
extern "C" {
#endif

    struct _post {
        unsigned long id;
        timestamp t;
        string body;
    };
    
    typedef struct _post post;

#ifdef __cplusplus
}
#endif

#endif /* POST_H */

