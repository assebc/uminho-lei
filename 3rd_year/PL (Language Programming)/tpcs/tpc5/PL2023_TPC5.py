import re

def print_res(line: str):
  print("maq: " + line)

def valid_coin(coin: str):
  # only accepts 5c or above
  return (re.match(r"(5|10|20|50)c", coin) != None) or (re.match(r"(1|2)e", coin) != None)

def coin_balance(coin: str):
  if coin == "5c":
    return 0.05
  elif coin == "10c":
    return 0.1
  elif coin == "20c":
    return 0.2
  elif coin == "50c":
    return 0.5
  elif coin == "1e":
    return 1
  elif coin == "2e":
    return 2
  return 0

def add_balance(coins: str):
  balance = 0.0
  all_coins = coins[6:].split(',')
  for c in all_coins:
    c = c.strip()
    if valid_coin(c):
      balance += coin_balance(c)
    else:
      print_res(c + " - moeda inválida")
  return balance

def make_call(number: str, balance: float):
  out = 0
  number = number[2:]
  print(number)
  if re.match(r"(601|641)\d+",number) != None: # blocked numbers
    print_res("Esse número não é permitido neste telefone. Queira discar novo número!")
  elif re.match(r"(00)\d+",number) != None: # international line
    if balance >= 1.5:
      balance -= 1.5
    else:
      print_res("Não possui saldo suficiente. Queira inserir mais moedas e discar novamente!")
  elif re.match(r"(2)\d+",number) != None and len(number) == 9: # national line
    if balance >= 0.25:
      balance -= 0.25
    else:
      print_res("Não possui saldo suficiente. Queira inserir mais moedas e discar novamente!")
  elif re.match(r"(800)\d+",number) != None and len(number) == 9: # green line
    balance -= 0.0
  elif re.match(r"(808)\d+",number) != None and len(number) == 9: # blue line
    if balance >= 0.1:  
      balance -= 0.1
    else:
      print_res("Não possui saldo suficiente. Queira inserir mais moedas e discar novamente!")
  else: # invalid numbers
    print_res("Esse número é inválido ou não existe. Queira discar novo número!")
  return balance

def balance_splitter(balance: float):
  balance_str = str(balance)
  balance_splited = balance_str.split(".")
  return balance_splited[0]+"e"+balance_splited[1]+"c"

def print_balance(balance: float):
  print_res("saldo = " + balance_splitter(balance))

def change(balance: float, out: bool):
  map_coins = {"5c": 0, "10c": 0, "20c": 0, "50c": 0,"1e": 0, "2e": 0}
  # this brings limitations because of float conflicts in python
  # this version as a normal public phone does not accept coins below 5 cents
  while balance > 0.05:
    for coin in ["2e", "1e", "50c", "20c", "10c"]:
      if balance >= coin_balance(coin):
        map_coins[coin] += 1
        balance -= coin_balance(coin)
        break

  if out:
    print(f"maq: troco = {map_coins['2e']}x2e, {map_coins['1e']}x1e, {map_coins['50c']}x50c, {map_coins['20c']}x20c, {map_coins['10c']}x10c, {map_coins['5c']}x5c")
    print_res("Volte sempre!") 
  else:
    print_res("Tome os seus " + balance_splitter(balance) + " de volta!")
    print(f"maq: {map_coins['2e']}x2e, {map_coins['1e']}x1e, {map_coins['50c']}x50c, {map_coins['20c']}x20c, {map_coins['10c']}x10c, {map_coins['5c']}x5c")
    print_res("Volte sempre!")

def main():
  states = ["LEVANTAR","POUSAR","MOEDA","T","ABORTAR"]
  state = ""
  ins = str(input())
  balance = 0.00
  out = True
  if re.fullmatch(r"(?i:LEVANTAR)", ins):
    state = states[0]
    print_res("Introduza moedas!")
    ins = str(input())

    if re.match(r"(?i:MOEDA)", ins):
      state = states[2]
      balance += add_balance(ins)
      print_balance(balance)

      ins = str(input())

      while re.fullmatch(r"(?i:POUSAR)", ins) == None:
        # using if statements because match is for 3.10+ python version
        if re.match(r"(?i:MOEDA)", ins):
          state = states[2]
          balance += add_balance(ins)
          print_balance(balance)

        elif re.match(r"(?i:T=)", ins):
          state = states[3]
          balance = make_call(ins, balance)
          print_balance(balance)
            
        elif re.match(r"(?i:ABORTAR)", ins):
          state = states[-1]
          out = False
          break

        else:
          print_res("Ação inválida ou inexistente!")

        ins = str(input())

    else:
      print("Precisa de inserir moedas primeiramente!")

    change(balance, out)

  else:
    print("Ação inválida ou inexistente!")
    
if __name__ == "__main__":
  main()