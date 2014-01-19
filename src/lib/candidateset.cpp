#include <iostream>

#include "candidateset.h"

// get the number of candidates in the set:
long CandidateSet::getSize() const {
	return candidateList_.size();
}

// access candidates by index:
Candidate* CandidateSet::operator[] (const long index) const {
	return candidateList_[index];
}

// add a new candidate:
void CandidateSet::addCandidate(Candidate* newCandidate) {
	candidateList_.push_back(newCandidate);
}

// delete a candidate by index:
void CandidateSet::deleteCandidate(long index) {
	candidateList_.erase(candidateList_.begin() + index);
}

// for merging candidate sets:
CandidateSet& CandidateSet::operator+=(const CandidateSet& rhs) {
	for (int i=0; i < rhs.getSize(); ++i) {
		addCandidate(rhs[i]);
	}
	return *this;
}

// delete Partition objects from all contained candidates:
void  CandidateSet::deletePartitions() {
	for (int i=0; i < getSize(); ++i) {
		delete candidateList_[i]->getPartition();
		candidateList_[i]->setPartition(NULL);
	}
}