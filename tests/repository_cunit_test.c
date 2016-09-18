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

string _build_path_test_helper(target t, ...) {
    string result;
    va_list vl;
    va_start(vl, t);
    result = _build_path(t, vl);
    va_end(vl);
    return result;
}



void test_repository__build_post_path() {
    const char* expected = "posts/100";
    string result = _build_post_path(100);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_repository__build_posts_path() {
    const char* expected = "posts/";
    string result = _build_posts_path();
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_repository__build_path_posts() {
    const char* expected = "posts/";
    string result = _build_path_test_helper(TARGET_POSTS);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_repository__build_path_post() {
    const char* expected = "posts/100";
    string result = _build_path_test_helper(TARGET_POST, 100);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_repository__build_url() {
    const char* expected = "http://localhost:3000/profile/someone";
    string path = string_create("profile/someone");
    string result = _build_url(path);
    CU_ASSERT_STRING_EQUAL(result.s, expected);
}

void test_repository__request() {
    const char* expected = "This file is part of testing procedure it is used to test the repository by getting it form github";
    string url = string_create("https://raw.githubusercontent.com/akodakim/shill/master/tests/test_repository_sample_content");
    string result = _request(url);
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
            (NULL == CU_add_test(pSuite, "test_repository__build_posts_path", test_repository__build_posts_path)) ||
            (NULL == CU_add_test(pSuite, "test_repository__build_post_path", test_repository__build_post_path)) ||
            (NULL == CU_add_test(pSuite, "test_repository__build_path_posts", test_repository__build_path_posts)) ||
            (NULL == CU_add_test(pSuite, "test_repository__build_path_post", test_repository__build_path_post)) ||
            (NULL == CU_add_test(pSuite, "test_repository__build_url", test_repository__build_url)) ||
            (NULL == CU_add_test(pSuite, "test_repository__request", test_repository__request)) ||
            (0)
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
