#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define FILAS 15
#define COLUMNAS 12


void ganar(){

printf("      #####                                                 	\n");
printf("     #     #    ##    #    #    ##    #####    ####   #####  	\n");
printf("     #     #  #    #  #    #   #  #   #   #   #    #  #    #	\n");
printf("     #  ####  #    #  # #  #  #    #  #    #  #    #  #    # 	\n");
printf("     #     #  ######  #  # #  ######  #    #  #    #  #####  	\n");
printf("     #     #  #    #  #   ##  #    #  #    #  #    #  #   #  	\n");
printf("      #####   #    #  #    #  #    #  #####    ####   #    # 	\n");

	getch();
}
void perder(){
 printf("######                                                 	\n");
 printf("#     #  ######  #####   #####    ####   #####    ##   	\n");
 printf("#     #  #       #    #  #    #  #    #    #     #  #  	\n");
 printf("#     #  #####   #    #  #    #  #    #    #    #    # 	\n");
 printf("#     #  #       #####   #####   #    #    #    ###### 	\n");
 printf("#     #  #       #   #   #   #   #    #    #    #    # 	\n");
 printf("######   ######  #    #  #    #   ####     #    #    # 	\n");
	getch();
}

int elegirDificultad(){
	int dificultad;
	printf("1-Facil        5 minas\n2-Medio       10 minas\n3-Dificil     15 minas\n4-Extremo     30 minas");
	do{
		printf("\nEscoge un nivel de dificultad: ");
		scanf("%d",&dificultad);
	}while(dificultad<1 || dificultad>4);
	return dificultad;
}

int numeroDeMinas(int dificultad){
	int devolver;
	if(dificultad==1)
		devolver=5;
	if(dificultad==2)
		devolver=10;
	if(dificultad==3)
		devolver=15;
	if(dificultad==4)
		devolver=30;
	return devolver;			
}

void iniciar_tablero(char matriz [FILAS][COLUMNAS]){
	int i,j;
	for(i=0;i<FILAS;i++){
		for(j=0;j<COLUMNAS;j++){
			matriz[i][j]='?';
		}
	}
}

void printar_tablero(char matriz [FILAS][COLUMNAS]){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
	int i,j;
	for(i=1;i<FILAS-1;i++){
		printf("%2d  ",i);
		for(j=1;j<COLUMNAS-1;j++){
			if(matriz[i][j]=='*')
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);				
			if(matriz[i][j]>48 && matriz[i][j]<57)
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			if(matriz[i][j]=='.')
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
			if(matriz[i][j]==2)
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);			
			printf("%2c ",matriz[i][j]);
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
		
		printf("\n");
	}
	printf("\n   ");
	for(i=1;i<COLUMNAS-1;i++){
		printf(" %2d",i);
	}
	printf("\n\n\n");
}

void iniciar_tabla_minas(char matriz [FILAS][COLUMNAS],int *limpiables,int dificultad){
	int a,i,j,sum,r1,r2;
	int nminas=0;
	nminas=numeroDeMinas(dificultad);

	for(i=1;i<FILAS-1;i++){ 
		for(j=1;j<COLUMNAS-1;j++){
			matriz[i][j]='.';
		}
	}
	
	*limpiables=(FILAS-2)*(COLUMNAS-2)-nminas;
	while(nminas!=0){
		r1=rand()%13+1;
		r2=rand()%10+1;
		if(matriz[r1][r2]=='.'){
			matriz[r1][r2]='*';
			nminas--;
		}
	}
	
	for(i=1;i<FILAS-1;i++){ //pone numeros donde sea necesario respecto a las minas que hay
		for(j=1;j<COLUMNAS-1;j++){
			if(matriz[i][j]=='.'){
				sum=48;
				if(matriz[i-1][j-1]=='*'){
					sum++;
				}
				if(matriz[i-1][j]=='*'){
					sum++;
				}
				if(matriz[i-1][j+1]=='*'){
					sum++;
				}
				if(matriz[i][j-1]=='*'){
					sum++;
				}
				if(matriz[i][j+1]=='*'){
					sum++;
				}
				if(matriz[i+1][j-1]=='*'){
					sum++;
				}
				if(matriz[i+1][j]=='*'){
					sum++;
				}
				if(matriz[i+1][j+1]=='*'){
					sum++;
				}
				if(sum>48){
					matriz[i][j]=sum;
				}
			}
		}
	}
	
}

