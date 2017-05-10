#include "csv_read.h"


csv_read::csv_read()
{
}
void csv_read::read(char *fname)
{
	ifstream file(fname);

	string str;
	int p;

	if (file.fail()){
		cerr << "failed." << endl;
		exit(0);
	}
	while (getline(file, str)){
		//コメント箇所は除く
		if ((p = str.find("//")) != str.npos) continue;
		vector<string> inner;

		//コンマがあるかを探し、そこまでをvaluesに格納
		while ((p = str.find(",")) != str.npos){
			inner.push_back(str.substr(0, p));

			//strの中身は", "の1文字を飛ばす
			str = str.substr(p + 1);
		}
		inner.push_back(str);
		values.push_back(inner);
	}

	for (unsigned int i = 0; i < values.size(); ++i){
		for (unsigned int j = 0; j < values[i].size(); ++j){
			cout << values[i][j] << ",";
		}
		cout << endl;
	}

}
void csv_read::writeOnly1vector(char *fname, std::vector <int> Data)
{
	ofstream ofs(fname);

	vector<int>::iterator it;
	for (it = Data.begin(); it != Data.end(); it++)
	{
		ofs << (*it) << "," << endl;
	}
	return;
	
	

}
std::vector <vector <float>>csv_read::push_amatrix(vector<vector<string>> values)
{
	std::vector <vector <float>> e;
	e.resize(values.size());
	int j;
	for (int i = 0; i < values.size(); i++)
	{
		e.at(i).resize(values.at(i).size()-1);
		for (j = 0; j < e.at(i).size(); j++)
		{
			e.at(i).at(j) = stof(values.at(i).at(j));
		}
		b.push_back(stof(values.at(i).at(j)));
	}
	
	return e;
}

csv_read::~csv_read()
{
}
