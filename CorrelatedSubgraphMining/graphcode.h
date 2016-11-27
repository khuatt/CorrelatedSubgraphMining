#ifndef GRAPHCODE_H
#define GRAPHCODE_H

#include "graph.h"

#include<iostream>
#include<map>
#include<vector>
#include<fstream>

using namespace std;

class DFS
{
public:
	int from;
	int to;
	int fromlabel;
	int elabel;
	int tolabel;

	bool operator == (const DFS& d2)
	{
		return (from == d2.from && to == d2.to && fromlabel == d2.fromlabel && elabel == d2.elabel && tolabel == d2.tolabel);
	}
	
	bool operator != (const DFS& d2)
	{
		return (!(*this == d2));
	}
	DFS() : from(-1), to(-1), fromlabel(-1), elabel(-1), tolabel(-1) {};
};

typedef vector<int> RMPath;

class DFSCode : public vector<DFS>
{
private:
	RMPath rmpath;

public:
	const RMPath& buildRMPath();
	
	unsigned int nodeCount(void);

	void push(int from, int to, int fromlabel, int elabel, int tolabel)
	{
		resize(size()+1);
		DFS& d = (*this)[size()-1];
		
		d.from = from;
		d.to = to;
		d.fromlabel = fromlabel;
		d.elabel = elabel;
		d.tolabel = tolabel;
	}
	
	void pop()
	{ 
		resize (size() - 1);
	}
	ostream& write(ostream &);

	/* Convert current DFS code into a graph.
	 */
	bool toGraph(Graph &);
};

struct PDFS
{
	unsigned int id;
	Edge *edge;
	PDFS *prev;
	PDFS() : id(0), edge(0), prev(0) {};
};

class History : public vector<Edge*>
{
private:
	vector<int> edge;
	vector<int> vertex;

public:
	bool hasEdge(unsigned int id)
	{
		return (bool)edge[id];
	}
	
	bool hasVertex(unsigned int id)
	{
		return (bool)vertex[id];
	}

	void build(Graph&, PDFS*);
	History() {};
	History(Graph& g, PDFS* p)
	{
		build(g, p);
	}
};

class Projected : public vector<PDFS>
{
public:
	void push(int id, Edge* edge, PDFS* prev)
	{
		resize(size()+1);
		PDFS& d = (*this)[size()-1];
		d.id = id;
		d.edge = edge;
		d.prev = prev;
	}
};

typedef vector<Edge*> EdgeList;
typedef map<int, map<int, map<int,Projected>>>						Projected_map3;
typedef map<int, map<int, Projected>>								Projected_map2;
typedef map<int, Projected>											Projected_map1;
typedef map<int, map<int, map<int,Projected>>>::iterator			Projected_iterator3;
typedef map<int, map<int, Projected>>::iterator						Projected_iterator2;
typedef map<int, Projected>::iterator								Projected_iterator1;
typedef map<int, map<int, map<int, Projected>>>::reverse_iterator	Projected_riterator3;

bool get_forward_pure(Graph&, Edge*, int, History&, EdgeList&);
bool get_forward_rmpath(Graph&, Edge*, int, History&, EdgeList&);
bool get_forward_root(Graph&, Vertex&, EdgeList&);
Edge* get_backward(Graph&, Edge*, Edge*, History&);

//class GraphCode
//{
//private:
//	typedef map<int, map<int, map<int,Projected>>>						Projected_map3;
//	typedef map<int, map<int, Projected>>								Projected_map2;
//	typedef map<int, Projected>											Projected_map1;
//	typedef map<int, map<int, map<int,Projected>>>::iterator			Projected_iterator3;
//	typedef map<int, map<int, Projected>>::iterator						Projected_iterator2;
//	typedef map<int, Projected>::iterator								Projected_iterator1;
//	typedef map<int, map<int, map<int, Projected>>>::reverse_iterator	Projected_riterator3;
//	
//	vector<Graph>	TRANS;
//	DFSCode			DFS_CODE;
//	DFSCode			DFS_CODE_IS_MIN;
//	Graph			GRAPH_IS_MIN;
//	
//	unsigned int ID;
//	unsigned int minsup;
//	unsigned int maxpat_min;
//	unsigned int maxpat_max;
//	
//	bool where;
//	bool enc;
//	bool directed;
//	ostream* os;
//	ofstream fos;
//	
//	map<unsigned int, map<unsigned int, unsigned int>> singleVertex;
//	map<unsigned int, unsigned int> singleVertexLabel;
//	
//	bool is_min();
//	bool project_is_min(Projected&);
//	
//	map<unsigned int,unsigned int> support_counts(Projected& projected);
//	unsigned int support(Projected&);
//	void project (Projected&);
//	void report (Projected&,unsigned int);
//	
//	void read(char*);
//	void run_intern(void);
//public:
//	GraphCode(void);
//	~GraphCode(void);
//	void run(char* fname,std::ostream& _os,unsigned int _minsup,unsigned int _maxpat_min,unsigned int _maxpat_max,bool _enc,bool _where,bool _directed);
//};

#endif