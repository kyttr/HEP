/* 
 * File:   main.cpp
 * Author: kaya
 *
 * Created on March 23, 2013, 8:51 PM
 */

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

/*
 * For the moment I will use that file to compile root files like ".C", ".root" files
 */
int main(int argc, char** argv) {

    //string[] filesArray={""}
    //vector<string> filesArray ={ "altgraph" };
    vector<string> filesArray;
    filesArray.push_back("altgraph");
    int len=filesArray.size();
    
    string tmp;
    string tmpCommand;
    const char* tmpCommand_char;
    for (int i=0;i<len;i++)
    {
        tmp=filesArray.at(i);
        tmpCommand="g++  "+tmp+".C -o "+tmp+".out `root-config --cflags --glibs`";
        
        //http://stackoverflow.com/questions/347949/convert-stdstring-to-const-char-or-char
        tmpCommand_char=tmpCommand.c_str();
        system(tmpCommand_char);
    }
    
    return 0;
}

