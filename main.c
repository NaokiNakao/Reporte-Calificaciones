#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

/* Macros */

#define MAXID        8
#define LENNOMBRE   15
#define LENAPEL     15
#define LENDESC     15
#define MAXCLAVE     8
#define MAXEST       6

#define MIN      0
#define MAX    100

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

      do {
         printf("Parcial 1: ");
         scanf("%f", &gr.p1[index].valor);
      } while (gr.p1[index].valor < MIN || gr.p1[index].valor > MAX);

      do {
         printf("Parcial 2: ");
         scanf("%f", &gr.p2[index].valor);
      } while (gr.p2[index].valor < MIN || gr.p2[index].valor > MAX);

      do {
         printf("Examen final: ");
         scanf("%f", &gr.ef[index].valor);
      } while (gr.ef[index].valor < MIN || gr.ef[index].valor > MAX);

      do {
         printf("Tareas: ");
         scanf("%f", &gr.ta[index].valor);
      } while (gr.ta[index].valor < MIN || gr.ta[index].valor > MAX);

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



















