void limpiarBlancos(char tablero[FILAS][COLUMNAS],char minas[FILAS][COLUMNAS],int fila,int columna){
	tablero[fila][columna]='.';

	if(minas[fila-1][columna-1]=='.' && tablero[fila-1][columna-1]=='?'){
		limpiarBlancos(tablero,minas,fila-1,columna-1);
	}
	else{
		if((minas[fila-1][columna-1]>48 && minas[fila-1][columna-1]<57)&& tablero[fila-1][columna-1]=='?'){
			tablero[fila-1][columna-1]=minas[fila-1][columna-1];
		}
	}
	
	if(minas[fila-1][columna]=='.' && tablero[fila-1][columna]=='?'){
		limpiarBlancos(tablero,minas,fila-1,columna);
	}
	else{
		if((minas[fila-1][columna]>48 && minas[fila-1][columna]<57)&& tablero[fila-1][columna]=='?'){
			tablero[fila-1][columna]=minas[fila-1][columna];
		}
	}
	
	if(minas[fila-1][columna+1]=='.' && tablero[fila-1][columna+1]=='?'){
		limpiarBlancos(tablero,minas,fila-1,columna+1);
	}
	else{
		if((minas[fila-1][columna+1]>48 && minas[fila-1][columna+1]<57)&& tablero[fila-1][columna+1]=='?'){
			tablero[fila-1][columna+1]=minas[fila-1][columna+1];
		}
	}
	
	if(minas[fila][columna-1]=='.' && tablero[fila][columna-1]=='?'){
		limpiarBlancos(tablero,minas,fila,columna-1);
	}
	else{
		if((minas[fila][columna-1]>48 && minas[fila][columna-1]<57)&& tablero[fila][columna-1]=='?'){
			tablero[fila][columna-1]=minas[fila][columna-1];
		}
	}
	
	if(minas[fila][columna+1]=='.' && tablero[fila][columna+1]=='?'){
		limpiarBlancos(tablero,minas,fila,columna+1);
	}
	else{
		if((minas[fila][columna+1]>48 && minas[fila][columna+1]<57)&& tablero[fila][columna+1]=='?'){
			tablero[fila][columna+1]=minas[fila][columna+1];
		}
	}
	
	if(minas[fila+1][columna-1]=='.' && tablero[fila+1][columna-1]=='?'){
		limpiarBlancos(tablero,minas,fila+1,columna-1);
	}
	else{
		if((minas[fila+1][columna-1]>48 && minas[fila+1][columna-1]<57)&& tablero[fila+1][columna-1]=='?'){
			tablero[fila+1][columna-1]=minas[fila+1][columna-1];
		}
	}
	
	if(minas[fila+1][columna]=='.' && tablero[fila+1][columna]=='?'){
		limpiarBlancos(tablero,minas,fila+1,columna);
	}
	else{
		if((minas[fila+1][columna]>48 && minas[fila+1][columna]<57)&& tablero[fila+1][columna]=='?'){
			tablero[fila+1][columna]=minas[fila+1][columna];
		}
	}
	
	if(minas[fila+1][columna+1]=='.' && tablero[fila+1][columna+1]=='?'){
		limpiarBlancos(tablero,minas,fila+1,columna+1);
	}
	else{
		if((minas[fila+1][columna+1]>48 && minas[fila+1][columna+1]<57)&& tablero[fila+1][columna+1]=='?'){
			tablero[fila+1][columna+1]=minas[fila+1][columna+1];
		}
	}
}

int comprobarVictoria(char tablero[FILAS][COLUMNAS],int limpiables){
	int i,j;
	int sum=0;
	int retornar=0;
	for(i=1;i<FILAS-1;i++){  
		for(j=1;j<COLUMNAS-1;j++){
			if(tablero[i][j]=='.' || (tablero[i][j]>48 && tablero[i][j]<57)){
				sum++;
			}
		}
	}
	if (sum==limpiables){
		retornar=1;
	}
	return retornar;
}

