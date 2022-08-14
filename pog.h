#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

struct pog_command {
	string name;
	string value;
};

struct pog_command_error {
	string line;
	string error;
};


void parse_pog_file(const string& file, unordered_map<string, pog_command>& pog_map, vector<pog_command_error>& bad_lines);


