#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// 2.可怜的小企鹅
bool cmp(int num1, int num2)
{
	return num1 > num2;
}
void q2()
{
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;
		vec[i] = tmp;
	}
	sort(vec.begin(), vec.end(), cmp);
	//sort(vec.begin(), vec.end(), greater<int>());
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += vec[i - 1] * i;
	}
	cout << sum;
}
// 3.最有希望的一年
void q3()
{
	int n;
	cin >> n;
	string s;
	cin >> s;

	vector<int> dp(n);
	dp[0] = 1;
	for (int i = 1; i < n; i++)
	{
		if (s[i] == s[i - 1])
		{
			dp[i] = dp[i - 1];
		}
		else
		{
			dp[i] = dp[i - 1] + 1;
		}
	}
	cout << dp[n - 1];
}
// 4.最喜欢破冰活动了
void q4()
{
	int n, m;
	cin >> n >> m;
	vector<int> nums1((n + 1) * n / 2);
	vector<int> nums2(m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			nums1.push_back(j);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int tmp;
		cin >> tmp;
		nums2[i] = tmp;
	}
	int count = 0;
	for (int i = 0; i < nums1.size(); i++)
	{
		if (nums1[i] == nums2[0])
		{
			int j;
			for (j = 1; j < m; j++)
			{
				if (nums1[j + i] != nums2[j])
					break;
			}
			if (j == m) count++;
		}
	}
	cout << count;
}
// 5.互相交流的蜜蜂
void q5()
{
	int n, d;
	cin >> n >> d;
	vector<int> coordinates(n);
	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;
		coordinates[i] = tmp;
	}
	int count = 0;
	int left = 0, right = 1;
	while (right < n)
	{
		if (right == left && coordinates[right+1] - coordinates[right] > d)
		{
			right = right + 2;
			left++;
		}
		else if (right == left)
		{
			right++;
		}

		if (coordinates[right] - coordinates[left] <= d)
		{
			count++;
			right++;
		}
		else
		{
			right--;
			left++;
		}
	}
	cout << count;
}
// 6.穿越洞穴
void q6()
{
	int N, a, b;
	cin >> N >> a >> b;
	vector<int> vec(N+1);
	for (int i = 1; i <= N; i++)
	{
		int k;
		cin >> k;
		vec[i] = k;
	}
	vector<int> dist(N + 1, -1);
	queue<int> q;
	dist[a] = 0;
	q.push(a);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (u == b) break; // 提前找到终点可以跳出

		int jump = vec[u];
		// 向后跳 u-jump
		int v1 = u - jump;
		if (v1 >= 1 && dist[v1] == -1)
		{
			dist[v1] = dist[u] + 1;
			q.push(v1);
		}
		// 向前跳 u+jump
		int v2 = u + jump;
		if (v2 <= N && dist[v2] == -1)
		{
			dist[v2] = dist[u] + 1;
			q.push(v2);
		}
	}
	cout << dist[b];
}
// 7.格斗哈拉
void q7()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, m, k;
		cin >> n >> m >> k;

		int R = (n - 1) / m + 1;        //总行数
		int last = n - (R - 1) * m;     //最后一行个数

		// k的坐标 rk,ck
		int rk = (k - 1) / m + 1;
		int ck = (k - 1) % m + 1;

		// 行代价：环形上下
		int dr = abs(1 - rk);
		int cost_r = min(dr, R - dr);

		// 列代价：本行内环形左右
		int len_c;
		if (rk == R) len_c = last;
		else len_c = m;
		int dc = abs(1 - ck);
		int cost_c = min(dc, len_c - dc);

		cout << cost_r + cost_c;
	}
}
// 8.树上守卫战
void q8()
{
	int T; cin >> T;
	while (T--)
	{
		int n; cin >> n;
		vector<vector<int>> adj(n + 1);
		for (int i = 0; i < n - 1; i++)
		{
			int u, v; cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		// BFS求根1的最大深度（边数）
		vector<int> dep(n + 1, 0);
		vector<int> fa(n + 1, -1);
		queue<int> q;
		q.push(1);
		dep[1] = 0;
		int maxd = 0;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			maxd = max(maxd, dep[u]);
			for (int ne : adj[u])
			{
				if (ne != fa[u])
				{
					fa[ne] = u;
					dep[ne] = dep[u] + 1;
					q.push(ne);
				}
			}
		}
		if (maxd == 1) cout << "YES\n";
		else cout << "NO\n";
	}
}
int main()
{
	//q2();
	//q3();
	//q4();
	//q5();
	//q6();
	//q7();
	//q8();
	return 0;
}
