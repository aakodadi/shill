/* 
 * File:   command.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 21, 2016, 2:24 AM
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <config.h>
#include "system.h"
#include "service.h"
#include "argument.h"
#include "configuration.h"
#include "user.h"

#ifdef __cplusplus
extern "C"
{
#endif

  enum _command
  {
    COMMAND_FEED,
    COMMAND_POST,
    COMMAND_COMMENT,
    COMMAND_LOGIN,
    COMMAND_REGISTER,
    COMMAND_CONFIGURE
  };

  typedef enum _command command;

  void commande_execute ();

  command _command_get_form_argument ();
  void _command_feed ();
  void _command_post ();
  void _command_login ();
  void _command_register ();
  void _command_configure ();


#ifdef __cplusplus
}
#endif

#endif /* COMMAND_H */

