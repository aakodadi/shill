#include <stdio.h>
#include <time.h>
#include "../service/service.h"

#include "command.h"

const char* command_list[4] = {"login", "post", "comment", ""};

void commande_execute() {
    post* result = get_posts();
    unsigned long post_i;
    char date[20];
    /*
     * Temporary
     */
    for (post_i = 0; post_i < 2; post_i++) {
        // this is not good buffer overflow danger*****
        strftime(date, 20, "%Y-%m-%d %H:%M:%S", localtime(&result[0].t.created_at));
        printf("Id: %lu\nBody: %s\nDate: %s\n\n",
                result[post_i].id,
                result[post_i].body.s,
                date);
    }
}