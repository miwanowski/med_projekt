#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "fun.h"
#include "utils.h"

void displayUsage(char* argv[]) {
	std::cerr << "Usage: " << argv[0] << " <filename> <target_col> \"<col1>,...,<coln>\" [options]";
	std::cerr << std::endl;
	std::cerr << "Available options:" << std::endl;
	std::cerr << "  --holds        : use Holds (default)" << std::endl;
	std::cerr << "  --sholds       : use StrippedHolds" << std::endl;
	std::cerr << "  --rsholds      : use ReducedStrippedHolds" << std::endl;
	std::cerr << "  --prsholds     : use PartReducedStrippedHolds" << std::endl;
	std::cerr << "  --product      : use Product (default)" << std::endl;
	std::cerr << "  --sproduct     : use StrippedProduct" << std::endl;
	std::cerr << "  --optprune     : use optional pruning" << std::endl;
	std::cerr << "  --nooptprune   : don't use optional pruning (default)" << std::endl;
}

int main(int argc, char* argv[]) {
		// display usage when given too few arguments:
		if (argc < 2) {
			displayUsage(argv);
			return 1;
		}
		// get obligatory arguments:
		std::string filename  		= argv[1];
		bool paramsInsideDataFile   = false;

		// check if params are defined inside data file:
		std::string headerLine;
		std::ifstream dataFile (filename.c_str());
		if (dataFile.is_open()) {
			std::getline(dataFile, headerLine);
			if (headerLine[0] == '#') {
				paramsInsideDataFile = true;
			}
			dataFile.close();
		}

		if (!paramsInsideDataFile && argc < 4) {
			displayUsage(argv);
			return 1;
		}

		std::string targetColString;
		std::string colString;

		if (paramsInsideDataFile) {
			std::vector<std::string> splitFileParams = split(headerLine.substr(1), ' ');
			if (splitFileParams.size() != 2) {
				std::cerr << "Improper parameters defined inside the data file!" << std::endl;
				std::cerr << "Correct format of the optional first line inside the data file is:" << std::endl;
				std::cerr << "#<target_col> <col1>,...,<coln>" << std::endl;
				return 1;
			}
			targetColString = splitFileParams[0];
			colString 		= splitFileParams[1];
		}
		int i;
		// get command line arguments:
		if (argc >= 4 && argv[2][0] != '-' && argv[3][0] != '-') {
			targetColString = argv[2];
			colString 		= argv[3];
			i = 4;
		} else {
			i = 2;
		}
		// parse target column:
		std::istringstream ss(targetColString);
		int targetCol;
		ss >> targetCol;

		std::cout<< "targetCol=" << targetCol << std::endl;
		std::cout<< "cols=" << colString << std::endl << std::endl;

		// parse columns:
		std::vector<std::string> splitColString = split(colString, ',');
		std::vector<int> cols;
		for (std::vector<std::string>::iterator i = splitColString.begin(); i != splitColString.end(); ++i) {
			std::istringstream ss(*i);
			int currentCol;
			ss >> currentCol;
			cols.push_back(currentCol);
		}
		// parse options:
		for (; i < argc; ++i) {
			std::string option = argv[i];
			if (option == "--holds") {
				Fun::holdsVariant_ = &Fun::holds;
				// std::cout << "using regular holds" << std::endl;
			} else if  (option == "--sholds") {
				Fun::holdsVariant_ = &Fun::strippedHolds;
				// std::cout << "using stripped holds" << std::endl;
			} else if  (option == "--rsholds") {
				Fun::holdsVariant_ = &Fun::reducedStrippedHolds;
				// std::cout << "using reduced stripped holds" << std::endl;
			} else if  (option == "--prsholds") {
				Fun::holdsVariant_ = &Fun::partReducedStrippedHolds;
				// std::cout << "using part reduced stripped holds" << std::endl;
			} else if  (option == "--product") {
				Fun::productVariant_ = &Fun::product;
				// std::cout << "using regular product" << std::endl;
			} else if  (option == "--sproduct") {
				Fun::productVariant_ = &Fun::strippedProduct;
				// std::cout << "using stripped product" << std::endl;
			} else if  (option == "--optprune") {
				Fun::optionalPruning = true;
				// std::cout << "using optional pruning" << std::endl;
			} else if  (option == "--nooptprune") {
				Fun::optionalPruning = false;
				// std::cout << "not using optional pruning" << std::endl;
			} else {
				std::cerr << "Unrecognized option: " << option << std::endl;
				return 1;
			}
		}

		// execute the algorithm:
		CandidateSet res = Fun::fun(filename, cols, targetCol);

		// output results:
		std::cout << "\nResults:" << std::endl;
		for (int i = 0; i < res.getSize(); ++i) {
			printAttributeList(res[i]->getAttributeList());
			std::cout << std::endl;
		}

		return 0;
}