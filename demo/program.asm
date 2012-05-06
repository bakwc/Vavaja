mov inputstr ah
int 15
int 13
mov ah dh
mov inputstr ah
int 15
int 13
mov ah eh
mov dh eax
mov eh ebx
div ebx
mov outstr ah
int 15
int 12
int 10
inputstr:
.string Input number: 
outstr:
.string Result: 
