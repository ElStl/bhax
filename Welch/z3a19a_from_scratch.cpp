// TODO Bátfai Norbert GNU GPL v3

#include <iostream>
#include <functional>
#include <random>
#include <chrono>

class Unirand {

    private:
        std::function <int()> random;

    public:
        Unirand(long seed, int min, int max): random(
            std::bind(
                std::uniform_int_distribution<>(min, max),
                std::default_random_engine(seed) 
            )
        ){}    

   int operator()(){return random();}
        
};

template <typename ValueType>
class BinRandTree {

protected:
	class Node {
        
    private:
		ValueType value;
		Node *left;
        Node *right;
        int count{0};
        
        // TODO rule of five
        Node(const Node &);
        Node & operator = (const Node &);
        Node(Node &&);
        Node & operator = (Node &&);
        
    public:
        Node(ValueType value, int count = 0): value(value), count(count), left(nullptr), right(nullptr) {}
        ValueType getValue()const {return value;}
        Node * leftChild()const {return left;}
        Node * rightChild()const {return right;}
        void leftChild(Node * node){left = node;}
        void rightChild(Node * node){right = node;}
        int getCount()const {return count;}
        void incCount(){++count;}
	};
    
    Node *root;
    Node *treep;
    int depth{0};

private:
    // TODO rule of five
    
    
public:
    BinRandTree(Node *root = nullptr, Node *treep = nullptr): root(root), treep(treep){
        std::cout << "BT ctor" << std::endl;
    }
    
    BinRandTree(const BinRandTree & old){
        std::cout << "BT copy ctor" << std::endl;
        
        root = cp(old.root, old.treep);

    }
    
    Node* cp(Node *node, Node *treep){
        
        Node *newNode = nullptr;
        
        if(node){
            
            newNode = new Node(node->getValue(), node->getCount());
            
            newNode->leftChild(cp(node->leftChild(), treep));
            newNode->rightChild(cp(node->rightChild(), treep));
            
            if(node == treep)
                this->treep = newNode;
        }
        
        return newNode;
        
    }


    BinRandTree & operator = (const BinRandTree & old){
        std::cout << "BT copy assign" << std::endl;
        
        BinRandTree tmp{old};
        std::swap(*this, tmp);
        return *this;

    }
    BinRandTree(BinRandTree && old){
        std::cout << "BT move ctor" << std::endl;

        root = nullptr;
        *this = std::move(old);
        
    }
    BinRandTree & operator = (BinRandTree && old){
        std::cout << "BT move assign" << std::endl;
        
        std::swap(old.root, root);
        std::swap(old.treep, treep);
        
        return *this;

    }
    ~BinRandTree(){
        std::cout << "BT dtor" << std::endl;

    deltree(root);
        
    }
    BinRandTree & operator <<(ValueType value);
    void print(){print(root, std::cout);}
    void printr(){print(*root, std::cout);}
    void print(Node *node, std::ostream & os);
    void print(const Node  &cnode, std::ostream & os);
    void deltree(Node *node);
    
    Unirand ur{std::chrono::system_clock::now().time_since_epoch().count(), 0, 2};
    
    int whereToPut(){
        
            return ur();
    }

};

template <typename ValueType>
class BinSearchTree : public BinRandTree<ValueType>{

public:
    BinSearchTree() {}
    BinSearchTree & operator <<(ValueType value);
    
};

template <typename ValueType, ValueType vr, ValueType v0>
class ZLWTree : public BinRandTree<ValueType>{

public:
    ZLWTree(): BinRandTree<ValueType>(new typename BinRandTree<ValueType>::Node(vr)) {
         this->treep = this->root;
    }
    ZLWTree & operator <<(ValueType value);
    
};

template <typename ValueType>
BinRandTree<ValueType> &BinRandTree<ValueType>::operator <<(ValueType value){
    
    int rnd = whereToPut();
    
    if(!treep){
        
        root = treep = new Node(value);
        
    }else if (treep->getValue() == value) {
        
        treep->incCount();
        
    }else if (!rnd) {

        treep = root;
        *this << value;
        
    }else if (rnd == 1) {
        
        if(!treep->leftChild()){
            
            treep->leftChild(new Node(value));
            
        }else{
            
            treep = treep->leftChild();
            *this << value;
        }
        
    }else if (rnd == 2) {
        
        if(!treep->rightChild()){
            
            treep->rightChild(new Node(value));
            
        }else{
            
            treep = treep->rightChild();
            *this << value;
        }
    }
    
    return *this;
}

