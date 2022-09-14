--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
-- SQL 
--
-- Q U E R I E S
-- Operações de Manipulacao de Dados.
-- Queries simples e complexas.
-- Exemplos de Aplicação.
-- Exercícios apresentados nas aulas.
-- Belo, O., 2020, 2021.
--

-- Indicação da base de dados de trabalho.
USE Sakila;

-- Consulta de todo o conteúdo da tabela "Customer"
SELECT *
	FROM Customer;

-- Consulta de todo o conteúdo da tabela "Customer", com indicação do esquema
-- à qual pertence.

SELECT *
	FROM Sakila.Customer;
SELECT *
	FROM Northwind.Customers;
SELECT *
	FROM World.City;

-- Consulta de todo o conteúdo das tabelas "Country", "City" e "Address".
SELECT *
	FROM Country;
--
SELECT *
	FROM City;
--
SELECT *
	FROM Address;

-- Outros tipos de utilização da instrução SELECT
-- Visualização de uma constante.
SELECT 1;
SELECT '1';
SELECT 'Olá Mundo!' AS "Mensagem";

-- Realização do calculo de uma expressao matemática.
SELECT 1 + 2 * 3 AS Resultado;

-- Utilização da funcao PI(), que nos fornece o valor da constante matemática pi.
SELECT PI();

-- Utilização da funcao SIN(), que nos fornece o seno de um dado valor.
SELECT SIN(90);

-- Visualização da string °A Linguagem SQL é um mundo!".
SELECT 'A Linguagem SQL é um mundo!' AS Obs;

-- Utilização da funcao NOW(), que nos fornece a data e a hora atuais do sistema.
SELECT NOW();

-- Utilização da funcao CURDATE(), que nos fornece a data atual do sistema.
SELECT CURDATE();


-- Queries com filtragem de dados.
-- Uma query com seleção de atributos e critério de filtragem.
--
SELECT *
	FROM Customer
	WHERE C.customer_id = 1;

--
SELECT 
	C.last_name AS Ultimo, C.email AS Correio, 
	C.customer_id AS Id, C.first_name AS Primeiro 
	FROM Customer AS C
	WHERE C.customer_id = 1;

--
SELECT first_name, last_name, email
	FROM Customer
	WHERE customer_id = 1 OR 
    customer_id =2 OR
	customer_id = 3 OR 
	customer_id =4;

-- Utilização do operador IN
SELECT customer_id, first_name, last_name, email
	FROM Customer
	WHERE customer_id IN (1,2,3,4,5);

-- Utilizando o operador NOT juntamente com o operador IN
SELECT customer_id, first_name, last_name, email
	FROM Customer
	WHERE customer_id NOT IN (1,8,3,4,12);
    
-- Uma range query - uma querie com filtragem de um conjunto de valores entre 
-- dois limites 
SELECT customer_id, first_name, last_name, email
	FROM Customer
	WHERE customer_id >= 1 AND customer_id <= 5;

-- Utilização do operador BETWEEN
SELECT customer_id, first_name, last_name, email
	FROM Customer
	WHERE customer_id BETWEEN 1 AND 5;

-- Conjugação dos peradores NOT, IN e OR numa expressão de filtragem 
SELECT customer_id, first_name, last_name, email, address_id
	FROM Customer
	WHERE customer_id NOT IN (1,5,22) OR address_id = 1;

-- Consulta de uma lista de eMails de clientes - "customer"
SELECT customer_id, first_name, last_name, email
	FROM Customer;

-- Consulta de uma lista de eMails de funcionários - "staff", com ordenação
-- dos registos da tabela resultante.
SELECT staff_id, first_name, last_name, email
	FROM Staff
    WHERE staff_id IN (1,2,3)
	ORDER BY last_name ASC;

-- Consulta de uma lista de eMails de funcionários - "staff", com ordenação
-- dos seus resultados segundo dois atributos.
SELECT staff_id, first_name, last_name, email
	FROM Staff
	ORDER BY last_name, first_name DESC;


