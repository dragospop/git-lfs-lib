#include <string>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>
#include "../lfs_pointer.h"

namespace lfslib::comm
{
	using json = nlohmann::json;

	

	struct Batch
	{
		std::string operation;
		std::string ref;
		std::vector<LfsPointer> objects;
	};

	struct Action
	{
		static const std::string download;
		static const std::string upload;

		std::string operation;
		std::string url;
		std::map<std::string, std::string> headers;

		bool isEmpty() const
		{
			return operation.empty();
		}
	};

	struct Object
	{
		LfsPointer ptr;
		Action action;
		bool authenticated;
	};

	/// <summary>
	/// converts LfsPointer to json
	/// </summary>
	/// <param name="j"></param>
	/// <param name="ptr"></param>
	inline void to_json(json& j, const LfsPointer& ptr) {
		j = json{ {"oid", ptr.oid}, {"size", ptr.size} };
	}

	inline void to_json(json& j, const std::vector<LfsPointer>& v) {
		std::vector<json> jv;
		jv.reserve(v.size());
		for (const auto& o : v)
		{
			jv.emplace_back(json{ {"oid", o.oid}, {"size", o.size} });
		}

		j = jv;
	}

	/// <summary>
	///  // POST https://lfs-server.com/objects/batch
	///  // Accept: application/vnd.git-lfs+json
	///  // Content-Type: application/vnd.git-lfs+json
	///  // Authorization: Basic ... (if needed)
	///  {
	///    "operation": "download",
	///    "transfers": [ "basic" ],
	///    "ref": { "name": "refs/heads/main" },
	///    "objects": [
	///      {
	///        "oid": "12345678",
	///        "size": 123
	///      }
	///    ],
	///    "hash_algo": "sha256"
	///  }
	/// 
	/// 
	/// </summary>
	/// <param name="j"></param>
	/// <param name="b"></param>
	inline void to_json(json& j, const Batch& b) {
		json jobjects;
		to_json(jobjects, b.objects);

		j = json{ {"operation", b.operation}, {"transfers", std::array<std::string, 1> {"basic"}}, {"objects", jobjects}, {"hash_algo", "sha256"} };

		if (!b.ref.empty())
			j["ref"] = b.ref;
	}



	/// <summary>
	///  {
	///   "transfer": "basic",
	///   "objects": [
	///     {
	///       "oid": "1111111",
	///       "size": 123,
	///       "authenticated": true,
	///       "actions": {
	///         "download": {
	///           "href": "https://some-download.com",
	///           "header": {
	///             "Key": "value"
	///           },
	///           "expires_at": "2016-11-10T15:29:07Z"
	///         }
	///       }
	///     }
	///   ],
	///   "hash_algo": "sha256"
	///  }
	/// 
	/// 
	/// </summary>
	/// <param name="j"></param>
	/// <param name="b"></param>
	inline void from_json(const json& j, Object& obj)
	{
		j["oid"].get_to(obj.ptr.oid);
		j["size"].get_to(obj.ptr.size);
		j["authenticated"].get_to(obj.authenticated);

		if (j.contains("actions"))
		{
			auto jactions = j["actions"];
			bool hasAction = false;
			

			if (jactions.contains(Action::download))
			{
				obj.action.operation = Action::download;
				hasAction = true;
			}

			if (j.contains(Action::upload))
			{
				obj.action.operation = Action::upload;
				hasAction = true;
			}

			if (hasAction) 
			{
				j["headers"].get_to(obj.action.headers);
				j["href"].get_to(obj.action.url);
			}
			else
			{
				obj.action = Action{};
			}
		}
	}
}
