--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- P R O C E D I M E N T O S
-- F U N C O E S
-- G A T I L H O S
-- Operações de Descrição de Dados.
-- Criação, alteração e remoção de gatilhos, procedimentos armazenados e funções.
--
-- Exemplos de Aplicação.
-- Belo, O., 2020, 2021.
--

-- Indicação da Base de Dados de Trabalho.
USE Sakila;


--
-- P R O C E D I M E N T O S
-- Criacao de um procedimento para nos indicar os 5 maiores pagamentos realizados
-- e respetivos clientes.
DELIMITER $$
CREATE PROCEDURE sp5TopPagamentos()
BEGIN
	SELECT P.payment_id, P.amount, C.first_name, C.last_name 
		FROM payment AS P INNER JOIN customer AS C
			ON P.customer_id=C.customer_id
		ORDER BY amount DESC
		LIMIT 5;
END $$

--
-- Execucao do procedimento "sp5TopPagamentos".
CALL sp5TopPagamentos;

--
-- Remocao do procedimento "sp5TopPagamentos" do sistema.
DROP PROCEDURE sp5TopPagamentos;

--
-- Criacao de um procedimento para nos indicar os 3 melhores clientes de uma loja 
-- da "Sakila".
-- Utilização de parâmetros de entrada.
DELIMITER $$
CREATE PROCEDURE sp3TopClientesLoja 
	(IN NrLoja INT)
BEGIN
	SELECT S.store_id AS "Loja", 
		CONCAT(C.first_name,' ',C.last_name) AS Cliente, 
		SUM(P.amount) AS "Valor Pago" 
		FROM payment AS P INNER JOIN customer AS C
			ON P.customer_id=C.customer_id
			INNER JOIN staff AS F
				ON F.staff_id=P.staff_id
				INNER JOIN store AS S
					ON F.store_id=S.store_id
		WHERE S.store_id = NrLoja
		GROUP BY CONCAT_WS(' ',C.first_name, C.last_name)
		ORDER BY SUM(P.amount) DESC
		LIMIT 3;
END $$

--
-- Execucao do procedimento "sp3TopClientesLoja".
CALL sp3TopClientesLoja(1);
CALL sp3TopClientesLoja(2);
CALL sp3TopClientesLoja(3);

--
-- Remocao do procedimento "sp3TopClientesLoja" do sistema.
DROP PROCEDURE sp3TopClientesLoja;

--
-- Criação da tabela "Calendar".
CREATE TABLE Calendar (
	Id DATE NOT NULL,
	DayName VARCHAR(10) NOT NULL,
	MonthName VARCHAR(15) NOT NULL,
	Week INT NOT NULL,
	Quarter INT NOT NULL,
	PRIMARY KEY (Id))
ENGINE = InnoDB;

-- Consulta dos metadados de uma tabela.
DESC Calendar;

--
DROP TABLE Calendar;


-- Geração de um calendário.
-- Utilização de parâmetros de entrada.
DELIMITER $$
CREATE PROCEDURE spCalendarioN30D 
	(IN DataInicio DATE, IN NrDias INT)
BEGIN
	DECLARE DataFim DATE;
	SET DataFim = ADDDATE(DataInicio, INTERVAL +NrDias DAY);
	SET SQL_SAFE_UPDATES = 0;
	TRUNCATE TABLE Calendar;
	WHILE DataInicio  <= DataFim DO
		INSERT INTO Calendar	
			(Id,DayName,MonthName,Week,Quarter)
			VALUES(DataInicio,DAYNAME(DataInicio),MONTHNAME(DataInicio),WEEK(DataInicio),QUARTER(DataInicio));
		SET  DataInicio = ADDDATE(DataInicio, INTERVAL +1 DAY); 
	END WHILE;
	SET SQL_SAFE_UPDATES = 1;
	SELECT *
		FROM Calendar;
END $$

--
CALL spCalendarioN30D('2016-01-01', 60);
SELECT * FROM Calendar;

--
DROP PROCEDURE spCalendarioN30D; 

-- Modificação do esquema de uma tabela.
ALTER TABLE Calendar
	ADD Weekend CHAR(1) DEFAULT NULL;

--
DESC Calendar;

--
DROP PROCEDURE spCalendarioN30D; 

--
-- Geração de um calendário - Versão 2, com registo do fim de semana.
DELIMITER $$
CREATE PROCEDURE spCalendarioN30DWE 
	(IN DataInicio DATE, IN NrDias INT)
BEGIN
	DECLARE DataFim DATE;
	DECLARE FimDeSemana CHAR(1);
	SET DataFim = ADDDATE(DataInicio, INTERVAL +NrDias DAY);
	SET SQL_SAFE_UPDATES = 0;
	TRUNCATE TABLE Calendar;
	WHILE DataInicio  <= DataFim DO
		IF DAYNAME(DataInicio) = 'Saturday' OR
		   DAYNAME(DataInicio) = 'Sunday'
		THEN
			SET FimDeSemana = 'S';
		ELSE 
			SET FimDeSemana = 'N';
		END IF;
		INSERT INTO Calendar	
			(Id,DayName,MonthName,Week,Quarter,Weekend)
			VALUES(DataInicio,DAYNAME(DataInicio),MONTHNAME(DataInicio),WEEK(DataInicio),
					QUARTER(DataInicio),FimDeSemana);
		SET  DataInicio = ADDDATE(DataInicio, INTERVAL +1 DAY); 
	END WHILE;
	SET SQL_SAFE_UPDATES = 1;
	SELECT *
		FROM Calendar;
