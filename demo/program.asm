mov start ah
int 11
int 13
mov ah ch
mov 0 ah
start:
add 1 ah
int 11
cmp ah ch
jne %start
int 10
