/* 
 * File:   repository.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 15, 2016, 8:39 AM
 */

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../type/string_type.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * Because we don't want the services to deal with urls,
     * these enumerations are used to tell the repository which element
     * or elements we are requesting.
     * The repository would request the right url according to the _target
     * passed.
     */
    enum _target {
        TARGET_POST,
        TARGET_POSTS
    };

    typedef enum _target target;

    string repository_request(target t, ...);
    
    string _build_path(target t, va_list vl);
    string _build_post_path(unsigned long id);
    string _build_posts_path();
    string _build_url(string path);
    string _request(string url);
    
    size_t _curl_callback(void *ptr, size_t size, size_t nmemb, string* s);
    
    

#ifdef __cplusplus
}
#endif

#endif /* REPOSITORY_H */

