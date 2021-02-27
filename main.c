/*
   Programa para almacenar reporte de notas.

   Autor: Naoki Nakao
   Fecha: 27/02/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

/* Macros */

#define TRUE    1
#define FALSE   0

#define MAXID       10
#define LENNOMBRE   15
#define LENAPEL     15
#define LENDESC     15
#define MAXCLAVE    20
#define MAXEST       4
#define MAXOPC       7
#define CHAROPC     40

#define UP      72
#define DOWN    80
#define ESC     27
#define ENTER   13

#define MIN      0
#define MAX    100
#define PP    0.75

#define PASAR_D   59.5
#define PASAR_C   69.5
#define PASAR_B   79.5
#define PASAR_A   89.5

/* Estructuras */

typedef struct{
   char id[MAXID], pnombre[LENNOMBRE], papellido[LENAPEL];
}EST;

typedef struct{
   char desc[LENDESC];
   float porc;
   float valor;
}EVAL;

typedef struct{
   char clave[MAXCLAVE];
   EST est[MAXEST];
   EVAL p1[MAXEST], p2[MAXEST], ef[MAXEST], ta[MAXEST], pp[MAXEST];
}GRUPO;

/* Prototipos de función */

GRUPO getGrupo(void);
void setColor(int, int);
void defaultColor();
void getCalifEval(EVAL*, char*, char*, char*);
float calcCalif(GRUPO*, int);
int selectOpciones();
void showOpciones(char [][CHAROPC], int);
void showNotaMinMax(EST*, EVAL*, char*, int, int);
void notaMinMax(EVAL*, int*, int*);
void showSupProm(EST*, EVAL*, char*);
float promedio(EVAL*);
void showNotaNec(GRUPO*);
void getNotaNec(GRUPO*, int, float, int, int);
void showEvalFinales(GRUPO*);

