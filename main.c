#include <stdio.h>
#include <stdlib.h>
#include "argument/argument.h"
#include "configuration/configuration.h"
#include "command/command.h"

int main(int argc, char** argv) {
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
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    
    printf("command: %s\n", arguments.commande);
    
    configuration_parse();
    
    printf("base-url: %s\n\n", arguments.base_url);

    commande_execute();

    return (EXIT_SUCCESS);
}

