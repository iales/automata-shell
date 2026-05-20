# TP 1 - Fases de la Traducción y Errores

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

🔗 [Ver enunciado del trabajo práctico](https://josemariasola.github.io/ssl/assignments/Ssl%20Assignments.pdf#page=37)

---

## Preprocesador
*b)* Comando utilizado para preprocesar `hello2.c`: `gcc -E hello2.c -o hello2.i`  
  
El contenido de `hello2.c` tiene varios errores sintácticos, como por ejemplo la falta de una llave al final del main.
Aun así, se puede preprocesar tranquilamente, ya que estos errores y/o faltas no afectan el funcionamiento del preprocesador.
En este caso en particular, el preprocesador, solo prepara un texto plano (.i) en donde, en ``hello2.c``, se reemplazará el ``/*medio*/`` por un espacio vacío,
se incluirá al header ``stdio.h`` que se llama utilizando ``#include <stdio.h>`` en la primera línea, etc. Luego el compilador analizara este archivo .i y
detectara los errores correspondientes.

*d)* Investigar la semántica de: ``int printf(const char * restrict s, ...);``  
- `int`: indica se trata de una función de tipo ``int``, es decir, devuelve un entero. En esta función en particular, este entero indica la cantidad de caracteres impresos,
o un valor negativo si ocurre un error.
- ``printf``: es el nombre que se le dio a la función.
- ``const char * restrict s``: ``const`` hace que el contenido apuntado por el puntero ``char*`` no pueda ser modificado dentro de la función. 
Luego, ``char*`` es un puntero a caraceteres, representa una cadena de texto terminada en ``\0``. Y por ultimo ``restrict s`` indica que ``s`` es el único puntero que accede
 a esta región de memoria, permite optimizaciones del compilador.

Resumidamente, ``const char * restrict s``, es un puntero a una cadena constante que la función no modificará, y que no se debe compartir con otros punteros.
Por ultimo ``...`` indica que esta función acepta un numero variable de argumentos.  

*e)* Comando utilizado para solo preprocesar `hello3.c`: `gcc -E hello3.c -o hello3.i`  
Las únicas diferencias entre ``hello3.c`` y ``hello3.i`` se encuentra en las primeras 4 lineas, en donde en el ``hello3.i`` se encuentran las siguientes líneas de código:
```c
# 0 "hello3.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "hello3.c"
```
Se tratan de directivas del preprocesador para el compilador, no son código fuente real.
- ``# 0 "hello3.c"`` Inicia el archivo ``hello3.c`` (línea 0)
- ``# 0 "<built-in>"`` Inicia una sección de código interno del compilador
- ``# 0 "<command-line>"`` Inicia una sección de macros definidas desde la línea de comandos
- ``# 1 "hello3.c"`` Retorna a la línea 1 del archivo ``hello3.c``

Lo mas interesante es la diferencia entre ``hello3.i`` y ``hello2.i``, ya que como en ``hello2.c`` se encuentra el ``#include <stdio.h>``, el preprocesador debe reemplazar
esta línea de código por el archivo header correspondiente, y es lo que se puede ver en las primeras 1016 líneas de código de ``hello2.i``.


## Compilación
*b)* Comando utilizado para compilar `hello3.i`: `gcc -S hello3.i -o hello3.s`  
Los errores que mostro la terminal al intentar compilar ``hello3.c`` fueron los siguientes: 
Primero dio error la función ``prontf`` ya que no estaba declarada, entonces la cambiamos a ``printf``. 
Y luego daba error porque faltaba la llave final ``}``, asi que la agregamos y finalmente compilo.

*c)* El funcionamiento del código ensamblador en ``hello4.s`` consiste en los siguientes pasos:

- Se define una cadena que utilizara printf más adelante.
> .LC0:  
>  .ascii "La respuesta es %d\12\0"

- Comienza main guardando el base pointer con un push,
  que nos permitirá restaurarlo luego, y se establece un nuevo base pointer marcando asi el comienzo del stack frame actual.
>main:  
>  pushq	%rbp  
>  movq	%rsp, %rbp  

- Se reserva espacio en la pila para variables locales.
> subq	$48, %rsp  


- Se llama a la rutina de inicialización de Windows.
> call	__main  

- Se le asigna 42 a la variable i y se guarda en el stack frame.
>movl	$42, -4(%rbp)  

- Se carga la dirección de la cadena definida previamente y se llama a printf.
> leaq	.LC0(%rip), %rax  
> movq	%rax, %rcx  
> call	printf  

