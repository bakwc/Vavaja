int 13
mov ah bh
mov 1 ah
label1:
int 11
add 1 ah
cmp ah bh
jne label1
int 11
int 10
