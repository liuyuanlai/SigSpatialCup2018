#include "findPath.h"
#include <stack>
using namespace std;

FindPath::FindPath (UndirectedGraph g, boost::ptr_vector<AllEdgePath> pathStore, vector<string> vecStrEdge, vector<string> vecVertices, Desc2StrMap descIndexVertices) {
    
    this->g = g;
    this->pathStore = pathStore;
    this->descIndexVertices = descIndexVertices;
    this->vecStrEdge = vecStrEdge;
    this->vecVertices = vecVertices;
    this->Ename = get(boost::edge_index, g);
    //index = get(boost::vertex_index, g);
}

void FindPath::pathFindDup(Vertex start, Vertex end) {
    this->start = start;
    this->end = end;
    unordered_set<Vertex> visitedNode;
    this->pathFindingDup(this->start, to_string(this->start), "", visitedNode);
    string in_path;
    //unordered_set<string> result;
    for (size_t k = 0; k < vertexRes.size(); k++){
        in_path = vertexRes[k];
        vector<string> m_currentPath;  
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

void FindPath::pathFindNoDup(Vertex start, Vertex end) {
    this->start = start;
    this->end = end;
    unordered_set<Vertex> visitedNode;
    VertexEdgePath tmpVertexEdgePath = this->pathFindingNoDupIterative(this->start, visitedNode);
    //VertexEdgePath tmpVertexEdgePath = this->pathFindingNoDup(this->start, visitedNode);
    // for (int v = 0; v < vecVertices.size(); v++) {
    //     typename GraphTraits::out_edge_iterator out_i, out_end;
    //     typename GraphTraits::edge_descriptor e;
    //     for (tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
    //         e = *out_i;
    //         Vertex targ = target(e, g);
    //         cout << v << ">" << targ << ": " << pathStore[v][targ].second << endl;
    //     } 

    // }
    // cout << tmpVertexEdgePath.first << endl;
    // cout << tmpVertexEdgePath.second << endl;
    vector<string> vecPath;  
    boost::algorithm::split(vecPath, tmpVertexEdgePath.first, boost::algorithm::is_any_of(">"));  
    for(size_t i = 0; i < vecPath.size()-1; i++)  
    {  
        result.insert(vecVertices[stoi(vecPath[i])]);  
    }
    boost::algorithm::split(vecPath, tmpVertexEdgePath.second, boost::algorithm::is_any_of(">"));  
    for(size_t i = 0; i < vecPath.size() - 1; i++)  
    {  
        //cout << "edgeRes" << m_currentPath[i] << endl;
        result.insert(vecStrEdge[stoi(vecPath[i])]);  
    } 

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

VertexEdgePath FindPath::pathFindingNoDupIterative(Vertex start, unordered_set<Vertex> visitedNode){
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;
    unordered_set<Vertex> analyzedNode;
    stack<Vertex> node;
    tempPath path;
    Vertex cur = start;
    Vertex tem;
    bool next = false;
    bool begin = true;
    while(!node.empty() || begin == true){
        begin = false;
        while(true){
            //cout << "analysis node: " << cur << endl;
            next = false;
            if(analyzedNode.find(cur) != analyzedNode.end()) break;
            visitedNode.insert(cur);
            analyzedNode.insert(cur);
            tie(out_i, out_end) = out_edges(cur, g);
            while(out_i != out_end){
                e = *out_i;
                Vertex targ = target(e, g);
                if (visitedNode.find(targ) != visitedNode.end() || pathStore[cur][targ].first != "null") {out_i++;continue;}
                if(next == false) {tem = targ; next = true;}
                else {
                    node.push(targ);
                    //cout << "push neighbor" << targ << endl;
                }
                out_i++;
            }
            node.push(cur);
            //cout << "push node" << cur << endl;
            if(!next) break;
            cur = tem;
            if(cur == end) {node.push(cur); visitedNode.insert(cur); analyzedNode.insert(cur); break;}
        }
         
        cur = node.top();
        node.pop();
        //cout << "pop " << cur << endl;
        bool isEnd = true;
        tie(out_i, out_end) = out_edges(cur, g);
        while(!node.empty() && out_i != out_end){
            e = *out_i;
            Vertex targ = target(e, g);
            if(node.top() == targ && analyzedNode.find(targ) == analyzedNode.end()){
                Vertex tem1 = node.top();
                node.pop();
                //cout << "pop" << tem1 << endl;
                node.push(cur);
                //cout << "push back" << cur << endl;
                cur = tem1;
                isEnd = false;
                break;
            }
            out_i++;
        }
    
        if(isEnd){
            //cout << "store path of : " << cur << endl;
            if(cur == end) {path[cur] = VertexEdgePath(to_string(cur) + ">", ""); Vertex temp = node.top(); pathStore[temp][cur].first = path[cur].first; pathStore[temp][cur].second = path[cur].second; cur = node.top(); continue;}
            string tempVertexPath = "", tempEdgePath = "";
            tie(out_i, out_end) = out_edges(cur, g);
            while(out_i != out_end){
                e = *out_i;
                Vertex targ = target(e, g);
                if (pathStore[cur][targ].first != "null" && (node.empty() || node.top() != targ)) {
                    if (pathStore[cur][targ].first != "dead") {
                        tempVertexPath += to_string(cur) + ">" + pathStore[cur][targ].first;
                        tempEdgePath += to_string(Ename[e]) + ">" + pathStore[cur][targ].second;
                        //cout << cur << "to " << targ << "is " << pathStore[cur][targ].first;
                    }    
                }
                out_i++;
            }
            visitedNode.erase(cur); analyzedNode.erase(cur);
            if (tempVertexPath == "") {path[cur] = VertexEdgePath("dead", "dead");}
            else path[cur] = VertexEdgePath(tempVertexPath, tempEdgePath);
            //cout << cur << "path is : " << path[cur].first << endl;
            if(!node.empty()) {Vertex temp = node.top(); pathStore[temp][cur].first = path[cur].first; pathStore[temp][cur].second = path[cur].second; cur = node.top();}
        }
    }
    //cout << "Path is : " << path[start].first << endl;
    return path[start];
}

VertexEdgePath FindPath::pathFindingNoDup (Vertex start, unordered_set<Vertex> visitedNode) {
    typename GraphTraits::out_edge_iterator out_i, out_end;
    typename GraphTraits::edge_descriptor e;

    visitedNode.insert(start);
    if (start == end) return VertexEdgePath(to_string(start) + ">", "");
    string tempVertexPath = "", tempEdgePath = "";
    
    for (tie(out_i, out_end) = out_edges(start, g); out_i != out_end; ++out_i) 
    { 
        e = *out_i;
        Vertex targ = target(e, g);

        if (visitedNode.find(targ) != visitedNode.end()) {continue;}

        if (pathStore[start][targ].first == "null") {
            VertexEdgePath tmpVertexEdgePath = this->pathFindingNoDup(targ, visitedNode);
            pathStore[start][targ].first = tmpVertexEdgePath.first;
            pathStore[start][targ].second = tmpVertexEdgePath.second;
            if (tmpVertexEdgePath.first != "dead") {
                tempVertexPath += to_string(start) + ">" + pathStore[start][targ].first;

                pathStore[start][targ].second = to_string(Ename[e]) + ">" + pathStore[start][targ].second;
                tempEdgePath += pathStore[start][targ].second;
            }
            
        }
        else if (pathStore[start][targ].first == "dead") {continue;}
        else {
            tempVertexPath += to_string(start) + ">" + pathStore[start][targ].first;
            tempEdgePath += pathStore[start][targ].second;
        }
    }
    if (tempVertexPath == "") return VertexEdgePath("dead", "dead");
    else return VertexEdgePath(tempVertexPath, tempEdgePath);
}

void FindPath::checkResult (string expectedFile) {
    unordered_set<string> expectedRes;
    string s;
    ifstream fileStream(expectedFile);
    while (getline(fileStream, s)) {
        //cout << s << endl;
        s.erase(remove(s.begin(), s.end(), '\r'), s.end());
        expectedRes.insert(s);
    }
    //for(const auto& elem: result) cout << elem << endl;
    if (expectedRes == result) cout << "Result check passed..." << endl;
    else cout << "Result check didn't pass..." << endl;
}

// FindPath::~FindPath() {

// }