- Devuelve 0 al main, libera la pila, recupera el valor del base pointer que reservamos al principio y recupera.
> movl	$0, %eax  
> addq	$48, %rsp  
> popq	%rbp  
> ret  

*d)* Comando utilizado para ensamblar `hello4.s`: `gcc -c hello4.s -o hello4.o`  

## Vinculación
*a)* Comando utilizado para vincular `hello4.o`: `gcc hello4.o -o hello4`  

*b)* En primera instancia se vinculó correctamente ``hello4.o`` sin generar errores, al ver esto decidimos investigar por qué pasaba esto y resulta que el error que
debería saltar ya fue corregido previamente cuando corregimos ``hello3.c``, y se trataba del llamado a la función ``prontf``.  
Esto ocurre debido a que los compiladores más nuevos de C (nuestro compilador compila hasta C23 inclusive) son menos permisivos y no permiten llamar a funciones que
no fueron declaradas, en este caso, ``prontf``. Y es este el error de vinculación que tendría que haber saltado al intentar vincular ``hello4.o``
pero que fue corregido antes.  
Debido a esto vamos a saltear ``hello5.c`` y trabajar con ``hello4.c`` para lo que queda de este apartado de vinculación.  

*c)* Al ejecutar ``hello4.exe`` vemos que obtenemos como resultado un numero basura y no determinista, es decir, varía por cada ejecución y no es predecible. 
Esto ocurre ya que, dentro de ``printf``, ``%d`` esta esperando un argumento ``int``, pero no se le está pasando ninguno. Ejemplo de resultados al ejecutar:
```bash
La respuesta es 115632464
La respuesta es -363435696
La respuesta es -296588976
La respuesta es 1619355984
```  

## Corrección de Bug
*a)* Al compilar y ejecutar ``hello6.c`` obtenemos “La respuesta es 42”, lo cual indica que el bug fue solucionado y que el programa funciona correctamente.  

## Remoción de prototipo
*b)* En nuestro caso no funciona, y para explicarlo vamos a responder las siguientes preguntas:
- i. ¿Arroja error o warning?  
  Cuando intentamos compilar hello7.c, nos arrojo un error, y un warning:  
    
  ```bash
      hello7.c: In function 'main':
  hello7.c:3:5: error: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
      3 |     printf("La respuesta es %d\n", i);
        |     ^~~~~~
  hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
    +++ |+#include <stdio.h>
      1 | int main(void){
  hello7.c:3:5: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
      3 |     printf("La respuesta es %d\n", i);
        |     ^~~~~~
  hello7.c:3:5: note: include '<stdio.h>' or provide a declaration of 'printf'

  ```
  Ambos relacionados al hecho de que falta la inclusión del header ``stdio.h`` que es donde se encuentra la declaración de la funcion ``printf``. 
  Sin esta declaracion, la función no anda y no podemos compilar el código.
  
- ii. ¿Qué es un prototipo y de qué maneras se puede generar?  
  Es la declaración de una función que especifica su tipo de retorno y los tipos de sus parámetros. 
  Se puede generar declarando la funcion antes del main, incluyendo un header que contenga su declaración o definiendo directamente la función antes de usarla.  

- iii. ¿Qué es una declaración implícita de una función?  
  Consiste en usar una función sin haberla declarado antes, como pasa con ``printf`` en ``hello7.c``. Los compiladores mas viejos de C permiten que esto ocurra y compilan.

- iv. ¿Qué indica la especificación?  
  En el contexto de especificación del estándar del lenguaje C la especificación (según el estándar que se use, como C99, C11 o C23) 
  indica que todas las funciones deben ser declaradas antes de usarse. Desde C99 en adelante, las declaraciones implícitas están prohibidas 
  y su uso genera un error de compilación.  

- v. ¿Cómo se comportan las principales implementaciones?
  Tal y como se menciono previamente, en los compiladores de C mas modernos (C99 para adelante), reportan error si no hay prototipo. 
  En C antiguo, asumían ``int`` como tipo de retorno y hacían vinculación riesgosa.  

- vi. ¿Qué es una función built-in?  
  Es una función provista por el compilador, no definida por el usuario ni en una biblioteca externa.

- vii. Conjeturé la razón por la cual gcc se comporta como se comporta ¿Va realmente contra la especificación?  
  En nuestro caso, al tener GCC 14.2.0, se sigue el estándar del lenguaje C moderno en donde se prohíbe el uso de declaraciones implícitas, por ende, 
  no va en contra de la especificación. Esto quiere decir que nuestro compilador respeta la especificación mas reciente, 
  y es la razón por la cual nos da error al compilar.
  
