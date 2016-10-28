#include <stdio.h>
#include <jansson.h>
#include <string.h>
#include <unistd.h>
#include "../argument/argument.h"
#include "../error/error.h"
#include "../type/string.h"

#include "configuration.h"

#define DEFAULT_BASE_URL "http://shilld.herokuapp.com/"

string _configuration_get_file_path() {
    string err_msg;
    string conf_file_path;
    string home_directory;
    string file_name = string_create(".shill_config.json");
    string separator = string_create("/");

    if (arguments.config == NULL) {
        home_directory = string_create(getenv("HOME"));

        if (home_directory.len == 0) {
            err_msg = string_create("Couldn't find home directory");
            error_handle(IO_ERROR, 0, err_msg.s);
            exit(-1);
        }

        conf_file_path = string_catd(&home_directory, &separator);
        conf_file_path = string_catd(&conf_file_path, &file_name);
    } else {
        conf_file_path = string_create(arguments.config);
    }
}

void configuration_parse() {
    string err_msg;
    int errnum;
    string conf_file_path;
    FILE* conf_file;
    json_t *json_root, *json_configuration, *json_server, *json_base_url,
            *json_user, *json_username, *json_auth_token;
    json_error_t error;

    conf_file_path = _configuration_get_file_path();

    conf_file = fopen(conf_file_path.s, "r");
    if (conf_file == NULL) {
        errnum = errno;
        if (errnum == ENOENT){
            configuration_create();
            return;
        }
        err_msg = string_createf("Cannot open configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    json_root = json_loadf(conf_file, 0, &error);

    if (fclose(conf_file)) {
        errnum = errno;
        err_msg = string_createf("Cannot close configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }
    if (!json_root) {
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " Error on line %d column %d : %s",
                conf_file_path.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " Expected root element to be a json object",
                conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_configuration = json_object_get(json_root, "configuration");

    if (!json_is_object(json_configuration)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " \"configuration\" element not found or is not a json object",
                conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_server = json_object_get(json_configuration, "server");

    json_user = json_object_get(json_configuration, "user");

    if (!json_is_object(json_server)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " \"server\" element not found or is not a json object",
                conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_base_url = json_object_get(json_server, "base-url");

    if (!json_is_string(json_base_url)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\". "
                "\"base-url\" element not found or is not a string",
                conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    configuration.base_url =
            string_create(json_string_value(json_base_url));

    if (json_is_object(json_user)) {
        json_username = json_object_get(json_user, "username");
        json_auth_token = json_object_get(json_user, "auth_token");

        if (json_is_string(json_username)) {
            configuration.u.username =
                    string_create(json_string_value(json_username));
        } else {
            configuration.u.username.len = -1L;
        }

        if (json_is_string(json_auth_token)) {
            configuration.u.auth_token =
                    string_create(json_string_value(json_auth_token));
        } else {
            configuration.u.auth_token.len = -1L;
        }
    } else {
        configuration.u.auth_token.len = -1L;
        configuration.u.username.len = -1L;
    }

    json_decref(json_root);
}

void configuration_save_user() {
    string err_msg;
    int errnum;
    string conf_file_path;
    FILE* conf_file;
    json_t *json_root, *json_configuration, *json_user, *json_username,
            *json_auth_token;
    json_error_t error;

    conf_file_path = _configuration_get_file_path();

    conf_file = fopen(conf_file_path.s, "r");
    if (conf_file == NULL) {
        errnum = errno;
        err_msg = string_createf("Cannot open configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    json_root = json_loadf(conf_file, 0, &error);

    if (fclose(conf_file)) {
        errnum = errno;
        err_msg = string_createf("Cannot close configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }
    if (!json_root) {
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " Error on line %d column %d : %s",
                conf_file_path.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " Root element is not a json object", conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_configuration = json_object_get(json_root, "configuration");

    if (!json_is_object(json_configuration)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json file \"%s\"."
                " \"configuration\" element not found or is not a json object",
                conf_file_path.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_username = json_pack("s", configuration.u.username.s);
    json_auth_token = json_pack("s", configuration.u.auth_token.s);

    json_user = json_object();

    json_object_set(json_user, "username", json_username);
    json_object_set(json_user, "auth_token", json_auth_token);

    json_object_set(json_configuration, "user", json_user);

    conf_file = fopen(conf_file_path.s, "w");
    if (conf_file == NULL) {
        errnum = errno;
        err_msg = string_createf("Cannot open configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    if (json_dumpf(json_root, conf_file, JSON_INDENT(4)) == -1) {
        errnum = errno;
        json_decref(json_root);
        err_msg = string_createf("Cannot write into configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    if (fclose(conf_file)) {
        errnum = errno;
        json_decref(json_root);
        err_msg = string_createf("Cannot close configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    json_decref(json_root);
}

void configuration_create() {
    string err_msg;
    int errnum;
    string conf_file_path;
    FILE* conf_file;
    json_t *json_root, *json_configuration, *json_server, *json_base_url;

    conf_file_path = _configuration_get_file_path();

    if (arguments.base_url == NULL) {
        json_base_url = json_pack("s", DEFAULT_BASE_URL);
    } else {
        json_base_url = json_pack("s", arguments.base_url);
    }
    
    json_configuration = json_object();
    json_root = json_object();
    json_server = json_object();
    
    json_object_set(json_server, "base-url", json_base_url);
    json_object_set(json_configuration, "server", json_server);
    json_object_set(json_root, "configuration", json_configuration);

    conf_file = fopen(conf_file_path.s, "w");
    if (conf_file == NULL) {
        errnum = errno;
        json_decref(json_root);
        err_msg = string_createf("Cannot create configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    if (json_dumpf(json_root, conf_file, JSON_INDENT(4)) == -1) {
        errnum = errno;
        json_decref(json_root);
        err_msg = string_createf("Cannot write into configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    if (fclose(conf_file)) {
        errnum = errno;
        json_decref(json_root);
        err_msg = string_createf("Cannot close configuration file \"%s\"",
                conf_file_path.s);
        error_handle(IO_ERROR, errnum, err_msg.s);
    }

    json_decref(json_root);
}