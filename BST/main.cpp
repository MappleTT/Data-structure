//这里的二分树为普通的二分搜索树
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
template <typename K,typename V>
class BST{
private:
    struct Node{
        Node *left;
        Node *right;
        K key;
        V val;
        Node (K key,V val){
            this->key=key;
            this->val=val;
            this->left=NULL;
            this->right=NULL;
        }
        Node(Node *node){
            this->right=node->right;
            this->left=node->left;
            this->val=node->val;
            this->key=node->key;
        }
    };

    int size;
    Node *root;


    //插入节点
    Node *addNode(Node *node,K key,V val){
        if(node==NULL) {
            size++;
            return new Node(key, val);
        }
        else if(node->key<key){
            node->right=addNode(node->right,key,val);
        }
        else if(node->key>key){
            node->left=addNode(node->left,key,val);
        }
        else {
            node->val=val;
        }
        return node;
    }


    //查询以root为根节点的二叉树是否包含键为key的节点
    bool contain(Node *node,K key){
        if(node==NULL)
            return false;
        else if(node->key<key){
            return contain(node->right,key);
        }
        else if(node->key>key){
            return contain(node->left,key);
        }
        else
            return true;
    }

    //返回以root为根的二叉树键为key的的值，如果不存在则返回空
    V *Search(Node *node,K key){
        if(node==NULL)
            return NULL;
        if(node->key<key){
            return Search(node->right,key);
        }
        else if(node->key>key){
            return Search(node->left,key);
        }
        else{
            return &(node->val);
        }
    }

    //前序遍历
    void preOrder(Node *node){
        if(node!=NULL){
            cout<<node->key<<" "<<node->val<<endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    //中序遍历
    void inOrder(Node *node){
        if(node!=NULL){
            inOrder(node->left);
            cout<<node->key<<" "<<node->val<<endl;
            inOrder(node->right);
        }
    }

    //后序遍历
    void postOrder(Node *node){
        if(node!=NULL){
            postOrder(node->left);
            postOrder(node->right);
            cout<<node->key<<" "<<node->val<<endl;
        }
    }

    //销毁二叉树
    void destroy(Node *node){
        if(node!=NULL){
            destroy(node->left);
            destroy(node->right);
            delete node;
            size--;
        }
    }

    //层序遍历
    void LevelOrder(Node *node){
        if(node==NULL)
            return ;
        queue<Node *>q;
        q.push(node);
        while(!q.empty()){
            Node *node=q.front();
            q.pop();
            if(node->left!=NULL){
                q.push(node->left);
            }
            if(node->right!=NULL){
                q.push(node->right);
            }
            cout<<node->key<<" "<<node->val<<endl;
        }
    }

    //删除二分树中最小的节点
    Node *removeMin(Node *node){
        if(node->left==NULL){
            Node *rig=node->right;
            delete node;
            size--;
            return rig;
        }
        node->left=removeMin(node->left);
        return node;
    }

    //删除二分树中最大的节点
    Node *removeMax(Node *node){
        if(node->right==NULL){
            Node *lef=node->left;
            delete node;
            size--;
            return lef;
        }
        node->right=removeMax(node->right);
        return node;
    }


    //得到以node为根节点的二分树中最小的节点
    Node *minimum(Node *node){
        if(node->left==NULL)
            return node;
        return minimum(node->left);
    }

    //得到以node为根节点的二分树中最小的节点
    Node *maximum(Node *node){
        if(node->right==NULL)
            return node;
        return maximum(node->right);
    }

    //删除键为Key的节点
    Node* remove(Node *node,K key){
        if(node==NULL)
            return NULL;
        if(node->key>key){
            remove(node->left,key);
        }
        else if(node->key<key){
            remove(node->right,key);
        }
        else {
            if(node->left==NULL){
                Node *rig=node->right;
                delete node;
                size--;
                return rig;
            }
            if(node->right==NULL){
                Node *lef=node->left;
                delete node;
                size--;
                return lef;
            }
            //这里的处理是指左右孩子都不为空，我们将右子树中最大的节点取代删除的节点，这样依旧保持了二分搜索树的性质
            //这里必须要new一个节点的空间，防止此指针地址空间被系统覆盖(使用及时可以得到正确值，一旦有其它函数的调用，此空间就会被覆盖，数据丢失)
            Node *p=new Node(minimum(node->right));
            size++;
            p->left=node->left;
            //调用removeMin()函数时size--了;
            p->right=removeMin(node->right);
            delete node;
            //此时我们还需要再减一次保证节点个数正确
            size--;
            return p;
        }
        return node;
    }


public:
    BST(){
        this->size=0;
        root=NULL;
    }

    ~BST(){
        destroy(root);
    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        return root==NULL;
    }


    //插入键为key值为val的节点
    void addNode(K key,V val){
        root=addNode(root,key,val);
    }

    //查询以root为根节点的二叉树是否包含键为key的节点
    bool contain(K key){
        return contain(root,key);
    }

    //返回以root为根的二叉树键为key的的值，如果不存在则返回空
    V* Search(K key){
        if(!contain(key))
            return NULL;
        return Search(root,key);
    }

    //前序遍历
    void preOrder(){
        preOrder(root);
    }

    //中序遍历
    void inOrder(){
        inOrder(root);
    }

    //后序遍历
    void postOrder(){
        postOrder(root);
    }

    //层序遍历
    void LevelOrder(){
        LevelOrder(root);
    }

    //删除二分树中最小的节点
    void removeMin(){
        root=removeMin(root);
    }

    //删除二分树中最大的节点
    void removeMax(){
        root=removeMax(root);
    }

    //删除键为Key的节点
    void remove(K key){
        root=remove(root,key);
    }

};

int main()
{



    return 0;
}