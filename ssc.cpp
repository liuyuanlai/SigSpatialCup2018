#include <iostream>
#include <tuple>
#include <ctime>
#include <string>
#include <vector>

#include "findPath.h"
#include "buildGraph.h"

using namespace std;
namespace pt = boost::property_tree;

int main() {
    string filepath = "SampleDataset1/SampleDataset1.json";
    string outputpath = "SampleDataset1/output.txt";
    // string filepath = "EsriNapervilleElectricNetwork/EsriNapervilleElectricNetwork.json";
    // string outputpath = "EsriNapervilleElectricNetwork/output.txt";
    BuildGraph buildGraph = BuildGraph(filepath);

    UndirectedGraph g = buildGraph.g;

    string startstr = "{7FC28536-6F4A-4A9A-B439-1D87AE2D8871}";
    string endstr = "{5F396092-90DD-4E07-8C7D-2FB8480771C1}";

    // string startstr = "{42236F76-4CEE-449E-82E7-94F96ABB88C4}";
    // string endstr = "{1CAF7740-0BF4-4113-8DB2-654E18800028}";

    Vertex start = buildGraph.strIndexVertices[startstr];
    Vertex end = buildGraph.strIndexVertices[endstr];

    FindPath path(g, buildGraph.pathStore, buildGraph.vecStrEdge, buildGraph.vecVertices, buildGraph.descIndexVertices, start, end);

    clock_t start_t = clock();

    path.pathFindNoDup();//call pathfind algorithm

    clock_t end_t = clock();
    cout << "execution time: " << (double) (end_t-start_t)/CLOCKS_PER_SEC << endl;

    path.checkResult(outputpath);

    //buildGraph.printEdge();
    buildGraph.pathStore.clear();
}

