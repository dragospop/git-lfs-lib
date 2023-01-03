#pragma once
#include <string>
#include "dll_export.h"

/// <summary>
/// Class repesenting a git lfs pointer
/// </summary>
class GIT_LFS_LIB_DLL_EXPORT LfsPointer
{
public:
	std::string oid;
	int64_t size = 0;

	std::string toString() const;
	static LfsPointer fromString(const std::string& rep);
};
