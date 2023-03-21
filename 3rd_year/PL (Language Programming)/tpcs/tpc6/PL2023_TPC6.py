import ply.lex as lex
import re

tokens = (
  'FUNC_NAME', # V
  'CAST', # V
  'VARIABLES', # V
  'KEYWORDS', # V
  'AUXILIAR_PROGRAM', # V
  'PROGRAM', # V
  'LOOPS_KEYWORDS', # V
  'BRACKETS_OPEN', # V
  'BRACKETS_CLOSE', # V
  'CBRACKETS_OPEN', # V
  'CBRACKETS_CLOSE', # V
  'RBRACKETS_OPEN', # V
  'RBRACKETS_CLOSE', # V
  'RETS', # V
  'NUMBER', # V
  'LESS', # V
  'BIGGER', # V
  'EQUALS', # V
  'PLUS', # V,
  'TIMES', # V
  'DIVIDE', # V
  'MINUS', # V
  'COMMENT', # V
  'MULTI_COMMENT', # V
  "COMMA", # V
  'LINE_END', # V
  'LIST', # V
  'SET', # V
  'TUPLE' # V
)

t_VARIABLES = r' \w+(?=\[)*'
t_FUNC_NAME = r' \w+(?=[\{\(])' 
t_PROGRAM = r'program '
t_AUXILIAR_PROGRAM = r'function '
t_LINE_END = r'\;'
t_COMMA = r'\,'
t_LIST = r'\[.*,*\]'
t_SET =  r'\{.*,*\}'
t_TUPLE = r'\(.*,*\)'
t_BRACKETS_OPEN = r'\('
t_BRACKETS_CLOSE = r'\)'
t_CBRACKETS_OPEN = r'\{'
t_CBRACKETS_CLOSE = r'\}'
t_RBRACKETS_OPEN = r'\['
t_RBRACKETS_CLOSE = r'\]'
t_COMMENT = r'//.*'
t_MULTI_COMMENT = r'/\*[\s\S]*?\*/'
t_EQUALS = r'\='
t_LESS = r'<'
t_BIGGER = r'>'
t_PLUS = r'\+'
t_TIMES = r'\*'
t_MINUS = r'\-'
t_DIVIDE = r'\/'
t_RETS = r'\.{2}'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)

    return t

def t_CAST(t):
    r'int|float|char|string|double|long|bool'
    return t

def t_KEYWORDS(t):
    r'if|in|or|else|elif|(else if)'
    return t

def t_LOOPS_KEYWORDS(t):
    r'for|while'
    return t

def t_error(t):
    if re.match(r'[ \t\n]', t.value[0]) == None:
      print(f"Unspecified token {t.value[0]}")
    t.lexer.skip(1)

example1 = '''
/* factorial.p
-- 2023-03-20 
-- by jcr
*/

int i;

// Função que calcula o factorial dum número n
function fact(n){
  int res = 1;
  while res > 1 {
    res = res * n;
    res = res - 1;
  }
}

// Programa principal
program myFact{
  for i in [1..10]{
    print(i, fact(i));
  }
}

'''

example2 = '''
/* max.p: calcula o maior inteiro duma lista desordenada
-- 2023-03-20 
-- by jcr
*/

int i = 10, a[10] = {1,2,3,4,5,6,7,8,9,10};

// Programa principal
program myMax{
  int max = a[0];
  for i in [1..9]{
    if max < a[i] {
      max = a[i];
    }
  }
  print(max);
}
'''

lexer = lex.lex()
lexer.input(example1)

print("\n\n\n")
print("EXAMPLE 1")
print("\n\n")


while tok := lexer.token():
    print(tok)

print("\n\n\n")
print("EXAMPLE 2")
print("\n\n")


lexer.input(example2)

while tok := lexer.token():
    print(tok)
