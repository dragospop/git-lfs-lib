#include "lfs_pointer.h"
#include <stdexcept>
#include <ranges>
#include <vector>
#include <sstream>
#include <optional>
#include <charconv>

#include "string_utils.h"

//template<class T>
//constexpr std::optional<T> to_int(const std::string_view& input)
//{
//	std::stoi(input);
//	T out;
//	const std::from_chars_result result = std::from_chars(input.data(), input.data() + input.size(), out);
//	if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range)
//	{
//		return std::nullopt;
//	}
//	return out;
//}

std::vector<std::string_view> split(const std::string_view& s, char delimiter)
{
	std::vector<std::string_view> output;
	//output.reserve(strv.length() / 4);
	auto first = s.begin();

	while (first != s.end())
	{
		const auto second = std::find(first, std::cend(s), delimiter);
		//std::cout << first << ", " << second << '\n';
		if (first != second)
		{
			output.emplace_back(s.substr(std::distance(s.begin(), first), std::distance(first, second)));
		}

		if (second == s.end())
			break;

		first = std::next(second);
	}

	return output;
}


std::string LfsPointer::toString() const
{
	std::string content("version https://git-lfs.github.com/spec/v1\noid sha256:");
	content += this->oid + '\n';
	content += "size " + std::to_string(this->size) + "\n\n";
	return content;
}






LfsPointer LfsPointer::fromString(const std::string& rep)
{
	// example:
	// version https://git-lfs.github.com/spec/v1
	// oid sha256 : 4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393
	// size 12345

	constexpr size_t shaHeadLength = std::char_traits<char>::length("sha256:");
	
	static const std::string_view line1("version https://git-lfs.github.com/spec/v1\n");
	const std::string normalLineEnd = string_replace(rep, "\r\n", "\n");
	std::string_view repView(normalLineEnd);

	// Check that the pointer starts with the correct line
	if (!repView.starts_with(line1))
		throw std::runtime_error("Pointe file format is incorrect");

	repView.remove_prefix(line1.size());
	auto lines = split(repView, '\n');

	bool foundOid = false;
	bool foundSize = false;
	LfsPointer lfsPoiner;

	for (const auto& line : lines)
	{
		auto spacePos = line.find(' ');
		if (spacePos != line.npos)
		{
			auto token0 = line.substr(0, spacePos);
			auto token1 = line.substr(spacePos + 1);

			if (token0 == "oid")
			{
				if (!token1.starts_with("sha256:"))
					throw std::runtime_error("Unsupported hash function for oid, only sha256 is supportedS");

				lfsPoiner.oid = token1.substr(shaHeadLength);
				foundOid = true;
			}

			if (token0 == "size")
			{
				lfsPoiner.size = std::stoll(token1.data());
				foundSize = true;
			}
		}
		
	}

	if (!(foundOid && foundSize))
		throw std::runtime_error("File does not look like a lfs pointer");

	return lfsPoiner;
}
