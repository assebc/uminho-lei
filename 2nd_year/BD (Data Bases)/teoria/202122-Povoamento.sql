--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
-- SQL 
--
-- Q U E R I E S
-- Operações de Manipulacao de Dados.
-- Povoamento da base de dados.
-- Exemplos de Aplicação.
-- Exercícios apresentados nas aulas.
-- Belo, O., 2021.
--

-- Indicação da base de dados de trabalho.
USE CozinhaAM;

-- Povoamento das tabelas do esquema da base de dados.
-- Utilização da instrução I N S E R T.
-- Povoamento incial da tabela "TiposReceita"
-- SELECT * FROM TiposReceita;
INSERT INTO TiposReceita
	(Id, Descrição)
    Values ('1','Entrada');
INSERT INTO TiposReceita
	(Descrição, Id)
    Values ('Prato de Carne','2');
INSERT INTO TiposReceita
    Values ('3','Aperitivo');
INSERT INTO TiposReceita
	(Id, Descrição)
    VALUES 
		('4','Prato de Peixe'),
		('5','Sobremesa');

-- Povoamento incial da tabela "Receita"
-- SELECT * FROM Receita  WHERE Tipo = '2';
INSERT INTO Receita
	(Id, Designação, Custo, Foto, Tipo)
    VALUES ('3','Arroz de Pato','12.50',NULL,'2');
INSERT INTO Receita
	(Id, Designação,Tipo)
    VALUES 
    ('4','Bacalhau com Todos','4'),
    ('5','Bife da Casa','3'),
    ('6','Pescada Cozida com Grelos','4');
    
-- Alteração de registos de tabelas do esquema da base de dados.
-- Utilização da instrução U P D A T E.
--
UPDATE Receita
	SET Tipo = '2'
    WHERE Id='5';


-- Remoção de registos de tabelas do esquema da base de dados.
-- Utilização da instrução D E L E T E.
--
DELETE FROM Receita
	WHERE Id = '5';

--
-- <fim>
-- Belo, O., 2021

