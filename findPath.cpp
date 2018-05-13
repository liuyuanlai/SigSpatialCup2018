#include "findPath.h"

using namespace std;

FindPath::FindPath (UndirectedGraph g, desc2strMap descIndexVertices, Vertex start, Vertex end) {
    
    this->g = g;
    this->descIndexVertices = descIndexVertices;
    Ename = get(boost::edge_name, g);
    //index = get(boost::vertex_index, g);
    this->start = start;
    this->end = end;
    // Vname = get(boost::vertex_name, g);
    // for(int i = 0; i < 17; i++) {
    //     Vertex node = vertex(i, g);
    //     cout << "node" + to_string(i) + ": " << Vname[node] << endl;
    // }
}



void FindPath::pathFinding(Vertex start, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res){
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;
    //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname = get(boost::vertex_name, g);

    visitedNode.insert(start);
    
    for (tie(out_i, out_end) = out_edges(start, g); out_i != out_end; ++out_i) 
    { 
        e = *out_i;
        //cout << "edge:" << e << endl;
        Vertex src = source(e, g), targ = target(e, g);
        //cout << Vname[targ] << endl;
        if(visitedNode.find(targ) != visitedNode.end()) {continue;}
        //string tempPath = currentPath + "->" + to_string(index[targ]); //name[targ];
        string tempPath = currentPath + ">" + Ename[*out_i] + ">" + descIndexVertices[targ];
        //cout << Vname[targ] << endl;
        //cout << tempPath << endl;
        if(targ == end) {
            res.push_back(tempPath);
            //cout << tempPath << endl;
        }
        this->pathFinding(targ, tempPath, visitedNode, res);
    }
}

// FindPath::~FindPath() {

// }


