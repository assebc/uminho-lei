import ply.lex as lex

tokens = (
  'TAG',
  'OPEN_TAG',
  'CLOSE_TAG',
  'COMMA',
  'KEY',
  'VALUE',
  'EQUALS'
)

t_TAG = r'@\w+' 
t_EQUALS = r'='
t_KEY = r'\w+'
t_COMMA = r','
t_OPEN_TAG = r'\{'
t_CLOSE_TAG = r'\}'

t_ignore = r' \t\n'


def t_ANY_error(t): # regra válida para todos os estados
  print(f"Ilegal char: {t.value[0]}")
  t.lexer.skip(1)

def t_VALUE(t):
  r'[\"\{]\s*(.*)[\"\}]'
  if len(t.value) > 2:
    t.value = t.value[1:-1]
  else: 
    t.value = None

  return t

data ='''
@incollection {HDYE78,
author = "Ricardo Martini and Pedro Rangel Henriques and Giovani Libreloto",
title = "Storing Archival Emigration Documents to Create Virtual Exhibition Rooms",
booktitle = "New Contributions in Information Systems and Technologies",
series="Advances in Intelligent Systems and Computing",
editor="Rocha, Alvaro and Correia, Ana and Costanzo, S. and Reis, Luis Paulo",
volume="353",
pages="403-409",
year = "2015",
month =  "April"

@book {H787,
author = {Vitor T. Martins and Pedro Rangel Henriques and Daniela da Cruz},
title = {An AST-based tool, Spector, for Plagiarism Detection},
booktitle = {Proceedings of SLATE’15},
pages = {173--178},
ISBN = {},
year = {2015},
month =   {},
publisher = {Fundacion General UCM},
annote = {Keywords: software, plagiarism, detection, comparison, test}}

@book {H787,
author = {Vitor T. Martins and Pedro Rangel Henriques and Daniela da Cruz},
title = "{A}n {AST}-based tool, {S}pector, for Plagiarism Detection",
booktitle = {Proceedings of SLATE’15},
pages = {173--178},
ISBN = {},
year = {2015},
month =   {},
publisher = {Fundaci ́on General UCM},
annote = {Keywords: software, plagiarism, detection, comparison, test}
}

'''

lexer = lex.lex()

lexer.stack = list()

lexer.input(data)

while tok := lexer.token():
  print(tok)