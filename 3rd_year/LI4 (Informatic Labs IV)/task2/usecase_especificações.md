# Especificação dos Use Cases

---

## Gerar códigos promocionais

### Descrição:
- Comerciante cria código promocional referente a um dos seus produtos
- Adição de um produto-comerciante
- Produtos - comerciante

### Cenários:
1. O Jorge queria vender um produto a um preço mais barato para um dos seus clientes, para isso ele foi consultar os seus produtos, na sua banca pessoal, selecionou o produto que pretendia descontar e clicou em "Ver", deu o número que pretende descontar e clicou em "Criar código promocional". Depois, através dos contactos fornecidos pelo cliente, deu o código promocional ao cliente para que ele podesse ter o desconto no produto.

### Mockups de referência:
- Produto - vista comerciante
- 

### Pré-condição:
- Utilizador autenticado e na página de "consulta de produto"

### Pós-condição:
- Novo código promocional gerado

### Fluxo normal:
1. Utilizador seleciona o produto que pretende descontar clicando em "Ver"
2. Utilizador escolhe a quantidade do desconto e clica no botão "Criar código promocional"
3. Sistema verifica que a quantidade do desconto não é maior que o preço do produto

### Fluxo exceção(1)[Desconto > preço do produto](passo 3):
3.1 Sistema verifica que a quantidade do desconto é maior que o preço do produto
3.2 Sistema cancela a criação de código promocional do produto e mostra um aviso de adição impossibilitada

---

## Registo de Empresa

### Descrição:
- Utilizador preenche uma ficha, com os seus dados e os dados da sua Empresa, com o objetivo de associar a Empresa à sua conta.

### Cenários:
1. O Jorge pretende associar a sua empresa "Par de Solas" à sua conta do Onlyfeiras. Como tal, foi às definições da sua conta e clicou no botão "Faz o registo aqui". De seguida preencheu os dados que foram pedidos fornecendo primeiro as suas informações pessoais: o seu nome completo "Jorge Fernando Ramires Lencastre", o seu email "jorge@pardesolas.pt", a sua morada "Rua Moura Coutinho 63", o seu código-postal "4704-512", o seu telemóvel "920956755" e o seu cargo na empresa "CEO & Manager"; e depois os dados de empresa: o local "Rua de Caires 284", o nome de registo "Par de Solas", o número de contruibuinte "272443590", o código-postal "4704-502" e o número de telemóvel "289603101". Ao fim de ter preenchido todos os campos, Jorge clica em "Submeter" e recebe um aviso a dizer "O teu registo foi submetido com sucesso! Irás receber um email assim que este for aprovado".
2. O Jorge clicou em "Submeter" antes de ter preenchido o seu cargo na empresa, o que resultou do campo "cargo na empresa" ter ficado salientado, acabando o Jorge por preenhcer o seu cargo na empreasa e clicar "Submeter" recebendo um aviso a dizer "O teu registo foi submetido com sucesso! Irás receber um email assim que este for aprovado".

### Mockups de referência:
- Definições de conta - Usuário Cadastrado
- Registo Empresa - Usuário Cadastrado
- Confirmação Registo Empresa

### Pré-condição:
- Utilizador autenticado e na página de "definições do utilizador"

### Pós-condição:
- Nova ficha de registo de empresa entregue para os Organizadores.

### Fluxo normal:
1. Utilizador clica no botão "Faz o registo aqui"
2. Utilizador fornece na secção de "Informações pessoais do representante" o seu nome completo, o seu email, a sua morada, o seu código-postal, o seu telemóvel e o cargo que exerce na empresa. Fornece na secção de "Dados de empresa" o local, o nome de registo, o numero de contribuinte, o código-postal e o telemóvel da empresa e clica em "Submeter"
3. Sistema verifica que todos os campos foram preenchidos e avisa o utilizador que o seu registo de empresa foi recebido com sucesso e que irá receber um email assim que esteja aprovado
4. Sistema guarda a ficha do registo de empresa e envia-a para os Organizadores, para poderem validá-la

