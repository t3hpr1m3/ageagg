#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <vector>

typedef std::map<int,int> age_dict;

/*
 * Print program usage.
 */
void usage(const char* progname) {
	std::cerr << "Usage: " << progname << " <filename> " << std::endl << std::endl;
}

/*
 * Dump error to console, then display usage information.
 */
void a_bort(const char* progname, const char* msg) {
	std::cerr << "Error: " << msg << std::endl << std::endl;
	usage(progname);
}

/*
 * Quick test to see if a file exists on the filesystem.
 */
bool file_exists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

/*
 * Splits a string on the specified delimiters.
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	elems.clear();
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


int main(int argc, char *argv[]) {

	// make sure we received enough arguments
	if (argc < 2) {
		a_bort(argv[0], "filename is required.");
		return 1;
	}

	const std::string filename = argv[1];

	// is it a real file?
	if (!file_exists(filename)) {
		a_bort(argv[0], (std::string() + "file not found: " + filename).c_str());
		return 1;
	}

	//
	// Iterate over the lines in the file, processing each record as a tuple.
	//
	age_dict ages;
	age_dict::iterator age;
	std::ifstream input(filename.c_str());
	std::vector<std::string> elems;
	int key;
	for (std::string line; std::getline(input, line);) {
		//
		// split the line at the comma
		//
		split(line, ',', elems);

		//
		// make sure we have at least 2 fields
		//
		if (elems.size() >= 2) {

			//
			// convert age to an int
			//
			key = atoi(elems[1].c_str());

			//
			// If there is already an element matching this age, just
			// increment its count.  otherwise, add a new one.
			//
			if ((age = ages.find(key)) != ages.end()) {
				age->second++;
			} else {
				ages[key] = 1;
			}
		}
	}

	//
	// Now, print the results
	//
	std::cout << std::setw(8) << std::left << "Age" << "Count" << std::endl;
	std::cout << std::setw(8) << std::left << "===" << "=====" << std::endl;
	for (age = ages.begin(); age != ages.end(); age++) {
		std::cout << std::setw(8) << std::left << age->first << age->second << std::endl;
	}

	return 0;
}
