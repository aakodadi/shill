/*
 * File:   post_collection_model_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Oct 26, 2016, 9:49:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../model/post_collection.h"

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

void
test_post_collection_initialize ()
{
  post_collection pc;
  post_collection_initialize (&pc);
  CU_ASSERT_EQUAL (pc.len, -1L);
  CU_ASSERT_PTR_NULL (pc.p);
}

void
test_post_collection_destroy ()
{
  post_collection pc;
  post_collection_initialize (&pc);
  post_collection_destroy (&pc);
  CU_ASSERT_EQUAL (pc.len, -1L);
  CU_ASSERT_PTR_NULL (pc.p);
}

void
test_post_collection_deserialize ()
{
  const char* source = "[{\"id\": 1, \"body\":\"test post 1\"},"
          "{\"id\": 2, \"body\":\"test post 2\"}]";
  string pc_json = string_create (source);
  post_collection result = post_collection_deserialize (pc_json);
  CU_ASSERT_EQUAL (result.len, 2);
  CU_ASSERT_PTR_NOT_NULL (result.p);
  CU_ASSERT_STRING_EQUAL (result.p[0].body.s, "test post 1");
  CU_ASSERT_EQUAL (result.p[0].id, 1);
  CU_ASSERT_STRING_EQUAL (result.p[1].body.s, "test post 2");
  CU_ASSERT_EQUAL (result.p[1].id, 2);
}

int
main ()
{
  CU_pSuite pSuite = NULL;

  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* Add a suite to the registry */
  pSuite = CU_add_suite ("post_collection_model_test", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Add the tests to the suite */
  if ((NULL == CU_add_test (pSuite, "test_post_collection_initialize", test_post_collection_initialize)) ||
      (NULL == CU_add_test (pSuite, "test_post_collection_destroy", test_post_collection_destroy)) ||
      (NULL == CU_add_test (pSuite, "test_post_collection_deserialize", test_post_collection_deserialize)))
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
