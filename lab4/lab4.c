#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t startTime, stopTime;

//Struktura do przechowywania liczb dla SIMD
typedef struct myVector{
    float  a;
    float  b;
    float  c;
    float  d;
}myVector;

//Generacja tablicy wektorów
void randVectorTable(myVector * table, int size){
    for(int i=0; i<size; i++){
        table[i].a= rand()%100 + 1;
        table[i].b= rand()%100 + 1;
        table[i].c= rand()%100 + 1;
        table[i].d= rand()%100 + 1;
    }
}

myVector createVector(float a, float  b, float c, float d){
    myVector toReturn;
    toReturn.a=a;
    toReturn.b=b;
    toReturn.c=c;
    toReturn.d=d;
    return toReturn;
}

//Działania dla SIMD

//Dodawanie SIMD
double AddSIMD (myVector table[], int amountOfNumbers){
    myVector addResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "addps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(addResult)
                :"g"(a), "g"(b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return ((time/CLOCKS_PER_SEC)/10);
}

//Odejmowanie SIMD
float SubSIMD (myVector table[], int amountOfNumbers){
    myVector subResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "subps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(subResult)
                :"g"(a), "g"(b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

//Mnożenie SIMD
float MulSIMD (myVector table[], int amountOfNumbers){
    myVector mulResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "mulps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(mulResult)
                :"g"(a), "g"(b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

//Dzielenie SIMD
float DivSIMD (myVector table[], int amountOfNumbers){
    myVector divResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "divps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(divResult)
                :"g"(a), "g"(b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

//Działania dla SISD

float AddSISD(myVector table[], int amountOfNumbers){
    myVector addResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "fld %1\n"
                "fadd %2\n"
                :"=t"(addResult.a)
                :"m"(a.a), "m"(b.a)
            );
            
            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();
            
            __asm__(
                "fld %1\n"
                "fadd %2\n"
                :"=t"(addResult.b)
                :"m"(a.b), "m"(b.b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fadd %2\n"
                :"=t"(addResult.c)
                :"m"(a.c), "m"(b.c)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fadd %2\n"
                :"=t"(addResult.d)
                :"m"(a.d), "m"(b.d)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }
 
    return (time/CLOCKS_PER_SEC)/10;
}

float SubSISD(myVector table[], int amountOfNumbers){
    myVector subResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "fld %1\n"
                "fsub %2\n"
                :"=t"(subResult.a)
                :"m"(a.a), "m"(b.a)
            );
            
            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fsub %2\n"
                :"=t"(subResult.b)
                :"m"(a.b), "m"(b.b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fsub %2\n"
                :"=t"(subResult.c)
                :"m"(a.c), "m"(b.c)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fsub %2\n"
                :"=t"(subResult.d)
                :"m"(a.d), "m"(b.d)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

float MulSISD(myVector table[], int amountOfNumbers){
    myVector mulResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "fld %1\n"
                "fmul %2\n"
                :"=t"(mulResult.a)
                :"m"(a.a), "m"(b.a)
            );
            
            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fmul %2\n"
                :"=t"(mulResult.b)
                :"m"(a.b), "m"(b.b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fmul %2\n"
                :"=t"(mulResult.c)
                :"m"(a.c), "m"(b.c)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fmul %2\n"
                :"=t"(mulResult.d)
                :"m"(a.d), "m"(b.d)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

float DivSISD(myVector table[], int amountOfNumbers){
    myVector divResult;
    myVector a;
    myVector b;
    double time = 0;

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "fld %1\n"
                "fdiv %2\n"
                :"=t"(divResult.a)
                :"m"(a.a), "m"(b.a)
            );
            
            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

             __asm__(
                "fld %1\n"
                "fdiv %2\n"
                :"=t"(divResult.b)
                :"m"(a.b), "m"(b.b)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fdiv %2\n"
                :"=t"(divResult.c)
                :"m"(a.c), "m"(b.c)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
            startTime = clock();

            __asm__(
                "fld %1\n"
                "fdiv %2\n"
                :"=t"(divResult.d)
                :"m"(a.d), "m"(b.d)
            );

            stopTime = clock();
            time += (double)(stopTime - startTime);
        }
    }

    return (time/CLOCKS_PER_SEC)/10;
}

int main(){

    srand(time(NULL));

    myVector myVectorTable[8192];
    randVectorTable(myVectorTable, 8192);

    FILE * file;
    file=fopen("wyniki.txt","w");

    fprintf(file,"Typ obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 2048\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(myVectorTable,2048));
    fprintf(file,"%s %f","\n- ",SubSIMD(myVectorTable,2048));
    fprintf(file,"%s %f","\n* ",MulSIMD(myVectorTable,2048));
    fprintf(file,"%s %f","\n/ ",DivSIMD(myVectorTable,2048));
    
    fprintf(file,"\n\nTyp obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 4096\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(myVectorTable,4096));
    fprintf(file,"%s %f","\n- ",SubSIMD(myVectorTable,4096));
    fprintf(file,"%s %f","\n* ",MulSIMD(myVectorTable,4096));
    fprintf(file,"%s %f","\n/ ",DivSIMD(myVectorTable,4096));

    fprintf(file,"\n\nTyp obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 8192\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(myVectorTable,8192));
    fprintf(file,"%s %f","\n- ",SubSIMD(myVectorTable,8192));
    fprintf(file,"%s %f","\n* ",MulSIMD(myVectorTable,8192));
    fprintf(file,"%s %f","\n/ ",DivSIMD(myVectorTable,8192));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 2048\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(myVectorTable,2048));
    fprintf(file,"%s %f","\n- ",SubSISD(myVectorTable,2048));
    fprintf(file,"%s %f","\n* ",MulSISD(myVectorTable,2048));
    fprintf(file,"%s %f","\n/ ",DivSISD(myVectorTable,2048));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 4096\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(myVectorTable,4096));
    fprintf(file,"%s %f","\n- ",SubSISD(myVectorTable,4096));
    fprintf(file,"%s %f","\n* ",MulSISD(myVectorTable,4096));
    fprintf(file,"%s %f","\n/ ",DivSISD(myVectorTable,4096));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 8192\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(myVectorTable,8192));
    fprintf(file,"%s %f","\n- ",SubSISD(myVectorTable,8192));
    fprintf(file,"%s %f","\n* ",MulSISD(myVectorTable,8192));
    fprintf(file,"%s %f","\n/ ",DivSISD(myVectorTable,8192));

    fclose(file);

    return 0;
}
