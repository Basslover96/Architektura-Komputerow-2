SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0 

.text
tocompare: .ascii "Haslo"
tocompare_len = . - tocompare

msg: .ascii "Write text to compare(5): \n"
msg_len = . - msg

thesame: .ascii "Text from the variable equals text from buffor. \n"
thesame_len = . - thesame

notthesame: .ascii "Text from the variable is different from text from buffon. \n"
notthesame_len = . - notthesame

.data
buf: .ascii "     "
buf_len = . - buf

.global _start
_start:

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $0, %ebx
mov %eax,%edx

Loop:
mov tocompare(,%ebx,1), %al
mov buf(,%ebx,1),%ah
inc %ebx
cmp %al,%ah
jne Bad
cmp %ebx,%edx
je Good
jmp Loop

Good:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $thesame,%ecx
mov $thesame_len,%edx
int $0x80
jmp Exit

Bad:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $notthesame,%ecx
mov $notthesame_len,%edx
int $0x80

Exit:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
