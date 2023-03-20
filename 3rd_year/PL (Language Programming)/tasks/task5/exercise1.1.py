import ply.lex as lex

tokens = (
  'WORD',
  'COMMA',
  'DOT',
  'E_MARK',
  'Q_MARK',
  'RETS'
)

t_WORD = r'\w+'
t_COMMA = r'\,'
t_DOT = r'\.'
t_E_MARK = r'\!'
t_Q_MARK = r'\?'
t_RETS = r'\.{3,}'

t_ignore = ' \t\n'

def t_error(t):
  print(f"Invalid char {t.value[0]}")
  t.lexer.skip(1)

lexer = lex.lex()

while data := input():
  lexer.input(data)
  while tok := lexer.token():
    print(tok)
