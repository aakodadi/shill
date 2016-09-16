#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "string_type.h"

string string_create(const char* source) {
    unsigned long len;
    string destination;
    if (source == NULL) {
        len = 0;
        destination.len = 0;
        destination.s = malloc(1);
        destination.s[0] = '\0';
        return destination;
    }
    len = strlen(source);
    destination.len = len;
    destination.s = malloc(len + 1);
    strncpy(destination.s, source, len + 1);
    destination.s[destination.len] = '\0';
    return destination;
}

string string_n_create(const char* source, unsigned long size) {
    string destination;
    if (source == NULL) {
        destination.len = 0;
        destination.s = malloc(1);
        strncpy(destination.s, "", 1);
        return destination;
    }
    destination.len = size;
    destination.s = malloc(size + 1);
    strncpy(destination.s, source, size + 1);
    destination.s[destination.len] = '\0';
    return destination;
}

unsigned long string_destroy(string* s) {
    unsigned long len;
    len = s->len;
    s->len = 0;
    free(s->s);
    s->s = NULL;
    return len;
}

string string_cat(string s1, string s2) {
    string destination;
    destination.len = s1.len + s2.len;
    destination.s = malloc(destination.len + 1);
    strncpy(destination.s, s1.s, s1.len + 1);
    strncat(destination.s, s2.s, s2.len + 1);
    return destination;
}

string string_catd(string* s1, string* s2) {
    string destination = string_cat(*s1, *s2);
    string_destroy(s1);
    string_destroy(s2);
    return destination;
}

string string_cpy(string source) {
    string destination;
    destination = string_create(source.s);
    return destination;
}

string string_cpyd(string* source) {
    string destination = string_cpy(*source);
    string_destroy(source);
    return destination;
}

int string_cmp(string s1, string s2) {
    return strcmp(s1.s, s2.s);
}

string string_from_unsigned_long(unsigned long n) {
    int len = snprintf(NULL, 0, "%lu", n);
    string destination = string_create("");
    free(destination.s);
    destination.s = malloc(len + 1);
    snprintf(destination.s, len + 1, "%lu", n);
    destination.len = len;
    return destination;
}