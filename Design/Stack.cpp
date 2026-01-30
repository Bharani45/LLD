#include <bits/stdc++.h>
using namespace std;
class AStack{
    public:
    vector<int>arr;
    AStack(){}
    void push(int i){
        arr.push_back(i);
    }
    int top(){
        return arr.back();
    }
    int pop(){
        int k=arr.back();
        arr.pop_back();
        return k;
    }
};
class Aqueue{
    public:
    deque<int>arr;
    Aqueue(){}
    void push(int i){
        
    }
};
class Node{
    public:
    int val;
    Node* next;
    Node(int v):val(v),next(nullptr){}
};
class Nstack{
    Node* top;
    Nstack(){
        top=nullptr;
    }
    void push(int i){
        Node* temp=new Node(i);
        if(!top){
            top=temp;
        }else{
            temp->next=top;
            top=temp;
        }
    }
    int top(){
        return top->val;
    }
    int pop(){
        int k=top->val;
        top=top->next;
        return k;
    }
};
class Nqueue{
    public:
    Node* front;
    Node* rear;
    Nqueue(){
        front=nullptr;
        rear=nullptr;
    }
    void push(int i){
        Node* temp=new Node(i);
        if(!rear){
            rear=temp;
        }else{
            rear->next=temp;
            rear=temp;
        }
        if(!front){
            front=rear;
        }
    }
    int front(){
        return front->val;
    }
    int pop(){
        int k=front->val;
        front=front->next;
        return k;
    }
};
class QStack{
    public:
    queue<int>p;
    queue<int>q;
    void push(int i){
        p.push(i);
        while(!q.empty()){
            p.push(q.front());
            q.pop();
        }
        swap(p,q);
    }
    int top(){
        return q.front();
    }
    int pop(){
        int k=top();
        q.pop();
        return k;
    }
};
class MyQueue {
public:
    stack<int>p;
    stack<int>q;
    MyQueue() {
        
    }
    
    void push(int x) {
        while(!q.empty()){
            p.push(q.top());
            q.pop();
        }
        q.push(x);
        while(!p.empty()){
            q.push(p.top());
            p.pop();
        }
    }
    
    int pop() {
        int k=q.top();
        q.pop();
        return k;
    }
    
    int peek() {
        return q.top();
    }
    
    bool empty() {
        return q.empty();
    }
};


int main(){
    return 0;
}