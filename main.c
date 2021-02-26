/*
   Programa para almacenar reporte de notas.

   Autor: Naoki Nakao
   Fecha:

   Cosas por hacer:
   -//Promedio parcial
   -Presentar nota m�xima y m�nima por evaluaci�n y cu�les estudiantes las obtuvieron
   -Opci�n de presentar los estudiantes con mayor nota sobre el promedio en P1, P2, F o T
   -Tabla de posibilidades de pasar, sacar C, B o A
   -Tabla con evaluaciones finales
   -Men� de opciones
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

/* Macros */

#define MAXID        8
#define LENNOMBRE   15
#define LENAPEL     15
#define LENDESC     15
#define MAXCLAVE    20
#define MAXEST       6

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

/* Prototipos de funci�n */

GRUPO getGrupo(void);
void setColor(int, int);
void defaultColor();
void getCalifEval(EVAL*, char*, char*, char*);
void calcPP(GRUPO*);
void notaMinMax(EVAL*, int*, int*);

int main()
{
   GRUPO grupo;

   grupo = getGrupo();
   calcPP(&grupo);

   return 0;
}

/*
   Funci�n    : getGrupo
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
   Funci�n    : setColor
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
   Funci�n    : defaultColor
   Argumentos : ---
   Objetivo   : reestablecer los colores por defecto
   Retorno    : ---
*/
void defaultColor()
{
   setColor(WHITE, BLACK);
}

/*
   Funci�n    : getCalifEval
   Argumentos : EVAL* eval: estructura con las evaluaciones
                char* str1: mensaje del tipo de evaluaci�n
                char* str2: mensaje del porcentaje
                char* str3: mensaje de descripci�n
   Objetivo   : capturar los diferentes par�metros de las evaluaciones
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
   Funci�n    : calcPP
   Argumentos : GRUPO* gr: estructura con la informaci�n del grupo
   Objetivo   : calcular el promedio parcial en base a 75% de los estudiantes
   Retorno    : ---
*/
void calcPP(GRUPO* gr)
{
   int index;

   for (index = 0; index < MAXEST; index++)
   {
      gr->pp->valor = ( (gr->p1->valor*gr->p1->porc) + (gr->p2->valor*gr->p2->porc) +
                       (gr->ef->valor*gr->ef->porc) + (gr->ta->valor*gr->ta->porc) ) / PP;
   }

   return;
}

/*
   Funci�n    : notaMinMax
   Argumentos : EVAL* eval: estructura con las evaluaciones
                int* ind_min: �ndice del estudiante con menor nota
                int* ind_max: �ndice del estudiante con mayor nota
   Objetivo   : encontrar los estudiantes con menor y mayor nota en una evaluaci�n
   Retorno    : ---
*/
void notaMinMax(EVAL* eval, int* ind_min, int* ind_max)
{
   int index;
   float n_min, n_max;

   // buscando nota m�nima
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

   // buscando nota m�xima
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



















































