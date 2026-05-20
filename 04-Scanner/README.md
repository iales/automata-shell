# TP 4 - Scanner

## 👨‍💻 Equipo Nº 8

### 👥 Integrantes

1. **Nombre:** Ivan  
   **Apellido:** Ales  
   **Legajo:** 213.775-6  
   **GitHub:** [iales](https://github.com/iales)

2. **Nombre:** Federico Gaston  
   **Apellido:** Ales  
   **Legajo:** 218.570-2  
   **GitHub:** [FedericoAles](https://github.com/FedericoAles)

🔗 [Ver enunciado del trabajo práctico](https://josemariasola.github.io/ssl/assignments/Ssl%20Assignments.pdf#page=123)

---

# Acerca del trabajo práctico  

# Scanner

## Objetivo

- Realizar un analizador léxico (Scanner) para declaraciones. Debera identificar lexemas y
devolver tokens.
- Desarrollar las especificaciones del Scanner de 4 formas: Automata Finito (AF), Lenguaje Natural (LN), Gramatica (BNF) y Expresion Regular (RegEX).
- Implementar el Scanner con codigo en C, aplicando contenidos aprendidos en la cursada como interfaces, flujos de entrada y salida, Makefile, etc.

## Consideraciones
- Plantear los literales numerico en su version mas basica. Es decir, no tener cuenta las variaciones como 1'000'000, 0xFF, etc.
- Las declaraciones no van a ser inicializadas, por lo que no se incluye el `=` y otros caracteres involucrados.
- No considerar *typedef*, *struct*, *const*, entre otros. Ya que solo complejizan el cumplimiento de los objetivos planteados.
- No considerar las palabras clave. Entra todo en la categoria de *Identificador*.


## Especificaciones  

### **Automata Finito (AF)**
- **Q**: Conjunto Finito de Estados
  ```
  INIT  
  ERR  
  INID  
  ID  
  INNUM  
  NUM
  LPA
  INLPA
  RPA
  LBR
  RBR
  PUN
  PTR
  INV  
  ```
- **Qo**: Estado Inicial     
  `INIT`
  
- **Σi**: Alfabeto de entrada     
  ```
  - WSPACE = ( ' ' | '\t' | '\n' | '\r' )
  - L = letra [A-Z] | [a-z]
  - D = digito [0-9]
  - x = caracter lexicamente invalido
  - n = caracter invalido para el literal numerico  
  - z = caracter invalido para identificador ( ' ' | '\t' | '\n' | ';' | '[' | ']' | '(' | ')' | '!' | '"' | '#' | '$' | '%' | '&' | '\'' | '\*' | '+' | ',' | '-' | '.' | '/' | ':' | '<' | '=' | '>' | '?' | '@' | '\\' | '^' | '`' | '{' | '|' | '}' | '~' )
  - c = caracter e Σi
  ```
- **T**: Transicion    
  `Q = Σi * Q`
  
- **Tabla de transiciones**:
    
| Estado actual | Símbolo leído           | Estado siguiente                    |
| ------------- | ----------------------- | ----------------------------------- |
| INIT          | WSPACE                  | INIT                                |
| INIT          | x                       | ERR                                 |
| INIT          | L / _                   | INID                                |
| INIT          | D                       | INNUM                               |
| INIT          | "("                     | INLPA                               |
| INIT          | ")"                     | RPA                                 |
| INIT          | "["                     | LBR                                 |
| INIT          | "]"                     | RBR                                 |
| INIT          | ";"                     | PUN                                 |
| INIT          | "*"                     | PTR                                 |
| INID          | L / D / _               | INID                                |
| INID          | z                       | ID                                  |
| INNUM         | D                       | INNUM                               |
| INNUM         | n                       | NUM                                 |
| INLPA         | c - { ) }               | LPA                                 |
| INLPA         | )                       | INV                                 |

---

### **Gramatica (BNF)** 

```
id ::= ( letra | UND ) { letra | digito | UND }
literal_numerico ::= digito { digito }

letra(L) ::= a | b | ... | z | A | B | ... | Z  
digito(D) ::= 0 | 1 | ... | 9

operador ::= LPA | RPA | LBR | RBR | PTR | INV  
puntuador ::= ';'  
LPA ::= '('
RPA ::= ')'
LBR ::= '['
RPR ::= ']'
PTR ::= '*'
INV ::= '()'
UND ::= '_'
```
---

### **Expresiones Regulares (RegEX)**

```
Identificador [ a-zA-Z_ ][ a-zA-Z_0-9 ]*
Literal_Numerico [ 0-9 ]+
Operador [ *()\[\] ]  
Puntuador [ ; ]  
```

---

### **Lenguaje Natural (LN)**
El Scanner desarrollado comienza en un estado incial esperando el flujo de entrada, con el primer caracter determina que tipo de *Token* es y adapta su comportamiento dependiendo cual sea. Luego, si corresponde, guarda el tipo de Token, el lexema leido con la siguiente estructura: `(TipoToken, Lexema, TokenValue)` que es el Token identificado. Los posibles comportamientos del Scanner segun el primer caracter que ingresa son los siguientes:
- Si se trata de un caracter de tipo *WhiteSpace* se mantendra en el estado inicial, ya que son caracteres que el Scanner ignora y utiliza para separar tokens.  
- Si es una letra, o un guion bajo entonces se trata de un *Identificador* frente a esta situacion seguira esperando caracteres validos para este tipo de Token (cualquier letra, cualquier numero y el guion bajo), hasta recibir uno que no lo sea y marque el fin del *Identificador*.
- Si es un digito se tratara de un *Literal Numerico*, el Token se formara de solo de numeros, por lo que cualquier otro caracter no numerico marcara el fin del Token.
- Si se trata de un operador ('(', ')', '\[', '\]', '*', '()') entonces se pasara directo a un estado de fin, ya que este Token esta formado unicamente por el caracter operador ingresado.
- Si es un caracter puntuador (';') habra un comportamiento similar al del operador, se registra el puntuador y se finaliza el Token, ya que no se esperan mas caracteres.
- Finalmente, si se trata de un caracter lexicamente invalido se identificara como un Token de tipo error y se pasara directo a un estado final de *Error*.


# Parser

---

## Objetivo

- El parser debe analizar la estructura sintáctica de una declaración (ya tokenizada por el scanner) y construir una traducción en lenguaje natural que describa qué significa la declaración en C.
- El parser utiliza una gramática recursiva para reconocer **declaraciones de tipo C** simplificadas, interpretando punteros (`*`), funciones (`()`), arreglos (`[]`) y nombres de identificadores.

## Especificaciones

### Componentes principales

- **Token actual:** 
  - `token`: el token que se está analizando.  
- **Funciones principales:**  
  - `dcl(void)`: analiza punteros y llama a `dirdcl()`  
  - `dirdcl(void)`: analiza nombres, paréntesis, funciones y arreglos.  
- **Variables globales:**  
  - `name`: guarda el nombre del identificador.  
  - `out`: guarda la descripción textual construida.  

---

## Lenguaje Natural (LN)

El parser comienza leyendo los tokens devueltos por el scanner.  
Luego interpreta las declaraciones según las siguientes reglas:

1. **Cuenta los punteros (`*`)** y los traduce como "apuntador a".  
2. **Reconoce el nombre del identificador.**  
3. **Reconoce estructuras adicionales:**
   - `()`: "función que regresa"
   - `[]`: "arreglo[n] de"
4. **Combina todo para formar la descripción final.**

---

# BNF

```
translation-unit:
  declaration
  |translation-unit declaration  
  ;

declaration:
  name dcl ';'  
  ;

dcl:
  optional *'s direct-dcl  
  ;

direct-dcl:
  name
  |(dcl)
  |direct-dcl()
  |direct-dcl[optional size]
  ;
```