int main()
{
   GRUPO grupo;
   int opc;
   char key;

   // Comentar la línea 83 y quitar comentarios desde la línea
   // 86 hasta 132 para obviar la captura de datos.

   grupo = getGrupo();

   /*strcpy(grupo.est[0].id, "1020321");
   strcpy(grupo.est[0].pnombre, "Julian");
   strcpy(grupo.est[0].papellido, "Diaz");
   grupo.p1[0].valor = 95;
   grupo.p1[0].porc = 0.20;
   grupo.p2[0].valor = 80;
   grupo.p2[0].porc = 0.30;
   grupo.ef[0].valor = 60;
   grupo.ef[0].porc = 0.25;
   grupo.ta[0].valor = 80;
   grupo.ta[0].porc = 0.25;

   strcpy(grupo.est[1].id, "1020456");
   strcpy(grupo.est[1].pnombre, "Alfredo");
   strcpy(grupo.est[1].papellido, "Sanz");
   grupo.p1[1].valor = 80;
   grupo.p1[1].porc = 0.20;
   grupo.p2[1].valor = 75;
   grupo.p2[1].porc = 0.30;
   grupo.ef[1].valor = 50;
   grupo.ef[1].porc = 0.25;
   grupo.ta[1].valor = 67;
   grupo.ta[1].porc = 0.25;

   strcpy(grupo.est[2].id, "1020567");
   strcpy(grupo.est[2].pnombre, "Julio");
   strcpy(grupo.est[2].papellido, "Perez");
   grupo.p1[2].valor = 80;
   grupo.p1[2].porc = 0.20;
   grupo.p2[2].valor = 85;
   grupo.p2[2].porc = 0.30;
   grupo.ef[2].valor = 75;
   grupo.ef[2].porc = 0.25;
   grupo.ta[2].valor = 70;
   grupo.ta[2].porc = 0.25;

   strcpy(grupo.est[3].id, "1034203");
   strcpy(grupo.est[3].pnombre, "Marco");
   strcpy(grupo.est[3].papellido, "Baez");
   grupo.p1[3].valor = 85;
   grupo.p1[3].porc = 0.20;
   grupo.p2[3].valor = 75;
   grupo.p2[3].porc = 0.30;
   grupo.ef[3].valor = 90;
   grupo.ef[3].porc = 0.25;
   grupo.ta[3].valor = 75;
   grupo.ta[3].porc = 0.25;*/

   // calculando promedio parcial
   for (int index = 0; index < MAXEST; index++)
      grupo.pp[index].valor = ((calcCalif(&grupo,index)-grupo.ef[index].valor*grupo.ef[index].porc)/PP);

   while (TRUE)
   {
      opc = selectOpciones();
      system("cls");

      // mostrando calificaciones máximas y mínimas en las evaluaciones
      if (opc == 0)
      {
         showNotaMinMax(grupo.est, grupo.p1, "     PARCIAL 1     ", 3, 1);
         showNotaMinMax(grupo.est, grupo.p2, "     PARCIAL 2     ", 30, 1);
         showNotaMinMax(grupo.est, grupo.ef, "    EXAMEN FINAL   ", 3, 15);
         showNotaMinMax(grupo.est, grupo.ta, "       TAREAS      ", 30, 15);
      }

      // mostrando calificaciones superiores al promedio en parcial 1
      else if (opc == 1)
         showSupProm(grupo.est, grupo.p1, "Superior al Promedio Parcial 1");

      // mostrando calificaciones superiores al promedio en parcial 2
      else if (opc == 2)
         showSupProm(grupo.est, grupo.p2, "Superior al Promedio Parcial 2");

      // mostrando calificaciones superiores al promedio en examen final
      else if (opc == 3)
         showSupProm(grupo.est, grupo.ef, "Superior al Promedio Examen Final");

      // mostrando calificaciones superiores al promedio tareas
      else if (opc == 4)
         showSupProm(grupo.est, grupo.ta, "Superior al Promedio Tareas");

      // mostrando calificaciones necesarias para pasar con cierta nota
      else if (opc == 5)
         showNotaNec(&grupo);

      // mostrando evaluaciones finales
      else if (opc == 6)
         showEvalFinales(&grupo);

      gotoxy(3, 29);
      setColor(BLUE, YELLOW);
      printf("Presione [ESC] para regresar.");
      defaultColor();
      do {
         key = getch();
      } while (key != ESC);
   }

   return 0;
}

/*
   Función    : getGrupo
   Argumentos : ---
   Objetivo   : capturar los datos generales del grupo
   Retorno    : (GRUPO) gr : estructura con datos del grupo
*/
GRUPO getGrupo(void)
{
   GRUPO gr;
   int index;

   printf("Clave del grupo: ");
   fflush(stdin);
   gets(gr.clave);
   printf("\n");

   for (index = 0; index < MAXEST; index++)
   {
      setColor(WHITE, BLUE);
      printf("Datos estudiante %d:\n\n", index+1);
      defaultColor();

      printf("ID: ");
      fflush(stdin);
      gets(gr.est[index].id);

      printf("Nombre: ");
      fflush(stdin);
      gets(gr.est[index].pnombre);

      printf("Apellido: ");
      fflush(stdin);
      gets(gr.est[index].papellido);

      getCalifEval(&gr.p1[index], "Parcial 1", "Procentaje del parcial 1", "Descripcion del parcial 1");
      getCalifEval(&gr.p2[index], "Parcial 2", "Procentaje del parcial 2", "Descripcion del parcial 2");
      getCalifEval(&gr.ef[index], "Examen final", "Procentaje del examen final", "Descripcion del examen final");
      getCalifEval(&gr.ta[index], "Tareas", "Procentaje de las tareas", "Descripcion de las tareas");

      printf("\n");
   }

   return gr;
}

/*
   Función    : setColor
   Argumentos : int ct: color del texto
                int cf: color del fondo
   Objetivo   : cambiar los colores de texto y fondo
   Retorno    : ---
*/
void setColor(int ct, int cf)
{
   textcolor(ct);
   textbackground(cf);
}