-- Utilização da instrução UNION
-- Consulta de uma lista de eMails de clientes - "customer" -  e 
-- funcionários - "staff" simultneamente.
SELECT customer_id, first_name, last_name, email
	FROM Customer
UNION
SELECT staff_id, first_name, last_name, email
	FROM Staff;

-- Complemento da query anterior com alguma "cosmética" para realce dos resultados.
SELECT 'C' AS Tipo, customer_id AS "Nr Cliente", 
	first_name AS Nome, last_name AS Apelido, 
	email, '______' AS Observacoes
	FROM Customer
UNION
SELECT 'F', staff_id, first_name, last_name, email, '______'
	FROM Staff;

-- Utilização da instrução UNION para juntar dados provenientes de duas tabelas
-- integradas em esquemas de bases de dados diferentes - "Sakila" e "Northwind".
SELECT 'Sak' AS BaseDados, customer_id AS NrCliente, last_name AS Primeiro, 
	first_name AS Ultimo, NOW() 
	FROM Sakila.Customer
UNION
SELECT 'Nor', id, last_name, first_name, NOW()
	FROM Northwind.Customers;

--
SELECT 'S' AS "Base",Customer_Id AS "Id", CONCAT(First_Name,' ',Last_Name) AS "Nome"
	FROM Sakila.Customer
UNION 
SELECT 'N', Id, CONCAT(first_name,' ',last_name)
	FROM Northwind.Customers;


-- Utilização de subqueries.
-- Utilização da query anterior como sub-query de uma outra, com ordenação
-- dos resultados.
--
SELECT Customer_Id AS Identificador, 
	CONCAT(First_Name,' ', Last_Name) AS Nome
	FROM Customer
    WHERE Customer_ID NOT IN (1,2,3)
    ORDER BY Nome ASC;
--
SELECT Customer_Id AS Identificador, 
	CONCAT(First_Name,' ', Last_Name) AS Nome
	FROM Customer
    WHERE Customer_ID NOT IN (
		SELECT Customer_ID 
			FROM Customer
            WHERE Customer_id IN (1,2,3))
	ORDER BY Nome ASC;

--
-- Utilização de subqueries numa operação de união de resultados.
SELECT *
FROM (
	SELECT 'C' AS Tipo, customer_id AS Nr, 
		first_name AS Nome, last_name AS Apelido, 
		email, '______' AS Observacoes
		FROM Customer AS C
	UNION
	SELECT 'F', staff_id, first_name, last_name, email, '______'
		FROM Staff AS S) AS T
ORDER BY Nome, Apelido ASC;

-- Utilização do operador LIKE.
--
SELECT *
	FROM customer
	WHERE email LIKE 'ja_'
	ORDER BY email;

SELECT *
	FROM customer
	WHERE email LIKE '%@%'
	ORDER BY email;

SELECT *
	FROM customer
	WHERE email LIKE 'a%@%.org'
	ORDER BY email;

SELECT *
	FROM customer
	WHERE email LIKE 'ja___.RICE%'
	ORDER BY email;

--
SELECT *
	FROM City
    WHERE City NOT LIKE '%r_d%';

-- com NOT
SELECT *
	FROM customer
	WHERE email NOT LIKE 'ja___.RICE%'
	ORDER BY email;

--
SELECT *
	FROM City
	WHERE city LIKE 'P%';

-- Utilização do operador IS
-- Análise de valores nulos (NULL) numa query.
SELECT *
	FROM customer
	WHERE email IS NULL;

--
SELECT *
	FROM customer
	WHERE email IS NOT NULL;

-- Utilização da função de agregação COUNT().
SELECT COUNT(*)
	FROM customer;

--
SELECT COUNT(customer_id) AS "Nr de Clientes"
	FROM customer;

-- Utilização da função de agregação COUNT(), SUM(), MAX(), MIN() e AVG().
SELECT COUNT(*), SUM(amount), MAX(amount), 
	MIN(amount), AVG(amount)
	FROM payment;

-- 
SELECT COUNT(*), SUM(amount), MAX(amount), 
	MIN(amount), AVG(amount)
	FROM payment
	WHERE customer_id IN (1,2,3);

