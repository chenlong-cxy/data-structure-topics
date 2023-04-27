#include "UnionFindSet.h"

int main() {
	UnionFindSet ufs(10);
	ufs.unionSet(0, 6);
	ufs.unionSet(0, 7);
	ufs.unionSet(0, 8);

	ufs.unionSet(1, 4);
	ufs.unionSet(1, 9);

	ufs.unionSet(2, 3);
	ufs.unionSet(2, 5);

	//ufs.unionSet(8, 1);
	ufs.unionSet(1, 8);

	//ufs.unionSet(2, 1);
	ufs.print();
	//ufs.findRoot(4);
	//ufs.print();
	//ufs.findRoot(9);
	//ufs.print();

	//vector<string> v = { "张三", "李四", "王五", "赵六", "田七", "周八", "吴九" };
	//UnionFindSet<string> ufs(v);
	//cout << ufs.getNum() << endl;
	//ufs.unionSet("张三", "李四");
	//ufs.unionSet("王五", "赵六");
	//cout << ufs.getNum() << endl;
	//ufs.unionSet("张三", "赵六");
	//cout << ufs.getNum() << endl;

	return 0;
}
