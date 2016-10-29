/* 
 * File:   post_collection.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 22, 2016, 10:46 PM
 */

#ifndef POST_COLLECTION_H
#define POST_COLLECTION_H

#include "../type/string.h"
#include "../model/post.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct _post_collection
  {
    post* p;
    unsigned long len;
  };

  typedef struct _post_collection post_collection;

  void post_collection_initialize (post_collection *pc);
  void post_collection_destroy (post_collection *pc);
  post_collection post_collection_deserialize (string pc_json);


#ifdef __cplusplus
}
#endif

#endif /* POST_COLLECTION_H */

