#include "treebuilder.h"



bool TreeBuilder::Initialize(std::string& sourseDir, vector <string>& includeslibsDirs)
{
	if (std::filesystem::exists(sourseDir))
	{
		m_sourseDir = sourseDir;
	}
	else 
	{
		cerr << "Unanable source dir";
		return false;
	}
	for (auto& u : includeslibsDirs) 
	{
		if (std::filesystem::exists(u))
		{
			m_includesAndLibsDirs.push_back(u);
		}
	}
	level = -1;
	m_initialized = true;
	return true;
}

void TreeBuilder::Run()
{
	if (m_initialized)
	{
		auto files = ReadDirectory(m_sourseDir);
		DoWork(files);
		cout << "\n";
		set <size_t> countValues;
		for (const auto& u : m_count)
		{
			countValues.insert(u.second);
		}
		auto res = FlipMap(m_count);
		for (auto& u = countValues.rbegin(); u != countValues.rend(); ++u)
		{
			auto iterpair = res.equal_range(*u);
			for (auto l = iterpair.first; l != iterpair.second; l++)
			{
				cout << l->second << " " << l->first << "\n";
			}
		}
	}
}

void TreeBuilder::DoWork(vector<std::pair<string, char>> &data)
{
	level++;
	for (auto i = 0; i < data.size(); i++)
	{
		if (CheckAndPrintFile(data[i])) {
			auto result = GetDependFromFile(data[i].first);
			if (!result.empty())
			{
				DoWork(result);
				level--;
			}
		}
	}
}

bool TreeBuilder::CheckAndPrintFile(std::pair<string, char>& file) 
{
	auto result = false;
	std::filesystem::path path;
	std::filesystem::path checkext(file.first);
	if (checkext.extension() == L".hpp" || checkext.extension() == L".cpp" || checkext.extension() == L".h")
	{
		switch (file.second)
		{
		case 0:
			for (auto& u : m_includesAndLibsDirs)
			{
				path = std::filesystem::path(u +"/" + file.first);
				if (std::filesystem::exists(path))
				{
					std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level*2) << path.filename().u8string() << "\n";
					result = true;
					break;
				}
			}
			if (!result)
			{
				path = std::filesystem::path(file.first);
				std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level*2) << path.filename().u8string() << "(!)\n";
			}
			break;
		case 1:
			path = std::filesystem::path(m_sourseDir + "/" + file.first);
			if (std::filesystem::exists(path))
			{
				std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level*2) << path.filename().u8string() << "\n";
				result = true;
			}
			else
			{
				std::cout << std::setfill('.') << setw(path.filename().u8string().size() + level*2) << path.filename().u8string() << "(!)\n";
			}
			break;
		case 2:
			path = std::filesystem::path(file.first);
			if (std::filesystem::exists(path))
			{
				std::cout << path.filename().u8string() << "\n";
				result = true;
			}
			else
			{
				std::cout << path.filename().u8string() << "(!)\n";
			}
			break;
		}
		auto mapref = m_count.find(path.filename().u8string());
		if (mapref != m_count.end())
		{
			mapref->second++;
			if (file.second != 2) 
			{
				result = false;
			}
		}
		else
		{
			m_count[path.filename().u8string()] = 1;
		}
	}
	if (result)
	{
		file.first = path.u8string();
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
				//not implemented: unstandard includes like: 
				//#include<aaa> #include"bb" 
				//in one line
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

	for (const auto& p : directory)  
	{
		auto pa = p.path();
		auto extension = pa.extension();
		if (extension == L".hpp" || extension == L".cpp" || extension == L".h")
		{
			files.push_back(std::pair<string, char>(pa.u8string(), 2));
		}
		else if (p.is_directory()) {
			auto sub = ReadDirectory(pa.u8string());
			for (auto& u : sub)
				files.push_back(u); 
		}
	}
	return files;
}