void hacer_jugada(char tablero [FILAS][COLUMNAS],char minas [FILAS][COLUMNAS],int *fin,int limpiables){
	int eleccion;
	int fila,columna;
	
	do{
	printf("Liberar espacio (1) o colocar bandera (2)");
	scanf("%d",&eleccion);
	}while(eleccion!=1 && eleccion!= 2)	;
	
	if(eleccion==1){
		printf("Escoge una fila: ");
		scanf("%d",&fila);
		printf("Escoge una columna: ");
		scanf("%d",&columna);
		tablero[fila][columna]=minas[fila][columna];
		if(tablero[fila][columna]=='*'){
			*fin=*fin+1;
			system("cls");
			printar_tablero(tablero);
			perder();
		}
		if(tablero[fila][columna]=='.'){
			limpiarBlancos(tablero,minas,fila,columna);
		}
		
		if(comprobarVictoria(tablero,limpiables)==1){ //caso victoria
			*fin=*fin+1;
			system("cls");
			printar_tablero(tablero);
			ganar();
		}
			
	}
	else{
		printf("Digues una fila");
		scanf("%d",&fila);
		printf("Digues una columna");
		scanf("%d",&columna);
		if(tablero[fila][columna]=='?'){
			tablero[fila][columna]=2;
		}
	}
}

void juego(){
	
	system("cls");
	char tablero [FILAS][COLUMNAS]; 
	char minas [FILAS][COLUMNAS];
	int fin=0;
	int limpiables=0; //casillas libres por descubrir, al tenerlas todas descubiertas gana
	int dificultad=0;
	
	iniciar_tablero(tablero);
	printar_tablero(tablero); //0=libre, 1=mina, 2=banderita
	iniciar_tablero(minas);
	dificultad=elegirDificultad();
	iniciar_tabla_minas(minas,&limpiables,dificultad);	

	while(fin!=1){
		system("cls");
		printar_tablero(tablero);
		hacer_jugada(tablero,minas,&fin,limpiables);
		system("cls");
	}
	system("pause");
	system("cls");
}

void instrucciones(){
	printf("Como jugar:\n Esta version del buscaminas consiste en un tablero con casillas ocultas sobre el que tendremos que ir\n revelando las casillas, al caer en una mina se pierde, al caer sobre un blanco se mostrara un punto el\n qual significara que esa casilla esta vacia, a su vez mostrara las casillas de alrededor hasta encontrar\n un numero, al caer en un numero se revelara dicho numero. Los numeros indican la cantidad de minas que\n hay alrededor de esa casilla. En esta version no se empezara siempre con un espacio en blanco, esto hace\n que el juego tenga a su vez un factor de aleatoriedad aumentando las posiblidades de que pierdas.\nTambien incluye la posiblidad de poner banderas por el mapa, cuya funcion es ayudar al jugador recordandole\n donde puede haber una mina.");
	getch();
}

void autor(){
	printf("\nJuego creado unica y exclusivamente por Ivan Sanchez 'El potato'");
	getch();
}

void bienvenida(){
	
	int menu=0;
	do{
		system("cls");
		printf("	.______    __    __       _______.  ______     ___      .___  ___.  __  .__   __.      ___           _______.\n");
		printf("	|   _  \\  |  |  |  |     /       | /      |   /   \\     |   \\/   | |  | |  \\ |  |     /   \\         /       |\n");
		printf("	|  |_)  | |  |  |  |    |   (----`|  ,----'  /  ^  \\    |  \\  /  | |  | |   \\|  |    /  ^  \\       |   (----`\n");
		printf("	|   _  <  |  |  |  |     \\   \\    |  |      /  /_\\  \\   |  |\\/|  | |  | |  . `  |   /  /_\\  \\       \\   \\    \n");
		printf("	|  |_)  | |  `--'  | .----)   |   |  `----./  _____  \\  |  |  |  | |  | |  |\\   |  /  _____  \\  .----)   |   \n");
		printf("	|______/   \\______/  |_______/     \\______/__/     \\__\\ |__|  |__| |__| |__| \\__| /__/     \\__\\ |_______/   \n\n\n");
		printf("1-Jugar\n");
		printf("2-Como jugar\n");
		printf("3-Sobre el autor\n");
		printf("4-Salir\n");
		scanf("%d",&menu);
		switch(menu){
			case 1:
				juego(); 
				break;
			case 2:
				instrucciones();
				break;
			case 3:
				autor();
				break;		
		}
		
	}while(menu!=4);
	system("pause");
	system("cls");

}

void despedida(){
	system("cls");
	printf("Gracias por jugar\n");
	system("pause");
	system("cls");
}


int main (){
	
	srand(time(NULL));
	
	bienvenida();
	
	despedida();
	
	return 0;
}

