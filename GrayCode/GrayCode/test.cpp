#include <iostream>
#include <string>
using namespace std;

//二进制码转格雷码
string BinaryToGray(string binary)
{
	string gray(binary.size(), '0');
	//1、保留二进制码的最高位作为格雷码的最高位
	gray[0] = binary[0];
	//2、格雷码的其余位为二进制码对应位与其上一位相异或
	for (size_t i = 1; i < gray.size(); i++)
	{
		gray[i] = (binary[i - 1] - '0') ^ (binary[i] - '0') + '0';
	}
	return gray;
}

//格雷码转二进制码
string GrayToBinary(string gray)
{
	string binary(gray.size(), '0');
	//1、保留格雷码的最高位作为二进制码的最高位
	binary[0] = gray[0];
	//2、二进制码的其余位为格雷码对应位与二进制码上一位相异或
	for (size_t i = 1; i < gray.size(); i++)
	{
		binary[i] = (binary[i - 1] - '0') ^ (gray[i] - '0') + '0';
	}
	return binary;
}

int main()
{
	cout << BinaryToGray("1111") << endl;
	cout << GrayToBinary("1111") << endl;
	return 0;
}