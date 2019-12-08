//   "CASINO COYOTE"
//   JUEGO HECHO POR:
//
//   Diego Arturo Velàzquez Trejo  ENP 6
//   Heriberto Toscano Delgado     ENP 6
//   Mariano Salero Narvàez        ENP 6
//
//   Para concursos interpreparatorianos 2017-2018
//   ¡Gracias por jugarlo!
// 
//   VERSION 1.0

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

bool Comenzarajugar=false;
bool division; //Esta es la función booleana que nos devuelve un valor verdadero si es posible dividir
bool boolJuegoDiv; //Esta función nos devuelve un valor verdadero si se dividió
bool boolAseg;  //Esta función booleana nos devuelve un valor verdadero si es posible asegurar 
bool AsegurarAp=false; //Nos permite devolver un valor verdadero si el usuario aseguró, y por ende, apostó
bool doblarr; //Devuelve valor verdadero si el usario dobló
bool bprepa9;  // Devuelve verdadero si se esta en prepa 9, nos ayuda para mandar el mensaje del boss final
bool totem;    // Devuelve verdadero si se juega contra el totem (boss final)
bool modohistoria; //Devuelve verdadero si se juega el modo historia
bool wintotem;  //Devuelve verdadero si se le gana al totem
bool blackjack0;
bool bool0win; 
bool bool0tie;
bool bool2win;
bool bool2tie;
/* Estas funciones booleanas nos devuelven un valor verdadero si las manos con las que juega el jugador ganan(en el caso de bool0win y bool2win)
o empatan(bool0tie y bool2tie) y falso si la condicional no se cumplió, el número 0 en las funciones de nuestro juego normalmente indican que se
trata de la mano 1, que siempre se genera y el 2 es para la mano que se genera cuando divides */ 
int dinjugador;
int n1=0; //apuesta a la mano default
int n2=0; //Apuesta a la mano que se dividio
int n3=0; //Apuesta a asegurar
int v=0;  //Almacena variables de las apuestas
int b=0;
int z;
int xp, yp;
char m1[151], m2[100] , m3[100], m4[100],m5[100], np[2];//estas cadenas almacenan los mensajes de los alumnos de cada plantel
/* n1, n2 y n3 son variables que tendrá la cantidad apostada por el usuario a lo largo del transcurso de cada juego, n1 tiene la apuesta de 
la mano 1, n2 de la mano 2 y n3 de la apuesta de asegurar */
void marco(int xm, int ym, int xi,int yi, int con, int color, int fon);//crea un marco de color y puede desplegar ciertos mensajes en la pantalla
void impmen ( char cad[],int tam);//perite que los mensajes enviados a pantalla enten correctamente escritos
char nombre[18], nombre2[18];
char mat[17][11];
char matCartaComp[14][7];
char MatrizMensaje[53][5];
char Principal[87][16];
char Tab[126][17];
int mano [12][28]={{0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0},
                   {0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0},
                   {0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0},
                   {0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0},
                   {0,2,1,2,1,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,1,2,1,2,0},
                   {0,2,1,2,1,2,1,2,2,0,2,2,0,0,0,0,2,2,0,2,2,1,2,1,2,1,2,0},
                   {0,2,1,2,1,2,1,2,2,0,2,2,0,0,0,0,2,2,0,2,2,1,2,1,2,1,2,0},
                   {0,2,1,2,1,2,1,2,2,2,2,2,0,0,0,0,2,2,2,2,2,1,2,1,2,1,2,0},
                   {0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0},
                   {0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0},
                   {0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
                   {0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0}};//almacena el diseño de las manos
int xf,yf, ficha[12][24], ficha2[12][24];
int Score1, Score0, Score2;
/*La estructura Elementos es aquella que contiene los valores de cada jugador: la variable valChng es aquella que llevará un control 
de las cartas "A´s" que tiene la partida de cada jugador para poder controlar parte de la función de ValidacionAs, el valor de sumaNum
será aquel que contenga la sumatoria de los valores de las cartas de cada jugador. conteoCartas es la variable que nos llevará un conteo 
de las cartas que se van solicitando a lo largo de la partida, para controlar la función de CrearCarta. Por otra parte la variable 
de boolResta nos indicará si se puede llevar a cabo la resta de 10 cuando una carta A pasa de tener valor de 11 a 1 en caso que sea necesario.
Finalmente las variables BoR´s son aquellas que irán retornando su valor a verdadero en el caso que la función de ValidacionAs le asigne un 
valor de 11 a alguna carta "A". Teniendo estos valores en verdadero de ser el caso, se efecturará la resta.*/
struct Elementos{
       int valChng;
       int sumaNum;
       int conteoCartas;
       bool boolResta;
       bool BoR1; 
       bool BoR2; 
       bool BoR3; 
       bool BoR4;     
       bool Juego;        
}Player[3]; //Player[0] es el usuario inicial. Player[1] será la computadora y finalmente Player[2] será el juego en donde se divida la partida. 
/*La estructura carta tiene los elementos que nuestras cartas poseerán: sus coordenadas en X y en Y y por otra parte el símbolo aleatorio de cada carta
El número aleatorio que tendrá y su color.*/
struct carta{ 
       int CoordX;
       int CoordY;
       int randSim;   
       int randNum;
       int color;    
              
}cartas[48]; 

void Juego(int apmax, int apmin);
int apuesta1(int apmax, int apmin); //Función que se llama para ejecutar menú de apuesta
void Ocultar();
void gotoxy1(int x,int y);
/*La función de inicio hace la lectura del archivo txt en donde almacenamos una matriz bidimensional que contiene la interfaz del nombre 
que aparece en la primera parte del juego. */
void Inicio();
/*Esta función se encarga de hacer la lectura desde el archivo txt donde yacen las instrucciones.*/
void lecturaInstrucciones();
/*La función de lecturaJugadores abrirá un archivo txt en donde se van almacenando todos los usuarios que 
han jugado el Casino Coyote junto con sus bolsas de dinero*/
void lecturaJugadores();
/* La función de PrincipalFrame es la primera interfaz del juego en donde aparece el menú con la opción de jugar
aparece la tabla de jugadores y las instrucciones. Esta función abre archivos de texto en donde tenemos el nombre decorativo y las
instrucciones del juego.*/
void PrincipalFrame();
/*La función de mensaje es aquella que desplegará el mensaje al terminar la partida. Su parámetro de entrada será 
aquél número al archivo que se mandará a leer.*/
void Mensaje(int NumMensaje);
void scenary(int color1, int color2, int color3);
/*La función de inizializar es aquella que inicializa en cero todos nuestros valores de la estructura elementos y 
de la estructura cartas.*/
void inicializar();
/*DefBaraja es la función que defiriná las coordendas en donde se irán mostrando las cartas,
definirá también los elementos de la estructura de cartas: numero aleatorio que tendrá la carta,
su símbolo aleatorio y definirá su color. Este proceso se hará tanto para las cartas de la computadora
como las cartas del jugador. Por otra parte, si es que llegan a salir dos cartas del mismo valor,
esta función cambiará el valor de division a verdadero para que se pueda ejecutar el menú preguntando al jugador si
desea dividir.*/
void DefBaraja();
/*La función de ValidacionAs es aquella que recibe como parámetros de entrada los valores de valChng(Variable propia de
cada jugador que hará un conteo de las cartas "A´s" que se tengan para llevar un control al momento
de ajustar el valor a uno(1) u once(11)), NoC(Número de cartas), y por último tendrá como parámetro de entrada el número del jugador 
que se encuentra jugando por el momento. Ésta función, dependiendo los casos en los que pueda salir una carta "A", le retornará el valor
de 1 u 11 a la carta según sea el caso.Para llevar un control más preciso, retorna verdadero los valores de BoR(1-4), 
mismos valores que darán pie a la resta de 10 en el caso de que en el juego haya una carta "A" que originalmente haya valido
11 y ahora requiera disminuir su valor a 1.*/
int ValidacionAs(int valCg, int NoC, int p);
/*La función de animacion va a dar una ligera sensación de que se están volteando las cartas a la hora de jugar. Recibe como 
parámetros de entrada el número de carta a la que le hará la animación y el jugador que solicitó la carta.*/
void animacion(int w, int J);
/*La función de CleanCrds será la que limpie todas las cartasdel juego anterior, tanto del jugador como
de la computadora,  para poder volver a jugar.*/
void CleanCrdS();
/*La función de dividir es aquella que despliega un menú preguntándole al jugador si desea dividir, en cierto caso...
*/
void dividir(); //Esta función ejecuta el menú para dividir
void Aseg();    // Menú de asegurar
/*Nuestro programa va creando aleatoriamente las cartas al momento de que se pidan, para ello la función CrearCarta que tiene como
parámetros de entrada el número de carta que se está solicitando, el jugador que lo solicita que tiene como posibles valores el 0 o 1. Por último 
tiene como tercer parámetro Ju que alude a la estructura de Elements y puede tomar como valor el 0,1 o 2. Esta función
inicialmente abre aleatoriamente un archivo de texto en donde aguardan uno de los cuatro símbolos posibles para la carta.
Lo pone en la carta que estpa creando y según sea el número aleatorio de la carta que se está solicitando, lo pone en el extremo superior izquierdo.
Esta función tiene por otra parte a la función de ValidaciónAS, misma que le asignará el símbolo de A a la carta y que establecerá su valor.
Por último, pondrá el símbolo "K", "J", "Q" si es que el número aleatorio de esa carta estuvo en el margen de 11 a 13.*/
void CrearCarta(int w, int J, int Ju);
/*La función de AlgJueComp será aquella que controle el juego de la computadora, está condicionada para ir pidiendo cartas
siempre y cuando la sumatoria de sus valores sea menor o igual a 17. Esta función tiene los BoR´s que controlan los valores de A
para poder restarle 10 al juego de la computadora en caso de que haya tenido una carta A y se haya pasado de 21.*/
void AlgJueComp();
/*La función de AlgJue es la encargada de poder controlar la forma en la que el usuario puede jugar. Esta función integra las funciones de
dividir y de doblar al igual que controla las cartas que vas pidiendo. Podrás pedir la cantidad de cartas que quieras siempre y cuando
la suma de sus valores no sobrepase el 21.Esta función también va a llevar a cabo la resta a la sumatoria de los valores de las cartas
en el caso que exista una carta "A" con valor de 11 y su suma haya sobrepasado el 21 para así darle a la carta "A" el valor de 1.*/
void AlgJue();
/*La función de jugar integrará a las funciones de DefBaraja y AskCrd, y será aquella que ejecutará el juego de cada uno. Si su parámetro 
de entrada es o, jugará el usuario, si es 1 jugará la computadora y si es 2 jugará el segundo juego en caso de ser dividido.*/
void jugar(int JU); 
void DefGan(int S0, int S1, int S2);
void menuPregunta(); //Pregunta si se quiere jugar de nuevo
int doblar(int apuesta);//Dobla la apuesta cuando el usuario lo solicita 
void limpiarmsj();//borra de la pantalla los menús
void borrarmano();//coloca caracteres '219' de color verde 
void bormat();//llena las matricez ficha y ficha 2 con 0
void manita();//imprime en la pnantalla el dibujo de las manos
void lecfich(int cordx, int cordy,int numrand, int confich, int mat[][24]);//le los archivos de los montones de las fichas y los almacena en una matriz
void fichas(int nfich, int colfich);//coloca fichas en el tablero 
void dinero();//Da las ganancias de las apuestas si el usuario gana, también regresa si empata
void distrito(); //Mapa de la CDMX
void prepa1();//le el atchivo de p1 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 1
void prepa2();//le el atchivo de p2 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 2 
void prepa3();//le el atchivo de p3 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 3 
void prepa4();//le el atchivo de p4 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 4 
void prepa5();//le el atchivo de p5 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 5
void prepa6();//le el atchivo de p6 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 6 
void prepa7();//le el atchivo de p7 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 7 
void prepa8();//le el atchivo de p8 y lo dibuja en la pantalla ,asigna mensajes a m1,m2,m3,m4ym5, permite la entrada al casino de prepa 8
void prepa9(); //Juego en las prepas 
void monito(int xmin, int xmax, int ymin, int ymax, int xm1, int xm2, int xm3, int xm4, int xm5, int ym1, int ym2, int ym3, int ym4, int ym5, int color);/*permite que el protagonista se mueva en los mapas que delimita esta funcion y genera a los alumnos de los 9 planteles  
y permite el acceso al casino de cada prepa*/
void mon(int x1, int y1);//imprime un alumno en las cordenadas indicadas
void lectur(char nprepa[2]);//lee el archivo de la prepa seleecionada en la cadena y los manda a la pantalla
void menudf();
void ganarfinal(); //pantalla cuando se gana el modo historia

int main(){
  system("mode con cols=170 lines=60");
  marco(82,17,34,14,2,12,2);
  getchar();
  system("CLS");
  Sleep(750);
  Inicio();
  PrincipalFrame(); 
  return 0;
}
void gotoxy1(int x,int y){  
  HANDLE handle;  
  handle=GetStdHandle(STD_OUTPUT_HANDLE);  
  COORD coordenada;  
  coordenada.X=x;  
  coordenada.Y=y;  
  SetConsoleCursorPosition(handle,coordenada);  
}

void lecturaInstrucciones(){
     char Arch[1000], tecla;
     int i, c;
     i=0;
     FILE * archivo;
     archivo=fopen("c:\\cartas\\instrucciones.txt", "r");
     while((c=fgetc(archivo)) != EOF)
	 {
          if(c=='\n') 
              printf("\n"); 
          else
		  {
              textcolor(15);
              if(c == '*') 
                 putchar(160);
              else if(c == '-')
                 putchar(161);
              else if(c == '?')
                 putchar(130);
              else 
                 putchar(c);
          }   
     }
     fclose(archivo);     
     printf("\n\n\n\n%cDesea Regresar al men%c de inicio?", 168,163);
     printf("\n\nEXIT"); 
     printf(" <- ");
     tecla = getch();
     if(tecla != 0)
	{
         system("CLS");
         Inicio();
         PrincipalFrame();         
     }
     return;      
}
void lecturaJugadores(){
     char Arch[1000], tecla;
     int i, c, k;
     i=0;
     FILE * archivo;
     archivo=fopen("c:\\cartas\\Jugadores.txt", "r");
     while((c=fgetc(archivo)) != EOF)
	 {
          if(c=='\n') 
              printf("\n"); 
          else if(c == '#')
          { 
                  putchar(219);
                  textcolor(4);
          }
          else  
          {
                  putchar(c);
                  textcolor(15);
          }
            
     }
     fclose(archivo);
     DefBaraja();
     for(k = 0; k<8; k++)
          CrearCarta(k, 0, 0);
     gotoxy(2,24);
     textcolor(15);
     printf("\n\n\n\n%cDesea Regresar al men%c de inicio?", 168,163);
     printf("\n\nEXIT"); 
     printf(" <- ");
     tecla = getch();
     if(tecla != 0)
	{
         system("CLS");
         Inicio();
         PrincipalFrame();         
     }
     return;      
}
void PrincipalFrame(){
     dinjugador=0;
     char  letra, TEC;
     int l=0, i=0, o=0;
     int x=82,y=22;
     for(i=0; i<25; i++)
	 {
          for(o=0; o<20; o++)
		  {
             textbackground(15); 
             gotoxy1(i+60,o+21); putchar(' ');
          }
     }
     gotoxy1(66, 22);
	 textcolor(0);
	 printf("MODO HISTORIA");
     gotoxy1(69, 26);
	 textcolor(0);
	 printf("JUGAR");
     gotoxy1(64,30); 
	 textcolor(0); 
	 printf("TABLA DE PUNTAJES");
     gotoxy1(65,34); 
	 textcolor(0); 
	 printf("INSTRUCCIONES");
	 gotoxy1(69,38); 
	 textcolor(0); 
	 printf("SALIR");
     gotoxy1(x,y); 
	 textbackground(11); 
	 textcolor(15); 
	 printf("<-");
     while(TEC!=13 )
	 {    
        if(kbhit())
		{
         gotoxy1(x,y); 
		 textbackground(15); 
		 printf("  ");
         TEC=getch();
         if(TEC=='w' && y<=38 && y>=26||TEC=='W' && y<=38 && y>=26) 
		 	y=y-4;
         if(TEC=='s' && y>=22 && y<=34||TEC=='S' && y>=22 && y<=34) 
		 	y=y+4;  
         gotoxy1(x,y);  
		 textbackground(11); 
		 textcolor(15); 
		 printf("<-");                    
        }
     }
     if(TEC==13 && y==22)
     {
          dinjugador= 500;
          modohistoria=true;
          gotoxy1(64, 23); 
          textbackground(15);
          textcolor(2);
          printf("Ingresar su nombre: ");
          gotoxy1(64, 24);
          strcpy(nombre2,"                  ");
          while(letra!=13)
		  {
                letra=getch();
                if(isalpha(letra)!=0 && l<19)
				{ 
                    textcolor(0);
                    putchar(letra);
                    nombre2[l]=letra;
                    l++;
                }
          }
          strcat(nombre2, "\0");
          textbackground(0);
          menudf();
     }      
     if(TEC==13 && y==26)
	 { 
          dinjugador=5000;
          Comenzarajugar=true;
          gotoxy1(64, 27); 
          textbackground(15);
          textcolor(2);
          printf("Ingresar su nombre: ");
          gotoxy1(64, 28);
          strcpy(nombre,"                  ");
          while(letra!=13)
		  {
                letra=getch();
                if(isalpha(letra)!=0 && l<19)
				{ 
                    textcolor(0);
                    putchar(letra);
                    nombre[l]=letra;
                    l++;
                }
          }
          strcat(nombre, "\0");
          textbackground(0); 
          Comenzarajugar==true;
          scenary(2,15,12);
          Juego(10000,1);
     }
     else if(TEC == 13 && y == 30)
     {
        textbackground(0);
	 	system("CLS");
	 	lecturaJugadores();
      }
     else if(TEC == 13 && y == 34)
	 {
          textbackground(0);
          system("CLS");  
          Inicio();
          lecturaInstrucciones();      
     }
     else if(TEC == 13 && y == 38)  
          exit(0);  
     return;     
}
void Inicio(){
     int col=0,ren=0,i=0, o=0;
     char tecla;
     system("CLS");
     FILE *archivo; 
     archivo = fopen("c:\\cartas\\principal.txt", "r");
     while(!feof(archivo))
	 {
            tecla=fgetc(archivo);
            tecla != '\n' ? ((Principal[col][ren] = tecla) & (col++)): ((ren++)&(col=0));         
     } 
     for(i=0; i<16; i++){
        for(o=0; o<87; o++){
           gotoxy1(32+o,3+i);
           switch (Principal[o][i])
             {
                case '0' :
                        putchar(' ');
                        break;
                case '1' :
                        textcolor(10);
                        putchar(219);
                        break;
                case '2' :
                        textcolor(12);
                        putchar(219);
                        break;
                case '3' :
                        textcolor(5);
                        putchar(219);
                        break;
                case '4' : 
                        textcolor(12);
                        putchar(219);
                        break;
                case '5' : 
                        textcolor(4);
                        putchar(219);
                        break;
                case '6' : 
                       textcolor(5);
                       putchar(219);
                       break; 
             }
        }
            
    }
    fclose(archivo);
    return;     
}
void Mensaje(int NumMensaje){ 
     int i=0, k=0, col = 0, ren = 0, j = 0;
	 char nomar[30], numcad[5], tecla;
	 strcpy(nomar, "c:\\cartas\\mensajes\\n");
     sprintf(numcad, "%d", NumMensaje);
     strcat(nomar, numcad);
     strcat(nomar, ".txt");
     FILE *arch;
     arch= fopen(nomar, "r");
     while(!feof(arch))
        {
             tecla = fgetc(arch);
	         tecla != '\n' ? ((MatrizMensaje[col][ren] = tecla) & (col++)): ((ren++)&(col=0)); 
        } 
     for(i=0; i< 5; i++)
	 {
        for(j=0; j < 53; j++)
		{
             textcolor(14);
             textbackground(4);
             gotoxy1(j+59,i+18);
             putchar(MatrizMensaje[j][i] == '1' ? 219 : ' ');
        }        
     }
    Sleep(1500);
    for(i=0; i < 5; i++)
	{
        for(j=0; j < 53; j++)
		{
             gotoxy1(j+59,i+18); 
             (NumMensaje == 3) ? textbackground(0) : textbackground(2);
             putchar(' ');
        }
    }
    textbackground(0);
    gotoxy1(59,16); textbackground(2); printf("           "); textbackground(0); 
    fclose(arch);
    return;
}
void scenary(int color1, int color2, int color3){
     int col=0, ren=0, i=0, o=0;
     char tecla;
     FILE *arch; 
     system("CLS");
     arch=fopen("c:\\cartas\\tablero.txt", "r");
     Sleep(1000);
     for(i=1; i<29;i++)
	 {
          textcolor(14);
          gotoxy1(1,i); 
		  putchar(186);
          gotoxy1(27,i); 
		  putchar(186);
          gotoxy1(154,i); 
		  putchar(186);
     }
    for(i=1; i<128; i++)
	{
         textcolor(14);
         gotoxy1(i+26,1); 
		 putchar(205);
         gotoxy1(i+26, 29); 
		 putchar(205);       
    }
    for(i=1; i<27; i++)
	{
         textcolor(14);
         gotoxy1(i,29); 
		 putchar(205); 
         gotoxy1(i,1); 
		 putchar(205);  
    } 
    gotoxy1(27,29); 
	textcolor(14); 
	putchar(200);
    gotoxy1(1,1); 
	putchar(201);
    gotoxy1(154, 1); 
	putchar(187);
    gotoxy1(154, 29); 
	putchar(188);
    gotoxy1(1,29); 
	putchar(200);
    gotoxy1(27,1); 
	putchar(203);
    gotoxy1(27,29); 
	putchar(202);
    textcolor(0);
    gotoxy1(2,22); 
	textbackground(12); 
	textcolor(15);  
	textbackground(14);
    gotoxy1(2,23); 
	textcolor(4);
	printf("  Para solicitar cartas  "); 
	gotoxy1(2,24); 
	textbackground(14);
	textcolor(4);
    printf("     PRESIONAR 'A'       "); 
	textbackground(0);
    gotoxy1(2,25); 
	textbackground(12); 
	textcolor(14);
	printf("  Si no deseas otra carta", 140); 
	textbackground(0);
    gotoxy1(2,26); 
	textbackground(12); 
	textcolor(14);
	printf("     PRESIONAR ENTER     "); 
	textbackground(0);
    while(!feof(arch))
        {
            tecla=fgetc(arch);
            tecla != '\n' ? ((Tab[col][ren] = tecla) & (col++)): ((ren++)&(col=0));         
        } 
    for(i=0; i<17; i++)
	{
        for(o=0; o<126; o++)
		{
           gotoxy1(28+o,12+i);
           switch (Tab[o][i])
             {
                case '1' :
                        textcolor(color1);
                        putchar(219);
                        break;
                case '2' :
                        textcolor(color2);
                        putchar(219);
                        break;
                case '3' :
                        textcolor(color3);
                        putchar(219);
                        break;
             }
        }
            
    }
    fclose(arch);
    gotoxy1(110,15);
    textbackground(11);
    if(modohistoria==false)
           printf("%s", nombre);
    else
           printf("%s", nombre2);
    textbackground(0);
    return;     
}
void inicializar(){
     int i=0, k= 0;
     for(k=0; k<3; k++)
     {
         Player[k].sumaNum = 0; 
         Player[k].valChng = 0; 
         Player[k].BoR1 = false;
         Player[k].BoR2 = false;
         Player[k].BoR3 = false;
         Player[k].BoR4 = false;         
     }
 	 Player[0].conteoCartas=0;
 	 Player[2].conteoCartas=17;
     Player[1].conteoCartas=32;
     for(i=0; i<48; i++)
	   {
          cartas[i].color=0;
          cartas[i].randNum=0;
          cartas[i].randSim=0;
          cartas[i].CoordX=0;
          cartas[i].CoordY=0;                        
       }
     return;      
}
void DefBaraja(){ 
     inicializar();
     int a=0, b=0, s=0, d=0,f=0, h=0, i=0;
     srand(time(NULL));  
     for(b=0; b<=48; b++)
		{ 
            cartas[b].randSim = rand()%4+1; 
            cartas[b].randNum = rand()%13+1;
            cartas[0].randSim = cartas[16].randSim;               
            cartas[b].color = rand()%2+1;
            cartas[0].color = cartas[16].color;
        }
     cartas[16].randNum = cartas[0].randNum; 
     for(i=0; i<8; i++)
	 {
         cartas[i].CoordX=1+a;
         cartas[i+8].CoordX=1+a;
         a=a+19;
         cartas[i].CoordY=30;
         cartas[i+8].CoordY=30;  
     }
     for(i=32; i<40; i++)
	 {
         cartas[i].CoordX=28+ d;
         cartas[i+8].CoordX=28+ d; 
         d=d+16;
         cartas[i].CoordY=2;
         cartas[i+8].CoordY=2; 
     }
     for(i=16; i<24; i++)
	 {
         cartas[i].CoordX=3+f;
         cartas[i+8].CoordX=3+f;
         f=f+19;
         cartas[i].CoordY=36;
         cartas[i+8].CoordY=36;
     }
     division=false;
     if(cartas[0].randNum == cartas[1].randNum && dinjugador>=z || cartas[0].randNum>=10 && cartas[1].randNum>=10 && dinjugador>=z)
           division=true;
     if((cartas[32].randNum == 10) || (cartas[32].randNum==1) || (cartas[32].randNum==11) || (cartas[32].randNum==12) || (cartas[32].randNum==13))
	 	   boolAseg=true;
	 else
	  	   boolAseg=false;
     return;     
}
int ValidacionAs(int valCg, int NoC, int p){
       if(NoC == 0 || NoC == 16)
	   {
		   Player[p].BoR4=true; 
		   return 11;
	   }
       else if(NoC==17 && Player[2].sumaNum<=10)
	   {
		   Player[p].BoR4=true; 
		   return 11;
	   }
       else if(NoC>=18 && Player[2].valChng != 0)
	   		return 1;
       else if(Player[p].sumaNum == 10)
	   		return 11;
       else if(Player[p].sumaNum >10)
	   		return 1;
       else if(Player[p].sumaNum <10 && NoC>1)
	   {
		    Player[p].BoR2=true;
		    return 11;
	   }
       else if((NoC == 1 || NoC == 17) && valCg== 1)
	   return 1;
       else if((NoC == 1 || NoC ==17) && valCg==0 && Player[p].sumaNum<=10)
	   {
	   Player[p].BoR3=true; 
	   return 11;
	   }
       else return 1;
}
void animacion(int numcartas, int J){
     int i= 0, n= 0;
     if(J==0){     
        gotoxy1(cartas[numcartas].CoordX, cartas[numcartas].CoordY);
        textbackground(15);
        for(n=cartas[numcartas].CoordY; n<= cartas[numcartas].CoordY+13; n++){
                   for(i= cartas[numcartas].CoordX; i<= cartas[numcartas].CoordX + 16; i++){ 
                       gotoxy1(i,n);
                       (cartas[numcartas].color == 1) ? textcolor(12) : textcolor(0); putchar(206);
                       }
                    }
        textbackground(0);
     }
     else if(J==2){
        textbackground(15);
        for(n=cartas[numcartas].CoordY; n<= cartas[numcartas].CoordY+6; n++){
                   for(i= cartas[numcartas].CoordX; i<= cartas[numcartas].CoordX + 13; i++){ 
                       gotoxy1(i,n);
                       (cartas[numcartas].color == 1) ? textcolor(0) : textcolor(12); putchar(206);
                       }
                    }
        textbackground(0);
     }
     else if(J==3){     
        gotoxy1(cartas[numcartas].CoordX, cartas[numcartas].CoordY);
        textbackground(0);
        for(n=cartas[numcartas].CoordY; n<= cartas[numcartas].CoordY+13; n++){
                   for(i= cartas[numcartas].CoordX; i<= cartas[numcartas].CoordX + 16; i++){ 
                       gotoxy1(i,n);
                       putchar(' ');
                       }
                    }
        textbackground(0);
     }
     Sleep(200);
     return;      
}
void CleanCrdS(){ 
        int i=0, o=0;
		for(o=1; o<=153; o++)
		{
           for(i=30; i<= (Score2 != 0 ? 53 : 43); i++)
		   {
               gotoxy1(o,i); 
			   printf(" ");  
           }
        }
        gotoxy1(cartas[0].CoordX+1, cartas[0].CoordY-2);
        textcolor(11); 
		printf("SUMA DE TUS CARTAS:     ");  
        for(o=28; o<=153; o++)
		{
           for(i=2; i<=10; i++)
		   {
               gotoxy1(o,i); 
			   printf(" ");  
           }
        }  
        gotoxy1(cartas[32].CoordX, cartas[32].CoordY+7);
        printf("                   ");     
}
void dividir(){
    int x=17,y=10,i=0,o=0;
    char flecha;
    for(i=2; i<26; i++)
	{ 
		gotoxy1(i,8); 
		putchar(205); 
		gotoxy1(i,13); 
		putchar(205);
	}
    gotoxy1(4, 8); 
	textcolor(0); 
	textbackground(15); 
	printf("%cDividir la partida?", 168);
    gotoxy1(7, 10); 
	textbackground(14); 
	textcolor(0); 
	printf("%c %c %c SI", 3,4,5);
    gotoxy1(7, 12);
	textbackground(12); 
	textcolor(15);
	printf("%c %c %c NO", 6,5,4);
    gotoxy1(x,y); 
	textbackground(11); 
	textcolor(4); 
	printf("<-");
    while(flecha!='a' && flecha!='A' && flecha!=13 )
	{    
        if(kbhit())
		{
	         gotoxy1(x,y); 
			 textbackground(0); 
			 printf("  ");
	         flecha=getch();
	         if(flecha=='w' && y==12||flecha=='W' && y==12)
			  	y=y-2;
	         if(flecha=='s' && y==10||flecha=='S' && y==10) 
			 	y=y+2;
	         gotoxy1(x,y);  
			 textbackground(11); 
			 textcolor(4); 
			 printf("<-");                   
        }
    }
    textbackground(0);
    boolJuegoDiv=false;
    if(flecha==13 && y==10)
	{ 
                  animacion(0,3); 
                  if(cartas[0].randNum !=11) 
				       Player[0].sumaNum=Player[0].sumaNum-cartas[0].randNum; 
                  else if(cartas[0].randNum==11) 
				  {
					  Player[2].BoR4=true; 
	                  Player[0].valChng=Player[0].valChng-1; 
					  Player[0].sumaNum=11;
	                  Player[2].valChng=1;
                  } 
                  gotoxy1(cartas[0].CoordX+1, cartas[0].CoordY-2);
                  textcolor(11);  
				  printf("SUMA DE TUS CARTAS: %i ", Player[0].sumaNum); 
                  boolJuegoDiv=true;
                  Player[2].sumaNum= Player[2].sumaNum+cartas[0].randNum;
	} 
    else if(flecha == 'a' || flecha =='A') 
		  dividir();
    for(i=8; i<14; i++)
	{
       for(o=2; o<26; o++)
	   {
          gotoxy1(o,i); 
		  printf(" ");
    	}
    }
     return;     
}
void Aseg(){
    int x=17,y=5,i=0,o=0;
    char flecha;
    for(i=2; i<26; i++)
	{ 
		gotoxy1(i,3); 
		putchar(205); 
		gotoxy1(i,8); 
		putchar(205);
	}
    gotoxy1(4, 3); 
	textbackground(15); 
	textcolor(0);
	printf("%cDesea asegurar?", 168);
    gotoxy1(7, 5); 
	textbackground(14); 
	textcolor(0); 
	printf("%c %c %c SI", 3,4,5);
    gotoxy1(7, 7);
	textbackground(12); 
	textcolor(15);
	printf("%c %c %c NO", 6,5,4);
    gotoxy1(x,y); 
	textbackground(11); 
	textcolor(4); 
	printf("<-");
    while(flecha!='a' && flecha!='A' && flecha!=13 )
	{    
        if(kbhit())
		{
	         gotoxy1(x,y); 
			 textbackground(0); 
			 printf("  ");
	         flecha=getch();
	         if(flecha=='w' && y==7||flecha=='W' && y==7) 
			 	y=y-2;
	         if(flecha=='s' && y==5||flecha=='S' && y==5) 
			 	y=y+2;
	         gotoxy1(x,y);  
			 textbackground(11); 
			 textcolor(4); 
			 printf("<-");                  
        }
    }
     if(flecha==13 && y==5)
     {	    
           AsegurarAp=true;  
           limpiarmsj(); 
           n3=apuesta1(n1,1);
     }                                  
     else if(flecha==13 && y==7)
    	AsegurarAp=false;
     limpiarmsj();
     textbackground(0);
     for(i=3; i<9; i++)
	 {
       for(o=2; o<26; o++)
	   {
          gotoxy1(o,i); 
		  printf(" ");
       }
     }
     return;     
}
void CrearCarta(int NumCarta, int Jugador, int estructuraElementos){ 
     int i=0, k=0;
	 char nomar[30], numcad[5], tecla;
     animacion(NumCarta,Jugador);
     (Jugador == 0 ||Jugador == 2) ? strcpy(nomar, "c:\\cartas\\cartasjug\\atributo") : strcpy(nomar, "c:\\cartas\\cartasComp\\atributo");
     sprintf(numcad, "%d", cartas[NumCarta].randSim);
     strcat(nomar, numcad);
     strcat(nomar, ".txt");
     FILE *arch;
     arch= fopen(nomar, "r");
     int col = 0, ren = 0;
     while(!feof(arch))
        {
             tecla = fgetc(arch);
             if(Jugador == 0) 
				 tecla != '\n' ? ((mat[col][ren] = tecla) & (col++)): ((ren++)&(col=0)); 
             else
				 tecla != '\n' ? ((matCartaComp[col][ren] = tecla) & (col++)): ((ren++)&(col=0));
        } 
     if(Jugador == 0) 
	 {    
           textbackground(15);
           for(i=0; i<14; i++)
		   {
                for(k=0; k<17; k++)
				{
                    gotoxy1(cartas[NumCarta].CoordX +k,cartas[NumCarta].CoordY+i); 
                    if(mat[k][i] == '3')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(3);
                    }
                    else if(mat[k][i] == '4')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(4);       
                    }
                    else if(mat[k][i] == '5')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(5);       
                    }
                    else if(mat[k][i] == '6')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(6);       
                    }
                    else
                         printf(" ");
                }
            }
    }
    else if(Jugador == 1)
	   {  
            textbackground(15);
            for(i=0; i<7; i++)
			{
                for(k=0; k<14; k++)
				{ 
                    gotoxy1(cartas[NumCarta].CoordX +k,cartas[NumCarta].CoordY+i); 
                    if(matCartaComp[k][i] == '3')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(3);
                    }
                    else if(matCartaComp[k][i] == '4')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(4);
                    }
                    else if(matCartaComp[k][i] == '5')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(5);
                    }
                    else if(matCartaComp[k][i] == '6')
					{
                          (cartas[NumCarta].color == 1) ? textcolor(0) : textcolor(12);
                          putchar(6);
                    }
                    else 
                         printf(" ");
                }
            }    
       }
     textbackground(0);
	 gotoxy1(cartas[NumCarta].CoordX +1,cartas[NumCarta].CoordY +1); 
     textbackground(15);
     if(cartas[NumCarta].randNum != 1 && cartas[NumCarta].randNum != 11 && cartas[NumCarta].randNum != 12 && cartas[NumCarta].randNum != 13)
		{
             (cartas[NumCarta].color == 1)? textcolor(0): textcolor(12);
             printf("%i", cartas[NumCarta].randNum); 
        }
     else if(cartas[NumCarta].randNum==1)
		{ 
			(cartas[NumCarta].color == 1)? textcolor(0): textcolor(12); 
			printf("A "); 
			cartas[NumCarta].randNum = ValidacionAs(Player[Jugador].valChng, NumCarta, estructuraElementos); 
	        Player[estructuraElementos].valChng++;
		}
     else if(cartas[NumCarta].randNum==11)
		{ 
			(cartas[NumCarta].color == 1)? textcolor(0): textcolor(12); 
			printf("J "); 
			cartas[NumCarta].randNum=10;
		}
     else if(cartas[NumCarta].randNum==12)
		{ 
			(cartas[NumCarta].color == 1)? textcolor(0): textcolor(12); 
			printf("Q "); 
			cartas[NumCarta].randNum=10;
		}
     else if(cartas[NumCarta].randNum==13)
		{ 
			(cartas[NumCarta].color == 1)? textcolor(0): textcolor(12); 
			printf("K "); 
			cartas[NumCarta].randNum=10;
		}
      textbackground(0);
      fclose(arch);       
}
void AlgJueComp(){
     Player[1].Juego=false;
     Player[1].boolResta==false;
     Player[1].conteoCartas = 33;
     Player[1].sumaNum = cartas[32].randNum;
     if(boolAseg==true && Player[1].conteoCartas==33 && dinjugador>0)
          Aseg();
     while(Player[1].conteoCartas<48 && Player[1].sumaNum<17 && ((Player[0].sumaNum <=21 && boolJuegoDiv == false) || ((Player[0].sumaNum <=21 || Player[2].sumaNum <=21) && boolJuegoDiv == true)))
	 {
            CrearCarta(Player[1].conteoCartas,1,1);
            Player[1].sumaNum=Player[1].sumaNum+ cartas[Player[1].conteoCartas].randNum;
            gotoxy1(cartas[32].CoordX, cartas[32].CoordY+7);
            textcolor(11);  
			printf("Suma de la casa: %i ", Player[1].sumaNum); 
            if(Player[1].boolResta==false && Player[1].sumaNum>21 && (Player[1].BoR2==true || Player[1].BoR3==true || Player[1].BoR4==true) && Player[1].valChng!=0)
			{            
                     Player[1].sumaNum=Player[1].sumaNum-10;
                     gotoxy1(cartas[32].CoordX, cartas[32].CoordY+7);
                     textcolor(11);  
					 printf("Suma de la casa: %i ", Player[1].sumaNum); 
                     (Player[1].BoR2==true) ? (Player[1].BoR2=false):(Player[1].BoR2==true);
                     (Player[1].BoR3==true) ? (Player[1].BoR3=false):(Player[1].BoR3==true);
                     (Player[1].BoR4==true) ? (Player[1].BoR4=false):(Player[1].BoR4==true); 
                     Player[1].boolResta=true;            
                     
            }
            Player[1].conteoCartas++;
            if(Player[1].sumaNum>=17)
                  Player[1].Juego=true;
            else                     
                  Player[1].Juego=false;
            Sleep(500);
     }
   if((Player[0].sumaNum > 21 && boolJuegoDiv == false) || (Player[0].sumaNum > 21 && Player[2].sumaNum > 21 && boolJuegoDiv == true))
	    CrearCarta(33,1,0);
   Sleep(1000);
   return;     
     
} 
void AlgJue(int jugador){ 
     char tecla, respuesta;    
     Player[0].conteoCartas=1;
     Player[jugador].boolResta = false;
     if(jugador == 0)
	 { 
		 CrearCarta(0,0,0);
         CrearCarta(32,1,1); 
		 animacion(1,0); 
		 animacion(33,2);
	 }
     Player[0].sumaNum=cartas[0].randNum;
     gotoxy1(cartas[0].CoordX +1, cartas[0].CoordY-2); 
	 textcolor(11);  
	 printf("SUMA DE TUS CARTAS:   ", Player[jugador].sumaNum); 
     while((jugador == 0 && boolJuegoDiv == false) ? (tecla != 13 && Player[jugador].conteoCartas<16 && Player[jugador].sumaNum<21) : ( (jugador == 0 && boolJuegoDiv == true) ? (Player[jugador].conteoCartas <3) : (Player[jugador].conteoCartas < 18)) )
	 {
	     if(kbhit())
		 {
	        tecla=getch();
	        if(tecla=='a' || tecla=='A')
			{
	            CrearCarta(Player[jugador].conteoCartas,0,jugador);
	            Player[jugador].sumaNum=Player[jugador].sumaNum+ cartas[Player[jugador].conteoCartas].randNum;
	            gotoxy1(cartas[0].CoordX +1, cartas[0].CoordY-2);
	            textcolor(11);  
				printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);                              
	            if(division==true && Player[0].conteoCartas==1 && jugador==0)
				{ 
					dividir(); 
					if(boolJuegoDiv==true)
					{
						animacion(16,0); 
						animacion(2,0);
						animacion(17,0);
						CrearCarta(16,0,0); 
						limpiarmsj();
						n2=apuesta1(v,b); 
						limpiarmsj();
					}
				}
	      		textbackground(0);
	            if(Player[jugador].boolResta == false && Player[jugador].sumaNum>21 && (Player[jugador].BoR2==true || Player[jugador].BoR3==true || Player[jugador].BoR4==true) && Player[jugador].valChng!=0)
				{            
	                     Player[jugador].sumaNum=Player[jugador].sumaNum-10;
	                     gotoxy1(cartas[0].CoordX +1, cartas[0].CoordY-2);
	                     textcolor(11);  
						 printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);
                         Player[jugador].BoR2=false;
	                     Player[jugador].BoR3=false;
	                     Player[jugador].BoR4=false; 
	                     Player[jugador].boolResta=true;            
	                     
	            }
	            Player[jugador].conteoCartas++;
	        }//cierra el if del A 
           if(boolJuegoDiv==false && dinjugador>=n1)
           {
                gotoxy1(2, 21); 
                textcolor(0); 
                textbackground(15); 
                printf("  Para doblar apuesta    ");
                textbackground(0);
                gotoxy1(2,22);
                textbackground(15); 
                printf("     PRESIONAR 'D'       "); 
                textbackground(0);
           }
           if((tecla=='d' || tecla=='D') && boolJuegoDiv == false && dinjugador>=n1)
           {
                doblarr=true;
                n1=doblar(n1);
                CrearCarta(Player[0].conteoCartas,0,0);  
                Player[0].sumaNum=Player[0].sumaNum+ cartas[Player[0].conteoCartas].randNum; 
                gotoxy1(cartas[0].CoordX +1, cartas[0].CoordY-2);
	            textcolor(11);  
				printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);
				Player[0].conteoCartas = 16;
				limpiarmsj();  
				if(Player[jugador].boolResta==false && Player[jugador].sumaNum>21 && (Player[jugador].BoR2==true || Player[jugador].BoR3==true || Player[jugador].BoR4==true) && Player[jugador].valChng!=0)
				{            
	                     Player[jugador].sumaNum=Player[jugador].sumaNum-10;
	                     gotoxy1(cartas[0].CoordX +1, cartas[0].CoordY-2);
	                     textcolor(11);  
						 printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);      
	            }
           }  //cierra el if de la D           
	      } //cierra el if del kbhit
   }//cierra el while
   if(jugador==0 && boolJuegoDiv==false)
    { 
			if(tecla==13 && Player[jugador].conteoCartas==1 && boolJuegoDiv==false)
  	   {
			   CrearCarta(1,0,0); 
			   Player[jugador].sumaNum= cartas[0].randNum+ cartas[1].randNum;
			   gotoxy1(cartas[0].CoordX+1, cartas[0].CoordY-2);
			   textcolor(11);  
			   printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);
	  	}
    }
   else if(jugador==0 && boolJuegoDiv==true)
    { 
   		if(tecla==13 && Player[jugador].conteoCartas==2)
   		{
		   CrearCarta(2,0,0); 
		   Player[jugador].sumaNum= cartas[2].randNum+ cartas[1].randNum;
		   gotoxy1(cartas[0].CoordX+1, cartas[0].CoordY-2);
		   textcolor(11);  
		   printf("SUMA DE TUS CARTAS: %i ", Player[jugador].sumaNum);
    	}
	}
    gotoxy1(2, 21); 
    textcolor(0); 
    textbackground(0); 
    printf("                         ");
    textbackground(0);
    gotoxy1(2,22);
    textbackground(0); 
    printf("                         ");
   if(Player[jugador].sumaNum==21)
   		Mensaje(1);
   else if(Player[jugador].sumaNum>21) 
   		Mensaje(5);
   return;       
} 
void jugar(int usuario){
     char tecla;
     Player[usuario].boolResta=false; 
     (usuario == 0 || usuario == 2) ? AlgJue(usuario) : AlgJueComp();
     return;
}
void DefGan(int S0, int S1, int S2){
       if(S0<=21)
       {
                 gotoxy1(59,16); 
                 textbackground(14); 
                 textcolor(9); 
                 printf("JUEGO 1: "); 
                 textbackground(0);
       }
       if((S0>S1 )&& (S0<21) )
       {
                 Mensaje(4); 
                 bool0win=true;
       }
       else if(S0==21) 
       {
            Mensaje(4); 
            blackjack0=true;
       }
       else if(S0<21 && S1>21)
       {
            Mensaje(4); 
            bool0win=true;
       }
       else if(S0==S1 && S0<21)
       {
            Mensaje(2); 
            bool0tie=true;
       }
       else if(S0<S1 && S1<21) 
            Mensaje(5);
       else if(S1==21 && S0 != 21) 
            Mensaje(5);
       if(S2 !=0)
       {
          if(S2<=21)
          {
                gotoxy1(59,16); 
                textbackground(9); 
                textcolor(14); 
                printf("JUEGO 2: "); 
                textbackground(0);
          }
          if((S2>S1 )&& (S2<21) )
          { 
               Mensaje(4); 
               bool2win=true;
          }
          else if(S2==21)
          { 
               Mensaje(4); 
               bool2win=true;
          }
          else if(S2<21 && S1>21)
          {
               Mensaje(4); 
               bool2win=true;
          }
          else if(S2==S1 && S2<21) 
          {
               Mensaje(2); 
               bool2tie=true;
          }
          else if(S2<S1 && S1<21) 
               Mensaje(5);
          else if(S1==21 && S2 != 21) 
               Mensaje(5);
       }
     return;     
}
void menuPregunta(){
     char TEC;
     int x=87,y=20, i=0, o=0;
     for(i=0; i<25; i++)
     {
          for(o=0; o<13; o++)
          {
             textbackground(15); 
             gotoxy1(i+75,o+14); 
             putchar(' ');
          }
       }
     gotoxy1(80, 16); 
     textcolor(0); 
     printf("%cDesea Jugar?", 168);
     gotoxy1(84,20); 
     textcolor(0); 
     printf("SI");
     gotoxy1(84,23); 
     textcolor(0); 
     printf("NO");
     gotoxy1(x,y); 
     textbackground(11); 
     textcolor(15); 
     printf("<-");
     while(TEC!='a' && TEC!='A' && TEC!=13 )
     {    
        if(kbhit())
        {
             gotoxy1(x,y); 
             textbackground(15); 
             printf("  ");
             TEC=getch(); 
             if(TEC=='w' && y==23||TEC== 'W' && y==23) 
                         y=y-3;
             if(TEC=='s' && y==20||TEC== 'S' && y==23) 
                         y=y+3;
             gotoxy1(x,y);  
             textbackground(11); 
             textcolor(15); 
             printf("<-");                    
         }
       }
     if(TEC==13 && y ==20)
     { 
          Comenzarajugar=true;
          gotoxy1(78, 25); 
          textcolor(4);
          for(i=0; i<25; i++)
          {
                  for(o=0; o<13; o++)
                  {
                          textbackground(2); 
                          gotoxy1(i+75,o+14); 
                          putchar(' ');
                  }
          } 
     }
     else if(TEC==13 && y ==23)
     {
          FILE *archivo;
          archivo=fopen("c:\\cartas\\Jugadores.txt", "a");
          fprintf(archivo, "\n%s acumul%c: %i pumad%clares", nombre, 162, dinjugador, 162);
          fclose(archivo);
          Comenzarajugar=false;
          textbackground(0);
          system("CLS");
          if(modohistoria==false)
          {
             Inicio();
             PrincipalFrame();
          }
          else
            menudf();
     }
     else if(TEC == 'a' || TEC=='A')
          menuPregunta();
     textbackground(0);
     return;     
}
void borrarmano(int condic)
{ 
 int i=0, j=0;
 if(condic==1||condic==3)
 {
     for(i = 0; i < 12; i++)
     {
        for(j = 0; j < 28; j++)
        {
             textcolor(2);
             gotoxy1(j+33,i+14);
             putchar(219);
        }
      }
  }
  if(condic==2||condic==3)
 {
     for(i = 0; i < 12; i++)
     {
        for(j = 0; j < 28; j++)
        {
             textcolor(2);
             gotoxy1(j+120,i+14);
             putchar(219);
        }
     }        
 } 
  return;
}
void bormat()
{
int i=0, j=0;
for(i = 0; i < 12; i++)
      {
        for(j = 0; j < 24; j++)
        {
		  ficha[i][j]=0;
	    }
      }
for(i = 0; i < 12; i++)
      {
        for(j = 0; j < 24; j++)
		  ficha2[i][j]=0;
      }
}
void manita(int crx, int cry){
int p1, p2, i=0, j=0;
      for(i = 0; i < 12; i++)
      {
        for(j = 0; j < 28; j++)
        {
             textcolor(4);
             gotoxy1(j+crx,i+cry);
             switch ( mano[i][j] )
             {
                case 1 :textcolor(0);
                        putchar(219);
                        break;
                case 2 :textcolor(7);
                        putchar(219);
                        break;
                case 0 :textcolor(2);
                        putchar(219);
                        break;
             }
         }                    
       }
    return;
}
void lecturas (int mat[][24], int cdx, int cdy, char loc[] )
{ 
     char tecla;
     FILE *fichi; 
     int y=0, x;
     fichi=fopen(loc, "r");
    while(!feof(fichi)){
             while(y<2)
             {
                    for(x=0;x<4;x++)
                    {
                      tecla=fgetc(fichi);
                         if(tecla=='5'||tecla=='6'||tecla=='3'||tecla=='1'||tecla=='7')
                                mat[cdy+y][cdx+x]=tecla;
                         
                    }
              y++;
			}
}
   fclose(fichi);
	return ;
}
void impfich(int mat[][24], int con)
{
	    int i=0, j=0;
	    if(con==2)
              manita(120,14);
        if(con==1)
              manita(33,14);
    	Sleep(1000);
    	borrarmano(con);
    		      for(i = 0; i < 12; i++)
                  {
                        for(j = 0; j < 24; j++)
                        {
                             textcolor(4);
                             if(con==2)
                                 gotoxy1(j+120,i+14);
                             if(con==1)
                                 gotoxy1(j+33,i+14);
                             switch ( mat[i][j] )
                                    {
    		
                                            case '5':
                                            textbackground(2);
                                            textcolor(5);
                                            putchar(184);
                                            textbackground(0);
                                            break;
                                            case '6':
                                            textbackground(2);
                                            textcolor(0);
                                            putchar(184);
                                            textbackground(2);
                                            break;
                                            case '3':
                                            textbackground(2);	
                                            textcolor(1);
                                            putchar(184);
                                            textbackground(0);
                                            break;
                                            case '1':
                                            textbackground(2);
                                            textcolor(10);
                                            putchar(184);
                                            textbackground(0);
                                            break;
                                            case '7':
                                            textbackground(2);
                                            textcolor(15);
                                            putchar(184);
                                            textbackground(0);
                                            break;
                                      }
                                 }
                          }
	return;
}
void lecfich(int cordx, int cordy,int numrand, int confich, int mat[][24])
{
	    char location[30];
		if(confich==5)
		{
		     if(numrand==1)
             {
		          strcpy(location, "c:\\cartas\\fichas\\c5n1.txt");
		          lecturas(mat, cordx, cordy, location );
             } 
			 if(numrand==2)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c5n2.txt");
                  lecturas(mat, cordx, cordy, location );
             }
			 if(numrand==3)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c5n3.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	    } 
	    if(confich==6)
	    {
	    	 if(numrand==1)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c6n1.txt");
                  lecturas(mat, cordx, cordy, location );
             }
			 if(numrand==2) 
             {
			      strcpy(location, "c:\\cartas\\fichas\\c6n2.txt");
                  lecturas(mat, cordx, cordy, location );
             }
			 if(numrand==3)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c6n3.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
        }
	    if(confich==3)
	    {
	    	 if(numrand==1)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c3n1.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
			 if(numrand==2)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c3n2.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
			 if(numrand==3) 
             {
			      strcpy(location, "c:\\cartas\\fichas\\c3n3.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	    } 
	    if(confich==10)
	    {
	         if(numrand=1)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c10n1.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	         if(numrand==2)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c10n2.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
		     if(numrand==3)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c10n3.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	   }
	    if(confich==7)
	    {
	    	 if(numrand=1)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c7n1.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	         if(numrand==2)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c7n2.txt");
                  lecturas(mat, cordx, cordy, location );
             }  
		     if(numrand==3)
             {
			      strcpy(location, "c:\\cartas\\fichas\\c7n2.txt");
                  lecturas(mat, cordx, cordy, location );
             } 
	    }
	return;
}
void fichas(int nfich, int colfich)
{ 
    yf=0;
    int num=nfich, nr, i=0, j=0;
    srand(time(NULL));
    nr=rand()%3+1;
    xf=num;
	if(nfich>=8&&nfich<16)
    {
       xf=num-8;	
	   yf=yf+2;
    }
	if(nfich>=16&&nfich<24)
    {
       xf=num-16;	
	   yf=yf+4;
    }
	if(nfich>=24&&nfich<32)
    {
       xf=num-24;	
	   yf=yf+6;
    }
	if(nfich>=32&&nfich<40)
    {
       xf=num-32;	
	   yf=yf+8;
    }
	if(nfich>=40&&nfich<48)
    {
       xf=num-40;	
	   yf=yf+10;
    }
	if(nfich>=48&&nfich<56)
       xf=num-48;	
	if(nfich>=56&&nfich<64)
    {
       xf=num-56;	
	   yf=yf+2;
    }
	if(nfich>=64&&nfich<72)
    {
       xf=num-64;	
	   yf=yf+4;
    }
	if(nfich>=72&&nfich<80)
    {
       xf=num-72;	
	   yf=yf+6;
    }
	if(nfich>=80&&nfich<88)
    {
       xf=num-80;	
	   yf=yf+8;
    }
	if(nfich>=88&&nfich<=96)
    {
       xf=num-88;	
	   yf=yf+10;
    }
    xf=xf*3;
	if(nfich<48)
    {
     lecfich(xf,yf,nr,colfich,ficha);
     impfich(ficha, 1);
    }
    if(nfich>=48&&nfich<96)
    {
      lecfich(xf,yf,nr,colfich,ficha2);	
      impfich(ficha2,2);	
	}
	return;
}
int apuesta1(int apmax,int apmin)
{
  int x=17, y=6,apuesta=0, cfich=0, apuestainv=0, i=0; 
    z=apmin;
    char flecha;
    textbackground(0);
  do
  {   
      if(boolJuegoDiv==false)
      {
          for(i=17;i<=23; i++)
          {
                 gotoxy1(i,2); 
                 putchar(' ');
          } 
      apuesta=0;
      borrarmano(3);
      cfich=0;
      for(i=50; i<=125; i++)
              {
                    gotoxy1(i,11);
                    printf(" ");
              }
      gotoxy1(8,2);
      textbackground(0);
      textcolor(15); 
      printf("Apuesta:%i",apuesta);
      xf=0;
      yf=0;
      bormat();
   }
   do
  {
    apuesta=0;
    gotoxy1(2,20);
    textcolor(15);
    printf("Tienes: %i pumad%clares",dinjugador,162);
    gotoxy1(3, 3); 
    textcolor(0); 
    textbackground(15); 
    printf("%cCuanto desea apostar?", 168);
    gotoxy1(7, 6); 
    textbackground(14); 
    textcolor(0); 
    printf("10000");
    gotoxy1(7, 8);
    textbackground(12); 
    textcolor(14);
    printf("1000 ");
    gotoxy1(7, 10);
    textbackground(9); 
    textcolor(15);
    printf("500 ");
    gotoxy1(7, 12);
    textbackground(10); 
    textcolor(0);
    printf("100 ");
    gotoxy1(7, 14);
    textbackground(6); 
    textcolor(15);
    printf("10  ");
    gotoxy1(7, 16);
    textbackground(5); 
    textcolor(15);
    printf("corregir");
    gotoxy1(7, 18);
    textbackground(11); 
    textcolor(0);
    printf("confirmar");
    textbackground(0);
    gotoxy1(x,y);  
    textbackground(0); 
    textcolor(15); 
    printf("<-"); 
      while(flecha!=13 || y!=18)
      {
          textbackground(0);
          textcolor(15); 
          gotoxy1(8,2);
          printf("Apuesta:%i",apuesta);
          if(kbhit()){
                   gotoxy1(x,y); 
                   textbackground(0); 
                   printf("  ");
                   flecha=getch();
                   if(flecha=='w' && y<=18 && y>=8||flecha=='W' && y<=18 && y>=8) 
                           y=y-2;
                   if(flecha=='s' && y>=6 && y<=16||flecha=='S' && y>=6 && y<=16) 
                           y=y+2; 
                   gotoxy1(x,y); 
                   textbackground(0); 
                   textcolor(15); 
                   printf("<-");   
                   if(flecha==13 && y==6)
                         {
                                 apuesta=apuesta+10000; 
                                 fichas(cfich,5);
                                 cfich++; 
                         }
                   if(flecha==13 && y==8)
                   {
                                 apuesta=apuesta+1000; 
                                 fichas(cfich,6);
                                 cfich++; 
                   } 
                   if(flecha==13 && y==10)
                   {
                                 apuesta=apuesta+500; 
                                 fichas(cfich,3);
                                 cfich++; 
                   }
                   if(flecha==13 && y==12)
                   {
                                 apuesta=apuesta+100; 
                                 fichas(cfich,10);
                                 cfich++; 
                   }
                   if(flecha==13 && y==14)
                   {
                                 apuesta=apuesta+10; 
                                 fichas(cfich,7);
                                 cfich++; 
                   }
                   if(flecha==13 && y==16)
                   {  
                                        apuesta=0;
                                        cfich=0;
                                        borrarmano(3);
                                        for(x=17;x<=23; x++)
                                        {
                                            gotoxy1(x,2); 
                                            putchar(' ');
                                        } 
                                        for(x=50; x<=125; x++)
                                        {
                                            gotoxy1(x,11);
                                            printf(" ");
                                        }
                                        gotoxy1(8,2);
                                        textbackground(0);
                                        textcolor(15); 
                                        printf("Apuesta:%i",apuesta);
                                        xf=0;
                                        yf=0;
                                        bormat();
                                        for(x=17; x<=20; x++)
                                        {
                                            gotoxy1(x,16);
                                            printf(" ");
                                        } 
                                        x=17;
                                        y=6;
                                        gotoxy1(x,y);  
                                        printf("<-"); 
                                        }
                             if(cfich>96)
                                       {
                                        apuesta=0;
                                        cfich=0;
                                        borrarmano(3);
                                        for(x=17;x<=23; x++)
                                        {
                                            gotoxy1(x,2); 
                                            putchar(' ');
                                        } 
                                        for(x=50; x<=125; x++)
                                        {
                                            gotoxy1(x,11);
                                            printf(" ");
                                        }
                                        gotoxy1(8,2);
                                        textbackground(0);
                                        textcolor(15); 
                                        printf("Apuesta:%i",apuesta);
                                        xf=0;
                                        yf=0;
                                        bormat();
                                        for(x=17; x<=20; x++)
                                        {
                                            gotoxy1(x,y);
                                            printf(" ");
                                        } 
                                        x=17;
                                        y=16;
                                        gotoxy1(x,y);  
                                        printf("<-"); 
                                        }
                   }
          }
       }
       while(flecha!=13 && y!=18);
        for(x=17; x<=20; x++) 
        {               
                  gotoxy1(x,18);
                  printf(" ");
        } 
        x=17;
        y=6;
        if(apmin>apuesta)
      {
            y=6;
            gotoxy1(50,10);
            textbackground(0);
            printf("Te faltan pumadolares, espera a que llegue prepa s%c",161);
            Sleep(3000);
                        for(i=17;i<=23; i++)
                                        {
                                            gotoxy1(i,2); 
                                            putchar(' ');
                                        } 
                        apuesta=0;
                        borrarmano(3);
                        cfich=0;
                        for(i=50; i<=125; i++)
                                  {
                                          gotoxy1(i,10);
                                          printf(" ");
                                  }
            gotoxy1(8,2);
            textcolor(15); 
            printf("Apuesta:%i",apuesta);
            xf=0;
            yf=0;
            bormat();
      }
        if(apmax<apuesta && AsegurarAp==false)
        {
            y=6;
            gotoxy1(50,10);
            textbackground(0);
            printf("Tienes muchos pumadolares, mejor ve a la pumatienda a comprar una puma-taza");
            Sleep(3000);
                        for(i=17;i<=23; i++)
                        {
                                        gotoxy1(i,2); 
                                        putchar(' ');
                        } 
            borrarmano(3);
            cfich=0;
                        for(i=50; i<=125; i++)
                        {
                                  gotoxy1(i,10);
                                  printf(" ");
                        }
            gotoxy1(8,2);
            textcolor(15); 
            printf("Apuesta:%i",apuesta);
            xf=0;
            yf=0;
            bormat();
          }
         if(apuesta>n1/2  && AsegurarAp==true)
         {
            y=6;
            gotoxy1(50,10);
            textbackground(0);
            printf("No puedes apostar m%cs de la mitad de lo que ya apostaste, chavo",133);
            Sleep(3000);
                        for(i=17;i<=23; i++)
                        {
                                        gotoxy1(i,2); 
                                        putchar(' ');
                        } 
            borrarmano(3);
            cfich=0;
                        for(i=50; i<=125; i++)
                        {
                                  gotoxy1(i,10);
                                  printf(" ");
                        }
            gotoxy1(8,2);
            textcolor(15); 
            printf("Apuesta:%i",apuesta);
            xf=0;
            yf=0;
            bormat();                 
         
         }                
          if(apuesta>dinjugador && apuesta<=apmax)
      {
            y=6;
            gotoxy1(50,10);
            textbackground(0);
            printf("No me intentes estafar, chavo :(");
            Sleep(3000);
                        for(i=17;i<=23; i++)
                                        {
                                            gotoxy1(i,2); 
                                            putchar(' ');
                                        } 
                        apuesta=0;
                        borrarmano(3);
                        cfich=0;
                        for(i=50; i<=125; i++)
                                  {
                                          gotoxy1(i,10);
                                          printf(" ");
                                  }
            gotoxy1(8,2);
            textcolor(15); 
            printf("Apuesta:%i",apuesta);
            xf=0;
            yf=0;
            bormat();
      } 
         
      } 
  while(apmax<apuesta||apmin>apuesta||AsegurarAp==true && apuesta>n1/2||apuesta>dinjugador && apuesta<=apmax);
  gotoxy1(2,20);
  dinjugador=dinjugador-apuesta;
  textcolor(15);
  printf("Tienes: %i pumad%clares",dinjugador,162);
  limpiarmsj();
  return apuesta;  
}

int doblar(int apuesta){
    int apuesta2=apuesta;
    if(doblarr==true)
{
    dinjugador=dinjugador-apuesta;
    apuesta2=apuesta*2;
    gotoxy1(2,20);
    textcolor(15);
    printf("Tienes: %i pumad%clares",dinjugador,162);
}
    return apuesta2;
}
void limpiarmsj(){
int i=0, o=0;
for(i=2; i<21; i++)
{
  textbackground(0);
  for(o=2; o<27; o++)
  {
          gotoxy1(o,i); 
          printf(" ");
  } 
}
  gotoxy1(2,20);
  textcolor(15);
  printf("Tienes: %i pumad%clares",dinjugador,162);
}
void dinero(){
     if(bool0win==true||blackjack0==true && boolJuegoDiv==true)
     {
          n1*=2;
          dinjugador=dinjugador+n1;
          bool0win=false;
     }
      if(bool0tie==true)
     {
          dinjugador=dinjugador+n1;
          bool0tie=false;
     }
     if(blackjack0==true && boolJuegoDiv==false)
     {
          n1*= 1.5;
          dinjugador=dinjugador+n1;
          blackjack0=false;              
     }
     if (bool2win==true)
     {
          n2*=2;
          dinjugador=dinjugador+n2;
          bool2win=false;
     }
      if (bool2tie==true)
     {
          dinjugador=dinjugador+n2;
          bool2tie=false;
     }
     if(AsegurarAp==true && Player[1].conteoCartas==2 && Player[1].sumaNum==21)
     {    
         n3*=2;
         dinjugador=dinjugador+n3;
     }
	 AsegurarAp=false;
     gotoxy1(2,20);
     textcolor(15);
	 printf("Tienes: %i pumad%clares",dinjugador,162);
	 n1=0;n2=0;n3=0;
	 return;
}
void Juego(int apmax, int apmin)
{ 
  v=apmax, b=apmin;
  gotoxy1(45,26);
  textbackground(14);
  printf("Apuesta minima:%i", apmin);
  gotoxy1(110,26);
  textbackground(14);
  printf("Apuesta maxima:%i", apmax);
  while(Comenzarajugar==true)
	{
     DefBaraja();
     n1=apuesta1(v,b);
     {
     Score0=0, Score1=0, Score2=0;
     jugar(0); Score0=Player[0].sumaNum;
     if(boolJuegoDiv==true)
	 { 
              jugar(2); 
              Score2=Player[2].sumaNum;
	 }
     boolJuegoDiv=false;
     jugar(1); 
     Score1=Player[1].sumaNum;
     DefGan(Score0, Score1, Score2);
     dinero();
     CleanCrdS();
     if(totem==true && dinjugador!=0)
     {
      wintotem=true;
     } 
     if(b>dinjugador)
     {
     if(dinjugador>0)
                 menudf();
     if(dinjugador==0)      
           {      
                 system("CLS");
                 Mensaje(3);
                 system("CLS");
                 textbackground(0);
                 textcolor(4);
                 gotoxy1(20,20);
                 textbackground(14);
                 printf("Has perdido, presiona ENTER para volver al inicio");
                 textbackground(0);
                 FILE *archivo;
                 archivo=fopen("c:\\cartas\\Jugadores.txt", "a");
                 fprintf(archivo, "\n%s acumul%c: %i pumad%clares", nombre, 162, dinjugador, 162);
                 fclose(archivo);
                 getchar();
                 Inicio();
                 PrincipalFrame();
           }
     }
     if(wintotem==true)
     {
             ganarfinal();
             menudf();
     }
     
       if(dinjugador>apmin)
            menuPregunta();
     }

}
  return;
}
void impmen( char cad[], int tam)
{
     int x;
     char prub;
     for(x=0;x<=tam; x++)
     {    
          prub=cad[x];
          if(prub!='#'&&prub!='*'&&prub!='%'&&prub!='$'&&prub!='-'&&prub!=':'&&prub!='&'&&prub!='='&& prub!='+')
          {
          gotoxy1(x,41);
          printf("%c",prub);
          }
          else 
          {
               if(prub=='#')
               {
                  gotoxy1(x,41);
                  printf("%c",160);
               }
               if(prub=='*')
               {
                  gotoxy1(x,41);
                  printf("%c",130);            
               }
                 if(prub=='%')
               {
                  gotoxy1(x,41);
                  printf("%c",161);            
               }
                 if(prub=='$')
               {
                  gotoxy1(x,41);
                  printf("%c",162);            
               }
                 if(prub=='-') 
               {
                  gotoxy1(x,41);
                  printf("%c",163);            
               }
                 if(prub==':')
               {
                  gotoxy1(x,41);
                  printf("%c",173);            
               }
                 if(prub=='&')
               {
                  gotoxy1(x,41);
                  printf("%c",168);           
               }
               if(prub=='=')
                {
                  gotoxy1(x,41);
                  printf("%c",224);            
               }
               if(prub=='+')
                {
                  gotoxy1(x,41);
                  printf("%c",164);         
               }
                   
          }
     }
  return;
}
void mon (int xl, int yl )
{
	gotoxy1(xl,yl);
    printf("%c",02);
    gotoxy1(xl,yl+1);
    printf("%c",197);
    gotoxy1(xl,yl+2);
    printf("%c",94);
	return;
}
void lectur(char nprepa[2])
{
	char loc[30];
	int tabla[40][140];
	strcpy(loc,"c:\\cartas\\prepas\\p");
	strcat(loc, nprepa);
	strcat(loc, ".txt");
	FILE *dib;
	dib=fopen(loc,"r");
	int y=0, x=0, i=0, j=0;
    char tecla;
    while (!feof(dib))
    {
        while(y<=40)
        {
            for(x=0;x<141;x++)
            {
                tecla=fgetc(dib);
                if(tecla=='0'||tecla=='1'||tecla=='2'||tecla=='3'||tecla=='4'||tecla=='5'||tecla=='6'||tecla=='7'||tecla=='8'||tecla=='9'||tecla=='a'||tecla=='b'||tecla=='c'||tecla=='d'||tecla=='e'||tecla=='f' ||tecla=='g')
                tabla[y][x]=tecla;
            }
            y++;
        }
    }
	fclose(dib);
    for(i = 0; i < 40; i++)
        for(j = 0; j < 140; j++){
             gotoxy1(j+25,i);
             switch ( tabla[i][j] )
             {
                case '1' :textcolor(15);
                          putchar(177);
                          break;//ladrillo blanco
                case '2' :textcolor(15);
                          putchar(219);
                          break;//cuadro blanco blanca
                case '5' :textcolor(2);
                          putchar(219);
                          break;//pasto
                case '4' :textcolor(4);
                          putchar(177);
                          break;//ladrillo rojo
                case '3' :textcolor(3);
                          putchar(177);
                          break;//ladrillo azul 
                case '6' :textcolor(8);
                          putchar(177);
                          break;//rocas grises
                case '7' :textcolor(3);
                          putchar(219);
                          break;//bloque azul
                case '8' :textcolor(1);
                          putchar(219);
                          break;//bloque azul
                case '9' :textcolor(14);
                          putchar(219);
                          break;//bloque amarillo
                case 'a' :textcolor(6);
                          putchar(219);
                          break;//color de pared de casino
                case 'b' :textcolor(1);
                          putchar(177);
                          break;//color de pared de casino
                case 'c' :textcolor(12);
                          putchar(219);
                          break;//bloque rojo
                case 'd' :textcolor(6);
                          putchar(177);
                          break;//bloque café 
                case 'e' :textcolor(2);
                          putchar(219);
                          break;//bloque verde
                case 'f' :textcolor(7);
                          putchar(219);
                          break;//bloque gris 
                case 'g' :textcolor(13);
                          putchar(219);
                          break; //bloquerosa 
            
             }
        } 
	return;
}
void monito(int xmin, int xmax, int ymin, int ymax, int xm1, int xm2, int xm3, int xm4, int xm5, int ym1, int ym2, int ym3, int ym4, int ym5, int color)//, char m1[], char m2[] ,char m3[], char m4[])
{
	ymax-=3;
	char c,f;
	int i ;
	c=' ';
	xp=xmin;
	yp=ymin;
	while(f!=13)
    	{
	        for(i=0;i<3;i++)
	 	    {
                gotoxy1(xp,yp+i);
                textbackground(color);
	            putchar(' ');
	     	}
	     	textcolor(15);
			if(c=='s'||c=='S')
			    yp+=1;
			if(c=='w'||c=='W')
			    yp-=1;
			if(c=='a'||c=='A')
			    xp-=1;
			if(c=='d'||c=='D')
			    xp+=1;
            if(c=='q'||c=='Q')
			    menudf();
		    if(xp>xmax)
		        xp=xmax;
		    if(yp>ymax)
		        yp=ymax;
		    if(yp<ymin)
		        yp=ymin;
		    if(xp<xmin)
		        xp=xmin;
		    if(xp==xm1-2 && yp==ym1 && bprepa9==false)
			{
				gotoxy1(1,41);
		    	impmen(m1,100);
		    	getch();
			}
		    if(xp==xm2-2 && yp==ym2)
			{
				gotoxy1(1,41);
		    	impmen(m2,100);
		    	getch();
			}
			if(xp==xm3-2 && yp==ym3)
			{
				gotoxy1(1,41);
		    	impmen(m3,100);
		    	getch();
			}   
			if(xp==xm4-2 && yp==ym4)
			{
				gotoxy1(1,41);
		    	impmen(m4,100);
		    	getch();
			}
			if(xp==xm5-2 && yp==ym5)
			{
				gotoxy1(1,41);
		    	impmen(m5,100);
		    	f=getch();
			}  
			if(xp==xm1-2 && yp==ym1)
			{
				if(bprepa9==true)
                      totem=true;
                gotoxy1(1,41);
		    	impmen(m1,151);
		    	f=getch();
			}  
            mon(xp, yp);
		    mon(xm1, ym1);
		    mon(xm2, ym2);
		    mon(xm3, ym3);
		    mon(xm4, ym4);
		    mon(xm5, ym5);
		    for(i=0;i<=150;i++)
		    {
		    	textbackground(0);
				gotoxy1(i,41);
		    	putchar(' ');
			}
         if(f!=13)
         c=getch();	
	}
	return;
}
void borrarmensajes ()
{ 
    int c;
	for (c=0;c<=100;c++)
	    m1[c]=' ';
    for (c=0;c<=100;c++)
	    m2[c]=' ';
	for (c=0;c<=100;c++)
	    m3[c]=' ';
	for (c=0;c<=100;c++)
	    m4[c]=' ';	     
	for (c=0;c<=151;c++)
	    m5[c]=' ';
	return ;
}
void prepa1 ()
{
	borrarmensajes ();
    strcpy(np, "1");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de Blackjack, b-scalo");
	strcpy(m2, "&Sab%as que Gabino Barreda fund$ la primera ENP en el a+o de 1867?");
	strcpy(m3, "V#monos a trajas");
	strcpy(m4, ":::CONDONES M y SICO, CONDONES M y SICO, ARRIBA, ARRIBA LA PREPA DE XOCHIMILCO!!!!");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
    do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,1,6);
	monito(25,139,8,29, 56, 78, 27, 36, 89, 9, 13, 15, 19, 21,0);
	Comenzarajugar=true;
    scenary(2,15,12);
    Juego(500,1);
}
	while(Comenzarajugar==false && dinjugador>=10);
	if(dinjugador<10)
	  menudf();
	return;
}
void prepa2 ()
{
	borrarmensajes ();
    strcpy(np, "2");
    strcpy(m1, "Por aqu% esta cerca el chavo con el pase de acceso para jugar en la competencia de Blackjack, b-scalo");
	strcpy(m2, "Los de iniciaci$n universitaria no pueden jugar Blackjack asi que vete de aqui ");
	strcpy(m3, "&sab%as que Rodolfo Neri Vela estudi$ en la Prepa 2?");
	strcpy(m4, "::::CAMA, SEXO y ORGASMO, CAMA, SEXO y ORGASMO, ARRIBA ARRIBA LA PREPA DE DON ERASMO!!!!");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,4,5);
	monito(26,103,12,30, 89, 78, 46, 67, 97, 15, 26, 21, 18, 19,0);
	Comenzarajugar=true;
    scenary(2,7,12);
    Juego(1000,200);
}
	while(Comenzarajugar==false && dinjugador>=200);
	if(dinjugador<200)
	  menudf();
	return;
}
void prepa3 ()
{
	borrarmensajes ();
    strcpy(np, "3");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de blackjack, b-scalo");
	strcpy(m2, "&Sab%as que la prepa 3 inici$ sus labores como una escuela nocturna para trabajadores");
	strcpy(m3, "::::COMBATE, ACCI=N Y GUERRA, COMBATE ACCI=N Y GUERRA ARRIBA LA PREPA JUSTO CIEERA!!!!!");
	strcpy(m4, "Vamos a canchear");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,12,4);
	monito(91,139, 10,28 , 95, 136, 135, 118,103, 15, 24, 21, 18, 19,0);
	Comenzarajugar=true;
    scenary(2,15,128);
    Juego(1500,400);
}
	while(Comenzarajugar==false && dinjugador>=400);
	if(dinjugador<400)
	  menudf();
	return;
}
void prepa4 ()
{
	borrarmensajes ();
    strcpy(np, "4");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de blackjack, b-scalo");
	strcpy(m2, "¡¡¡¡RON, TEQUILA, TONAYA, RON, TEQUILA, TONYA , ARRIBA, ARRIBA LA PREPA DE TACUBAYA!!!!");
	strcpy(m3, "&Quieres deprimirte? a-n te faltan 5 prepas");
	strcpy(m4, ":::scooby doo, pap#!!!");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,7,8);
	monito(33,94 , 16,37 , 93, 46, 58, 87,78, 17, 28, 33, 23, 25,0);
	Comenzarajugar=true;
    scenary(2,6,15);
    Juego(3000,900);
}
	while(Comenzarajugar==false && dinjugador>=900);
	if(dinjugador<900)
	  menudf();
	return;
}
void prepa5 ()
{
	borrarmensajes ();
    strcpy(np, "5");
    strcpy(m1, "Por aquí anda el chavo con el pase de acceso para jugar en la competencia de blackjack, búscalo");
	strcpy(m2, "¡¡¡ALFALFA, VACAS Y CACA, ALFALFA, VACAS Y CACA, ARRIBA, ARRIBA LA FACULTAD DE COAPA");
	strcpy(m3, "Vamos a jugar americano");
	strcpy(m4, "¿Sabías que la prepa 5 es la preparatoria mas grande de Latinoamérica, alberga mas de 100000 estudiantes?");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,3,11);
	monito(48,108 , 8,29 , 92, 57, 68, 87,78, 17, 12, 25, 23, 10 ,0);
	Comenzarajugar=true;
    scenary(2,8,7);
    Juego(5000,1000);
}
	while(Comenzarajugar==false && dinjugador>=1000);
	if(dinjugador<1000)
	  menudf();
	return;
}
void prepa6 ()
{
	borrarmensajes ();
    strcpy(np, "6");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de blackjack, b-scalo");
	strcpy(m2, "&Sab%as que la prepa 6 es la instituci$n que pide mas aciertos en el examen de comipems");
	strcpy(m3, ":::SEXO, CAMA, EMBARAZO, SEXO, CAMA, EMBARAZO, ARRIBA ARRIBA LA PREPA ANTONIO CASO!!!!");
	strcpy(m4, "&Sab%as que la biblioteca de la prepa 6 tiene un acervo de 640000 libros");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,4,12);
	monito(25,165 , 24,35 ,150 , 117, 48, 87,78, 29, 32, 27, 30, 27 ,0);
	Comenzarajugar=true;
    scenary(2,7,12);
    Juego(7000,2000);
}
	while(Comenzarajugar==false && dinjugador>=2000);
	if(dinjugador<2000)
	  menudf();
	return;
}
void prepa7 ()
{
	borrarmensajes ();
    strcpy(np, "7");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de blackjack, b-scalo");
	strcpy(m2, "Sab%as que Hugo S#nchez y A%da Rom#n estudiaron en la prepa 7");
	strcpy(m3, "::::PANTALETA, MEDIA y LIGA, PANTALETA, MEDIA Y LIGA ARRIBA ARRIBA LA PREPA DE LA VIGA!!!");
	strcpy(m4, "La prepa 7 se fund$ en 1964");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    textcolor(4);
    marco(24,39,0,0,1,2,7);
	monito(46,143 , 27,40 ,136 , 117, 48, 87,78, 36, 32, 29, 30, 35 ,12);
	Comenzarajugar=true;
    scenary(2,3,13);
    Juego(15000,5000);
}
	while(Comenzarajugar==false && dinjugador>=5000);
	if(dinjugador<5000)
	  menudf();
	return;
}
void prepa8 ()
{
	borrarmensajes ();
    strcpy(np, "8");
    strcpy(m1, "Por aqu% anda el chavo con el pase de acceso para jugar en la competencia de blackjack, b-scalo");
	strcpy(m2, ":::::CHICHI, NALGA, BIZCOCHO, CHICHI, NALGA, BIZCOCHO, ARRIBA, ARRIBA, LA PREPA 8!!!!!!!!");
	strcpy(m3, ":Queremos justicia para Marco!");
	strcpy(m4, ":Se debe poner un alto a la desaparici$n de estudiantes!");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,1,9);
    gotoxy1(0,0);
	monito(26,163 , 21,39 ,136 , 147, 48, 87,78, 36, 32, 29, 30, 35 ,0);
	Comenzarajugar=true;
    scenary(2,15,12);
    Juego(18000,9000);
}
	while(Comenzarajugar==false && dinjugador>=9000);
	if(dinjugador<9000)
	  menudf();
	return;
}
void prepa9 ()
{
	borrarmensajes ();
    bprepa9=true;
    strcpy(np, "9");
    strcpy(m1, "Para retar al totem, necesitas tener 37000 pumad$lares y presionar ENTER, deber#s apostar todo,si me engañas, te engañar*");
	strcpy(m2, ":::CAMA, SEXO Y CONDONES, CAMA, SEXO Y CONDONES, ARRIBA ARRIBA LOS HALCONES!!!");
	strcpy(m3, "Este es el -ltimo escenario y te aviso que perder#s, nadie puede ganarle al t$tem");
	strcpy(m4, "&Sab%as que Jaime Maussan estudi$ en la prepa 9?");
	strcpy(m5, "Si deseas jugar presiona ENTER, si no, presiona cualquier tecla ");
	do
{
    system("CLS");
    lectur(np);
    marco(24,39,0,0,1,5,7);
    gotoxy1(0,0);
	monito(48,163 , 17,39 ,132 , 145, 58, 87,78, 19, 32, 23, 30, 35 ,0);
	Comenzarajugar=true;
    if(totem==true && dinjugador>=37000)
    {
        scenary(2,15,12);
        Juego(dinjugador,dinjugador);
    }
    else
    {
        scenary(2,128,9);
        Juego(20000,15000);
    }
}
	while(Comenzarajugar==false && dinjugador>=15000);
	if(dinjugador<15000)
	  menudf();
	return;
}

