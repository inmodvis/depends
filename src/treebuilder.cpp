#include "treebuilder.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iomanip>


bool TreeBuilder::Initilize(std::string sourseDir, std::string includesDir, std::string libDir) 
{
	bool result = false;
	m_sourseDir = sourseDir;
	m_includesDir = includesDir;
	m_libDir = libDir;
	level = -1;
	//check dirs for exist
	if (true)
		result = true;
	return result;
}

void TreeBuilder::Run()
{
	auto files = ReadDirectory(m_sourseDir);
	DoWork(files);

}

void TreeBuilder::DoWork(vector<std::pair<string, char>> &data)
{
	level++;
	for (auto i = 0; i < data.size(); i++)
	{
		auto work = data[i];
		// std::cout << std::setfill('.') << setw(level) << data[i].first << "\n";
		if (CheckAndPrintFile(data[i])) {
			auto result = GetDependFromFile(work.first); //if only file exists! filecheck();
			// main work or/and adding to structure
			level++;
			for (auto j = 0; j < result.size(); j++)
			{
				//std::cout << std::setfill('.') << setw(level) << result[j].first << "\n"; // chackresult() and check before
				CheckAndPrintFile(result[j]);
			}
			level--;
			if (!result.empty())
				DoWork(result);
				level--;
				
		}
	}
}

bool TreeBuilder::CheckAndPrintFile(std::pair<string, char> file) 
{
	auto result = false;
	std::filesystem::path path;
	switch (file.second)
	{
	case 0 :		
		break;
	case 1 :
		path = std::filesystem::path(m_sourseDir + "\\" + file.first);
		if (std::filesystem::exists(path))
		{
			std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level+1) << path.filename().u8string() << "\n";
			result = true;
		}
		else
		{
			std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level+1) << path.filename().u8string() << "(!)\n";
		}
		break;
	case 2 :
		path = std::filesystem::path(file.first);
		if (std::filesystem::exists(path)) 
		{
			//std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level+1) << path.filename().u8string() << "\n";
			std::cout << path.filename().u8string() << "\n";
			result = true;
		} 
		else
		{
			// std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level+1) << path.filename().u8string() << "(!)\n";
			std::cout << path.filename().u8string() << "(!)\n";
		}
		break;
	}
	return result;
}





vector<std::pair<string, char>> TreeBuilder::GetDependFromFile(std::string& file)
{
	vector<std::pair<string, char>> res;
	ifstream myfile;

	string str;
	string temp;
	bool commented = false;
	regex str_expr("^\\s*#\\s*include\\s+(?:<[^>]*>|\"[^\"]*\")\\s*"); // #include <...>  and #include "..." 
	regex str_expr_first("^\\s*#\\s*include\\s+(?:<[^>]*>)\\s*");	// #include <...>
	regex str_expr_second("^\\s*#\\s*include\\s+(\"[^\"]*\")\\s*"); // #include "..."
	regex str_remove("^\\s*#\\s*include|\<|\>|\"+|\\s");  // #include <> and #include"" 
	regex inline_com("\.*\/\/\.*"); // comment //
	regex inline_remove("\/\/\.*");
	regex start_com("\.*\/\\*\.*");  // comment /*
	regex end_com("\.*\\*\/\.*"); // comment /*
	myfile.open(file, ios_base::in);
	while (!myfile.eof())
	{
		temp.clear();
		getline(myfile, temp);
		if (!commented)
		{
			if (regex_match(temp, inline_com))
			{
				temp = regex_replace(temp, inline_remove, "");
			}
			if (regex_match(temp, start_com))
			{
				regex start_com_remove("\/\\*\.*");
				temp = regex_replace(temp, start_com_remove, "");
				commented = true;
			}
			if (regex_match(temp, str_expr))
				//TODO: also #include<aaa>#include"bb" separate by includes and remove everything !!! 
			{
				if (regex_match(temp, str_expr_first))
					res.push_back(std::pair<string, char>(regex_replace(temp, str_remove, ""), 0));
				else if (regex_match(temp, str_expr_second))
					res.push_back(std::pair<string, char>(regex_replace(temp, str_remove, ""), 1));
			}
		}
		else
		{
			if (regex_match(temp, end_com))
			{
				auto pos = temp.find("*/");
				temp.replace(0, pos + 2, "");
				if (regex_match(temp, str_expr))
				{
					if (regex_match(temp, str_expr_first))
						res.push_back(std::pair<string, char>(regex_replace(temp, str_remove, ""), 0));
					else if (regex_match(temp, str_expr_second))
						res.push_back(std::pair<string, char>(regex_replace(temp, str_remove, ""), 1));
				}
				commented = false;
			}
		}

	}

	return res;
}




vector<std::pair<string, char>> TreeBuilder::ReadDirectory(std::string path)
{
	vector<std::pair<string, char>> files;
	std::filesystem::directory_iterator directory;
	try
	{
		directory = std::filesystem::directory_iterator(path);
	}
	catch (std::exception)
	{
		cerr << "No such directory";
	}

	for (const auto& p : directory) //add directories recrtution 
	{
		auto pa = p.path();
		auto extension = pa.extension();
		if (extension == L".hpp" || extension == L".cpp" )
		{
			files.push_back(std::pair<string, char>(pa.u8string(), 2));
		}
		else if (p.is_directory()) {
			auto sub = ReadDirectory(pa.u8string());
			for (auto& u : sub)
				files.push_back(u); //todo optimize
		}
	}
	return files;
}
