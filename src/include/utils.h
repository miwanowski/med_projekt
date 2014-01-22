/*
* Helper utilities.
*/

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

void printArrayRepresentation(std::vector<long>* ar);

void printAttributeList(std::vector<int> al);

#endif