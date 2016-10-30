# Autoconf requirements
# Initialize, and use more options.
AC_INIT([shill], [0.0.1], [akodadi.abdelhakim@gmail.com])

# Force autoconf to be at least this version number.
AC_PREREQ([2.68])

# Safety check - list a source file that wouldn't be in other directories.
AC_CONFIG_SRCDIR([src/main.c])

# Put configuration results here, so we can easily #include them
AC_CONFIG_HEADERS([src/config.h])

# Put autotools auxiliary files in a subdir, so they don't clutter top dir.
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Enable "automake" to simplify creating makefiles.
AM_INIT_AUTOMAKE([1.11 subdir-objects -Wall -Werror])
AC_CONFIG_FILES([Makefile])

# Look for a C compiler
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([JANSSON], [jansson])
PKG_CHECK_MODULES([CUNIT], [cunit])

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

AC_OUTPUT
