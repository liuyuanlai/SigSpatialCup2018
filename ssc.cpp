#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"

using namespace std;
namespace pt = boost::property_tree;

int main() {
	pt::ptree root;
	pt::read_json("SampleDataset1/SampleDataset1.json", root);
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> UndirectedGraph;
	typedef pair<string, string> Edge;

	std::vector<Edge> edgeVec;

	//string type_ = root.get<string>("type");
	//cout << type_ << endl;
	for (pt::ptree::value_type &row : root.get_child("rows")) {
		//cout << row.second.get<string>("viaGlobalId") << endl;
		edgeVec.push_back(Edge(row.second.get<string>("fromGlobalId"),row.second.get<string>("toGlobalId")));
	}

	UndirectedGraph g(edgeVec.size());
	for (int i = 0; i < edgeVec.size(); ++i) {
    	//boost::add_edge(edgeVec[i].first, edgeVec[i].second, g);
    	cout << edgeVec[i].first << endl;
    }



	//printf("%s\n", "test");
}