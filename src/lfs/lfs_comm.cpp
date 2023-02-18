#include "lfs_comm.h"
#include "sha256.h"
#include <fstream>
#include <stdexcept>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace lfslib;

const std::string LfsComm::contentType{ "application/vnd.git-lfs+json" };
const cpr::Header LfsComm::stdHeader{ {"Content-Type", LfsComm::contentType}, {"Accept", LfsComm::contentType} };

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

    json toSend{ batch };

    cpr::Response r = cpr::Post(cpr::Url{ url + "/objects/batch" },
        cpr::Body{ toSend.dump() },
        LfsComm::stdHeader);

    json res = json::parse(r.text);

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
    cpr::Header header(LfsComm::stdHeader);
    if (!obj.action.headers.empty())
    {
        header.insert(obj.action.headers.begin(), obj.action.headers.end());
    }

    if (!ptrToFile.contains(obj.ptr))
        throw std::runtime_error("Lfs Upload: Pointer file not found");

    const auto& filePath = ptrToFile[obj.ptr];

    std::ofstream os{ filePath, std::ios::binary };
    if (!os)
    {
        throw std::runtime_error("Lfs Upload: could not read input file");
    }

    cpr::Response r = cpr::Download(os, cpr::Url{ obj.action.url }, header);
}

void LfsComm::uploadAction(const LfsComm::CommObj& obj)
{
    cpr::Header header(LfsComm::stdHeader);
    if (!obj.action.headers.empty())
    {
        header.insert(obj.action.headers.begin(), obj.action.headers.end());
    }

    if (!ptrToFile.contains(obj.ptr))
        throw std::runtime_error("Lfs Upload: Pointer file not found");

    const auto& filePath = ptrToFile[obj.ptr];

    std::ifstream is{ filePath, std::ios::binary | std::ios::ate };
    if (!is)
    {
        throw std::runtime_error("Lfs Upload: could not read input file");
    }

    auto fileSize = is.tellg();
    std::string str(fileSize, '\0'); // construct string to stream size
    is.seekg(0);
    if (is.read(&str[0], fileSize))
    {
        cpr::Response r = cpr::Post(cpr::Url{ obj.action.url },
            cpr::Body{ str },
            header);
    }
    else
    {
        throw std::runtime_error("Coulld not read file");
    }
    
}
