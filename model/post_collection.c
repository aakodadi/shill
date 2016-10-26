#include <jansson.h>

#include "post.h"
#include "../error/error.h"
#include "post_collection.h"

void post_collection_initialize(post_collection *pc) {
    pc->len = -1L;
    pc->p = NULL;
}

void post_collection_destroy(post_collection *pc) {
    unsigned long i_post;

    if (pc->len != -1L) {
        for (i_post = 0; i_post < pc->len; i_post++) {
            post_destroy(&pc->p[i_post]);
        }
        free(pc->p);
    }
    pc->len = -1L;
    pc->p = NULL;
}

post_collection post_collection_deserialize(string pc_json) {
    string err_msg;
    post_collection result;
    unsigned long i_post;
    json_t *json_root, *json_post, *json_id, *json_body, *json_created_at,
            *json_updated_at;
    json_error_t error;

    json_root = json_loads(pc_json.s, 0, &error);

    if (!json_root) {
        err_msg = string_createf("Cannot parse json content \n\"%s\"."
                "\nError on line %d column %d : %s",
                pc_json.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_array(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\"."
                "\nExpected root element to be an array", pc_json.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    result.len = json_array_size(json_root);
    result.p = malloc(result.len * sizeof (post));

    for (i_post = 0; i_post < result.len; i_post++) {
        json_post = json_array_get(json_root, i_post);

        if (!json_is_object(json_post)) {
            json_decref(json_root);
            err_msg = string_createf("Cannot parse json content \n\"%s\"."
                    "\nExpected elements in root array to be objects",
                    pc_json.s);
            error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
        }

        json_id = json_object_get(json_post, "id");
        json_body = json_object_get(json_post, "body");
        json_created_at = json_object_get(json_post, "created_at");
        json_updated_at = json_object_get(json_post, "updated_at");

        if (json_is_integer(json_id)) {
            result.p[i_post].id = json_integer_value(json_id);
        }

        if (json_is_string(json_body)) {
            result.p[i_post].body = string_create(json_string_value(json_body));
        }

        if (json_is_integer(json_created_at)) {
            result.p[i_post].t.created_at = json_integer_value(json_created_at);
        }

        if (json_is_integer(json_updated_at)) {
            result.p[i_post].t.updated_at = json_integer_value(json_updated_at);
        }
    }

    json_decref(json_root);

    return result;
}