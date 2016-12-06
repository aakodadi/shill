#include "string_type.h"

string
string_create (const char* source)
{
  unsigned long len;
  string destination;
  if (source == NULL)
    {
      len = 0;
      destination.len = 0;
      destination.s = malloc (1);
      destination.s[0] = '\0';
      return destination;
    }
  len = strlen (source);
  destination.len = len;
  destination.s = malloc (len + 1);
  if (destination.s == NULL)
    {
      error (EXIT_FAILURE, errno, _ ("unable to allocate memory for a string"));
    }
  strncpy (destination.s, source, len + 1);
  destination.s[destination.len] = '\0';
  return destination;
}

string
string_createf (const char* source, ...)
{
  unsigned long len;
  string destination;
  va_list vl;
  va_start (vl, source);
  len = vsnprintf (NULL, 0, source, vl);
  va_end (vl);
  destination.s = malloc (len + 1);
  if (destination.s == NULL)
    {
      error (EXIT_FAILURE, errno, _ ("unable to allocate memory for a string"));
    }
  va_start (vl, source);
  vsnprintf (destination.s, len + 1, source, vl);
  va_end (vl);
  destination.len = len;
  return destination;
}

string
string_n_create (const char* source, unsigned long size)
{
  string destination;
  if (source == NULL)
    {
      destination.len = 0;
      destination.s = malloc (1);
      strncpy (destination.s, "", 1);
      return destination;
    }
  destination.len = size;
  destination.s = malloc (size + 1);
  if (destination.s == NULL)
    {
      error (EXIT_FAILURE, errno, _ ("unable to allocate memory for a string"));
    }
  strncpy (destination.s, source, size + 1);
  destination.s[destination.len] = '\0';
  return destination;
}

unsigned long
string_destroy (string* s)
{
  unsigned long len;
  len = s->len;
  s->len = -1L;
  free (s->s);
  s->s = NULL;
  return len;
}

string
string_cat (string s1, string s2)
{
  string destination;
  destination.len = s1.len + s2.len;
  destination.s = malloc (destination.len + 1);
  if (destination.s == NULL)
    {
      error (EXIT_FAILURE, errno, _ ("unable to allocate memory for a string"));
    }
  strncpy (destination.s, s1.s, s1.len + 1);
  strncat (destination.s, s2.s, s2.len + 1);
  return destination;
}

string
string_catd (string* s1, string* s2)
{
  string destination = string_cat (*s1, *s2);
  string_destroy (s1);
  string_destroy (s2);
  return destination;
}

string
string_cpy (string source)
{
  string destination;
  destination = string_create (source.s);
  return destination;
}

string
string_cpyd (string* source)
{
  string destination = string_cpy (*source);
  string_destroy (source);
  return destination;
}

int
string_cmp (string s1, string s2)
{
  return strcmp (s1.s, s2.s);
}

string
string_from_unsigned_long (unsigned long n)
{
  unsigned long len = snprintf (NULL, 0, "%lu", n);
  string destination;
  destination.s = malloc (len + 1);
  if (destination.s == NULL)
    {
      error (EXIT_FAILURE, errno, _ ("unable to allocate memory for a string"));
    }
  snprintf (destination.s, len + 1, "%lu", n);
  destination.len = len;
  return destination;
}

string
string_gets (unsigned long max_size)
{
  string destination = string_create ("");
  char c[STRING_CHUNK_SIZE];
  string tmp;
  unsigned long size = STRING_CHUNK_SIZE < max_size ?
          STRING_CHUNK_SIZE : max_size;
  while (fgets (c, size, stdin))
    {
      if (c[strlen (c) - 1] == '\n')
        {
          c[strlen (c) - 1] = '\0';
          tmp = string_create (c);
          destination = string_catd (&destination, &tmp);
          return destination;
        }
      tmp = string_create (c);
      destination = string_catd (&destination, &tmp);
      printf ("%s\n", destination.s);
      max_size -= destination.len;
      if (max_size == 0)
        {
          return destination;
        }
      size = STRING_CHUNK_SIZE < max_size ?
              STRING_CHUNK_SIZE : max_size;
    }
  return destination;
}

string
string_getpass (unsigned long max_size)
{
  struct termios old, new;
  string destination = string_create ("");
  char c[STRING_CHUNK_SIZE];
  string tmp;
  unsigned long size = STRING_CHUNK_SIZE < max_size ?
          STRING_CHUNK_SIZE : max_size;
  if (tcgetattr (STDIN_FILENO, &old) != 0)
    {
      error (EXIT_FAILURE, errno, _ ("Unable to disable echoing while \
reading a password"));
    }
  new = old;
  new.c_lflag &= ~ECHO;
  if (tcsetattr (STDIN_FILENO, TCSAFLUSH, &new) != 0)
    {
      error (EXIT_FAILURE, errno, _ ("Unable to disable echoing while \
reading a password"));
    }
  while (fgets (c, size, stdin))
    {
      if (c[strlen (c) - 1] == '\n')
        {
          c[strlen (c) - 1] = '\0';
          tmp = string_create (c);
          destination = string_catd (&destination, &tmp);
          tcsetattr (STDIN_FILENO, TCSAFLUSH, &old);
          return destination;
        }
      tmp = string_create (c);
      destination = string_catd (&destination, &tmp);
      printf ("%s\n", destination.s);
      max_size -= destination.len;
      if (max_size == 0)
        {
          tcsetattr (STDIN_FILENO, TCSAFLUSH, &old);
          return destination;
        }
      size = STRING_CHUNK_SIZE < max_size ?
              STRING_CHUNK_SIZE : max_size;
    }
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &old);
  return destination;
}
