// 江科大21年校赛--糖果（1433）
#include <iostream>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		scanf("%d", &n);

		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < n; i++)
		{
			int tmp;
			scanf("%d", &tmp);
			if (tmp == 1)
				cnt1++;
			else
				cnt2++;
		}

		if (cnt1 % 2 == 1)
		{
			cout << "NO" << endl;
		}
		else if (cnt1 > 0)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}

	return 0;
}