### Fluxo alternativo (1)[Falta de campos preenchidos](passo 3):
3.1 Sistema verifica que nem todos os campos foram preenchidos e salienta os campos que falta preencher
3.2 Utilizador preenche os campos em falta
3.3 Regressa a 3

---

## Envio de candidatura de participação

### Descrição:
- Utilizador preenche a candidatura de participação, com os produtos pretendidos, uma descrição e uma imagem, para poder participar numa feira 

### Cenários:
1. O Gustavo pretende participar na feira "Expo calçados e Materiais" para vender os seus sapatos. Para isso, ele clicou no botão de "Participar", presente na página da "Expo calçados e Materiais" ainda por decorrer, selecionou os sapatos na sua banca pessoal, escreveu uma descrição "Por favor comprem os meus sapatos, eu preciso de dinheiro" e uma imagem dos seus sapatos. Gustavo clica em "Submeter" e recebe um aviso a dizer "O teu registo foi submetido com sucesso! Irás receber um email assim que este for aprovado".
2. O Gustavo, ao selecionar os sapatos na sua banca pessoal, reparou que tem muitos sapatos para vender, por isso decidiu patrocionar a feira "Expo calçados e Materiais" para poder selecionar mais produtos na candidatura.

### Mockups de referência:
- Feira por decorrer
- Cadidatura a feira aka criação de banca - comerciante

### Pré-condição:
- Utilizador autenticado e presenta na página de uma feira por decorrer

### Pós-condição:
- Nova candidatura de participação enviada para os Organizadores

### Fluxo normal:
1. Utilizador clica em "Participar"
2. Utilizador seleciona os produtos, da sua banca pessoal, que pretende levar para a feira (no máximo 15)
3. Utilizador fornece uma descrição e uma imagem para a nova banca (opcional)
4. Utilizador clica em "Submeter"
5. Sistema guarda a candidatura de participação e envia-a para os Organizadores, para poderem validá-la

### Fluxo alternativo(1)[Patrocina](passo 1):
1.1 Utilizador seleciona a opção de ser patrocinador
1.2 Utilizador seleciona os produtos, da sua banca pessoal, que pretende levar para a feira (no máximo 15)
1.3 Utilizador fornece uma descrição e uma imagem para a nova banca (opcional)
1.4 Utilizador clica em "Submeter" e paga os 50 euros
1.5 Salta para 5

---

## Visita Feira

### Descrição:
- Utilizador visita uma banca

### Cenários:
1. 

### Mockups de referência:
- Página Inicial - Usuário Cadastrado
- Feira por Decorrer
- Feira a Decorrer

### Pré-condição:
- Utilizador autenticado e presente na página inicial

### Pós-condição:
- Utilizador presente na página de uma feira

### Fluxo normal:
1. Utilizador clica numa das feiras presentes na página inicial

---

## Visita Banca

### Descrição:
- Utilizador visita uma banca

### Cenários:

### Mockups de referência:
- Feira a Decorrer
- Banca de Feira

### Pré-condição:
- Utilizador autenticado e presente na página de uma feira a decorrer

### Pós-condição:
- Utilizador presente na página de uma banca

### Fluxo normal:
1. Utilizador clica no icon de um dos participantes de uma feira

---

## Consultar Carrinho

### Descrição:
- Utilizador pretende consultar todos os produtos que adicionou ao carrinho

### Cenários:
1. O Carlos queria consultar o carrinho, para ver quantos produtos tinha adicionado. Para isso ele clicou no icon do carrinho e reparou que tinha dois artigos que custavam 10 euros e um serviço. Também verificou que o custo total do cesto era de 20 euros e o tempo que cada artigo tem antes que volte a sair do carrinho.

### Mockups de referência:
- Carrinho de Compras

### Pré-condição:
- Utilizador autenticado

### Pós-condição:
- True

### Fluxo normal:
1. Utilizador clica no icon do carrinho de compras, presente em todas as páginas desde que esteja autenticado
2. Sistema calcula o preço de todos os produtos no carrinho do utilizador
3. Utilizador vê todos os produtos que tem no carrinho, o preço total de todos os produtos e, caso seja um artigo, o tempo que tem até sair do carrinho

