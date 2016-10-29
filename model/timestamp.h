/* 
 * File:   timestamp.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 * Brief: created_at and updated_at fields will be often used in this project.
 * So lets go ahead and define them once for all. afterwards we will be
 * dealing with just one timestamp field.
 *
 * Created on September 15, 2016, 6:20 AM
 */

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "time.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct _timestamp
  {
    time_t created_at;
    time_t updated_at;
  };

  typedef struct _timestamp timestamp;


#ifdef __cplusplus
}
#endif

#endif /* TIMESTAMP_H */

