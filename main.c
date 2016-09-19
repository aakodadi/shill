#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>
#include "argument/argument.h"
#include "service/repository.h"
#include "configuration/configuration.h"
#include "service/service.h"
#include "model/post.h"

int main(int argc, char** argv) {
    
    
    /*
     * Default values.
     */
    arguments.verbose = 0;
    arguments.config = "config.json";
    
    /*
     * Parse our arguments; every option seen by parse_opt will be
     * reflected in arguments.
     */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    
    printf("command: %s\n", arguments.commande);
    
    configuration_parse();
    
    printf("base-url: %s\n", configuration.base_url);
    
    post* posts;
    posts = get_posts();
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&posts[0].t.created_at));
    
    printf("post: id = %lu, body = %s, created_at = %s\n", posts[0].id, posts[0].body.s, buff);


    return (EXIT_SUCCESS);
}

