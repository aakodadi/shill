/* 
 * File:   user.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on October 16, 2016, 2:01 PM
 */

#ifndef USER_H
#define USER_H

#include "timestamp.h"
#include "../type/string.h"


#ifdef __cplusplus
extern "C" {
#endif

    struct _user{
        unsigned long id;
        timestamp t;
        string username;
        string email;
        string name;
        string password;
        string password_confirmation;
        string auth_token;
    };

    typedef struct _user user;
    
    user user_serialize(string user_json);
    string user_deserialize(user u);


#ifdef __cplusplus
}
#endif

#endif /* USER_H */

