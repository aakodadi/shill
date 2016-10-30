/*
 * File:   configuration_cunit_test.c
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on Sep 18, 2016, 10:07:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/configuration/configuration.h"
#include "../src/argument/argument.h"

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
test_configuration_parse_with_valid_file ()
{
  arguments.config = "test/valid_config.json";
  configuration_parse ();
  CU_ASSERT_STRING_EQUAL (configuration.base_url.s,
                          "http://test.valid.com:3000/");
  CU_ASSERT_STRING_EQUAL (configuration.u.username.s,
                          "testusername");
  CU_ASSERT_STRING_EQUAL (configuration.u.auth_token.s,
                          "YjfTVTJvovLGq1Knix5");
}

void
test_configuration_parse_with_valid_file_without_user ()
{
  arguments.config = "test/valid_config_without_user.json";
  configuration_parse ();
  CU_ASSERT_STRING_EQUAL (configuration.base_url.s,
                          "http://test.valid.com:3000/");
  CU_ASSERT_EQUAL (configuration.u.username.len, -1L);
  CU_ASSERT_EQUAL (configuration.u.auth_token.len, -1L);
}

int
main ()
{
  CU_pSuite pSuite = NULL;

  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* Add a suite to the registry */
  pSuite = CU_add_suite ("Configuration Cunit Test", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Add the tests to the suite */
  if (
      (NULL == CU_add_test (pSuite, "test_configuration_parse_with_valid_file", test_configuration_parse_with_valid_file)) ||
      (NULL == CU_add_test (pSuite, "test_configuration_parse_with_valid_file_without_user", test_configuration_parse_with_valid_file_without_user)) ||
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
