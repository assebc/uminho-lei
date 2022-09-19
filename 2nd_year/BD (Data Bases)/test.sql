-- SGBD
CREATE DATABASE IF NOT EXISTS `teste`;
USE `teste`;

-- tabelas
CREATE TABLE IF NOT EXISTS `investigador`(
  num_cedula INT NOT NULL,
  nome VARCHAR(100) NOT NULL,
  data_nas DATE NOT NULL,
    PRIMARY KEY (num_cedula));

CREATE TABLE IF NOT EXISTS `telefone`(
  numero INT NOT NULL,
  num_cedula INT NOT NULL REFERENCES investigador(num_cedula),
    PRIMARY KEY (numero));


CREATE TABLE IF NOT EXISTS `email`(
    email VARCHAR(100) NOT NULL,
    num_cedula INT NOT NULL REFERENCES investigador(num_cedula),
        PRIMARY KEY (email));

CREATE TABLE IF NOT EXISTS `dossier`(
  id_dossier INT NOT NULL,
  nome VARCHAR(100) NOT NULL,
  data_dossier DATE,
  num_dias INT NOT NULL,
  num_cedula INT NOT NULL  REFERENCES investigador(num_cedulas),
    PRIMARY KEY (id_dossier));

CREATE TABLE IF NOT EXISTS `area`(
      cod_area INT NOT NULL,
      descricao VARCHAR(100) NOT NULL,
    num_cedula INT NOT NULL REFERENCES investigador(num_cedula),
        PRIMARY KEY (cod_area));
        
INSERT INTO investigador (num_cedula, nome, data_nas) VALUES('5','JoÃ£o','2002-04-13');
INSERT INTO investigador (num_cedula, nome, data_nas) VALUES('4','Carlos','2003-04-13');
INSERT INTO investigador (num_cedula, nome, data_nas) VALUES('3','Hirokumata','1969-04-13');

INSERT INTO telefone(numero, num_cedula) VALUES ('933333333', '5');
INSERT INTO telefone(numero, num_cedula) VALUES ('911111111', '5');
INSERT INTO telefone(numero, num_cedula) VALUES ('933333334', '4');
INSERT INTO telefone(numero, num_cedula) VALUES ('911111112', '4');
INSERT INTO telefone(numero, num_cedula) VALUES ('933333344', '3');
INSERT INTO telefone(numero, num_cedula) VALUES ('911111122', '3');
  
INSERT INTO email(email, num_cedula) VALUES ("joazinhotutoriaisminecraft@gmail.com", '5');
INSERT INTO email(email, num_cedula) VALUES ("joaoyoutuber@gmail.com", '5');
INSERT INTO email(email, num_cedula) VALUES ("joazinhocatarinotutoriaisminecraft@gmail.com", '4');
INSERT INTO email(email, num_cedula) VALUES ("joaocarlos@gmail.com", '4');
INSERT INTO email(email, num_cedula) VALUES ("queloaloz@gmail.com", '3');
INSERT INTO email(email, num_cedula) VALUES ("flangoflito@gmail.com", '3');

INSERT INTO area (cod_area, descricao, num_cedula) VALUES('4', "fraude", '5');
INSERT INTO area (cod_area, descricao, num_cedula) VALUES('3', "roubo", '4');
INSERT INTO area (cod_area, descricao, num_cedula) VALUES('2', "fraude", '3');

INSERT INTO dossier (id_dossier, nome, data_dossier, num_dias, num_cedula) VALUES ('1',"arroz",'2022-12-21','5','5');
INSERT INTO dossier (id_dossier, nome, data_dossier, num_dias, num_cedula) VALUES ('2',"massa",'2022-12-22','3','4');


SELECT COUNT(*) FROM area WHERE cod_area = 4;

SELECT COUNT(num_cedula),cod_area FROM area GROUP BY cod_area ORDER BY descricao;