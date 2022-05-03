#include <iostream>
#include <string>
using namespace std;

//��������ת������
string BinaryToGray(string binary)
{
	string gray(binary.size(), '0');
	//1������������������λ��Ϊ����������λ
	gray[0] = binary[0];
	//2�������������λΪ���������Ӧλ������һλ�����
	for (size_t i = 1; i < gray.size(); i++)
	{
		gray[i] = (binary[i - 1] - '0') ^ (binary[i] - '0') + '0';
	}
	return gray;
}

//������ת��������
string GrayToBinary(string gray)
{
	string binary(gray.size(), '0');
	//1����������������λ��Ϊ������������λ
	binary[0] = gray[0];
	//2���������������λΪ�������Ӧλ�����������һλ�����
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