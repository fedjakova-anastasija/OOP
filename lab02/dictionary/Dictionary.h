#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>  
#include <map>
#include <string>

typedef std::multimap<std::string, std::string> Dictionary;

bool FindTranslation(const Dictionary& dictionary, const std::string& userAnswer);
bool CheckEmptyAnswer(const std::string& unknownWord, std::string& userTranslation);
void InsertInDictionary(Dictionary& dictionary, const std::string& userAnswer, const std::string& translation);

