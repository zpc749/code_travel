// 定义红黑树节点
struct RBNode
{
    // 定义枚举, 节点颜色
    enum class Color {RED, BLACK};
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int value) : data(value), color(Color::RED), 
                        left(nullptr), right(nullptr), parent(nullptr) {}
    // 判断节点是红色还是黑色
    inline bool isRed() { return color == Color::RED; }
    inline bool isBlack() { return color == Color::BLACK; }
    // 设置节点颜色
    inline void setRed() { color = Color::RED; }
    inline void setBlack() { color = Color::BLACK; }
};

// 定义红黑树类
class RBTree
{
public:
    RBTree();
    ~RBTree();
    void buildTree();
    // 节点的插入
    void insert(int data);
    // 节点的删除
    void remove(int data);
    // 中序遍历
    void inorder();
    // 节点的颜色
    inline bool isBlack(RBNode* node)
    {
        return node == nullptr || node->isBlack();
    }
    inline bool isRed(RBNode* node)
    {
        return node != nullptr && node->isRed();
    }

private:
    enum class FindOP { Insert, Remove };
    // 左旋
    void leftRotate(RBNode* root);
    // 右旋
    void rightRotate(RBNode* root);
    // 插入修复
    void insertFixup(RBNode* root);
    // 删除修复
    void removeFixup(RBNode* root);
    // 节点迁移 n2->n1
    void transplant(RBNode* n1, RBNode* n2);
    // 根据数据找插入/删除位置
    RBNode* findPos(int data, FindOP op = FindOP::Insert);
    // 遍历
    void inorder(RBNode* root);
    void clear(RBNode* root);
private:
    RBNode* m_root; // 红黑树根节点
};

RBTree::RBTree() : m_root(nullptr)
{
}

RBTree::~RBTree()
{
    clear(m_root);
}

void RBTree::clear(RBNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    clear(root->left);
    clear(root->right);
    cout << "释放节点: " << root->data << endl;
    delete root;
}

void RBTree::leftRotate(RBNode* root)
{
    RBNode* rightChild = root->right;
    root->right = rightChild->left;
    if (rightChild->left != nullptr)
    {
        rightChild->left->parent = root;
    }

    rightChild->parent = root->parent;
    if (root->parent == nullptr)
    {
        m_root = rightChild;
    }
    else if (root == root->parent->left)
    {
        root->parent->left = rightChild;
    }
    else
    {
        root->parent->right = rightChild;
    }
    rightChild->left = root;
    root->parent = rightChild;
}

void RBTree::rightRotate(RBNode* root)
{
    RBNode* leftChild = root->left;
    root->left = leftChild->right;
    if (leftChild->right != nullptr)
    {
        leftChild->right->parent = root;
    }
    leftChild->parent = root->parent;
    if (root->parent == nullptr)
    {
        m_root = leftChild;
    }
    else if (root == root->parent->right)
    {
        root->parent->right = leftChild;
    }
    else
    {
        root->parent->left = leftChild;
    }
    leftChild->right = root;
    root->parent = leftChild;
}

RBNode* RBTree::findPos(int data, FindOP op)
{
    RBNode* parent = nullptr;
    RBNode* curNode = m_root;
    while (curNode != nullptr)
    {
        parent = curNode; 
        if (data < curNode->data)
        {
            curNode = curNode->left;  
        }
        else if (data > curNode->data)
        {
            curNode = curNode->right; 
        }
        else
        {
            return op == FindOP::Insert ? nullptr : curNode;
        }
    }

    return op == FindOP::Insert ? parent : nullptr;
}

void RBTree::insert(int data)
{
    RBNode* node = new RBNode(data);
    RBNode* parent = findPos(data);    
    node->parent = parent;
    if (parent == nullptr)
    {
        m_root = node;
    }
    else if (data < parent->data)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
    insertFixup(node);
}