-- Utilização da clausula GROUP BY, com limitação de valores e ordenação 
-- de resultados.
SELECT customer_id AS NrCliente, 
	COUNT(*) AS NrPagamentos, 
	SUM(amount) AS TotalPagamentos, 
	MAX(amount) AS MaiorPagamento, 
	MIN(amount) AS MenorPagamento, 
	AVG(amount) AS MédiaPagaments
	FROM payment
	GROUP BY customer_id    
    ORDER BY SUM(amount) DESC
	LIMIT 10;
    
--
SELECT CONCAT(first_name, ' ', last_name) AS Cliente, 
	COUNT(*) AS NrPagamentos, 
	SUM(amount) AS TotalPagamentos, 
	MAX(amount) AS MaiorPagamento, 
	MIN(amount) AS MenorPagamento, 
	AVG(amount) AS MédiaPagaments
	FROM payment 
		INNER JOIN customer
		ON payment.customer_id=customer.customer_id
    GROUP BY CONCAT(first_name, ' ', last_name)    
    ORDER BY Cliente ASC;    

--
-- Pagamentos efetuados pelos pelos clientes.
SELECT CONCAT(CL.First_name," ",CL.Last_Name) AS Nome, 
PY.Payment_id AS Pagamento, PY.Amount AS Quantia
	FROM Payment AS PY 
		INNER JOIN Customer AS CL
		ON PY.Customer_Id=Cl.Customer_Id
	WHERE CL.Customer_id IN (1,2,3);

--
SELECT CONCAT(CL.First_name," ",CL.Last_Name) AS Nome, 
PY.Payment_id AS Pagamento, PY.Amount AS Quantia
	FROM Payment AS PY, Customer AS CL
	WHERE CL.Customer_id IN (1,2,3) AND
		PY.Customer_Id=Cl.Customer_Id;
    
--
SELECT CL.Customer_id, CL.First_Name, CL.Last_name, PY.Amount
	FROM Payment AS PY 
		INNER JOIN Customer AS CL
		ON PY.Customer_Id=CL.Customer_Id 
    WHERE CL.Customer_id IN (1,2,3);

--
-- Quais foram os 10 filmes mais aluguados durante o ano de '2005'? 
SELECT I.Film_Id, F.Title, COUNT(R.Rental_Id) AS NrALugueres 
	FROM Rental AS R 
		INNER JOIN Inventory AS I 
		ON R.Inventory_Id=I.Inventory_Id
			INNER JOIN Film AS F
            ON I.Film_Id=F.Film_id
    WHERE YEAR(R.Rental_Date) = 2005
    GROUP BY I.Film_Id
    ORDER BY NrALugueres DESC
    LIMIT 10;

--
-- Quais foram os 10 filmes (Id e Título) mais alugados?
-- Indicar número de alugueres e valor recebido.
SELECT 
	FL.Film_id AS IdFilme, 
	FL.Title AS Titulo, 
	COUNT(*) AS NrALugueres,
    SUM(PY.Total) AS ValorTotal
	FROM Rental AS RT 
		INNER JOIN Inventory AS IV
        ON RT.Inventory_Id=IV.Inventory_Id
			INNER JOIN Film AS FL
            ON IV.Film_Id = FL.Film_Id
				INNER JOIN ( 
					SELECT Rental_Id, SUM(Amount) AS Total
						FROM Payment
						WHERE Rental_Id IS NOT NULL
						GROUP BY Rental_Id )
				AS PY
				ON PY.Rental_Id=RT.Rental_id
	GROUP BY FL.Film_id
    ORDER BY NrALugueres DESC
    LIMIT 10;

-- Manipulacao de valores do tipo DATE e DATETIME
--
SELECT *
	FROM rental
	WHERE rental_date = '2005-05-24';
--
SELECT *
	FROM rental
	WHERE DATE(rental_date) = '2005-05-24';

--
SELECT MAX(DATE(rental_Date))
	FROM rental;

-- 
SELECT YEAR(NOW()) AS Ano;
SELECT MONTH(NOW()) AS Ano;
SELECT MONTHNAME(NOW()) AS Ano;
SELECT DAY(NOW()) AS Ano;
SELECT WEEK(NOW()) AS Ano;

