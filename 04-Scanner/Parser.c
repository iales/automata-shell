#include "Parser.h"

char name[MAXTOKEN];
char out[1000];

void dirdcl(void); 

void dcl(void) {
  int ns = 0;

  while (token.tipo == PTR) { 
    ns++;
    GetNextToken(); 
  }

  dirdcl();

  while (ns-- > 0) strcat(out, "apuntador a ");
}

void dirdcl(void) {
  if (token.tipo == LPA) {                        // Si es un '('
    GetNextToken();                               // Avanza al siguiente
    
    dcl();                                        // Analiza lo que está dentro del paréntesis
    
    if (token.tipo != RPA) { 
      printf("error: falta )\n");                 // Se abrio un parentesis y nunca se cerro
    }
    else {
      GetNextToken(); 
    }
  } 
  else if (token.tipo == ID) {
    strcpy(name, token.lexema);                   // Guarda el nombre del ID
    GetNextToken(); 
  }
  else {
    printf("error: nombre o (dcl) esperado\n");
  }

  while (token.tipo == INV || token.tipo == LBR) {
    
    if (token.tipo == INV) {                      // Caso de invocación '()'
      strcat(out, "función que regresa ");
      GetNextToken();                             
    } 
    else if (token.tipo == LBR) {                 // Caso de arreglo '['
      strcat(out, "arreglo[");
      GetNextToken();
      
      
      if (token.tipo == NUM){                     // Analizar el tamaño (si existe)
        strcat(out, token.lexema);
        GetNextToken();
      }
      
      
      if (token.tipo == RBR){                     // Espera ']'
        strcat(out, "] de ");
        GetNextToken();
      } else { 
        printf("error: falta ]\n");               // Se abrio un corchete y nunca se cerro
      }
    } 
    else break;
  }
}