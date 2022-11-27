# Especificação dos Use Cases

## Use Cases
- Criação da conta de Administrador
- Criação da conta de Jogador Base
- Criação da conta de Jogador Premium
- Login
- Criação de um campeonato
- Adição de um campeonato à lista de campeonatos disponíveis
- Remoção de um campeonato à lista de campeonatos disponíveis
- Adição de um circuito
- Adição de um carro
- Adição de um piloto
- Configuração de um campeonato
- Preparação para a corrida
- Simulação da Corrida Base
- Simulação da Corrida Premium

## Atores

- Gestor
- Administrador
- Jogador
- Guest

---
## Criação da conta de Administrador

### Descrição:
- Gestor cria uma conta para um administrador.

### Cenários:
1. O Manuel (Gestor) quer criar uma conta para um administrador. Fornece o nome "Jorge" e, de seguida, define uma palavra-passe.

### Pré-condição:
- True 

### Pós-condição:
- Nova conta de Administrador adicionada ao sistema.

### Fluxo normal:
1. Gestor fornece nome e palavra-passe
2. Sistema verifica disponibilidade do nome
3. Sistema regista a conta como "administrador"

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

---

## Criação da conta de Jogador Base

### Descrição:
- Guest cria conta.

### Cenários:
1. O Jorge quer criar uma conta como jogador base. Começa por escolher o seu nome ("Jorge") e, de seguida, define uma palavra-passe.

### Pré-condição:
- True 

### Pós-condição:
- Nova conta de Jogador Base adicionada ao jogo.

### Fluxo normal:
1. Guest define um nome e uma palavra passe
2. Sistema verifica disponibilidade do nome
3. Sistema regista a conta como "jogador base"

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

---

## Criação da conta de Jogador Premium

### Descrição:
- Guest cria conta.

### Cenários:
1. O Jorge quer criar uma conta como jogador premium. Começa por escolher o seu nome ("Jorge") e, de seguida, define uma palavra-passe.

### Pré-condição:
- True 

### Pós-condição:
- Nova conta de Jogador Premium adicionada ao jogo.

### Fluxo normal:
1. Guest define um nome e uma palavra passe
2. Sistema verifica disponibilidade do nome
3. Sistema regista a conta como "jogador premium"

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

---

## Login

### Descrição:
- Guest (Administrador ou Jogador) faz login na sua conta.

### Cenários:
1. O Artur quer fazer o login na sua conta. Começa por escolher a opção de login e posteriormente fornece o seu nome e palavra-passe ao jogo.

### Pré-condição:
- True

### Pós-condição:
- Utilizador autenticado (como "administrador" ou "jogador")

### Fluxo normal:
1. Utilizador fornece um nome e uma palavra passe
2. Sistema verifica validade dos dados
3. Sistema verifica que o utilizador é um "jogador"
4. Sistema autentica o login do utilizador como "jogador"

### Fluxo alternativo (1)[Dados de login de administrador] (passo 3)
3.1 Sistema verifica que o utilizador é um "administrador"  
3.2 Sistema autentica o login do utilizador como "administrador".

---

## Criação de um campeonato

### Descrição:
- Administrador cria um campeonato.

### Cenários:
1. O Artur faz login como administrador, vai à opção campeonatos e adiciona um capeonato à lista de campeonatos disponíveis. Começa por lhe dar o nome "CampeUMnato". De seguida, escolhe os circuitos "Gualtar Campus", "Sta Tecla Bairro" e "Azurém Campus" da lista de circuitos disponíveis.

### Pré-condição:
- Administrador autenticado
- Existência de circuitos

### Pós-condição:
- Novo campeonato adicionado ao jogo

### Fluxo normal:
1. Administrador fornece nome do campeonato
2. Sistema verifica disponibilidade do nome
3. Sistema apresenta circuitos existentes
4. Admin escolhe circuito(s) a adicionar
5. Sistema regista o campeonato

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

---

## Adição de um campeonato à lista de campeonatos disponíveis

### Descrição:
- Administrador disponibiliza campeonato aos jogadores

### Cenários:
1. Após ter criado o "CampeUMnato", o Artur decide adicioná-lo à lista de campeonatos disponíveis.
2. O João verifica que existem campeonatos que não estão na lista de campeonatos disponíveis e decide adicioná-los.

### Pré-condição:
- Administrador autenticado.
- Existência de campeonatos indisponíveis.

