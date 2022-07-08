--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- SQL - Operações sobre strings utilizando expressões regulares.
--
-- Exemplos de Aplicação.
-- Belo, O., 2016.
--

-- Base de Dados de Trabalho.
USE Sakila;


-- Utilização de expressões regulares.

-- Query to find all the names, which contain 'mar'
SELECT name 
	FROM person_tbl 
	WHERE name REGEXP 'mar';
--
SELECT * 
 	FROM customer 
	WHERE first_name REGEXP '^And';

-- Uma query equivalente utilizando o operador LIKE.
SELECT * 
 	FROM customer 
	WHERE first_name LIKE 'And%';

-- Utilização do operador equivalente RLIKE - é um sinónimo.
SELECT * 
 	FROM customer 
	WHERE first_name RLIKE '^And';

--
SELECT City 
	FROM City 
	WHERE City REGEXP '^A|^B|^R';

--
SELECT * 
 	FROM customer 
	WHERE email REGEXP 'org$';

-- Utilização conjunta com o operador NOT.
SELECT * 
 	FROM customer 
	WHERE email NOT REGEXP 'org$';

-- 
SELECT * 
 	FROM customer 
	WHERE address_id REGEXP '[7-9]$';

-- 
SELECT * 
 	FROM customer 
	WHERE first_name REGEXP '^And' AND 
	      address_id REGEXP '[7-9]$';

-- Todos os nomes de cidades que comecem por uma vogal ou acabem com lis. 
SELECT City 
	FROM City
	WHERE City REGEXP '^[aeiou]|lis$';

-- Todos os nomes de cidades que tenham exatamente cinco caracteres.
SELECT City 
	FROM City
	WHERE City REGEXP '^.....$';

-- O mesmo que a query anterior.
SELECT City 
	FROM City
	WHERE City REGEXP '^.{5}$';

--
SELECT City 
	FROM City
	WHERE City REGEXP '^A.. D...i$';

--
SELECT 'abcde' REGEXP 'a[bcd]{1,10}e';  -- 1
--
SELECT 'aXbc' REGEXP '[a-dXYZ]';  -- 1
--
SELECT 'gheis' REGEXP '^[^a-dXYZ]+$'; -- 1


-- Utilização de expressões regulares estendidas.
--
SELECT 'justalnums' REGEXP '[[:alnum:]]+'; -- 1
--
SELECT 'a word a' REGEXP '[[:<:]]word[[:>:]]';  -- 1
--


--
-- <fim>
