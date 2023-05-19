import re

er1 = re.compile(r'\\def:(?P<abrev>(?i:\w+))=(?P<word>(?i:\w+));')
er2 = re.compile(r'\\(?i:\w+)')
er3 = re.compile(r'\b(?i:in)\b')
er4 = re.compile(r'(?i:mente)\b')

def subs(lines):
    res = []
    abrevs = {}
    opt = 0
    for line in lines:
        if tok := er1.search(line):
            key = "\\" + tok.groupdict()["abrev"].lower()
            abrevs[key] = tok.groupdict()["word"].lower()
            opt = 1
        if tok := er2.search(line):
            if tok.group() in abrevs.keys():
                line = er2.sub(abrevs[tok.group()], line)
        if tok := er3.search(line):
            line = er3.sub('/', line)
        if tok := er4.search(line): 
            line = er4.sub('~', line)

        if opt != 1:
            res.append(line)
        opt = 0
    return res

fi = open("data/input.txt", "r")
fo = open("data/output.txt", "w+")
lines = subs(fi.readlines())
fo.writelines(lines)

fi.close()
fo.close()
