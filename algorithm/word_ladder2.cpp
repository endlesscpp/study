#include <vector>
#include <string>
#include <unordered_set>
#include <deque>
#include <map>
#include <iostream>
using namespace std;

void construct_path(map<string, vector<string>>& parent, string from, vector<string>& path, vector<vector<string>>& ans)
{
    path.push_back(from);
    vector<string>& parents = parent[from];

    if (parents.empty()) {
        ans.push_back(path);
        reverse(ans.back().begin(), ans.back().end());
    } else {
        for (auto next : parents) {
            construct_path(parent, next, path, ans);
        }
    }

    path.pop_back();
}

class Solution {
    public:
        vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
            bool found = false;
            vector<vector<string>> ans;
            unordered_set<string> curr, next;
            unordered_set<string> visited;
            map<string, vector<string>> parent;

            if (start == end) {
                ans.push_back(vector<string>(1, start));
                return ans;
            }

            curr.insert(start);
            visited.insert(start);

            while (!curr.empty() && !found) {
                // move to here to output all path
                for (auto word: curr)
                    visited.insert(word);

                for (const auto& str2: curr) {
                    string str = str2;
                    string saved_str = str;
                    unordered_set<string> used;

                    for (int i = 0; i<str.length(); i++) {
                        char saved = str[i];
                        for (char ch = 'a'; ch <= 'z'; ch++) {
                            if (ch == saved)
                                continue;

                            str[i] = ch;

                            if (str == end) {
                                found = true;

                                parent[str].push_back(saved_str);
                                break;
                            }

                            if (dict.count(str) > 0 && visited.count(str) == 0) {
                                parent[str].push_back(saved_str);
                                next.insert(str);
                                // visited.insert(str); // moved up
                            }
                        }
                        str[i] = saved;
                    }
                }

                curr.clear();
                swap(curr, next);
            }

            if (found) {
                vector<string> path;
                construct_path(parent, end, path, ans);
            }

            return ans;        
        }
};

int main()
{
    string from = "nape";
    string to = "mild";
    unordered_set<string> dict = {
        "dose","ends","dine","jars","prow","soap","guns","hops","cray","hove","ella","hour","lens","jive","wiry","earl","mara","part","flue","putt","rory","bull","york","ruts","lily","vamp","bask","peer","boat","dens","lyre","jets","wide","rile","boos","down","path","onyx","mows","toke","soto","dork","nape","mans","loin","jots","male","sits","minn","sale","pets","hugo","woke","suds","rugs","vole","warp","mite","pews","lips","pals","nigh","sulk","vice","clod","iowa","gibe","shad","carl","huns","coot","sera","mils","rose","orly","ford","void","time","eloy","risk","veep","reps","dolt","hens","tray","melt","rung","rich","saga","lust","yews","rode","many","cods","rape","last","tile","nosy","take","nope","toni","bank","jock","jody","diss","nips","bake","lima","wore","kins","cult","hart","wuss","tale","sing","lake","bogy","wigs","kari","magi","bass","pent","tost","fops","bags","duns","will","tart","drug","gale","mold","disk","spay","hows","naps","puss","gina","kara","zorn","boll","cams","boas","rave","sets","lego","hays","judy","chap","live","bahs","ohio","nibs","cuts","pups","data","kate","rump","hews","mary","stow","fang","bolt","rues","mesh","mice","rise","rant","dune","jell","laws","jove","bode","sung","nils","vila","mode","hued","cell","fies","swat","wags","nate","wist","honk","goth","told","oise","wail","tels","sore","hunk","mate","luke","tore","bond","bast","vows","ripe","fond","benz","firs","zeds","wary","baas","wins","pair","tags","cost","woes","buns","lend","bops","code","eddy","siva","oops","toed","bale","hutu","jolt","rife","darn","tape","bold","cope","cake","wisp","vats","wave","hems","bill","cord","pert","type","kroc","ucla","albs","yoko","silt","pock","drub","puny","fads","mull","pray","mole","talc","east","slay","jamb","mill","dung","jack","lynx","nome","leos","lade","sana","tike","cali","toge","pled","mile","mass","leon","sloe","lube","kans","cory","burs","race","toss","mild","tops","maze","city","sadr","bays","poet","volt","laze","gold","zuni","shea","gags","fist","ping","pope","cora","yaks","cosy","foci","plan","colo","hume","yowl","craw","pied","toga","lobs","love","lode","duds","bled","juts","gabs","fink","rock","pant","wipe","pele","suez","nina","ring","okra","warm","lyle","gape","bead","lead","jane","oink","ware","zibo","inns","mope","hang","made","fobs","gamy","fort","peak","gill","dino","dina","tier"};

    Solution s;
    vector<vector<string>>  ans = s.findLadders(from, to, dict);
    for (auto v : ans) {
        for (auto str : v) {
            cout<<str<<"->";
        }
        cout<<endl;
    }

    cout<<"finished\n"<<endl;
    return 0;
}