SELECT YEAR(payment_date) AS Ano
	FROM payment
	ORDER BY YEAR(payment_date) ASC;
--
SELECT DISTINCT YEAR(payment_date) AS Ano
	FROM payment
	ORDER BY YEAR(payment_date) ASC;

--
SELECT DISTINCT MONTH(payment_date) AS Mês
	FROM payment
	ORDER BY MONTH(payment_date) ASC;

-- 
SELECT *
	FROM rental
	WHERE DATE(rental_date) = CURDATE();

--
-- Alugueres realizados em 2005 durante o mês de Dezembro.
SELECT COUNT(*)
	FROM rental
	WHERE YEAR(rental_date) = 2005
		AND MONTH(rental_date) = 12;

-- 
SELECT ADDDATE(CURDATE(), INTERVAL 1 DAY) as Amanha;

--
SELECT ADDDATE(CURDATE(), INTERVAL -7 DAY) as SemanaPassada;

--
SELECT WEEK(CURDATE());

--
SELECT WEEK(ADDDATE(CURDATE(), INTERVAL -7 DAY)) as SemanaPassada;

--
SELECT ADDDATE(CURDATE(), INTERVAL -1 YEAR) as HaUmAnoAtras;

--
SELECT CURTIME();

--
SELECT ADDTIME(CURTIME(),CURTIME());

--
SELECT ADDTIME(CURTIME(),'1:00');

-- Formatação de valores do tipo DATE nos resultados de saída de uma query. 
-- %W	Weekday - Nome do dia da semana (Sunday..Saturday).
-- %M	Month - Nome do mês (January..December).
-- %Y	Year - Ano, numérico, quatro dígitos.
SELECT DATE_FORMAT(CURDATE(), '%W %M %Y');

--
SELECT NOW();
-- %D	Day - Dia do mês com sufixo inglês (0th, 1st, 2nd, 3rd, ‚Ä¶)
-- %y	Year - Ano, numèrico, dois dígitos.
-- %a	Nome abreviado do dia da semana (Sun..Sat).
-- %d	Dia do mês, numérico (00..31)
-- %m	Mês, numérico (00..12)
-- %b	Nome do mês abreviado (Jan..Dec)
-- %j	Dia do ano (001..366)
SELECT DATE_FORMAT(NOW(),'%D %y %a %d %m %b %j');

--
SELECT DATEDIFF(NOW(),'2014-10-12');

--
SELECT DAY(rental_date) AS Dia,
	DAYNAME(rental_date) AS NomeDia,
	DAYOFMONTH(rental_date) AS DiaDoMes,
	MONTHNAME(rental_date) AS DiaDoMes,
	DAYOFWEEK(rental_date) AS DiaDaSemana,
	DAYOFYEAR(rental_date) AS DiasDoAno
	FROM rental
	WHERE rental_date = '2005-05-24 22:53:30';

--
-- Quais foram os alugueres realizados nos meses de Maio, Junho e Julho de 2005.
SELECT Rental_id, rental_date
	FROM rental
	WHERE MONTHNAME(Rental_date) IN ('May','June', 'July') AND 
		YEAR(rental_date) = 2005;

--
-- Quais foram os valores dos alugueres realizados entre nos meses de Maio, Junho e 
-- Julho de 2005.
SELECT RE.Rental_id, RE.rental_date, PA.amount
	FROM rental AS RE 
		INNER JOIN Payment AS PA
			ON RE.Rental_id = PA.Rental_id
	WHERE MONTHNAME(RE.Rental_date) IN ('May','June', 'July') AND 
		YEAR(RE.rental_date) = 2005;


-- Manipulacao de valores do tipo string - CHAR() e VARCHAR().
--
SELECT LENGTH('Os Cursos MIEI e LCC');
--
SELECT CONCAT('O SGBD My', 'S', 'QL');
--
SELECT CONCAT_WS(' ', first_name, last_name) 
	FROM customer;
