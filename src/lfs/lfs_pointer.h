#pragma once
#include <string>
#include <filesystem>
#include <functional>
#include "dll_export.h"

/// <summary>
/// Class repesenting a git lfs pointer
/// </summary>
class GIT_LFS_LIB_DLL_EXPORT LfsPointer
{
public:
	std::string oid;
	int64_t size = 0;

	bool operator==(const LfsPointer& other) const
	{
		return this->oid == other.oid && this->size == other.size;
	}

	std::string toString() const;
	static LfsPointer fromString(const std::string& rep);

	static LfsPointer getPointer(const std::filesystem::path& file);
};

namespace std {
	template <>
	struct hash<LfsPointer> {
		auto operator()(const LfsPointer& p) const -> size_t {
			return std::hash<std::string>{}(p.oid) ^ std::hash<int64_t>{}(p.size);
		}
	};
}  // namespace std