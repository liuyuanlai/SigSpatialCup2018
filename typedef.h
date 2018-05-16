#ifndef __TYPE_DEF__
#define __TYPE_DEF__

using namespace std;

// typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
// typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
typedef boost::property<boost::edge_index_t, std::size_t> EdgeProperty;
// typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty> UndirectedGraph;
typedef typename boost::graph_traits<UndirectedGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<UndirectedGraph> GraphTraits;
typedef boost::property_map<UndirectedGraph, boost::vertex_index_t>::type VertexIndexMap;
typedef typename boost::property_map<UndirectedGraph, boost::edge_index_t>::type EdgeIndexMap;
typedef map<UndirectedGraph::vertex_descriptor, string> desc2strMap;
// typedef tuple<string, string, string> Edge;
typedef pair<string, string> Edge;
typedef pair<string, string> VertexEdgePath;
typedef map<int, VertexEdgePath> AllEdgePath;

#endif