#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <assert.h>
#include <curl/curl.h>
#include "../configuration/configuration.h"
#include "../error/error.h"

#include "repository.h"

string repository_request(target t, ...) {
    va_list vl;
    string path;
    string url;
    string result;
    va_start(vl, t);
    path = _build_path(t, vl);
    va_end(vl);
    url = _build_url(path);
    result = _request(url);
    string_destroy(&path);
    string_destroy(&url);
    return result;
}

string _build_path(target t, va_list vl) {
    unsigned long id;
    switch (t) {
        case TARGET_POST:
            id = va_arg(vl, unsigned long);
            return _build_post_path(id);
        case TARGET_POSTS:
            return _build_posts_path();
        default:
            error_handle(CODE_ERROR, 0, "In repository, unexpected target while building path, this code block must never get executed");
            break;
    }
}

string _build_posts_path() {
    string path = string_create("posts/");
    return path;
}

string _build_post_path(unsigned long id) {
    string path = string_create("posts/");
    string tmp = string_from_unsigned_long(id);
    path = string_catd(&path, &tmp);
    return path;
}

string _build_url(string path) {
    string base_url = string_create(configuration.base_url);
    string url = string_cat(base_url, path);
    string_destroy(&base_url);
    return url;
}

string _request(string url) {
    string data;

    string err_msg;
    int errnum;

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        data = string_create("");
        curl_easy_setopt(curl, CURLOPT_URL, url.s);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            errnum = errno;
            err_msg = string_createf("Unable to perform a request to the server \"%s\"", curl_easy_strerror(res));
            error_handle(IO_ERROR, errnum, err_msg.s);
        }

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