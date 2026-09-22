// 图的存储

// 1.邻接矩阵（无权无向图）
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;                    // 输入：顶点数 边数
    vector<vector<int>> adj(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    cout << "邻接矩阵：" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << adj[i][j] << " ";
        cout << endl;
    }
    return 0;
}


// 2.邻接表
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;                       // 顶点数 边数
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "邻接表：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (int v : adj[i]) cout << v << " ";
        cout << endl;
    }
    return 0;
}


// 3.十字链表
#include <iostream>
#include <vector>
using namespace std;

struct ArcNode {
    int tailVex;         // 起点
    int headVex;         // 终点
    int weight;          // 权值
    ArcNode* hlink;      // 入边链（相同终点）
    ArcNode* tlink;      // 出边链（相同起点）

    ArcNode(int t, int h, int w)
        : tailVex(t), headVex(h), weight(w), hlink(nullptr), tlink(nullptr) {}
};

struct VNode {
    int data;            // 顶点信息
    ArcNode* firstIn;    // 第一条入边
    ArcNode* firstOut;   // 第一条出边

    VNode() : data(0), firstIn(nullptr), firstOut(nullptr) {}
};

class OrthogonalList {
private:
    vector<VNode> vertices;  // 顶点数组

public:
    // 初始化 n 个顶点
    OrthogonalList(int n) : vertices(n) {
        for (int i = 0; i < n; ++i) vertices[i].data = i;
    }

    // 添加有向弧 tail -> head，权值 w
    void addArc(int tail, int head, int w = 1) {
        ArcNode* arc = new ArcNode(tail, head, w);

        // 1. 插入到 tail 的出边链（头插法）
        arc->tlink = vertices[tail].firstOut;
        vertices[tail].firstOut = arc;

        // 2. 插入到 head 的入边链（头插法）
        arc->hlink = vertices[head].firstIn;
        vertices[head].firstIn = arc;
    }

    // 打印所有顶点的出边
    void printOutEdges() {
        cout << "所有出边：" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << i << " 的出边: ";
            for (ArcNode* p = vertices[i].firstOut; p; p = p->tlink) {
                cout << "(" << p->tailVex << "->" << p->headVex
                     << ", w=" << p->weight << ") ";
            }
            cout << endl;
        }
    }

    // 打印所有顶点的入边
    void printInEdges() {
        cout << "所有入边：" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << i << " 的入边: ";
            for (ArcNode* p = vertices[i].firstIn; p; p = p->hlink) {
                cout << "(" << p->tailVex << "->" << p->headVex
                     << ", w=" << p->weight << ") ";
            }
            cout << endl;
        }
    }

    // 释放内存
    ~OrthogonalList() {
        for (int i = 0; i < vertices.size(); ++i) {
            ArcNode* p = vertices[i].firstOut;
            while (p) {
                ArcNode* next = p->tlink;
                delete p;
                p = next;
            }
        }
    }
};

int main() {
    int n = 4;  // 顶点数
    OrthogonalList graph(n);

    // 添加有向边
    graph.addArc(0, 1, 5);
    graph.addArc(0, 2, 3);
    graph.addArc(1, 2, 2);
    graph.addArc(2, 3, 4);
    graph.addArc(3, 1, 1);

    graph.printOutEdges();
    cout << endl;
    graph.printInEdges();

    return 0;
}


// 4.邻接多重表
#include <iostream>
#include <vector>
using namespace std;

struct EdgeNode {
    int mark;           // 访问标记
    int ivex, jvex;     // 两个顶点下标
    int weight;         // 权值
    EdgeNode* ilink;    // 依附于 ivex 的下一条边
    EdgeNode* jlink;    // 依附于 jvex 的下一条边

    EdgeNode(int i, int j, int w = 1)
        : mark(0), ivex(i), jvex(j), weight(w),
          ilink(nullptr), jlink(nullptr) {}
};

struct VNode {
    int data;
    EdgeNode* firstEdge;

    VNode() : data(0), firstEdge(nullptr) {}
};

class AdjacencyMultilist {
private:
    vector<VNode> vertices;
    vector<EdgeNode*> allEdges;   // 记录所有边结点，方便统一释放

public:
    // 初始化 n 个顶点
    AdjacencyMultilist(int n) : vertices(n) {
        for (int i = 0; i < n; ++i) vertices[i].data = i;
    }

    // 添加无向边 u - v，权值 w
    void addEdge(int u, int v, int w = 1) {
        EdgeNode* edge = new EdgeNode(u, v, w);
        allEdges.push_back(edge);

        // 插入到 u 的边链表（通过 ilink 链接）
        edge->ilink = vertices[u].firstEdge;
        vertices[u].firstEdge = edge;

        // 插入到 v 的边链表（通过 jlink 链接）
        edge->jlink = vertices[v].firstEdge;
        vertices[v].firstEdge = edge;
    }

    // 遍历顶点 u 的所有邻边
    void printNeighbors(int u) {
        cout << u << " 的邻边: ";
        for (EdgeNode* p = vertices[u].firstEdge; p; ) {
            if (p->ivex == u) {
                cout << p->jvex << " ";
                p = p->ilink;      // 当前边以 u 为 ivex，走 ilink
            } else {
                cout << p->ivex << " ";
                p = p->jlink;      // 当前边以 u 为 jvex，走 jlink
            }
        }
        cout << endl;
    }

    // 打印所有边（避免重复，只打印 ivex < jvex 的边）
    void printAllEdges() {
        cout << "所有边：" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            for (EdgeNode* p = vertices[i].firstEdge; p; ) {
                if (p->ivex == i && p->ivex < p->jvex) {
                    cout << "(" << p->ivex << " - " << p->jvex
                         << ", w=" << p->weight << ") ";
                }
                if (p->ivex == i) p = p->ilink;
                else p = p->jlink;
            }
        }
        cout << endl;
    }

    // 析构：释放所有边结点
    ~AdjacencyMultilist() {
        for (EdgeNode* e : allEdges) delete e;
    }
};

int main() {
    int n = 5;
    AdjacencyMultilist graph(n);

    // 添加无向边
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 4);
    graph.addEdge(3, 4, 1);
    graph.addEdge(1, 4, 6);

    // 遍历各顶点的邻边
    for (int i = 0; i < n; ++i) graph.printNeighbors(i);

    cout << endl;
    graph.printAllEdges();

    return 0;
}


// 5.边集数组
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;   // 起点、终点、权值
    bool operator<(const Edge& other) const {
        return w < other.w;   // 按权值升序，Kruskal 需要
    }
};

vector<Edge> edges;   // 边集数组
// 有向边 u -> v
void addDirectedEdge(int u, int v, int w) {
    edges.push_back({u, v, w});
}

// 无向边 u - v（存两次，适合 Bellman-Ford 等需要双向松弛的算法）
void addUndirectedEdgeDouble(int u, int v, int w) {
    edges.push_back({u, v, w});
    edges.push_back({v, u, w});
}

// 无向边 u - v（只存一次，适合 Kruskal，因为并查集不关心方向）
void addUndirectedEdgeSingle(int u, int v, int w) {
    edges.push_back({u, v, w});
}
for (const auto& e : edges) {
    cout << e.u << " -> " << e.v << "，权值 " << e.w << endl;
}
