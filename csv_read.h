#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class csv_read
{
public:
	csv_read();
	~csv_read();
	void read(char *fname);
	void csv_read::writeOnly1vector(char *fname, std::vector <int> Data);
	std::vector <vector <float>> push_amatrix(vector<vector<string>> values);
	vector<vector<string>> values;
	std::vector<float>b;
};

