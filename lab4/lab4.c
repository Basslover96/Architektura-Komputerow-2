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

myVector createVector(int a, int  b, int c, int d){
    myVector toReturn;
    toReturn.a=a;
    toReturn.b=b;
    toReturn.c=c;
    toReturn.d=d;
    return toReturn;
}

//Działania dla SIMD

//Dodawanie SIMD
double AddSIMD (int amountOfNumbers){
    myVector addResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    double time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers/4;j++){
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
           
		printf("%f",a.a);
		printf

            stopTime = clock();
            time += (double)(stopTime - startTime)/CLOCKS_PER_SEC;
        }
    }

    return time/10;
}

//Odejmowanie SIMD
float SubSIMD (int amountOfNumbers){
    myVector subResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers/4;j++){
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
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

//Mnożenie SIMD
float MulSIMD (int amountOfNumbers){
    myVector mulResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers/4;j++){
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
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

//Dzielenie SIMD
float DivSIMD (int amountOfNumbers){
    myVector divResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers/4;j++){
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
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

//Działania dla SISD

float AddSISD(int amountOfNumbers){
    myVector addResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "add %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(addResult.a)
                :"g"(a.a), "g"(b.a)
            );
            
            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "add %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(addResult.b)
                :"g"(a.b), "g"(b.b)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "add %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(addResult.c)
                :"g"(a.c), "g"(b.c)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "add %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(addResult.d)
                :"g"(a.d), "g"(b.d)
            );

            stopTime = clock();
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

float SubSISD(int amountOfNumbers){
    myVector subResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "sub %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(subResult.a)
                :"g"(a.a), "g"(b.a)
            );
            
            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "sub %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(subResult.b)
                :"g"(a.b), "g"(b.b)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "sub %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(subResult.c)
                :"g"(a.c), "g"(b.c)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "sub %%eax, %%ebx\n"
                "mov %%ebx, %0\n"
                :"=g"(subResult.d)
                :"g"(a.d), "g"(b.d)
            );

            stopTime = clock();
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

float MulSISD(int amountOfNumbers){
    myVector mulResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mul %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(mulResult.a)
                :"g"(a.a), "g"(b.a)
            );
            
            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mul %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(mulResult.b)
                :"g"(a.b), "g"(b.b)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mul %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(mulResult.c)
                :"g"(a.c), "g"(b.c)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mul %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(mulResult.d)
                :"g"(a.d), "g"(b.d)
            );

            stopTime = clock();
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

float DivSISD(int amountOfNumbers){
    myVector divResult;
    myVector a;
    myVector b;
    myVector table[amountOfNumbers];
    float time = 0;

    randVectorTable(table,amountOfNumbers);

    for(int i = 0; i<10; i++){
        for(int j = 0; j<amountOfNumbers;j++){
            a = createVector(table[j].a,table[j].b,table[j].c,table[j].d);
            b = createVector(table[j].a,table[j].b,table[j].c,table[j].d);

            startTime = clock();

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "xor %%edx, %%edx\n"
                "div %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(divResult.a)
                :"g"(a.a), "g"(b.a)
            );
            
             __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "xor %%edx, %%edx\n"
                "div %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(divResult.b)
                :"g"(a.b), "g"(b.b)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "xor %%edx, %%edx\n"
                "div %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(divResult.c)
                :"g"(a.c), "g"(b.c)
            );

            __asm__(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "xor %%edx, %%edx\n"
                "div %%ebx\n"
                "mov %%eax, %0\n"
                :"=g"(divResult.d)
                :"g"(a.d), "g"(b.d)
            );

            stopTime = clock();
            time += (stopTime - startTime);
        }
    }
    
    time/=CLOCKS_PER_SEC;

    return time/10;
}

int main(){

    srand(time(NULL));

    FILE * file;

    file=fopen("wyniki.txt","w");

    fprintf(file,"Typ obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 2048\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(2048));
    fprintf(file,"%s %f","\n- ",SubSIMD(2048));
    fprintf(file,"%s %f","\n* ",MulSIMD(2048));
    fprintf(file,"%s %f","\n/ ",DivSIMD(2048));

    fprintf(file,"\n\nTyp obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 4096\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(4096));
    fprintf(file,"%s %f","\n- ",SubSIMD(4096));
    fprintf(file,"%s %f","\n* ",MulSIMD(4096));
    fprintf(file,"%s %f","\n/ ",DivSIMD(4096));

    fprintf(file,"\n\nTyp obliczen: SIMD\n");
    fprintf(file,"Liczba liczb: 8192\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSIMD(8192));
    fprintf(file,"%s %f","\n- ",SubSIMD(8192));
    fprintf(file,"%s %f","\n* ",MulSIMD(8192));
    fprintf(file,"%s %f","\n/ ",DivSIMD(8192));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 2048\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(2048));
    fprintf(file,"%s %f","\n- ",SubSISD(2048));
    fprintf(file,"%s %f","\n* ",MulSISD(2048));
    fprintf(file,"%s %f","\n/ ",DivSISD(2048));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 4096\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(4096));
    fprintf(file,"%s %f","\n- ",SubSISD(4096));
    fprintf(file,"%s %f","\n* ",MulSISD(4096));
    fprintf(file,"%s %f","\n/ ",DivSISD(4096));

    fprintf(file,"\n\nTyp obliczen: SISD\n");
    fprintf(file,"Liczba liczb: 8192\n");
    fprintf(file,"Sredni czas [s]:\n");
    fprintf(file,"%s %f","+ ",AddSISD(8192));
    fprintf(file,"%s %f","\n- ",SubSISD(8192));
    fprintf(file,"%s %f","\n* ",MulSISD(8192));
    fprintf(file,"%s %f","\n/ ",DivSISD(8192));
    
    fclose(file);

    return 0;
}
