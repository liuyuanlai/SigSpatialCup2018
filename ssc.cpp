#include <stdio.h>
#include <iostream>
#include "buildgraph.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

int main() {
	pt::ptree root;
	pt::read_json("SampleDataset1/SampleDataset1.json", root);

	string type_ = root.get<string>("type");
	cout << type_ << endl;
	for (pt::ptree::value_type &row : root.get_child("rows")) {
		cout << row.second.get<string>("viaGlobalId") << endl;
    	
	}

	//printf("%s\n", "test");
}