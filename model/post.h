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


#ifdef __cplusplus
extern "C" {
#endif

    struct __post {
        unsigned long id;
        _timestamp timestamp;
        char* body;
    };
    
    typedef struct __post _post;

#ifdef __cplusplus
}
#endif

#endif /* POST_H */

