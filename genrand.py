from random import randint

s = '{'
for i in range(0, 256/16):
    for j in range(0,16):
        s += str(hex(randint(0,1<<32))) + ', '
    s += '\n'
s += '}'

print s


