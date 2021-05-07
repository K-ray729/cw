
#ifndef _H_DRAW_H_
#define _H_DRAW_H_



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;
struct mynode{
	long id;
	double lat;
	double lon;
};

void divide_node_link(string mapPath, string nodePath, string linkPath);
void get_all_nodes(string nodePath);
void generate_gnuplot_dat(string linkPath, string outPath);

#endif
