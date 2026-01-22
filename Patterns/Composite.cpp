#include <bits/stdc++.h>
using namespace std;
class FileSystem{
    public:
        virtual void display()=0;
};
class File;
class Folder:public FileSystem{
    public:
        string name;
        Folder(string s):name(s){}
        vector<FileSystem*>store;
        void add(FileSystem* file){
            store.push_back(file);
            cout<<"File "<<endl;
        }
        void display(){
            cout<<"Folder "<<name<<" :"<<endl;
            for(auto i:store){
                i->display();
            }
        }
};
class File:public FileSystem{
    public:
        string id;
        File(string i):id(i){}
        void display(){
            cout<<"FIle "<<id<<endl;
        }
};

int main() {
    // 1. Create simple files
    FileSystem* file1 = new File("resume.pdf");
    FileSystem* file2 = new File("photo.png");
    FileSystem* file3 = new File("notes.txt");

    // 2. Create a folder and add files
    Folder* folder1 = new Folder("My Documents");
    folder1->add(file1);
    folder1->add(file2);

    // 3. Create a parent folder and add the sub-folder + a file
    Folder* root = new Folder("Root");
    root->add(folder1); // Adding a Folder to a Folder
    root->add(file3);   // Adding a File to a Folder

    // 4. Print everything
    root->display(); 
    
    return 0;
}