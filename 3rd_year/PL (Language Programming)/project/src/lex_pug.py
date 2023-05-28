import ply.lex as lex

indent_level = 0

def get_indentation(input_str, pos):
    string = input_str[pos:].partition('\n')[0]
    indent = 0
    for char in string:
        if char == ' ':
            indent += 1
        elif char == '\t':
            indent += 4
        else:
            break
    return int(indent / 4)

special_chars = {
    '&': "&amp;",
    '\"': "&quot;",
    '<': "&lt;",
    '>': "&gt;",
    '`': "\""
}

self_closing = (
    'area',
    'base',
    'br',
    'col',
    'embed',
    'hr',
    'img',
    'input',
    'link',
    'meta',
    'param',
    'source',
    'track',
    'wbr'
)

doctypes = {
    "xml": "?xml version=\"1.0\" encoding=\"utf-8\" ?",
    "transitional": "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"",
    "strict": "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"",
    "frameset": "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\"",
    "1.1": "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\"",
    "basic": "!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML Basic 1.1//EN\" \"http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd\"",
    "mobile": "!DOCTYPE html PUBLIC \"-//WAPFORUM//DTD XHTML Mobile 1.2//EN\" \"http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd\"",
    "plist": "!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\""
}

# Define the token names
tokens = (
    'COMMENT_BLOCK',
    'DEDENT',
    'INDENT',
    'TAG',
    'STRING'
)

states = (
    ("atributte", "exclusive"),
    ("multiline", "exclusive")
)

def t_COMMENT_BLOCK(t):
    r'\/\/([^\|]([\n\s{4}]*))*\|'
    t.lexer.comment_start_line = t.lexer.lineno
    return t    

def t_DOCTYPE(t):
    r'doctype([^\n]+)'
    t.value = t.lexer.lexmatch.group(2).strip()
    if (t.value in doctypes):
        t.value = doctypes[t.value]
    else:
        t.value = "!DOCTYPE " + t.value
    return t

def t_LITERALTAG(t):
    r'<[^<]+>'
    return t

def t_TAG(t):
    r'[^\n]+'
    if '#' in t.value:
        t.lexer.tag = True
    else:
        t.lexer.tag = False
    if t.value in self_closing:
        t.type = 'TAG_SELF_CLOSE'
    if t.value[-1] == '.' and t.value.find("script") == -1:
        t.lexer.push_state('multiline')
    return t

def t_multiline_TAG(t) :
    r'[^\n]+'
    t.type = 'STRING'
    if (t.value[-1] == '|'):
        t.lexer.pop_state()
    return t

def t_DOT(t):
    r'\.(?![^\s]+)'
    return t

def t_COMMA(t):
    r',(?![^\s]+)'
    return t

def t_IGNORECOMMENT(t):
    r'\/\/(\-.*|$)'
    pass

def t_LPAREN(t):
    r'\('
    if(t.lexer.tag):
        print("ERROR: tag using '#'")
        exit(0)
    t.lexer.push_state('atributte')
    return t

def t_VERTBARS(t):
    r'\|(\n*\|)*'
    t.lexer.lineno += len([n for n in t.value if n == '\n'])
    t.lexer.tabcount -= 1
    return t

def t_ANY_newline(t):
    r'\n[ \t]*'
    global indent_level
    t.lexer.lineno += 1
    i = len(t.value) - 1
    if (t.value[-1] != '\n') and (i != indent_level):
        if i > indent_level:
            t.type = 'INDENT'
            t.value = i
            indent_level = i
        elif i < indent_level:
            t.type = 'DEDENT'
            t.value = i
            indent_level = i
        return t
    else:
        pass

def t_DIV(t):
    r'\.[\w\d_-]+'
    return t

def t_atributte_ATRIBUTE_VALUE_MULTILINE(t):
    r'(?<=\=)`[^`]+?`(?=[\s\)])'
    for v in t.value:
        if v == '\n':
            t.lexer.lineno += 1
    for char in special_chars:
        t.value = t.value.replace(char, special_chars[char])
    t.value = t.value, None
    return t

def t_atributte_ATRIBUTE_VALUE(t):
    r'(?<=\=)([\"\']?).*?([\"\']?)(?=[\s\)])'
    start = t.lexer.lexmatch.group(3)
    end = t.lexer.lexmatch.group(4)
    if (start != end):
        print("ERROR: needs to use (''', '\"' ou '')")
        exit()
    t.value = t.value, start
    return t

def t_atributte_ATRIBUTE_NAME(t):
    r'[^= \)\n]+'
    return t

def t_atributte_EQUALS(t):
    r'='
    return t

def t_atributte_RPAREN(t):
    r'\)'
    t.lexer.pop_state()
    return t

def t_ANY_space(t):
    r'\s+'
    pass

t_ANY_ignore = ""

def t_ANY_error(t):
    print(f"Illegal character {t.value[0]}")
    t.lexer.skip(1)