END $$

--
CALL spCalendarioN30DWE('2016-01-01', 60);
SELECT * FROM Calendar;

--
DROP PROCEDURE spCalendarioN30DWE; 


--
-- Geração de um calendário - Versão, com mudanças de estruturas de controlo. 
DELIMITER $$
CREATE PROCEDURE spCalendarioN30DWE2 
	(IN DataInicio DATE, IN NrDias INT)
BEGIN
	DECLARE DataFim DATE;
	DECLARE FimDeSemana CHAR(1);
	SET DataFim = ADDDATE(DataInicio, INTERVAL +NrDias DAY);
	SET SQL_SAFE_UPDATES = 0;
	TRUNCATE TABLE Calendar;
	REPEAT 
		CASE DAYNAME(DataInicio)
			WHEN 'Saturday' THEN SET FimDeSemana = 'S';
			WHEN 'Sunday'THEN SET FimDeSemana = 'S';
			ELSE
				BEGIN
					SET FimDeSemana = 'N';
				END;
		END CASE;
		INSERT INTO Calendar	
			(Id,DayName,MonthName,Week,Quarter,Weekend)
			VALUES(DataInicio,DAYNAME(DataInicio),MONTHNAME(DataInicio),WEEK(DataInicio),
					QUARTER(DataInicio),FimDeSemana);
		SET  DataInicio = ADDDATE(DataInicio, INTERVAL +1 DAY); 
	UNTIL DataInicio > DataFim END REPEAT;
	SET SQL_SAFE_UPDATES = 1;
	SELECT *
		FROM Calendar;
END $$

--
CALL spCalendarioN30DWE2('2016-01-01', 60);

--
DROP PROCEDURE spCalendarioN30DWE2 


--
-- F U N C O E S
-- Criação de uma funcao que indica o email de um cliente dado o seu número de cliente.
DELIMITER $$
CREATE FUNCTION fuEMailCliente
	(NrCliente INT)
	RETURNS VARCHAR(75)
    DETERMINISTIC
BEGIN
	DECLARE eMailCliente VARCHAR(75); 
	SELECT email INTO eMailCliente
		FROM customer
		WHERE customer_id = NrCliente;
    RETURN eMailCliente;
END $$

-- Invocacao da funcao "fuEMailCliente".
SELECT fuEMailCliente(1);

-- Remocao da funcao "fuEMailCliente" do sistema.
DROP FUNCTION fuEMailCliente;


-- G A T I L H O S (Triggers).
-- Criação de uma funcao que indica o email de um cliente dado o seu número de cliente.

--
ALTER TABLE Customer
	ADD RentalNrs INT NOT NULL DEFAULT 0;

--
DESC customer;

--
DROP PROCEDURE spActNrAlugueresCliente;

--
DELIMITER $$
CREATE PROCEDURE spActNrAlugueresCliente
	(IN NrCliente INT)
BEGIN
	UPDATE customer
		SET RentalNrs = (SELECT COUNT(*) FROM rental WHERE Customer_Id = NrCliente)
		WHERE Customer_Id = NrCliente;
	SELECT customer_id, rentalnrs
		FROM customer 
		WHERE Customer_Id = NrCliente;

END $$

--
CALL spActNrAlugueresCliente(1);

--
SELECT customer_id, rentalnrs
	FROM customer 
	WHERE Customer_Id = 1;

--
DELIMITER $$
CREATE TRIGGER tgActINrAlugueresCliente 
	AFTER INSERT ON rental
	FOR EACH ROW
BEGIN
	UPDATE customer
		SET RentalNrs = RentalNrs + 1
		WHERE Customer_Id = NEW.Customer_Id;
END $$

--
DESC customer;

--
DELIMITER $$
CREATE TRIGGER tgActRNrAlugueresCliente 
	AFTER DELETE ON rental
	FOR EACH ROW
BEGIN
	UPDATE customer
		SET RentalNrs = RentalNrs - 1
		WHERE Customer_Id = OLD.Customer_Id;
END $$

-- Istruções necessárias para a demonstração da atuação do gatilho criado.
INSERT INTO rental
	(rental_date, inventory_id, customer_id, return_date, staff_id)
	VALUES(CURDATE(),2666,103,ADDDATE(CURDATE(), INTERVAL +8 DAY),1);

--
INSERT INTO rental
	(rental_date, inventory_id, customer_id, return_date, staff_id)
	VALUES(CURDATE(),1,1,ADDDATE(CURDATE(), INTERVAL +8 DAY),1);

--
SELECT * 
	FROM rental
	WHERE customer_id = 1
	ORDER BY rental_id DESC
	LIMIT 5;

--
SELECT customer_id, rentalnrs
	FROM customer 
	WHERE Customer_Id = 1;

--
-- <fim>
