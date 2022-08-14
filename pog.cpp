#include <fstream>
#include <iostream>
#include <regex>
#include "pog.h"

#define POG_LINE_DESCRPTION "name;file_or_url"

using std::regex;

void parse_pog_file(const string& file, unordered_map<string, pog_command>& pog_map, vector<pog_command_error>& bad_lines) 
{
	string line;
	std::ifstream f;
	pog_command item;
	bool is_bad_line;
	size_t colon_idx;

	string name;
	string value;

	regex regex_comment = regex(R"(^\s*\\)"); 

	f.open(file);
	while (!f.eof()) {
		std::getline(f,line);
		if (std::regex_search(line, regex_comment))
			continue;

    	if ((colon_idx = line.find_first_of(";")) == string::npos) {
			bad_lines.push_back(pog_command_error{line, string("missing colon, the structure of a line is: ") + POG_LINE_DESCRPTION });
			continue;
		}

		name = line.substr(0, colon_idx);
		value = line.substr(colon_idx+1);

		pog_map[name] = pog_command { name, value };
	}
	f.close();
}