/*
   Función    : defaultColor
   Argumentos : ---
   Objetivo   : reestablecer los colores por defecto
   Retorno    : ---
*/
void defaultColor()
{
   setColor(WHITE, BLACK);
}

/*
   Función    : getCalifEval
   Argumentos : EVAL* eval: estructura con las evaluaciones
                char* str1: mensaje del tipo de evaluación
                char* str2: mensaje del porcentaje
                char* str3: mensaje de descripción
   Objetivo   : capturar los diferentes parámetros de las evaluaciones
   Retorno    : ---
*/
void getCalifEval(EVAL* eval, char* str1, char* str2, char* str3)
{
   do {
      printf("%s: ", str1);
      scanf("%f", &eval->valor);
   } while (eval->valor < MIN || eval->valor > MAX);

   do {
      printf("%s: ", str2);
      scanf("%f", &eval->porc);
   } while (eval->porc < 0 || eval->porc > 1);

   printf("%s: ", str3);
   fflush(stdin);
   gets(eval->desc);

   return;
}

/*
   Función    : calcCalif
   Argumentos : GRUPO* gr: estructura con la información del grupo
                int est: índice del estudiante
   Objetivo   : calcular las calificaciones de los estudiantes
   Retorno    : (float) result: calificación total del estudiante
*/
float calcCalif(GRUPO* gr, int est)
{
   float result;
   result = (gr->p1[est].valor*gr->p1[est].porc) + (gr->p2[est].valor*gr->p2[est].porc) +
            (gr->ef[est].valor*gr->ef[est].porc) + (gr->ta[est].valor*gr->ta[est].porc);
   return result;
}

/*
   Función    : selectOpciones
   Argumentos : ---
   Objetivo   : presentar menú de opciones para elegir
   Retorno    : (int) index: opción seleccionada
*/
int selectOpciones()
{
   char key, index = 0;

   char opciones[][CHAROPC] = {"Nota maxima y minima por evaluacion",
                               "Mayor nota sobre el promedio en P1 ",
                               "Mayor nota sobre el promedio en P2 ",
                               "Mayor nota sobre el promedio en EF ",
                               "Mayor nota sobre el promedio en TA ",
                               "Posibilidades de nota              ",
                               "Calificaciones finales             "};

   _setcursortype(FALSE);

   system("cls");

   gotoxy(3,3);
   setColor(WHITE, LIGHTBLUE);
   printf("OPCIONES:");
   defaultColor();

   do {

      showOpciones(opciones, index);

      do {
         key = getch();
      } while (key != UP && key != DOWN && key != ENTER);

      if (key == UP)
      {
         if (index)
            index--;
         else
            index = MAXOPC-1;
      }
      if (key == DOWN)
      {
         if (index < MAXOPC-1)
            index++;
         else
            index = 0;
      }

   } while (key != ENTER);

   return index;
}

/*
   Función    : showOpciones
   Argumentos : char opc[][CHAROPC]: contiene la descripción de las opciones
                int select: posición de la opción seleccionada actualmente
   Objetivo   : mostrar las opciones
   Retorno    : ---
*/
void showOpciones(char opc[][CHAROPC], int select)
{
   int index, pos_x = 3, pos_y = 5;

   for (index = 0; index < MAXOPC; index++)
   {
      gotoxy(pos_x, pos_y+index);
      if (index == select)
         setColor(BLUE, YELLOW);
      printf("%s", opc[index]);
      defaultColor();
   }

   return;
}

