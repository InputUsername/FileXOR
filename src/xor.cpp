#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<char> read_bytes(std::string);
std::vector<char> bytes_xor(std::vector<char>, std::vector<char>);

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		std::cout << "Usage: " << argv[0] << " <in> <key> <out>" << std::endl;
		return 1;
	}
	else
	{
		std::vector<char> bytes = read_bytes(argv[1]);
		
		std::string key_s(argv[2]);
		std::vector<char> key(key_s.begin(), key_s.end());

		std::vector<char> encrypted = bytes_xor(bytes, key);
		std::string encrypted_s(encrypted.begin(), encrypted.end());
		
		std::ofstream ofs(argv[3], std::ofstream::binary);
		ofs.write(encrypted_s.c_str(), encrypted_s.length());
		ofs.close();
	}

	return 0;
}

std::vector<char> read_bytes(std::string filename)
{
	std::ifstream ifs(filename, std::ifstream::binary | std::ifstream::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	ifs.close();

	return result;
}

std::vector<char> bytes_xor(std::vector<char> bytes, std::vector<char> key)
{
	const int bytesLen = bytes.size();
	const int keyLen = key.size();
	int bytesPos = 0, keyPos = 0;

	std::vector<char> result(bytesLen);

	char b, k;

	for (bytesPos = 0; bytesPos < bytesLen; bytesPos++)
	{
		b = bytes[bytesPos];
		k = key[keyPos];

		result[bytesPos] = b ^ k;

		keyPos++;
		keyPos %= keyLen;
	}

	return result;
}
