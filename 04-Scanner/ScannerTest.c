#include "Scanner.h"

static const char* TokenTypeNames[] = {
  "LPA",     // (
  "RPA",     // )
  "LBR",     // [
  "RBR",     // ]
  "PTR",     // *
  "INV",     // ()
  "ID",      // Identificador
  "NUM",     // Literal numerico
  "PUN",     // ;
  "ERR"
};

int main() {

  GetNextToken();

  while(token.tipo != EOF) {
    if(token.tokenValue != -1){
      printf("(%s, %s, %d)\n",
        TokenTypeNames[token.tipo], 
        token.lexema,
        token.tokenValue);
    }else{
      printf("(%s, %s, _)\n",
         TokenTypeNames[token.tipo],
         token.lexema);
    }
      
    GetNextToken();
  }

  printf("\nTabla de Simbolos:\n");
  for(int i = 0 ; i < symbolCount ; i++){
    printf(" [%d] %s\n", symbolTable[i].value, symbolTable[i].name);
  }
}