#include "lfs_comm.h"
#include "sha256.h"
#include <fstream>

LfsComm::LfsComm()
{
}

LfsComm::~LfsComm()
{
}

LfsPointer LfsComm::upload(const std::filesystem::path& file)
{
    if (std::ifstream is{ file, std::ios::binary | std::ios::ate }) {
        auto size = is.tellg();
        std::string str(size, '\0'); // construct string to stream size
        is.seekg(0);
        if (is.read(&str[0], size))
        {
            SHA256 sha256;
        }
    }

	return LfsPointer();
}

void LfsComm::download(const std::filesystem::path& file, const LfsPointer& ptr)
{
}

void LfsComm::download(const std::filesystem::path& file, const std::string& oid, int64_t size)
{
}
