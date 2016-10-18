/* 
 * File:   configuration.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 18, 2016, 7:11 PM
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../model/user.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _shill_configuration {
        const char* base_url;
        user u;
    };

    typedef struct _shill_configuration shill_configuration;
    
    void configuration_parse();
    
    shill_configuration configuration;
    
    
#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATION_H */

