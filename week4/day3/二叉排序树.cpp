// bstree.hpp
template<typename T, typename CompFunc = less<T>>
class BST
{
public:
    struct Node
    {
        Node(T value = T()) : data(value), left(nullptr), right(nullptr) {}
        T data;         // 数据域
        Node* left;     // 左孩子
        Node* right;    // 右孩子
    };
    // 类成员函数
    BST(CompFunc comp = CompFunc());
    ~BST();
    // 非递归
    void insertNormal(const T& value);
    void removeNormal(const T& value);
    Node* queryNormal(const T& value);
    // 递归
    void insert(const T& value);
    void remove(const T& value);
    Node* query(const T& value);
    // 递归中序遍历二叉树
    void inorder();

private:    
    // 内部接口
    // 递归中序遍历二叉树
    void inorder(Node* root);
    Node* insert(Node* root, const T& value);
    Node* remove(Node* root, const T& value);
    Node* query(Node* root, const T& value);
    // 释放树节点
    void clear(Node* root);

private:
    Node* m_root;       // 根节点
    CompFunc m_comp;    // 函数对象(可调用对象)
};
