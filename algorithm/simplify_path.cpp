#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

string simplifyPath(string path)
{
    if (path.empty() || path[0] != '/')
        return path;

    size_t begin = 1;
    size_t end;
    vector<string> dirs;

    while ( end = path.find('/', begin) ) {
        string dir;
        if (end == string::npos)
            dir = path.substr(begin, path.length() - begin);
        else
            dir = path.substr(begin, end-begin);

        if (dir == "..") {
            if (!dirs.empty())
                dirs.pop_back();
        } else if (dir == ".") {
            // do nothing
        } else if (dir == "") {
            // do nothing
        } else {
            dirs.push_back(dir);
        }

        if (end == string::npos)
            break;

        begin = end + 1;
    }

    if (dirs.empty())
        return "/";

    stringstream ss;
    for (auto dir : dirs) {
        ss <<"/"<<dir;
    }
    return ss.str();
}



int main()
{
    // string path = "/home/";
    // string path = "/a/./b/../../c/";
    string path = "/...";
    cout<<simplifyPath(path)<<endl;

    return 0;
}
