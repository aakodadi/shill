#include <jansson.h>

#include "post.h"
#include "../error/error.h"

void post_initialize(post *p) {
    p->id = -1L;
    p->body.len = -1L;
    p->t.created_at = 0;
    p->t.updated_at = 0;
}

void post_destroy(post *p) {
    p->id = -1L;

    if (p->body.len != -1L) {
        string_destroy(&p->body);
    }

    p->t.created_at = 0;
    p->t.updated_at = 0;
}

post post_deserialize(string post_json) {
    post result;
    json_t *json_root, *json_id, *json_body, *json_created_at, *json_updated_at;
    json_error_t error;
    string err_msg;

    json_root = json_loads(post_json.s, 0, &error);

    if (!json_root) {
        err_msg = string_createf("Cannot parse json content \n\"%s\"."
                "\nError on line %d column %d : %s",
                post_json.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n"
                "Root element is not a json object", post_json.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }


    json_id = json_object_get(json_root, "id");
    json_body = json_object_get(json_root, "body");
    json_created_at = json_object_get(json_root, "created_at");
    json_updated_at = json_object_get(json_root, "updated_at");

    post_initialize(&result);
    if (json_is_integer(json_id)) {
        result.id = (unsigned long) json_integer_value(json_id);
    }

    if (json_is_string(json_body)) {
        result.body = string_create(json_string_value(json_body));
    }

    if (json_is_integer(json_created_at)) {
        result.t.created_at = json_integer_value(json_created_at);
    }

    if (json_is_integer(json_updated_at)) {
        result.t.updated_at = json_integer_value(json_updated_at);
    }

    json_decref(json_root);

    return result;
}

string post_serialize(post p) {
    string result;

    json_t *json_root = NULL, *json_body = NULL, *json_post = NULL;

    if (p.body.len != -1L) {
        json_body = json_pack("s", p.body.s);
    }

    json_root = json_object();
    json_post = json_object();

    if (json_body != NULL) {
        json_object_set(json_post, "body", json_body);
    }

    json_object_set(json_root, "post", json_post);

    result = string_create(json_dumps(json_root, JSON_COMPACT));

    json_decref(json_root);

    return result;
}