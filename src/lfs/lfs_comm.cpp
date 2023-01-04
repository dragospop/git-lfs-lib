#include "lfs_comm.h"
#include "sha256.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace lfslib;

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


void lfslib::LfsComm::runBatch(const Batch& batch)
{
    auto objs = sendBatch(batch);
    doActions(objs);
}


std::vector<LfsComm::CommObj> LfsComm::sendBatch(const Batch& batch)
{
    using json = nlohmann::json;
    json res;

    if (res.contains("transfer"))
        if (res["transfer"].get<std::string>() != "basic")
            throw std::runtime_error("unsupported transfer");

    if (res.contains("hash_algo"))
        if (res["hash_algo"].get<std::string>() != "sha256")
            throw std::runtime_error("unsupported hash algo");

    return res.at("objects").get<std::vector<LfsComm::CommObj>>();
}

void lfslib::LfsComm::doActions(std::vector<CommObj>& objects)
{
    for (const auto& o : objects)
    {
        if (!o.action.isEmpty())
        {
            if (o.action.operation == Action::download)
            {
                downloadAction(o);
            }
            else if (o.action.operation == Action::upload)
            {
                uploadAction(o);
            }
        }
    }
}

void LfsComm::downloadAction(const LfsComm::CommObj& obj)
{

}

void LfsComm::uploadAction(const LfsComm::CommObj& obj)
{

}
