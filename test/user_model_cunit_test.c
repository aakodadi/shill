/*
 * File:   user_model_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Oct 18, 2016, 6:05:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include <config.h>
#include <jansson.h>
#include "string_type.h"
#include "user.h"

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
  if(CU_get_number_of_failures () == 0)
    {
      return 0;
    }
  else
    {
      exit (EXIT_FAILURE);
    }
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
test_user_initialize ()
{
  user u;
  user_initialize (&u);

  CU_ASSERT_EQUAL (u.username.len, -1L);
  CU_ASSERT_PTR_NULL (u.username.s);
  CU_ASSERT_EQUAL (u.email.len, -1L);
  CU_ASSERT_PTR_NULL (u.email.s);
  CU_ASSERT_EQUAL (u.name.len, -1L);
  CU_ASSERT_PTR_NULL (u.name.s);
  CU_ASSERT_EQUAL (u.password.len, -1L);
  CU_ASSERT_PTR_NULL (u.password.s);
  CU_ASSERT_EQUAL (u.password_confirmation.len, -1L);
  CU_ASSERT_PTR_NULL (u.password_confirmation.s);
  CU_ASSERT_EQUAL (u.auth_token.len, -1L);
  CU_ASSERT_PTR_NULL (u.auth_token.s);
  CU_ASSERT_EQUAL (u.id, -1L);
  CU_ASSERT_EQUAL (u.t.created_at, 0);
  CU_ASSERT_EQUAL (u.t.updated_at, 0);
}

void
test_user_destroy ()
{
  user u;
  user_initialize (&u);

  u.username = string_create ("testuser");
  CU_ASSERT_STRING_EQUAL (u.username.s, "testuser");
  u.email = string_create ("testuser@example.com");
  CU_ASSERT_STRING_EQUAL (u.email.s, "testuser@example.com");
  u.name = string_create ("Test User");
  CU_ASSERT_STRING_EQUAL (u.name.s, "Test User");
  u.password = string_create ("password");
  CU_ASSERT_STRING_EQUAL (u.password.s, "password");
  u.password_confirmation = string_create ("password");
  CU_ASSERT_STRING_EQUAL (u.password_confirmation.s, "password");
  u.auth_token = string_create ("evrhOg037cZOJxAMFQM5dA");
  CU_ASSERT_STRING_EQUAL (u.auth_token.s, "evrhOg037cZOJxAMFQM5dA");

  user_destroy (&u);
  CU_ASSERT_EQUAL (u.username.len, -1L);
  CU_ASSERT_PTR_NULL (u.username.s);
  CU_ASSERT_EQUAL (u.email.len, -1L);
  CU_ASSERT_PTR_NULL (u.email.s);
  CU_ASSERT_EQUAL (u.name.len, -1L);
  CU_ASSERT_PTR_NULL (u.name.s);
  CU_ASSERT_EQUAL (u.password.len, -1L);
  CU_ASSERT_PTR_NULL (u.password.s);
  CU_ASSERT_EQUAL (u.password_confirmation.len, -1L);
  CU_ASSERT_PTR_NULL (u.password_confirmation.s);
  CU_ASSERT_EQUAL (u.auth_token.len, -1L);
  CU_ASSERT_PTR_NULL (u.auth_token.s);
  CU_ASSERT_EQUAL (u.id, -1L);
  CU_ASSERT_EQUAL (u.t.created_at, 0);
  CU_ASSERT_EQUAL (u.t.updated_at, 0);
}

void
test_user_deserialize ()
{
  const char* source = "{\"id\": 1547, \"username\":\"testuser\","
          "\"email\":\"testuser@email.com\", \"name\":\"Test user\","
          " \"password\": \"testpass\"}";
  string source_string = string_create (source);
  user result = user_deserialize (source_string);

  CU_ASSERT_STRING_EQUAL (result.username.s, "testuser");
  CU_ASSERT_STRING_EQUAL (result.email.s, "testuser@email.com");
  CU_ASSERT_STRING_EQUAL (result.name.s, "Test user");
  CU_ASSERT_STRING_EQUAL (result.password.s, "testpass");
  CU_ASSERT_EQUAL (result.id, 1547);
}

void
test_user_serialize ()
{
  const char* expected = "{\"user\":{\"username\":\"testuser\","
          "\"email\":\"testuser@email.com\",\"name\":\"Test user\","
          "\"password\":\"testpass\"}}";
  string expected_string = string_create (expected);
  user source;
  user_initialize (&source);
  source.username = string_create ("testuser");
  source.email = string_create ("testuser@email.com");
  source.name = string_create ("Test user");
  source.password = string_create ("testpass");
  string result = user_serialize (source);

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
  pSuite = CU_add_suite ("User Model CUnit Test", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Add the tests to the suite */
  if (
      (NULL == CU_add_test (pSuite, "test_user_initialize", test_user_initialize)) ||
      (NULL == CU_add_test (pSuite, "test_user_destroy", test_user_destroy)) ||
      (NULL == CU_add_test (pSuite, "test_user_serialize", test_user_serialize)) ||
      (NULL == CU_add_test (pSuite, "test_user_deserialize", test_user_deserialize))
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
