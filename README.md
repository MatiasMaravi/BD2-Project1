# Base de Datos II: Proyecto 1

### Integrantes:
- Calizaya Alvarez, Alejandro
- Isidro Salazar, Leonardo
- Machaca Soloaga, Leandro
- Maravi Anyosa, Matias
- Sandoval Rivera, Jerimy
## Introduccion:
### Objetivo del proyecto:

- Implementar estructura de datos en archivos para realizar una mejor busqueda de registros en archivos, para conseguir busquedas eficientes y rapidas.
- Desarrollar algoritmos de busqueda con menor tiempo de ejecucion en el acceso a memoria secundaria
  
### Descripcion del dominio de datos a usar:
**Falta**

### Resultados que esperamos obtener mediante el uso de tecnicas de indexacion:

- Verificar que el uso de estructura de datos vistos en clase son una mejor forma de acceder a registros en memoria secundaria.
- Establecer que estructura de datos es la mas eficiente en tiempo de ejecucion y acceso a memoria secundaria.
- Disminuir la cantidad de accesos a memoria a secundaria.
- Ordenar los registros en memoria secundaria de una manera eficiente
- Recuperacion y eliminacion eficiente de registros. 


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
El AVL es una estructura de datos que se caracteriza por ser un árbol BST autoequilibrado donde la diferencia entre las alturas de los subárboles izquierdo y derecho para cualquier nodo no puede ser más de uno. Esta estructura lo usamos con archivos y registros para una búsqueda más eficiente donde cada nodo es un registro y el archivo tiene dos punteros para la organizacion a la derecha y a la izquierda.
<p align="center">
  <img src="https://estructurasite.files.wordpress.com/2016/04/arboles1.jpg" height="400"/>
</p>

#### Inserción:

La inserción de un registro comienza con el caso base donde el árbol tendrá su primer registro en la posición 1 del archivo y será el nodo padre del árbol. Después del primer nodo (registro), se realizarán inserciones a la izquierda del árbol si el siguiente registro tiene una llave primaria menor al registro del nodo padre, de la misma forma se realizarán inserciones a la derecha del árbol si el siguiente registro tiene una llave primaria mayor al registro del nodo padre. Cada vez que la diferencia entre las alturas del subárbol izquierdo y el subárbol derecho de cualquier nodo sea más de uno, se realizarán rotaciones en el archivo cambiando la dirección de la posición del nodo padre y los hijos dependiendo de si la rotación es a la derecha o izquierda.
<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree10.png" height="250"/>
</p>

De ser necesario en algunos casos se harán rotaciones dobles a la izquierda y derecha o derecha e izquierda.

<p align="center">
  <img src="https://www.ibiblio.org/pub/Linux/docs/LuCaS/Tutoriales/doc-programacion-arboles-avl/htmls/tree11.png" height="400"/>
</p>

#### Eliminacion:

<p align="center">
  <img src="https://i.ibb.co/SxK675f/avl1.png" height="400"/>
</p>

Caso 1:
La eliminación se realiza con la búsqueda del registro a eliminar y presenta los casos correspondientes, si el nodo padre no tiene hijos (registros), se elimina directamente el registro.
<p align="center">
  <img src="https://raw.githubusercontent.com/MatiasMaravi/BD2-Project1/main/Imagenes/AVLFile_img/AVLF1.png" height="250"/>
</p>

<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/AVLFile_img/AVLF2_1.png?raw=true" height="250"/>
</p>

Caso 2:
La eliminación cuando el nodo padre solo tiene un hijo a la izquierda o a la derecha se cambia directamente el nodo con el padre y ahora el nodo padre es una hoja, que se puede eliminar, en el caso de registro se escribe el registro del nodo padre con el hijo.

<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/AVLFile_img/AVLF3.png?raw=true" height="250"/>
</p>

<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/AVLFile_img/AVLF4.png?raw=true" height="250"/>
</p>

Caso 3: 
La eliminación cuando el nodo padre tiene dos hijos se busca al nodo izquierdo mayor del sub arbol de registros para intercambiar por el padre, en este casos e sobre escribe el padre con el hijo para luego realizar el remove del nodo repetido del sub-arbol, en este caso eliminar el registro una vez sobre escrito.

<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/AVLFile_img/AVLF6.png?raw=true" height="250"/>
</p>

<p align="center">
  <img src="https://github.com/MatiasMaravi/BD2-Project1/blob/main/Imagenes/AVLFile_img/AVLF7.png?raw=true" height="250"/>
</p>

Después de cada eliminación se realiza un balance y un update height al AVL del archivo.
#### Búsqueda:

