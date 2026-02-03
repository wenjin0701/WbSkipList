#include <List>
#include <iostream>
#include <stack>
#include <random>

template <typename Key, typename Value>
class SkipNode {
public:
    SkipNode(Key key, Value value) 
        : key_(key)
        , value_(value)
    {}
    Key getKey() const { return key_; }
    Value getValue() const {return value_; }
    void setValue(const Value& value) { value_ = value; }
    friend class SkipList<Key, Value>;
private:
    Key key_;
    Value value_;
    std::shard_ptr<SkipNode<Key, Value>> next_;
    std::weak_ptr<SkipNode<Key, Value>> prev_;
    std::weak_ptr<SkipNode<Key, Value>> up_;
    std::shard_ptr<SkipNode<Key, Value>> down_;
};

template <typename Key, typename Value>
class SkipList {
    using SkipNodeType = SkipNode<Key, Value>;
    using SkipNodePtr = std::shared_pt<SkipNodeType>;

    SkipList() {
        headNode_ = std::make_shared<SkipNodeType>(Key(), Value());
        maxLevel_ = 0;
    }
    SkipNodePtr getNode(Key key) {
        auto node = headNode_;
        while (node) {
            if (node->getKey() == key) {
                return node;
            } else if (node->next_ == nullptr || node->next_->getKey() > key) {
                node = node->down_;
            } else {
                node = node->next_;
            }
        }
        return nullptr;
    }
    void deleteNode(Key key) {
        SkipNodePtr node = headNode_;
        while (node) {
            if (node->getKey() == key) {
                node->next_ = node->next_->next_;
                node = node->down_;
            } else if (node->next_ == nullptr || node->next_->getKey() > key) {
                node = node->down_;
            } else {
                node = node->next_;
            }
        }
    }
    void insertNode(Key key, Value value) {
        if (getNode(key) != nullptr) {
            getNode(key)->setValue(value);
            return;
        }

        std::stack<SkipNodePtr> stack = new std::stack<SkipNodePtr>();
        SkipNodePtr node = headNode_;
        while (node) {
            if (node->next_ == nullptr || node->next_->getKey() > key) {
                stack.push(node);
                node = node->down_;
            } else {
                node = node->next_;
            }
        }
        int level = 1;
        SkipNodePtr down_node = nullptr;
        while (!stack.empty()) {
            node = stack.pop();
            SkipNodePtr newNode = std::make_shared<SkipNodeType>(key, value);
            newNode->down_ = down_node;
            down_node = newNode;
            if (node->next_ == nullptr) {
                node->next_ = newNode;
            } else {
                newNode->next_ = node->next;
                node->next_ = newNode;
            }
            if (level > MAX_LEVEL) {
                break;
            }
            double rand = random_.nextDouble();
            if (rand > 0.5) {
                level++;
            }
            if (level > maxLevel_) {
                maxLevel_ = level;;
                SkipNodePtr newHeadNode = std::make_shared<SkipNodeType>(Key(), Value());
                newHeadNode->down_ = headNode_;
                headNode_ = newHeadNode;
                stack.push(headNode_);
            }
        }
    }
private:
    SkipNodePtr headNode_;
    int maxLevel_;
    Random random_ = Random();
    const int MAX_LEVEL = 32;
};

int main() {
    SkipList<int, int> skipList;
    skipList.insertNode(1, 1);
    skipList.insertNode(2, 2);
    skipList.insertNode(3, 3);
    std::cout << "The value of key 2 is: " << skipList.getNode(2)->getValue() << std::endl;
    return 0;
}