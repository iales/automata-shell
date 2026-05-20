#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#define MAX_LEX 64
#define MAX_SYMBOLS 256

typedef enum {
  LPA,     // (
  RPA,     // )
  LBR,     // [
  RBR,     // ]
  PTR,     // *
  INV,     // ()
  ID,      // Identificador
  NUM,     // Literal numerico
  PUN,     // ;
  ERR      // Error
} TokenType;

typedef struct {
  TokenType tipo;                           // Tipo del Token
  char lexema[MAX_LEX];                     // Texto literal del token
  int tokenValue;                           // Valor numerico unico para IDs
} Token;

typedef struct {
  char name[MAX_LEX];                       // Nombre del identificador
  int value;                                 // Valor unico asignado
} Symbol;


// Tabla de Simbolos
extern Symbol symbolTable[MAX_SYMBOLS];     // Puntero constante a la tabla
extern int symbolCount;                     // Cantidad actual de Simbolos

int getSymbolValue(const char* name);

// Token Global
extern Token token;
bool GetNextToken(void);

#endif