#ifndef DUALSIMULATION_H
#define DUALSIMULATION_H

#include "graph.h"
#include "utility.h"
#include <iostream>
#include <vector>

using namespace std;

class DualSimulation
{
public:
	vector< vector<unsigned int> > simulate(Graph& g, Graph& q, vector< vector<unsigned int> > & candidates);
};

#endif