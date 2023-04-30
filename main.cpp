#include <iostream>
#include <time.h>
#ifdef __linux__
    #include "GeneticAlgorithm.h"
    #include "SuperMatrix.h"
    #include "SuperVector.h"
    #include "Problem.h"
#else
    #include <GeneticAlgorithm.h>
    #include <SuperMatrix.h>
    #include <SuperVector.h>
    #include <Problem.h>
    #include <Windows.h>
#endif


#define POP_SIZE 30
#define DEFAULT_ORIGEM 2
#define MAX_GERATIONS 60

//#define DebugPrint(x) cout<<x<<endl
#define DebugPrint(x)

#ifdef __linux__
    #define MINE_TRUCKS_PATH "./MINE_PATHS.txt"
    #define MINE_PATH "./"
#else// windows

    #define MINE_TRUCKS_PATH "d:\\MINE_PATHS.txt"
    #define MINE_PATH "d:\\"

#endif // __linux__

#define THIS_TRUCK 0

GeneticAlgorithm truck(MINE_TRUCKS_PATH);
Problem minaDinamica;

using namespace std;


int main(int argc,  char** argv)
{
try{
    const clock_t begin_time = clock();
    uint16_t gerations=0,i;
    uint8_t origem = DEFAULT_ORIGEM;
    individuo_t result;
    minaDinamica.curTruck = THIS_TRUCK;

    //cout<<" argCount = "<<argc<<endl;
    if(argc < 3) //0 é o caminho do exe
    {
        cout<<"Numero de parametros insuficiente, passe como parametro:"<<endl;
        cout<<"  \"Indice do caminhao\" \"indice da posicao atual\""<<endl;
        cout<<"n de paramentrs "<<(int)argc<<endl;
        return (6);
    }
    else
    {
        minaDinamica.curTruck = atoi(argv[1]);
        //cout<<" Truck ID = "<<atoi(argv[1])<<endl;
        origem = atoi(argv[2]);
        //cout<<" Pos ID = "<<atoi(argv[2])<<endl;
    }

    DebugPrint((int)origem <<" "<<(int)minaDinamica.curTruck);




    minaDinamica.begin(MINE_PATH);
    truck.Problema = minaDinamica;

    DebugPrint("Criando");
    //create a new population
    truck.CreatePopulation(POP_SIZE,origem);

    DebugPrint("Criado");


    //evolve the population
    for(gerations=0;gerations<MAX_GERATIONS;gerations++)
    {
        truck.Evolve();
    }

//    for(int i=0;i<truck.population.size();i++)
//    {
//        cout<<(int)i<<" ";
//        truck.population[i]->printBackward();
//        cout<<" { ";
//        cout<< minaDinamica.mainFunction(truck.population[i]);
//        cout<<" }\n\n ";
//    }

    //system("CLS");
    //get the best

    result= truck.theBest();

    minaDinamica.mainFunction(result,false);

    result->printBackward();



    //std::cout<<endl <<"{"<< float( clock () - begin_time )*1000.0 /  CLOCKS_PER_SEC<<"ms}";
    std::cout <<"{"<< (float( clock () - begin_time )*1000.0 /  CLOCKS_PER_SEC)<<"ms}";

}catch (const std::exception& e) { // reference to the base of a polymorphic object
     std::cout <<"ERROR: "<< e.what();

}

return 0;
}


