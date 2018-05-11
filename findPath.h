#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <boost/algorithm/string.hpp>

using namespace std;

class FindPath {
	private:
		typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
		typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;
		typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
        typedef boost::graph_traits<UndirectedGraph> GraphTraits;
        typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type IndexMap;
        // typedef typename boost::property_map<UndirectedGraph, boost::edge_name_t>::type typev;

        boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname;
        boost::property_map<UndirectedGraph, boost::edge_name_t>::type Ename;
        IndexMap index;
    public:
    	FindPath(){};
    	~FindPath();
        FindPath (UndirectedGraph g);
        void pathFinding(Vertex start, Vertex end, UndirectedGraph g, string currentPath, unordered_set<Vertex> visitedNode, vector<string> &res);

};