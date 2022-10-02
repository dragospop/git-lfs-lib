#pragma once
#include <string>
#include <gtest/gtest.h>
#include <git-lfs-lib/lfs_pointer.h>

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

TEST_F(LfsPointerTest, IFail) {

	ASSERT_EQ(0, 2);
}