---

## Adição de Produto no Carrinho

### Descrição:
- Utilizador adiciona o produto pretendido ao carrinho

### Cenários:
1. O Gustavo estava a ver a banca da "Par de Solas", na feira "Expo Calçado e Materias", e viu uns pares de sapatos azuis que gostava de comprar para si e para o seu irmão, portanto clicou no produto e viu que estavam dois em stock, selecionou "2" na quantidade pretendida e clicou em "Adicionar ao carrinho", e, consequentemente, foi levado para a página do seu carrinho, agora com dois pares de sapatos azuis novos.
2. O Gustavo queria comprar dois pares de sapatos azuis mas só havia 1 em stock, mesmo assim selecionou "1" na quantidade pretendida e clicou em "Adicionar ao carrinho" resultando num aviso de adição impossibilitada.

### Mockups de referência:
- Banca de Feira
- Produto - vista utilizador

### Pré-condição:
- Utilizador autenticado e na página de uma banca de uma feira.

### Pós-condição:
- Novo produto adicionado ao carrinho do utilizador

### Fluxo normal:
1. Utilizador clica no produto do tipo artigo que pretende comprar
2. Utilizador seleciona a quantidade pretendida desse produto e clica no botão "Adicionar ao carrinho"
3. Sistema verifica que a quantidade pretendida é igual ou menor que a quantidade de stock desse produto
4. Sistema adiciona os produtos ao carrinho do utilizador, tirando-os de stock e reservando-os durante 30 minutos, tirando-os do carrinho e voltando a pô-los em stock se estes produtos não tiverem sido comprados durante esse espaço de tempo

### Fluxo alternativo(1)[Tipo de produto "Serviço"](passo 1):
1.1 Utilizador clica no produto do tipo serviço que pretende comprar
1.2 Utilizador clica no botão "Adicionar ao carrinho"
1.3 Sistema adiciona o produto ao carrinho do utilizador
1.4 Salta para 5

### Fluxo exceção(2)[Quantidade pretendida > quantidade de stock](passo 3):
3.1 Sistema verifica que a quantidade pretendida é maior que a quantidade de stock desse produto
3.2 Sistema cancela a adição do produto no carrinho do utilizador e mostra um aviso de adição impossibilitada

---

## Remoção de Produto no Carrinho

### Descrição:
- Utilizador pretende remover um produto no seu carrinho de compras

### Cenários:
1. O Vasco queria remover o serviço de pintar o seu carro, pois não achou mais que era uma boa ideia. Como tal, ele clicou no icon do carrinho e clicou em "Remover" no produto pretendido. A página deu reload e Vasco notou que já não estava lá o produto.

### Mockups de referência:
- Carrinho de Compras

### Pré-condição:
- Utilizador autenticado e na página do carrinho

### Pós-condição:
- Produto removido do carrinho de compras

### Fluxo normal:
1. Utilizador clica em "Remover" no produto que pretende remover do carrinho
2. Sistema remove o produto pretendido do carrinho de compras do utilizador e dá refresh à página

---

## Compra de Produtos

### Descrição:
- Utilizador pretende comprar todos os produtos que foi adicionando ao seu carrinho

### Cenários:
1. O Tiago decidiu comprar os produtos que tinha adicionado ao carrinho, então clicou no icon do carrinho de compras e verificou que tinha lá dois artigos e um serviço e que o preço dos produtos era de 100 euros e decidiu continuar com a compra clicando em "Validar Cesto". De seguida reparou que o custo da entrega, que é adicionado ao preço total, era de 10 euros, tornando o preço total a 110 euros e confirmando o pagamento clicando em "Pagar". Foi-lhe apresentado os detalhes da sua encomenda, e agora o Tiago está à espera que os comerciantes o contactem sobre o serviço e sobre a encomenda dos dois artigos.

### Mockups de referência:
- Carrinho de Compras
- Pagamento e expedição
- Confirmação de encomenda

