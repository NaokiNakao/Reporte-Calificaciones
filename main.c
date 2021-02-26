/*
   Programa para almacenar reporte de notas.

   Autor: Naoki Nakao
   Fecha:

   Cosas por hacer:
   -//Promedio parcial
   -Presentar nota máxima y mínima por evaluación y cuáles estudiantes las obtuvieron
   -Opción de presentar los estudiantes con mayor nota sobre el promedio en P1, P2, F o T
   -Tabla de posibilidades de pasar, sacar C, B o A
   -Tabla con evaluaciones finales
   -Menú de opciones
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

/* Macros */

#define TRUE    1
#define FALSE   0

#define MAXID        8
#define LENNOMBRE   15
#define LENAPEL     15
#define LENDESC     15
#define MAXCLAVE    20
#define MAXEST       6
#define MAXOPC       7
#define CHAROPC     40

#define UP      72
#define DOWN    80
#define ESC     27
#define ENTER   13

#define MIN      0
#define MAX    100
#define PP    0.75

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
void selectOpciones(GRUPO*);
void showOpciones(char [][CHAROPC], int);
void getCalifEval(EVAL*, char*, char*, char*);
float calcCalif(GRUPO*, int);
void notaMinMax(EVAL*, int*, int*);

int main()
{
   GRUPO grupo;
   int est;

   //grupo = getGrupo();
   selectOpciones(&grupo);

   // calculando el promedio parcial
   //for (est = 0; est < MAXEST; est++)
      //grupo.pp[est].valor = (calcCalif(&grupo, est) - grupo.ef[est].valor*grupo.ef[est].porc) / PP;

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
   Función    : selectOpciones
   Argumentos : GRUPO* gr: estructura con la información del grupo
   Objetivo   : presentar menú de opciones para elegir
   Retorno    : ---
*/
void selectOpciones(GRUPO* gr)
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

   gotoxy(3,3);
   setColor(WHITE, LIGHTBLUE);
   printf("OPCIONES:");
   defaultColor();

   do {

      showOpciones(opciones, index);

      do {
         key = getch();
      } while (key != UP && key != DOWN && key != ENTER && key != ESC);

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

   } while (key != ENTER && key != ESC);
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

   // buscando nota mínima
   *ind_min = 0;
   n_min = eval[0].valor;

   for (index = 0; index < MAXEST; index++)
   {
      if (eval[index].valor < n_min)
      {
         *ind_min = index;
         n_min = eval[index].valor;
      }
   }

   // buscando nota máxima
   *ind_max = 0;
   n_max = eval[0].valor;

   for (index = 0; index < MAXEST; index++)
   {
      if (eval[index].valor > n_max)
      {
         *ind_max = index;
         n_max = eval[index].valor;
      }
   }

   return;
}



















































