#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int singleNumber1(vector<int>& nums) {
		int ret = 0;
		//通过范围for遍历容器，逐个异或
		for (auto e : nums)
		{
			ret ^= e;
		}
		return ret; //返回异或后的结果
	}
	int singleNumber2(vector<int>& nums) {
		int ret = 0;
		for (int i = 0; i < 32; i++) //int类型有32个比特位
		{
			int total = 0;
			//遍历nums，统计nums中第i个比特位为1的元素个数
			for (auto e : nums)
			{
				total += ((e >> i) & 1);
			}
			//如果第i个比特位为1的元素个数不能被3整除
			//则说明只出现一次的数字的这一比特位为1
			if (total % 3 != 0)
			{
				ret |= (1 << i); //将ret的第i个比特位设置为1
			}
		}
		return ret; //返回只出现一次的数字
	}
	vector<int> singleNumber3(vector<int>& nums) {
		//1、遍历数组nums，对数组中的所有元素进行异或
		int ret = 0;
		for (auto e : nums)
		{
			ret ^= e;
		}

		//2、找出ret当中任意一个不为0的比特位（这里从低位到高位进行查找）
		int index = 0;
		while (((ret >> index) & 1) == 0)
		{
			index++;
		}

		//3、将nums数组中第index个比特位为1和不为1的数字分组进行异或
		int a = 0, b = 0;
		for (auto e : nums)
		{
			if ((e >> index) & 1) //第index个比特位为1的数字
			{
				a ^= e;
			}
			else //第index个比特位不为1的数字
			{
				b ^= e;
			}
		}

		//4、将这两个只出现一次的数字放到容器v当中进行返回
		vector<int> v;
		v.push_back(a);
		v.push_back(b);
		return v;
	}
	int singleNumber4(vector<int>& nums, int k) {
		int ret = 0;
		for (int i = 0; i < 32; i++) //int类型有32个比特位
		{
			int total = 0;
			//遍历nums，统计nums中第i个比特位为1的元素个数
			for (auto e : nums)
			{
				total += ((e >> i) & 1);
			}
			//如果第i个比特位为1的元素个数不能被3整除
			//则说明只出现一次的数字的这一比特位为1
			if (total % k != 0)
			{
				ret |= (1 << i); //将ret的第i个比特位设置为1
			}
		}
		return ret; //返回只出现一次的数字
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