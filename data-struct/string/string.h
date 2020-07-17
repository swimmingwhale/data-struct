#ifndef string_h
#define string_h
#include "common.h"
#include <string.h>

struct String{
    char *elem;
    int size;
    int capacity;
};

typedef struct String String;


String string_init(void);
void string_insert(String *S, char *s);
int string_match(char *P, char *T);
int string_kmp(char *P, char *T);
int string_bm(char *P,char* T);
#endif /* string_h */
