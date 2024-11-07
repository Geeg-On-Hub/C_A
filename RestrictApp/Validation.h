#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

// Function to check if the path is within the restricted folder
bool IsWithinRootFolder(const std::string& path, const std::string& rootFolder);

// Function to check if the path is outside the restricted folder
bool IsOutsideRootFolder(const std::string& path, const std::string& rootFolder);

#endif // VALIDATION_H
