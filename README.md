# BD2-Project1

### Extendible Hashing:
El extendible hashing es un metodo de hash dinamico en el que utilizamos directorios(indices) y depositos(Buckets) para realizar hash de datos. En terminos mas simples el extendible
hashing es un metodo agresivamente flexible en el que la función hash también experimenta cambios dinámicos.

#### Inserción:
La inserccion en el extendible hashing cuenta con una serie de pasos:

Paso 1:
- Hallar el binario del atributo por el cual vamos a insertar en el extendible hashing.

Paso 2:
- Se verifica la profundidad del Bucket en el cual se insertara el registro.
  Por ejemplo , si  el binario obtenido es: 110001 y la profundidad del bucket es 2. Entonces, la función hash devolverá los 2 primeros numeros del binario es decir 11.

Paso 3:  
- Como la inserccion lo estamos haciendo siguiendo un lineamiento tipo árbol, insertaremos a la izquierda si el la posicion en donde se evalue el binario es 0 y derecha si es 1, de esta forma los buckets se encontraran en las hojas.
  
  <img width="542" alt="image" aling="center" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/9ee84baa-9287-4e86-936f-bed2b5104fd4">

  
Paso 4:
- Verificaremos el desbordamiento del bucket es decir si el bucket se encuentra lleno, de ser asi tendremos que crear otro bucket y aumentarle su profundidad, si ya se llego a la profundidad global, es decir el numero maximo de buckets, se procedera a crear un nuevo bucket y enlazarlo al ultimo bucket creado.

- Es importante aclarar que los registros se dividiran a la mitad para el nuevo y el antiguo bucket.

  

