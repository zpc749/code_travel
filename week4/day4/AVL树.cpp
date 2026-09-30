struct AVLNode 
{
    int val;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

// AVL 树
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    bool insert(int value);
    bool remove(int value);
    void inorder();
    
private:
    int height(AVLNode* root);
    int balance(AVLNode* root);
    AVLNode* rightRotate(AVLNode* root);
    AVLNode* leftRotate(AVLNode* root);
    AVLNode* rotate(AVLNode* root);
    void inorder(AVLNode* root);
    AVLNode* insert(AVLNode* root, int value);
    AVLNode* remove(AVLNode* root, int value);

private:
    // 根节点
    AVLNode* m_root;
};

AVLTree::AVLTree() : m_root(nullptr)
{
}

AVLTree::~AVLTree()
{
    clear(m_root);
}

void AVLTree::clear(AVLNode* root)
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

int AVLTree::height(AVLNode* root)
{
    return root ? root->height : 0;
}

int AVLTree::balance(AVLNode* root)
{
    return root ? height(root->left) - height(root->right) : 0;
}

AVLNode* AVLTree::leftRotate(AVLNode* root)
{
    AVLNode* right = root->right;
    AVLNode* child = right->left;
    right->left = root;
    root->right = child;
    root->height = std::max(height(root->left), height(root->right)) + 1;
    right->height = std::max(height(right->left), height(right->right)) + 1;
    return right; 
}

AVLNode* AVLTree::rightRotate(AVLNode* root)
{
    AVLNode* left = root->left;
    AVLNode* child = left->right;
    left->right = root;
    root->left = child;
    root->height = std::max(height(root->left), height(root->right)) + 1;
    left->height = std::max(height(left->left), height(left->right)) + 1;
    return left; 
}

AVLNode* AVLTree::rotate(AVLNode* root)
{
    int curBalance = balance(root);
    if (curBalance > 1 && balance(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (curBalance > 1 && balance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (curBalance < -1 && balance(root->right) <= 0)
    {
        return leftRotate(root);
    }
    if (curBalance < -1 && balance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

bool AVLTree::insert(int value)
{
    m_root = insert(m_root, value);
    return m_root != nullptr;
}

AVLNode* AVLTree::insert(AVLNode* root, int value)
{
    // 空树
    if (root == nullptr)
    {
        return new AVLNode(value);
    }
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        return root;
    }
    root->height = std::max(height(root->left), height(root->right)) + 1;
    return rotate(root);
}

bool AVLTree::remove(int value)
{
    return remove(m_root, value);
}

AVLNode* AVLTree::remove(AVLNode* root, int value)
{
    if (root == nullptr)
    {
        return root;
    }
    if (value < root->data)
    {
        root->left = remove(root->left, value); 
    }
    else if (value > root->data)
    {
        root->right = remove(root->right, value); 
    }
    else  
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            AVLNode* node = root->left ? root->left : root->right;
            if (node == nullptr)
            {
                node = root;
                root = nullptr;
            }
            else
            {
                *root = *node;
            }
            delete node;
        }
        else
        {
            AVLNode* current = root->right;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            root->data = current->data;
            root->right = remove(root->right, current->data);
        }
    }
    if (root == nullptr)
    {
        return root;
    }
    root->height = std::max(height(root->left), height(root->right)) + 1;
    return rotate(root);
}

void AVLTree::inorder(AVLNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
