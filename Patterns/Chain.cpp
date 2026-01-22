#include <bits/stdc++.h>
using namespace std;
class ATM{
    public:
        ATM* ptr;
        ATM(){
            ptr=nullptr;
        }
        void next(ATM* p){
            ptr=p;
        }
        virtual void dispense(int amt)=0;
        
};
class Thousand:public ATM{
    public:
        void dispense(int amt)override{
            if(amt>1000){
                cout<<"Dispensing "<<(amt/1000)*1000<<endl;
                amt=amt%1000;
            }
            ptr->dispense(amt);
        }
};
class Hundred:public ATM{
    public:
        void dispense(int amt)override{
            if(amt>100){
                cout<<"Dispensing "<<(amt/100)*100<<endl;
                amt=amt%100;
            }
            ptr->dispense(amt);
        }
};
class Remainder:public ATM{
    public:
        void dispense(int amt)override{
            cout<<"Dispensing remaining "<<amt<<endl; 
        }
};
class Solution{
    public:
        int longest(vector<int>arr,int k){
            unordered_map<int,int>mpp;
            int sum=0;
            int rh=0;
            int len=0;
            while(rh<arr.size()){
                sum+=arr[rh];
                if(sum==k){
                    len=max(len,rh+1);
                }
                int rem=sum-k;
                if(mpp.find(rem)!=mpp.end()){
                    len=max(len,rh-mpp[rem]);
                }
                if(mpp.find(sum)==mpp.end()){
                    mpp[sum]=rh;
                }
                rh++;
            }
            return len;
        }
        vector<int> leader(vector<int>nums){
            int n=nums.size();
            vector<int>ans;
            int maxi=INT_MIN;
            for(int i=n-1;i>=0;i--){
                if(nums[i]>maxi){
                    maxi=nums[i];
                    ans.push_back(nums[i]);
                    cout<<nums[i]<<endl;
                }
            }
            reverse(ans.begin(),ans.end());
            return ans;
        }
        void ms(vector<int>& arr,int l,int r,int mid,int& cnt){
            int j=mid+1;
            for(int i=l;i<=mid;i++){
                while(j<=r && arr[i]>arr[j]){
                    j++;
                }
                cnt+=j-(mid+1);
            }
            j=mid+1;
            int i=l;
            vector<int>temp;
            while(i<=mid && j<=r){
                if(arr[i]<arr[j]){
                    temp.push_back(arr[i]);
                    i++;
                }else{
                    temp.push_back(arr[j]);
                    j++;
                }
            }
            while(i<=mid){
                temp.push_back(arr[i]);
                i++;
            }
            while(j<=r){
                temp.push_back(arr[j]);
                j++;
            }
            for(int k=l;k<=r;k++){
                arr[k]=temp[k-l];
            }
        }
        void merge(vector<int>& arr,int l,int r,int& cnt){
            if(l>=r){
                return;
            }
            int mid=(l+r)/2;
            merge(arr,l,mid,cnt);
            merge(arr,mid+1,r,cnt);
            ms(arr,l,r,mid,cnt);
        }
        int inversion(vector<int>arr){
            int cnt=0;
            merge(arr,0,arr.size()-1,cnt);
            return cnt;
        }
};
int main(){
    Solution s;
    vector<int>arr= {10, 5, 2, 7, 1, 9};  
    vector<int>nums =  {1,2,3,4,5,6,2,3};
    cout<<s.inversion(nums)<<endl;
    return 0;
}