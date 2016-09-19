/* 
 * File:   service.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 18, 2016, 10:47 PM
 */

#ifndef SERVICE_H
#define SERVICE_H

#include "../model/post.h"

#ifdef __cplusplus
extern "C" {
#endif

    post* get_posts();
    post get_post(unsigned long id);


#ifdef __cplusplus
}
#endif

#endif /* SERVICE_H */

