#include <stdio.h>

typedef struct MyVector{
    float s1,s2,s3,s4;
}MyVector;

int main(){

    MyVector a,b,c,d,etap12,etap3;
    float wyznacznik=0;

    //Dane macierzy
    a.s1=1;
    a.s2=2;
    a.s3=4;
    a.s4=5;

    b.s1=7;
    b.s2=2;
    b.s3=5;
    b.s4=1;

    c.s1=3;
    c.s2=2;
    c.s3=5;
    c.s4=1;

    d.s1=3;
    d.s2=8;
    d.s3=4;
    d.s4=1;

    __asm__(
        //---Etap 1---
        "movups %1,%%xmm0\n"
        "movups %2,%%xmm1\n"
        //a0,a2,a0,a1 01 00 10 00
        "shufps $0x48,%%xmm0,%%xmm0\n"
        //b1,b0,b3,b2 10 11 00 01
        "shufps $0xB1,%%xmm1,%%xmm1\n"
        "mulps %%xmm0,%%xmm1\n"
        "movups %1,%%xmm2\n"
        "movups %2,%%xmm3\n"
        //a1,a0,a3,a2 10 11 00 01
        "shufps $0xB1,%%xmm2,%%xmm2\n"
        //b0,b2,b0,b1 01 00 10 00
        "shufps $0x48,%%xmm3,%%xmm3\n"
        "mulps %%xmm2,%%xmm3\n"
        "subps %%xmm3,%%xmm1\n"
        "movups %%xmm1,%%xmm0\n"
        //---Etap 2---
        "movups %3,%%xmm1\n"
        "movups %4,%%xmm2\n"
        //c2,c1,c1,c0 00 01 01 10
        "shufps $0x16,%%xmm1,%%xmm1\n"
        //d3,d3,d2,d3 11 10 11 11
        "shufps $0xEF,%%xmm2,%%xmm2\n"
        "mulps %%xmm1,%%xmm2\n"
        "movups %3,%%xmm3\n"
        "movups %4,%%xmm4\n"
        //c3,c3,c2,c3 11 10 11 11
        "shufps $0xEF,%%xmm3,%%xmm3\n"
        //d2,d1,d1,d0 00 01 01 10
        "shufps $0x16,%%xmm4,%%xmm4\n"
        "mulps %%xmm3,%%xmm4\n"
        "subps %%xmm4,%%xmm2\n"
        "movups %%xmm2,%%xmm1\n"
        "mulps %%xmm0,%%xmm1\n"
        "movups %%xmm1, %0\n"
        : "=g"(etap12)
        : "g"(a),"g"(b),"g"(c),"g"(d)
    );

    __asm__(
        //---Etap 3---
        "movups %1,%%xmm2\n"
        "movups %2,%%xmm3\n"
        "movups %3,%%xmm4\n"
        "movups %4,%%xmm5\n"
        //a2,a3,c0,c0 00 00 11 10
        "shufps $0xE, %%xmm4,%%xmm2\n"
        //b3,b1,d1,d2 10 01 01 11
        "shufps $0x97, %%xmm5,%%xmm3\n"
        "mulps %%xmm2,%%xmm3\n"
        "movups %%xmm3, %%xmm2\n"
        "movups %1,%%xmm3\n"
        "movups %2,%%xmm4\n"
        "movups %3,%%xmm5\n"
        "movups %4,%%xmm6\n"
        //a3,a1,c1,c2 10 01 01 11
        "shufps $0x97, %%xmm5,%%xmm3\n"
        //b2,b3,d0,d0 00 00 11 10
        "shufps $0xE, %%xmm6,%%xmm4\n"
        "mulps %%xmm3,%%xmm4\n"
        "movups %%xmm4, %%xmm3\n"
        "subps %%xmm2,%%xmm3\n"
        "movups %%xmm3, %0\n"
        : "=g"(etap3)
        : "g"(a),"g"(b),"g"(c),"g"(d)
    );

    //---Etap 4---
    wyznacznik=etap12.s1+etap12.s2+etap12.s3+etap12.s4+etap3.s1*etap3.s3+etap3.s2*etap3.s4;

    printf("Wyznacznik wynosi: %f.\n",wyznacznik);

    return 0;
}