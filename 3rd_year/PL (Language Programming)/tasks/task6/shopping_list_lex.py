import ply.lex as lex

tokens = (
    'CATEGORY',
    'CATEGORY_START',
    'BULLET',
    'INT',
    'PRODUCT',
    'PRICE',
    'END',
    'SEPARATOR'
)

t_SEPARATOR = r'::'
t_CATEGORY_START = r':'
t_END = r';'
t_BULLET = r'-'

def t_CATEGORY(t):
    r'\b[A-Z]+\b'
    return t

def t_PRICE(t):
    r'\d+\.\d+'
    t.value = float(t.value)
    return t

def t_INT(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_PRODUCT(t):
    r'\w+(\s+\w+)*'
    return t

t_ignore = ' \t\n'

def t_error(t):
    print(f"Illegal char {t.value[0]}")
    t.lexer.skip(1)

lexer = lex.lex()

def main():
    with open("shopping_list.txt") as f:
        content = f.read()

    lexer.input(content)

    while tok := lexer.token():
        print(tok)