-- -- 
-- Universidade do Minho
-- Disciplina de Bases de Dados
-- A Linguagem SQL
-- Manipulação de Dados
-- Caso de Estudo: A Mercearia da D. Acácia
-- Esquema Global - Vista de Vendas e Vista de Compras integradas
-- Povoamento inicial da base de dados.
-- MySQL 8.0.28 (MySQL Community Server GPL)
-- 2022, Março/Abril
-- --

-- Indicação da base de dados de trabalho
USE Mercearia;

-- Povoamento das tabelas da base de dados
--
-- Povoamento da tabela "Profissão"
-- DESC Profissão;
-- SELECT * FROM Profissão;
-- DELETE FROM Profissão;
INSERT INTO Profissão
	(Id, Descrição)
	VALUES
	('1','Engenheiro'),
    ('2','Professor'),
    ('3','Mecânico'),
    ('4','Padeiro'),
    ('5','Florista')
    ;
--
INSERT INTO Profissão
	(Descrição, Id)
	VALUES
	('Eletricista','6'),
	('Vendedor','7')
    ;
--
INSERT INTO Profissão
	VALUES
	('8','Outra')
    ;

-- Povoamento da tabela "Função"
-- DESC Função;
-- SELECT * FROM Função;
-- DELETE FROM Função;
INSERT INTO Função
	(Id, Descrição)
	VALUES 
    ('1','Gestor'),
    ('2','Auxiliar')
    ;
    
-- Povoamento da tabela "Categoria"
-- DESC Categoria;
-- SELECT * FROM Categoria;
-- DELETE FROM Categoria;
INSERT INTO Categoria
	(Id, Descrição)
	VALUES
    ('01','Padaria'),
    ('02','Laticínios'),
    ('03','Charcutaria'),
    ('04','Vegetais'),
    ('05','Peixe e Marisco'),
    ('06','Carne'),
    ('07','Cereais e Leguminosas'),
    ('08','Fruta'),
    ('09','Congelados Diversos'),
    ('10','Vinhos, Refrigerantes e Águas Minerais'),
    ('11','Doces e Sobremesas'),
    ('12','Condimentos Variados')
    ;
    
-- Povoamento da tabela "RamoAtividade"
-- DESC RamoAtividade;
-- SELECT * FROM RamoAtividade;
-- DELETE FROM RamoAtividade;
INSERT INTO RamoAtividade
	(Id, Descrição)
	VALUES
    ('1','Frutas e Vegetais'),
    ('2','Laticínios'),
    ('3','Cereais e Leguminosas'),
    ('4','Peixe e Marisco'),
    ('5','Carnes'),
    ('6','Cash and Carry')
    ;
 
 
-- Povoamento da tabela "Funcionário"
-- DESC Funcionário;
-- SELECT * FROM Funcionário;
-- DELETE FROM Funcionário;
INSERT INTO Funcionário
    (Id,Nome,Função,Password,eMail)
	VALUES 
    ('1','D.Acácia','1','ac67tr','acacia@mercearia.com'),
    ('2','Maria Catalpa','2','1234','mcatalpa@mercearia.com')
    ;
    
-- Povoamento da tabela "Cliente"
-- DESC Cliente;
-- SELECT * FROM Cliente;
-- DELETE FROM Cliente;
INSERT INTO Cliente
    (Id,Nome,Profissão,Contribuinte,DataNascimento,Dívida,Rua,Localidade,
    CodPostal,Pontos,eMail)
	VALUES 
    ('1','Joaquim Maria Custódio Pires','2','111111111','1990-01-01',
    '0','Rua das Hortas de Cima, 12, R/C','Bairro do Prado','1111-A11','0',NULL),
    ('2','Maria da Luz Vilas','6','222222222','1997-08-25',
    '0','Av. do Sol Nascente','Aveiras do Canto','2222-B22','0','mluz@mail.com'),
    ('3','Mário Rui Taborda','5','333333333','1970-06-03',
    '0','Av. Padre Pereira Melo, 89, 1ºD ','Salinas','3333-B33','0',NULL),
    ('4','José Sousa Priscos','1','444444444','1986-09-21',
    '0','Rua das Hortas de Cima, 44','Bairro do Prado','1111-A11','0','joses@mail.com'),
    ('5','Mariana do Canto da Paz','1','555555555','1998-12-30',
    '0','Beco das Ladaínhas, 2 R/C','Teor do Crato','5555-B55','0','mcpaz@mail.com'),
    ('6','Ana Judite Valente','3','666666666','1994-11-11',
    '0','Rua da Imprensa, 21, 5ºEsq','Cais da Vila','6666-C66','0','ana.judite@mail.com'),
    ('7','Pedro Martins Castro e Sousa','6','777777777','1999-03-24',
    '0','Rua Salvador Macedo da Cunha','Travessos','7777-A77','0','pmartins@mail.com'),
    ('8','Florbela Sebe Mar Alto','1','888888888','1989-06-12',
    '0','Trav. Eng. Cónego Pires','Igrejas','8888-A88','0','flor@mail.com')
    ;

