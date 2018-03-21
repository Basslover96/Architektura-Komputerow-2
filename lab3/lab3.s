SYSEXIT = 1
EXIT_SUCCESS = 0

.text
.data
float1: .float 1.11
float2: .float -2.22
zero: .float 0.00

#Kontrola zaokrąglenia
r_nearest: .short 0x000
r_down: .short 0x400
r_up: .short 0x800
r_trunkate: .short 0xc00

#Kontrola precyzji
single: .short 0x000
double: .short 0x200
extended: .short 0x300

#Baza
base: .short 0x103F

.global _start
_start:

#Ustawienie trybu zaokrąglania i precyzji
mov r_nearest, %eax
mov double, %ebx
mov base, %ecx

add %eax, %ebx
add %ebx, %ecx
mov %ecx, base
fldcw base

jmp exceptions

#Działania

addition:
fld float1
fadd float2

subtraction:
fld float1
fsub float2

multiplication:
fld float1
fmul float2

division:
fld float1
fdiv float2

jmp exit

#Wyjątki
exceptions:

#NaN 0/0 = NaN
fldz
fdiv zero

# +0 0/float1 = +0
fldz
fdiv float1 

# -0 0/float2 = -0
fldz
fdiv float2

# +inf float1/0 = +inf
flds float1
fdiv zero

# -inf float2/0 = -inf
flds float2
fdiv zero

exit:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
