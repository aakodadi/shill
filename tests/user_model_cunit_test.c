/*
 * File:   user_model_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Oct 18, 2016, 6:05:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include <jansson.h>
#include "../type/string.h"
#include "../model/user.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int _json_compare(string s1, string s2){
    json_t *json_root1, *json_root2;
    json_error_t error;

    json_root1 = json_loads(s1.s, 0, &error);
    json_root2 = json_loads(s2.s, 0, &error);
    return json_equal(json_root1, json_root2);
}

void test_user_deserialize() {
    const char* source = "{\"id\": 1547, \"username\":\"testuser\","
    "\"email\":\"testuser@email.com\", \"name\":\"Test user\","
    " \"password\": \"testpass\"}";
    string source_string = string_create(source);
    user result = user_deserialize(source_string);
    
    CU_ASSERT_STRING_EQUAL(result.username.s, "testuser");
    CU_ASSERT_STRING_EQUAL(result.email.s, "testuser@email.com");
    CU_ASSERT_STRING_EQUAL(result.name.s, "Test user");
    CU_ASSERT_STRING_EQUAL(result.password.s, "testpass");
    CU_ASSERT_EQUAL(result.id, 1547);
}

void test_user_serialize() {
    const char* expected = "{\"user\":{\"username\":\"testuser\","
    "\"email\":\"testuser@email.com\",\"name\":\"Test user\","
    "\"password\":\"testpass\"}}";
    string expected_string = string_create(expected);
    user source;
    user_initialize(&source);
    source.username = string_create("testuser");
    source.email = string_create("testuser@email.com");
    source.name = string_create("Test user");
    source.password = string_create("testpass");
    string result = user_serialize(source);
    
    CU_ASSERT(_json_compare(result, expected_string));
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("User Model CUnit Test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_user_serialize", test_user_serialize)) ||
            (NULL == CU_add_test(pSuite, "test_user_deserialize", test_user_deserialize))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