-- Introduzindo apenas os valores dos atributos obrigatórios (NOT NULL)
--
INSERT INTO Cliente
    (Id,Nome,Contribuinte,Dívida,Rua,Localidade,CodPostal,Pontos)
	VALUES 
    ('9','Sónia Fraga Leiras','999999999','0','Trav. João Pais, 21','Vilas','9999-A99','0'),
    ('10','Manuel Costa Paz','101101101','0','Rua do Travesso Azul, 2ºEsq','Lourinho','1010-B10','0')
    ;
    
-- Povoamento da tabela "Telefone"
-- DESC Telefone;
-- SELECT * FROM Telefone;
-- DELETE FROM Telefone;
INSERT INTO Telefone
    (Cliente,Telefone)
	VALUES 
    ('1','+351 111 111 111'),
    ('2','+351 222 222 221'),
    ('3','+351 333 333 331'),
    ('3','+351 333 333 332'),
    ('5','+351 555 555 551'),
    ('5','+351 555 555 552'),
    ('6','+351 666 666 661')
    ;
    
-- Povoamento da tabela "Recomendação"
-- DESC Recomendação;
-- SELECT * FROM Recomendação;
-- DELETE FROM Recomendação;
INSERT INTO Recomendação
    (Cliente,ClienteRecomendado,Pontos)
	VALUES 
    ('1','2','100'),
    ('1','3','100'),
    ('3','5','100')
    ;

-- Povoamento da tabela "Fornecedor"
-- DESC Fornecedor;
-- SELECT * FROM Fornecedor;
-- DELETE FROM Fornecedor;
INSERT INTO Fornecedor
    (Id,Designação,Contribuinte,Contato,Rua,Localidade,CodPostal,eMail,Telefone,RamoAtividade)
    VALUES 
    ('1','Pomar Verde, Lda.','111111110','Paulo Santos','Av. da Pátria, 23','Nação','1111-34A','paulo.santos@pomarverde.com','+351 980 098 876','1'),
    ('2','Quinta do Vale Alado','222222221','Ana Paiva','Rua Eng Pires da Silva, 89a','Pomares','2222-X22','anap@quintavale.com','+351 786 453 231','2'),
    ('3','Celeiros do Campo','333333331','Sofia Lazer','Rua Safira da Costa, 456, 2Dto','Pedras Preciosas','3333-F3G','sofia@celeiros.com','+351 456 432 123','3'),
    ('4','Carnes do Prado','444444441','Francisco Pereira','Trav. dos Bispos da Casa, 45','Igrejas','4444-S4A','fpgest@cprado.com','+351 654 321 786','5'),
    ('5','Peixaria Encantada ','555555551','Rosa Sardinha','Cais da Maré, 22','Ribeiras do Mar','55555-M55','rosas@encantada.com','+351 678 655 009','4'),
    ('6','Companhia dos Aviários','666666661','Francisco Pereira','Pr. Campo de Rosas, 1234','Avestos','6666-F6S','francisco@compavia.com','+351 567 675 432','5'),
    ('7','Armazém do Comércio','777777771','Evaristo Prado','Campo das Cebolas, 234, Armazém A','Vendas Velhas','7777-7TO','evaristo@armcomercio.com','+351 345 567 789','6')
    ;

