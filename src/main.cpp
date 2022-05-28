// depends.cpp: определяет точку входа для приложения.
//
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <regex>
#include <iomanip>

#include <memory>
#include "treebuilder.h"

using namespace std;


int main() //add argv !
{
	string sourcePath = "../../../testPath";
	string libPath = "../../../testPath";
	string includePath = "../../../testPath";
	

	auto treeBuilder = std::make_shared<TreeBuilder>();
	if (treeBuilder->Initilize(sourcePath, includePath, libPath))
		treeBuilder->Run();
}