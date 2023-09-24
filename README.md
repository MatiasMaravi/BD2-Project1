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
### Extendible Hashing:
