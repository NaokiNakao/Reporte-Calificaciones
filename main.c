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
#define P1    0.20
#define P2    0.30
#define EF    0.25
#define TA    0.25

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
void getCalifEval(EVAL*, char*, char*, char*);
void setColor(int, int);
void defaultColor();

int main()
{
   GRUPO grupo;

   grupo = getGrupo();

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



















































