mov inputstr ah
int 15
int 14
mov eax ebx

mov inputstr ah
int 15
int 14

mov eax ecx
mov ebx eax

int 17

mul ecx

mov outstr ah
int 15
int 12
int 13
int 10
inputstr:
.string Input number: 
outstr:
.string Result: 