void RBTree::insertFixup(RBNode* root)
{
    while (root->parent != nullptr && root->parent->isRed())
    {
        RBNode* grandpa = root->parent->parent;
        RBNode* uncle = nullptr;
        if (root->parent == grandpa->left)
        {
            uncle = grandpa->right;
        }
        else
        {
            uncle = grandpa->left;
        }

        if (uncle != nullptr && uncle->isRed())
        {
            root->parent->setBlack();
            uncle->setBlack();
            grandpa->setRed();
            root = grandpa; 
        }
        else
        {
            if (root->parent == grandpa->left && root == root->parent->right)
            {
                root = root->parent;
                leftRotate(root);
            }
            else if (root->parent == grandpa->right && root == root->parent->left)
            {
                root = root->parent;
                rightRotate(root);
            }

            root->parent->setBlack();
            grandpa->setRed();
            if (root->parent == grandpa->left)
            {
                rightRotate(grandpa);
            }
            else
            {
                leftRotate(grandpa);
            }
        }
    }
    m_root->setBlack();
}

void RBTree::transplant(RBNode* n1, RBNode* n2)
{
    if (n1->parent == nullptr)
    {
        m_root = n2;
    }
    else if (n1 == n1->parent->left)
    {
        n1->parent->left = n2;
    }
    else
    {
        n1->parent->right = n2;
    }
    if (n2 != nullptr)
    {
        n2->parent = n1->parent;
    }
}

void RBTree::remove(int data)
{
    if (m_root == nullptr)
    {
        return;
    }
    RBNode* curNode = findPos(data, FindOP::Remove);
    if (curNode == nullptr)
    {
        cout << "没有找到要删除的节点..." << endl;
        return;
    }

    if (curNode->left != nullptr && curNode->right != nullptr)
    {
        RBNode* preNode = curNode->left;
        while (preNode->right != nullptr)
        {
            preNode = preNode->right;
        }
        curNode->data = preNode->data;
        curNode = preNode; 
    }
    RBNode* child = curNode->left; 
    if (child == nullptr)
    {
        child = curNode->right;
    }
    if (child != nullptr)
    {
        transplant(curNode, child);
        RBNode::Color color = curNode->color;
        delete curNode;
        if (color == RBNode::Color::BLACK)
        {
            removeFixup(child); 
        }
    }
    else
    {
        if (curNode->parent == nullptr)
        {
            delete curNode;
            m_root = nullptr;
            return;
        }
        else
        {
            if (curNode->isBlack())
            {
                removeFixup(curNode);
            }
            transplant(curNode, nullptr);
            delete curNode;
        }
    }
}

void RBTree::removeFixup(RBNode* node)
{
    while (node != m_root && node->isBlack()) 
    {
        if (node == node->parent->left) 
        {
            RBNode* sibling = node->parent->right;
            if (isRed(sibling)) 
            {
                sibling->setBlack();
                node->parent->setRed();
                leftRotate(node->parent);
                sibling = node->parent->right;
            }
            if(isBlack(sibling->left) && isBlack(sibling->right))
            {
                sibling->setRed();
                node = node->parent;
            }
            else
            {
                if (isBlack(sibling->right))
                {
                    sibling->left->setBlack();
                    sibling->setRed();
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->setBlack();
                sibling->right->setBlack();
                leftRotate(node->parent);
                break;
            }
        }
        else 
        {
            RBNode* sibling = node->parent->left;
            if (isRed(sibling)) 
            {
                sibling->setBlack();
                node->parent->setRed();
                rightRotate(node->parent);
                sibling = node->parent->left;
            }
            if (isBlack(sibling->right) && isBlack(sibling->left)) 
            {
                sibling->setRed();
                node = node->parent;
            }
            else 
            {
                if (isBlack(sibling->left)) 
                {
                    sibling->right->setBlack();
                    sibling->setRed();
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->setBlack();
                sibling->left->setBlack();
                rightRotate(node->parent);
                break;
            }
        }
    }
    node->setBlack();
}
