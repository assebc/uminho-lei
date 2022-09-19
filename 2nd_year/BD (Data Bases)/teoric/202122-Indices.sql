--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- Í N D I C E S 
-- Operações de Descrição de Dados.
-- Criação, alteração e remoção de índices.
--
-- Exemplos de Aplicação.
-- Belo, O., 2020, 2021.
--

-- Indicação da Base de Dados de Trabalho.
USE Sakila;

--
-- Criacao de um índice (INDEX) sobre o atributo "rental_date" da tabela "rental".
CREATE INDEX idxRentalDate 
	ON rental (rental_date);

--
-- Criacao de um índice único sobre o atributo "email" da tabela "customer".
CREATE UNIQUE INDEX idxEMail 
	ON customer (email);

--
-- Criacao de um índice composto (mais do que um atributo) sobre a tabela "payment".
CREATE INDEX idxCustomerRental
	ON payment (customer_id, rental_id);

--
-- Visualizacao dos índices definidos sobre a tabela 'rental'.
SHOW INDEX FROM rental;
SHOW INDEX FROM customer;
SHOW INDEX FROM payment;

--
-- Remoção de todos os índices criados anteriormente.
DROP INDEX idx_RentalDate ON rental;
DROP INDEX idx_eMail ON customer;
DROP INDEX idx_CustomerRental ON payment;

--
-- Visualizacao de todos os índices criados sobre as tabelas da base de dados "Sakila".
-- Utilização de uma vista do sistema - INFORMATION_SCHEMA.STATISTICS
SELECT DISTINCT TABLE_NAME, INDEX_NAME
	FROM INFORMATION_SCHEMA.STATISTICS
	WHERE TABLE_SCHEMA = 'Sakila';

--
-- <fim>






