int 13
mov ah bh
mov 1 ah
int 11
add 1 ah
cmp ah bh
jne %10
int 11
int 10
