import ply.yacc as yacc

from lex_pug import tokens
from parser_r import *

def p_document(p):
    '''
    document : elemList
    '''
    p[0] = p[1]

def p_string(p) :
    '''
    string : string STRING
           | STRING
    '''
    if len(p) == 3 :

        p[0] = p[1]+string(p[2])
    else :
        p[0] = string(p[1])

def p_elemList(p):
    '''
    elemList : elemList elem
             | elem
             | string
             | empty
    '''
    if len(p) == 3:
        if p[1] == []:  
            p[0] = p[2]
        elif p[2] == []:  
            p[0] = p[1]
        else:
            p[0] = p[1] + p[2]
    else:
        p[0] = p[1]

def p_elem(p) :
    '''
    elem : TAG INDENT elemList DEDENT
         | TAG INDENT elemList
         | TAG
         | COMMENT_BLOCK
    '''
    if len(p) == 2:
        if p[1][0] == '/':
            p[0] = comment(p[1])
        else :
            p[0] = open_tag(p[1]) + close_tag(p[1])
    else:
        p[0] = open_tag(p[1]) + ponto(p[3]) + close_tag(p[1])

def p_empty(p):
    '''
    empty :
    '''
    pass

def p_error(p):
    if p is None:
        print("Erro de sintaxe: token inesperado no final do arquivo")
    else:
        print(f"Erro de sintaxe: token inesperado '{p.value}' na linha {p.lineno}")
