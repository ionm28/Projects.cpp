#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

class Node{
       public:
        int value;
        Node* left;
        Node* right;
        Node(int key){
            value=key;
            left=right=nullptr;
        }
        ~Node();
};

class BST{
    public:
        BST();
       ~BST();
        void insertKey(int newKey);
        std::vector<int> inOrder();
        int getHeight();
        void prettyPrint();
        void init();
        void Levels();
        void Print();
    private:
        Node* insertKeyPrivate(int key, Node* priv);
        void inOrderPrivate(Node* priv, std::vector<int> &v);
        int getHeightPrivate(Node* priv);
       void addToMatrixPrivate(Node* priv, int lvl, int pozLine, std::vector<std::vector<int>>&matrix, int &checkZero, int &x, int &y);
         Node* root;
         std::vector<std::vector<int>>matrix;
         int checkZero=0,x,y;
};

void BST::Print(){
    int sizeLine=getHeight();
    int sizeCol=inOrder().size();
    int i,j;
    for(i=0;i<sizeLine;i++){
        for(j=0;j<sizeCol;j++)
            std::cout<<matrix.at(i).at(j);
        std::cout<<std::endl;
    }
}

void BST::prettyPrint(){
    if(getHeight()>0){
     int sizeLine=getHeight();
    int sizeCol=inOrder().size();
    int i,j;
    std::string convert;
    std::cout<<std::setfill('-')<<std::setw(4*sizeCol+sizeCol+1)<<""<<std::endl;
    for(i=0;i<sizeLine;i++){
        std::cout<<'|';
        std::cout<<std::setfill(' ');
        for(j=0;j<sizeCol-1;j++)
            if(x==i&&y==j||matrix.at(i).at(j)!=0){
                convert=std::to_string(matrix.at(i).at(j));
                std::cout<<std::setw(4)<<std::right<<convert<<'|';
            }
            else
                std::cout<<"    |";
        if(x==i&&y==j||matrix.at(i).at(j)!=0){
                convert=std::to_string(matrix.at(i).at(j));
                std::cout<<std::setw(4)<<std::right<<convert<<'|';
        }
        else
            std::cout<<"    |";
        std::cout<<std::endl;
        std::cout<<std::setfill('-')<<std::setw(4*sizeCol+sizeCol+1)<<""<<std::endl;
    }
    }
}

void BST::Levels(){
    int h=getHeight();
    int i;
    for(i=1;i<=h;i++)
        addToMatrixPrivate(root,i,i-1,matrix,checkZero,x,y);
}

void BST::addToMatrixPrivate(Node* priv, int lvl, int pozLine, std::vector<std::vector<int>>&matrix, int &checkZero, int &x, int &y){
        if(priv==nullptr)
              return;
         if(lvl==1){
            std::vector<int>length=inOrder();
            int i;
            for(i=0;i<length.size()&&length.at(i)!=priv->value;i++);
            matrix.at(pozLine).at(i)=priv->value;
            if(priv->value==0){
                checkZero++;
                x=pozLine;
                y=i;
            }
         }
         else if(lvl>1){
             addToMatrixPrivate(priv->left,lvl-1,pozLine,matrix,checkZero,x,y);
             addToMatrixPrivate(priv->right,lvl-1,pozLine,matrix,checkZero,x,y);
        }

}

void BST::init(){
    int sizeLine=getHeight();
    int sizeCol=inOrder().size();
    int i;
    matrix.resize(sizeLine);
    for(i=0;i<sizeLine;i++)
        matrix.at(i).resize(sizeCol);
}

Node::~Node(){
    if(left)
        delete left;
    if(right)
        delete right;
}


BST::BST(){
    root=nullptr; 
}
BST::~BST(){
    if(root)
        delete root;
}

void BST::insertKey(int newKey){
     root=insertKeyPrivate(newKey,root);
}

Node* BST::insertKeyPrivate(int key,Node* priv){
    
    if(priv==nullptr)
        return new Node(key);
    if(key<priv->value){
            priv->left=insertKeyPrivate(key,priv->left);
    }
    else{
            priv->right=insertKeyPrivate(key,priv->right);
    }
    return priv;
}

std::vector<int> BST::inOrder(){
    std::vector<int>v;
    inOrderPrivate(root,v);
    return v;
}

void BST::inOrderPrivate(Node* priv,std::vector<int> &v){
    if(priv==nullptr)
        return;
    inOrderPrivate(priv->left,v);
    v.push_back(priv->value);
    inOrderPrivate(priv->right,v);
}

int BST::getHeight(){
    int h;
    h=getHeightPrivate(root);
    return h;
}

int BST::getHeightPrivate(Node* priv){

    int hleft,hright;
    if(priv==nullptr)
        return 0;
    else{
        hleft=getHeightPrivate(priv->left);
        hright=getHeightPrivate(priv->right);
        if(hleft>hright)
            return hleft+1;
        else
            return hright+1;
    }
}

int main()
{
    int number;
    BST tree;
    std::cout<<"Enter the numbers to be stored: ";
     std::cin>>number;
    while(!std::cin.fail()){
            tree.insertKey(number);
            std::cin>>number;
    }
    std::cout<<std::endl;
    tree.init();
    tree.Levels();
    std::vector<int>v= tree.inOrder();
    std::cout<<"The numbers in sorted order: ";
    for(int i=0;i<v.size();i++)
        std::cout<<v.at(i)<<" ";
    std::cout<<std::endl;
    tree.prettyPrint();
   return 0;
}