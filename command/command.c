#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../service/service.h"
#include "../argument/argument.h"
#include "../error/error.h"

#include "command.h"

const char* command_list[4] = {"login", "post", "comment", "queue"};

void commande_execute() {
    command c = _command_get_form_argument();
    switch(c){
        case COMMAND_QUEUE:
            _queue();
            break;
        default:
            error_handle(CODE_ERROR, 0, "Command unimplemented yet");
    }
}

command _command_get_form_argument() {
    if (strcmp("login", arguments.commande) == 0) {
        return COMMAND_LOGIN;
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

void _queue() {
    post_collection result = get_posts();
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