/*
   Función    : showNotaMinMax
   Argumentos : EST* est: estructura con la información de los estudiantes
                EVAL* eval: estructura que contiene las calificaiones de "est"
                char* str: cadena para describir el tipo de evaluación
                int pos_x: indica la posición en x (columnas)
                int pos_y: indica la posición en y (filas)
   Objetivo   : mostrar la nota mínima y máxima de una evaluación
   Retorno    : ---
*/
void showNotaMinMax(EST* est, EVAL* eval, char* str, int pos_x, int pos_y)
{
   int min, max;

   notaMinMax(eval, &min, &max);

   gotoxy(pos_x, pos_y);
   setColor(WHITE, LIGHTBLUE);
   printf("%s", str);
   defaultColor();

   // mostrando nota máxima
   gotoxy(pos_x, pos_y+2);
   printf("Nota m%cxima:", 160);
   gotoxy(pos_x, pos_y+3);
   printf("ID: %s", est[max].id);
   gotoxy(pos_x, pos_y+4);
   printf("Nombre: %s", est[max].pnombre);
   gotoxy(pos_x, pos_y+5);
   printf("Apellido: %s", est[max].papellido);
   gotoxy(pos_x, pos_y+6);
   printf("Calificaci%cn: %.2f", 162, eval[max].valor);

   // mostrando nota mínima
   gotoxy(pos_x, pos_y+8);
   printf("Nota m%cnima:", 161);
   gotoxy(pos_x, pos_y+9);
   printf("ID: %s", est[min].id);
   gotoxy(pos_x, pos_y+10);
   printf("Nombre: %s", est[min].pnombre);
   gotoxy(pos_x, pos_y+11);
   printf("Apellido: %s", est[min].papellido);
   gotoxy(pos_x, pos_y+12);
   printf("Calificaci%cn: %.2f", 162, eval[min].valor);

   return;
}

/*
   Función    : notaMinMax
   Argumentos : EVAL* eval: estructura con las evaluaciones
                int* ind_min: índice del estudiante con menor nota
                int* ind_max: índice del estudiante con mayor nota
   Objetivo   : encontrar los estudiantes con menor y mayor nota en una evaluación
   Retorno    : ---
*/
void notaMinMax(EVAL* eval, int* ind_min, int* ind_max)
{
   int index;
   float n_min, n_max;

   *ind_min = 0;
   *ind_max = 0;
   n_min = eval[0].valor;
   n_max = eval[0].valor;

   for (index = 0; index < MAXEST; index++)
   {
      if (eval[index].valor < n_min)
      {
         *ind_min = index;
         n_min = eval[index].valor;
      }

      if (eval[index].valor > n_max)
      {
         *ind_max = index;
         n_max = eval[index].valor;
      }
   }

   return;
}

/*
   Función    : showSupProm
   Argumentos : EST* est: estructura con la información de los estudiantes
                EVAL* eval: estructura con las evaluaciones
                char* str: cadena para describir el tipo de evaluación
   Objetivo   : mostrar estudiantes con calificaciones sobre el promedio en una evaluación
   Retorno    : ---
*/
void showSupProm(EST* est, EVAL* eval, char* str)
{
   int index, pos_x = 3, pos_y = 3;
   float prom = promedio(eval);

   setColor(WHITE, LIGHTBLUE);
   printf("%s", str);
   defaultColor();

   for (index = 0; index < MAXEST; index++)
   {
      if (eval[index].valor > prom)
      {
         gotoxy(pos_x, pos_y);
         printf("ID: %s", est[index].id);
         gotoxy(pos_x, ++pos_y);
         printf("Nombre: %s", est[index].pnombre);
         gotoxy(pos_x, ++pos_y);
         printf("Apellido: %s", est[index].papellido);
         gotoxy(pos_x, ++pos_y);
         printf("Calificaci%cn: %.2f", 162, eval[index].valor);
         pos_y += 2;
      }
   }

   return;
}

/*
   Función    : promedio
   Argumentos : EVAL* eval: estructura con las evaluaciones
   Objetivo   : calcular el promedio de las califiaciones en "eval"
   Retorno    : (float) result: promedio de las calificaciones
*/
float promedio(EVAL* eval)
{
   int index;
   float result = 0;

   for (index = 0; index < MAXEST; index++)
      result += eval[index].valor;

   return result / MAXEST;
}

