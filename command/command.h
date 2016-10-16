/* 
 * File:   command.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 21, 2016, 2:24 AM
 */

#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif
    
    enum _command {
        COMMAND_QUEUE,
        COMMAND_POST,
        COMMAND_COMMENT,
        COMMAND_LOGIN,
        COMMAND_REGISTER,
    };
    
    typedef enum _command command;
    
    void commande_execute();
    
    command _command_get_form_argument();
    void _queue();
    void _post();
    void _login();
    void _register();


#ifdef __cplusplus
}
#endif

#endif /* COMMAND_H */

