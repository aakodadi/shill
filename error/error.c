#include "error.h"

#include <string.h>


const char* code_error_message = "\nCode error: Development error\n";
const char* memory_error_message = "\nMemory error: Error while trying to allocate memory\n";
const char* io_error_message = "\nIO error: Error while dealing with a file\n";

void error_handle(error e, int errnum, const char* info) {
    char* msg;
    switch (e) {
        case CODE_ERROR:
            msg = code_error_message;
            break;
        case MEMORY_ERROR:
            msg = memory_error_message;
            break;
        case IO_ERROR:
            msg = io_error_message;
            break;
        default:
            return;
    }
    fputs(msg, stderr);
    if (info == NULL && errnum == 0) {
        /* do nothing, no additional information for this error */
    } else if (info == NULL) {
        fprintf(stderr, "System message: %s\n", strerror(errnum));
    } else if (errnum == 0) {
        fprintf(stderr, "Involved object: %s\n", info);
    } else {
        fprintf(stderr, "Involved object: %s\nSystem message: %s\n", info, strerror(errnum));
    }
    exit(errnum);
}