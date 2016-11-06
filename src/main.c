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

  set_program_name (argv[0]);

  /*
   * Default values.
   */
  arguments.config = NULL;
  arguments.commande = NULL;
  arguments.username = NULL;
  arguments.base_url = NULL;

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
      printf ("Unable to retrieve configuration.\n");
      printf ("Trying to create a new one...\n");
      configuration_create ();
      configuration_parse ();
    }

  commande_execute ();

  return (EXIT_SUCCESS);
}