-- Povoamento da tabela "Evento"
-- DESC Evento;
-- SELECT * FROM Evento;
-- DELETE FROM Evento;
INSERT INTO Evento
	(Fornecedor,Data,Descrição)
    VALUES 
    ('1','2022-01-04','Estabelecimento do contrato de fornecimento de bens.'),
    ('1','2022-02-05','Acordo para recolha de bens não comercializados.'),
    ('2','2022-01-11','Reclamação de lote de produtos danificados.'),
    ('4','2022-03-21','Visita à loja do gestor de marketing do fonecedor.')
    ;
    
-- Povoamento da tabela "Artigo"
-- DESC Artigo;
-- SELECT * FROM Artigo;
-- DELETE FROM Artigo;
INSERT INTO Artigo
    (Id,Descrição,Categoria,Preço,IVA,Desconto,Stock,QtVendida)
    VALUES
    ('01','Pão de Centeio 1un','1','0.10','23','0.00','50','0'),
    ('02','Pão de Milho 1un','1','0.20','23','0.00','20','0'),
	('03','Pão de Trigo 1un','1','0.05','23','0.00','150','0'),
	('04','Leite Magro 1lt','2','0.25','23','0.00','100','0'),
	('05','Leite Meio-Gordo 1lt','2','0.25','23','0.00','100','0'),
	('06','Leite Gordo 1lt','2','0.25','23','0.00','100','0'),
	('07','Leite com Chocolate 1lt','2','0.35','23','0.00','200','0'),
    ('08','Mortadela de Porco com Pimenta 100gr','3','0.80','23','0.00','100','0'),
    ('09','Fiambre de Porco (Perna) 100gr','3','1.00','23','0.00','300','0'),
    ('10','Mortadela de Perú com Azeitona 100gr','3','0.90','23','0.00','100','0'),
    ('11','Presunto 9 meses cura 200gr','3','3.50','23','0.00','75','0'),
    ('12','Batata Vermelha 1kg','4','0.80','23','0.00','30','0'),
    ('13','Salsa 100gr','4','0.30','23','0.00','20','0'),
    ('14','Batata Branca 1kg','4','0.80','23','0.00','30','0'),
    ('15','Cebolas Brancas 1kg','4','0.60','23','0.00','90','0'),
    ('16','Alhos 250gr','4','1.70','23','0.00','45','0'),
    ('17','Couve Portuguesa 1un','4','0.75','23','0.00','10','0'),
    ('18','Alface Frisada 1un','4','0.20','23','0.00','50','0'),
    ('19','Pimento Verde 1u','4','0.10','23','0.00','40','0'),
    ('20','Couves Bruxelas 0.5kg','4','1.00','23','0.00','15','0'),
    ('21','Bróculos 1kg','4','1.25','23','0.00','10','0'),
    ('22','Sardinha 0.5kg','5','1.75','23','0.00','10','0'),
    ('23','Camarão Médio  1kg','5','10.25','23','0.00','10','0'),
    ('24','Carapau  1kg','5','3.90','23','0.00','10','0'),
    ('25','Pescada  1kg','5','2.50','23','0.00','30','0'),
    ('26','Mexilhão  1kg','5','4.65','23','0.00','5','0'),
    ('27','Polvo  1kg','5','7.00','23','0.00','10','0'),
    ('28','Lulas 1kg','5','2.00','23','0.00','15','0'),
    ('29','Lavagante 1kg','5','40.00','23','0.00','5','0'),
    ('30','Carne de Porco - Escalopes 0.5kg','6','1.75','23','0.00','30','0'),
    ('31','Carne de Vaca - Costeletas 1.0kg','6','8.00','23','0.00','25','0'),
    ('32','Carne de Perú - Bifes 0.5kg','6','3.50','23','0.00','15','0'),
    ('33','Carne de Coelho - Inteiro 1kg','6','5.95','23','0.00','10','0'),
    ('34','Carne de Borrego - Inteiro 1kg','6','6.35','23','0.00','20','0'),
    ('35','Arroz Carolino 1kg','7','0.75','23','0.00','80','0'),
    ('36','Arroz Agulha 1kg','7','0.90','23','0.00','120','0'),
    ('37','Couscous 1kg','7','0.90','23','0.00','20','0'),
    ('38','Feijão Frade 1kg','7','0.30','23','0.00','30','0'),
    ('39','Feijão Manteiga 1kg','7','0.80','23','0.00','60','0'),
    ('40','Farinha de Trigo 1kg','7','1.00','23','0.00','175','0'),
    ('41','Farinha de Milho 0.5kg','7','0.70','23','0.00','75','0'),
    ('42','Laranja 1kg','8','0.90','23','0.00','50','0'),
    ('43','Maçã 1kg','8','0.50','23','0.00','100','0'),
    ('44','Pêra 1kg','8','0.70','23','0.00','70','0'),
    ('45','Manga 1kg','8','2.90','23','0.00','20','0'),
    ('46','Tangerina 1kg','8','0.75','23','0.00','60','0'),
    ('47','Pisa Napolitana 200gr','9','1.75','23','0.00','10','0'),
    ('48','Filetes de Peixe 500gr','9','5.24','23','0.00','15','0'),
    ('49','Rissóis 500gr','9','6.00','23','0.00','15','0'),
    ('50','Croquetes 250gr','9','3.00','23','0.00','25','0'),
    ('51','Sumo Laranja 1l','10','0.90','23','0.00','50','0'),
    ('52','Água Mineral 5l','10','1.00','23','0.00','100','0'),
    ('53','Cola Limão 1l','10','0.50','23','0.00','50','0'),
    ('54','Água Tónica 1l','10','0.80','23','0.00','20','0'),
    ('55','Gasosa 1l','10','0.20','23','0.00','20','0'),
    ('56','Sumo Maçã 1l','10','0.92','23','0.00','30','0'),
    ('57','Açucar Refinado 1Kg','11','0.70','23','0.00','50','0'),
    ('58','Adoçante granulado 200gr','11','0.90','23','0.00','40','0'),
    ('59','Chocolate Negro 200gr','11','1.50','23','0.00','20','0'),
    ('60','Cacau 250gr','11','2.00','23','0.00','10','0'),
    ('61','Maionese 200gr','12','1.00','23','0.00','100','0')
    ;

