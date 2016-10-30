ACLOCAL_AMFLAGS = -I m4 --install

MODULES_SOURCES = \
  src/argument/argument.c \
  src/argument/argument.h \
  src/command/command.c \
  src/command/command.h \
  src/configuration/configuration.c \
  src/configuration/configuration.h \
  src/service/service.c \
  src/service/service.h \
  src/service/repository.c \
  src/service/repository.h \
  src/error/error.c \
  src/error/error.h \
  src/type/string.c \
  src/type/string.h \
  src/model/timestamp.h \
  src/model/user.c \
  src/model/user.h \
  src/model/post.c \
  src/model/post.h \
  src/model/post_collection.c \
  src/model/post_collection.h


bin_PROGRAMS = shill
shill_SOURCES = \
  src/main.c \
  $(MODULES_SOURCES)

shill_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@

shill_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@

TESTS = \
  string_type_cunit_test \
  configuration_cunit_test \
  repository_cunit_test \
  post_model_cunit_test \
  user_model_cunit_test \
  post_collection_model_cunit_test

check_PROGRAMS = \
  $(TESTS)

string_type_cunit_test_SOURCES = \
  test/string_type_cunit_test.c \
  $(MODULES_SOURCES)

configuration_cunit_test_SOURCES = \
  test/configuration_cunit_test.c \
  $(MODULES_SOURCES)

repository_cunit_test_SOURCES = \
  test/repository_cunit_test.c \
  $(MODULES_SOURCES)

user_model_cunit_test_SOURCES = \
  test/user_model_cunit_test.c \
  $(MODULES_SOURCES)

post_model_cunit_test_SOURCES = \
  test/post_model_cunit_test.c \
  $(MODULES_SOURCES)

post_collection_model_cunit_test_SOURCES = \
  test/post_collection_model_cunit_test.c \
  $(MODULES_SOURCES)

string_type_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
configuration_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
repository_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
post_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
user_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
post_collection_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@

string_type_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
configuration_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
repository_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
post_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
user_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
post_collection_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@

EXTRA_DIST = m4/NOTES
