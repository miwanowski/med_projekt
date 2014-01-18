/*
* Main class of fun algorithm.
*/

#ifndef FUN_H
#define FUN_H

#include "partition.h"
#include "candidate.h"
#include "candidateset.h"

class Fun {
public:
	typedef Partition::ArrayRepresentation ArrayRepresentation;
	typedef Partition::Group Group;

	Fun(/* something here? */);

	// main method:
	static CandidateSet fun(/* attribute set AT, target attribure D */);

	// generate C_k+1 candidates from C_k:
	static CandidateSet* funGen(CandidateSet ck);

	// all variants of "Holds" function:
	static bool holds(Candidate* c, Partition* d);
	static bool strippedHolds(Candidate* c, Partition* d);
	static bool reducedStrippedHolds(Candidate* c, Partition* d);
	static bool partReducedStrippedHolds(Candidate* c, Partition* d);

	// all variants of "Product" function:
	static Partition* product(Partition* a, Partition* b);
	static Partition* strippedPoduct(Partition* a, Partition* b);
};

#endif