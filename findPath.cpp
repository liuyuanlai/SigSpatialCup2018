#include "findPath.h"

// class FindPath{

// public:
//     void pathFinding(Vertex start, Vertex end, UndirectedGraph g, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res){
//         //unordered_set<Vertex> visitedNode;
//         typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
//         typedef boost::graph_traits<UndirectedGraph> GraphTraits;
//         typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type IndexMap;
//         typename GraphTraits::out_edge_iterator out_i, out_end;
//         typename GraphTraits::edge_descriptor e;

//         boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname = get(boost::vertex_name_t(), g);
//         boost::property_map<UndirectedGraph, boost::edge_name_t>::type Ename = get(boost::edge_name, g);
//         IndexMap index = get(boost::vertex_index, g);
//         visitedNode.insert(start);
//         for (tie(out_i, out_end) = out_edges(start, g);out_i != out_end; ++out_i) 
//         { 
//             e = *out_i;
//             Vertex src = source(e, g), targ = target(e, g);
//             if(visitedNode.find(targ) != visitedNode.end()) {continue;}
//             //string tempPath = currentPath + "->" + to_string(index[targ]); //name[targ];
//             string tempPath = currentPath + ">" + Ename[*out_i] + ">" + Vname[targ];
//             //cout << tempPath << endl;
//             if(index[targ] == index[end]) {
//                 res.push_back(tempPath);
//                 //cout << tempPath << endl;
//             }
//             pathFinding(targ, end, g, tempPath, visitedNode, res);
//         }
//     }
// };

using namespace std;

FindPath::FindPath (UndirectedGraph g) {
    //Vname = get(boost::vertex_name, g);
    // for(int i = 0; i < 17; i++) {
    //     Vertex node = vertex(i, g);
    //     cout << "node" + to_string(i) + ": " << Vname[node] << endl;
    // }
    Ename = get(boost::edge_name, g);
    index = get(boost::vertex_index, g);
    Vname = get(boost::vertex_name, g);
}

FindPath::~FindPath() {

}

void FindPath::pathFinding(Vertex start, Vertex end, UndirectedGraph g, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res){
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;
    boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname_1 = get(boost::vertex_name, g);
    for(int i = 0; i < 17; i++) {
        Vertex node = vertex(i, g);
        if (Vname[node] != Vname_1[node]) {
            cout << "vname:node" + to_string(i) + ": " << Vname[node] << endl;
            cout << "vname_1:node" + to_string(i) + ": " << Vname_1[node] << endl;
        }
    }
    //Vname = get(boost::vertex_name, g);
    //boost::property_map<UndirectedGraph, boost::edge_name_t>::type Ename = get(boost::edge_name, g);
    //IndexMap index = get(boost::vertex_index, g);
    visitedNode.insert(start);
    
    for (tie(out_i, out_end) = out_edges(start, g); out_i != out_end; ++out_i) 
    { 
        e = *out_i;
        Vertex src = source(e, g), targ = target(e, g);
        cout << Vname[targ] << endl;
        if(visitedNode.find(targ) != visitedNode.end()) {continue;}
        //string tempPath = currentPath + "->" + to_string(index[targ]); //name[targ];
        string tempPath = currentPath + ">" + Ename[*out_i] + ">" + Vname[targ];
        //cout << Vname[targ] << endl;
        //cout << tempPath << endl;
        if(index[targ] == index[end]) {
            res.push_back(tempPath);
            //cout << tempPath << endl;
        }
        pathFinding(targ, end, g, tempPath, visitedNode, res);
    }
}



