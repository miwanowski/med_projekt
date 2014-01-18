#include <iostream>

#include "candidateset.h"

// get the number of candidates in the set:
long CandidateSet::getSize() const {
	return candidateList_.size();
}

// access candidates by index:
Candidate* CandidateSet::operator[] (const long index) {
	return candidateList_[index];
}

// add a new candidate:
void CandidateSet::addCandidate(Candidate* newCandidate) {
	candidateList_.push_back(newCandidate);
}