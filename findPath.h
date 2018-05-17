#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/algorithm/string.hpp>
#include <unordered_set>


#include "typedef.h"

using namespace std;

class FindPath {
	private:
        //boost::property_map<UndirectedGraph, boost::vertex_name_t>::type Vname;
        EdgeIndexMap Ename;
        //IndexMap index;
        UndirectedGraph g;
        boost::ptr_vector<AllEdgePath> pathStore;
        Desc2StrMap descIndexVertices;
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
        FindPath (UndirectedGraph g, boost::ptr_vector<AllEdgePath> pathStore, vector<string> vecStrEdge, vector<string> vecVertices, Desc2StrMap descIndexVertices);
        void checkResult(string expectedfile);
        void pathFindDup(Vertex start, Vertex end);
        void pathFindNoDup(Vertex start, Vertex end);
        void pathFindingDup(Vertex start, string currentVertexPath, string currentEdgePath, unordered_set<Vertex> visitedNode);
        VertexEdgePath pathFindingNoDup(Vertex start, unordered_set<Vertex> visitedNode);

};