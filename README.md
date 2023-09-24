# BD2-Project1

### Extendible Hashing:
El extendible hashing es un metodo de hash dinamico en el qu utilizamos directorios(indices) y depositos(Buckets) para realizar hash de datos. En terminos mas simples el extendible
hashing es un metodo agresivamente flexible en el que la función hash también experimenta cambios dinámicos.

#### Inserción:
La inserccion en el extendible hashing cuenta con una serie de pasos:

Paso 1:
- Hallar el binario de la llave a insertar en el hash table.

Paso 2:
- Se verifica la profundidad del Bucket en el cual se insertara el registro.
  Por ejemplo , si  el binario obtenido es: 110001 y la profundidad del bucket es 2. Entonces, la función hash devolverá los 2 primeros numeros del binario es decir 11.
  
Paso 3:
- Verificaremos el desbordamiento del bucket es decir si el bucket se encuentra lleno, de ser asi tendremos que crear otro bucket y aumentarle su profundidad

