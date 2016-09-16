/* 
 * File:   repository.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 15, 2016, 8:39 AM
 */

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../type/string_type.h"

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
        post_target
    };

    enum _collection_target {
        posts_target
    };

    typedef enum _target target;
    typedef enum _collection_target collection_target;

    /*
     * Temporary: use this as the base url
     * TODO: get it from the configuration
     */
    extern const char* _base_url;

    string repository_request(target t, unsigned long id);
    string repository_request_collection(collection_target t);

    string request_post(unsigned long id);
    string request_posts();
    
    size_t _curl_callback(void *ptr, size_t size, size_t nmemb, string* s);

#ifdef __cplusplus
}
#endif

#endif /* REPOSITORY_H */

