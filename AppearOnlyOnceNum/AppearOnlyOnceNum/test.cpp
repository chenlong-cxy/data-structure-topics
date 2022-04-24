#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int singleNumber1(vector<int>& nums) {
		int ret = 0;
		//ͨ����Χfor����������������
		for (auto e : nums)
		{
			ret ^= e;
		}
		return ret; //��������Ľ��
	}
	int singleNumber2(vector<int>& nums) {
		int ret = 0;
		for (int i = 0; i < 32; i++) //int������32������λ
		{
			int total = 0;
			//����nums��ͳ��nums�е�i������λΪ1��Ԫ�ظ���
			for (auto e : nums)
			{
				total += ((e >> i) & 1);
			}
			//�����i������λΪ1��Ԫ�ظ������ܱ�3����
			//��˵��ֻ����һ�ε����ֵ���һ����λΪ1
			if (total % 3 != 0)
			{
				ret |= (1 << i); //��ret�ĵ�i������λ����Ϊ1
			}
		}
		return ret; //����ֻ����һ�ε�����
	}
	vector<int> singleNumber3(vector<int>& nums) {
		//1����������nums���������е�����Ԫ�ؽ������
		int ret = 0;
		for (auto e : nums)
		{
			ret ^= e;
		}

		//2���ҳ�ret��������һ����Ϊ0�ı���λ������ӵ�λ����λ���в��ң�
		int index = 0;
		while (((ret >> index) & 1) == 0)
		{
			index++;
		}

		//3����nums�����е�index������λΪ1�Ͳ�Ϊ1�����ַ���������
		int a = 0, b = 0;
		for (auto e : nums)
		{
			if ((e >> index) & 1) //��index������λΪ1������
			{
				a ^= e;
			}
			else //��index������λ��Ϊ1������
			{
				b ^= e;
			}
		}

		//4����������ֻ����һ�ε����ַŵ�����v���н��з���
		vector<int> v;
		v.push_back(a);
		v.push_back(b);
		return v;
	}
	int singleNumber4(vector<int>& nums, int k) {
		int ret = 0;
		for (int i = 0; i < 32; i++) //int������32������λ
		{
			int total = 0;
			//����nums��ͳ��nums�е�i������λΪ1��Ԫ�ظ���
			for (auto e : nums)
			{
				total += ((e >> i) & 1);
			}
			//�����i������λΪ1��Ԫ�ظ������ܱ�3����
			//��˵��ֻ����һ�ε����ֵ���һ����λΪ1
			if (total % k != 0)
			{
				ret |= (1 << i); //��ret�ĵ�i������λ����Ϊ1
			}
		}
		return ret; //����ֻ����һ�ε�����
	}
};

int main()
{
	vector<int> v{ 1, 2, 1, 3, 2, 5 };
	vector<int> ret = Solution().singleNumber3(v);
	for (auto e : ret)
	{
		cout << e << " ";
	}
	cout << endl;
	return 0;
}