-- Povoamento da tabela "Promoção"
-- DESC Promoção;
-- SELECT * FROM Promoção;
-- DELETE FROM Promoção;
INSERT INTO Promoção
    (Artigo,Data,Desconto)
    VALUES 
    ('01','2022-01-01','10.00'),
    ('03','2022-01-10','15.00'),
    ('14','2022-01-21','12.50'),
    ('42','2022-02-01','7.70'),
    ('21','2022-02-04','5.00'),
    ('21','2022-03-02','5.00'),
    ('32','2022-03-23','10.00'),
    ('08','2022-03-23','5.00')
    ;
 
-- Povoamento da tabela "ArtigoFornecedor"
-- DESC ArtigoFornecedor;
-- SELECT * FROM ArtigoFornecedor;
-- DELETE FROM ArtigoFornecedor;
INSERT INTO ArtigoFornecedor
	(Artigo,Fornecedor,Desconto,Quantidade,Entrega,Preço,DataReferência)
    VALUES 
    ('12','1','10','100','3','0.60','2020-01-01'),
    ('13','1','10','20','3','0.20','2020-01-01'),
    ('14','1','10','100','3','0.65','2020-01-01'),
    ('15','1','10','50','3','0.40','2020-01-01'),
    ('14','2','20','200','4','0.60','2020-02-03'),
    ('15','2','20','100','3','0.50','2020-02-03'),
    ('16','2','10','50','2','1.30','2020-02-03'),
    ('35','3','5','150','7','0.68','2021-11-23'),
    ('38','3','10','50','6','0.20','2021-11-23'),
    ('40','3','5','250','4','0.75','2021-11-23'),
    ('41','3','15','170','7','0.60','2021-11-23'),
    ('30','4','8','50','2','1.50','2022-03-03'),
    ('32','4','7.5','50','2','2.50','2022-03-03'),
    ('33','4','10','50','2','5.20','2022-03-03'),
    ('34','4','5','50','2','5.80','2022-03-03'),
    ('22','5','5','25','2','1.30','2021-10-23'),
    ('24','5','5','35','2','3.50','2021-10-23'),
    ('25','5','5','20','2','2.20','2021-10-23'),
    ('27','5','5','10','2','6.30','2021-10-23'),    
    ('51','7','10','75','3','0.75','2021-12-12'),
    ('52','7','5','50','4','0.80','2021-12-12'),
    ('54','7','15','100','3','0.65','2021-12-12'),
    ('56','7','10','80','6','0.77','2021-12-12')
    ;

