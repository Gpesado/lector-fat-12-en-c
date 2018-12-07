# lector-fat-12-en-c
Lector de estructura y de archivos FAT 12 realizado en C.

# Informe
Explicacion de funcionamiento de los archivos .c:

## read_boot.c :
La función principal de este archivo es la de mostrar el Fat12 Boot Sector del filesystem
FAT12, para esto se define el struct Fat12BootSector utilizando como guía el material dejado
como referencia en el TP.
1) Primero que nada, se carga la imagen del filesystem FAT12 mediante un fopen.
2) Antes de analizar el boot, se revisa si la partición es de tipo FAT12, utilizando el mismo
manejo que se realizó en el read_mbr.c. En caso de que no sea de tipo FAT12 el
programa terminará con return -1, en caso contrario continuará su ejecución.
3) Utilizando un fseek al puntero 0 empezaremos a leer desde dicha posición el Fat12 Boot
Sector, almacenando la información en el struct Fat12BootSector.
4) Luego de esto, mediante varios printf se muestra toda la información obtenida del struct
Fat12BootSector.
5) Por último se cerrará el filesystem y fin del programa.

## read_mbr.c :
Este archivo tiene como función principal mostrar la cantidad de tablas de particiones que
hay, junto con los datos más relevantes de ellas que son “Primer Byte” (para ver si es
booteable o no), “Inicio de CHS”, Tipo de partición, “Fin de CHS”, “Dirección de LBA”, y
“longitud de Sectores”. Para esto se guardarán en el struct definido como “PartitionTable”.
1) Primero que nada, se carga la imagen del filesystem FAT12 mediante un fopen.
2) Usando un fseek al puntero 0x1BE nos moveremos a dicha posición en la cual están
las tablas de particiones
3) Luego de esto iremos leyendo con fread las 4 tablas de particiones del sistema utilizando
el struct comentado anteriormente.
4) Con toda la información ya recolectada del struct de las particiones , se irá mostrando la
misma con varios printf.
5) Por último se cerrará el filesystem y fin del programa.

## read_root.c :
Este archivo tiene como función principal mostrar la información de cada entrada en el
directorio raíz. Para esto se definen todas las estructuras necesarias a utilizar, en nuestro
caso PartitionTable (Estructura utilizada para cada entrada en la tabla de particiones 16
bytes), Fat12BootSector (Estructura que contendrá la información del MBR en especial la
del boot sector) y Fat12Entry (Estructura utilizada para leer cada entrada del root directory
32 bytes).
1) De igual manera que en los archivos anteriores abrimos el archivo, nos ubicamos en
la tabla de particiones, leemos las entradas, luego volvemos al inicio, y leemos el
boot sector.
2) A partir de acá, mostramos la ubicación en donde nos encontramos, el tamaño de
los sectores, el tamaño de la FAT en sectores, y cuantos FAT existen.
3) La ubicación hasta ese momento es el inicio de las tabla FAT, osea el 0x200.
4) Con fseek nos pasamos por encima las 2 tabla fat moviéndonos 2048 bytes y
ubicándonos en el root directory (2048 bytes ya que existen 2 FAT, cada FAT tiene 2
sectores y un sector mide 512 bytes).
5) Una vez ubicados en el root directory, recorremos cada entrada con fread y con la
estructura FAT12Entry de 32 bytes. El root directory tiene 512 entradas.
6) Por cada entrada, ejecutamos la función print_file_info que recibe el buffer que
leeremos usando la estructura y esta función se encarga de mostrar el nombre de
los archivos borrados, archivos y directorios basándose en su primer byte y en su
atributo.
7) Una vez mostrada cada entrada en el root directory. Mostramos la ubicación del
primer cluster del disco.

## leertxt.c :
Este archivo tiene como función leer el archivo HOLA.txt, el cual es el único archivo no
borrado con contenido en el filesystem.
Para esto, se utiliza casi el mismo código utilizado en leer root, ya que se necesita la información
del MBR para conocer el tamaño de los clusters y llegar hasta el comienzo del primer cluster
(luego del root directory).
1) Seguimos la misma secuencia que el read_root.c
2) Una vez que encontramos el archivo en una de las entradas del root directory,
capturamos la información del cluster donde se encuentra y el tamaño del archivo.
3) Con esos datos, llamamos al método leer que recibe los datos mencionado
anteriormente y además el tamaño del cluster y la posición del primer cluster luego del
root directory, que es tamaño de un sector * cantidad de sectores que forman un cluster
4) Una vez en leer, abrimos la imagen y con fseek nos ubicamos en la posición de memoria
en el cual se encontraría el primer cluster del archivo. Para esto, realizamos la cuenta:
Posición del primer cluster + (número del primer cluster del archivo - 2 * tamaño del
cluster)
5) Luego, utilizamos el dato del tamaño del archivo y con fread llenamos el buffer con los
datos del archivo txt. Y por último se muestra con printf
