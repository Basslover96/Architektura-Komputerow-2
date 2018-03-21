SYSEXIT = 1
EXIT_SUCCESS = 0

.code32
.data

liczba1: .long 0xF1111111, 0xE2222222, 0x33333333, 0x04444444
liczba2: .long 0x05555555, 0x44444444, 0x33333333, 0x0F222222

#Liczba iteracji pętli
iterator = ((. - liczba1)/4)-1

.global _start
_start:

#Zerowanie flagi przeniesienia
clc

#Ustawienie iteratora dla pętli
movl $iterator, %ecx

loop:
#Wpisanie liczb do rejestrów
movl liczba1(,%ecx,4), %eax
movl liczba2(,%ecx,4), %ebx

#Dodawanie
adcl %ebx, %eax

#Wysłanie wyniku do stosu
pushl %eax 

pushf

#Zmniejszenie licznika pętli
subl $1, %ecx
cmp $0, %ecx
jl last

popf

jmp loop

#Dopisanie 1 przy ostatnim przeniesieniu
last:
popf
jnc end
xor %edx, %edx
movl $1, %edx
pushl %edx

end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
