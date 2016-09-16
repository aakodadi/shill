/*
 * File:   repository_cunit_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Sep 15, 2016, 1:57:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../service/repository.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_repository_request() {
    const char* expected = "{\"id\":1,\"body\":\"test post body 2\",\"created_at\":\"2016-09-14T06:33:35.777Z\",\"updated_at\":\"2016-09-14T06:33:35.777Z\"}";
    target t = post_target;
    unsigned long id = 1;
    string result = repository_request(t, id);
    CU_ASSERT_STRING_EQUAL(result.s, expected);

}

void test_repository_request_collection() {
    const char* expected = "[{\"id\":1,\"body\":\"test post body 2\",\"created_at\":\"2016-09-14T06:33:35.777Z\",\"updated_at\":\"2016-09-14T06:33:35.777Z\"},{\"id\":2,\"body\":\"test post body 1\",\"created_at\":\"2016-09-14T06:34:03.876Z\",\"updated_at\":\"2016-09-14T06:34:03.876Z\"}]";
    collection_target t = posts_target;
    string result = repository_request_collection(t);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_request_posts() {
    const char* expected = "[{\"id\":1,\"body\":\"test post body 2\",\"created_at\":\"2016-09-14T06:33:35.777Z\",\"updated_at\":\"2016-09-14T06:33:35.777Z\"},{\"id\":2,\"body\":\"test post body 1\",\"created_at\":\"2016-09-14T06:34:03.876Z\",\"updated_at\":\"2016-09-14T06:34:03.876Z\"}]";
    string result = request_posts();
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_request_post() {
    const char* expected = "{\"id\":1,\"body\":\"test post body 2\",\"created_at\":\"2016-09-14T06:33:35.777Z\",\"updated_at\":\"2016-09-14T06:33:35.777Z\"}";
    unsigned long id = 1;
    string result = request_post(id);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("Repository CUnit Test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (
            (NULL == CU_add_test(pSuite, "test_repository_request", test_repository_request)) ||
            (NULL == CU_add_test(pSuite, "test_repository_request_collection", test_repository_request_collection)) ||
            (NULL == CU_add_test(pSuite, "test_request_post", test_request_post)) ||
            (NULL == CU_add_test(pSuite, "test_request_posts", test_request_posts))
            ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
