import ply.lex as lex

states = (
    ('taga', 'exclusive'),
    ('tagf', 'exclusive'), # num estado exclusivo, apenas aplicamos os tokens e regras para esse estado
                           # por outro lado, num estado inclusivo, as regras e tokens desse estado juntam-se às outras regras e tokens
                           # o estado inicial chama-se 'INITIAL' e não é preciso defini-lo
)

tokens = (
    'ABRIR_TAG',
    'ABRIR_TAG_F',
    'FECHAR_TAG',
    'NOME_TAG',
    'VALOR'
)

t_VALOR = r'[^<]+'

t_ignore = r' \t'

def t_ABRIR_TAG_F(t):
    r'</'
    t.lexer.begin('tagf') # entramos no estado 'tagf'
    return t

def t_ABRIR_TAG(t):
    r'<'
    t.lexer.begin('taga') # entramos no estado 'taga'
    return t

def t_taga_tagf_FECHAR_TAG(t):
    r'>'
    t.lexer.begin('INITIAL') # voltamos ao estado inicial
    return t

def t_taga_NOME_TAG(t):
    r'\w+'
    t.lexer.stack.append(t.value)
    return t

def t_tagf_NOME_TAG(t):
    r'\w+'
    if len(t.lexer.stack) > 0:
        if (nt := t.lexer.stack.pop(-1)) != t.value:
            print(f"Erro - esperado nome de tag '{nt}', mas foi lido '{t.value}'!")
    else:
        print("Erro - nenhuma tag aberta!")
    return t


def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    
def t_ANY_error(t): # regra válida para todos os estados
    print(f"Carácter ilegal: {t.value[0]}")
    t.lexer.skip(1)


data = '''
<pessoa>
    <nome>Maria</nome>
    <idade>32</idade>
</pessoa>
'''

lexer = lex.lex()

lexer.stack = list() # vamos usar esta lista como stack para verificar os nomes das tags

lexer.input(data)


while tok := lexer.token():
    print(tok)