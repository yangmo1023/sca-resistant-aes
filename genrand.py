#!/usr/bin/python
from random import randint

s = '{'
for i in range(0, 256/16):
    for j in range(0,16):
        s += str(hex(randint(0,1<<32))) + ', '
    s += '\n'
s += '}'

print 'random (32-bit):'
print s

def randslice():
    r = randint(0,1<<16)
    r2 = 0
    for i in range(0,16):
        b = r & (1 << i)
        r2 |= ((b << i)| (b << (i+1)))

    return r2



print 'random sliced (32-bit):'

s = '{'
for i in range(0, 256/16):
    for j in range(0,16):
        s += str(hex(randslice())) + ', '
    s += '\n'
s += '}'

print s
