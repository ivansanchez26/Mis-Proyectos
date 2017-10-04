/* EXERCICI 1*/

create or replace procedure factura (v_dni estudiants.dni%type)
is
  v_comprovar_estudiant NUMBER(3):=0;
  v_comprovar_estudiant2 NUMBER(3):=0;
  v_dies NUMBER(6):=0;
  v_habitacio estu_hab.id_habitacio%type;
  v_preudia habitacions.preudia%type;
  v_factura estu_hab.factura%type;
  v_tipus habitacions.categoria%type;
  v_menjador estudiants.menjador%type;
  v_nom estudiants.nom%type;
  v_cognom estudiants.cognom%type;
  v_mesos NUMBER(3):=0;
  v_quotames estudiants.quotames%type;
BEGIN
  SELECT COUNT(dni) into v_comprovar_estudiant FROM  estudiants WHERE dni=v_dni;
  
  IF v_comprovar_estudiant=0 THEN
    dbms_output.put_line('No s ha trobat cap estudiant');
  END IF; 
  
  SELECT COUNT(dni) INTO v_comprovar_estudiant2 FROM estu_hab WHERE data_ini IS NOT NULL AND data_fi IS NULL AND dni=v_dni;
  
  
  IF v_comprovar_estudiant2=0 THEN
    dbms_output.put_line('Has triat un estudiant no allotjat');
  END IF;  
  
  IF v_comprovar_estudiant2=0 THEN
    SELECT TRUNC(MONTHS_BETWEEN(data_fi,data_ini)) INTO v_mesos FROM estu_hab WHERE dni=v_dni;
  END IF;  
  
  IF v_comprovar_estudiant2!=0 THEN
    SELECT TRUNC(MONTHS_BETWEEN(SYSDATE,data_ini)) INTO v_mesos FROM estu_hab WHERE dni=v_dni;
  END IF;
  
  SELECT quotames INTO v_quotames FROM estudiants WHERE v_dni=dni;
  
  SELECT SYSDATE-data_ini INTO v_dies FROM estu_hab WHERE v_dni=dni;
  
  
  SELECT id_habitacio INTO v_habitacio FROM estu_hab WHERE v_dni=dni;
  
  SELECT preudia INTO v_preudia FROM habitacions WHERE id_habitacio=v_habitacio;
  
  SELECT categoria INTO v_tipus FROM habitacions WHERE id_habitacio=v_habitacio;
  
  CASE v_tipus
    WHEN 'Simple' THEN
      v_factura:=v_dies*v_preudia;
    WHEN 'Triple' THEN
      v_factura:=(v_dies*v_preudia)/3;
    WHEN 'Doble' THEN
      v_factura:=(v_dies*v_preudia)/2;
  END CASE;    
 
  v_factura:=v_factura+v_mesos*v_quotames;
  
  SELECT menjador INTO v_menjador FROM estudiants WHERE v_dni=dni;
  
  IF UPPER(v_menjador) LIKE 'S' THEN
    v_factura:=v_factura+v_dies*10;
  END IF;
  
  UPDATE estu_hab 
  SET factura=v_factura
  WHERE dni=v_dni;
  
  UPDATE estu_hab 
  SET data_fi=SYSDATE
  WHERE dni=v_dni;
  
  SELECT nom,cognom INTO v_nom,v_cognom FROM estudiants WHERE dni=v_dni;
  
  dbms_output.put_line('L estudiant ' || v_nom || ' ' || v_cognom || ' amb dni ' || v_dni || ' ha pagat ' || v_factura);
  
  
  
END; 


/*Casos de prova*/

/*Dni que existeix i DNI que no existeix*/
	/*El DNI 34123456-L no hauria de tornar cap missatge*/
	/*El DNI 12345 hauria de dir que no existeix un estudiant*/

/*Dni d' estudiant no allotjat*/
	/*El DNI 34123456-L no hauria de tornar cap missatge*/
	/*El DNI 12345 hauria de dir que no es un usuari allotjat(també podriem modificar la data de fi d' un estudiant i probar amb ell)*/	
	
/*Pagar quotames*/
	/*Agafar un DNI com 34123456-L hauria de donar 5362, al posarli la quota a 1 hauria de donar 5089 */

/*Pagar Preudia*/
	/*Agafar un DNI qualsevol com 34123456-L i comprovar que torni els dies que ha estat multiplicat pel seu preudia. Hauria de donar aprox. 5362. Pot variar ja que canvia segons el dia executat perque fa servir SYSDATE.
	/*Canviarli a l' estudiant amb dni 34123456-L la categoria de l' habitació a doble i comprovar que dona uns 3976. Canviar també a triple i comprovar que doni uns 3514.*/
	
/*Treureli el menjador a un estudiant com 34123456-L i comprovar quant paga*/
	/*Amb menjador hauria de pagar 5362 sense hauria de pagar 3052*/

/*Comprovar xifres decimals*/
		/*Posarli dues xifres decimals a v_factura al final del procediment i comprovar que ens escriu un valor amb decimals*/
		
/*Comprovar update*/
		/*Anar a estu_hab i comprovar que s' ha actualitzat la factura i la data de sortida*/
		
		


/*EXERCICI 2*/


create or replace function universitat (v_sigles universitats.sigles%type) return NUMBER
is
  v_id_universitat universitats.id_universitat%type;
  v_import NUMBER(9):=0;
  v_estudiants NUMBER(3):=0;
  v_quotes NUMBER(5):=0;
  v_tipus universitats.tipus%type;
  v_comptar NUMBER(3):=0;
BEGIN
  SELECT id_universitat INTO v_id_universitat FROM universitats WHERE UPPER(sigles) LIKE UPPER(v_sigles);
  SELECT COUNT(dni) INTO v_estudiants FROM estudiants WHERE id_universitat=v_id_universitat;
  SELECT tipus INTO v_tipus FROM universitats WHERE id_universitat=v_id_universitat;
  SELECT SUM(quotames) INTO v_quotes FROM estudiants WHERE id_universitat=v_id_universitat;
  
  IF v_estudiants=0 THEN
    dbms_output.put_line('No hi ha cap estudiant');
    return 0;
  END IF;  
  
  CASE v_tipus
    WHEN 'PUB' THEN
      v_import:=v_estudiants*100;
      v_import:=v_import+v_quotes*0.10;
    WHEN 'PRI' THEN
      v_import:=v_estudiants*50;
      v_import:=v_import+v_quotes*0.5;
  END CASE;
  return v_import;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    dbms_output.put_line('No s ha trobat cap universitat');
    return -1;
  WHEN TOO_MANY_ROWS THEN
    dbms_output.put_line('Hi ha mes d una universitat amb aquestes sigles.');
  WHEN OTHERS THEN
    dbms_output.put_line('Error num: ' || SQLCODE || SQLERRM);
    return -2;
END;   


/*Casos de prova*/

	/*Universitat publica*/
		/*Si provem amb la universitat UB hauria de retornar 518*/
		/*Si canviem el tipus de la universitat UB a PRI hauria de retornar 340*/
	/*Si provem amb una universitat inexistent com XX hauria de retornar -1*/
	/*Si provem amb una universitat sense residents com PFB hauria de retornar 0*/
	
		