/*
   Función    : showNotaNec
   Argumentos : GRUPO* gr: estructura con la información del grupo
   Objetivo   : mostrar la calificación necesaria en el examen final para pasar con cierta letra
   Retorno    : ---
*/
void showNotaNec(GRUPO* gr)
{
   int index, pos_x = 3, pos_y = 3;

   gotoxy(pos_x, pos_y);
   setColor(BLUE, YELLOW);
   printf("   ID     Estudiante           D        C        B        A   ");
   defaultColor();

   for (index = 0; index < MAXEST; index++)
   {
      gotoxy(pos_x, pos_y+index+1);
      printf("%s", gr->est[index].id);
      gotoxy(pos_x+10, pos_y+index+1);
      printf("%s %s", gr->est[index].pnombre, gr->est[index].papellido);

      getNotaNec(gr, index, PASAR_D, pos_x+29, pos_y+index+1);
      getNotaNec(gr, index, PASAR_C, pos_x+38, pos_y+index+1);
      getNotaNec(gr, index, PASAR_B, pos_x+47, pos_y+index+1);
      getNotaNec(gr, index, PASAR_A, pos_x+56, pos_y+index+1);
   }

   return;
}

/*
   Función    : getNotaNec
   Argumentos : GRUPO* gr: estructura con la información del grupo
                int est: índice del estudiante
                float obj: objetivo de nota
                int pos_x: posición en x (columnas)
                int pos_y: posición en y (filas)
   Objetivo   : calcular y mostar la calificación en una evaluación específica
   Retorno    : ---
*/
void getNotaNec(GRUPO* gr, int est, float obj, int pos_x, int pos_y)
{
   float nota;

   nota = (obj - gr->p1[est].valor*gr->p1[est].porc - gr->p2[est].valor*gr->p2[est].porc -
           gr->ta[est].valor*gr->ta[est].porc) / gr->ef[est].porc;

   gotoxy(pos_x, pos_y);

   if (nota <= MIN)
      printf(" N/A");
   else if (nota > MAX)
      printf(" ---");
   else
      printf("%.2f", nota);

   return;
}

/*
   Función    : showEvalFinales
   Argumentos : GRUPO* gr: estructura con la información del grupo
   Objetivo   : mostrar las evaluaciones finales
   Retorno    : ---
*/
void showEvalFinales(GRUPO* gr)
{
   int index, pos_x = 3, pos_y = 3;
   float calif;

   gotoxy(pos_x, pos_y);
   setColor(WHITE, LIGHTBLUE);
   printf("                                  EVALUACIONES                              ");
   setColor(BLUE, YELLOW);
   gotoxy(pos_x, pos_y+1);
   printf("   ID     Estudiante       P1     P2     EF     TA    Prom.  Calificaci%cn   ", 162);
   gotoxy(pos_x, pos_y+2);
   printf("                          (20%c)  (30%c)  (25%c)  (25%c)  (75%c)     Final       ", 37, 37, 37, 37, 37);
   defaultColor();

   for (index = 0; index < MAXEST; index++)
   {
      gotoxy(pos_x, pos_y+index+3);
      printf("%s", gr->est[index].id);
      gotoxy(pos_x+10, pos_y+index+3);
      printf("%s %s", gr->est[index].pnombre, gr->est[index].papellido);
      gotoxy(pos_x+26, pos_y+index+3);
      printf("%.2f", gr->p1[index].valor);
      gotoxy(pos_x+33, pos_y+index+3);
      printf("%.2f", gr->p2[index].valor);
      gotoxy(pos_x+40, pos_y+index+3);
      printf("%.2f", gr->ef[index].valor);
      gotoxy(pos_x+47, pos_y+index+3);
      printf("%.2f", gr->ta[index].valor);
      gotoxy(pos_x+54, pos_y+index+3);
      printf("%.2f", gr->pp[index].valor);

      calif = calcCalif(gr, index);
      gotoxy(pos_x+66, pos_y+index+3);

      // verificando la letra
      if (calif < 60)
         printf("F");
      else if (calif >= 60 && calif < 70)
         printf("D");
      else if (calif >= 70 && calif < 80)
         printf("C");
      else if (calif >= 80 && calif < 90)
         printf("B");
      else if (calif >= 90)
         printf("A");
   }

   return;
}


















































