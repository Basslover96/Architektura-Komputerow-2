#include <stdio.h>

typedef struct MyVector{
    float s1,s2,s3,s4;
}MyVector;

int main(){

    MyVector a,b,c,d,etap12,etap3;
    float wyznacznik=0;
    float etap41,etap42;

    //Dane macierzy
    a.s1=0;
    a.s2=2;
    a.s3=4;
    a.s4=5;

    b.s1=7;
    b.s2=2;
    b.s3=5;
    b.s4=-2;

    c.s1=3;
    c.s2=2;
    c.s3=5;
    c.s4=1;

    d.s1=7;
    d.s2=8;
    d.s3=4;
    d.s4=1;

    __asm__(
        //---Etap 1---
        "movups %1,%%xmm0\n"
        "movups %2,%%xmm1\n"
        //01 00 10 00
        "shufps $0x48,%%xmm0,%%xmm0\n"
        //10 11 00 01
        "shufps $0xB1,%%xmm1,%%xmm1\n"
        "mulps %%xmm0,%%xmm1\n"

        "movups %1,%%xmm2\n"
        "movups %2,%%xmm3\n"
        //10 11 00 01
        "shufps $0xB1,%%xmm2,%%xmm2\n"
        //01 00 10 00
        "shufps $0x48,%%xmm3,%%xmm3\n"
        "mulps %%xmm2,%%xmm3\n"
        "subps %%xmm3,%%xmm1\n"
        "movups %%xmm1,%%xmm0\n"


        //---Etap 2---
        "movups %3,%%xmm1\n"
        "movups %4,%%xmm2\n"
        //00 01 01 10
        "shufps $0x16,%%xmm1,%%xmm1\n"
        //11 10 11 11
        "shufps $0xEF,%%xmm2,%%xmm2\n"
        "mulps %%xmm1,%%xmm2\n"

        "movups %3,%%xmm3\n"
        "movups %4,%%xmm4\n"
        //11 10 11 11
        "shufps $0xEF,%%xmm3,%%xmm3\n"
        //00 01 01 10
        "shufps $0x16,%%xmm4,%%xmm4\n"
        "mulps %%xmm3,%%xmm4\n"
        "subps %%xmm4,%%xmm2\n"
        "movups %%xmm2,%%xmm1\n"

        "mulps %%xmm0,%%xmm1\n"
        "movups %%xmm1, %0\n"
        : "=g"(etap12)
        : "g"(a),"g"(b),"g"(c),"g"(d)
    );

    //---Etap 3---
    __asm__(
        "movups %1,%%xmm2\n"
        "movups %2,%%xmm3\n"
        "movups %3,%%xmm4\n"
        "movups %4,%%xmm5\n"
        //00 00 11 10
        "shufps $0xE, %%xmm4,%%xmm2\n"
        //10 01 01 11
        "shufps $0x97, %%xmm5,%%xmm3\n"
        "mulps %%xmm2,%%xmm3\n"
        "movups %%xmm3, %%xmm2\n"

        "movups %1,%%xmm3\n"
        "movups %2,%%xmm4\n"
        "movups %3,%%xmm5\n"
        "movups %4,%%xmm6\n"
        //10 01 01 11
        "shufps $0x97, %%xmm5,%%xmm3\n"
        //00 00 11 10
        "shufps $0xE, %%xmm6,%%xmm4\n"
        "mulps %%xmm3,%%xmm4\n"
        "movups %%xmm4, %%xmm3\n"

        "subps %%xmm2,%%xmm3\n"
        "movups %%xmm3, %0\n"
        : "=g"(etap3)
        : "g"(a),"g"(b),"g"(c),"g"(d)
    );

    //---Etap 4---
    __asm__(
        "fld %1\n"
        "fmul %2\n"
        : "=t"(etap41)
        : "m"(etap3.s1),"m"(etap3.s3)
    );

    __asm__(
        "fld %1\n"
        "fmul %2\n"
        : "=t"(etap42)
        : "m"(etap3.s2),"m"(etap3.s4)
    );

    //---Etap 5---
    __asm__(
        "fld %1\n"
        "fadd %2\n"
        "fadd %3\n"
        "fadd %4\n"
        "fadd %5\n"
        "fadd %6\n"
        : "=t"(wyznacznik)
        : "m"(etap12.s1),"m"(etap12.s2),"m"(etap12.s3),"m"(etap12.s4),"m"(etap41),"m"(etap42)
    );

    //wyznacznik=etap12.s1+etap12.s2+etap12.s3+etap12.s4+etap3.s1*etap3.s3+etap3.s2*etap3.s4;
    printf("Wyznacznik wynosi: %f.\n",wyznacznik);

    return 0;
}
