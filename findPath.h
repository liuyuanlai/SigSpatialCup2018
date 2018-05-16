#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <boost/algorithm/string.hpp>
#include <unordered_set>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace std;

//typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
//typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
typedef boost::property<boost::edge_index_t, std::size_t> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty> UndirectedGraph;
typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<UndirectedGraph> GraphTraits;
typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type IndexMap;
typedef map<UndirectedGraph::vertex_descriptor, string> desc2strMap;
typedef pair<string, string> VertexEdgePath;
typedef map<int, VertexEdgePath> AllEdgePath;

class FindPath {
	private:
		
        // typedef typename boost::property_map<UndirectedGraph, boost::edge_name_t>::type typev;

        //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname;
        boost::property_map<UndirectedGraph, boost::edge_index_t>::type Ename;
        //IndexMap index;
        UndirectedGraph g;
        boost::ptr_vector<AllEdgePath> pathStore;
        desc2strMap descIndexVertices;
        vector<string> vecStrEdge;
        vector<string> vecVertices;
        Vertex start;
        Vertex end;

        vector<string> vertexRes;
	    vector<string> edgeRes;
	    unordered_set<string> result;
    public:
    	FindPath(){};
    	//~FindPath();
        FindPath (UndirectedGraph g, boost::ptr_vector<AllEdgePath> pathStore, vector<string> vecStrEdge, vector<string> vecVertices, desc2strMap descIndexVertices, Vertex start, Vertex end);
        bool checkResult(string expectedfile);
        void pathFindDup();
        void pathFindNoDup();
        void pathFindingDup(Vertex start, string currentVertexPath, string currentEdgePath, unordered_set<Vertex> visitedNode);
        VertexEdgePath pathFindingNoDup(Vertex start, unordered_set<Vertex> visitedNode);

};