### Pré-condição:
- Utilizador autenticado e na página do carrinho

### Pós-condição:
- Carrinho de compras vazio e os comerciantes, dos respetivos produtos comprados, notificados

### Fluxo normal:
1. Utilizador clica em "Validar o cesto"
2. Sistema notifica os comerciantes de todos os produtos do tipo serviço enviando-lhes mais uma encomenda no seu menu de encomendas
3. Sistema calcula o custo de entrega
4. Utilizador vê o custo dos produtos mais o custo de entrega e clica em "Pagar"
5. Sistema confirma o pagamento, enviando uma notificação aos comerciantes dos respetivos produtos para o seu menu de encomendas, e esvaziando o carrinho de compras do utilizador 

### Fluxo alternativo(1)[Cliente não tem morada registada]
4.1 Utilizador fornece morada
4.2 Sistema guarda a morada nos dados do utilizador
4.2 Regressa a 4

### Fluxo exceção(2)[Carrinho Vazio](passo 4):
4.1 Sistema verifica que o carro está vazio
4.2 Sistema avisa que o carro está vazio

---

## Consulta Banca Pessoal

### Descrição:
- Utilizador pretende aceder à sua banca pessoal

### Cenários:
1. O Carlos pretende consultar a sua banca pessoal, para ver os produtos que já tinha adicionado. Para isso, ele clicou no icon da banca e reparou que tinha 3 produtos do tipo artigo, onde dois estavam em stock e um sem.

### Mockups de referência:
- Produtos-comerciante

### Pré-condição:
- Utilizador autenticado

### Pós-condição:
- True

### Fluxo normal:
1. Utilizador clica no icon da banca, presente em todas as páginas desde que esteja autenticado
3. Utilizador vê todos seus produtos, se estão em stock ou não, e os seus tipos (artigo ou serviço)

---

## Adição de Produto à Banca

### Descrição:
- Utilizador adiciona um produto à sua banca pessoal

### Cenários:
1. 

### Mockups de referência:
- Produtos-comerciante
- Adição/edição de um produto-comerciante

### Pré-condição:
- Utilizador autenticado e na página da banca pessoal

### Pós-condição:
- Novo produto adicionado à banca pessoal do utilizador

### Fluxo normal:
1. Utilizador clica em "Adicionar produto"
2. Utilizador carrega uma foto do produto, escreve um nome, uma descrição, seleciona o tipo do produto como "Artigo" e dá o preço e o stock do produto
3. Sistema verifica que todos os campos foram preenchidos
4. Sistema verifica que o preço está no formato de número e que não passa das duas casas decimais e que o stock está no formato de um número inteiro
5. Sistema adiciona o produto à banca pessoal do utilizador

### Fluxo alternativo(1)[Falta de campos preenchidos](passo 3):
3.1 Sistema verifica que nem todos os campos foram preenchidos e salienta os campos que falta preencher
3.2 Utilizador preenche os campos em falta
3.3 Regressa a 3

### Fluxo alternativo(2)[Formato de preço e stock errados](passo 4):
4.1 Sistema verifica que o preço não está no formato de número ou que passa das duas casas decimais ou que o stock está no formato de um número inteiro, salientado os campos que estiverem no formato errado
4.2 Utilizador preenche os campos de preço e de stock com o formato certo
4.3 Regressa a 4

### Fluxo alternativo(3)[tipo de produto como "Serviço"](passo 2):
2.1 Utilizador carrega uma foto do produto, escreve uma descrição e seleciona o tipo do produto como "Serviço"
2.2 Sistema verifica que todos os campos foram preenchidos
2.3 Salta para 5

### Fluxo alternativo(4)[Falta de campos preenchidos](passo 2.2):
2.2.1 Sistema verifica que nem todos os campos foram preenchidos e salienta os campos que falta preencher
2.2.2 Utilizador preenche os campos em falta
2.2.3 Regressa a 2.2

---

## Edição de Produto

### Descrição:
- Utilizador a um produto à sua banca pessoal

