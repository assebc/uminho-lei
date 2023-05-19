import re

er0 = re.compile(r'^((?i:eu|ele)):')
er1 = re.compile(r'^((?i:eu)):')
er2 = re.compile(r'^((?i:ele)):')
er3 = re.compile(r'^((?i:eu))=(?P<name1>[a-zA-z ]+)((?i:ele))=(?P<name2>[a-zA-Z ]+)$')

def subs(lines: list[str], num_file: int) -> list[str]:
    res = list()
    
    match num_file:
        case 1:
            for line in lines:
                res.append(er0.sub(r"",line))
                  
        case 2:
            for i in range(len(lines)):
                if i%2 == 0: res.append(er1.sub("entrevistador: ", lines[i]))
                else: res.append(er2.sub("entrevistado: ",lines[i]))
            
        case 3:
            names = er3.search(lines[0])
            name1 = names.groupdict()["name1"]
            name2 = names.groupdict()["name2"]
            for i in range(1,len(lines)):
                if er1.search(lines[i]): res.append(er1.sub(f"{name1}:",lines[i]))
                else: res.append(er2.sub(f"{name2}:",lines[i]))

    return res

def output(filename: str):
    return re.sub(r'input',"output",filename)

input_file = input("name of input file: ")
num_file = re.search(r'\d+',input_file)
output_file = output(input_file)

fi = open(f"data/{input_file}", "r")
lines = subs(fi.readlines(), int(num_file[0]))

fo = open(f"data/{output_file}", "w+")
fo.writelines(lines)