La búsqueda se realiza de la siguiente manera tras un método recursivo buscamos al registro que tenga el mismo value a buscar en el archivo recorriendo el árbol hacia al lado izquierdo del sub arbol o hacia al lado derecho del sub arbol, con la condición de que el value sea mayor o menor.

#### Búsqueda por rango:

La búsqueda por rango es la misma que la búsqueda de un registro con la diferencia de que al momento de encontrar un registro, dentro del rango establecido. Se almacena en un vector de registros recorriendo el árbol hacia al lado izquierdo del subárbol o hacia al lado derecho del subárbol, con la condición de que el value sea mayor o menor.

### Extendible Hashing:
El extendible hashing es un método de hash dinámico en el que utilizamos directorios (índices) y depósitos (Buckets) para realizar hash de datos. En términos más simples, el extendible hashing es un método agresivamente flexible en el que la función hash también experimenta cambios dinámicos.

#### Inserción:
La inserción en el extendible hashing cuenta con una serie de pasos:
1. Hallar el binario del atributo por el cual vamos a insertar en el Extendible Hashing.
2. Se verifica la profundidad del Bucket en el cual se insertara el registro. Por ejemplo, si  el binario obtenido es "110001" y la profundidad del bucket es 2. Entonces, la función hash devolverá los 2 primeros numeros del binario, es decir, "11".
3. Como la inserción lo estamos haciendo siguiendo un lineamiento de un árbol digital, insertaremos a la izquierda si la posición en donde se evalue el binario es 0 y derecha si es 1. De esta forma, los buckets se encontrarán en las hojas.
  
<p align="center">
  <img width="400" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/09dad397-9a82-4bf1-8f71-b44d94555508">
</p>
  
4. Verificaremos el desbordamiento del bucket, es decir, si el bucket se encuentra lleno. De ser así, tendremos que crear otro bucket y aumentarle su profundidad. Si ya se llegó a la profundidad global, es decir, el número máximo de buckets, se procederá a crear un nuevo bucket y enlazarlo al último bucket creado.

<p align="center">
  <img width="549" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/30c02482-18cd-4168-9106-cdf70028281a">
</p>

Es importante aclarar que los registros se dividirán a la mitad para el nuevo y el antiguo bucket.

<p align="center">
  <img width="404" alt="image" src="https://github.com/MatiasMaravi/BD2-Project1/assets/90939274/b8872adf-aaf5-4fed-ab34-52142fd35755">
</p>

#### Búsqueda:

En el algoritmo de búsqueda, primero hashearemos la llave a través de la cual vamos a buscar. Luego, recorremos el árbol digital, dependiendo el valor que obtendremos en el binario. Si es "0" avanzaremos por la rama izquierda, sino iremos por la derecha. En caso no se encuentre la llave, devolverá un valor sin nada.

#### Eliminación:

En el algoritmo de Eliminación utilizaremos el algoritmo de búsqueda ya que buscaremos la llave a eliminar en el extendible y procederemos a eliminarlo. Reduciremos el número de elementos en el bucket por lo que si se inserta un nuevo elemento en el bucket, este reescribirá al registro que ya está eliminado.

#### Ventajas y desventajas:

##### Ventajas:

- No hay problema de pérdida de datos ya que la capacidad de almacenamiento aumenta dinámicamente.
- Con los cambios dinámicos en la función hash, los valores antiguos asociados se repiten con la nueva función hash.

##### Desventajas:

- El número de buckets puede aumentar significativamente si se aplican hash a varios registros en el mismo bucket manteniendo la distribución de registros no uniforme.
- Desperdicio de memoria debido a que ciertos depósitos contienen más datos que otros.

## Accesos a Memoria Secundaria:
### Inserción:
- Sequential File: O(n)
- AVL File: O(log n)
- Extendible Hashing: O(log n)

Entendemos que, tanto el AVL File como el Extendible Hashing, son las mejores opciones para insertar valores. Esto se debe a que el Sequential File depende de un caso importante, cuando el archivo auxiliar alcanza su tope. Cuando este sucede, se procede a reordenar, algo que no pasa con las demás técnicas.

### Búsqueda:
- Sequential File: O(log n) + O(k)
- AVL File: O(log n)
- Extendible Hashing: O(log n) + O(m)

En este caso, podemos observar que el AVL File es el más eficiente para las búsquedas ya que no depende de ningún factor adicional, como lo son los tamaños de los archivos auxiliares y el contenido del bucket.

### Eliminación:
- Sequential File: O(log n) + O(k)
- AVL File: O(log n)
- Extendible Hashing: O(log n) + O(m)

