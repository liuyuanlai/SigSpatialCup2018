#include "buildGraph.h"

using namespace std;
namespace pt = boost::property_tree;

BuildGraph::BuildGraph(string file) {
	pt::ptree root;
	pt::read_json(file, root);
	cout << "Read file completed..." << endl;

    for (pt::ptree::value_type &row : root.get_child("rows")) {
		vecEdge.push_back(Edge(row.second.get<string>("fromGlobalId"), row.second.get<string>("toGlobalId")));
		vecStrEdge.push_back(row.second.get<string>("viaGlobalId"));
		setVertices.insert(row.second.get<string>("fromGlobalId"));
		setVertices.insert(row.second.get<string>("toGlobalId"));
	}
	cout << "Parse file completed..." << endl;

	numVertices = setVertices.size();
	g = UndirectedGraph(numVertices);
	vecVertices.insert(vecVertices.end(), setVertices.begin(), setVertices.end());

	for(int i = 0; i < numVertices; i++)
    {
	    //boost::put(boost::vertex_name, g, i, vecVertices[i]); // set the property of a vertex
	    boost::add_vertex(g);
	    strIndexVertices[vecVertices[i]] = i;     // retrives the associated vertex descriptor
	    //cout <<  strIndexVertices[vecVertices[i]] << endl;
	    descIndexVertices[i] = vecVertices[i];
	    pathStore.push_back(new AllEdgePath());
    }
    cout << "Add vertices completed..." << endl;

    for(int i = 0; i < vecEdge.size(); i++)
  	{
    	//boost::add_edge(strIndexVertices[get<0>(vecEdge[i])], strIndexVertices[get<1>(vecEdge[i])], EdgeProperty(get<2>(vecEdge[i])), g);
    	//boost::add_edge(strIndexVertices[vecEdge[i].first], strIndexVertices[vecEdge[i].second], EdgeProperty(vecStrEdge[i]), g);
  		boost::add_edge(strIndexVertices[vecEdge[i].first], strIndexVertices[vecEdge[i].second], EdgeProperty(i), g);
  		pathStore.at(strIndexVertices[vecEdge[i].first])[strIndexVertices[vecEdge[i].second]] = VertexEdgePath("null", "null");
  		pathStore.at(strIndexVertices[vecEdge[i].second])[strIndexVertices[vecEdge[i].first]] = VertexEdgePath("null", "null");

  	}
    cout << "Add edges completed..." << endl;
};

UndirectedGraph BuildGraph::getGraph () {
	return g;
}

void BuildGraph::printEdge() {
	boost::graph_traits<UndirectedGraph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << source(*ei, g)<< "," << target(*ei, g) << ") ";
    std::cout << std::endl;
}