-- Povoamento da tabela "Venda"
-- DESC Venda;
-- SELECT * FROM Venda;
-- DELETE FROM Venda;
INSERT INTO Venda
	(Número,Data,Total,TotalComIva,Cliente,Funcionário)
    VALUES 
    ('01','2022-01-01','3.00','3.69','1','1'),
    ('02','2022-01-21','1.30','1.60','2','1'),
    ('03','2022-02-02','1.75','2.15','3','1'),
    ('04','2022-02-11','15.05','18.51','1','1'),
    ('05','2022-03-09','4.00','4.92','4','1'),
    ('06','2022-03-12','8.00','9.84','5','2'),
    ('07','2022-03-28','5.00','6.15','6','1'),
    ('08','2022-03-29','19.50','23.96','3','1'),
    ('09','2022-04-01','7.35','9.04','2','1'),    
    ('10','2022-04-02','11.25','13.84','8','2')
    ;

-- Povoamento da tabela "VendaArtigo"
-- DESC VendaArtigo;
-- SELECT * FROM VendaArtigo;
-- DELETE FROM VendaArtigo;
INSERT INTO VendaArtigo
	(Venda,Artigo,Quantidade,Preço,Valor,IVA)
    VALUES 
    ('01','01','10','0.10','1.00','23'),
    ('01','02','10','0.20','2.00','23'),
    ('02','19','5','0.10','0.50','23'),
    ('02','13','1','0.30','0.30','23'),
    ('02','03','10','0.05','0.50','23'),    
    ('03','22','1','1.75','1.75','23'),
    ('04','01','5','0.10','0.50','23'),
    ('04','41','10','0.70','7.00','23'),
    ('04','26','1','4.65','4.65','23'),
    ('04','45','1','2.90','2.90','23'),
    ('05','08','5','0.80','4.00','23'),
    ('06','12','10','0.80','8.00','23'),
    ('07','21','4','1.25','5.00','23'),
    ('08','31','2','8.00','16.00','23'),
    ('08','22','2','1.75','3.50','23'),
    ('09','44','2','0.70','1.40','23'),
    ('09','33','1','5.95','5.95','23'),
    ('10','11','1','3.50','3.50','23'),
    ('10','21','3','1.25','3.75','23'),
    ('10','31','0.5','8.00','4.00','23')
    ;

-- Povoamento da tabela "Compra"
-- DESC Compra;
-- SELECT * FROM Compra;
-- DELETE FROM Compra;
INSERT INTO Compra
	(Número,DataEmissão,DataEntrega,NrArtigos,Valor,Funcionário,Fornecedor)
    VALUES 
    ('1','2022-02-28','2022-03-15','1','6.00','1','1'),
    ('2','2022-03-21','2022-03-30','2','31.00','1','2'),
    ('3','2022-04-01','2022-04-10','2','11.20','1','3')
    ;

-- Povoamento da tabela "CompraArtigo"
-- DESC CompraArtigo;
-- SELECT * FROM CompraArtigo;
-- DELETE FROM CompraArtigo;
INSERT INTO CompraArtigo
	(Compra,Artigo,Quantidade,Preço)
    VALUES 
    ('1','12','10','0.60'),
	('2','15','10','0.50'),
    ('2','16','20','1.30'),
    ('3','35','15','0.68'),
    ('3','38','5','0.20')
	;

-- Povoamento da tabela "Entrega"
-- DESC Entrega;
-- SELECT * FROM Entrega;
-- DELETE FROM Entrega;
INSERT INTO Entrega
	(Fornecedor,Compra,Artigo,Data,Quantidade)
	VALUES
    ('1','1','12','2022-03-15','10'),
	('2','2','15','2022-03-30','10'),
    ('2','2','16','2022-03-30','20'),
    ('3','3','35','2022-04-10','15'),
    ('3','3','38','2022-04-10','5')
	;
    
-- <fim>
-- Belo, O. 2022
--

 
 
