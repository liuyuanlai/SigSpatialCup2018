#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <tuple>

using namespace std;
namespace pt = boost::property_tree;

int main() {
	pt::ptree root;
	pt::read_json("SampleDataset1/SampleDataset1.json", root);
	typedef tuple<string, string, string> Edge;
	typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
	typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> UndirectedGraph;

	vector<Edge> vecEdge;
	vector<string> vecVertices;
	unordered_set<string> vertices;
	map<string, UndirectedGraph::vertex_descriptor> indexes;


	for (pt::ptree::value_type &row : root.get_child("rows")) {
		//cout << row.second.get<string>("viaGlobalId") << endl;
		vecEdge.push_back(Edge(row.second.get<string>("fromGlobalId"),row.second.get<string>("toGlobalId"), row.second.get<string>("viaGlobalId")));
		vertices.insert(row.second.get<string>("fromGlobalId"));
		vertices.insert(row.second.get<string>("toGlobalId"));
	}

	int numVertices = vertices.size();
	UndirectedGraph g(numVertices);
	vecVertices.insert(vecVertices.end(), vertices.begin(), vertices.end());

	for(int i = 0; i < numVertices; i++)
    {
	    boost::put(boost::vertex_name_t(), g, i, vecVertices[i]); // set the property of a vertex
	    indexes[vecVertices[i]] = boost::vertex(i, g);     // retrives the associated vertex descriptor
    }

    for(int i = 0; i < vecEdge.size(); i++)
  	{
    	boost::add_edge(indexes[get<0>(vecEdge[i])], indexes[get<1>(vecEdge[i])], EdgeProperty(get<2>(vecEdge[i])), g);
  	}


	vector<string> :: iterator itr;
    for (itr = vecVertices.begin(); itr != vecVertices.end(); itr++)
        cout << (*itr) << endl;
    
	// for (int i = 0; i < vecEdge.size(); ++i) {
 //    	//boost::add_edge(vecEdge[i].first, vecEdge[i].second, g);
 //    	cout << vecEdge[i].first << endl;
 //    }



	//printf("%s\n", "test");
}