### Pós-condição:
- Novo campeonato disponível aos jogadores.

### Fluxo normal:
1. Sistema apresenta campeonatos indisponíveis.
2. Administrador seleciona um campeonato a disponibilizar.
3. Sistema atualiza campeonato como disponível.

---

## Remoção de um campeonato da lista de campeonatos disponíveis

### Descrição:
- Administrador torna um campeonato indisponível para os jogadores

### Cenários:
1. O Alberto reparou que existiam dois campeonatos com os mesmos circuitos mas diferentes nomes, o "CampeUMnato" e o "CampEInato" então decidiu remover da lista de campeonatos disponíveis o "CampeUMnato".
2. A Maria achou que o "CampeUMnato" tinha circuitos muito difíceis então decidiu remover dos campeonatos disponíveis o único campeonato.

### Pré-condição:
- Administrador autenticado
- Existência de campeonatos disponíveis

### Pós-condição:
- Novo campeonato indisponível aos jogadores

### Fluxo normal:
1. Sistema apresenta campeonatos disponíveis.
2. Administrador seleciona um campeonato a indisponibilizar.
3. Sistema atualiza campeonato como indisponível.

---

## Adição de um circuito

### Descrição:
- Administrador adiciona um circuito no jogo, indicando o tamanho, curvas e chicanes, o grau de ultrapassagem dos segmentos e o nº de voltas

### Cenários:
1. O José faz login no jogo como administrador e opta por adicionar um novo circuito. Indica como nome do novo circuito a adicionar “Gualtar Campus”. De seguida, indica que o mesmo tem 2Km, 9 curvas e 1 chicane. Com essa informação, o sistema calcula que o circuito tem 10 rectas e apresenta a lista de curvas e rectas de modo a que o José indique o grau de dificuldade de ultrapassagem (GDU) em cada uma. Para as rectas 1 e 6, e curvas 2 e 3, indica um GDU de possível. Para as rectas 4, 5, 7 e 8, e curvas 4, 5, 7 e 8, indica um GDU de impossível. Para os restantes, indica um GDU de difícil. Finalmente, regista o circuito, indicando que cada corrida deverá ter 10 voltas. O circuito passa a estar disponível para integrar campeonatos.

### Pré-condição:
- Administrador autenticado

### Pós-condição:
- Novo circuito adicionado ao jogo

### Fluxo normal:
1. Administrador fornece nome, tamanho em km, nº de curvas, nº de chicanes e nº voltas
2. Sistema verifica disponibilidade do nome do circuito
3. Sistema calcula nº de retas
4. Sistema apresenta lista de curvas e retas (segmentos da pista)
5. Administrador fornece GDU's para cada segmento
6. Sistema regista novo circuito

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

---

## Adição de um carro

### Descrição:
- Administrador adiciona um carro ao jogo, indicando categoria, marca, modelo, cilindrada, potências do(s) motor(es) e o perfil aerodinâmico

### Cenários:
1. O José faz login no jogo como administrador e opta por adicionar um novo carro. Começa por consultar as categorias disponíveis nesta versão do jogo ("C1", "C2", "GT", "SC", talvez categorias a ser adicionadas futuramente). O José opta pela categoria “C2” e, de seguida, indica a marca e modelo do carro: um Ferrari 488 GTE. O José sabe que a cilindrada é de 3902cm3 e a potência do motor de combustão de 661CV e fornece esses valores. Uma vez que o carro não é híbrido, não há lugar à indicação da potência do motor eléctrico. Finalmente, escolhe o perfil aerodinâmico do carro (PAC). Considerando as características do mesmo indica um valor de 0.21 e termina o registo do carro, que fica disponível para ser utilizado em jogos.

### Pré-condição:
- Administrador autenticado

### Pós-condição:
- Novo carro adicionado ao jogo

### Fluxo normal:
1. Sistema apresenta as categorias disponíveis
2. Administrador escolhe categoria, marca, modelo, cilindrada e potência
3. Sistema verifica que o carro é C1 e necessita de fiabilidade (e pode ser híbrido)
4. Administrador indica que carro não é híbrido
5. Administrador indica fiabilidade
6. Sistema verifica fiabilidade
7. Administrador indica PAC
8. Sistema regista carro e este fica disponível para jogar

