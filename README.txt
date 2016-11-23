#INSTALLATION
#Instalación

Antes de la instalacion se debe contar con CMake, ParadisEO y mingw32 (en Windows)
A continuación se describen los pasos para su instalación en sistemas Linux
	1)Ser usuario root
	2)apt-get install libboost-all-dev
	3)apt-get install cmake
	4)Para PardisEO revisar Anexo A Tesis


Verificar que Gnuplot tenga instalado el visor 'wxt', si no cuenta con el ejecutar
apt-get install gnuplot-x11

#Agregar al archivo CMakelist.txt la ubicación de ParadisEO

#Para la compilacion del trabajo seguir los siguientes pasos

##En la linea de comandos, ir al sub-directorio build del trabajo e ingresar los siguiente comando:

###Para Linux
> cmake .. (On Unix) //Para identificar el compilador y chequear las dependencias
> make //Para compilar el codigo
> make install //Para cargar los archivos de configuracion y escenarios de pruebas
> cd application //Es la carpeta donde se compila el codigo

###Dentro de la carpeta build/application se encuentran las Matriz1(R5), Matriz2(R4), Matriz3(R3), Matriz4(R2). Para ejecutar el algoritmo
se debe cambiar el nombre de cualquiera de estos archivo por el nombre Matriz.
###Para la ejecución es de obligación contar con los archivos: Anclas, Matriz y Allposition (son todas las posiciones reales de todos los nodos, se utiliza solo para motrar los resultados graficamente).

> ./nombrecodigo @nombre.param // Se ejecuta el codigo con el correspondiente archivo de configuración

###Para windows 
> cmake .. -G "MinGW Makefiles" o cmake .. -G"Visual Studio 9 2008" //todo depende del compilador que se utilice.
> mingw32-make (On Window) //Para compilar el codigo
