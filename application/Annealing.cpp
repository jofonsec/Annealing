#include <eo>
#include <ga.h>
#include <Individuo.h>
#include <IndiInit.h>
#include <escenario.h>
#include <sys/time.h>

// Funcion de Fitness
#include <localizacionEvalPenal.h>
#include <eval/moFullEvalByModif.h>
#include <eval/moFullEvalByCopy.h>

//Vecinos y vecindario
#include <problems/permutation/moSwapNeighbor.h>
//#include <problems/permutation/moSwapNeighborhood.h>
#include <moSwapNeighborhood.h>

#include <problems/permutation/moShiftNeighbor.h>
#include <neighborhood/moRndWithReplNeighborhood.h>

//Componentes del algoritmo
#include <coolingSchedule/moCoolingSchedule.h>

//Algoritmo
#include <algo/moSA.h>

//comparador
#include <comparator/moSolNeighborComparator.h>

//continuators
#include <continuator/moTrueContinuator.h>
#include <continuator/moCheckpoint.h>
#include <continuator/moFitnessStat.h>
#include <utils/eoFileMonitor.h>
#include <continuator/moCounterMonitorSaver.h>

typedef moSwapNeighbor<Individuo> swapNeighbor ; //swap Neighbor
typedef moSwapNeighborhood<Individuo> swapNeighborhood; //classical swap Neighborhood

typedef moShiftNeighbor<Individuo> shiftNeighbor; //shift Neighbor
typedef moRndWithReplNeighborhood<shiftNeighbor> rndShiftNeighborhood; //rnd shift Neighborhood (Indexed)


