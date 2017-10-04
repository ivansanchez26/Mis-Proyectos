
SELECT CONCAT (SUBSTR(cognom,1,3),emp_no) FROM emp;
/*Com a admin creem un usuari per emmagatzemar les taules*/
CREATE USER empresa IDENTIFIED BY empresapass 
DEFAULT TABLESPACE users
QUOTA 2M ON users;

GRANT DBA TO empresa;

CREATE ROLE COMERCIAL;

GRANT select,update,insert ON empresa.client TO COMERCIAL;
GRANT select,update,insert ON empresa.comanda TO COMERCIAL;
GRANT create session TO COMERCIAL;

CREATE PROFILE COMERCIAL LIMIT
SESSIONS_PER_USER 1
FAILED_LOGIN_ATTEMPTS 2
PASSWORD_LOCK_TIME 30;

SELECT CONCAT (SUBSTR(cognom,1,3),emp_no) FROM emp WHERE ofici LIKE 'VENEDOR';

CREATE USER ARR7499 IDENTIFIED BY SABADELL PASSWORD EXPIRE;
CREATE USER SAL7521 IDENTIFIED BY SABADELL PASSWORD EXPIRE;

ALTER USER SAL7521 PROFILE COMERCIAL;
ALTER USER ARR7499 PROFILE COMERCIAL;

GRANT COMERCIAL TO ARR7499,SAL7521; 




CREATE ROLE ADMINISTRATIU;

GRANT select,update ON empresa.comanda TO ADMINISTRATIU;
GRANT select ON empresa.productes TO ADMINISTRATIU;
GRANT select ON empresa.client TO ADMINISTRATIU;

CREATE PROFILE ADMINISTRATIU LIMIT
SESSIONS_PER_USER 2
IDLE_TIME 20
FAILED_LOGIN_ATTEMPTS 3;

SELECT CONCAT (SUBSTR(cognom,1,3),emp_no) FROM emp WHERE UPPER(ofici) LIKE 'EMPLEAT';

CREATE USER JIM7900 IDENTIFIED BY SABADELL PASSWORD EXPIRE;
CREATE USER ALO7876 IDENTIFIED BY SABADELL PASSWORD EXPIRE;

ALTER USER JIM7900 PROFILE ADMINISTRATIU;
ALTER USER ALO7876 PROFILE ADMINISTRATIU;

GRANT ADMINISTRATIU TO JIM7900,ALO7876;





CREATE ROLE ANALISTA;

GRANT SELECT,UPDATE,INSERT ON empresa.client TO ANALISTA ;
GRANT SELECT,UPDATE,INSERT ON empresa.comanda TO ANALISTA;
GRANT SELECT,UPDATE,INSERT ON empresa.dept TO ANALISTA;
GRANT SELECT,UPDATE,INSERT ON empresa.detall TO ANALISTA;
GRANT SELECT,UPDATE,INSERT ON empresa.producte TO ANALISTA;
GRANT CONNECT TO ANALISTA;
GRANT DROP ANY TABLE TO ANALISTA;
GRANT CREATE ANY TABLE TO ANALISTA;

SELECT CONCAT (SUBSTR(cognom,1,3),emp_no) FROM emp WHERE UPPER(ofici) LIKE 'ANALISTA';


CREATE USER GIL7788 IDENTIFIED BY SABADELL PASSWORD EXPIRE;
CREATE USER FER7902 IDENTIFIED BY SABADELL PASSWORD EXPIRE;

GRANT ANALISTA TO GIL7788,FER7902 WITH ADMIN OPTION;


SELECT * FROM DBA_USERS JOIN DBA_PROFILES ON  dba_profiles.profile=dba_users.profile WHERE USERNAME LIKE 'GIL7788';



