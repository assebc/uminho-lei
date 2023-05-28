import sys
import ply.lex as lex
import ply.yacc as yacc

import lex_pug
import yacc_pug

if __name__== "__main__":

    if len(sys.argv) != 2:
        print("Usage: python main.py <input_file>")
        sys.exit(1)

    input_file = sys.argv[1]

    lexer = lex.lex(module=lex_pug)
    lexer.tabcount = 0
    lexer.lasttab = 0
    lexer.tag = False
    parser = yacc.yacc(module=yacc_pug)

    with open(f"../tests/pug/{input_file}.pug", 'r') as file:
        content = file.read()
    
    html = parser.parse(content, lexer=lexer)


    with open(f"../tests/html/output.html", "w+") as f:
        f.write(html)