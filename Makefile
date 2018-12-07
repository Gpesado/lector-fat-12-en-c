.PHONY: all clean

SRC = read_boot.c read_mbr.c read_root.c leertxt.c
BIN = $(SRC:.c=)

clean:
	rm -f $(BIN) $(OBJ)

all: 
	gcc read_boot.c -o read_boot
	gcc read_mbr.c -o  read_mbr
	gcc read_root.c -o read_root
	gcc leertxt.c -o leertxt 

echo "BIENVENIDOS AL COMPILADOR DEL PROGRAMA!"
echo "EN EL MISMO SE COMPILARA Y SE MOSTRARA CADA RESULTADO"
echo "PERTENECIENTE AL TP 1"
echo ""
echo ""
echo "TP 1"
echo "MATERIA: SISTEMAS OPERATIVOS Y REDES 2"
echo "PROFESOR:"
echo "	-TCACH, ALEXIS GUIDO"
echo "ALUMNOS:"
echo "	-PESADO, GONZALO"
echo "	-POMPILIO, MAXIMILIANO"
echo "	-DIAZ, JONATAN"

echo ""
echo "PUNTO 2, MOSTRAR EL MBR MEDIANTE CODIGO C"
echo ""
echo "BOOT SECTOR"
echo ""
./read_boot
echo ""
echo "TABLA DE PARTICION"
echo ""
./read_mbr
echo ""
echo "PUNTO 3 (A), MOSTRAR CUANTOS Y CUALES ARCHIVOS TIENE EL FILESYSTEM"
echo ""
./read_root
echo ""
echo "PUNTO 4 (A), MOSTRAR QUE HAY EN EL ARCHIVO NO BORRADO"
echo ""
./leertxt
echo ""
echo ""
echo "MUCHAS GRACIAS POR UTILIZAR ESTE COMPILADOR DE CODIGO"
