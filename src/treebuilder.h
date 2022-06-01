#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iomanip>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>


using namespace std;

class TreeBuilder 
{
private:
	string m_sourseDir;
	bool m_initialized = false;
	vector <string> m_includesAndLibsDirs;
	int level;
	map <string, size_t> m_count;
	void DoWork(vector<std::pair<string, char>>& data);
	bool CheckAndPrintFile(std::pair<string, char>& file);
	vector<std::pair<string, char>> ReadDirectory(std::string dir);
	vector<std::pair<string, char>> TreeBuilder::GetDependFromFile(std::string& file);

public: 
	bool Initialize(std::string& sourseDir, vector <string>& includeslibsDirs);
	void Run();
	

};

template<typename A, typename B>
std::pair<B, A> FlipPair(const std::pair<A, B>& p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> FlipMap(const std::map<A, B>& src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		FlipPair<A, B>);
	return dst;
}