## Compilación Separada: Contratos y Módulos
*b)* Para que la vinculación funcione y podamos generar el ejecutable encontramos dos posibles soluciones:  
  
En la primer posible solucion añadimos ``#include <stdio.h>`` en ``studio1.c``, para que  ``studio1.c`` pueda
llamar a la funcion ``printf``, ya que ocurría el mismo error que nos ocurría en ``hello7.c``. A su vez agregamos el prototipo ``void prontf(const char* s, int i);``
en la primera línea de ``hello8.c`` porque nuestro compilador prohíbe las declaraciones implícitas.  
  
En el caso de la segunda posible solución pensamos en forzar la compilación en un estándar de C mas antiguo y permisivo que permita a ``studio1.c`` utilizar a ``printf``
sin incluir el header ``stdio.h``. Para esto utilizamos los siguientes comandos:  
```bash
gcc -c studio1.c -o studio1.o -std=c89
gcc -c hello8.c -o hello8.o -std=c89
gcc hello8.o studio1.o -o hello8
```

*c)* Al hacer esto nos saltan dos errores, uno por poner argumentos de más: ``error: too many arguments to function 'prontf'.``
Y otro por poner argumentos de menos: ``error: too few arguments to function 'prontf'.``  
Esto ocurre debido a que ``prontf`` no es lo mismo que ``printf`` y esta definida de forma tal que tiene solo dos parámetros, un ``char*`` y un ``int``
, por ende, puede recibir solo eso y nada más.  

*d)* iv. ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor?   
La principal ventaja es la creación de abstracción entre consumidor y proveedor. Es decir, nuestro consumidor, ``hello9.c``, utiliza la implementación que provee 
``studio2.c`` pero lo hace mediante la interfaz que este exporta, la cual es ``studio.h``. Al hacer esto, ``hello9.c`` nunca accede realmente a ``studio2.c``
, es decir, el cliente esta desacoplado de los detalles internos de la implementación del proveedor.  
Esta abstracción facilita el mantenimiento y actualización del código, ya que se podría cambiar la implementación de ``studio2.c`` sin que el cliente se vea afectado.  
De la misma manera que ``studio2.c`` accede a la implementación de las bibliotecas estándar, pero lo hace a través de la interfaz ``stdio.h``.  

## Crédito extra
¿Qué son las bibiliotecas?  
Son colecciones de código preescrito que proporcionan funciones y procedimientos reutilizables. 
Estas pueden ser funciones, estructuras de datos, etc. que facilitan y optimizan tareas comunes sin necesidad de reescribir el código cada vez que se necesiten.  
  
¿Se pueden distribuir?  
Si, se pueden distribuir. Están diseñadas para ser distribuidas como paquetes que pueden ser instalados y usados por otros programas.  
  
¿Son portables?  
Depende, pueden ser portables como no portables. Las bibliotecas portables son diseñadas para funcionar en múltiples plataformas, 
mientras que las no portables están diseñadas para plataformas específicas. La portabilidad de una biblioteca depende de si utilizan interfaces y 
funcionalidades que son comunes en diferentes sistemas operativos y arquitecturas.  
  
Ventajas de las bibliotecas:  

- *Reutilización de código*: Las bibliotecas permiten que el código se reutilice en varios proyectos sin tener que escribirlo de nuevo.
- *Reducción de errores*: Al usar funciones ya probadas y verificadas en bibliotecas, se minimizan los errores.
- *Modularidad*: Las bibliotecas favorecen la separación de responsabilidades, lo que mejora la mantenibilidad y legibilidad del código.
- *Eficiencia*: Utilizar bibliotecas especializadas puede hacer que los programas sean más eficientes en cuanto a tiempo de desarrollo y ejecución.
- *Compartición de recursos*: Las bibliotecas dinámicas permiten que varios programas compartan el mismo código, lo que optimiza el uso de memoria y almacenamiento.
  
Desventajas de las bibliotecas:  

- *Dependencia*: Los programas que usan bibliotecas dependen de ellas. Si una biblioteca cambia o se elimina, el programa puede dejar de funcionar.
- *Tamaño del archivo*: Las bibliotecas estáticas pueden aumentar el tamaño del ejecutable, especialmente si son grandes.
- *Problemas de compatibilidad*: Las bibliotecas pueden generar conflictos si hay múltiples versiones de la misma biblioteca o si la biblioteca
  no es compatible con la plataforma.
