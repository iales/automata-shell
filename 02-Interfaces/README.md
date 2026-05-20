# TP 2 - Interfaces & Makefile — Temperaturas

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

🔗 [Ver enunciado del trabajo práctico](https://josemariasola.github.io/ssl/assignments/Ssl%20Assignments.pdf#page=33)

---

# Acerca del trabajo práctico  

Para este trabajo utilizamos un Makefile que automatiza la compilación de los dos ejecutables del proyecto: `TablasDeConversion` y `ConversionTest`; el Makefile incluye reglas para cada archivo objeto `.o`, lo cual ayuda a entender cómo se construye cada parte del programa.  
Sin embargo, este podría simplificarse eliminando esas reglas intermedias, ya que make puede generarlas automáticamente si se definen correctamente las dependencias de los ejecutables. Entonces el Makefile podria quedar de la siguiente manera y crear los dos ejecutables sin problemas:  
```bash
ConversionTest : ConversionTest.o Conversion.o

TablasDeConversion : TablasDeConversion.o Conversion.o
``` 
Por otro lado, tambien se lo podría hacer más extenso, agregando los comandos a ejecutar para cada uno de los objetivos. Por ejemplo en el caso de ConversionTest:
```bash
ConversionTest : ConversionTest.o Conversion.o
	cc ConversionTest.o Conversion.o -o ConversionTest

ConversionTest.o : ConversionTest.c Conversion.h
	cc -c ConversionTest.c
``` 