### Fluxo alternativo (1)[Carro é SC](passo 3):
3.1 Sistema verifica que o carro é SC  
3.2 Regressa a 5

### Fluxo alternativo (2)[Carro é C2](passo 3):
3.1 Sistema verifica que o carro é C2  
3.2 Regressa a 4

### Fluxo alternativo (3)[Carro é GT](passo 3):
3.1 Sistema verifica que o carro é GT  
3.2 Regressa a 4

### Fluxo alternativo (4)[Carro é C2 híbrido](passo 4):
4.1 Administrador indica que carro é híbrido  
4.2 Administrador indica potência do motor elétrico  
4.3 Regressa para 5.

### Fluxo alternativo (5)[Cilindrada não se enquadra na categoria](passo 2):
5.1 Sistema verifica que a cilindrada não se enquadra na categoria.  
5.2 Regressa para 4.

---

## Adição de um piloto

### Descrição:
- Administrador adiciona um piloto ao jogo, indicando nome e níveis de perícia

### Cenários:
1. O José faz login no jogo como administrador e decide adicionar um novo piloto. Começa por indicar que o nome será “Battery Voltar” e, de seguida, os seus níveis de perícia. No critério “Chuva vs. Tempo Seco” (CTS), indicou um valor de 0.6, indicando um ligeiro melhor desempenho em tempo seco. No critério “Segurança vs. Agressividade” (SVA), indicou um valor de 0.4, indicando que o piloto tende a arriscar pouco (logo terá alguma maior dificuldade em ultrapassar, mas menor probabilidade de se despistar). Finalmente, regista o piloto, que fica disponível.

### Pré-condição:
- Administrador autenticado

### Pós-condição:
- Novo piloto adicionado ao jogo

### Fluxo normal:
1. Administrador indica o nome do piloto
2. Sistema verifica disponibilidade do nome do piloto
3. Administrador indica os níveis de perícia nos critérios de CTS ("Chuva vs. Tempo Seco") e SVA ("Segurança vs Agressividade") 
4. Sistema verifica que os dados de níveis de perícia estão válidos
5. Sistema regista novo piloto

### Fluxo alternativo (1)[Nome indisponível](passo 2):
2.1 Sistema informa que o nome não está disponível  
2.2 Regressa a 1.

### Fluxo alternativo (2)[Níveis de perícia inválidos](passo 4):
4.1 Sistema informa que os dados são inválidos  
4.2 Regressa a 3.

---

## Configuração de um campeonato

### Descrição:
- Jogador configura um novo campeonato, escolhendo campeonato, carro e piloto

### Cenários:
1. O Francisco e três amigos resolveram jogar um campeonato de Racing Manager. O Francisco faz login como jogador, escolhe um campeonato e avalia os circuitos que o compõem. Como a maioria são circuitos rápidos, decide participar com um Ferrari 488 GTE (um carro da categoria C2). Escolhe como piloto Battery Voltas, por considerar ser um piloto equilibrado em termos de desempenho. Após inscrever-se, cada um dos amigos escolhe também o seu carro e piloto.

### Pré-condição:
- True

### Pós-condição:
- Jogador registado

### Fluxo normal:
1. Jogador seleciona campeonato
2. Jogador seleciona carro e piloto pretendido
3. Sistema verifica dados
4. Sistema regista o jogador no campeonato
5. Jogador decide começar campeonato

### Fluxo alternativo (1)[Adicionar outro jogador](passo 5):
5.1. Jogador escolhe adicionar outro jogador  
5.2. Regressa a 2

---

## Preparação para a corrida

### Descrição:
- Jogador(es) configura(m) o(s) carro(s) para a corrida

### Cenários:
1. As condições da primeira corrida são apresentadas: o circuito é o “Gualtar Campus” e a situação meteorológica é de tempo seco (a outra possibilidade seria chuva). O Francisco sabe que cada um dos jogadores deve alterar a afinação do carro. O Francisco decide alterar a afinação (possível por se tratar de um C2) e aumenta a downforce de 0.5 (valor neutro) para 0.7. Após a afinação a seu gosto, o Francisco escolhe pneus macios, o que permite ter melhor desempenho no início da corrida, à custa do desempenho no final. Dos três modos de funcionamento do motor (conservador, normal ou agressivo), o Francisco escolhe o agressivo, aumentado o desempenho do carro à custa de maior probabilidade de o motor ter uma avaria.

