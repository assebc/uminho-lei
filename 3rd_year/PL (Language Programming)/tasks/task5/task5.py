import ply.lex as lex

tokens = (
    'NUMBER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIVIDE',
    'PAROPEN',
    'PARCLOSE'
)

t_PLUS = r'\+'
t_TIMES = r'\*'
t_DIVIDE = r'\/'
t_PAROPEN = r'\('
t_PARCLOSE = r'\)'

def t_MINUS(t):
  r'\-'
  return t

def t_NUMBER(t):
  r'-?\d+'
  t.value = int(t.value)
  return t

t_ignore = ' \t\n'

def t_error(t):
  print(f"Invalid char {t.value[0]}")
  t.lexer.skip(1)

lexer = lex.lex()

while data := input():
  lexer.input(data)
  while tok := lexer.token():
    print(tok)