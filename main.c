#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>
#include "argument/argument.h"
#include "service/repository.h"

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

    char* text = "{ \"post\": { \"id\": \"0\", \"body\": \"body text\" } }";
    json_t *root;
    json_error_t error;
    root = json_loads(text, 0, &error);

    if (!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }
    
    json_t *post = json_object_get(root, "post");
    json_t *body = json_object_get(post, "body");
    const char* body_text = json_string_value(body);
    printf("%s", body_text);


    return (EXIT_SUCCESS);
}

