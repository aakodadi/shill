/*
 * File:   string_type_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Sep 15, 2016, 11:09:44 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../type/string.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_string_create() {
    const char* source = "test string";
    string result = string_create(source);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, source);
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_createf() {
    string result = string_createf("test %s %d", "string", 1);
    CU_ASSERT_EQUAL(result.len, 13);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen(result.s), 13);
    CU_ASSERT_STRING_EQUAL(result.s, "test string 1");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_create_with_empty_source() {
    const char* source = "";
    string result = string_create(source);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, source);
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_create_with_null_source() {
    const char* source = NULL;
    string result = string_create(source);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, "");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_n_create() {
    char* source;
    unsigned long size = 10;
    source = malloc(20);
    strncpy(source, "test string", 12);
    source[11] = 'a';
    source[12] = 'a';
    string result = string_n_create(source, size);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen(result.s), size);
    CU_ASSERT_EQUAL(result.len, size);
    CU_ASSERT_STRING_EQUAL(result.s, "test strin");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_destroy() {
    string s = string_create("test string");
    unsigned long result = string_destroy(&s);
    CU_ASSERT_EQUAL(result, 11);
    CU_ASSERT_EQUAL(s.len, 0);
    CU_ASSERT_PTR_NULL(s.s);
}

void test_string_destroy_empty() {
    string s = string_create("");
    unsigned long result = string_destroy(&s);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_EQUAL(s.len, 0);
    CU_ASSERT_PTR_NULL(s.s);
}

void test_string_cat() {
    string s1 = string_create("test string 1");
    string s2 = string_create("test string 2");
    string result = string_cat(s1, s2);
    CU_ASSERT_EQUAL(result.len, s1.len + s2.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen(s1.s) + strlen(s2.s), result.len);
    CU_ASSERT_EQUAL(strlen(s1.s) + strlen(s2.s), strlen(result.s));
    CU_ASSERT_STRING_EQUAL(result.s, "test string 1test string 2");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_cat_with_s1_empty() {
    string s1 = string_create("");
    string s2 = string_create("test string 2");
    string result = string_cat(s1, s2);
    CU_ASSERT_EQUAL(result.len, s1.len + s2.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, "test string 2");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_cat_with_s2_empty() {
    string s1 = string_create("test string 1");
    string s2 = string_create("");
    string result = string_cat(s1, s2);
    CU_ASSERT_EQUAL(result.len, s1.len + s2.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, "test string 1");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_cat_form_empty_sources() {
    string s1 = string_create("");
    string s2 = string_create("");
    string result = string_cat(s1, s2);
    CU_ASSERT_EQUAL(result.len, s1.len + s2.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, "");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_catd() {
    string s1 = string_create("test string 1");
    string s2 = string_create("test string 2");
    unsigned long s1_len = s1.len;
    unsigned long s2_len = s2.len;
    string result = string_catd(&s1, &s2);
    CU_ASSERT_EQUAL(result.len, s1_len + s2_len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_STRING_EQUAL(result.s, "test string 1test string 2");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
    /*
     * test if s1 and s2 was destroyed
     */
    CU_ASSERT_EQUAL(s1.len, 0);
    CU_ASSERT_EQUAL(s2.len, 0);
    CU_ASSERT_PTR_NULL(s2.s);
    CU_ASSERT_PTR_NULL(s2.s);
}

void test_string_cpy() {
    string source = string_create("test string");
    string result = string_cpy(source);
    CU_ASSERT_EQUAL(result.len, source.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen(source.s), result.len);
    CU_ASSERT_EQUAL(strlen(result.s), strlen(source.s));
    CU_ASSERT_STRING_EQUAL(result.s, source.s);
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_cpy_from_empty_source() {
    string source = string_create("");
    string result = string_cpy(source);
    CU_ASSERT_EQUAL(result.len, source.len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen(source.s), result.len);
    CU_ASSERT_EQUAL(strlen(result.s), strlen(source.s));
    CU_ASSERT_STRING_EQUAL(result.s, source.s);
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

void test_string_cpyd() {
    string source = string_create("test string");
    unsigned long source_len = source.len;
    string result = string_cpyd(&source);
    CU_ASSERT_EQUAL(result.len, source_len);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(strlen("test string"), result.len);
    CU_ASSERT_EQUAL(strlen(result.s), strlen("test string"));
    CU_ASSERT_STRING_EQUAL(result.s, "test string");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
    /*
     * test if source was destroyed
     */
    CU_ASSERT_EQUAL(source.len, 0);
    CU_ASSERT_PTR_NULL(source.s);
}

void test_string_cmp() {
    string s1 = string_create("test string 1");
    string s2 = string_create("test string 2");
    int result = string_cmp(s1, s2);
    CU_ASSERT_TRUE(result < 0);
}

void test_string_from_unsigned_long() {
    unsigned long n = 100;
    string result = string_from_unsigned_long(n);
    CU_ASSERT_EQUAL(strlen(result.s), result.len);
    CU_ASSERT_EQUAL(result.len, 3);
    CU_ASSERT_EQUAL(strlen(result.s), 3);
    CU_ASSERT_STRING_EQUAL(result.s, "100");
    CU_ASSERT_EQUAL(result.s[result.len], '\0');
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("String Type CUnit Test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_string_create", test_string_create)) ||
            (NULL == CU_add_test(pSuite, "test_string_createf", test_string_createf)) ||
            (NULL == CU_add_test(pSuite, "test_string_create_with_empty_source", test_string_create_with_empty_source)) ||
            (NULL == CU_add_test(pSuite, "test_string_destroy", test_string_destroy)) ||
            (NULL == CU_add_test(pSuite, "test_string_n_create", test_string_n_create)) ||
            (NULL == CU_add_test(pSuite, "test_string_destroy_empty", test_string_destroy_empty)) ||
            (NULL == CU_add_test(pSuite, "test_string_cat", test_string_cat)) ||
            (NULL == CU_add_test(pSuite, "test_string_cat_with_s1_empty", test_string_cat_with_s1_empty)) ||
            (NULL == CU_add_test(pSuite, "test_string_cat_with_s2_empty", test_string_cat_with_s2_empty)) ||
            (NULL == CU_add_test(pSuite, "test_string_cat_form_empty_sources", test_string_cat_form_empty_sources)) ||
            (NULL == CU_add_test(pSuite, "test_string_catd", test_string_catd)) ||
            (NULL == CU_add_test(pSuite, "test_string_cpy", test_string_cpy)) ||
            (NULL == CU_add_test(pSuite, "test_string_cpy_from_empty_source", test_string_cpy_from_empty_source)) ||
            (NULL == CU_add_test(pSuite, "test_string_cpyd", test_string_cpyd)) ||
            (NULL == CU_add_test(pSuite, "test_string_cmp", test_string_cmp)) ||
            (NULL == CU_add_test(pSuite, "test_string_from_unsigned_long", test_string_from_unsigned_long))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
