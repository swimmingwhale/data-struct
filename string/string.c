#include "string.h"


struct string string_init()
{
    struct string S;
    S.elem = malloc(2*sizeof(char));
    S.capacity = 1;
    S.size = 0;
    *S.elem = '\0';
    return S;
}


//在末尾追加字符串
void string_insert(struct string *string, char *s)
{
    int len = (int)strlen(s);
    //扩容
    if(string->capacity < string->size+len){
        string->elem = realloc(string->elem,(string->capacity+len+1)*sizeof(char));
        string->capacity += len;
    }
    
    for (int i = 0; i<len; i++) {
        *(string->elem+string->size+i) = *(s+i);
    }
    *(string->elem+string->size+len) = '\0';
    string->size += len;
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

int *build_next(char *P)
{
    int m = (int)strlen(P), j=0;
    int *N = malloc(m*sizeof(int));
    int t = N[0] = -1;
    
    while (j < m-1) {
        if (0>t || P[j] == P[t]) {
            j++;t++;
            N[j] = (P[j] != P[t] ? t : N[t]);
        }else{
            t = N[t];
        }
    }
    return N;
}


//KMP算法
int string_kmp(char *P, char *T)
{
    int *next = build_next(P);
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


int *build_bc(char *P)
{
    int *bc = malloc(256*sizeof(int));
    
    for (int j=0; j<256; j++) {
        bc[j] = -1;
    }
    
    for (int m = (int)strlen(P),j=0; j<m; j++) {
        bc[P[j]] = j;
    }
    
    return bc;
}


int *build_ss(char *P)
{
    int m = (int)strlen(P);
    int *ss = malloc(m*sizeof(int));
    ss[m-1] = m;
    
    for (int lo = m -1,hi = m-1,j=lo-1; j>=0; j--) {
        if ((lo<j) && ss[m-hi+j-1] <=j-lo) {
            ss[j] = ss[m-hi+j-1];
        }else{
            hi = j; lo = min(lo,hi);
            while ((0<=lo)&&(P[lo] == P[m-hi+lo-1])) {
                lo--;
            }
            ss[j] = hi -lo;
        }
    }
    return ss;
}


int *build_gs(char *P)
{
    int *ss = build_ss(P);
    int m = (int)strlen(P);
    int *gs = malloc(m*sizeof(int));
    for (int j =0; j<m; j++) {
        gs[j] = m;
    }
    for (int i = 0, j = m-1; j<UINT_MAX; j--) {
        if (j+1 == ss[j]) {
            while (i<m-j-1) {
                gs[i++] = m-j-1;
            }
        }
    }
    for (int j=0; j<m-1; j++) {
        gs[m-ss[j]-1] = m-j-1;
    }
    return gs;
}



int string_bm(char *P,char* T)
{
    int* bc = build_bc(P);
    int* gs = build_gs(P);
    int i = 0;

    while (strlen(T)>=i+strlen(P)) { //不断右移模式串
        int j = (int)strlen(P) -1; //从模式串的尾端开始
        while (P[j]==T[i+j]) { //自右向左对比
            if(0>--j)break;
        }
        if (0>j) { //完全匹配
            break;
        }else{   //否则在gs表与bc表选择最大者
            i+= max(gs[j], j-bc[T[i+j]]);
        }
    }

    return i;
}
