#include "string.h"


String string_init()
{
    String S;
    S.elem = malloc(2*sizeof(char));
    S.capacity = 1;
    S.size = 0;
    *S.elem = '\0';
    return S;
}


//在末尾追加字符串
void string_insert(String *S, char *s)
{
    int len = (int)strlen(s);
    //扩容
    if(S->capacity < S->size+len){
        S->elem = realloc(S->elem,(S->capacity+len+1)*sizeof(char));
        S->capacity += len;
    }
    
    for (int i = 0; i<len; i++) {
        *(S->elem+S->size+i) = *(s+i);
    }
    *(S->elem+S->size+len) = '\0';
    S->size += len;
}


//蛮力匹配
int string_match(char *P, char *T)
{
    int n = (int)strlen(T),i = 0;
    int m = (int)strlen(P),j = 0;
    
    while (j<m && i<n) {
        if (T[i] == P[j]) {
            i++;
            j++;
        }else{
            i -= j -1;
            j = 0;
        }
    }
    return i - j;
}

int *buildNext(char *P)
{
    int m = (int)strlen(P), j=0;
    int *N = malloc(m*sizeof(int));
    int t = N[0] = -1;
    
    while (j < m-1) {
        if (0>t || P[j] == P[t]) {
            N[++j] = ++t;
        }else{
            t = N[t];
        }
    }
    return N;
}


//KMP算法
int string_kmp(char *P, char *T)
{
    int *next = buildNext(P);
    int n = (int)strlen(T),i = 0;
    int m = (int)strlen(P),j = 0;
    
    while (j<m && i<n) {
        if (0>j || T[i] == P[j]) {
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    return i - j;
}
