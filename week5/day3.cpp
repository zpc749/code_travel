// 环形链表2（142）
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        // 第一阶段：找相遇点
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
            // 相遇了
            if(slow == fast){
                slow = head;        // slow回到头
                // 第二阶段：同速前进
                while(slow != fast){
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow; // 相遇就是入环点
            }
        }
        return nullptr; // 无环
    }
};


// 两数相加（2）
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1); // 虚拟头
        ListNode* cur = dummy;
        int carry = 0; // 进位
        
        while(l1 != nullptr || l2 != nullptr || carry != 0){
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            
            carry = sum / 10;        // 更新进位
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        return dummy->next;
    }
};


// 删除链表的倒数第N个结点（19）
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 创建一个虚拟头节点，dummyhead->next 指向 head
        ListNode* dummyhead = new ListNode(0, head);

        // 初始化两个指针，起始位置都指向 dummyhead
        ListNode* fast = dummyhead;
        ListNode* slow = dummyhead;

        // 将 fast 指针向前移动 n+1 步，以便 fast 和 slow 指针之间始终隔 n 个节点
        for (int i = 0; i < n + 1; i++) {
            fast = fast->next;
        }

        // 同时移动 fast 和 slow，直到 fast 到达链表末尾
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // 此时 slow 指向待删除节点的前一个节点
        slow->next = slow->next->next;

        // 返回删除节点后的链表
        return dummyhead->next;
    }
};


// 两两交换链表中的节点（24）
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* cur = head;

        // 要有一对可以交换：cur和cur->next都不为空
        while(cur != nullptr && cur->next != nullptr){
            ListNode* next = cur->next;

            // 三步交换
            pre->next = next;
            cur->next = next->next;
            next->next = cur;

            // 指针后移，准备下一组
            pre = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};


// K个一组翻转链表（25）
class Solution {
public:
    // 翻转 [head, tail] 区间，返回新头
    ListNode* reverse(ListNode* head, ListNode* tail) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(pre != tail) { // 到tail就停（包含tail）
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy;

        while(true) {
            // 检查有没有k个
            ListNode* end = pre;
            for(int i = 0; i < k && end; i++) end = end->next;
            if(!end) break; // 不够k个，结束

            ListNode* start = pre->next;
            ListNode* nextGroup = end->next;

            // 翻转当前组
            ListNode* newHead = reverse(start, end);
            // 拼接
            pre->next = newHead;
            start->next = nextGroup;

            // pre走到本组新尾（原来的start）
            pre = start;
        }
        return dummy->next;
    }
};


// 随机链表的复制（138）
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;
        Node* cur = head;
        // 第一步：创建所有新节点，建立映射
        while(cur) {
            mp[cur] = new Node(cur->val);
            cur = cur->next;
        }
        // 第二步：补 next、random
        cur = head;
        while(cur) {
            mp[cur]->next = mp[cur->next];   // cur->next为空时 mp[]自动取null
            mp[cur]->random = mp[cur->random];
            cur = cur->next;
        }
        return mp[head];
    }
};


// 排序链表（148）
class Solution {
public:
    // LeetCode21：合并两个有序链表
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;
        while(l1 && l2){
            if(l1->val < l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy->next;
    }

    ListNode* sortList(ListNode* head) {
        // 边界：空 / 只有1个节点，本身有序
        if(!head || !head->next) return head;

        // 快慢指针找中点
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* preMid = nullptr; // 用来断开中点前面
        while(fast && fast->next){
            preMid = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        preMid->next = nullptr; // ！！断开左右链，非常关键

        ListNode* left = sortList(head);
        ListNode* right = sortList(slow);
        return merge(left, right);
    }
};


// 合并K个升序链表（23）
class Solution {
public:
    // 就是 LeetCode21：合并两条有序链表
    ListNode* mergeTwo(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;
        while(l1 && l2) {
            if(l1->val < l2->val) {
                cur->next = l1; l1 = l1->next;
            } else {
                cur->next = l2; l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy->next;
    }

    // 分治：合并 [l, r] 区间内的链表
    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        if(l == r) return lists[l];
        if(l > r) return nullptr;
        int mid = (l + r) / 2;
        ListNode* left = merge(lists, l, mid);
        ListNode* right = merge(lists, mid+1, r);
        return mergeTwo(left, right);
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size()-1);
    }
};


// LRU缓存（146）
class LRUCache {
private:
    int cap;
    // list< pair<key,val> >：头=最近，尾=最久
    list<pair<int,int>> l;
    unordered_map<int, list<pair<int,int>>::iterator> mp;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(mp.find(key) == mp.end()) return -1;
        // 取到节点，移到表头
        auto it = mp[key];
        int val = it->second;
        l.erase(it);               // 删除旧位置
        l.push_front({key, val}); // 插到头部
        mp[key] = l.begin();      // 更新迭代器
        return val;
    }
    
    void put(int key, int value) {
        // 已存在：更新+移头
        if(mp.count(key)){
            auto it = mp[key];
            l.erase(it);
            l.push_front({key, value});
            mp[key] = l.begin();
            return;
        }
        // 不存在：新节点
        if(l.size() >= cap){
            // 删除尾部（最久未用）
            int delKey = l.back().first;
            l.pop_back();
            mp.erase(delKey);
        }
        l.push_front({key, value});
        mp[key] = l.begin();
    }
};
