#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>


/* definici?del registre poblacions*/
struct Poblacio {
	int codiPoblacio; 
	char nomPoblacio[50];
	int habitants;
};

struct Sensor {
	int codiPoblacio;
	int hora;
	int temperatura;
};

struct Resum {
	int codi;
	char nomPoblacio[50];
	int max;
	int min;
	int promig;
};

int sizePoblacio = sizeof(struct Poblacio);

int xifra (char c){
	int qValor;
	switch (c){
		case '0':	qValor = 0;break;
		case '1':	qValor = 1;break;
		case '2':	qValor = 2;break;
		case '3':	qValor = 3;break;
		case '4':	qValor = 4;break;
		case '5':	qValor = 5;break;
		case '6':	qValor = 6;break;
		case '7':	qValor = 7;break;
		case '8':	qValor = 8;break;
		case '9':	qValor = 9;break;
		case '-':   qValor = -2;break;
		default:	qValor = -1;break;
	}
	return qValor;
}

struct Poblacio tractar_linia(char cadena[80]){
		struct Poblacio p;
		char pob[40];
		int posInici, posFi,i,j,k;
		int valor, qValor;
		char poblacio[30];
		int habitants;
		int n;	
		
		// 0.- per si vols comprovar el que has llegit del fitxer
		//printf("Tractar: %s\n",cadena);
		//return p;
		// 0.- Fi
		
		//1.a obtenir el primer camp i passar-ho a num?ic
		posInici = 0;
		valor = 0;
		i=0;
		while (cadena[i]!=';') {
			qValor = xifra(cadena[i]);
			valor = valor*10 + qValor;
			i++;			
		}
		p.codiPoblacio = valor;
		
		//2.a obtenir segon camp
		posInici = i+1;
		i = posInici;
		while (cadena[i]!=';') i++;
		posFi = i-1; 
	
		//2.b passar-ho a la variable corresponent
		for (i=posInici;i<=posFi;i++){
			pob[i-posInici] = cadena[i];
		}	
		pob[i-posInici]= '\0';

		strcpy(p.nomPoblacio,pob);

		//3.a obtenir tercer camp
		posInici = posFi + 2;

		i = posInici;
		valor = 0;
		qValor = xifra(cadena[i]);
		while (qValor!=-1){
			valor = valor*10 + qValor;
			i++;
			qValor = xifra(cadena[i]);
		};

		p.habitants = valor;

	    //printf("nP: %d, nomP: %s, habitants: %d\n",p.codiPoblacio,p.nomPoblacio, p.habitants);
		return p;
}

struct Sensor tractarLinia2(char cadena[80]){
	struct Sensor s;
		
		int posInici,i;
		int valor, qValor;
		
		
			
		
		
		posInici = 0;
		valor = 0;
		i=0;
		while (cadena[i]!=';') {
			qValor = xifra(cadena[i]);
			valor = valor*10 + qValor;
			i++;			
		}
		s.codiPoblacio = valor;
		
		
		posInici = i+1;
		i = posInici;
		valor = 0;
		while (cadena[i]!=';'){
			qValor = xifra(cadena[i]);
			valor = valor*10 + qValor;
			i++;
		} 
		
		s.hora = valor;
		
		posInici = i + 1;
		i = posInici;
		valor = 0;
		qValor = xifra(cadena[i]);
		
		int negatiu=0;
		
		while (qValor!=-1){
			if(qValor==-2){
				negatiu++;
			}
			else{
				valor = valor*10 + qValor;
			}
			i++;
			qValor = xifra(cadena[i]);
		};
		
		if(negatiu!=0)
			valor= -valor;
		s.temperatura = valor;

	  //  printf("codi: %d, hora: %d, temperatura: %d\n",s.codiPoblacio,s.hora, s.temperatura);
		return s;
}

