import ply.yacc as yacc

from shopping_list_lex import tokens

def p_list(p):
    'list : categories'
    p[0] = p[1]

def p_categories(p):
    '''categories : categories category
                  | category'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[1]
        p[0].update(p[2])

def p_category(p):
    'category : CATEGORY CATEGORY_START products'
    p[0] = { p[1] : p[3] }

def p_products(p):
    '''products : products product
                | product'''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[2]]

def p_product(p):
    'product : BULLET INT SEPARATOR PRODUCT SEPARATOR PRICE SEPARATOR INT END'
    p[0] = (p[4], p[6] * p[8])

def p_error(p):
    print("Syntax error!")

parser = yacc.yacc()

with open("shopping_list.txt", encoding="utf8") as f:
    content = f.read()

print(parser.parse(content))