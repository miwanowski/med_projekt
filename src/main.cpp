#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "fun.h"
#include "utils.h"

int main(int argc, char* argv[]) {
		// display usage when given too few arguments:
		if (argc < 4) {
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
			return 1;
		}

		// get obligatory arguments:
		std::string filename  		= argv[1];
		std::string targetColString = argv[2];
		std::string colString 		= argv[3];

		// parse target column:
		std::istringstream ss(targetColString);
		int targetCol;
		ss >> targetCol;

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
		for (int i=4; i < argc; ++i) {
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
		std::cout << "Results:" << std::endl;
		for (int i = 0; i < res.getSize(); ++i) {
			printAttributeList(res[i]->getAttributeList());
			std::cout << std::endl;
		}

		return 0;
}