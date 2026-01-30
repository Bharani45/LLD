#include <bits/stdc++.h>
using namespace std;
class T{
    public:
        T(){
            cout<<"constructed"<<endl;
        }
        ~T(){
            cout<<"Destrcuted"<<endl;
        }
};
void func(){
    try{
        T t;
        throw 5;
    }
    catch(int x){
        cout<<"Func Error"<<endl;
        throw;
    }
}
template <class a>
a maxi(a b, a c){
    if(b>c){
        return b;
    }
    return c;
}
class functor{
    public:
        bool operator()(int a,int b){
            return a<b;
        }
};
int add(int a,int b){
    return a+b;
}
int sub(int a,int b){
    return a-b;
}
int calc(int a,int b,int (*ptr)(int,int)){
    return ptr(a,b);
}
void handling(){
    ofstream file;
    file.open("data.txt",ios::trunc);
    file<<"Bharani The Best"<<endl;
    file.close();
    ifstream f;
    f.open("data.txt");
    string ls;
    string the;
    string best;
    while(f>>ls>>the>>best){
        cout<<ls<<the<<best<<endl;
    }
}
class Solution{
    public:
        vector<int> dir(vector<int>& arr){
            int i=0;
            int j=0;
            for(int k:arr){
                if(k==0){
                    i++;
                }else if(k==1){
                    j++;
                }else if(k==2){
                    i--;
                }else{
                    j--;
                }
            }
            return {i,j};
        }
        int ks(vector<int>val,vector<int>wt,int cap){
            vector<pair<int,int>>ls;
            for(int i=0;i<val.size();i++){
                ls.push_back({val[i],wt[i]});
            }
            sort(ls.begin(),ls.end(),[](const pair<int,int> a,const pair<int,int>b){
                return (a.first/a.second)>(b.first/b.second);
            });
            int ans=0;
            for(auto i:ls){
                if(cap-i.second>=0){
                    ans+=i.first;
                    cap-=i.second;
                }else{
                    ans+=(i.first/i.second)*cap;
                    return ans;
                }
            }
            return ans;
        }
    int maxMeetings(vector<int>& start, vector<int>& end){
        vector<pair<int,int>>ls;
        for(int i=0;i<start.size();i++){
            ls.push_back({start[i],end[i]});
        }
        sort(ls.begin(),ls.end(),[](pair<int,int>a,pair<int,int>b){
            if(a.second==b.second){
                return a.first<b.first;
            }
            return a.second<b.second;
        });
        int prev=-1;
        int cnt=0;
        for(auto i:ls){
            if(prev<i.first){
                cnt++;
                prev=i.second;
            }
        }
        return cnt;
    }
    int findPlatform(vector<int>& Arrival, vector<int>& Departure){
        sort(Arrival.begin(),Arrival.end());
        sort(Departure.begin(),Departure.end());
        int ans=0;
        int pt=0;
        for(int i=0;i<Arrival.size();i++){
            if(Arrival[i]<Departure[i]){
                if(pt==0){
                    pt++;
                }else{
                    pt--;
                }
            }
            ans=max(ans,pt);
        }
        return ans;
    }
};
int main(){
    Solution s;
    vector<int>val={900, 940, 950, 1100, 1500, 1800};
    vector<int>wt={910, 1200, 1120, 1130, 1900, 2000};
    cout<<s.findPlatform(val,wt);
    return 0;
}