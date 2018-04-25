/*
   File:   main.c
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014, 2018 Free
   Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "progname.h"
#include "argument.h"
#include "configuration.h"
#include "command.h"

int
main (int argc, char** argv)
{

  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  set_program_name (argv[0]);

  /*
   * Default values.
   */
  arguments.config = NULL;
  arguments.commande = NULL;
  arguments.username = NULL;
  arguments.base_url = NULL;


  /* If any writes failed, change the exit status.
     This is implemented in the Gnulib module "closeout".  */
  atexit (close_stdout);

  /*
   * Parse our arguments; every option seen by argument_parse will be
   * reflected in arguments.
   */
  argument_parse (argc, argv);
  configuration_initialize ();
  configuration_parse ();

  /*
   * Check if we successfully parsed the configuration
   * If not, create a new configuration and retry again
   */
  if (configuration.base_url.s == NULL)
    {
      printf (_ ("Unable to retrieve configuration.\n"));
      printf (_ ("Trying to create a new one...\n"));
      configuration_create ();
      configuration_parse ();
    }

  commande_execute ();

  return (EXIT_SUCCESS);
}
