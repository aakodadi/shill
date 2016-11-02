#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include "argument/argument.h"
#include "configuration/configuration.h"
#include "command/command.h"

int
main (int argc, char** argv)
{
  /*
   * Default values.
   */
  arguments.verbose = 0;
  arguments.config = NULL;
  arguments.commande = NULL;
  arguments.username = NULL;
  arguments.base_url = NULL;

  /*
   * Parse our arguments; every option seen by parse_opt will be
   * reflected in arguments.
   */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
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
