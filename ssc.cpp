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
    BuildGraph buildGraph = BuildGraph(filepath);

    UndirectedGraph g = buildGraph.g;


    Vertex start = vertex(13, g);
    Vertex end = vertex(2, g);
    vector<string> vec;
    unordered_set<Vertex> visitedNode; 

    //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type name = get(boost::vertex_name, g);

    FindPath path(g, buildGraph.descIndexVertices, start, end);

    clock_t start_t = clock();
    path.pathFinding(start, buildGraph.descIndexVertices[start], visitedNode, vec);

    clock_t end_t = clock();
    cout << "execution time: " << (double) (end_t-start_t)/CLOCKS_PER_SEC << endl;
    string in_path;
    unordered_set<string> result;
    for (size_t k = 0; k < vec.size(); k++){
        in_path = vec[k];
        std::vector<std::string> m_currentPath;  
        boost::algorithm::split(m_currentPath, in_path, boost::algorithm::is_any_of(">"));  
        for(size_t i = 0; i<m_currentPath.size(); i++)  
        {  
            result.insert(m_currentPath[i]);  
        }  
    }
    cout << "Output: " << endl;
    for(auto itr = result.begin(); itr != result.end(); ++itr){
        cout << (*itr) << endl;
    }



	//vector<string> :: iterator itr;
    //cout << "Original nodes ID:\n";
    //for (itr = vecVertices.begin(); itr != vecVertices.end(); itr++)
    //    cout << (*itr) << endl;

    
    //IndexMap index = get(boost::vertex_index, g);

    //typedef boost::graph_traits<UndirectedGraph>::vertex_iterator vertex_iter;
    //std::pair<vertex_iter, vertex_iter> vp;
    //cout << "Vertices in the graph = ";
    //for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    //        std::cout << index[*vp.first] << " ";
    //std::cout << std::endl;

    //std::cout << "edges(g) = ";
    //boost::graph_traits<UndirectedGraph>::edge_iterator ei, ei_end;
    //for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    //    std::cout << "(" << index[source(*ei, g)]<< "," << index[target(*ei, g)] << ") ";
    //std::cout << std::endl;

/*
    //boost::graph_traits<UndirectedGraph>::vertex_descriptor start, end;
    //typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
    */

}

