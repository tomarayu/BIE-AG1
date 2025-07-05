#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Node
{
    int num;
    string color="uncolored";
    int checked =0;
};

namespace std{
    template<>
    struct hash<Node>{
        size_t operator()(const Node& key)const{
            return hash<int>()(key.num);
        }
    };
    
}


class CGraph{
    public:
    unordered_map<int ,vector<Node>>Graph;


    void addEdge(Node u, Node v, bool = 0){
        Graph[u.num].push_back(v);
        Graph[v.num].push_back(u);
        }

 
    
    void print(){
        for(auto i:Graph){
            cout<<i.first<<"->";
                for (auto j:i.second){
                    cout<<j.num<<" ,";
                }
                cout<<endl;
               
            
        }
    }
    void printlist(Node a){
        for(auto i:Graph){
            if (i.first==a.num){
                for(auto j:i.second){
                    cout<< j.num<< endl;
                }
            }
        }
    }

    void checkBi(){
        queue<vector<Node>>q; 
        for (auto i:Graph){
            q.push(i.second);
        }
        while (q.size()){
            cout<<q.front().begin<<endl;
            q.pop();

        }
        
    }
    


};



int main(){
    CGraph A;
    Node a,b,c,d,e,f,g,h;
    a.num=5;
    b.num=6;
    c.num=7;
    d.num=9;
    e.num=10;
    f.num=11;
    g.num=12;
    A.addEdge(a,b);
    A.addEdge(a,c);
    A.addEdge(a,d);
    A.addEdge(e,b);  
    A.addEdge(e,d);
    A.addEdge(f,c);
    A.addEdge(f,d);
    A.addEdge(g,c);
    //A.print();
    A.checkBi();
   // A.printlist(b);

}
//    Graph A;
//    A.addEdge(a,b);
//    A.addEdge(a,c);
//    A.addEdge(a,d);
// //    A.addEdge(e.num, b.num);
//    A.addEdge(e.num,c.num);
//    A.addEdge(e.num,d.num);
//    A.addEdge(f.num, b.num);
//    A.addEdge(f.num,c.num);
//    A.addEdge(f.num,d.num);
//    A.addEdge(g.num, b.num);
//    A.addEdge(g.num,c.num);
//    A.addEdge(g.num,d.num);
    // void printList(int u){
    //     for (auto i:Graph){
    //         if (i.first==u){
    //             for (auto j:i.second){
    //                 std::cout<<j<<" ";
    //             }
    //         }
    //         printf("\n");
    //     }
    // }