Al igual que el caso anterior, como se buscan en primera instancia los valores a eliminar, entonces utiliza la misma lógica. Por lo tanto, el AVL File sigue obteniendo la ventaja.

Donde:
- k: Número de registros en el "archivo auxiliar" del Sequential File
- m: Tamaño del bucket del Extendible Hashing
## Parser
### Descripción:
Para nuestro Parser de sentencias SQL hacemos uso de las siguientes clases:
- **Token**: Clase que representa un token de la sentencia SQL. Esta clase tiene un atributo de tipo enum que representa el tipo de token y un atributo de tipo string que representa el lexema del token.
```cpp
struct Token{
    enum Type{SELECT, ALL, 
                FROM, TABLE, 
                WHERE, CREATE, 
                INSERT, DELETE, 
                VALUES, INTO, 
                FILE, USING, 
                INDEX, HASH,
                AVL, SEQUENTIAL,
                BETWEEN, AND,
                STRING, NUMBER, 
                EQUAL, ID,
                LPAREN, RPAREN, VALUEPAREN,
                END, ERR};
    Type type;
    static const char* token_names[25];
    string lexema;
    Token(Type): type(type){
        lexema = "";
    }
    Token(Type type, const string lexema): type(type), lexema(lexema){}
};
```
- **Scanner**: Clase que representa un scanner de la sentencia SQL. Esta clase tiene un atributo de tipo unordered_map que representa las palabras reservadas de la sentencia SQL y un atributo de tipo string que representa la sentencia SQL. Nos sirve para obtener los tokens de la sentencia SQL.
```cpp
class Scanner{
public:
    Scanner(const char* input);
    Token* nextToken();
    bool paren_flag = false;
private:
    unordered_map<string, Token::Type> reserved;
    string input;
    int first, current;
    char nextChar();
    void rollBack();
    void startLexema();
    void consume_white_spaces(char &c);
    Token* scan_number(char &c);
    Token* scan_alpha(char &c);
    Token* scan_string(char &c);
    Token* scan_lparen(char &c);
    Token* scan_valueparen(char &c);
    Token::Type checkReserved(string lexema);
    string getLexema();
};
```
- **Parser**: Clase que representa un parser de la sentencia SQL. Esta clase tiene un atributo de tipo Scanner que representa el scanner de la sentencia SQL. Es la clase que verifica la sintaxis de la sentencia SQL. También ejecuta las funciones correspondientes a las QuerysSQL
```cpp
class Parser{
    Scanner* scanner;
    Token* current, *previous;
    bool match(Token::Type type);
    bool check(Token::Type type);
    bool advance();
    bool isAtEnd();
public:
    Parser(Scanner* scanner):scanner(scanner){
        previous = current = nullptr;
    }
    bool parse();
    bool parse_create_table();
    bool parse_select();
    bool parse_insert();
    bool parse_delete();
};
```
## Multindexacion
Para poder indexar un registro por cualquier atributo tuvimos que hacer uso de programación funcional, más especificamente Lambda Functions. Gracias a esto al momento de crear la estructura se define por cuál atributo del registro se va a indexar, buscar y eliminar.
- Ejemplo:
```cpp
template <class T, typename TK>
class AVLFile{
    string filename;
    long pos_root;
    std::function<bool(const T &, const T &)> less;
    std::function<bool(const T &, const T &)> greater;
    std::function<bool(const T &, const TK &)> equal_key;
    std::function<bool(const T &, const TK &)> less_key;
    std::function<bool(const T &, const TK &)> greater_key;
    std::function<TK(const T &)> get_key;
    public:
    //Resto del código...
}
```
- Ejemplo de instancia
```cpp
    key = cod
    AVLFile<Record,int> file("data.dat",
                    []( Record const&a, Record const&b) { return a.cod < b.cod;}, //less
                    []( Record const&a, Record const&b) { return a.cod > b.cod;}, //greater
                    []( Record const&a, int const&b) { return a.cod == b;}, //equal_key
                    []( Record const&a, int const&b) { return a.cod < b;}, //less_key
                    []( Record const&a, int const&b) { return a.cod > b;}, //greater_key
                    []( Record const&a) { return a.cod;} //get_key
                        );
```

## Conclusiones

- Sequential file es la estructura de datos menos conveniente a usar, por tener menor eficiencia que las otras que usamos.
- AVl file es la estructura de datos con mejor tiempo de ejecucion en accesos a memoria secundaria.
- Busqueda de registros en las 3 estructuras de datos implementadas son muy parecidas en cuestion de complejidad y acceso a memoria secundaria.

