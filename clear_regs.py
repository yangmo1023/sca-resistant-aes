#!/usr/bin/python
import sys,re
from sys import argv

if len(argv) != 3:
    print 'usage: %s <in-file> <out-file>' % argv[0]
    sys.exit(1)

asm = open(argv[1],'r').readlines()
outname = argv[2]

regs=re.compile('%[ilogsfp]{1,2}[0-9]{0,1}')
newasm = []

def find_leaky_reg(current_reg,code):
    #current_reg = '%l0'
    current_share = None
    current_line = 0
    line=0
    ret = []
    for i in code:
        line += 1
        spl = i.split('!')
        if len(spl) < 2: 
            continue
        if spl[0] == '':
            continue
        inst = spl[0]
        cmt = spl[1]

        args = cmt.replace('\n','').split(',')
        wshare = args.pop()
        while wshare == '':
            if len(args) == 0: break
            wshare = args.pop()
        if wshare == '': 
            continue
        operands = re.findall(regs, i)
        lastop = operands.pop()
        #print i, 'writes to ', wshare, '(%s)' % lastop
        if lastop == current_reg:

            if 'tmp' in wshare:
                continue

            if 'p1' in wshare:
                if current_share == None:
                    current_share = 'p1'
                    current_line = line
                elif current_share == 'p2':
                    print 'LEAKAGE line p1 %d, previously p2 %d, reg %s' % (line, current_line, current_reg)
                    if lastop not in operands:
                        ret.append(line-1)
                    else:
                        print 'data dependency, cant do anything'
                    current_share = 'p1'
                    current_line = line
                elif current_share == 'p1':
                    current_line = line
                    pass
            if 'p2' in wshare:

                if current_share == None:
                    current_share = 'p2'
                    current_line = line
                elif current_share == 'p2':
                    current_line = line
                elif current_share == 'p1':
                    print 'LEAKAGE line p2 %d, previously p1 %d, reg %s' % (line, current_line, current_reg)
                    if lastop not in operands:
                        ret.append(line-1)
                    else:
                        print 'data dependency, cant do anything'

                    current_share = 'p2'
                    current_line = line


    return ret



for i in ['%l0','%l1','%l2','%l3','%l4','%l5','%l6','%l7',
         '%g0','%g1','%g2','%g3','%g4','%g5','%g6','%g7',
         '%o0','%o1','%o2','%o3','%o4','%o5','%o6','%o7',
         '%i0','%i1','%i2','%i3','%i4','%i5','%i6','%i7']:
    leaks = find_leaky_reg(i, asm)
    offset = 0
    for j in leaks:
        asm.insert(j + offset,'\tmov\t0, %s\t\n' % i)
        offset += 1


open(outname,'w+').write(''.join(asm))


