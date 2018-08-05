#include <iostream>
#include <tuple>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

#include "findPath.h"
#include "buildGraph.h"

using namespace std;

int main(int argc, char* argv[]) {


    if (argc != 4) {
        cout << "Usage ./ssc.out [input dataset path] [starting points file path] [result path]" << endl;
        exit(1);
    }

    //string filepath = "SampleDataset1/SampleDataset1.json";
    //string outputpath = "SampleDataset1/output.txt";
    string inputpath = argv[1];
    string startPointFile = argv[2];
    string output = argv[3];
    vector<string> startpoints;
    //string inputpath = "EsriNapervilleElectricNetwork/EsriNapervilleElectricNetwork.json";
    string outputpath = "EsriNapervilleElectricNetwork/output.txt";

    clock_t start_t, end_t; 
    start_t = clock();

    BuildGraph buildGraph = BuildGraph(inputpath);

    end_t = clock();
    cout << "Build graph takes: " << (double) (end_t-start_t)/CLOCKS_PER_SEC << "s" << endl;

    cout << "Number of vertices: " << buildGraph.vecVertices.size() << endl;
    cout << "Number of edges: " << buildGraph.vecStrEdge.size() << endl;

    UndirectedGraph g = buildGraph.g;

    //string startstr = "{7FC28536-6F4A-4A9A-B439-1D87AE2D8871}";
    //string endstr = "{5F396092-90DD-4E07-8C7D-2FB8480771C1}";

    ifstream infile(startPointFile);
    string line;
    while(getline(infile, line)) {
        if(line[line.length() - 1] == '\r') line = line.substr(0, line.length() - 1);
        startpoints.push_back(line);
    }
    ofstream tofile(output);
    for (string startstr : startpoints) {
        for (auto endstr : buildGraph.controllers) {

            cout << startstr<<endl;
            //string startstr = "{42236F76-4CEE-449E-82E7-94F96ABB88C4}";
            //string endstr = "{1CAF7740-0BF4-4113-8DB2-654E18800028}";
            //string endstr = buildGraph.controllers[0];

            Vertex start = buildGraph.strIndexVertices[startstr];
            Vertex end = buildGraph.strIndexVertices[endstr];

            FindPath path(g, buildGraph.pathStore, buildGraph.vecStrEdge, buildGraph.vecVertices, buildGraph.descIndexVertices);

            start_t = clock();

            path.pathFindNoDup(start, end); //call non-duplicate pathfind algorithm
            // path.pathFindDup(start, end); //call duplicate pathfind algorithm

            end_t = clock();
            cout << "Find path takes: " << (double) (end_t-start_t)/CLOCKS_PER_SEC <<  "s" << endl;

            for (auto feature : path.result)
                tofile << feature << endl;

            path.checkResult(outputpath);
        }
    }

    //buildGraph.printEdge();
    buildGraph.pathStore.clear();
}

