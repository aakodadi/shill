#include"argument.h"

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    /*
     * Get the input argument from argp_parse, which we
     * know is a pointer to our arguments structure.
     */
    struct arguments *arguments = state->input;
    switch (key)
    {
    case 'v':
        arguments->verbose++;
        break;
    case 'c':
        arguments->config = arg;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
const char *argp_program_version =
        "shill 1.0, Build, "__DATE__;
const char *argp_program_bug_address =
        "<akodadi.abdelhakim@gmail.com>";