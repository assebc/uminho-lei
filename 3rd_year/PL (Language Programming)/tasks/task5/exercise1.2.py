import ply.lex as lex

tokens = (
  'WORD',
  'COMMA',
  'NUMBER',
  'BOOLEAN',
  'LISTOPEN',
  'LISTCLOSE'
)

t_WORD = r'\w+'
t_BOOLEAN = r'[Tt]rue|[Ff]ALSE'
t_COMMA = r'\,'
t_LISTOPEN = r'\['
t_LISTCLOSE = r'\]'

t_ignore = ' \t\n'

def t_NUMBER(t):
  r'-?\d+'
  t.value = int(t.value)
  return t


def t_error(t):
  print(f"Invalid char {t.value[0]}")
  t.lexer.skip(1)

lexer = lex.lex()

while data := input():
  lexer.input(data)
  while tok := lexer.token():
    print(tok)