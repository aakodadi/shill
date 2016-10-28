#include "error.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


const char* code_error_message = "\nCode error: This error must never be thrown in production, if it's the case please contact the developer\n";
const char* memory_error_message = "\nMemory error: Error while trying to allocate memory\n";
const char* io_error_message = "\nIO error: Error while interacting with a file\n";
const char* json_decode_error_message = "\nJson decode error: Error while parsing json\n";
const char* server_error_message = "\nServer error: Error while requesting a server\n";

void error_handle(error e, int errnum, const char* info) {
    const char* msg;
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
        case JSON_DECODE_ERROR:
            msg = json_decode_error_message;
            break;
        case SERVER_ERROR:
            msg = server_error_message;
            break;
        default:
            error_handle(CODE_ERROR, 0, "Unexpected error type in error handling module, in error/error.c, error_handler(), this code block must never get executed");
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