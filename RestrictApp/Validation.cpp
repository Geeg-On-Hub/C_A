#include "Validation.h"

bool IsWithinRootFolder(const std::string& path, const std::string& rootFolder) {
    return path.find(rootFolder) == 0; // Returns true if the path starts with rootFolder
}

bool IsOutsideRootFolder(const std::string& path, const std::string& rootFolder) {
    return path.find(rootFolder) != 0; // Returns true if the path does not start with rootFolder
}