### Pré-condição:
- Campeonato configurado

### Pós-condição:
- Jogador registado como pronto para corrida

### Fluxo normal:
1. Jogador escolhe fazer afinações ao seu carro
2. Jogador faz afinações
3. Jogador escolhe o tipo de pneu que pretende e se motor é híbrido ou não
4. Sistema regista jogador como pronto

### Fluxo alternativo (1)[Não faz afinações](passo 1):
1.1. Jogador escolhe não fazer afinações ao seu carro  
1.2. Regressa para 3

### Fluxo alternativo (2)[Escolha de motor](passo 3):
3.1 Jogador não consegue escolher tipo de motor se o carro for de categoria SC  
3.2 Regressa para 4

---

## Simulação da Corrida Base

### Descrição:
- Jogo simula a corrida

### Cenários:
1. O Francisco tem a versão base do jogo, os cálculos são feitos em função das posições relativas dos carro, em cada ponto relevante do circuito (recta/curva/chicane).
2. A Sara optou por um carro da categoria C1, híbrido, com downforce mínima, modo de motor agressivo, pneus macios e um piloto com SVA alto. Assim, durante a primeira volta consegue fazer uma ultrapassagem na curva 74. No entanto, na sétima volta, ao tentar uma ultrapassagem na chicane, acaba por sair de pista e ficar na última posição. Os pneus já não estavam em bom estado e acabou por não conseguir ultrapassar ninguém até ao final da corrida. Terminou em terceiro lugar pois o Manuel despistou-se na curva 1 durante a última volta. Nesta corrida nenhum carro sofreu uma avaria.

### Pré-condição:
- Corrida com todos os jogadores prontos 
- Jogador registado no sistema como "jogador base" ou não ter efetuado login

### Pós-condição:
- Corrida simulada

### Fluxo normal:
1. Sistema inicia a simulação da corrida
2. Após cada segmento (curva/reta/chicane) o sistema atualiza situações do mesmo
3. Sistema indica posições após cada volta
4. Sistema apresenta resultados no fim da corrida
5. Sistema atribui pontos a cada jogador, por posições e categorias somando para corridas futuras no mesmo campeonato
6. Sistema simula próximas corridas até serem feitas todas as existentes do campeonato
7. Sistema verifica que jogador não está autenticado
8. Jogador escolhe fazer login
9. Sistema contabiliza os pontos obtidos no ranking da sua conta 
10. Sistema mostra os rankings

### Fluxo alternativo (1)[Jogador já está autenticado](passo 7)
7.1 Sistema verifica que jogador já está autenticado  
7.2 Regressa a 9

### Fluxo alternativo (2)[Jogador não faz login](passo 8)
8.1 Jogador não faz login  
8.2 Regressa a 10

---

## Simulação da Corrida Premium

### Descrição:
- Jogo simula a corrida

### Cenários:
3. O Asdrubal tem a versão premium do jogo, logo os cálculos são efetuado às posições relativas de igual forma mas, essas posições são atualizadas em tempo real em qualquer parte/segmento da corrida.
2. A Sara optou por um carro da categoria C1, híbrido, com downforce mínima, modo de motor agressivo, pneus macios e um piloto com SVA alto. Assim, durante a primeira volta consegue fazer uma ultrapassagem na curva 74. No entanto, na sétima volta, ao tentar uma ultrapassagem na chicane, acaba por sair de pista e ficar na última posição. Os pneus já não estavam em bom estado e acabou por não conseguir ultrapassar ninguém até ao final da corrida. Terminou em terceiro lugar pois o Manuel despistou-se na curva 1 durante a última volta. Nesta corrida nenhum carro sofreu uma avaria.

### Pré-condição:
- Corrida com todos os jogadores prontos 
- Jogador registado no sistema como "jogador premium"

### Pós-condição:
- Corrida simulada

### Fluxo normal:
1. Sistema inicia a simulação da corrida
2. Sistema atualiza as situações do mesmo em tempo real
3. Sistema indica posições em tempo real
4. Sistema apresenta resultados no fim da corrida
5. Sistema atribui pontos a cada jogador, por posições e categorias somando para corridas futuras no mesmo campeonato
6. Sistema simula próximas corridas até serem feitas todas as existentes do campeonato
7. Sistema contabiliza os pontos obtidos no ranking da sua conta
8. Sistema mostra os rankings
