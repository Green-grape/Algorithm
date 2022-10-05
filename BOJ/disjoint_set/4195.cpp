#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node{
    int val;
    Node* parent;
    int childCount;
};

vector<Node*> nodes;

Node* getParent(Node* node){
    if(node->parent==node) return node;
    return node->parent=getParent(node->parent);
}

void unify(Node* node1, Node* node2){
    Node *p1=getParent(node1), *p2=getParent(node2);
    if(p1->val<p2->val){
        p2->parent=p1;
        p1->childCount+=p2->childCount+1;
    }else if(p1->val>p2->val){
        p1->parent=p2;
        p2->childCount+=p1->childCount+1;
    }
}

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->parent=node;
    node->childCount=0;
    return node;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int relationCount;
        cin >> relationCount;
        nodes=vector<Node*>(relationCount*2+1);
        for(int i=0;i<nodes.size();i++){
            nodes[i]=makeNode(i);
        }
        map<string, int> m;
        int ret=0;
        for(int i=0;i<relationCount;i++){
            char name1[21],name2[21];
            scanf("%s %s", name1, name2);
            map<string,int>::iterator it1=m.find(string(name1)), it2=m.find(string(name2));
            if(it1==m.end()){
                int idx=m.size();
                m[name1]=idx;
                it1=m.find(name1);
            }
            if(it2==m.end()){
                int idx=m.size();
                m[name2]=idx;
                it2=m.find(name2);
            }
            unify(nodes[it1->second], nodes[it2->second]);
            Node* curNode=getParent(nodes[it1->second]);
            int ret=(curNode->childCount)+1;
            cout << ret <<"\n";
        }
    }
    return 0;
}