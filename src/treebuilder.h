//#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

class TreeBuilder 
{
private:
	std::string m_sourseDir;
	std::string m_includesDir;
	std::string m_libDir;
	int level;

public: 
	bool Initilize(std::string sourseDir, std::string includesDir, std::string libDir);
	void Run();
	void DoWork(vector<std::pair<string, char>> &data);
	bool CheckAndPrintFile(std::pair<string, char>);
	vector<std::pair<string, char>> ReadDirectory(std::string dir);
	vector<std::pair<string, char>> TreeBuilder::GetDependFromFile(std::string& file);
};