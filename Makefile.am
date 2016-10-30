ACLOCAL_AMFLAGS = -I m4 --install

bin_PROGRAMS = shill
shill_SOURCES = \
  src/main.c \
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

shill_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@

shill_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@

EXTRA_DIST = m4/NOTES
