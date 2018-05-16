#include "findPath.h"

using namespace std;

FindPath::FindPath (UndirectedGraph g, boost::ptr_vector<AllEdgePath> pathStore, vector<string> vecStrEdge, vector<string> vecVertices, desc2strMap descIndexVertices, Vertex start, Vertex end) {
    
    this->g = g;
    this->pathStore = pathStore;
    this->descIndexVertices = descIndexVertices;
    this->vecStrEdge = vecStrEdge;
    this->vecVertices = vecVertices;
    this->Ename = get(boost::edge_index, g);
    //index = get(boost::vertex_index, g);
    this->start = start;
    this->end = end;
}

void FindPath::pathFindDup() {
    unordered_set<Vertex> visitedNode;
    this->pathFindingDup(start, to_string(start), "", visitedNode);
    string in_path;
    //unordered_set<string> result;
    for (size_t k = 0; k < vertexRes.size(); k++){
        in_path = vertexRes[k];
        std::vector<std::string> m_currentPath;  
        boost::algorithm::split(m_currentPath, in_path, boost::algorithm::is_any_of(">"));  
        for(size_t i = 0; i < m_currentPath.size(); i++)  
        {  
            //cout << "vertexRes" << m_currentPath[i] << endl;
            result.insert(vecVertices[stoi(m_currentPath[i])]);  
        }  
    }
    for (size_t k = 0; k < edgeRes.size(); k++){
        in_path = edgeRes[k];
        std::vector<std::string> m_currentPath;  
        boost::algorithm::split(m_currentPath, in_path, boost::algorithm::is_any_of(">"));  
        for(size_t i = 1; i < m_currentPath.size(); i++)  
        {  
            //cout << "edgeRes" << m_currentPath[i] << endl;
            result.insert(vecStrEdge[stoi(m_currentPath[i])]);  
        }  
    }
    cout << "Output: " << endl;
    for(auto itr = result.begin(); itr != result.end(); ++itr){
        cout << (*itr) << endl;
    }
}

void FindPath::pathFindNoDup() {
    unordered_set<Vertex> visitedNode;
    VertexEdgePath tmpVertexEdgePath = this->pathFindingNoDup(start, visitedNode);
    cout << tmpVertexEdgePath.first << endl;

}

void FindPath::pathFindingDup (Vertex start, string currentVertexPath, string currentEdgePath, unordered_set<Vertex> visitedNode){
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;
    //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname = get(boost::vertex_name, g);

    visitedNode.insert(start);
    
    for (tie(out_i, out_end) = out_edges(start, g); out_i != out_end; ++out_i) 
    { 
        e = *out_i;
        Vertex src = source(e, g), targ = target(e, g);
        if(visitedNode.find(targ) != visitedNode.end()) {continue;}        
        //string tempPath = currentPath + ">" + vecStrEdge[Ename[*out_i]] + ">" + descIndexVertices[targ];
        string tempVertexPath = currentVertexPath + ">" + to_string(targ);
        cout << "Current path: " << tempVertexPath << endl;
        string tempEdgePath = currentEdgePath + ">" + to_string(Ename[*out_i]);
        if(targ == end) {
            vertexRes.push_back(tempVertexPath);
            cout << "Find one path: " << tempVertexPath << endl;
            edgeRes.push_back(tempEdgePath);
            return;
        }
        this->pathFindingDup(targ, tempVertexPath, tempEdgePath, visitedNode);
    }
}

VertexEdgePath FindPath::pathFindingNoDup (Vertex start, unordered_set<Vertex> visitedNode) {
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;
    //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname = get(boost::vertex_name, g);

    visitedNode.insert(start);
    if (start == end) return VertexEdgePath(to_string(start), to_string(Ename[*out_i]));
    string tempVertexPath = "", tempEdgePath = "";
    
    for (tie(out_i, out_end) = out_edges(start, g); out_i != out_end; ++out_i) 
    { 
        e = *out_i;
        //Vertex src = source(e, g), targ = target(e, g);
        Vertex targ = target(e, g);
        if (visitedNode.find(targ) != visitedNode.end()) {continue;}

        if (pathStore[start][targ].first != "null") {
            tempVertexPath += ">" + pathStore[start][targ].first;
            tempEdgePath += ">" + pathStore[start][targ].second;
        }
        else {
            VertexEdgePath tmpVertexEdgePath = this->pathFindingNoDup(targ, visitedNode);
            pathStore[start][targ].first = tmpVertexEdgePath.first;
            pathStore[start][targ].second = tmpVertexEdgePath.second;
            tempVertexPath += ">" + pathStore[start][targ].first;
            tempEdgePath += ">" + pathStore[start][targ].second;

        }
    }
    return VertexEdgePath(tempVertexPath, tempEdgePath);
}

bool FindPath::checkResult (string expectedFile) {
    unordered_set<string> expectedRes;
    string s;
    ifstream fileStream(expectedFile);
    while (getline(fileStream, s)) {
        //cout << s << endl;
        s.erase(remove(s.begin(), s.end(), '\r'), s.end());
        expectedRes.insert(s);
    }
    if (expectedRes == result) return true;
    else return false;
}

// FindPath::~FindPath() {

// }


