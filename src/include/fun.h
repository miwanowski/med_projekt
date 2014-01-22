/*
* Main class of fun algorithm.
*/

#ifndef FUN_H
#define FUN_H

#include <string>
#include <map>

#include "partition.h"
#include "candidate.h"
#include "candidateset.h"
#include "hashtree.h"

class Fun {
private:
	Fun() { };

public:
	typedef Partition::ArrayRepresentation ArrayRepresentation;
	typedef Partition::Group Group;
	typedef Candidate::AttributeList AttributeList;
	typedef int AttributeId;
	typedef std::vector<AttributeId> AttributeIds;
	typedef std::map<AttributeId, std::string> AttributeMap;

	// the order of the used hash tree:
	static int hashTreeOrder_;

	// hash tree for candidate pruning:
	static HashTree* hashTree;

	// mapping of attribute ids to names:
	static AttributeMap attributeMap;

	// pointer to the selected "holds" function variant
	static bool (*holdsVariant_)(Candidate* c, Partition* d);

	// pointer to the selected "product" function variant
	static Partition* (*productVariant_)(Partition* a, Partition* b);

	// main method:
	static CandidateSet fun(const std::string& dataFilePath, 	// path to data file
							const AttributeIds aIds,			// list of attribute Ids
							const AttributeId targetId			// target attribute Id
							);

	// generate C_k+1 candidates from C_k:
	static CandidateSet* funGen(CandidateSet* ck);

	// all variants of "Holds" function:
	static bool holds(Candidate* c, Partition* d);
	static bool strippedHolds(Candidate* c, Partition* d);
	static bool reducedStrippedHolds(Candidate* c, Partition* d);
	static bool partReducedStrippedHolds(Candidate* c, Partition* d);

	// all variants of "Product" function:
	static Partition* product(Partition* a, Partition* b);
	static Partition* strippedProduct(Partition* a, Partition* b);

	// helper method for reading data file and generating initial candidates and partitions:
	static void generateInitialCandidates(const std::string& dataFilePath, 	// path to data file
										  const AttributeIds aIds,			// list of attribute Ids
										  const AttributeId targetId,		// target attribute Id
										  CandidateSet* cs,					// return: candidate set
										  Partition* targetPartition);		// return: target partition
};

#endif