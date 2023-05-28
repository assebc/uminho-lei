import re

def open_tag (str) : 
    padrao = r"^([a-z1-9]+)(\((.*)\))*\s*(.*)"
    padrao2 = r"^#(\w+)(.*)"
    padrao3 = r"^script\((\w+)(.*)\).$"
    match = re.match(padrao, str)
    match2 = re.match(padrao2,str)
    match3 = re.match(padrao3,str)
    str_final = ""

    if match3 != None :
        str_final = f'<script {match3.group(1)}{match3.group(2)}>\n'
    elif match2 != None :
        match_stripped = re.sub(r'^\.', '', match2.group(2))
        str_final = f'<div class = "{match_stripped}" id = "{match2.group(1)}">\n'
    else : 
        if match != None:
            if match.group(3) is None:
                str_final = f'<{match.group(1)}> {match.group(4)}\n'
            else:
                str_final = f'<{match.group(1)} {match.group(3)}>{match.group(4)}\n'
    return str_final

def close_tag (str) : 
    padrao = r"^(\w+)(.*)"
    padrao3 = r"^script\((\w+)(.*)\).$"
    match = re.match(padrao, str)
    match3 = re.match(padrao3,str)
    str_final = ""

    if match3 != None :
        pass
    elif match != None :
        str_final = f'</{match.group(1)}>\n'
    else :
        pass

    return str_final

def comment(str):
    str_final_regex = re.sub(r'^\/\/','',str)
    str_final = f'<!-- {str_final_regex} -->\n'
    return str_final
  
def string(str) :
    return re.sub(r'\|$','',str)

def ponto (str):
    return re.sub(r'\.|\.$','',str)