--
SELECT RTRIM('Os Cursos MIEI e LCC       ');
--
SELECT '       Os Cursos MIEI e LCC';
SELECT LTRIM('       Os Cursos MIEI e LCC');
--
SELECT TRIM(leading 'O' from 'Os Cursos MIEI e LCC');
--
SELECT LOCATE('MI', 'Os Cursos MIEI e LCC');
--
SELECT SUBSTRING('Os Cursos MIEI e LCC',5,5);
--
SELECT LEFT('Os Cursos MIEI e LCC',3);
--
SELECT RIGHT('Os Cursos MIEI e LCC', 3);
--
SELECT UCASE(last_name) 
	FROM Customer;
--
SELECT REPLACE('O curso de LEI', 'LEI', 'MIEI');

-- Operacoes com funcoes de manipulacao de strngs
--
SELECT staff_id AS Nr, UCASE(CONCAT(first_name,' ',last_name)) AS Nome, 
	email AS eMail
	FROM Staff;

-- Junções EXTERNAS
-- Exemplo de uma junção externa à esquerda
SELECT *
	FROM customer AS C LEFT OUTER JOIN rental AS R
		ON C.customer_id=R.customer_id;

-- Exemplo de uma junção externa à direita
SELECT *
	FROM film_actor AS FA RIGHT OUTER JOIN film AS F
		ON FA.film_id=F.film_id;

-- Utilização de uma operação de junção (interna) entre duas tabelas.
--
SELECT *
	FROM payment AS P INNER JOIN customer AS C
		ON P.customer_id=C.customer_id;

-- Utilização de operações encadeadas de junções internas.
SELECT I.City, 
	COUNT(*) AS NrPagamentos, 
	SUM(P.amount) AS TotalPagamentos, 
	MAX(P.amount) AS MaiorPagamento, 
	MIN(P.amount) AS MenorPagamento, 
	AVG(P.amount) AS MédiaPagamentos
	FROM payment AS P 
    INNER JOIN customer AS C
		ON P.customer_id=C.customer_id
		INNER JOIN address AS A
			ON C.address_id=A.address_id
			INNER JOIN City AS I
				ON A.city_id=I.city_id
	WHERE I.City = 'Po';

--
SELECT I.City, C.Customer_id, 
	COUNT(*) AS NrPagamentos, 
	SUM(P.amount) AS TotalPagamentos, 
	MAX(P.amount) AS MaiorPagamento, 
	MIN(P.amount) AS MenorPagamento, 
	AVG(P.amount) AS MédiaPagaments
	FROM payment AS P INNER JOIN customer AS C
		ON P.customer_id=C.customer_id
		INNER JOIN address AS A
			ON C.address_id=A.address_id
			INNER JOIN City AS I
				ON A.city_id=I.city_id
	WHERE I.City = 'Po' OR I.City = 'Boa Vista'
	GROUP BY I.City, C.Customer_id;

--
SELECT *
	FROM Customer AS C INNER JOIN address AS A
		ON C.address_id=A.address_id
		INNER JOIN City AS I
			ON A.city_id=I.city_id 
	WHERE I.city_id IN (38,39,40);

-- Utilização de operações de junção com sub-queries.
SELECT *
	FROM Customer AS C INNER JOIN address AS A
		ON C.address_id=A.address_id
		INNER JOIN City AS I
			ON A.city_id=I.city_id 
	WHERE A.city_id IN 
		(SELECT city_id
			FROM City
			WHERE City LIKE 'AT%');

-- 
SELECT 	C.customer_id AS Nr, C.first_name AS Nome, 
		C.last_name AS Apelido, 
		C.email, '______' AS Observacoes
	FROM Customer AS C INNER JOIN address AS A
		ON C.address_id=A.address_id
--		INNER JOIN City AS I
--			ON A.city_id=I.city_id 
	WHERE A.city_id NOT IN 
		(SELECT city_id
			FROM City
			WHERE City LIKE 'AT%');

--
SELECT COUNT(*)
	FROM film
	WHERE film_id NOT IN (
	SELECT DISTINCT I.film_id
		FROM rental AS R INNER JOIN inventory AS I
			ON R.inventory_id=I.inventory_id);

