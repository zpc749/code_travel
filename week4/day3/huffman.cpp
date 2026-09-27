struct HuffmanNode
{
    char data;
    int freq;   // 数据出现的频率（权值）
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// 定义霍夫曼树
class HuffmanTree
{
public:
    HuffmanTree(const string& data);
    ~HuffmanTree();

    string encode();
    string decode(const string& encodeStr);
private:
    void buildTree(const string& data);
    bool encode(HuffmanNode* root, string& code, unordered_map<char, string>& huffmanCode);
    bool decode(HuffmanNode* root, int& index, const string& encodeStr, string& decodeStr);
    void clear(HuffmanNode* root);

private:
    string m_data;
    HuffmanNode* m_root;
    struct Compare
    {
        bool operator()(HuffmanNode* n1, HuffmanNode* n2)
        {
            return n1->freq > n2->freq;
        }
    };
};
