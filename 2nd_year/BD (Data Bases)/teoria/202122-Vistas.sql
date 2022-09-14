--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- V I S T A S 
-- Operações de Descrição de Dados.
-- Criação, alteração e remoção de vistas.
--
-- Exemplos de Aplicação.
-- Belo, O., 2020, 2021.
--

-- Base de Dados de Trabalho.
USE Sakila;

--
-- VISTAS
CREATE VIEW Clientes 
AS
	SELECT Customer_id AS "Id", 
		CONCAT(First_Name,' ',Last_Name) AS "Nome", 
		Store_Id AS "Loja"
		FROM Customer;
--
DROP VIEW Clientes;
--    
SELECT *
	FROM Clientes;
    
-- Criacao da vista "vwEMailClientes"
CREATE VIEW vwEMailClientes AS
	SELECT 'C' AS Tipo, customer_id AS Nr, 
		first_name AS Nome, last_name AS Apelido, 
		email, 
		'______' AS Observacoes
		FROM Customer AS C;

-- Utilização da vista criada anteriormente
SELECT *
	FROM vwEMailClientes;

-- Utilização da vista criada com aplicação de filtros
SELECT *
	FROM vwEMailClientes
	WHERE Apelido LIKE 'Y%';

-- Utilizando a vista criada com aplicação de filtros e ordenação de resultados.
SELECT *
	FROM vwEMailClientes
	WHERE Apelido LIKE 'Y%'
	ORDER BY Apelido DESC;

-- Remoção da vista criada.
DROP VIEW vwEMailClientes;


-- Através da definição de uma vista, defina um objeto de dados que permita
-- criar uma única lista de emails dos clientes (customer) e dos funcionários (staff), 
-- fazendo a separação de cada registo consoante o tipo de contacto incorporado nesse objeto.
-- Criação da vista "vwListaEMails".
CREATE VIEW vwEMailsGeral AS
	SELECT 'C' AS Tipo, customer_id AS Nr, first_name AS Nome, last_name AS Apelido, 
		email
		FROM Customer
	UNION
	SELECT 'F', staff_id, first_name, last_name, email
		FROM Staff;

-- Exemplos da utilização da vista criada numa query.
-- Numa query simples.
SELECT *
	FROM vwEMailsGeral;

-- Numa query com critérios de filtragem e de ordenação.
SELECT Nr, Nome, Apelido, eMail
	FROM vwEMailsGeral
	WHERE Tipo = 'F'
	ORDER BY Nr;

-- Numa query com uma subquery e uma operação de junção.
SELECT *
	FROM (SELECT * 
			FROM vwEMailsGeral 
			WHERE Tipo = 'F') AS V 
		INNER JOIN Staff AS S
		ON V.Nr = S.Staff_Id;

-- Remoção da vista do sistema.
DROP VIEW vwEMailsGeral;


--
-- Criação de uma vista para fornecimento da informação geral relacionada com os
-- alugueres de films, que disponibilize elementos que permitem analisar os alugueres
-- realizados por calendário, cliente, cidade e filme.
-- Criação da vista "vwInfGeralALugueres".
-- SELECT * FROM vwInfGeralALugueres;
CREATE VIEW vwInfGeralALugueres AS
	SELECT 
		-- Dimension Data
		RT.Rental_Id, 
		DATE(RT.Rental_Date) AS Rental_Date,
		MONTH(RT.Rental_Date) AS Rental_Month, 
		QUARTER(RT.Rental_Date) AS Rental_Quarter, 
		YEAR(RT.Rental_Date) AS Rental_Year, 
		WEEK(RT.Rental_Date) AS Rental_Week, 
		RT.Staff_Id AS Employee_Id,
		concat(ST.first_name," ",ST.last_name) AS Employee_Name,
		CL.Customer_id AS Customer_Id, 
		concat(CL.first_name," ",CL.last_name) AS Customer_Name, 
		CT.City AS Customer_City,
		ST.store_id AS Store_Id,
		FI.film_id AS Film_Id,
		FI.title AS Film_Title,
		FI.Release_Year AS Film_Release_Year,
		FI.Rating AS Film_Rating, 
		-- Measure data
		'1' AS Rental_Units,
		PY.Amount AS Rental_Value
			FROM Customer AS CL 
				INNER JOIN Address AS AD
				ON CL.Address_id=AD.Address_id
					INNER JOIN City AS CT
					ON AD.City_Id=CT.City_Id
						INNER JOIN Rental AS RT
							ON CL.Customer_Id = RT.Customer_Id
							INNER JOIN Staff AS ST
								ON RT.Staff_Id = ST.Staff_Id
								INNER JOIN Inventory AS IV
									ON RT.inventory_id=IV.inventory_id
									INNER JOIN Film AS FI
										ON IV.film_id=FI.film_id
										INNER JOIN Payment AS PY
											ON RT.rental_id=PY.rental_id;

-- Remoção da vista "vwInfGeralALugueres".
DROP VIEW vwInfGeralALugueres;

-- <fim>
--

