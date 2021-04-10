#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
using namespace std;

vector<string> find_file(string path){
    cout<<path<<endl;
    struct dirent *ptr;  
    DIR *dir;
    string PATH = path;
    dir=opendir(PATH.c_str()); 
    vector<string> files;
    cout << "文件列表: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {
    
        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
        continue;
        //cout << ptr->d_name << endl;
        files.push_back(ptr->d_name);
    }
    
    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }

    closedir(dir);
    return files;
}

int main(int argc, char * argv[])
{
    vector<string> s = find_file("./lfw");
    return 0;
}
