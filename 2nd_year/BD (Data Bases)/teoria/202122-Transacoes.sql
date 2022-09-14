
--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- T R A N S A Ç Õ E S
--
-- Exemplos de Aplicação.
-- Belo, O., 2020.
--

-- Base de Dados de Trabalho.
USE Sakila;

-- Definição e utililação de transações.
-- Exemplo 1
-- Demonstrando os principais passos na realização de uma transação.

-- Instruções para preparação do exemplo de demonstração.
DESC staff;
--
SELECT *
	FROM staff;
-- Criacao de um novo registo na tabela "staff"
INSERT INTO staff
	(staff_id, first_name, last_name, address_id, email, store_id, active, username, password)
	VALUES(9, 'Nuno','Mankind',1, 'nuno9@sakilastaff.com', 2, 1, 'nuno', '658rpd65');

-- remocao do registo criado anteriormente.
DELETE FROM staff
	WHERE staff_id =9;

-- Definição da transação.
-- Atualização da informação do novo cliente criado.
-- Início da transação.
START TRANSACTION;
-- Verificar o estado inicial do registo.
SELECT * 
	FROM staff
	WHERE staff_id =9;
-- Realização de uma operação de modificação do registo.
UPDATE staff
	SET first_name = 'Nuna', last_name='Womankind'
	WHERE staff_id =9;
-- Verificar o estado final do registo.
SELECT * 
	FROM staff
	WHERE staff_id =9;
-- Desfazer a operação realizada.
ROLLBACK;


-- Verificar o estado do registo após a operação de ROLLBACK.
SELECT * 
	FROM staff
	WHERE staff_id =9;


-- Exemplo 2
-- Demonstrando os principais passos na realização de uma transação
-- envolvendo mais do que uma operação.

-- Instruções para preparação do exemplo de demonstração.
DESC Customer;
-- Alteração do esquema da tabela "customer"
ALTER TABLE Customer
	ADD RentalNrs INT NOT NULL DEFAULT 0;
--
DESC Staff;
-- Alteração do esquema da tabela "staff"
ALTER TABLE Staff
	ADD RentalNrs INT NOT NULL DEFAULT 0;
--
SELECT *
	FROM Customer
	WHERE Customer_id = 100;
SELECT *
	FROM Staff
	WHERE Staff_id = 1;
SELECT *
	FROM Inventory
	WHERE Inventory_id = 1;
SELECT *
	FROM Rental
	WHERE Customer_id = 1
	ORDER BY Rental_date DESC;
--
UPDATE Customer
	SET RentalNrs = 0
	WHERE Customer_Id = 100;
UPDATE Staff
	SET RentalNrs = 0
	WHERE Staff_Id = 1;


-- Definição da transação.
-- Inserção de um novo aluguer na base de dados, com atualização do
-- número de alugueres nas tabelas "customer" e "staff".
-- Início da transação
START TRANSACTION;
-- 1ª Operação - INSERT 
INSERT INTO Rental
	(Rental_date, Inventory_id, Customer_id, Return_date, Staff_id)
	VALUES(CURDATE(),2666,100,ADDDATE(CURDATE(), INTERVAL +8 DAY),1);

-- 2ª Operação - UPDATE
UPDATE Customer
	SET RentalNrs = RentalNrs +1
	WHERE Customer_Id = 100;

-- 3ª Operação - UPDATE 
UPDATE Staff
	SET RentalNrs = RentalNrs +1
	WHERE Staff_Id = 1;

-- Desfazer a operação realizada.
ROLLBACK;



-- Exemplo 3
-- Demonstrando os principais passos na realização de uma transação
-- envolvendo mais do que uma operação, com análise de erros e realização
-- da ação correspondente COMMIT ou ROLLBACK.
-- Utilização do caso de estudo anterior.
-- Criação de um procedimento.

-- DROP PROCEDURE spRegAluguer;
DELIMITER $$
CREATE PROCEDURE spRegAluguer 
	(IN Filme INT, Cliente INT, Staff INT)
BEGIN

	-- Declaração de um handler para tratamento de erros.
    DECLARE ErroTransacao BOOL DEFAULT 0;

    DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET ErroTransacao = 1;

	-- Início da transação
	START TRANSACTION;
	-- 1ª Operação - INSERT
	INSERT INTO Rental
		(Rental_date, Inventory_id, Customer_id, Return_date, Staff_id)
		VALUES(CURDATE(),Filme,Cliente,ADDDATE(CURDATE(), INTERVAL +8 DAY),Staff);
	-- 2ª Operação - UPDATE
	UPDATE Customer
		SET RentalNrs = RentalNrs +1
		WHERE Customer_Id = Cliente;
	-- 3ª Operação - UPDATE 
	UPDATE Staff
		SET RentalNrs = RentalNrs +1
		WHERE Staff_Id = Staff;
	-- Verificação da ocorrência de um erro.
    IF ErroTransacao THEN
		-- Desfazer as operações realizadas.
        ROLLBACK;
    ELSE
		-- Confirmar as operações realizadas.
        COMMIT;
    END IF;
END $$

-- Execução do procedimento implementado.
CALL spRegAluguer(1,100,1);


--
.. Utilização de SAVEPOINTS
-- Ilustração da sua aplicação
-- Instruções base
-- (...)

    DECLARE Fim INT DEFAULT 0;
    -- Declaração de um handler para o tratamento de exceções SQL.
    DECLARE CONTINUE HANDLER 
        FOR SQLEXCEPTION SET Erro = 1;   

    -- Definição do início da transação.
    START TRANSACTION;

    -- Definição de um savepoint.
    SAVEPOINT sp1;

    -- Remoção de registos
    DELETE FROM ...
    -- Inserção de novos registos
    INSERT INTO ...
        SELECT ...
        
	IF Erro = 1 THEN
        BEGIN
            -- Ocorreu um erro. 
            -- Coloca o estado da base igual ao que estava no momento da definição do savepoint em questão.
            ROLLBACK TO SAVEPOINT sp1;
            SET Erro = 0;
        END;
    END IF;
    
    -- Libertação da definiçao do savepoint sp1.
    RELEASE SAVEPOINT sp1;
  
    -- Definição de um segundo savepoint
    SAVEPOINT sp2;

    -- Remoção de registos.
    DELETE FROM ...
    -- Inserção de novos registos.
    INSERT INTO ...
    
    IF Erro = 1 THEN
        BEGIN
            -- Ocorreu um erro. 
            -- Coloca o estado da base igual ao que estava no momento da definição do savepoint em questão.
            ROLLBACK TO SAVEPOINT sp2;
            SET Erro = 0;
        END;
    END IF;
    
    RELEASE SAVEPOINT sp2;
    
    -- Atualização de dados.
    UPDATE ...
    
    IF Erro = 1 THEN
        ROLLBACK;
    ELSE 
        COMMIT;
    END IF;

(...)

--
-- <fim>




