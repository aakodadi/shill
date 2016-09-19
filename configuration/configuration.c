#include <stdio.h>
#include <jansson.h>
#include "../argument/argument.h"
#include "../error/error.h"
#include "../type/string.h"

#include "configuration.h"

void configuration_parse() {
    string err_msg;
    int errnum;
    char* conf_file_path = arguments.config;
    FILE* conf_file;
    json_t *json_root, *json_configuration, *json_server, *json_base_url;
    json_error_t error;

    conf_file = fopen(conf_file_path, "r");
    if (conf_file == NULL) {
        errnum = errno;
        err_msg = string_createf("Cannot open configuration file \"%s\"", conf_file_path);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    json_root = json_loadf(conf_file, 0, &error);

    if (fclose(conf_file)) {
        errnum = errno;
        err_msg = string_createf("Cannot close configuration file \"%s\"", conf_file_path);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }
    if (!json_root) {
        err_msg = string_createf("Cannot parse json file \"%s\". Error on line %d column %d : %s",
                conf_file_path,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\". Root element is not a json object", conf_file_path);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_configuration = json_object_get(json_root, "configuration");

    if (!json_is_object(json_configuration)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\". \"configuration\" element not found or is not a json object", conf_file_path);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_server = json_object_get(json_configuration, "server");

    if (!json_is_object(json_server)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\". \"server\" element not found or is not a json object", conf_file_path);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_base_url = json_object_get(json_server, "base-url");
    if (!json_is_string(json_base_url)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\". \"base-url\" element not found or is not a string", conf_file_path);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    configuration.base_url = json_string_value(json_base_url);
}
