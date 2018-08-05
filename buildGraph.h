#include <iostream>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/unordered_map.hpp>

#include "typedef.h"

using namespace std;

class BuildGraph {
	public:
		UndirectedGraph g;
		vector<Edge> vecEdge;
		vector<string> vecStrEdge;
		vector<string> vecVertices;
		unordered_set<string> setVertices;
		Str2DescMap strIndexVertices;
		Desc2StrMap descIndexVertices;
		//vector<map<int, string>> pathStore;
		boost::ptr_vector<AllEdgePath> pathStore;
		vector<string> controllers;
		int numVertices;

	public:
		BuildGraph (){};
		BuildGraph (string file);
		UndirectedGraph getGraph();
		void printEdge();


};

