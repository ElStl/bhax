#include <iostream>
using namespace std;
template <typename ValueType>
class BinTree {

protected:
    class Node {
        
    private:
        ValueType value;
        Node *left;
        Node *right;
        int count=0;
        
        // TODO rule of five
        Node(const Node &);
        Node & operator=(const Node &);
        Node(Node &&);
        Node & operator=(Node &&);
        
    public:
        Node(ValueType value): value(value), left(nullptr), right(nullptr) {}
        ValueType getValue(){return value;}
        Node * leftChild(){return left;}
        Node * rightChild(){return right;}
        void leftChild(Node * node){left = node;}
        void rightChild(Node * node){right = node;}
        int getCount(){return count;}
        void incCount(){++count;}        
    };

    Node *root;
    Node *treep;    
    int depth=0;
    
private:     
    
    
public:
    BinTree(Node *root = nullptr, Node *treep = nullptr): root(root), treep(treep) {
cout<<"BT ctor "<<endl;
	}
    BinTree(const BinTree & old){
	cout<<"BT copy ctor "<<endl;
		root = cp(old.root, old.treep);
		}
		Node * cp(Node *node,Node *treep)
		{
                    Node* newNode = nullptr;
                    if(node){
		    	newNode = new Node(node->getValue());		
                    	newNode->leftChild(cp(node->leftChild(),treep));
			newNode->rightChild(cp(node->rightChild(),treep));
			if(node == treep)
				this->treep=newNode;
			}
		
	return newNode;
		}
       
    BinTree & operator=(const BinTree & old){
cout<<"BT copy assign "<<endl;
        
		BinTree tmp{old};
		swap(*this,tmp);
		return * this;

	}
    BinTree(BinTree && old){
cout<<"BT move ctor "<<endl;
	root=nullptr;
	*this =move(old);

	
        }
    BinTree & operator=(BinTree && old){
cout<<"BT move assign "<<endl;
    
	swap(old.root,root);
	swap(old.treep,treep);
	return *this;


    }

    ~BinTree(){
	cout<<"BT dtor"<<endl;
        deltree(root);
    }
    BinTree & operator<<(ValueType value);
    void print(){print(root,cout);}
    void print(Node *node, ostream & os);
    void printfa(){printfa(root,cout);}
    void printfa(Node *node,ostream & os);
    void inorderprint(){inorderprint(root,cout);}
    void inorderprint(Node *node,ostream & os);
    void postorderprint(){postorderprint(root,cout);}
    void postorderprint(Node *node,ostream & os);
    void deltree(Node *node); 

};

template <typename ValueType>
class ZLWTree : public BinTree<ValueType> {

public:
    ZLWTree(): BinTree<ValueType>(new typename BinTree<ValueType>::Node('/')) {
        this->treep = this->root;
    }
    ZLWTree & operator<<(ValueType value);
    
    
};

template <typename ValueType>
BinTree<ValueType> & BinTree<ValueType>::operator<<(ValueType value)
{
    if(!treep) {

        root = treep = new Node(value);

    } else if (treep->getValue() == value) {

        treep->incCount();

    } else if (treep->getValue() > value) {

        if(!treep->leftChild()) {

            treep->leftChild(new Node(value));

        } else {

            treep = treep->leftChild();
            *this << value;
        }

    } else if (treep->getValue() < value) {

        if(!treep->rightChild()) {

            treep->rightChild(new Node(value));

        } else {

            treep = treep->rightChild();
            *this << value;
        }

    }

    treep = root;

    return *this;
}


template <typename ValueType>
ZLWTree<ValueType> & ZLWTree<ValueType>::operator<<(ValueType value)
{
    
    if(value == '0') {
        
        if(!this->treep->leftChild()) {
            
            typename BinTree<ValueType>::Node * node = new typename BinTree<ValueType>::Node(value);
            this->treep->leftChild(node);
            this->treep = this->root;
            
        } else {
            
            this->treep = this->treep->leftChild(); 
        }
        
    } else {

        if(!this->treep->rightChild()) {
            
            typename BinTree<ValueType>::Node * node = new typename BinTree<ValueType>::Node(value);
            this->treep->rightChild(node);
            this->treep = this->root;
            
        } else {
            
            this->treep = this->treep->rightChild(); 
        }
        
    }
    
    return *this;
}

template <typename ValueType>
void BinTree<ValueType>::print(Node *node, ostream & os) 
{
    if(node)
    {
        ++depth;
        print(node->leftChild(), os);
        
        for(int i=0; i<depth; ++i)
            os << "---";            
        os << node->getValue() << " " << depth << " " << node->getCount() << endl;     
        
        print(node->rightChild(), os);
        --depth;
    }
    
}
template <typename ValueType>
void BinTree<ValueType>::printfa(Node *node,ostream & os)
{

	
	if(node==nullptr)
    		return;
	os<<node->getValue()<<" ";
	printfa(node->leftChild(),os);
	printfa(node->rightChild(),os);
	
		
}
template <typename ValueType>
void BinTree<ValueType>::inorderprint(Node *node,ostream & os)
{


        if(node==nullptr)
                return;
        
        inorderprint(node->leftChild(),os);
        os<<node->getValue()<<" ";
	inorderprint(node->rightChild(),os);


}
template <typename ValueType>
void BinTree<ValueType>::postorderprint(Node *node,ostream & os)
{


        if(node==nullptr)
                return;

        postorderprint(node->leftChild(),os);
        postorderprint(node->rightChild(),os);
        os<<node->getValue()<<" ";


} 		


template <typename ValueType>
void BinTree<ValueType>::deltree(Node *node) 
{
    if(node)
    {
        deltree(node->leftChild());
        deltree(node->rightChild());
        
        delete node;
    }
    
}


int main(int argc, char** argv, char ** env)
{
    BinTree<int> bt;
    
    bt << 8 << 9 << 5 << 2 << 7;
    
    bt.print();
    
    cout << endl;

    ZLWTree<char> zt;

    zt <<'0'<<'1'<<'1'<<'1'<<'1'<<'0'<<'0'<<'1'<<'0'<<'0'<<'1'<<'0'<<'0'<<'1'<<'0'<<'0'<<'0'<<'1'<<'1'<<'1';
    
    zt.print();
    ZLWTree<char> zt2{zt};

    ZLWTree<char> zt3;
    zt3<<'1'<<'1'<<'1'<<'1'<<'1';
    cout<<"!***!"<<endl;
    zt=zt3;
    cout<<"!***!"<<endl;
    ZLWTree<char> zt4 = move(zt2);
    cout<<"preorder bejaras:\n";
    zt3.printfa();
    cout<<endl;
    bt.printfa();
    cout<<endl;
    cout<<"inorder bejaras:\n";
    zt3.inorderprint();
    cout<<endl;
    bt.inorderprint();
    cout<<endl;
    cout<<"postorder bejaras:\n";
    zt3.postorderprint();
    cout<<endl;
    bt.postorderprint();
    cout<<endl;
}
