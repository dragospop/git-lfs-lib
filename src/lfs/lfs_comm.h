#pragma once
#include <filesystem>
#include "../../include/git-lfs-lib/lfs_pointer.h"

/// <summary>
/// This class handles the comunication with a GitLfs server
/// </summary>
class LfsComm
{
public:
	LfsComm();
	~LfsComm();

	LfsPointer upload(const std::filesystem::path & file);
	void download(const std::filesystem::path& file, const LfsPointer& ptr );
	void download(const std::filesystem::path& file, const std::string& oid, int64_t size);
	

private:

};


