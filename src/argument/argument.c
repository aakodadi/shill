/*
   File:   argument.c
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
#include "argument.h"

int
argument_parse (int argc, char** argv)
{
  int optc;
  while ((optc = getopt_long (argc, argv, "c:u:htv", longopts, NULL)) != -1)
    {
      switch (optc)
        {
          /**
           * --help, --usage and --version exit immediately
           */
        case 'h':
          argument_print_help ();
          exit (EXIT_SUCCESS);
          break;
        case ARGUMENT_USAGE:
          argument_print_usage ();
          exit (EXIT_SUCCESS);
          break;
        case 'v':
          argument_print_version ();
          exit (EXIT_SUCCESS);
          break;
        case 'c':
          arguments.config = optarg;
          break;
        case 'u':
          arguments.username = optarg;
          break;
        case ARGUMENT_BASE_URL:
          arguments.base_url = optarg;
          break;
        default:
          break;
        }
    }

  if (optind + 1 == argc)
    {
      arguments.commande = argv[optind];
    }
  else if (optind == argc)
    {
      printf (_ ("%s: too few arguments: missing command argument\n"),
              program_name);
      argument_print_usage ();
      exit (EXIT_FAILURE);
    }
  else
    {
      printf (_ ("%s: too many arguments\n"),
              program_name);
      argument_print_usage ();
      exit (EXIT_FAILURE);
    }
}

void
argument_print_help ()
{
  /* TRANSLATORS: --help output 1 (synopsis)
     no-wrap */
  printf (_ ("\
Usage: %s [OPTION]... <COMMAND>\n"), program_name);

  /* TRANSLATORS: --help output 2 (brief description)
     no-wrap */
  fputs (_ ("\
Interact with people right form your terminal.\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output 3: options 1/2
     no-wrap */
  fputs (_ ("\
  -h, --help               display this help and exit\n\
      --usage              display a short usage message and exit\n\
  -v, --version            display version information and exit\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output 4: options 2/2
     no-wrap */
  fputs (_ ("\
  -c, --config-file=PATH    set configuration file \
(default ~/.shill_config.json)\n\
  -u, --username=USERNAME   set username for login\n\
      --base-url=URL        change base-url in configuration\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output 5: commands
     no-wrap */
  fputs (_ ("\
This is the list of all Shill commands.\n\
  register    create a new Shill account\n\
  login       login to a Shill account\n\
  feed        list posts queue\n\
  post        submit a new post\n\
  configure   perform modifications to Shill configuration\n"), stdout);

  printf ("\n");
  /* TRANSLATORS: --help output 6+ (reports)
     TRANSLATORS: the placeholder indicates the bug-reporting address
     for this application.  Please add _another line_ with the
     address for translation bugs.
     no-wrap */
  printf (_ ("\
Report bugs to: %s\n"), PACKAGE_BUGREPORT);
#ifdef PACKAGE_PACKAGER_BUG_REPORTS
  printf (_ ("Report %s bugs to: %s\n"), PACKAGE_PACKAGER,
          PACKAGE_PACKAGER_BUG_REPORTS);
#endif
#ifdef PACKAGE_URL
  printf (_ ("%s home page: <%s>\n"), PACKAGE_NAME, PACKAGE_URL);
#else
  printf (_ ("%s home page: <http://www.gnu.org/software/%s/>\n"),
          PACKAGE_NAME, PACKAGE);
#endif
  fputs (_ ("General help using GNU software: <http://www.gnu.org/gethelp/>\n"),
         stdout);
}

void
argument_print_usage ()
{
  /* TRANSLATORS: --usage output 1 (synopsis)
     no-wrap */
  printf (_ ("\
Usage: %s [-v] [-c FILE] [-u USERNAME] [--base-url=BASE-URL]\n\
          [--config=FILE] [--username=USERNAME] [--help] [--usage]\n\
          [--version] <COMMAND>\n"), program_name);

}

void
argument_print_version ()
{
  printf ("%s (%s) %s\n", PACKAGE, PACKAGE_NAME, VERSION);
  /* xgettext: no-wrap */
  puts ("");

  /* It is important to separate the year from the rest of the message,
     as done here, to avoid having to retranslate the message when a new
     year comes around.  */
  printf (_ ("\
  Copyright (C) %d Free Software Foundation, Inc.\n\
  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
  This is free software: you are free to change and redistribute it.\n\
  There is NO WARRANTY, to the extent permitted by law.\n"), COPYRIGHT_YEAR);
}