void llegirTemperatures(char temperatures[],char poblacions[]){
	
	FILE *fTemperatures;
	fTemperatures = fopen(temperatures,"rb");
	int temp;
	int i;
	int j=0;
	int sizeInt = sizeof(int);
	
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");
	
	
	FILE *fBinari;	
	struct Poblacio pob;
	int cont=0;
	
	fBinari=fopen(poblacions,"rb");

	if (fBinari == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");

	rewind(fBinari);
	
	int longitud=0;
	int espais=0;
	system("cls");
	printf("Nom poblacio \t \t \t   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23\n");
	rewind(fTemperatures);                   
	while(fread(&temp, sizeInt,1, fTemperatures) == 1) {
		
		if(j==0){
			fread(&pob, sizePoblacio,1, fBinari);
			longitud=strlen(pob.nomPoblacio);
			espais=35-longitud;
			printf("\n%s",pob.nomPoblacio);
			for(i=0;i<espais;i++){
				printf(" ");
			}
			//printf("%d",longitud);
			if(temp==99)
				printf("  ");
			else
				printf("%2d",temp);
		}
		else{
			if(temp == 99)
				printf("   ");
			else
				printf(" %2d",temp);	
		}
		j++;
		if(j==24)
			j=0;
	}
	
	fclose(fTemperatures);
}


void afegirSensor(){
	
	char sensor[30];
	printf("Digues el nom del fitxer de sensor que vols obrir: ");
	fflush(stdin);
	gets(sensor);
	
	struct Sensor Sensor1;
	int sizeSensor = sizeof(struct Sensor);
	int tamanyInt = sizeof(int);
	
	FILE *fSensor;
	
	fSensor= fopen(sensor,"r");
	
	if (fSensor == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");
	
	
	char cadena[80];
	
	FILE *fTemperatures;
	fTemperatures = fopen("temperatures.dat","r+b");
	int testTemp;
	
	rewind(fSensor);
	int j=0;  //prueba contar 
	while(fgets(cadena,80,fSensor)!=NULL){
		
		Sensor1 = tractarLinia2(cadena);
		
		/*printf("temp = %d\n",Sensor1.temperatura);
		j++;
		printf("j = %d",j);*/
		//printf("Codi: %d  hora: %d temp: %d\n" ,Sensor1.codiPoblacio,Sensor1.hora,Sensor1.temperatura);
		if(fseek(fTemperatures,tamanyInt*((Sensor1.codiPoblacio-1)*24)+tamanyInt*Sensor1.hora,SEEK_SET) == 0){
			fread(&testTemp,tamanyInt,1,fTemperatures);
			if(testTemp==99){
				fseek(fTemperatures,tamanyInt*((Sensor1.codiPoblacio-1)*24)+tamanyInt*Sensor1.hora,SEEK_SET);
				if (!fwrite(&Sensor1.temperatura,tamanyInt,1,fTemperatures) == 1)
				printf("No he pogut escriure el registre al buffer del fitxer\n"); 	
			}
			else
				printf("Temperatura ja posada a codi %d a l' hora %d\n",Sensor1.codiPoblacio,Sensor1.hora);
			
			
		}
		else
			printf("Posicio no trobada");
	}	
	
	fclose(fSensor);
	fclose(fTemperatures);
}


void generaTemps(char poblacions[],char temperatures[]){
	int tamany = sizeof(struct Poblacio);
	int contador = 0;
	struct Poblacio Poblacio1;
	FILE *fBinari;
	fBinari=fopen(poblacions,"r+b");
	
	if (fBinari == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");
	
	rewind(fBinari);            
	while(fread(&Poblacio1, tamany,1, fBinari) == 1) {
		contador++;
	}
		
		
	fclose(fBinari);
	int i;
	int tempStatic = 99;
	int hi = 0;
	FILE *fTemperatures;
	int tamanyInt = sizeof(int);
	fTemperatures=fopen(temperatures,"wb");
	
	if(fTemperatures!=NULL){
		
		for(i=0;i<contador*24;i++){

	        	if (!fwrite(&tempStatic,tamanyInt,1,fTemperatures) == 1)
					printf("No he pogut escriure el registre al buffer del fitxer\n");
				
						
	        
	    }
	}
	
	fclose(fTemperatures);
	
}

void modificarBinari(char poblacions[]){
	int tamany= sizeof(struct Poblacio);
	int menu;
	int aceptar;
	struct Poblacio Poblacio1;
	FILE *fBinari;
	fBinari=fopen(poblacions,"r+b");
	
	if (fBinari == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");
	
	int NumRegistre;	
	printf("Escriu el numero del registre que vols llegir: \n");
	scanf("%d",&NumRegistre);
		
	if ((fseek(fBinari,(NumRegistre-1)*tamany,SEEK_SET) == 0) &&
		 (fread(&Poblacio1, tamany,1, fBinari) == 1)) {
				printf("Codi poblacio: %d\n",Poblacio1.codiPoblacio);
				printf("Nom Poblacio: %s\n",Poblacio1.nomPoblacio);
				printf("Habitants: %d\n",Poblacio1.habitants);
				
		fflush(stdin);
		printf("1-Canviar Nom\n2-Canviar num. habitants");
		scanf("%d",&menu);
		if(menu==1){
			fflush(stdin);
			gets(Poblacio1.nomPoblacio);
			printf("Vols cancelar la operacio?\n1-Si\n2-No");
			scanf("%d",&aceptar);
			if(aceptar==2){
		        if (fseek(fBinari,(NumRegistre-1)*tamany,SEEK_SET) == 0){
		            if (fwrite(&Poblacio1,tamany,1,fBinari) == 1)
		                printf("He escrit be el registre al buffer del fitxer\n");
		            else
		                printf("No he pogut escriure el registre al buffer del fitxer\n");
		        }
	    	}
		}
		if(menu==2){
			scanf("%d",&Poblacio1.habitants);
			printf("Vols cancelar la operacio?\n1-Si\n2-No");
			scanf("%d",&aceptar);
			if(aceptar==2){
		        if (fseek(fBinari,(NumRegistre-1)*tamany,SEEK_SET) == 0){
		            if (fwrite(&Poblacio1,tamany,1,fBinari) == 1)
		                printf("He escrit be el registre al buffer del fitxer\n");
		            else
		                printf("No he pogut escriure el registre al buffer del fitxer\n");
		        }
	    	}
		}
			
	}
	else{
		printf("No puc llegir");
	}
	
	fclose(fBinari);	

}


void llegir_binari(char nomBinari[]){
	FILE *fBinari;	
	struct Poblacio pob;
	int cont=0;
	
	fBinari=fopen(nomBinari,"rb");

	if (fBinari == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");

	rewind(fBinari);                      // va al principi del fitxer
	while(fread(&pob, sizePoblacio,1, fBinari) == 1) {
		printf("%d ... %s: ... %d \n", pob.codiPoblacio,pob.nomPoblacio,pob.habitants);
		cont++;
	}
	if (! cont )
		printf("No he pogut llegir cap registre\n");
	else
		printf("He llegit %d poblacions\n",cont);
}

void llegir_fitxer(char fOrigen[], char fDesti[]){
    char cadena[80];
    FILE *Origen;
    FILE *Desti;
    int i=0;
    struct Poblacio qPob;

	Desti=fopen(fDesti,"wb");
	if (Desti==NULL){
		printf("No puc obrir dest?n");
		
	}

    Origen=fopen(fOrigen,"r");
    if(Origen!=NULL){
        while(fgets(cadena,80,Origen)!=NULL){
            //puts(frase);
            qPob = tractar_linia(cadena);
            
        	if (!fwrite(&qPob,sizePoblacio,1,Desti) == 1)
				printf("No he pogut escriure el registre al buffer del fitxer\n");

            i++;
        }
        printf("Llegides: %d\n", i);
        fclose(Origen);
        
    }
    else{
        printf("No puc obrir origen\n");
        
    }
    fclose(Desti);
    
    system("pause");
}

void consultar(char temperatures[]){
	
	FILE *fTemperatures;
	fTemperatures = fopen(temperatures,"rb");
	
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer");
	else
		printf("Fitxer obert correctament")	;
	
	
	
	
	
	int codi;
	printf("\nDigues el codi de la poblacio a consultar: ");
	
	do{
		scanf("%d",&codi);	
	}while(codi<1);
	
	int hora;
	
	printf("Digues l'' hora a consultar: ");
	do{
		scanf("%d",&hora);	
	}while(hora<0 || hora>23);
	
	int sizeInt = sizeof(int);
	int temp;
	
	
	
	rewind(fTemperatures);	
	if (fseek(fTemperatures,sizeInt*((codi-1)*24)+sizeInt*hora,SEEK_SET) == 0) 
	
		if(fread(&temp, sizeInt,1, fTemperatures) == 1) 
			if(temp==99)
				printf("No hi ha valor");
			else	
				printf("%d",temp);
		else
			printf("Poblacio no trobada");
	
	fclose(fTemperatures);
}

void resum(char temperatures[],char resum[],char poblacions[]){
	
	FILE *fTemperatures;
	int sizeInt = sizeof(int);
	fTemperatures = fopen(temperatures,"rb");
	int temp;
	int j=0;
	
	int i=0,k=0,x=0;
	int max=-100;
	int min=100;
	int promig;
	
	char sCodi[2];
	char sMax[2];
	char sMin[2];
	char sPromig[2];	
	
	struct Resum Resum1;
	int sizeResum = sizeof(struct Resum);
	
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer");
	else
		printf("Fitxer obert correctament")	;
		
	FILE *fResum;
	fResum = fopen(resum,"w");
	rewind(fResum);
	
	FILE *fPoblacions;
	fPoblacions = fopen(poblacions,"rb");
	struct Poblacio pob;
		
	
	rewind(fTemperatures);
	while (fread(&temp, sizeInt,1, fTemperatures) == 1){
		
		if(temp!=99){
			promig=promig+temp;
			if(temp>max)
				max=temp;
			if(temp<min)
				min=temp;
					
		}
		j++;
		if(j==24){
			fread(&pob, sizePoblacio,1, fPoblacions);
			promig=promig/24;
			Resum1.codi = i+1;
			Resum1.max = max;
			Resum1.min = min;
			Resum1.promig = promig;
			//fwrite(&Resum1,sizeResum,1,fResum);
			//printf("\ncodi = %d max = %d min= %d promig = %d",Resum1.codi,Resum1.max,Resum1.min,Resum1.promig);
			sprintf(sCodi, "%d", Resum1.codi); //Bendita funcion
			sprintf(sMax, "%d", Resum1.max);
			sprintf(sMin, "%d", Resum1.min);
			sprintf(sPromig, "%d", Resum1.promig);
		//	printf("%s - %s - %s - %s - %s\n",sCodi,pob.nomPoblacio,sMax,sMin,sPromig);
			
			if(max!=-100 && min!=100){
				fputs (sCodi, fResum); 
				putc(';',fResum);
				fputs (pob.nomPoblacio, fResum);
				putc(';',fResum); 
				fputs (sMax, fResum); 
				putc(';',fResum); 
				fputs (sMin, fResum);
				putc(';',fResum); 
				fputs (sPromig, fResum);
				putc(10,fResum); 
			}
			j=0;
			min=100;
			max=-100;
			promig=0;
			i++;
		}
		
		
		
	}	
		
	
	
	
	
	
	/*while(i!=j){
		fread(&temp,sizeInt*(i*24)+sizeInt*k,1,fTemperatures);
		if(temp!=99){
			promig=promig+temp;
			if(temp>max)
				max=temp;
			if(temp<min)
				min=temp;
			x++;		
		}
		k++;
		if(k==24){
			promig=promig/x;
			printf("codi = %d\nmax = %d\nmin= %d\n promig = %d",i+1,max,min,promig);
			k=0;
			x=0;
			i++;
		}
	}*/
	fclose(fTemperatures);
	fclose(fResum);
	fclose(fPoblacions);
	
}

void estadistiques(char temperatures[],char poblacions[]){
		
	FILE *fTemperatures;
	int sizeInt = sizeof(int);
	fTemperatures = fopen(temperatures,"rb");
	int temp;
	int j=0;
	
	int i=0,k=0,x=0;
	int max=-100;
	int min=100;
	int promig;
		
	
	

	
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer");
	else
		printf("Fitxer obert correctament")	;
		

	
	FILE *fPoblacions;
	fPoblacions = fopen(poblacions,"rb");
	struct Poblacio pob;
	struct Resum Resum1;
	
	int maxTotal=-100;
	int minTotal=100;
	char poblacioMaxTotal[50];
	char poblacioMinTotal[50];	
	
	rewind(fTemperatures);
	while (fread(&temp, sizeInt,1, fTemperatures) == 1){
		
		if(temp!=99){
			promig=promig+temp;
			if(temp>max)
				max=temp;
			if(temp<min)
				min=temp;
					
		}
		j++;
		if(j==24){
			fread(&pob, sizePoblacio,1, fPoblacions);
			promig=promig/24;
			Resum1.codi = i+1;
			Resum1.max = max;
			Resum1.min = min;
			Resum1.promig = promig;
			
		//	printf("\ncodi = %d max = %d min= %d promig = %d",Resum1.codi,Resum1.max,Resum1.min,Resum1.promig);
			
			if(max>maxTotal){
				maxTotal=max;
				strcpy(poblacioMaxTotal,pob.nomPoblacio);
			}
			if(min<minTotal){
				minTotal=min;
				strcpy(poblacioMinTotal,pob.nomPoblacio);
			}
			j=0;
			min=100;
			max=-100;
			promig=0;
			i++;
		}
		
		
		
	}	
	if(maxTotal!=-100)	
		printf("\nTemperatura maxima de %d a %s",maxTotal,poblacioMaxTotal);
	else
		printf("\nNo hi ha temperatures");
	if(minTotal!=100)	
		printf("\nTemperatura minima de %d a %s",minTotal,poblacioMinTotal);	
	
	
	fclose(fTemperatures);

	fclose(fPoblacions);
}

void exportTemperatures(char temperatures[],char temperaturesCsv[]){
	
	int temp;
	char sTemp[2];
	int j=0,k=0,x=0;
	FILE *fTemperatures;
	int sizeInt = sizeof(int);
	fTemperatures = fopen(temperatures,"rb");
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer");
	else
		printf("Fitxer obert correctament")	;
	
	FILE *fTemperaturesCsv;
	fTemperaturesCsv = fopen(temperaturesCsv,"w");
	if (fTemperaturesCsv == NULL)
		printf("No he pogut obrir el fitxer");
	else
		printf("Fitxer 2 obert correctament");
	
	
	char sCodi[2];
	
	while (fread(&temp, sizeInt,1, fTemperatures) == 1){
	//	printf("%d - %d\n",k+1,temp);
		if(temp!=99 && x==0){
			sprintf(sTemp,"%d",temp);
			sprintf(sCodi,"%d",k+1);
			fputs(sCodi,fTemperaturesCsv);
			putc(';',fTemperaturesCsv);
			fputs (sTemp, fTemperaturesCsv); 
			x++;
		}
		else{
			if(temp!=99){
				sprintf(sTemp,"%d",temp);
				putc(';',fTemperaturesCsv);
				fputs (sTemp, fTemperaturesCsv); 	
			}
		}
		if(temp)
		j++;
		if(j==24){
			if(x!=0){
				putc(10,fTemperaturesCsv); 
			}
			j=0;
			x=0;
			k++;
		}
	
	}
	fclose(fTemperatures);
	fclose(fTemperaturesCsv);	
}

void calor (char temperatures [], char poblacions[]){ //Es un minijoc: genera una temperatura "extrema" aleatoria en un camp, s' ha de dir el camp indicant 
													 //poblacio i hora en un temps determinat per a guanyar si es gunaya la temperatura torna a la normalitat, si es perd la temperatura es mante
	
	srand(time(NULL));
	FILE *fTemperatures;
	fTemperatures = fopen(temperatures,"r+b");
	int temp;
	int i;
	int j=0;
	int sizeInt = sizeof(int);
	int cont=0;
	
	if (fTemperatures == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");
	
	while(fread(&temp, sizeInt,1, fTemperatures) == 1) cont++;
	printf("%d",cont);
	
	int random;
	random= rand()%cont;
	int superTemp=88;
	int guardarTemp;
	
	fseek(fTemperatures,sizeInt*random,SEEK_SET);
	fread(&guardarTemp,sizeInt,1,fTemperatures);
	fseek(fTemperatures,sizeInt*random,SEEK_SET);
	fwrite(&superTemp,sizeInt,1,fTemperatures);
	
	
	FILE *fBinari;	
	struct Poblacio pob;
	
	
	fBinari=fopen(poblacions,"rb");

	if (fBinari == NULL)
		printf("No he pogut obrir el fitxer\n");
	else
		printf("Fitxer obert correctament\n");

	rewind(fBinari);
	
	system("cls");
	printf("S' ha trobat una temperatura extrema de 88 graus en una poblacio, nomes la brigada d' en Pingu es capac de restaurar la temperatura a la normalitat, indica a quina poblacio i a quina hora es troba aquesta temperatura extrema per ajudarlos a baixar la temperatura");
	getch();
	system("cls");
	printf("Digues a quina posicio es troba el valor erroni introduint codi primer i hora despres");
	getch();
	int capturarCodi;
	int capturarHora;
	
	
	int longitud=0;
	int espais=0;
	system("cls");
	printf("Nom poblacio \t \t \t   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23\n");
	rewind(fTemperatures);                   
	while(fread(&temp, sizeInt,1, fTemperatures) == 1) {
		
		if(j==0){
			fread(&pob, sizePoblacio,1, fBinari);
			longitud=strlen(pob.nomPoblacio);
			espais=33-longitud;
			printf("\n%s",pob.nomPoblacio);
			printf("%2d",pob.codiPoblacio);
			for(i=0;i<espais;i++){
				printf(" ");
			}
			//printf("%d",longitud);
			if(temp==99)
				printf("  ");
			else
				printf("%2d",temp);
		}
		else{
			if(temp == 99)
				printf("   ");
			else
				printf(" %2d",temp);	
		}
		j++;
		if(j==24)
			j=0;
	}
	clock_t start = clock(), diff;
	
	
	printf("\n\nDIGUES EL CODI!!   ");
	scanf("%d",&capturarCodi);
	printf("DIGUES LA HORA!!   ");
	scanf("%d",&capturarHora);
	
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	//printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);
	
	if((capturarCodi-1)*24+capturarHora == random && msec/1000 <20){
		fseek(fTemperatures,sizeInt*random,SEEK_SET);
		fwrite(&guardarTemp,sizeInt,1,fTemperatures);
		printf("Felicitats, la brigada d' en Pingu ha aconseguit tornar la temperatura a la normalitat");
	}
	else{
		if((capturarCodi-1)*24+capturarHora == random){
			printf("Has trigat massa, la brigada d' en pingu no ha aconseguit arribar a temps i ha mort tohom, una tragedia...");
		}
		else{
			printf("No has encertat la poblacio o l' hora, per aixo la brigada d' en pingu no ha aconseguit arribar a temps i ha mort tohom, una tragedia...");	
		}
	}
	/*clock_t start = clock(), diff;
	ProcessIntenseFunction();
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000); */
	fclose(fTemperatures);
}

void menu(){
	
	int opcio;
	do{
		getch();
		system("cls");
		printf("1-Generar fitxer poblacions\n");
		printf("2-Visualitzar fitxer poblacions\n");
		printf("3-Modificar fitxer poblacions\n");
		printf("4-Generar fitxer temperatures\n");
		printf("5-Afegir sensor\n");
		printf("6-Visualitzar fitxer temperatures\n");
		printf("7-Consultar temperatura d'' una poblacio\n");
		printf("8-Generar resum\n");
		printf("9-Mostrar estadistiques\n");
		printf("10-Exportar temperatures\n");
		printf("11-Ajuda en Pingu\n");
		printf("0-Sortir\n");
		scanf("%d",&opcio);
		
		switch(opcio){
			case 1:llegir_fitxer("valles.csv","poblacions.dat");break;
			case 2:llegir_binari("poblacions.dat");break;
			case 3:modificarBinari("poblacions.dat");break;
			case 4:generaTemps("poblacions.dat","temperatures.dat");break;
			case 5:afegirSensor();break;
			case 6:llegirTemperatures("temperatures.dat","poblacions.dat");break;
			case 7:consultar("temperatures.dat");break;
			case 8:resum("temperatures.dat","resum.txt","poblacions.dat");break;
			case 9:estadistiques("temperatures.dat","poblacions.dat");break;
			case 10:exportTemperatures("temperatures.dat","temperatures.csv");break;
			case 11:calor("temperatures.dat","poblacions.dat");break;
			case 0:break;
			default: printf("Digues una opcio correcta");
		}
		
	}while(opcio!=0);
}




void main(void) {
	
	menu();
	
}

