#include <eo>
#include <Individuo.h>
#include <IndiInit.h>
#include <localizacionEval.h>
#include <localizacionEvalPenal.h>
#include <individuoCruza.h>
#include <IndiSwapMutation.h>
#include <individuoMutacion.h>
#include <escenario.h>
#include <sys/time.h>




int main (int argc, char* argv[]){

//Primero se debe definir un parser que lee desde la linea de comandos o un archivo
    eoParser parser(argc, argv);
//Se definen los parametros, se leen desde el parser y le asigna el valor
    //Datos necesarios del escenario de prueba
    double _min = parser.createParam((double)(0.0), "ValorMinimo", "Delimitacion area de trabajo",'M',"Parametros Escenario").value();
    double _max = parser.createParam((double)(20.0), "ValorMaximo", "Delimitacion area de trabajo",'S',"Parametros Escenario").value();
    unsigned int NoAnclas = parser.createParam((unsigned int)(10), "Anclas", "Numero de nodos anclas",'A',"Parametros Escenario").value();
    unsigned int nodos = parser.createParam((unsigned int)(100), "Nodos", "Total de nodos",'N',"Parametros Escenario").value();
    double radio = parser.createParam((double)(5), "Radio", "Radio de comunicacion",'R',"Parametros Escenario").value();

    double DisReal[200][200];
    double vecAnclas[NoAnclas*2];

//Configuracion parametros algoritmo
    unsigned int POP_SIZE = parser.createParam((unsigned int)(100), "PopSize", "Tamano de la poblacion",'P',"Parametros Algoritmo").value();
    unsigned int numberGeneration = parser.createParam((unsigned int)(1000), "MaxGen", "Criterio de parada, Numero maximo de generaciones",'G',"Parametros Algoritmo").value();
    unsigned int Nc = parser.createParam((unsigned int)(2), "Nc", "Constante del operador SBX",'C',"Parametros Algoritmo").value();
    double Pcruza = parser.createParam((double)(0.87), "Pcruza", "Probabilidad de cruzamiento SBX",'X',"Parametros Algoritmo").value();
    double Pmutation = parser.createParam((double)(0.85), "Pmutacion", "Probabilidad de mutacion de la encapsulacion de SVN y Swap",'Y',"Parametros Algoritmo").value();
    double Pmutation1 = parser.createParam((double)(0.85), "Pmutacion1", "Probabilidad de mutacion de SVN",'Z',"Parametros Algoritmo").value();
    double Pmutation2 = parser.createParam((double)(0.5), "Pmutacion2", "Probabilidad de mutacion de Swap",'W',"Parametros Algoritmo").value();
    double sizeTorneo = parser.createParam((double)(8), "SizeTorneo", "Tamano del torneo para seleccion de individuos",'L',"Parametros Algoritmo").value();
    double sizeElist = parser.createParam((double)(2), "SizeElist", "Cantidad de individuos que se conservan",'B',"Parametros Algoritmo").value();
    double sizeTorneo1 = parser.createParam((double)(2), "SizeTorneo1", "Tamano del torneo para seleccion de individuos del elitismo",'Q',"Parametros Algoritmo").value();

//Parametros de guardado
    unsigned int setGeneracion = parser.createParam((unsigned int)(100), "setGeneracion", "Cada cuantas generaciones se guarda la poblacion",'T',"Guardar Datos").value();
    unsigned int setTime = parser.createParam((unsigned int)(0), "setTime", "Cada cuantos segundos se guarda la configuracion",'I',"Guardar Datos").value();

//Grafica
    std::string InPut = parser.createParam(std::string("Estadistica.txt"), "Input", "Archivo que contiene el Fitness, Media, DevStand",'o',"Salida - Grafica").value();
    bool graficaGnuplot = parser.createParam((bool)(0), "Gnuplot", "Grafica el Fitness y Media, 0 desactivado y 1 activado",'g',"Salida - Grafica").value();

//Termina la ejecucion al consultar la ayuda
    if (parser.userNeedsHelp())
         {
             parser.printHelp(std::cout);
             exit(1);
         }
//Verifica el ingreso de las probabilidades
    if ( (Pcruza < 0) || (Pcruza > 1) ) throw std::runtime_error("Pcruza Invalido");
    if ( (Pmutation < 0) || (Pmutation > 1) ) throw std::runtime_error("Pmutation encapsulaci�n Invalido");
    if ( (Pmutation1 < 0) || (Pmutation1 > 1) ) throw std::runtime_error("Pmutation de SVN Invalido");
    if ( (Pmutation2 < 0) || (Pmutation2 > 1) ) throw std::runtime_error("Pmutation de Swap Invalido");

//Parametro de tiempo
    struct timeval ti, tf;
    double tiempo;

/**CARGAR EL ESCENARIO**/
//Escenario
    //Lee desde archivo
    escenario *pEscenario = new escenario(nodos, NoAnclas);
    //Matriz de distancia
    for (int i=0; i<nodos ; i++)
        {for (int j=0; j<nodos; j++)DisReal[i][j] = pEscenario->obtenerDisRSSI(i,j);}
    //Posicion Nodos anclas
    for (int i=0 ; i<NoAnclas*2 ; i++)vecAnclas[i] = pEscenario->obtenerAnclas(i);

/**--------------------------------------------------------------**/

//Define la representaci�n (Individuo)
    Individuo cromosoma;

//Para la inicializaci�n del cromosoma, primero se debe definir como se generaran los genes
//Se utilizara un generador uniforme, (valor min, valor max)
    eoUniformGenerator<double> uGen(_min, _max);

//Crear el inicializador para los cromosomas, llamado random
    IndiInit random(nodos*2,uGen);

//Generar una subclase de la clase de la funci�n de evaluaci�n
    localizacionEvalPenal Fitness;

//Criterio de parada
    eoGenContinue<Individuo> parada(numberGeneration);

//Es otro criterio de parada en el cual se define el minimo de generaciones y cuantas generaciones sin mejoras
    //eoSteadyFitContinue<Individuo> parada(10,2);

/** CRUZA **/

    // Generar los limites para cada gen
    std::vector<double> min_b;
    std::vector<double> max_b;
    for(int i=0; i<nodos*2; i++) {
            min_b.push_back(_min);
            max_b.push_back(_max);
        }
    eoRealVectorBounds bounds(min_b, max_b);

    //Inicializar operador de cruce SBX
    individuoCruza crossover(bounds, Nc);

    //Cargar cantidad nodos anclas al operador
    crossover.setNoAnclas(NoAnclas);

/** MUTACION **/
    //Subclase de mutacion paper IEEE
    individuoMutacion mutationA(NoAnclas,numberGeneration,nodos,_min,_max);

    //Mutacion incluida en EO, permite llegar mas rapido a un fitness de 600
    individuoMutacion0 mutationB;

    //Combina operadores de mutacion con su respectivo peso
    eoPropCombinedMonOp<Individuo> mutation(mutationA,Pmutation1);
    mutation.add(mutationB, Pmutation2);

//Define un objeto de encapsulaci�n (it contains, the crossover, the crossover rate, the mutation and the mutation rate) -> 1 line
    eoSGATransform<Individuo> encapsulacion(crossover, Pcruza, mutation, Pmutation); //0.87

//Define el m�todo de selecci�n, selecciona un individuo por cada torneo (en el parentesis se define el tama�o del torneo)
    eoDetTournamentSelect<Individuo> torneo(sizeTorneo);

//Define un "eoSelectPerc" con el torneo como parametro por defecto (permite seleccionar el mejor individuo)
    eoSelectPerc<Individuo> seleccion(torneo);

//Define una estrategia de reemplazo por cada generaci�n
    //eoGenerationalReplacement<Individuo> reemplazo;

////Otra estrategia de reemplazo con elitismo
    eoElitism<Individuo> reemplazo(sizeElist,false); //antes 0.6

   //Para utilizar eoElitism se define un eoDetTournamentTruncate para seleccionar los individuos para el elitismo
        eoDetTournamentTruncate<Individuo> Trunca(sizeTorneo1);// antes 2

//Define una poblacion de Individuos
    eoPop<Individuo> poblacion;

//Cargar la matriz de distancias, cantidad nodos anclas y total de nodos
    Fitness.guardarDisReal(DisReal, NoAnclas, nodos, radio);

//Cargar posiciones nodos anclas
    Fitness.guardarAnclas(vecAnclas);

//Llena la poblaci�n y evalua cada cromosoma
    for(int i=0 ; i<POP_SIZE ; i++)
    {
        random(cromosoma);
        Fitness(cromosoma);
        poblacion.push_back(cromosoma);
    }

//Imprime la poblaci�n
    //poblacion.printOn(std::cout);

//Imprime un salto de linea
    std::cout<< std::endl;

//Contenedor de clases
    eoCheckPoint<Individuo> PuntoChequeo(parada);

//Cargar el valor de la generacion actual al operador de mutaci�n
    //Se inicializa el contador de generaciones
    eoIncrementorParam<unsigned> generationCounter("Gen.");
    //Se carga el contador de generaciones al operador de mutaci�n
    mutationA.setGen(& generationCounter);
    //Se carga el contador de generaciones al objeto eoCheckpoint para contar el n�mero de generaciones
    PuntoChequeo.add(generationCounter);


/** Guardar datos de la poblaci�n en archivos **/
    //Genera un archivo para guardar parametros
    eoState estado;
    //Guardar todo lo que necesites a la clase hija estado
    estado.registerObject(poblacion);
    //estado.registerObject(parser);
    //Guarda el tiempo de ejecucion desde la primera generacion
    eoTimeCounter time;
    PuntoChequeo.add(time);
    //Define cada cuantas generaciones se guarda la poblacion
    eoCountedStateSaver GuardarEstado(setGeneracion,estado,"generacion");
    //Siempre se debe agregar a la clase hija de eoCheckPoint para que se ejecute en cada generacion
    PuntoChequeo.add(GuardarEstado);

//Guardar algunas estadisticas de la poblacion
    //Muestra el mejor fitness de cada generaci�n
    eoBestFitnessStat<Individuo> Elmejor("Mejor Fitness");
    //La media y stdev
    eoSecondMomentStats<Individuo> SegundoStat;
    //Se agrega al eoCheckPoint
    PuntoChequeo.add(Elmejor);
    PuntoChequeo.add(SegundoStat);
    // Guarda los parametros a un archivo
    eoFileMonitor fileMonitor("stats.xg", " ");
    PuntoChequeo.add(fileMonitor);
    fileMonitor.add(generationCounter); //Numero de generaciones
    fileMonitor.add(time);              //Tiempo total de ejecucion desde la primera generacion
    fileMonitor.add(Elmejor);           //Mejor fitness
    fileMonitor.add(SegundoStat);       //Media y desviacion estandar

///** Grafica **/
//    eoFileMonitor fileMonitor1(InPut, " ");
//    fileMonitor1.add(Elmejor);           //Mejor fitness
//    fileMonitor1.add(SegundoStat);       //Media y desviacion estandar
//    PuntoChequeo.add(fileMonitor1);      //Agrega al checkpoint
//    GnuplotMonitor grafica(InPut,graficaGnuplot);       //Grafica el fitness y la media
//    grafica.setGen(& generationCounter); //Carga la generacion
//    PuntoChequeo.add(grafica);
///**------------------------------------------**/

// Incializa el algoritmo genetico secuencial
    eoEasyEA<Individuo> algoritmo(PuntoChequeo, Fitness, seleccion, encapsulacion, reemplazo, Trunca);

//Tiempo inicial
    gettimeofday(&ti, NULL);

//Corre el algoritmo en la poblacion inicializada
    algoritmo(poblacion);

//Tiempo Final
    gettimeofday(&tf, NULL);

    std::cout << std::endl;

//Imprime el mejor cromosoma
    poblacion.best_element().printOn(std::cout);

    std::cout << std::endl;
    std::cout << std::endl;

//Imprime el tiempo de ejecuci�n del algoritmo
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;

    std::cout <<"Tiempo de ejecucion en milisegundos: " << tiempo << std::endl;

    std::cout << std::endl;
//Se grafica el error y todos los nodos
    //std::string filename="generacion";
    //graphError error(filename, setGeneracion, numberGeneration, nodos, NoAnclas, _max);

  std::cout << std::endl;
  return EXIT_SUCCESS;


}
