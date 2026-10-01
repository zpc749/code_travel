struct TrieNode
{
    TrieNode(char c, int n) : ch(c), freq(n) {}
    char ch;
    int freq;    // frequence
    map<char, TrieNode*> children;
};

class TrieTree
{
public:
    TrieTree();
    ~TrieTree();
    void add(const string& word);
    void remove(const string& word);
    int query(const string& word);
    void preOrder();
    vector<string> queryPrefix(const string& prefix);

private:
    void deleteNodes(TrieNode* node);
    void preOrder(TrieNode* root, string& word, vector<string>& wordlist);
    TrieNode* remove(TrieNode* root, const string& word, int depth = 0);

private:
    TrieNode* m_root; 
};

TrieTree::TrieTree() : m_root(new TrieNode('\0', 0))
{
}

TrieTree::~TrieTree()
{
    if (m_root != nullptr)
    {
        deleteNodes(m_root);
    }
}

void TrieTree::deleteNodes(TrieNode* node)
{
    if (node == nullptr) return;
    for (auto& pair : node->children)
    {
        deleteNodes(pair.second);
    }
    delete node;
}

void TrieTree::add(const string& word)
{
    if (word.empty())
    {
        return; 
    }
    TrieNode* current = m_root; 
    for (const auto& ch : word)
    {
        auto it = current->children.find(ch);
        if (it == current->children.end())
        {
            current->children[ch] = new TrieNode(ch, 0);
        }
        current = current->children[ch];
    }
    current->freq++;
}

void TrieTree::remove(const string& word)
{
    remove(m_root, word);
}

TrieNode* TrieTree::remove(TrieNode* root, const string& word, int depth)
{
    if (!root)
    {
        return nullptr;
    }
    if (depth == word.length()) 
    {
        if (root->freq) 
        {
            root->freq = 0;
        }
        if (root->children.empty()) 
        {
            delete root;
            root = nullptr;
        }
        return root;
    }

    char ch = word[depth];
    root->children[ch] = remove(root->children[ch], word, depth + 1);
    if (root->children.empty() && root->freq < 1) 
    {
        delete root;
        root = nullptr;
    }
    return root;
}

void TrieTree::preOrder()
{
    string word;
    vector<string> wordList;
    preOrder(m_root, word, wordList);
    for (const auto& w : wordList)
    {
        cout << w << endl;
    }
    cout << endl;
}

void TrieTree::preOrder(TrieNode* root, string& word, vector<string>& wordlist)
{
    if (root == nullptr)
    {
        return;
    }

    if (root != m_root) 
    {
        word.push_back(root->ch);
        if (root->freq > 0)
        {
            wordlist.emplace_back(word);
        }
    }

    for (const auto& pair : root->children)
    {
        preOrder(pair.second, word, wordlist);
    }
    if (root != m_root)
    {
        word.pop_back();
    }
}

vector<string> TrieTree::queryPrefix(const string& prefix)
{
    if (prefix.empty())
    {
        return vector<string>();
    }

    TrieNode* cur = m_root;
    for (char ch : prefix)
    {
        auto childIt = cur->children.find(ch);
        if (childIt == cur->children.end())
        {
            return vector<string>();
        }
        cur = childIt->second;
    }
    
    vector<string> wordlist;
    string word(prefix, 0, prefix.size() - 1);
    preOrder(cur, word, wordlist);
    return wordlist;
}

int TrieTree::query(const string& word)
{
    if (word.empty())
    {
        return 0;
    }

    TrieNode* cur = m_root;
    for (char ch : word)
    {
        auto childIt = cur->children.find(ch);
        if (childIt == cur->children.end())
        {
            return 0; 
        }
        cur = childIt->second;
    }

    return cur->freq;
}
