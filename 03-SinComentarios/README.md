# TP 3 - Máquinas de Estado — Sin Comentarios

## 👨‍💻 Equipo Nº 8

### 👥 Integrantes

1. **Nombre:** Alexander  
   **Apellido:** Litovchenko  
   **Legajo:** 213.775-6  
   **GitHub:** [Litovchenko05](https://github.com/Litovchenko05)

2. **Nombre:** Lucas  
   **Apellido:** Cristin  
   **Legajo:** 213.624-7  
   **GitHub:** [LucasCristin23](https://github.com/LucasCristin23)

3. **Nombre:** Federico Gaston  
   **Apellido:** Ales  
   **Legajo:** 218.570-2  
   **GitHub:** [FedericoAles](https://github.com/FedericoAles)

4. **Nombre:** Ivan  
   **Apellido:** Ales  
   **Legajo:** 213.775-6  
   **GitHub:** [iales](https://github.com/iales)

5. **Nombre:** Bruno  
   **Apellido:** Reus  
   **Legajo:** 213.775-6  
   **GitHub:** [Brunoreus](https://github.com/Brunoreus)

🔗 [Ver enunciado del trabajo práctico](https://josemariasola.github.io/ssl/assignments/Ssl%20Assignments.pdf#page=73)

---

# Acerca del trabajo práctico  

## Especificaciones  
  
**Especificaciones matemáticas:**  
M = (Q, Σi, Σo, T, λ, Qo)  
- Q: Estados  
- Qo: Estado inicial  
- Σi: Alfabeto de entrada  
- Σo: Acciones (alfabeto de salida)  
- T: Q x Σi -> Q (función de transición)  
- λ: Q x Σi -> Σo (función de salida, Mealy)  
- T: Transición (inicio, evento, final)  
- λ: Acción (inicio, acción, final)  
  
### Reglas:
Q = {N, SE, LC, BC, BCS, STR, ESC_STR, CHR, ESC_CHR}  
Qo = N  
Σi = ASCII  
Σo = {c, ε, ESP, Z, E}  
c = escribir caracter leído  
ε = no escribir nada  
ESP = escribir espacio  
Z = escribir "/" y el caracter leido (/ + c)  
E = escribir espacio y el caracter leido (' ' + c)  
  
  
### Estados:
- **N (NORMAL):** fuera de comentarios y literales. Estado inicial.
- **SE (SALA_ESPERA):** se leyó `/`.
- **LC (LINE_COMMENT):** dentro de `// ...` hasta fin de línea.
- **BC (BLOCK_COMMENT):** dentro de `/* ... */`.
- **BCS (BLOCK_COMMENT_STAR):** dentro de bloque y se leyó `*` (posible cierre `*/`).
- **STR (STRING):** dentro de `"...` (String).
- **ESC_STR (ESCAPE_STRING):** se leyó `\` dentro de un string (consume un carácter).
- **CHR (CHAR):** dentro de `'...'` (CHAR).
- **ESC_CHR (ESCAPE_CHAR):** se leyó `\` dentro de un char (consume un carácter).

### Tabla de transiciones T (entrada)  
  
| **TT**        | **/**    | **\***   | **"**      | **'**      | **\\**         | **\n**     | **OTHER**  |
| ------------- | -------- | -------- | ---------- | ---------- | -------------- | ---------- | ---------- |
| **N**         | **SE**   | **N**    | **STR**    | **CHR**    | **N**          | **N**      | **N**      |
| **SE**        | **LC**   | **BC**   | **STR**    | **CHR**    | **N**          | **N**      | **N**      |
| **LC**        | **LC**   | **LC**   | **LC**     | **LC**     | **LC**         | **N**      | **LC**     |
| **BC**        | **BC**   | **BCS**  | **BC**     | **BC**     | **BC**         | **BC**     | **BC**     |
| **BCS**       | **N**    | **BCS**  | **BC**     | **BC**     | **BC**         | **BC**     | **BC**     |
| **STR**       | **STR**  | **STR**  | **N**      | **STR**    | **ESC_STR**    | **STR**    | **STR**    |
| **ESC_STR**   | **STR**  | **STR**  | **STR**    | **STR**    | **STR**        | **STR**    | **STR**    |
| **CHR**       | **CHR**  | **CHR**  | **CHR**    | **N**      | **ESC_CHR**    | **CHR**    | **CHR**    |
| **ESC_CHR**   | **CHR**  | **CHR**  | **CHR**    | **CHR**    | **CHR**        | **CHR**    | **CHR**    |

---

### Tabla de acciones λ (salida)  
  
| **TA**        | **/**    | **\***   | **"**      | **'**      | **\\**         | **\n**        | **OTHER**  |
| ------------- | -------- | -------- | ---------- | ---------- | -------------- | ------------- | ---------- |
| **N**         | **ε**    | **c**    | **c**      | **c**      | **c**          | **c**         | **c**      |
| **SE**        | **ε**    | **ε**    | **Z**      | **Z**      | **Z**          | **Z**         | **Z**      |
| **LC**        | **ε**    | **ε**    | **ε**      | **ε**      | **ε**          | **E**         | **ε**      |
| **BC**        | **ε**    | **ε**    | **ε**      | **ε**      | **ε**          | **ε**         | **ε**      |
| **BCS**       | **ESP**  | **ε**    | **ε**      | **ε**      | **ε**          | **ε**         | **ε**      |
| **STR**       | **c**    | **c**    | **c**      | **c**      | **c**          | **c**         | **c**      |
| **ESC_STR**   | **c**    | **c**    | **c**      | **c**      | **c**          | **c**         | **c**      |
| **CHR**       | **c**    | **c**    | **c**      | **c**      | **c**          | **c**         | **c**      |
| **ESC_CHR**   | **c**    | **c**    | **c**      | **c**      | **c**          | **c**         | **c**      |


## Alcance:
#### Comentarios:
- Reemplazar `//` hasta \n por un espacio (ESP).
- Reemplazar `/*...*/` (no anidados) por un espacio.
- `//` o `/* */` dentro de un string/char no se interpreta como comentario.
- `*/` se copia tal cual (si está fuera del bloque).

#### Texto normal:
- Cualquier carácter fuera de comentarios/literales se copia.
- `/` y `*` sueltos se copian.

#### Strings:
- Empiezan y terminan con `"`.
- `\` consume el próximo carácter (osea no se cierra si se lee `"`).
- \n en Strings se copian.

#### Chars:
- Empiezan y terminan con `'`.
- `\` consume el próximo carácter (osea no se cierra si se lee `'`).
- Multicaracter permitidos.

#### Otros:
- No modelamos EOF. Se asume que el archivo `.c` termina en estado válido o que el comportamiento fuera de cierre es irrelevante para el alcance del trabajo.
- Tampoco se tienen en cuenta los escapes con caracteres hexadecimales, octales o con códigos Unicode, se asumen como válidos.



## Benchmark

Durante las pruebas, vimos que ambas implementaciones funcionan correctamente y entregan el resultado esperado para archivos de tamaño moderado, mostrando tiempos de ejecución similares en esos casos.

Al ejecutar decenas de veces ambas implementaciones con un archivo `Test.c` de aproximadamente 1000 líneas, notamos que, en promedio, tardaban lo mismo en realizar la tarea de eliminar comentarios. 

Al ver esto decidimos incrementar el tamaño del archivo, y observamos que la implementación `RemoveCommentsV1.c` comenzaba a fallar alrededor de la línea **1126**, deteniendo la ejecución y dejando el archivo resultante `NoCommentsV1.c` incompleto.

Al realizar las pruebas con Make, vimos que el código de error que lanzaba esta implementación era el **127**, que puede estar indicando un *stack overflow*. La razon por la cual ocurre esto es que cada vez que una función recursiva se llama a sí misma, se esta usando espacio adicional en la pila de memoria y, cuando el archivo es muy largo, estas llamadas se acumulan y la pila se llena rápidamente. Como la pila tiene un tamaño limitado, si se supera ese límite, el programa se detiene abruptamente causando fallos y una salida incompleta, que es lo que nos esta ocurriendo.

Por otro lado, la implementación `RemoveCommentsV2.c`, que utiliza **GOTO**, funcionó correctamente con flujos de entrada mucho más grandes.

Con estos resultados, podemos concluir que la implementacion `RemoveCommentsV2.c`, es mejor, ya que es capaz de soportar flujos de entrada muchos mas grandes que la primera.  

Finalmente, por curiosidad, intentamos llevar la implementacion de **GOTO** al limite enviandole como flujo de entrada un archivo `Test.c` de 100 mil lineas de codigo. Sorpredentemente fue capaz de cumplir con la tarea de remover comentarios sin ningun problema ni demora, lo cual asegura mas nuestra conclusion de que es superior a la implementacion de funciones recursivas.
  
## Aclaraciones de las implementaciones

### Implementación con funciones recursivas
- **Estados:** cada estado es una función distinta; para acceder a un estado se llama a la función correspondiente.  
- **Transiciones:** el alfabeto de entrada se obtiene con `c = getchar();` y la acción que se realiza se ejecuta con `putchar(c);`. Para pasar al siguiente estado, se llama a la función del estado destino.

### Implementación con GOTO
- **Estados:** cada estado está representado con una etiqueta (label).  
- **Transiciones:** el alfabeto de entrada se obtiene con `c = getchar();` y la acción se realiza con `putchar(c);`. Para pasar al siguiente estado se usa `goto <etiqueta>`, donde `<etiqueta>` es el nombre del estado destino.








