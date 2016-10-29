/* 
 * File:   string_type.h
 * Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
 *
 * Created on September 15, 2016, 10:39 AM
 */

#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#define STRING_CHUNK_SIZE 1024

#ifdef __cplusplus
extern "C"
{
#endif

  struct _string
  {
    char* s;
    unsigned long len;
  };

  typedef struct _string string;

  string string_create (const char* source);
  string string_n_create (const char* source, unsigned long size);
  string string_createf (const char* source, ...);
  unsigned long string_destroy (string* s);
  string string_cat (string s1, string s2);
  string string_catd (string* s1, string* s2);
  string string_cpy (string source);
  string string_cpyd (string* source);
  int string_cmp (string s1, string s2);
  string string_from_unsigned_long (unsigned long n);
  string string_gets (unsigned long max_size);
  string string_getpass (unsigned long max_size);


#ifdef __cplusplus
}
#endif

#endif /* STRING_TYPE_H */

