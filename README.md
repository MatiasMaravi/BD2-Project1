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
El AVL es una estructura de datos que se caracteriza por ser un árbol BST autoequilibrado, donde la diferencia entre las alturas de los subárboles izquierdo y derecho, para cualquier nodo, no puede ser más de uno. Esta estructura lo usamos con archivos y registros para una búsqueda más eficiente donde cada nodo es un registro y el archivo tiene dos punteros para la organización a la derecha y a la izquierda.
<p align="center">
  <img src="https://estructurasite.files.wordpress.com/2016/04/arboles1.jpg" height="400"/>
</p>

#### Inserción:

La inserción de un registro comienza con el caso base donde el árbol tendrá su primer registro en la posición "1" del archivo y será el nodo padre del árbol. Después del primer nodo (Registro), se realizarán inserciones a la izquierda del árbol si el siguiente registro tiene un primary key menor al registro del nodo padre, de la misma forma se realizará inserciones a la derecha del árbol si el siguiente registro tiene un primary key mayor al registro del nodo padre. Cada vez que la diferencia entre las alturas del subárbol izquierdo y el subárbol derecho de cualquier nodo sea más de uno, se realizarán rotaciones en el archivo cambiando la dirección de la posición del nodo padre y los hijos dependiendo de si la rotación es a la derecha o izquierda.
<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree10.png" height="300"/>
</p>

De ser necesario en algunos casos se harán rotaciones dobles a la izquierda y derecha o derecha y izquierda.

<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree11.png" height="400"/>
</p>

#### Eliminación:
Numero 1:
La eliminación se realiza con la búsqueda del registro a eliminar y presenta los casos correspondientes. Si el nodo no tiene hijos o registros, se elimina directamente el registro ...
Numero 2:
La eliminación cuando ...
#### Búsqueda:

#### Búsqueda por rango:

### Extendible Hashing:
El extendible hashing es un método de hash dinámico en el que utilizamos directorios (índices) y depositos (Buckets) para realizar hash de datos. En términos más simples el extendible hashing es un método agresivamente flexible en el que la función hash también experimenta cambios dinámicos.

#### Inserción:
La inserción en el extendible hashing cuenta con una serie de pasos:
1. Hallar el binario del atributo por el cual vamos a insertar en el Extendible Hashing.
2. Se verifica la profundidad del Bucket en el cual se insertara el registro. Por ejemplo, si  el binario obtenido es "110001" y la profundidad del bucket es 2. Entonces, la función hash devolverá los 2 primeros numeros del binario, es decir, "11".
3. Como la inserción lo estamos haciendo siguiendo un lineamiento de un árbol digital, insertaremos a la izquierda si la posición en donde se evalue el binario es 0 y derecha si es 1. De esta forma, los buckets se encontrarán en las hojas.
  
<p align="center">
  <img width="400" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/09dad397-9a82-4bf1-8f71-b44d94555508">
</p>
  
4. Verificaremos el desbordamiento del bucket, es decir, si el bucket se encuentra lleno. De ser así, tendremos que crear otro bucket y aumentarle su profundidad. Si ya se llego a la profundidad global, es decir, el número máximo de buckets, se procederá a crear un nuevo bucket y enlazarlo al último bucket creado.

<p align="center">
  <img width="549" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/30c02482-18cd-4168-9106-cdf70028281a">
</p>

Es importante aclarar que los registros se dividiran a la mitad para el nuevo y el antiguo bucket.

<p align="center">
  <img width="404" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/b8872adf-aaf5-4fed-ab34-52142fd35755">
</p>

#### Búsqueda:

En el algoritmo de búsqueda, primero hashearemos la llave a través de la cual vamos a buscar. Luego, recorremos el arbol digital, dependiendo el valor que obtendremos en el binario. Si es "0" avanzaremos por la rama izquierda, sino iremos por la derecha. En caso no se encuentre la llave, devolverá un valor sin nada.

#### Eliminación:

En el algoritmo de Eliminación utilizaremos el algoritmo de búsqueda ya que buscaremos la llave a eliminar en el extendible y procederemos a eliminarlo. Reduciremos el número de elementos en el bucket por lo que si se inserta un nuevo elemento en el bucket, este reescribirá al registro que ya está eliminado.

#### Ventajas y desventajas:

##### Ventajas:

- No hay problema de pérdida de datos ya que la capacidad de almacenamiento aumenta dinámicamente.
- Con los cambios dinámicos en la función hash, los valores antiguos asociados se repiten con la nueva función hash.

##### Desventajas:

- El número de buckets puede aumentar significativamente si se aplican hash a varios registros en el mismo bucket manteniendo la distribución de registros no uniforme.
- Desperdicio de memoria debido a que ciertos depósitos contienen más datos que otros.