void menudf()
{
    bprepa9=false;
    wintotem=false;
    textbackground(0);
    system("CLS");
    int apuesta=0, cfich=0, apuestainv=0;
    char flecha='ñ';
    int j=0, x=0, y=0, i=0;
    char tecla;
	gotoxy1(3,3);
	textcolor(13);
    printf("Tienes: %i pumad%clares",dinjugador,162);
    strcpy(np, "0");
    lectur(np);
    x=29, y=6;
    marco(35,39,0,0,0,14,2);
    marco(159,39,35,0,0,14,2);
    textbackground(0); 
    gotoxy1(7, 6); 
    textbackground(14); 
    textcolor(0); 
    printf("Prepa 1");
    gotoxy1(7, 8);
    textbackground(12); 
    textcolor(14);
    printf("Prepa 2(1000)");
    gotoxy1(7, 10);
    textbackground(9); 
    textcolor(15);
    printf("Prepa 3(2000)");
    gotoxy1(7, 12);
    textbackground(10); 
    textcolor(0);
    printf("Prepa 4(3000)");
    gotoxy1(7, 14);
    textbackground(6); 
    textcolor(15);
    printf("Prepa 5(4000)");
    gotoxy1(7, 16);
    textbackground(5); 
    textcolor(15);
    printf("Prepa 6(5000)");
    gotoxy1(7, 18);
    textbackground(15); 
    textcolor(3);
    printf("Prepa 7(10000)");
    gotoxy1(7, 20);
    textbackground(13); 
    textcolor(4);
    printf("Prepa 8(18000)");
    gotoxy1(7, 22);
    textbackground(2); 
    textcolor(4);
    printf("Prepa 9(25000)");
    textbackground(0);
    gotoxy1(x,y);  
    textbackground(0); 
    textcolor(15); 
    printf("<-"); 
    gotoxy(4,2);
    printf("Para salir del juego, presiona E");
    while(flecha!=13)
      {
          if(kbhit()){
                   gotoxy1(x,y); 
                   textbackground(0); 
                   printf("  ");
                   flecha=getch();
                   if(flecha=='w' && y<=22 && y>=8||flecha=='W' && y<=22 && y>=8) 
                           y=y-2;
                   if(flecha=='s' && y>=6 && y<=20||flecha=='S' && y>=6 && y<=20) 
                           y=y+2; 
                   gotoxy1(x,y);  
                   textbackground(0);
                   textcolor(15); 
                   printf("<-");
                   if(flecha=='e'||flecha=='E')
                   {
                        modohistoria=false;
                        system("CLS");
                        Inicio();
                        PrincipalFrame();
                   }   
                   if(flecha==13 && y==6)
                       prepa1();
                   if(flecha==13 && y==8)
                   {
                      if(dinjugador>=1000) 
                          prepa2();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==10)
                   {
                      if(dinjugador>=2000) 
                          prepa3();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==12)
                   {
                      if(dinjugador>=3000) 
                          prepa4();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==14)
                   {
                      if(dinjugador>=4000) 
                          prepa5();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==16)
                    {
                      if(dinjugador>=5000) 
                          prepa6();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==18)
                   {
                      if(dinjugador>=10000) 
                          prepa7();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==20)
                   {
                      if(dinjugador>=18000) 
                          prepa8();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
                   if(flecha==13 && y==22)
                   {
                      if(dinjugador>=25000) 
                          prepa9();
                      else
                          gotoxy1(4,25);
                          printf("Consigue m%cs dinero,chavo",160);
                          Sleep(1000);
                          menudf();
                   }
}
}
}
void marco(int xm, int ym, int xi,int yi, int con, int color, int fon)
{
	textcolor(color);
	int x,y;
    for(x=xi;x<=xm;x++)
         {
           gotoxy1(x,yi);
           putchar(219);
           gotoxy1(x,ym);
           putchar(219);
         }
    for(y=yi;y<=ym;y++)
         {
           gotoxy1(xi,y);
           putchar(219);
           gotoxy1(xm,y);
           putchar(219);
         }
    if(con==1){
    textbackground(fon); 
    textcolor(15);
    gotoxy1(1,1);
    printf("Para volver al men%c  ",163);
    gotoxy1(1,2);
    printf("presiona Q           ");
    } 
    if(con==2){
     gotoxy1(35,15);
     textcolor(15);
     printf("Maximiza la pantalla y luego presiona ENTER :)");
    }
     return;
  }  
void ganarfinal()
{
    system("CLS");
    marco(159,39,0,0,0,1,2);
    gotoxy1(73, 20);
    textcolor(1);
    printf("¡Has ganado!");
	Sleep(3000);
	system("CLS");
	marco(159,39,0,0,0,5,2);
    gotoxy1(18, 20);
    textcolor(5);
    printf("Juego creado por Diego Arturo Velazquez Trejo, Heriberto Toscano Delgado y Mariano Salero Narvaez");
    Sleep(3000);
    system("CLS");
    marco(159,39,0,0,0,14,2);
    gotoxy1(25, 20);
    textcolor(14);
    printf("Te agradecemos por haber jugado este juego, de todo corazon");
    Sleep(3000);
    system("CLS");
    marco(159,39,0,0,0,10,2);
    gotoxy1(15, 20);
    textcolor(10);
    printf("Agradecimientos especiales a Angie por habernos dotado de todos los conocimientos necesarios para lograr este programa");
    Sleep(3000);
    system("CLS");
    marco(159,39,0,0,0,9,2);
    textcolor(9);
    gotoxy1(73, 20);
    printf("¡GRACIAS!");
    getch();
}
