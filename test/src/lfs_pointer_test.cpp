#include <string>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <git-lfs-lib/lfs_pointer.h>

namespace fs = std::filesystem;

class LfsPointerTest : public ::testing::Test
{
//public:
//	std::string oid;
//	int64_t size = 0;
//
//	std::string toString() const;
//	static LfsPointer fromString(const std::string& rep);
};

TEST_F(LfsPointerTest, toString) {
	LfsPointer p{ .oid = "4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393", .size = 1234 };

	std::string s = p.toString();
	std::string expected = "version https://git-lfs.github.com/spec/v1\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 1234\n\n";

	ASSERT_EQ(expected, s);
}

TEST_F(LfsPointerTest, fromString) {
	std::string s1 = "version https://git-lfs.github.com/spec/v1\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 12345\n";

	std::string s2 = "version https://git-lfs.github.com/spec/v1\r\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\r\n"
		"size 12345\r\n";

	std::string s3 = "version https://git-lfs.github.com/spec/v1\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 12345";


	std::string s4= "version https://git-lfs.github.com/spec/v1\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 12345\n\n";


	auto lfsPtr1 = LfsPointer::fromString(s1);

	ASSERT_EQ("4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393", lfsPtr1.oid);
	ASSERT_EQ(12345, lfsPtr1.size);

	auto lfsPtr2 = LfsPointer::fromString(s2);

	ASSERT_EQ("4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393", lfsPtr2.oid);
	ASSERT_EQ(12345, lfsPtr2.size);

	auto lfsPtr3 = LfsPointer::fromString(s3);

	ASSERT_EQ("4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393", lfsPtr3.oid);
	ASSERT_EQ(12345, lfsPtr3.size);

	auto lfsPtr4 = LfsPointer::fromString(s4);

	ASSERT_EQ("4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393", lfsPtr4.oid);
	ASSERT_EQ(12345, lfsPtr4.size);


}

TEST_F(LfsPointerTest, fromString_badFormat) {
	// bad no version
	std::string bad1 =
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 12345\n\n";

	// bad oid should be sha256 not sha2
	std::string bad2 = "version https://git-lfs.github.com/spec/v1\n"
		"oid sha2:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n"
		"size 12345\n\n";

	// bad no oid
	std::string bad3 = "version https://git-lfs.github.com/spec/v1\n"
		"size 12345\n\n";

	// bad no size
	std::string bad4 = "version https://git-lfs.github.com/spec/v1\n"
		"oid sha256:4d7a214614ab2935c943f9e0ff69d22eadbb8f32b1258daaa5e2ca24d17e2393\n";

	ASSERT_THROW(LfsPointer::fromString(bad1), std::runtime_error);
	ASSERT_THROW(LfsPointer::fromString(bad2), std::runtime_error);
	ASSERT_THROW(LfsPointer::fromString(bad3), std::runtime_error);
	ASSERT_THROW(LfsPointer::fromString(bad4), std::runtime_error);
}

TEST_F(LfsPointerTest, getPointer) 
{
	auto tempDir = fs::temp_directory_path();
	auto tempTestDir = tempDir / "LfsLibTest" / "LfsPointerTest";
	auto tempFile = tempTestDir / "getPointer.txt";

	fs::create_directories(tempTestDir);

	int fileSize = 0;

	if (fs::exists(tempFile))
		fs::remove(tempFile);

	{
		std::ofstream ofile(tempFile, std::ios::binary);
		int n = 0x41424344;
		fileSize += sizeof(n) + 1;
		ofile.write(reinterpret_cast<char*>(&n), sizeof(n)) << '\n';

		char c[] = "This is sample text.\n";
		ofile.write(c, sizeof(c) ).write("!\n", 2);
		fileSize += sizeof(c) + 2;
	}

	auto ptr = LfsPointer::getPointer(tempFile);


	ASSERT_EQ(fileSize, ptr.size);
	ASSERT_EQ(256 / 4, ptr.oid.size()); // total bits = 256; hex = 4
	ASSERT_EQ("087a02044a1299a0ffa1eb40001a724991fd8a8723c1d3928a8f15dedfa73e3a", ptr.oid);
}

TEST_F(LfsPointerTest, IFail) {

	ASSERT_EQ(0, 2);
}