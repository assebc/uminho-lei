--
-- Unidade Curricular de Bases de Dados.
-- Sistemas de Dados Relacionais.
--
-- U S E R S
-- Criação, alteração e remoção de utilizadores e seus privilégios.
--
-- Exemplos de Aplicação.
-- Belo, O., 2020, 2021.
--

-- Base de Dados de Trabalho.
USE Sakila;

-- Criação do utilizador 'admin'
CREATE USER 'admin'@'localhost';

-- Definição de password
SET PASSWORD FOR 'admin'@'localhost' = 'admin1234';
-- ou
UPDATE mysql.user 
	SET Password = PASSWORD('admin1234') 
	WHERE USER='admin' AND Host='localhost';

-- ou de forma alternativa 
CREATE USER 'admin'@'localhost'
	IDENTIFIED BY 'admin1234';

-- Criação do utilizador 'prog'
CREATE USER 'prog'@'localhost';
SET PASSWORD FOR 'prog'@'localhost' = 'prog1234';

-- Criação do utilizador 'user'
CREATE USER 'user'@'localhost';
SET PASSWORD FOR 'user'@'localhost' = 'user1234';

--
CREATE USER 'josefa'@'localhost' 
	IDENTIFIED BY 'josefa'
		WITH MAX_QUERIES_PER_HOUR 20
		MAX_UPDATES_PER_HOUR 10
		MAX_CONNECTIONS_PER_HOUR 5
		MAX_USER_CONNECTIONS 2;
		
-- Mudança do nome de um utilizador.
RENAME USER 'user'@'localhost' TO 'user'@'otherhost';

-- Remoção do utilizador do sistema.
DROP USER 'user'@'localhost';

-- Consulta dos utilizadores criados no sistema.
-- Caracterização geral de todos os utilizadores.
SELECT * 
	FROM mysql.user;

-- Caracterização geral de um utilizador em particular.
SELECT * 
	FROM mysql.user
	WHERE User = 'user';

-- Apenas os nomes dos utilizadres e dos sistemas em que estão definidos.
SELECT User, Host 
	FROM mysql.user
	ORDER BY User;

-- Atribuição de privilégios a utilizadores.
-- Definição de previlégios ao utilizador 'admin'. 
-- Permissão de acesso a todos os objetos de todas as bases de dados em 'localhost'.
GRANT ALL ON *.* TO 'admin'@'localhost';

-- Permissão de acesso a todos os objectos da base de dados em 'localhost'.
GRANT ALL ON Sakila.* TO 'admin'@'localhost';

-- Definição de alguns previlégios para o utilizador 'prog'. 
-- Permissão para a execução de instruções SELECT, INSERT e UPDATE na base de dados 
-- em 'localhost'.
GRANT SELECT, INSERT, UPDATE ON  Sakila.* TO 'prog'@'localhost';

-- Permissão para a criação e execução de procedimentos em 'localhost'.
GRANT CREATE ROUTINE ON Sakila.* TO 'prog'@'localhost';
GRANT EXECUTE ON PROCEDURE Sakila.* TO 'prog'@'localhost';

-- Definição de alguns previlégios para o utilizador 'user'. 
-- Permissão para a execução de instruções SELECT e INSERT sobre a base de dados 
-- em 'localhost', apenas sobre as tabelas 'Customer' e 'Rental'.
GRANT SELECT, INSERT ON Sakila.Customer TO 'user'@'localhost';
GRANT SELECT, INSERT ON Sakila.Rental TO 'user'@'localhost';

-- E apenas de leitura sobre a tabela "Inventory".
GRANT SELECT ON Sakila.Inventory TO 'user'@'localhost';

-- E apenas de leitura sobre os atributos 'Id' e 'Nome' da tabela 'Funcion√°rios'.
GRANT SELECT (Staff_Id, First_name, Last_Name) 
	ON Sakila.Staff TO 'user'@'localhost';

-- Consulta dos privil√©gios atribu√≠dos ao utilizador 'user' em 'localhost'.
SHOW GRANTS FOR 'user'@'localhost';

-- Refrescamento dos privilégios de utilizadores. 
FLUSH PRIVILEGES;


-- Remoção de privilégios a utilizadores.
-- Remoção de previlégios para o utilizador 'admin'.
-- Inibição da execução de instruções DELETE sobre a base de dados em 'localhost'.
REVOKE DELETE ON Sakila.* FROM 'admin'@'localhost';

-- Remoção de todos os tipos de privilégios de um utilizador
REVOKE ALL PRIVILEGES, GRANT OPTION FROM 'user'@'localhost';

--
-- <fim>
