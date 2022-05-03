-- -- 
-- Universidade do Minho
-- Disciplina de Bases de Dados
-- A Linguagem SQL
-- Descrição de Dados
-- Caso de Estudo: A Mercearia da D. Acácia
-- Implementação do Esquema Global - Vista de Vendas e Vista de Compras integradas
-- MySQL 8.0.28 (MySQL Community Server GPL)
-- 2022, Março/Abril
-- --

-- Criação da Base de Dados
-- DROP DATABASE Mercearia;
-- CREATE DATABASE Mercearia;
-- ou
-- CREATE SCHEMA Mercearia;
-- ou com algumas opções de configuração 
CREATE DATABASE Mercearia
	DEFAULT CHARSET=utf8mb4
    DEFAULT ENCRYPTION='N';

-- Indicação da base de dados de trabalho
USE Mercearia;

-- Criação das tabelas da base de dados
--
-- Criação da Tabela "Profissão"
-- DROP TABLE Profissão;
-- DESC Profissão;
CREATE TABLE Profissão (
    Id INT NOT NULL,
    Descrição VARCHAR(75) NOT NULL,
		PRIMARY KEY (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Função"
-- DROP TABLE Função;
-- DESC Função;
CREATE TABLE Função (
    Id INT NOT NULL,
    Descrição VARCHAR(75) NOT NULL,
		PRIMARY KEY (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Categoria"
-- DROP TABLE Categoria;
-- DESC Categoria;
CREATE TABLE Categoria (
    Id INT NOT NULL,
    Descrição VARCHAR(75) NOT NULL,
		PRIMARY KEY (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "RamoAtividade"
-- DROP TABLE RamoAtividade;
-- DESC RamoAtividade;
CREATE TABLE RamoAtividade (
    Id INT NOT NULL,
    Descrição VARCHAR(75) NOT NULL,
		PRIMARY KEY (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Funcionário"
-- DROP TABLE Funcionário;
-- DESC Funcionário;
CREATE TABLE Funcionário (
    Id INT NOT NULL,
    Nome VARCHAR(75) NOT NULL,
    Função INT NULL,
    Password VARCHAR(75) NOT NULL,
    eMail VARCHAR(150) NOT NULL,
		PRIMARY KEY (Id),
		FOREIGN KEY (Função) 
			REFERENCES Função(Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Cliente"
-- DROP TABLE Cliente;
-- DESC Cliente;
CREATE TABLE Cliente (
    Id INT NOT NULL,
    Nome VARCHAR(75) NOT NULL,
    Profissão INT NULL,
    Contribuinte INT NOT NULL,
    DataNascimento DATE NULL,
    Dívida DECIMAL(8,2) NOT NULL DEFAULT '0.00',
    Rua VARCHAR(100) NOT NULL,
    Localidade VARCHAR(75) NOT NULL,
    CodPostal VARCHAR(75) NOT NULL,
    Pontos INT NOT NULL DEFAULT '0.00',
    eMail VARCHAR(150),
		PRIMARY KEY (Id),
		UNIQUE KEY Contribuinte (Contribuinte),
		UNIQUE KEY eMail (eMail),
		FOREIGN KEY (Profissão) 
			REFERENCES Profissão(Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Telefone"
-- DROP TABLE Telefone;
-- DESC Telefone;
CREATE TABLE Telefone (
    Cliente INT NOT NULL,
    Telefone VARCHAR(50) NOT NULL,
		PRIMARY KEY (Cliente, Telefone),
		FOREIGN KEY (Cliente) 
			REFERENCES Cliente(Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Recomendação"
-- DROP TABLE Recomendação;
-- DESC Recomendação;
CREATE TABLE Recomendação (
    Cliente INT NOT NULL,
    ClienteRecomendado INT NOT NULL,
    Pontos INT NOT NULL DEFAULT '0',
		PRIMARY KEY (Cliente, ClienteRecomendado),
		FOREIGN KEY (Cliente) 
			REFERENCES Cliente(Id),
		FOREIGN KEY (ClienteRecomendado) 
			REFERENCES Cliente(Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Fornecedor"
-- DROP TABLE Fornecedor;
-- DESC Fornecedor;
CREATE TABLE Fornecedor (
    Id INT NOT NULL,
    Designação VARCHAR(100) NOT NULL,
    Contribuinte INT NOT NULL,
    Contato VARCHAR(200) NOT NULL,
    CodPostal VARCHAR(75) NOT NULL,
    Localidade VARCHAR(75) NOT NULL,
    Rua VARCHAR(100) NOT NULL,
    eMail VARCHAR(150) NOT NULL,
    Telefone VARCHAR(50) NOT NULL,
    RamoAtividade INT NOT NULL,
		PRIMARY KEY (Id),
        FOREIGN KEY (RamoAtividade) 
			REFERENCES RamoAtividade(Id)
)
 	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Evento"
-- DROP TABLE Evento;
-- DESC Evento;
CREATE TABLE Evento (
    Fornecedor INT NOT NULL,
    Data DATETIME NOT NULL,
    Descrição TEXT NOT NULL,
		PRIMARY KEY (Fornecedor, Data),
        FOREIGN KEY (Fornecedor) 
			REFERENCES Fornecedor(Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Artigo"
-- DROP TABLE Artigo;
-- DESC Artigo;
CREATE TABLE Artigo (
    Id INT NOT NULL,
    Stock DECIMAL(6,2) NOT NULL DEFAULT '0',
    Categoria INT NULL,
    Descrição VARCHAR(100) NOT NULL,
    Preço DECIMAL(6,2) NOT NULL DEFAULT '0',
    IVA INT NOT NULL,
    Desconto DECIMAL(6,2) NOT NULL DEFAULT '0',
    QtVendida DECIMAL(6,2) NOT NULL DEFAULT '0',
		PRIMARY KEY (Id),
		FOREIGN KEY (Categoria) 
			REFERENCES Categoria (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;

-- Criação da Tabela "Promoção"
-- DROP TABLE Promoção;
-- DESC Promoção;
CREATE TABLE Promoção (
    Artigo INT NOT NULL,
    Data DATE NOT NULL,
    Desconto DECIMAL(6,2) NOT NULL DEFAULT '0',
		PRIMARY KEY (Artigo, Data),
		FOREIGN KEY (Artigo) 
			REFERENCES Artigo (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
 
-- Criação da Tabela "ArtigoFornecedor"
-- DROP TABLE ArtigoFornecedor;
-- DESC ArtigoFornecedor;
 CREATE TABLE ArtigoFornecedor (
    Artigo INT NOT NULL,
    Fornecedor INT NOT NULL,
    Desconto DECIMAL(5,2) NOT NULL DEFAULT '0',
    Quantidade DECIMAL(5,2) NOT NULL DEFAULT '0',
    Entrega INT NOT NULL,
    Preço DECIMAL(8,2) NOT NULL DEFAULT '0',
    DataReferência DATE NOT NULL,
		PRIMARY KEY (Artigo, Fornecedor),
		FOREIGN KEY (Artigo) 
			REFERENCES Artigo (Id),
		FOREIGN KEY (Fornecedor) 
			REFERENCES Fornecedor (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
    
-- Criação da Tabela "Venda"
-- DROP TABLE Venda;
-- DESC Venda;
CREATE TABLE Venda (
    Número INT NOT NULL,
    Data DATE NOT NULL,
    Total DECIMAL(8,2) NOT NULL DEFAULT '0',
    TotalComIVA DECIMAL(8,2) NOT NULL DEFAULT '0',
    Cliente INT NOT NULL,
    Funcionário INT NOT NULL,
		PRIMARY KEY (Número),
		FOREIGN KEY (Cliente) 
			REFERENCES Cliente (Id),
		FOREIGN KEY (Funcionário) 
			REFERENCES Funcionário (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
 
-- Criação da Tabela "VendaArtigo"
-- DROP TABLE VendaArtigo;
-- DESC VendaArtigo;
CREATE TABLE VendaArtigo (
    Venda INT NOT NULL,
    Artigo INT NOT NULL,
    Quantidade DECIMAL(6,2) NOT NULL DEFAULT '0',
    Preço DECIMAL(6,2) NOT NULL DEFAULT '0',
    Valor DECIMAL(8,2) NOT NULL DEFAULT '0',
    IVA INT NOT NULL,
		PRIMARY KEY (Venda, Artigo),
		FOREIGN KEY (Venda)
			REFERENCES Venda (Número),
		FOREIGN KEY (Artigo) 
			REFERENCES Artigo (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
    
-- Criação da Tabela "Compra"
-- DROP TABLE Compra;
-- DESC Compra;
CREATE TABLE Compra (
    Número INT  NOT NULL,
    DataEmissão DATE NOT NULL,
    DataEntrega DATE NOT NULL,
    NrArtigos INT NOT NULL,
    Valor DECIMAL(8,2) NOT NULL DEFAULT '0',
    Funcionário INT NOT NULL,
    Fornecedor INT NOT NULL,
		PRIMARY KEY (Número),
		FOREIGN KEY (Funcionário) 
			REFERENCES Funcionário (Id),
		FOREIGN KEY (Fornecedor) 
			REFERENCES Fornecedor (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
    
-- Criação da Tabela "CompraArtigo"
-- DROP TABLE CompraArtigo;
-- DESC CompraArtigo;
CREATE TABLE CompraArtigo (
    Compra INT NOT NULL,
    Artigo INT NOT NULL,
    Quantidade DECIMAL(6,2) NOT NULL DEFAULT '0',
    Preço DECIMAL(8,2) NOT NULL DEFAULT '0',
		PRIMARY KEY (Compra, Artigo),
		FOREIGN KEY (Compra) 
			REFERENCES Compra (Número),
		FOREIGN KEY (Artigo) 
			REFERENCES Artigo (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
    
-- Criação da Tabela "Entrega"
-- DROP TABLE Entrega;
-- DESC Entrega;
CREATE TABLE Entrega (
    Fornecedor INT NOT NULL,
    Compra INT NOT NULL,
    Artigo INT NOT NULL,
    Data DATE NOT NULL,
    Quantidade DECIMAL(6,2) NOT NULL DEFAULT '0',
		PRIMARY KEY (Fornecedor, Compra, Artigo),
		FOREIGN KEY (Fornecedor) 
			REFERENCES Fornecedor (Id),
		FOREIGN KEY (Compra) 
			REFERENCES Compra (Número),
		FOREIGN KEY (Artigo) 
			REFERENCES Artigo (Id)
)
	ENGINE=InnoDB 
    DEFAULT CHARSET=utf8mb4;
    
-- <fim>
-- Belo, O. 2022
--
