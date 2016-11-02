#include <config.h>
#include"argument.h"

error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /*
   * Get the input argument from argp_parse, which we
   * know is a pointer to our arguments structure.
   */
  shill_arguments *arguments = state->input;
  switch (key)
    {
    case ARGP_KEY_INIT:
      break;
    case 'v':
      arguments->verbose++;
      break;
    case 'c':
      arguments->config = arg;
      break;
    case 'u':
      arguments->username = arg;
      break;
    case -1:
      arguments->base_url = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num == 0)
        {
          arguments->commande = arg;
        }
      else
        {
          return ARGP_ERR_UNKNOWN;
        }
      break;
    case ARGP_KEY_NO_ARGS:
      argp_error (state, "Too few arguments");
      break;
    case ARGP_KEY_END:
      break;
    case ARGP_KEY_SUCCESS:
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
const char *argp_program_version = PACKAGE " (" PACKAGE_NAME ") " VERSION;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;
