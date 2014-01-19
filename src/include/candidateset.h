/*
* Class representing a set of candidates or reducts (verified
* candidates).
*/

#ifndef CANDIDATESET_H
#define CANDIDATESET_H

#include "candidate.h"

class CandidateSet
{
	// internal data type for candidate list representation:
	typedef std::vector<Candidate*> CandidateList;

private:
	CandidateList candidateList_;

public:
	// create an empty candidate set:
	CandidateSet() { } ;

	// get the number of candidates in the set:
	long getSize() const;

	// access candidates by index:
	Candidate* operator[] (const long index) const;

	// add a new candidate:
	void addCandidate(Candidate* newCandidate);

	// delete a candidate by index:
	void deleteCandidate(long index);

	// for merging candidate sets:
	CandidateSet& operator+=(const CandidateSet& rhs);

	// delete Partition objects from all contained candidates:
	void deletePartitions();
};

#endif