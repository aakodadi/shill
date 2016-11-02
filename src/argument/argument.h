/* argument.h: arguments parsing header.

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef ARGUMENT_H
#define ARGUMENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <config.h>
#include "system.h"
#include "progname.h"

#define ARGUMENT_BASE_URL -1
#define ARGUMENT_USAGE -2

  /* Program documentation. */
  static char doc[] =
          "\nInteract with people right form your terminal\n";

  /* A description of the arguments we accept. */
  static char args_doc[] = "<command>";

  static const struct option longopts[] = {
    {"config-file", required_argument, NULL, 'c'},
    {"username", required_argument, NULL, 'u'},
    {"base-url", required_argument, NULL, ARGUMENT_BASE_URL},
    {"help", no_argument, NULL, 'h'},
    {"usage", no_argument, NULL, ARGUMENT_USAGE},
    {"version", no_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}
  };

  /* Used by the main function to communicate with parse_opt. */
  struct _shill_arguments
  {
    char *config;
    char *commande;
    char *username;
    char *base_url;
  };

  typedef struct _shill_arguments shill_arguments;

  int argument_parse(int argc, char** argv);
  void argument_print_help();
  void argument_print_usage();
  void argument_print_version();


  shill_arguments arguments;


#ifdef __cplusplus
}
#endif

#endif /* ARGUMENT_H */
