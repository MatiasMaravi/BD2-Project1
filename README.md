# BD2-Project1
# Base de Datos II: Proyecto 1

### Integrantes:
- Calizaya Alvarez, Alejandro
- Isidro Salazar, Leonardo
- Machaca Soloaga, Leandro
- Maravi Anyosa, Matias
- Sandoval Rivera, Jerimy

## Técnicas de Organización de Archivos:
### Sequential File:
El Sequential File es una técnica que usa, para un entendimiento mejor, punteros para su organización. Además, este usa dos archivos: uno para los "datos principales" y otro para los "datos auxiliares".

#### Inserción:
Este algoritmo es sencillo de entender. Simplemente verificamos si el registro a insertar es mayor al último registro perteneciente al "archivo principal". Si esto se cumple, insertamos este a la última parte del dicho archivo. Caso contrario, se le agrega al "archivo auxiliar". Cabe resaltar que cada vez que se ingresa se deben actualizar los punteros de los registros asociados al nuevo registro ingresado. Por lo cual, existen dos casos:
##### Caso 1:
Cuando el registro a insertar es el "mayor" (con respecto a la llave primaria) a todos los demás.
<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/SeqFile_img/SF1.png" height="400"/>
</p>

##### Caso 2:
Cuando el registro a insertar se encuentra entre dos registros.
<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/SeqFile_img/SF2.png" height="400"/>
</p>

Además, cuando se alcance el máximo de registros permitidos en el "archivo auxiliar", este procederá a realizar la reorganización.

#### Eliminación:
Este algoritmo se encarga de dos cosas. En primer lugar, hallará el valor a eliminar para obtener su predecesor y sucesor. En segundo lugar, será capaz de actualizar el puntero del registro a eliminar con el valor "-1a" ya que este puntero nunca se utiliza.
<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/SeqFile_img/SF3.png" height="400"/>
</p>

#### Búsqueda:
Para la búsqueda tenemos dos casos: búsqueda simple y búsqueda por rango. El primero, simplemente, realizará una búsqueda binaria en el "archivo principal". Si no se encuentra en el "archivo principal", entonces se recorrerá todo el "archivo auxiliar" hasta que se encuentre. Si se encuentra el registro a buscar, se retornará un puntero de este; sino, retornará un puntero vacío. El segundo, comparará con respecto a los valores condicionales, es decir, aquellos registros que están dentro del rango de los valores ingresados. Por lo cual, comienza desde el primer registro y va agregando aquellos registros que cumplan con esta condición. Hasta encontrar un registro que no cumpla con esta condición, se seguirá recorriendo los archivos.

### AVL File:
El avl es una estructura de datos que se caracteriza por ser un arbol BST autoequilibrado donde la diferencia entre las alturas de los subárboles izquierdo y derecho para cualquier nodo no puede ser más de uno. De esta estructura lo usamos con archivos y registros para una busqueda mas eficiente donde cada nodo es un registro y el archivo tiene dos punteros para la organizacion a la derecha y a la izquierda.
<p align="center">
  <img src="https://estructurasite.files.wordpress.com/2016/04/arboles1.jpg" height="400"/>
</p>

### Inserccion:

La inserccion de un registro comienza con el caso base donde el arbol tendra su primer registro en la posicion 1 del archivo y sera el nodo padre del arbol. Despues del primer nodo(Registro). Se realizaran insercciones a la izquierda del arbol si el siguiente registro tiene un primary key menor al registro del nodo padre, de la misma forma se relizara inserciones a la derecha del arbol si el siguiente registro tiene un primary key mayor al registro del nodo padre. Cada vez que la diferencia entre las alturas del subárbol izquierdo y el subárbol derecho de cualquier nodo sea mas de uno se realizaran rotaciones en el archivo cambiando la direccion de la poscion del nodo padre y los hijos dependiendo de si la rotacion es a la derecha o izquierda.
<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree10.png" height="400"/>
</p>

De ser necesario en algunos casos se haran rotaciones dobles a la izquierda y derecha o derecha y izquierda.

<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree11.png" height="400"/>
</p>

### Eliminacion:
Numero 1:
La eliminacion se realiza con la busqueda del registro a eliminar y presenta los casos correspondientes, si el nodo no tiene hijos o registros. Se elimina directamente el registro
Numero 2:
La eliminacion cuando 
### Busqueda:

### Busqueda por rango:

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
- Como la inserccion lo estamos haciendo siguiendo un lineamiento de un árbol digital, insertaremos a la izquierda si el la posicion en donde se evalue el binario es 0 y derecha si es 1, de esta forma los buckets se encontraran en las hojas.
  
<p align="center">
  <img width="670" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/09dad397-9a82-4bf1-8f71-b44d94555508">
</p>
  
Paso 4:
- Verificaremos el desbordamiento del bucket es decir si el bucket se encuentra lleno, de ser asi tendremos que crear otro bucket y aumentarle su profundidad, si ya se llego a la profundidad global, es decir el numero maximo de buckets, se procedera a crear un nuevo bucket y enlazarlo al ultimo bucket creado.

<p align="center">
  <img width="549" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/30c02482-18cd-4168-9106-cdf70028281a">
</p>

- Es importante aclarar que los registros se dividiran a la mitad para el nuevo y el antiguo bucket.

<p align="center">
  <img width="404" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/b8872adf-aaf5-4fed-ab34-52142fd35755">
</p>

#### Busqueda:

En el algoritmo de busqueda, primero hashearemos la llave a travez de la cual vamos a buscar, luego recorremos el arbol digital, dependiendo el valor que obtendremos en el binario, si es o avanzaremos por la rama izquierda sino iremos por la derecha, en caso no se encuentre la llave, devolvera un valor sin nada.

#### Eliminacion:

En el algoritmo de Eliminación utilizaremos el algoritmo de busqueda ya que buscaremos la llave a eliminar en el extendible y procederemos a eliminarlo, reduciremos el numero de elementos en el bucket por lo que si se inserta un nuevo elemento en el bucket, este reescribira al registro que ya esta eliminado.

### Ventajas y desventajas:

### Ventajas:

- No hay problema de pérdida de datos ya que la capacidad de almacenamiento aumenta dinámicamente.
- Con los cambios dinámicos en la función hash, los valores antiguos asociados se repiten con la nueva función hash.

### Desventajas:

- El numero de buckets puede aumentar significativamente si se aplican hash a varios registros en el mismo bucket manteniendo la distribución de registros no uniforme.
- Desperdicio de memoria debido a que ciertos depósitos contienen más datos que otros.