--
SELECT *
	FROM film
	WHERE film_id NOT IN (
	SELECT DISTINCT I.film_id
		FROM rental AS R INNER JOIN inventory AS I
			ON R.inventory_id=I.inventory_id);

--
SELECT F.film_id, F.title, R.rental_date
	FROM film AS F LEFT OUTER JOIN inventory AS I
			ON F.film_id=I.film_id
			LEFT OUTER JOIN rental AS R
				ON I.inventory_id=R.inventory_id;

--
SELECT *
	FROM film AS F INNER JOIN inventory AS I
		ON F.film_id=I.film_id
		INNER JOIN rental AS R
			ON I.inventory_id=R.inventory_id;

--
-- Quais os clientes que até hoje não realizaram qualquer aluguer.
SELECT *
	FROM customer
	WHERE customer_id NOT IN (
		SELECT DISTINCT customer_id
			FROM rental);
 
-- Criação de um novo registo na tabela "customer".
INSERT INTO customer 
	(customer_id, store_id, first_name, last_name, email, 
	address_id, active)
	VALUE 
	(600, 1,'João','Casinhas','casinhas@sakila.com',605,1),
	(601, 1,'Ana','Aninhos','aninhos@sakila.com',605,1);

-- Remoção dos registos criados anteriormente.
DELETE FROM customer
	WHERE customer_id = 600 OR customer_id = 601;

--
SELECT C.customer_id AS "Cliente", COUNT(R.rental_id) NrAlugueres, 
	MAX(R.rental_date) AS "DtUlAluguere"
	FROM Customer AS C LEFT OUTER JOIN rental AS R 
		ON C.customer_id=R.customer_id
	WHERE C.customer_id >= 595
	GROUP BY C.customer_id;

--
SELECT C.customer_id AS "Cliente", COUNT(P.payment_id) NrPagamentos, 
	SUM(P.amount) AS "ValorPago", IFNULL(MAX(P.payment_date),'?') AS "DtUltPagamento"
	FROM payment AS P RIGHT OUTER JOIN Customer AS C  
		ON P.customer_id=C.customer_id
	WHERE C.customer_id >= 595
	GROUP BY C.customer_id;

--
-- Quais são os 10 melhores clientes?
SELECT 
	C.Customer_ID AS NrCliente, 
	CONCAT(C.First_Name," ",C.Last_Name) AS Nome,
    COUNT(R.Rental_Id) AS NrAlugueres,
    SUM(P.Amount) AS TotalPago
	FROM Customer AS C 
		INNER JOIN Rental AS R
		ON C.Customer_Id = R.Customer_Id
			INNER JOIN Payment AS P
            ON R.Rental_Id = P.Rental_Id
	GROUP BY C.Customer_Id
    ORDER BY TotalPago DESC
    LIMIT 10;
    
--    
-- Quais os nomes dos atores dos filmes que foram alugados por clientes
-- do país 'Peru' durante o mês de 'Maio' de 2006.
SELECT DISTINCT 
	CONCAT(AC.first_name,' ', AC.last_name) AS NomeAtor 
	FROM country as C 
		INNER JOIN city AS I
		ON C.country_id=I.country_id
			INNER JOIN address AS A
			ON I.city_id=A.city_id
				INNER JOIN customer AS U
				ON U.address_id=A.address_id
					INNER JOIN rental AS R
					ON U.customer_id=R.customer_id
						INNER JOIN inventory AS N
						ON N.inventory_id=R.inventory_id
							INNER JOIN film AS F
							ON N.film_id=F.film_id
								INNER JOIN film_actor AS FA
								ON FA.film_id=F.film_id
									INNER JOIN actor AS AC
									ON AC.actor_id=FA.actor_id
	WHERE C.country = 'Peru'
		AND YEAR(R.rental_date) = '2005'
		AND MONTHNAME(R.rental_date) = 'May';

--
-- Exemplo da obtenção de dados para um relatório de gestão.
-- Combinação de dados entre várias tabelas.
SELECT 
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

--
-- 






--
-- <fim>
