#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <boost/algorithm/string.hpp>
#include <unordered_set>

using namespace std;

typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;
typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<UndirectedGraph> GraphTraits;
typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type IndexMap;

class FindPath {
	private:
		
        // typedef typename boost::property_map<UndirectedGraph, boost::edge_name_t>::type typev;

        boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname;
        boost::property_map<UndirectedGraph, boost::edge_name_t>::type Ename;
        IndexMap index;
        UndirectedGraph g;
    public:
    	FindPath(){};
    	~FindPath();
        FindPath (UndirectedGraph g);
        void pathFinding(int times, Vertex start, Vertex end, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res);

};