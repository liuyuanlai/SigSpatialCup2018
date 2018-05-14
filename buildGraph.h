#include <iostream>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>


using namespace std;

//typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
//typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
typedef boost::property<boost::edge_index_t, std::size_t> EdgeProperty;
//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty> UndirectedGraph;
typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<UndirectedGraph> GraphTraits;
//typedef tuple<string, string, string> Edge;
typedef pair<string, string> Edge;


class BuildGraph {
	public:
		UndirectedGraph g;
		vector<Edge> vecEdge;
		vector<string> vecStrEdge;
		vector<string> vecVertices;
		unordered_set<string> setVertices;
		map<string, UndirectedGraph::vertex_descriptor> strIndexVertices;
		map<UndirectedGraph::vertex_descriptor, string> descIndexVertices;
		int numVertices;

	public:
		BuildGraph (){};
		BuildGraph (string file);
		UndirectedGraph getGraph();


};

