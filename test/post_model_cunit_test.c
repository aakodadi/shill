/*
 * File:   post_model_cunit_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Oct 26, 2016, 12:57:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <jansson.h>
#include "../src/model/post.h"

/*
 * CUnit Test Suite
 */

int
init_suite (void)
{
  return 0;
}

int
clean_suite (void)
{
  return 0;
}

int
_json_compare (string s1, string s2)
{
  json_t *json_root1, *json_root2;
  json_error_t error;

  json_root1 = json_loads (s1.s, 0, &error);
  json_root2 = json_loads (s2.s, 0, &error);
  return json_equal (json_root1, json_root2);
}

void
test_post_initialize ()
{
  post p;
  post_initialize (&p);
  CU_ASSERT_EQUAL (p.body.len, -1L);
  CU_ASSERT_PTR_NULL (p.body.s);
  CU_ASSERT_EQUAL (p.id, -1L);
  CU_ASSERT_EQUAL (p.t.created_at, 0);
  CU_ASSERT_EQUAL (p.t.updated_at, 0);
}

void
test_post_destroy ()
{
  post p;
  post_initialize (&p);
  p.body = string_create ("This is a test post");
  CU_ASSERT_STRING_EQUAL (p.body.s, "This is a test post");
  post_destroy (&p);
  CU_ASSERT_EQUAL (p.body.len, -1L);
  CU_ASSERT_EQUAL (p.id, -1L);
  CU_ASSERT_EQUAL (p.t.created_at, 0);
  CU_ASSERT_EQUAL (p.t.updated_at, 0);
  CU_ASSERT_PTR_NULL (p.body.s);
}

void
test_post_deserialize ()
{
  const char* source = "{\"id\": 1547, \"body\":\"test post\"}";
  string post_json = string_create (source);
  post result = post_deserialize (post_json);
  CU_ASSERT_STRING_EQUAL (result.body.s, "test post");
  CU_ASSERT_EQUAL (result.id, 1547);
}

void
test_post_serialize ()
{
  const char* expected = "{\"post\":{\"body\":\"test post\"}}";
  string expected_string = string_create (expected);
  post p;
  post_initialize (&p);
  p.body = string_create ("test post");
  string result = post_serialize (p);
  CU_ASSERT (_json_compare (result, expected_string));
}

int
main ()
{
  CU_pSuite pSuite = NULL;

  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* Add a suite to the registry */
  pSuite = CU_add_suite ("post_model_cunit_test", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Add the tests to the suite */
  if ((NULL == CU_add_test (pSuite, "test_post_initialize", test_post_initialize)) ||
      (NULL == CU_add_test (pSuite, "test_post_destroy", test_post_destroy)) ||
      (NULL == CU_add_test (pSuite, "test_post_deserialize", test_post_deserialize)) ||
      (NULL == CU_add_test (pSuite, "test_post_serialize", test_post_serialize)))
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
