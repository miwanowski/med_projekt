/*
* Main class of fun algorithm.
*/

#ifndef FUN_H
#define FUN_H

#include <string>

#include "partition.h"
#include "candidate.h"
#include "candidateset.h"

class Fun {
public:
	typedef Partition::ArrayRepresentation ArrayRepresentation;
	typedef Partition::Group Group;
	typedef Candidate::AttributeList AttributeList;
	typedef int AttributeId;
	typedef std::vector<AttributeId> AttributeIds;

	Fun(/* something here? */);

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
	static Partition* strippedPoduct(Partition* a, Partition* b);

	// helper method for reading data file and generating initial candidates and partitions:
	static void generateInitialCandidates(const std::string& dataFilePath, 	// path to data file
										  const AttributeIds aIds,			// list of attribute Ids
										  const AttributeId targetId,		// target attribute Id
										  CandidateSet* cs,					// return: candidate set
										  Partition* targetPartition);		// return: target partition
};

#endif