int main (int argc, char* argv[]){

//Primero se debe definir un parser que lee desde la linea de comandos o un archivo
    eoParser parser(argc, argv);

//Se definen los parametros, se leen desde el parser y le asigna el valor
    unsigned seed = parser.createParam(unsigned(time(0)), "Semilla", "semilla de numeros aleatorios", 'G').value();
    //Datos necesarios del escenario de prueba
    double _min = parser.createParam((double)(0.0), "ValorMinimo", "Delimitacion area de trabajo",'M',"Parametros Escenario").value();
    double _max = parser.createParam((double)(200.0), "ValorMaximo", "Delimitacion area de trabajo",'S',"Parametros Escenario").value();
    unsigned int NoAnclas = parser.createParam((unsigned int)(20), "Anclas", "Numero de nodos anclas",'A',"Parametros Escenario").value();
    unsigned int nodos = parser.createParam((unsigned int)(120), "Nodos", "Total de nodos",'N',"Parametros Escenario").value();
    double radio = parser.createParam((double)(40), "Radio", "Radio de comunicacion",'R',"Parametros Escenario").value();

    double DisReal[500][500];
    double vecAnclas[NoAnclas*2];

//Configuracion parametros algoritmo
    unsigned int POP_SIZE = parser.createParam((unsigned int)(100), "PopSize", "Tamano de la poblacion",'P',"Parametros Algoritmo").value();
    unsigned int numberGeneration = parser.createParam((unsigned int)(10000), "MaxGen", "Criterio de parada, Numero maximo de generaciones",'G',"Parametros Algoritmo").value();
    unsigned int Nc = parser.createParam((unsigned int)(2), "Nc", "Constante del operador SBX",'C',"Parametros Algoritmo").value();
    double Alpha = parser.createParam((double)(0.5), "Alpha", "Constante del operador Aritmetico AX",'C',"Parametros Algoritmo").value();
    float preferencia = parser.createParam((float)(0.5), "Preferencia", "Constante del operador Uniforme, define el sesgo",'C',"Parametros Algoritmo").value();
    double epsilon = parser.createParam((double)(5), "Epsilon", "Rango de mutación",'F',"Parametros Algoritmo").value();
    double P_change = parser.createParam((double)(0.79), "P_cambio", "Probabilidad de que mute el gen",'E',"Parametros Algoritmo").value();
    double PmutationA = parser.createParam((double)(0.87), "P-SVN", "Probabilidad de mutacion SVN",'X',"Parametros Algoritmo").value();
    double PmutationB = parser.createParam((double)(0.85), "P-SWAP", "Probabilidad de mutacion SWAP",'Y',"Parametros Algoritmo").value();
    double PmutationC = parser.createParam((double)(0.85), "P-UM", "Probabilidad de mutacion de UM",'Z',"Parametros Algoritmo").value();
    double PmutationT = parser.createParam((double)(0.5), "P-TotalM", "Probabilidad de mutacion del encapsulamiento",'W',"Parametros Algoritmo").value();
    double PcruzaA = parser.createParam((double)(0.5), "P-SBX", "Probabilidad de cruzamiento operador SBX",'H',"Parametros Algoritmo").value();
    double PcruzaB = parser.createParam((double)(0.5), "P-AX", "Probabilidad de cruzamiento operador AX",'J',"Parametros Algoritmo").value();
    double PcruzaC = parser.createParam((double)(0.5), "P-UX", "Probabilidad de cruzamiento operador UX",'I',"Parametros Algoritmo").value();
    double PcruzaT = parser.createParam((double)(0.5), "P-TotalC", "Probabilidad de cruzamiento del encapsulamiento",'B',"Parametros Algoritmo").value();
    double sizeTorneo = parser.createParam((double)(8), "SizeTorneo", "Tamano del torneo para seleccion de individuos",'L',"Parametros Algoritmo").value();
    double sizeElist = parser.createParam((double)(2), "SizeElist", "Cantidad de individuos que se conservan",'B',"Parametros Algoritmo").value();
    double sizeTorneo1 = parser.createParam((double)(2), "SizeTorneo1", "Tamano del torneo para seleccion de individuos del elitismo",'Q',"Parametros Algoritmo").value();

//Parametros de guardado
    unsigned int setGeneracion = parser.createParam((unsigned int)(100), "setGeneracion", "Cada cuantas generaciones se guarda la poblacion",'T',"Guardar Datos").value();
    unsigned int setTime = parser.createParam((unsigned int)(0), "setTime", "Cada cuantos segundos se guarda la configuracion",'I',"Guardar Datos").value();

//Grafica
    std::string InPut = parser.createParam(std::string("Estadistica.txt"), "Input", "Archivo que contiene el Fitness, Media, DevStand",'o',"Salida - Grafica").value();
    bool graficaGnuplot = parser.createParam((bool)(0), "Gnuplot", "Grafica el Fitness y Media, 0 desactivado y 1 activado",'g',"Salida - Grafica").value();

// El nombre del archivo status donde todos los parametros seran guardados
    std::string str_status = parser.ProgramName() + ".status"; // default value
    std::string statusName = parser.createParam(str_status, "status","Status file",'S', "Persistence" ).value();

    std::string loadName = parser.createParam(std::string(""), "Carga","Se restaura desde un archivo guardado",'L', "Persistence" ).value();

//Termina la ejecucion al consultar la ayuda
    if (parser.userNeedsHelp()){
        parser.printHelp(std::cout);
        exit(1);
         }

    if (statusName != ""){
        std::ofstream os(statusName.c_str());
        os << parser;	// and you can use that file as parameter file
         }

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

//Define la representacion (Individuo)
    Individuo solucion;

//Generar una subclase de la clase de la funcion de evaluacion
    localizacionEvalPenal Fitness;

//Cargar la matriz de distancias, cantidad nodos anclas y total de nodos
    Fitness.guardarDisReal(DisReal, NoAnclas, nodos, radio);

//Cargar posiciones nodos anclas
    Fitness.guardarAnclas(vecAnclas);

// Operador de evaluacion para una solucion vecina
    moFullEvalByCopy<swapNeighbor> swapEval(Fitness);

    moFullEvalByCopy<shiftNeighbor> shiftEval(Fitness);

//Vecinos y vecindario
    swapNeighborhood swapNH;

    rndShiftNeighborhood rndShiftNH((nodos*2-1) * (nodos*2-1));

//Tasa de enfriamiento (Temperatura inicial, factor decrecimiento, numero de pasos sin decrecimiento, Temperatura final)
    moSimpleCoolingSchedule<Individuo> coolingSchedule(10000, 0.88, 100000, 0.01);

//Comparador de Vecinos
    moSolNeighborComparator<swapNeighbor> solComparator;

//Imprime un salto de linea
    std::cout<< std::endl;

//Para la inicializaci�n del solucion, primero se debe definir como se generaran los genes y la semilla
    rng.reseed(seed);
//Se utilizara un generador uniforme, (valor min, valor max)
    eoUniformGenerator<double> uGen(_min, _max);
//Crear el inicializador para los solucions, llamado random
    IndiInit random(nodos*2,uGen);
    random(solucion);
    Fitness(solucion);

//Solucion inicial
    std::cout << "Solucion Inicial:" << std::endl;
    std::cout << solucion << std::endl << std::endl;

//Uso del vecino y vecindario SWAP
    // std::cout << "SWAP NEIGHBORHOOD" << std::endl;
    // std::cout << "-----------------" << std::endl;
    // std::cout << "Neighbors List: (Neighbor -> fitness)" << std::endl;
    //
    // swapNeighbor n1;
    // swapNH.init(solucion, n1);
    // swapEval(solucion,n1);
    // n1.print();
    // while (swapNH.cont(solucion)) {
    //     swapNH.next(solucion, n1);
    //     swapEval(solucion,n1);
    //     n1.print();
    // }

//Checkpointing
    moTrueContinuator<swapNeighbor> continuator;//always continue
    moCheckpoint<swapNeighbor> checkpoint(continuator);
    moFitnessStat<Individuo> fitStat;
    checkpoint.add(fitStat);
    eoFileMonitor monitor("fitness.out", "");
    moCounterMonitorSaver countMon(100, monitor);
    checkpoint.add(countMon);
    monitor.add(fitStat);


// Incializa el algoritmo Simulated Annealing
    moSA<swapNeighbor> RecocidoSimulado(swapNH, Fitness, swapEval, coolingSchedule, solComparator, checkpoint);
    //moSA<shiftNeighbor> local(rndShiftNH, Fitness, shiftEval);

//Tiempo inicial
    gettimeofday(&ti, NULL);

//Corre el algoritmo en la poblacion inicializada
    RecocidoSimulado(solucion);
    //local(solucion);

//Tiempo Final
    gettimeofday(&tf, NULL);

    std::cout << std::endl;

    std::cout << "Solucion Final: " << solucion << std::endl ;
    std::cout << "#########################################" << std::endl;

//Imprime el mejor solucion
    //poblacion.best_element().printOn(std::cout);

    std::cout << std::endl;
    std::cout << std::endl;

//Imprime el tiempo de ejecuci�n del algoritmo
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;

    std::cout <<"Tiempo de ejecucion en milisegundos: " << tiempo << std::endl;
    std::cout <<"Tiempo de ejecucion en segundos: " << tiempo/1000.0 << std::endl;
    std::cout <<"Tiempo de ejecucion en minutos: " << (tiempo/1000.0)/60 << std::endl;

    std::cout << std::endl;
//Se grafica el error y todos los nodos
    //std::string filename="generacion";
    //graphError error(filename, setGeneracion, numberGeneration, nodos, NoAnclas, _max);

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