### Cenários:
1. 

### Mockups de referência:
- Produtos-comerciante
- Adição/edição de um produto-comerciante

### Pré-condição:
- Utilizador autenticado e na página da banca pessoal

### Pós-condição:
- Produto editado

### Fluxo normal:
1. Utilizador clica em "Editar" no produto que pretende editar
2. Utilizador carrega uma foto do produto, escreve um nome, uma descrição e dá o preço e o stock do produto
3. Sistema verifica que todos os campos estão preenchidos
4. Sistema verifica que o preço está no formato de número e que não passa das duas casas decimais e que o stock está no formato de um número inteiro
5. Sistema altera dados do produto

### Fluxo alternativo(1)[Falta de campos preenchidos](passo 3):
3.1 Sistema verifica que nem todos os campos estão preenchidos e salienta os campos que falta preencher
3.2 Utilizador preenche os campos em falta
3.3 Regressa a 3

### Fluxo alternativo(2)[Formato de preço e stock errados](passo 4):
4.1 Sistema verifica que o preço não está no formato de número ou que passa das duas casas decimais ou que o stock está no formato de um número inteiro, salientado os campos que estiverem no formato errado
4.2 Utilizador preenche os campos de preço e de stock com o formato certo
4.3 Regressa a 4

### Fluxo alternativo(3)[tipo de produto como "Serviço"](passo 2):
2.1 Utilizador carrega uma foto do produto e escreve uma descrição
2.2 Sistema verifica que todos os campos foram preenchidos
2.3 Salta para 5

### Fluxo alternativo(4)[Falta de campos preenchidos](passo 2.2):
2.2.1 Sistema verifica que nem todos os campos foram preenchidos e salienta os campos que falta preencher
2.2.2 Utilizador preenche os campos em falta
2.2.3 Regressa a 2.2

---

## Remoção de Produto à Banca

### Descrição:
- Utilizador remove um produto à sua banca pessoal

### Cenários:
1. 

### Mockups de referência:
- Produtos-comerciante
- Adição/edição de um produto - comerciante

### Pré-condição:
- Utilizador autenticado e na página da banca pessoal

### Pós-condição:
- Produto Removido da banca pessoal

### Fluxo normal:
1. Utilizador clica em "Remover" no produto que pretende remover
2. Sistema remove todas as instâncias desse produto, presentes na sua banca pessoal e possivelmente em bancas de feira e carrinhos de outros utilizadores 

---

## Definição de Conta

### Descrição:
- Utilizador vai para a página de definição de conta

### Cenários:
1.

### Mockups de referência:
- Definições de conta - Usuário Cadastrado
- Definições de conta - Usuário com marca registada

### Pré-condição:
- Utilizador autenticado

### Pós-condição:
- Utilizador presente na página de definição de conta

### Fluxo normal:
1. Utilizador clica no seu icon ou no seu nome, presente em qualquer página

---

## Alteração de Dados

### Descrição:
- Utilizador pretende alterar o seu nome de usuário ou morada ou contacto

### Cenários:
1.

### Mockups de referência:
- Definições de conta - Usuário Cadastrado
- Definições de conta - Usuário com marca registada

### Pré-condição:
- Utilizador autenticado

### Pós-condição:
- Dados do Utilizador alterados

### Fluxo normal:
1. Utilizador preenche os campos que pretende alterar, entre "Nome de Usuário" , "Contacto e "Morada" e clica em "Guardar Alterações"
2. Sistema altera os dados preenchidos desse utilizador

### Fluxo alternativo(1)[Falta de campos preenchidos](passo 2):
2.1 Sistema verifica que os campos de Morada não estão vazios nem estão todos preenchidos
2.2 Sistema salienta os campos da Morada que falta preencher
2.2 Salta para 2

---

## Consulta Feiravoritos

### Descrição:
- Utilizador consulta os seus feiravoritos

### Cenários:
1.

### Mockups de referência:
- Feiravoritos

### Pré-condição:
- Utilizador autenticado

### Pós-condição:
- Utilizador presente na página de feiravoritos

