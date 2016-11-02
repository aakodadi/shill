/*
 * File:   repository_cunit_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Sep 15, 2016, 1:57:43 PM
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "repository.h"
#include "configuration.h"
#include "argument.h"
#include <jansson.h>

/*
 * CUnit Test Suite
 */

int
init_suite (void)
{
  arguments.config = "test/valid_config_without_user.json";
  configuration_parse ();
  return 0;
}

int
clean_suite (void)
{
  return 0;
}

string
_build_path_test_helper (target t, ...)
{
  string result;
  va_list vl;
  va_start (vl, t);
  result = _build_path (t, vl);
  va_end (vl);
  return result;
}

void
test_repository__build_post_path ()
{
  const char* expected = "posts/100";
  string result = _build_post_path (100);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_posts_path ()
{
  const char* expected = "posts/";
  string result = _build_posts_path ();
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_register_path ()
{
  const char* expected = "users/";
  string result = _build_register_path ();
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_login_path ()
{
  const char* expected = "auth/";
  string result = _build_login_path ();
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_logout_path ()
{
  const char* expected = "auth/";
  string result = _build_logout_path ();
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_path_posts ()
{
  const char* expected = "posts/";
  string result = _build_path_test_helper (TARGET_POSTS);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_path_post ()
{
  const char* expected = "posts/100";
  string result = _build_path_test_helper (TARGET_POST, 100);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_path_register ()
{
  const char* expected = "users/";
  string result = _build_path_test_helper (TARGET_REGISTER, 100);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_path_login ()
{
  const char* expected = "auth/";
  string result = _build_path_test_helper (TARGET_LOGIN, 100);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_path_logout ()
{
  const char* expected = "auth/";
  string result = _build_path_test_helper (TARGET_LOGOUT, 100);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__build_url ()
{
  const char* expected = "http://localhost:3000/profile/someone";
  configuration.base_url = string_create ("http://localhost:3000/");
  string path = string_create ("profile/someone");
  string result = _build_url (path);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
}

void
test_repository__get ()
{
  const char* expected = "This file is part of testing procedure it is used to test the repository by getting it form github";
  long http_code;
  string url = string_create ("https://raw.githubusercontent.com/akodakim/shill/master/tests/test_repository_sample_content");
  string result = _get (url, &http_code);
  CU_ASSERT_STRING_EQUAL (result.s, expected);
  CU_ASSERT_EQUAL (http_code, 200);
}

void
test_repository__post ()
{
  const char* expected = "simple post data";
  long http_code;
  json_t *json_root, *json_data;
  json_error_t error;
  string data = string_create (expected);
  string url = string_create ("http://httpbin.org/post");
  string result = _post (url, &http_code, data);
  json_root = json_loads (result.s, 0, &error);
  json_data = json_object_get (json_root, "data");
  CU_ASSERT (json_is_string (json_data));
  CU_ASSERT_STRING_EQUAL (json_string_value (json_data), expected);
  CU_ASSERT_EQUAL (http_code, 200);
}

void
test_repository__delete ()
{
  const char* expected = "simple post data";
  long http_code;
  json_t *json_root, *json_data;
  json_error_t error;
  string data = string_create (expected);
  string url = string_create ("http://httpbin.org/delete");
  string result = _delete (url, &http_code, data);
  json_root = json_loads (result.s, 0, &error);
  json_data = json_object_get (json_root, "data");
  CU_ASSERT (json_is_string (json_data));
  CU_ASSERT_STRING_EQUAL (json_string_value (json_data), expected);
  CU_ASSERT_EQUAL (http_code, 200);
}

int
main ()
{
  CU_pSuite pSuite = NULL;

  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* Add a suite to the registry */
  pSuite = CU_add_suite ("Repository CUnit Test", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Add the tests to the suite */
  if (
      (NULL == CU_add_test (pSuite, "test_repository__build_posts_path", test_repository__build_posts_path)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_post_path", test_repository__build_post_path)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_register_path", test_repository__build_register_path)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_login_path", test_repository__build_login_path)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_logout_path", test_repository__build_logout_path)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_path_posts", test_repository__build_path_posts)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_path_post", test_repository__build_path_post)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_path_register", test_repository__build_path_register)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_path_login", test_repository__build_path_login)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_path_logout", test_repository__build_path_logout)) ||
      (NULL == CU_add_test (pSuite, "test_repository__build_url", test_repository__build_url)) ||
      (NULL == CU_add_test (pSuite, "test_repository__get", test_repository__get)) ||
      (NULL == CU_add_test (pSuite, "test_repository__post", test_repository__post)) ||
      (NULL == CU_add_test (pSuite, "test_repository__delete", test_repository__delete)) ||
      (0)
      )
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode (CU_BRM_VERBOSE);
  CU_basic_run_tests ();
  CU_cleanup_registry ();
  return CU_get_error ();
}
