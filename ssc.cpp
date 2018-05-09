#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <boost/algorithm/string.hpp>
#include <tuple>
#include <ctime>
#include <string>
#include <vector>

using namespace std;
namespace pt = boost::property_tree;
typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;
typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type IndexMap;

class FindPath{
public:
    void pathFinding(Vertex start, Vertex end, UndirectedGraph g, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res){
        //unordered_set<Vertex> visitedNode;
        typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
        typedef boost::graph_traits<UndirectedGraph> GraphTraits;
        typename GraphTraits::out_edge_iterator out_i, out_end;
        typename GraphTraits::edge_descriptor e;
        boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname = get(boost::vertex_name_t(), g);
        boost::property_map<UndirectedGraph, boost::edge_name_t>::type Ename = get(boost::edge_name, g);
        IndexMap index = get(boost::vertex_index, g);
        visitedNode.insert(start);
        for (tie(out_i, out_end) = out_edges(start, g);out_i != out_end; ++out_i) 
        { 
            e = *out_i;
            Vertex src = source(e, g), targ = target(e, g);
            if(visitedNode.find(targ) != visitedNode.end()) {continue;}
            //string tempPath = currentPath + "->" + to_string(index[targ]); //name[targ];
            string tempPath = currentPath + ">" + Ename[*out_i] + ">" + Vname[targ];
            //cout << tempPath << endl;
            if(index[targ] == index[end]) {
                res.push_back(tempPath);
                //cout << tempPath << endl;
            }
            pathFinding(targ, end, g, tempPath, visitedNode, res);
        }
    }
};

int main() {
	pt::ptree root;
	//pt::read_json("SampleDataset1/EsriNapervilleElectricNetwork.json", root);
    pt::read_json("SampleDataset1/SampleDataset1.json", root);
    typedef tuple<string, string, string> Edge;
    unordered_set<Vertex> visitedNode; 
	vector<Edge> vecEdge;
	vector<string> vecVertices;
	unordered_set<string> verticesSet;
	map<string, UndirectedGraph::vertex_descriptor> indexes;
    cout << "Read file!!!!!!" << endl;
	for (pt::ptree::value_type &row : root.get_child("rows")) {
		vecEdge.push_back(Edge(row.second.get<string>("fromGlobalId"),row.second.get<string>("toGlobalId"), row.second.get<string>("viaGlobalId")));
		verticesSet.insert(row.second.get<string>("fromGlobalId"));
		verticesSet.insert(row.second.get<string>("toGlobalId"));
	}
    cout << "Insert node!!!!!!" << endl;
	int numVertices = verticesSet.size();
	UndirectedGraph g(numVertices);
	vecVertices.insert(vecVertices.end(), verticesSet.begin(), verticesSet.end());//???????

	for(int i = 0; i < numVertices; i++)
    {
	    boost::put(boost::vertex_name_t(), g, i, vecVertices[i]); // set the property of a vertex
	    indexes[vecVertices[i]] = boost::vertex(i, g);     // retrives the associated vertex descriptor
    }
    cout << "Add vertex!!!!" << endl;
    for(int i = 0; i < vecEdge.size(); i++)
  	{
    	boost::add_edge(indexes[get<0>(vecEdge[i])], indexes[get<1>(vecEdge[i])], EdgeProperty(get<2>(vecEdge[i])), g);
  	}
    cout << "Add edges!!!!" << endl;
    Vertex start = vertex(13, g);
    Vertex end = vertex(2, g);
    vector<string> vec;
    boost::property_map<UndirectedGraph, boost::vertex_name_t>::type name = get(boost::vertex_name_t(), g);
    FindPath path;
    clock_t start_t = clock();
    path.pathFinding(start, end, g, name[start], visitedNode, vec);
    clock_t end_t = clock();
    cout << "execution time: " << (double) (end_t-start_t)/CLOCKS_PER_SEC << endl;
    string in_path;
    unordered_set<string> result;
    for (size_t k = 0; k < vec.size(); k++){
        in_path = vec[k];
        std::vector<std::string> m_currentPath;  
        boost::algorithm::split(m_currentPath, in_path, boost::algorithm::is_any_of(">"));  
        for(size_t i = 0;i<m_currentPath.size();i++)  
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