### Fluxo normal:
1. Utilizador clica no icon estrela presente em qualquer página

---

## Adiciona a Feiravoritos

### Descrição:
- Utilizador adiciona feira aos feiravoritos

### Cenários:
1.

### Mockups de referência:
- Página Inicial - Usuário Cadastrado
- Feira por decorrer
- Feira a decorrer

### Pré-condição:
- Utilizador autenticado e presente na página inicial ou na página de uma feira

### Pós-condição:
- Feira adicionada nos feiravoritos

### Fluxo normal:
1. Utilizador clica no icon da estrela não preenchida correspondente à feira que pretende adicionar
2. Sistema adiciona a feira pretendida aos feiravoritos do utilizador

---

## Remove dos Feiravoritos

### Descrição:
- Utilizador remove feira dos feiravoritos

### Cenários:
1.

### Mockups de referência:
- Página Inicial - Usuário Cadastrado
- Feira por decorrer
- Feira a decorrer

### Pré-condição:
- Utilizador autenticado e presente na página inicial ou na página de uma feira

### Pós-condição:
- Feira removida dos feiravoritos

### Fluxo normal:
1. Utilizador clica no icon da estrela preenchida correspondente à feira que pretende remover
2. Sistema remove a feira pretendida dos feiravoritos do utilizador

---

## Validação de Candidaturas de Participação

### Descrição:
- Organizador valida uma candidatura de participação

### Cenários:
1. 

### Mockups de referência:
- Verificação de cadidaturas - organizador
- Detalhes de candidatura - organizador

### Pré-condição:
- Organizador autenticado

### Pós-condição:
- Candidatura de participação validada ou recusada

### Fluxo normal:
1. Organizador clica no icon de Candidaturas, presentes em qualquer página de um organizador
2. Organizador clica em "ver detalhes" de uma das candidaturas
3. Organizador clica em "Validar"
4. Sistema adiciona nova banca à feira e envia um email ao utilizador sobre a validação, referentes à candidatura validada

### Fluxo alternativo(1)[Recusa candidatura](passo 3):
3.1 Organizador clica em "Recusar"
3.2 Sistema envia um email ao utilizador, referente à candidatura recusada

---

## Validação do registo de empresa

### Descrição:
- Organizador valida um registo de empresa

### Cenários:
1. 

### Mockups de referência:
- Verificação de marcas - organizador
- Detalhes de registo de empresa - organizador

### Pré-condição:
- Organizador autenticado

### Pós-condição:
- Registo de empresa recusado ou validado

### Fluxo normal:
1. Organizador clica no icon de verificação de marcas, presentes em qualquer página de um organizador
2. Organizador clica em "ver detalhes" de um dos registos
3. Organizador clica em "Validar"
4. Sistema associa a marca e envia um email ao utilizador, referente ao registo de empresa validado

### Fluxo alternativo(1)[Recusa registo de empresa](passo 3):
3.1 Organizador clica em "Recusar"
3.2 Sistema envia um email ao utilizador, referente ao registo de empresa recusado

---

## Criação de Feiras

### Descrição:
- Organizador cria uma nova feira fornecendo o título, a descrição, a fotografia , a data de começo e fim, o tipo e as etiquetas da feira

### Cenários:
1. 

### Mockups de referência:
- Dashboard - organizador
- Criação de feira - organizador

### Pré-condição:
- Organizador autenticado e presente na página inicial

### Pós-condição:
- Nova feira criada

### Fluxo normal:
1. Organizador clica em "Criar feira"
2. Organizador fornece o "Título" da feira, a "Descrição, a fotografia, a "Data começo"/"Data fim", as "Etiquetas" e o "Tipo"
3. Sistema verifica que todos os campos foram preenchidos
4. Sistema guarda a feira

### Fluxo alternativo(1)[Falta de campos preenchidos](passo 3):
3.1 Sistema verifica que nem todos os campos foram preenchidos e salienta os campos que falta preencher
3.2 Utilizador preenche os campos em falta
3.3 Regressa a 3



