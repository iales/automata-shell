#include "Scanner.h"
#include <string.h>

char illegal_id_chars[] = {
  ' ', '\t', '\n', ';', '[', ']', '(', ')',  
  '!', '"', '#', '$', '%', '&', '\'', '*',
  '+', ',', '-', '.', '/', ':', '<', '=', '>',
  '?', '@', '\\', '^', '`', '{', '|', '}', '~'
};

char operators[] = {
  '(', ')', '[', ']', '*'
};

char punctuators[] = {
  ';'
};

// Tabla de simbolos
Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int getSymbolValue(const char* name){
  int i;

  //Busca si ya existe el simbolo
  for(i = 0 ; i < symbolCount ; i++){
    if (strcmp(symbolTable[i].name, name) == 0){
      return symbolTable[i].value;                        // Ya existe, devuelve el valor
    }
  }

  // No existe, se agrega a la tabla
  if(symbolCount < MAX_SYMBOLS){
    strcpy(symbolTable[symbolCount].name, name);
    symbolTable[symbolCount].value = symbolCount + 1;     // Se asigna un valor unico
    symbolCount++;
    return symbolTable[symbolCount - 1].value;
  } else{
    printf("Error: Tabla de simbolos llena\n");
    return -1;
  }
}

static int isPUN(int c) {
  for(int i = 0; i < sizeof(punctuators); i++)  
    if (c == punctuators[i]) return 1;
  return 0;
}
static int isOP(int c) {
  for(int i = 0; i < sizeof(operators); i++)  
    if (c == operators[i]) return i;  // enum del OP
  return -1;  // no es OP
}
static int isWSpace(int c) {return c == ' ' || c == '\t' || c == '\n' || c == '\r';}
static int isNumber(int c) {return c >= '0' && c <= '9';}
static int validCharacter(int c) {
  for(int i = 0; i < sizeof(illegal_id_chars); i++)  
    if (c == illegal_id_chars[i]) return 0; // ilegal
  return 1; // legal
}

Token token;

bool GetNextToken(void) {
  int c = getchar();

  if (c == EOF) {
    token.tipo = EOF;
    return false;
  }
  else if (isPUN(c)) {
    token.tipo = PUN;
    token.lexema[0] = (char)c;
    token.lexema[1] = '\0';
    token.tokenValue = -1;
  } 
  else if (isOP(c) != -1) {
    token.tipo = isOP(c);
    token.tokenValue = -1;
    
    if (token.tipo == LPA) {
      int next = getchar();

      if (isOP(next) == RPA) {
        //Caso: operador de invocación "()"
        token.tipo = INV;
        token.lexema[0] = '(';
        token.lexema[1] = ')';
        token.lexema[2] = '\0';
      } else {
        // '(' solo
        ungetc(next, stdin);
        token.lexema[0] = '(';
        token.lexema[1] = '\0';
      }
    } else {
      // otros operadores individuales: ')', '[', ']', '*'
      token.lexema[0] = (char)c;
      token.lexema[1] = '\0';
    }
  }
  else if (isWSpace(c)) {
    GetNextToken();
  } 
  else if (isNumber(c)) {
    token.tipo = NUM;
    token.lexema[0] = c;

    c = getchar();
    int i = 1;
    while(isNumber(c) && i < MAX_LEX - 1) {
      token.lexema[i] = c;
      c = getchar();
      i++;
    }
    ungetc(c, stdin);
    token.lexema[i] = '\0';
    token.tokenValue = getSymbolValue(token.lexema);
  }
  else if (validCharacter(c)) {
    token.tipo = ID;
    token.lexema[0] = c;

    c = getchar();
    int i = 1;
    while(validCharacter(c) && i < MAX_LEX - 1) {
      token.lexema[i] = c;
      c = getchar();
      i++;
    }
    ungetc(c, stdin);
    token.lexema[i] = '\0';
    token.tokenValue = getSymbolValue(token.lexema);
  }
    else {
      token.tipo = ERR;
      token.lexema[0] = (char)c;
      token.lexema[1] = '\0';
      token.tokenValue = -1;
    }

  return true;
}
