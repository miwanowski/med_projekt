#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "fun.h"
#include "utils.h"
#include "candidate.h"
#include "candidateset.h"

Partition* Fun::product(Partition* a, Partition* b) {
	Partition* c = new Partition(a->getTableSize());
	ArrayRepresentation* t = a->getArrayRepresentation();
	std::vector<Group*> s = std::vector<Group*>(a->getTableSize());

	for (long groupId = 0; groupId < b->getGroupCount(); ++groupId) {
		Group* group = b->getGroup(groupId);
		Group aGroupIds;
		for (Group::const_iterator it = group->begin(); it != group->end(); ++it) {
			long j = (*t)[*it];
			if (s[j] == NULL)
				s[j] = new Group();
			s[j]->insert(*it);
			aGroupIds.insert(j);
		}
		for (Group::const_iterator it = aGroupIds.begin(); it != aGroupIds.end(); ++it) {
			c->addGroup(s[*it]);
			s[*it] = NULL;
		}
	}
	delete t;
	return c;
}

bool Fun::holds(Candidate* c, Partition* d) {
	ArrayRepresentation* t = d->getArrayRepresentation();
	Partition* cp = c->getPartition();
	for (long groupId = 0; groupId < cp->getGroupCount(); ++groupId) {
		Group* group = cp->getGroup(groupId);
		Group::const_iterator it = group->begin();
		long firstGroup = (*t)[*it];
		++it;
		for (; it != group->end(); ++it) {
			if (firstGroup != (*t)[*it]) {
				delete t;
				return false;
			}
		}
	}
	delete t;
	return true;
}

void Fun::generateInitialCandidates(const std::string& dataFilePath, 	// path to data file
									const AttributeIds aIds,			// list of attribute Ids
									const AttributeId targetId,			// target attribute Id
									CandidateSet* cs,					// return: candidate set
									Partition* targetPartition) {		// return: target partition
	std::ifstream dataFile (dataFilePath.c_str());
	if (dataFile.is_open()) {
		std::string headerLine;
		std::getline(dataFile, headerLine);
		std::vector<std::string> splitHeader = split(headerLine, ',');
		for (AttributeIds::const_iterator it = aIds.begin(); it != aIds.end(); ++it) {
			Candidate* newCandidate = new Candidate(new Partition());
			Candidate::AttributeList* newAttributeList = new Candidate::AttributeList();
			newAttributeList->push_back(splitHeader[*it]);
			newCandidate->setAttributeList(newAttributeList);
			cs->addCandidate(newCandidate);
		}
		std::string line;
		std::vector<std::vector<std::string> > attributeLevels;
		// initialize the vector of vectors of levels:
		for (AttributeIds::const_iterator it = aIds.begin(); it != aIds.end(); ++it) {
			attributeLevels.push_back(std::vector<std::string>());
		}
		std::vector<std::string> targetLevels;
		long dataLines = 0;
		while (std::getline(dataFile, line)) {
			dataLines++;
			//std::cout << "parsing line: " << line << std::endl;
			std::vector<std::string> splitLine = split(line, ',');
			long instanceId;
			std::istringstream ss(splitLine[0]);
			ss >> instanceId;
			// update attribute partitions:
			for (AttributeIds::const_iterator it = aIds.begin(); it != aIds.end(); ++it) {
				int attNo = it - aIds.begin();
				int attCol = *it;
				//std::cout << "parsing attribute " << attNo << " with column " << attCol << std::endl;
				// find if the current attribute value is already among attribute levels:
				std::vector<std::string>::iterator l = std::find(attributeLevels[attNo].begin(),
																 attributeLevels[attNo].end(),
																 splitLine[attCol]);
				if (l == attributeLevels[attNo].end()) {
					attributeLevels[attNo].push_back(splitLine[attCol]);
					Group* newGroup = new Group();
					newGroup->insert(instanceId);
					(*cs)[attNo]->getPartition()->addGroup(newGroup);
				} else {
					int groupId = l - attributeLevels[attNo].begin();
					(*cs)[attNo]->getPartition()->getGroup(groupId)->insert(instanceId);
				}
			}
			// update target attribute partition:
			std::vector<std::string>::iterator l = std::find(targetLevels.begin(),
															 targetLevels.end(),
															 splitLine[targetId]);
			if (l == targetLevels.end()) {
				targetLevels.push_back(splitLine[targetId]);
				Group* newGroup = new Group();
				newGroup->insert(instanceId);
				targetPartition->addGroup(newGroup);
			} else {
				int groupId = l - targetLevels.begin();
				targetPartition->getGroup(groupId)->insert(instanceId);
			}
		}
		for (int i=0; i < cs->getSize(); ++i) {
			(*cs)[i]->getPartition()->setTableSize(dataLines);
		}
		targetPartition->setTableSize(dataLines);
		dataFile.close();
	} else {
		std::cout << "Unable to open the requested file." << std::endl;
	}
}

// main method:
CandidateSet Fun::fun(const std::string& dataFilePath, 	// path to data file
					  const AttributeIds aIds,			// list of attribute Ids
					  const AttributeId targetId		// target attribute Id
					 ) {
	CandidateSet* c1 = new CandidateSet();
	Partition* d = new Partition();
	generateInitialCandidates(dataFilePath, aIds, targetId, c1, d);
	std::vector<CandidateSet*> candidateSets;
	std::vector<CandidateSet*> resultSets;
	candidateSets.push_back(c1);
	// main loop:
	for (int k=1; candidateSets[k-1]->getSize() != 0; ++k) {
		resultSets.push_back(new CandidateSet());
		for (int i=0; i < candidateSets[k-1]->getSize(); ++i) {
			if (holds( (*candidateSets[k-1])[i], d) ) {
				resultSets[k-1]->addCandidate((*candidateSets[k-1])[i]);
				candidateSets[k-1]->deleteCandidate(i);
			}
		}
		candidateSets.push_back(funGen(candidateSets[k-1]));
	}
	// merge result sets:
	CandidateSet resultSet;
	for (int i=0; i < resultSets.size(); ++i) {
		resultSet += *resultSets[i];
	}
	return resultSet;
}

CandidateSet* Fun::funGen(CandidateSet* ck) {
	// @TODO
	return new CandidateSet();
}