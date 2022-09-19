--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- C U R S O R E S
-- Definição e utilização
--
-- Exemplos de Aplicação.
-- Belo, O., 2020.
--

-- Base de Dados de Trabalho.
USE Sakila;

-- Exemplo 1
-- Envio de um cartão de "Boas Festas" a todos os clientes da Sakila.
-- DROP PROCEDURE spCartoesBoasFestas;
DELIMITER $$
CREATE PROCEDURE spCartoesBoasFestas 
	(OUT Cartoes VARCHAR(5000))
BEGIN
	DECLARE Fim INTEGER DEFAULT 0;
	DECLARE NomeCliente CHAR(75);
	-- Definição do cursor
	DEClARE csClientes CURSOR FOR 
		SELECT CONCAT(first_name,' ', last_name) AS Nome 
			FROM Customer
            WHERE Customer_Id IN (1,2,3)
			ORDER BY Nome ASC;
	-- Declaração do handler para deteção do final do cursor.
	DECLARE CONTINUE HANDLER 
		FOR NOT FOUND SET Fim = 1;
	-- Abertura e carregamento do cursor com os dados.
	OPEN csClientes;
	SET Cartoes ='';
	-- Travessia de todas as linhas do cursor.
	fazcartoes: LOOP
		-- Obtenção dos dados de uma linha do cursor.
		FETCH csClientes
			INTO NomeCliente;
		IF Fim = 1 THEN 
			LEAVE fazcartoes;
		END IF;
		-- Construção da lista com os cartoes de boas festas.
		SET Cartoes = CONCAT(Cartões,"Boas Festas ",NomeCliente,", Feliz Natal.\\");
	END LOOP fazcartoes;
	CLOSE csClientes;
END $$ 
DELIMITER ;

-- Execução do procedimento implementado.
CALL spCartoesBoasFestas(@Cartoes);
-- Intrução que representa o envio dos cartões aos vários clientes. :-)
SELECT @Cartoes;


-- <fim>
--
