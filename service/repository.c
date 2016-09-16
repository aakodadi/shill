#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <curl/curl.h>

#include "repository.h"

const char* _base_url = "http://localhost:3000/";

string repository_request(target t, unsigned long id) {
    switch (t) {
        case post_target:
            return request_post(id);
        default:

            break;
    }
}

string repository_request_collection(collection_target t) {
    switch (t) {
        case posts_target:
            return request_posts();
        default:

            break;
    }
}

string request_post(unsigned long id) {
    string url;
    string tmp;
    string data;

    CURL *curl;
    CURLcode res;

    url = string_create(_base_url);
    tmp = string_create("posts/");
    url = string_catd(&url, &tmp);
    tmp = string_from_unsigned_long(id);
    url = string_catd(&url, &tmp);

    curl = curl_easy_init();
    if (curl) {
        data = string_create("");
        curl_easy_setopt(curl, CURLOPT_URL, url.s);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return data;
}

string request_posts() {
    string url;
    string tmp;
    string data;

    CURL *curl;
    CURLcode res;

    url = string_create(_base_url);
    tmp = string_create("posts/");
    url = string_catd(&url, &tmp);

    curl = curl_easy_init();
    if (curl) {
        data = string_create("");
        curl_easy_setopt(curl, CURLOPT_URL, url.s);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return data;
}

size_t _curl_callback(void *ptr, size_t size, size_t nmemb, string* s) {
    string chunk = string_n_create(ptr, size * nmemb);
    *s = string_catd(s, &chunk);
    
    return size * nmemb;
}