#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../service/service.h"
#include "../argument/argument.h"
#include "../configuration/configuration.h"
#include "../error/error.h"
#include "../model/user.h"

#include "command.h"

void commande_execute() {
    command c = _command_get_form_argument();
    switch (c) {
        case COMMAND_QUEUE:
            _command_queue();
            break;
        case COMMAND_POST:
            _command_post();
            break;
        case COMMAND_LOGIN:
            _command_login();
            break;
        case COMMAND_REGISTER:
            _command_register();
            break;
        default:
            error_handle(CODE_ERROR, 0, "Command unimplemented yet");
    }
}

command _command_get_form_argument() {
    if (strcmp("login", arguments.commande) == 0) {
        return COMMAND_LOGIN;
    } else if (strcmp("register", arguments.commande) == 0) {
        return COMMAND_REGISTER;
    } else if (strcmp("post", arguments.commande) == 0) {
        return COMMAND_POST;
    } else if (strcmp("comment", arguments.commande) == 0) {
        return COMMAND_COMMENT;
    } else if (strcmp("queue", arguments.commande) == 0) {
        return COMMAND_QUEUE;
    } else {
        error_handle(CODE_ERROR, 0, "Unexpected argument");
    }
}

void _command_queue() {
    post_collection result = service_get_posts();
    unsigned long post_i;
    char date[20];
    /*
     * Temporary
     */
    for (post_i = 0; post_i < result.len; post_i++) {
        // this is not good buffer overflow danger*****
        strftime(date, 20, "%Y-%m-%d %H:%M:%S", localtime(&result.p[post_i].t.created_at));
        printf("Id: %lu\nBody: %s\nDate: %s\n\n",
                result.p[post_i].id,
                result.p[post_i].body.s,
                date);
        string_destroy(&result.p[post_i].body);
    }
    free(result.p);
}

void _command_post() {

}

void _command_login() {
    user u;
    user result;
    
    user_initialize(&u);
    if (arguments.username == NULL) {
        printf("Username: ");
        u.username = string_gets(50);
    } else {
        u.username = string_create(arguments.username);
    }

    printf("Password: ");
    u.password = string_getpass(72);
    
    result = service_login(u);
    user_destroy(&u);
    configuration.u = result;
    configuration_save_user();
}

void _command_register() {
    user u;
    user_initialize(&u);
    printf("Username: ");
    u.username = string_gets(50);
    printf("Email: ");
    u.email = string_gets(255);
    printf("Name: ");
    u.name = string_gets(50);
    printf("Password: ");
    u.password = string_getpass(72);
    printf("Password confirmation: ");
    u.password_confirmation = string_getpass(72);
    service_register(u);
    string_destroy(&u.username);
    string_destroy(&u.email);
    string_destroy(&u.name);
    string_destroy(&u.password);
    string_destroy(&u.password_confirmation);
}