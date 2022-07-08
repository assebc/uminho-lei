--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
-- SQL 
--
-- Q U E R I E S
-- Operações de Descrição de Dados.
-- Gestão de esquemas de bases de dados.
-- Exemplos de Aplicação.
-- Exercícios apresentados nas aulas.
-- Belo, O., 2021.
--

-- Criação do esquema físico da base de dados.
CREATE SCHEMA 
	IF NOT EXISTS cozinhaam 
    DEFAULT CHARACTER SET utf8;

-- Identificação de trabalho.
USE cozinhaam;

-- Criação das tabelas do esquema da base de dados.
-- Utilização da instrução C R E A T E   T A B L E.
-- Criação da tabela "TiposReceita".
--
CREATE TABLE IF NOT EXISTS TiposReceita (
	Id INT NOT NULL,
	Descrição VARCHAR(50) NOT NULL,
		PRIMARY KEY (Id)
	)
ENGINE = InnoDB;

-- Criação da tabela "Receita".
--
CREATE TABLE IF NOT EXISTS Receita (
	Id CHAR(5) NOT NULL,
	Designação VARCHAR(75) NOT NULL,
	Custo DECIMAL(8,2) NULL DEFAULT 0,
	Foto VARCHAR(150) NULL,
	Tipo INT NOT NULL,
		PRIMARY KEY (Id),
		FOREIGN KEY (Tipo)
			REFERENCES TiposReceita (Id))
ENGINE = InnoDB;

--
CREATE TABLE IF NOT EXISTS `mydb`.`Utensílio` (
  `Id` INT NOT NULL,
  `Nome` VARCHAR(75) NOT NULL,
  PRIMARY KEY (`Id`))
ENGINE = InnoDB;

--
CREATE TABLE IF NOT EXISTS `mydb`.`Ingrediente` (
  `Id` INT NOT NULL,
  `Nome` VARCHAR(75) NOT NULL,
  `Preço` DECIMAL(8,2) NULL DEFAULT 0,
  `Stock` DECIMAL(8,2) NULL DEFAULT 0,
  PRIMARY KEY (`Id`))
ENGINE = InnoDB;


--
CREATE TABLE IF NOT EXISTS ReceitaIngrediente (
	Receita CHAR(5) NOT NULL,
	Ingrediente INT NOT NULL,
	Quantidade DECIMAL(8,2) NOT NULL,
	PRIMARY KEY (Receita, Ingrediente),
	FOREIGN KEY (Receita)
		REFERENCES Receita (Id),
	FOREIGN KEY (Ingrediente)
		REFERENCES Ingrediente (Id)    
    )
ENGINE = InnoDB;

--
CREATE TABLE IF NOT EXISTS `mydb`.`ReceitaUtensílio` (
  `Receita` CHAR(5) NOT NULL,
  `Utensílio` INT NOT NULL,
  `Quantidade` DECIMAL(8,2) NOT NULL,
  PRIMARY KEY (`Receita`, `Utensílio`),
  INDEX `fk_ReceitaUtensílio_Utensílio1_idx` (`Utensílio` ASC) VISIBLE,
  CONSTRAINT `fk_ReceitaUtensílio_Receita1`
    FOREIGN KEY (`Receita`)
    REFERENCES `mydb`.`Receita` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_ReceitaUtensílio_Utensílio1`
    FOREIGN KEY (`Utensílio`)
    REFERENCES `mydb`.`Utensílio` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

--
CREATE TABLE IF NOT EXISTS `mydb`.`ReceitaProcesso` (
  `Receita` CHAR(5) NOT NULL,
  `Nr` INT NOT NULL,
  `Acção` VARCHAR(150) NOT NULL,
  PRIMARY KEY (`Receita`, `Nr`),
  CONSTRAINT `fk_ReceitaProcesso_Receita1`
    FOREIGN KEY (`Receita`)
    REFERENCES `mydb`.`Receita` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

-- Informação sobre os elementos do esquema criado.
-- Metadados de uma tabela.
--
DESC Receita;

-- Consulta da definição de uma tabela.
--
SHOW COLUMNS FROM Receita;

-- Consulta da definição de uma tabela no formato da instrução.
--
SHOW CREATE TABLE Receita;

-- Consulta da definição das chaves e dos índices de uma tabela.
--
SHOW KEYS FROM Receita;


-- Criação das tabelas do esquema da base de dados.
-- Utilização da instrução A L T E R   T A B L E.
-- Alteração do nome da tabela "".
ALTER TABLE Receita
    RENAME TO Receitas;

-- Adição de um novo atributo numa tabela.
--
ALTER TABLE TiposReceita
    ADD Observações TEXT NULL;

-- Adição simultânea de vários atributos numa tabela.
--
ALTER TABLE TiposReceita
    ADD ValorBase DECIMAL(10,2) NOT NULL DEFAULT 0
        AFTER Observações;

-- Modificação da definição de vários atributos de uma tabela.
--
ALTER TABLE TipopsReceita 
    MODIFY Observações VARCHAR(25) NOT NULL,
    MODIFY ValorBase DECIMAL(8,2) AFTER Descrição;

-- Modificação da definição de vários atributos de uma tabela.
--
ALTER TABLE Receita
    ADD Facebook VARCHAR(200);
ALTER TABLE Receita 
    CHANGE COLUMN Facebook Instagram VARCHAR(150) NULL;

-- Remoção de um atributo numa tabela.
--
ALTER TABLE Receita
    DROP COLUMN Facebook;
    
    
-- Remoção de tabelas do esquema da base de dados.
-- Utilização da instrução D R O P   T A B L E. 
-- Remoção da tabela "TiposReceita".
--
DROP TABLE TiposReceita;

--
-- <fim>
-- Belo, O., 2021






