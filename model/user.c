#include <jansson.h>

#include "user.h"
#include "../error/error.h"

void user_initialize(user *u) {
    u->id = -1L;
    u->username.len = -1L;
    u->email.len = -1L;
    u->name.len = -1L;
    u->password.len = -1L;
    u->password_confirmation.len = -1L;
    u->auth_token.len = -1L;
    u->t.created_at = 0;
    u->t.updated_at = 0;
}

void user_destroy(user *u) {
    u->id = -1L;

    if (u->username.len != -1L) {
        string_destroy(&u->username);
    }
    if (u->email.len != -1L) {
        string_destroy(&u->email);
    }
    if (u->name.len != -1L) {
        string_destroy(&u->name);
    }
    if (u->password.len != -1L) {
        string_destroy(&u->password);
    }
    if (u->password_confirmation.len != -1L) {
        string_destroy(&u->password_confirmation);
    }
    if (u->auth_token.len != -1L) {
        string_destroy(&u->auth_token);
    }

    u->t.created_at = 0;
    u->t.updated_at = 0;
}

user user_deserialize(string user_json) {
    user result;
    json_t *json_root, *json_id, *json_username, *json_email, *json_name,
            *json_password, *json_password_confirmation,
            *json_created_at, *json_updated_at, *json_auth_token;
    json_error_t error;
    string err_msg;

    json_root = json_loads(user_json.s, 0, &error);

    if (!json_root) {
        err_msg = string_createf("Cannot parse json content \n\"%s\".\nError on line %d column %d : %s",
                user_json.s,
                error.line,
                error.column,
                error.text);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }

    if (!json_is_object(json_root)) {
        json_decref(json_root);
        err_msg = string_createf("Cannot parse json content \n\"%s\".\n"
                "Root element is not a json object", user_json.s);
        error_handle(JSON_DECODE_ERROR, 0, err_msg.s);
    }


    json_id = json_object_get(json_root, "id");
    json_username = json_object_get(json_root, "username");
    json_email = json_object_get(json_root, "email");
    json_name = json_object_get(json_root, "name");
    json_password = json_object_get(json_root, "password");
    json_password_confirmation = json_object_get(json_root, "password_confirmation");
    json_created_at = json_object_get(json_root, "created_at");
    json_updated_at = json_object_get(json_root, "updated_at");
    json_auth_token = json_object_get(json_root, "auth_token");

    user_initialize(&result);
    if (json_is_string(json_id)) {
        sscanf(json_string_value(json_id), "%lu", &result.id);
    }

    if (json_is_string(json_username)) {
        result.username = string_create(json_string_value(json_username));
    }

    if (json_is_string(json_email)) {
        result.email = string_create(json_string_value(json_email));
    }

    if (json_is_string(json_name)) {
        result.name = string_create(json_string_value(json_name));
    }

    if (json_is_string(json_password)) {
        result.password = string_create(json_string_value(json_password));
    }

    if (json_is_string(json_password_confirmation)) {
        result.password_confirmation =
                string_create(json_string_value(json_password_confirmation));
    }

    if (json_is_integer(json_created_at)) {
        result.t.created_at = json_integer_value(json_created_at);
    }

    if (json_is_integer(json_updated_at)) {
        result.t.updated_at = json_integer_value(json_updated_at);
    }

    if (json_is_string(json_auth_token)) {
        result.auth_token = string_create(json_string_value(json_auth_token));
    }

    json_decref(json_root);

    return result;
}

string user_serialize(user u) {
    string result;

    json_t *json_root = NULL, *json_username = NULL, *json_email = NULL,
            *json_name = NULL, *json_password = NULL,
            *json_password_confirmation = NULL, *json_user = NULL;

    if (u.username.len != -1L) {
        json_username = json_pack("s", u.username.s);
    }
    if (u.email.len != -1L) {
        json_email = json_pack("s", u.email.s);
    }
    if (u.name.len != -1L) {
        json_name = json_pack("s", u.name.s);
    }
    if (u.password.len != -1L) {
        json_password = json_pack("s", u.password.s);
    }
    if (u.password_confirmation.len != -1L) {
        json_password_confirmation = json_pack("s", u.password_confirmation.s);
    }

    json_root = json_object();
    json_user = json_object();

    if (json_username != NULL) {
        json_object_set(json_user, "username", json_username);
    }
    if (json_email != NULL) {
        json_object_set(json_user, "email", json_email);
    }
    if (json_name != NULL) {
        json_object_set(json_user, "name", json_name);
    }
    if (json_password != NULL) {
        json_object_set(json_user, "password", json_password);
    }
    if (json_password_confirmation != NULL) {
        json_object_set(json_user, "password_confirmation",
                json_password_confirmation);
    }

    json_object_set(json_root, "user", json_user);

    result = string_create(json_dumps(json_root, JSON_COMPACT));

    json_decref(json_root);

    return result;
}