template <typename ValueType>
BinSearchTree<ValueType> &BinSearchTree<ValueType>::operator <<(ValueType value){
    
    if(!this->treep){
        
        this->root = this->treep = new typename BinRandTree<ValueType>::Node(value);
        
    }else if (this->treep->getValue() == value) {
        
        this->treep->incCount();
        
    }else if (this->treep->getValue() > value) {
        
        if(!this->treep->leftChild()){
            
            this->treep->leftChild(new typename BinRandTree<ValueType>::Node(value));
            
        }else{
            
            this->treep = this->treep->leftChild();
            *this << value;
        }
        
    }else if (this->treep->getValue() > value) {
        
        if(!this->treep->rightChild()){
            
            this->treep->rightChild(new typename BinRandTree<ValueType>::Node(value));
            
        }else{
            
            this->treep = this->treep->rightChild();
            *this << value;
        }
    }
    
    this->treep = this->root;
    
    return *this;
}

template <typename ValueType, ValueType vr, ValueType v0>
    ZLWTree<ValueType, vr , v0> & ZLWTree<ValueType, vr , v0>::operator <<(ValueType value){
        
        if(value == v0){
            
            if(!this->treep->leftChild()){
                
                typename BinRandTree<ValueType>::Node * node = new typename BinRandTree<ValueType>::Node(value);
                this->treep->leftChild(node);
                this->treep = this->root;
                
            }else{
                
                this->treep = this->treep->leftChild();
                
            }
                
        }else{
            if(!this->treep->rightChild()){
                
                typename BinRandTree<ValueType>::Node * node = new typename BinRandTree<ValueType>::Node(value);
                this->treep->rightChild(node);
                this->treep = this->root;
                
            }else{
                
                this->treep = this->treep->rightChild();
                
            }
            
        }
        
        
        return *this;
    }
    
template <typename ValueType>
void BinRandTree<ValueType>::print(Node *node, std::ostream & os){
    
    if(node){
        
        ++depth;
        print(node->leftChild(), os);
        
        for(int i{0}; i<depth; ++i)
            os << "---";
            
        os << node->getValue() << " " << depth << " " << node->getCount() << std::endl;
        
        print(node->rightChild(), os);
        --depth;
    }
    
    
}

template <typename ValueType>
void BinRandTree<ValueType>::print(const Node &node, std::ostream & os){
    
        ++depth;
        if(node.leftChild())
            print(*node.leftChild(), os);
        
        for(int i{0}; i<depth; ++i)
            os << "---";
            
        os << node.getValue() << " " << depth << " " << node.getCount() << std::endl;
        
        if(node.rightChild())
            print(*node.rightChild(), os);

        --depth;
    
}
    

template <typename ValueType>
void BinRandTree<ValueType>::deltree(Node *node){
    
    if(node){
        
        deltree(node->leftChild());
        deltree(node->rightChild());
        delete node;
    }
    
    
}
    
int main(int argc, char** argv, char ** env)
{
    BinRandTree<int> bt;
    
    bt << 1 << 2 << 5 << 2 << 2 << 7 << 6 << 7 << 5 << 2;
    
    bt.print();
    
    BinRandTree<int> bt2(bt);
    
    bt2.print();
    std::cout << std::endl;
    bt2.printr();
    
/*
    std::cout << std::endl;
    
    ZLWTree<char, '/', '0' > zt;
    
    zt << '0'<<'1'<<'0'<<'0'<<'0'<<'1'<<'1';
    
    zt.print();
    
    ZLWTree<char, '/', '0'> zt2{zt};
    
    ZLWTree<char, '/', '0'> zt3;

    zt3 << '1'<<'1'<<'1'<<'1'<<'1';
    
    std::cout << "***" << std::endl;
    zt = zt3;
    std::cout << "***" << std::endl;
    
    ZLWTree<char, '/', '0'> zt4 = std::move(zt2);
    
    BinSearchTree<std::string> bts;
    
    bts << "alma" << "korte" << "banan" << "korte";
    
    bts.print();
*/    
};

