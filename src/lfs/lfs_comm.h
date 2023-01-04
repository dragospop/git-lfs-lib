#pragma once
#include <filesystem>
#include <vector>
#include <cpr/cprtypes.h>
#include "comm/comm_action.h"
#include "lfs_pointer.h"

namespace lfslib
{
	/// <summary>
	/// This class handles the comunication with a GitLfs server
	/// </summary>
	class GIT_LFS_LIB_DLL_EXPORT LfsComm
	{
	public:
		LfsComm();
		~LfsComm();

		LfsPointer upload(const std::filesystem::path& file);
		void download(const std::filesystem::path& file, const LfsPointer& ptr);
		void download(const std::filesystem::path& file, const std::string& oid, int64_t size);


	private:
		using CommObj = lfslib::comm::Object;
		using Batch = lfslib::comm::Batch;
		using Action = lfslib::comm::Action;

		void runBatch(const Batch& batch);
		std::vector<CommObj> sendBatch(const Batch& batch);
		void doActions(std::vector<CommObj>& objects);
		void downloadAction(const CommObj& obj);
		void uploadAction(const CommObj& obj);

	private:
		std::string url;
		std::unordered_map<LfsPointer, std::filesystem::path> ptrToFile;

		static const std::string contentType;
		static const cpr::Header stdHeader;
	};
}



