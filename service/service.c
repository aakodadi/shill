#include <jansson.h>
#include <time.h>
#include "repository.h"
#include "../error/error.h"

#include "service.h"

post_collection get_posts() {
    string err_msg;
    string row_result;
    post_collection result;
    unsigned long post_i;
    json_t *json_root, *json_post, *json_id, *json_body, *json_created_at, *json_updated_at;
    json_error_t error;
    row_result = repository_get(TARGET_POSTS);

    json_root = json_loads(row_result.s, 0, &error);

    if (!json_root) {
        err_msg = string_createf("Cannot parse json content \n\"%s\".\nError on line %d column %d : %s",
                row_result.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_array(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\nRoot element is not a json array", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    result.len = json_array_size(json_root);
    result.p = malloc(result.len * sizeof (post));
    for (post_i = 0; post_i < result.len; post_i++) {
        json_post = json_array_get(json_root, post_i);

        if (!json_is_object(json_post)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\".\nElements in root array are not json objects", row_result.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        json_id = json_object_get(json_post, "id");
        json_body = json_object_get(json_post, "body");
        json_created_at = json_object_get(json_post, "created_at");
        json_updated_at = json_object_get(json_post, "updated_at");

        if (!json_is_integer(json_id)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\".\n id element is not a integer", row_result.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        if (!json_is_string(json_body)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\".\n body element is not a string", row_result.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        if (!json_is_integer(json_created_at)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\".\n created_at element is not a integer", row_result.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        if (!json_is_integer(json_updated_at)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\".\n updated_at element is not a integer", row_result.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        result.p[post_i].id = json_integer_value(json_id);
        result.p[post_i].body = string_create(json_string_value(json_body));
        result.p[post_i].t.created_at = json_integer_value(json_created_at);
        result.p[post_i].t.updated_at = json_integer_value(json_updated_at);
    }

    string_destroy(&row_result);
    json_decref(json_root);

    return result;

}

post get_post(unsigned long id) {
    string err_msg;
    string row_result;
    post result;
    json_t *json_root, *json_id, *json_body, *json_created_at, *json_updated_at;
    json_error_t error;
    row_result = repository_get(TARGET_POST, id);

    json_root = json_loads(row_result.s, 0, &error);

    if (!json_root) {
        err_msg = string_createf("Cannot parse json content \n\"%s\".\nError on line %d column %d : %s",
                row_result.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\nRoot element is not a json object", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    json_id = json_object_get(json_root, "id");
    json_body = json_object_get(json_root, "body");
    json_created_at = json_object_get(json_root, "created_at");
    json_updated_at = json_object_get(json_root, "updated_at");

    if (!json_is_integer(json_id)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n id element is not a integer", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_string(json_body)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n body element is not a string", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_integer(json_created_at)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n created_at element is not a integer", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_integer(json_updated_at)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n updated_at element is not a integer", row_result.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    string_destroy(&row_result);
    json_decref(json_root);

    result.id = json_integer_value(json_id);
    result.body = string_create(json_string_value(json_body));
    result.t.created_at = json_integer_value(json_created_at);
    result.t.updated_at = json_integer_value(json_updated_at);

    return result;
}