#include "Parser.h"

char datatype[MAXTOKEN];

int main() {
  
  GetNextToken();                                   // Inicia el reconocimiento de tokens 

  while (token.tipo != EOF) {

    strcpy(datatype, token.lexema);                 // Se guarda el tipo de dato
    out[0] = '\0';
    GetNextToken();                                 // Se avanza a la declaracion
    
    dcl();                                          // Se analiza gramaticalmente
    
    printf("%s: %s%s\n", name, out, datatype);      // Se imprime en el output el resultado del analisis en el dcl

    if (token.tipo == PUN) {                        // Si se trata de un ';' simplemente se pasa al siguiente Token
      GetNextToken();
    }
    
  }
  printf("\nTabla de Simbolos: \n");                // Imprime tabla de simbolos al final
  for(int i = 0 ; i < symbolCount ; i++){
    printf(" [%d] %s\n", symbolTable[i].value, symbolTable[i].name);
  }
}
