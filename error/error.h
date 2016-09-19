/* 
 * File:   error.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 * Brief: Errors handler
 *
 * Created on September 18, 2016, 2:09 PM
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * errors enumeration
     */
    enum _error {
        CODE_ERROR,
        MEMORY_ERROR,
        IO_ERROR,
        JSON_DECODE_ERROR,
        SERVER_ERROR
    };
    
    const char* code_error_message;
    const char* memory_error_message;
    const char* io_error_message;
    const char* json_decode_error_message;
    const char* server_error_message;

    typedef enum _error error;

    /*
     * error handler
     * @param e: error type
     * @param errnum: if system error it takes errno value, if not 0
     * @param info: additional information about the error, if none set to NULL
     */
    void error_handle(error e, int errnum, const char* info);


#ifdef __cplusplus
}
#endif

#endif /* ERROR_H */

