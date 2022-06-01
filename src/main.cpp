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


int main(int argc, char* argv[]) //add argv !
{
    string sourcePath;
    std::vector <string> includeandlibPaths;
    const char* flagPath = "-I";
    if (argc == 1) {
        cout << "no arguments!" << endl;
    }
    else {
        sourcePath = argv[1];
        for (int i = 2; i < argc;) {
            if (*argv[i] == *flagPath && i < argc)
            {
                includeandlibPaths.push_back(argv[i + 1]);
            }
            i += 2;
        }
        auto treeBuilder = std::make_shared<TreeBuilder>();
        if (treeBuilder->Initialize(sourcePath, includeandlibPaths))
            treeBuilder->Run();
    }
	
}

    