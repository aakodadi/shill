#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>
#include "model/post.h"
#include "argument/argument.h"

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
    
    
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/posts/1");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

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

