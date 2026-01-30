#include <bits/stdc++.h>
using namespace std;
class Node{
    public:
        int val;
        Node* next;
        Node(int v):val(v),next(nullptr){}
};
class DoubleNode{
    public:
        int val;
        DoubleNode* next;
        DoubleNode* prev;
        DoubleNode(int v):val(v),next(nullptr),prev(nullptr){}
        DoubleNode(int v,DoubleNode* n,DoubleNode* p):val(v),next(n),prev(p){}

};
Node* delnode(Node* head,int pos){
    Node* temp=head;
    for(int i=0;i<pos-1 && temp->next;i++){
        temp=temp->next;
    }
    if(temp->next){
        temp->next=temp->next->next;
    }else{
        temp->next=nullptr;
    }
    return head;
}
Node* insert( Node* head,int pos,int v){
    Node* val=new Node(v);
    Node* temp=head;
    int cnt=0;
    if(pos==0){
        val->next=head;
        return val;
    }
    while(cnt<pos-1 && temp){
        temp=temp->next;
        cnt++;
    }
    Node* prev=temp->next;
    temp->next=val;
    val->next=prev;
    return head;
}
void display(Node* head){
    while(head){
        cout<<head->val<<endl;
        head=head->next;
    }
}
DoubleNode* ddelete(DoubleNode* head, int pos) {
    if (!head) return nullptr;

    // DELETE HEAD
    if (pos == 0) {
        DoubleNode* temp = head;
        head = head->next;

        if (head)
            head->prev = nullptr;

        delete temp;
        return head;
    }

    DoubleNode* curr = head;

    for (int i = 0; i < pos && curr; i++) {
        curr = curr->next;
    }

    if (!curr) return head; // invalid position

    // DELETE MIDDLE OR TAIL
    if (curr->next)
        curr->next->prev = curr->prev;

    curr->prev->next = curr->next;

    delete curr;
    return head;
}

DoubleNode* dinsert(DoubleNode* head, int pos, int val) {
    DoubleNode* node = new DoubleNode(val);

    // INSERT AT HEAD
    if (pos == 0) {
        node->next = head;
        if (head)
            head->prev = node;
        return node;  // new head
    }

    DoubleNode* temp = head;

    for (int i = 0; i < pos - 1 && temp; i++) {
        temp = temp->next;
    }

    if (!temp) return head; // invalid position

    // INSERT IN MIDDLE OR END
    node->next = temp->next;
    node->prev = temp;

    if (temp->next)
        temp->next->prev = node;

    temp->next = node;

    return head;
}

class Solution{
    public:
    int n;
    int m;
    int recur(int i,int j,vector<vector<int>>& matrix){
        if(i>=n || j>=n){
            return 0;
        }
        if(i==n-1){
            return matrix[i][j];
        }
        int sum=0;
        for(int k=0;k<3;k++){
            if(k!=j){
                sum=max(sum,matrix[i][j]+recur(i+1,k,matrix));
            }
        }
        return sum;
    }
    int ninjaTraining(vector<vector<int>>& matrix) {
        n=matrix.size();
        m=matrix[0].size();
        int maxi=0;
        for(int i=0;i<m;i++){
            maxi=max(maxi,recur(0,i,matrix));
        }
        return maxi;
    }
};
int main(){
    Solution s;
    vector<vector<int>>ls= {{70, 40, 10}, {180, 20, 5}, {200, 60, 30}};
    cout<<s.ninjaTraining(ls);
    return 0;
}