//
// Created by Ayush on 10/15/2023.
//

#ifndef __PROGTEST__
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
//#include <vector>
#include <string>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {};



struct Path {
    Point from, to;
    unsigned length;

    Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

    friend bool operator == (const Path& a, const Path& b) {
        return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
    }

    friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

#endif



std::queue<size_t> top_sort(const std::vector<Path>& all_paths, size_t points, std::vector< std::vector<Path>> adjacencyList) {
    std::queue<size_t> queue;

    std::vector<size_t> indegree(points, 0);
    for (const Path & path : all_paths) {
            indegree[path.to] ++;


    }

    for ( size_t i = 0 ;i < points ; ++i )
    {
        if(indegree[i]==0)
        {
            queue.push(i);
        }

    }


    std::queue<size_t> top_sorted;
    while(!queue.empty()){
        size_t z = queue.front();
        top_sorted.push(z);
        queue.pop();
        for(auto path:adjacencyList[z]) {
            if (path.from == z) {
                indegree[path.to]--;
                if (indegree[path.to] == 0) {
                  //  top_sorted.push(indegree[path.to]);
                    queue.push(path.to);
                }
            }
        }

    }

    return top_sorted;

}



    void get_Dist_Arr(std::queue<size_t> &topologically_sorted_stack, std::vector<std::vector<Path>> &adj_list,
                      std::vector<size_t> &max_distance, std::vector<Path>& make, size_t& last_vertex, size_t& fat_new){
        while (!topologically_sorted_stack.empty()) {
            size_t u = topologically_sorted_stack.front();
            topologically_sorted_stack.pop();

            for (const Path &edge: adj_list[u]) {
                size_t v = edge.to;
                size_t new_distance = max_distance[u] + edge.length;
                if ( new_distance > max_distance[v] ) {
                    make[v] = edge;
                    if(new_distance>fat_new){
                        fat_new=new_distance;
                        last_vertex=v;
                    }
                    max_distance[v] = new_distance;
                }
            }
        }

    }


    std::vector<Path> longest_track(size_t points, const std::vector<Path> &all_paths) {
        std::queue<size_t> top_sorted;
        std::vector< std::vector<Path>> adjacencyList(points);


         for(auto path:all_paths){
            adjacencyList[path.from].push_back(path);
        }

        top_sorted = top_sort(all_paths, points, adjacencyList);

        
       


        std::vector<size_t> distances(points, 0);
        std::vector<Path> make_it(points, Path(points,points,0));
        size_t last_vertex=-1;
        std::vector<Path> make_it_top_sorted;
        size_t fat_new = 0;
        get_Dist_Arr(top_sorted, adjacencyList, distances, make_it, last_vertex, fat_new);


      while(1){

          make_it_top_sorted.insert(make_it_top_sorted.begin() , make_it[last_vertex]);
          last_vertex= make_it[last_vertex].from;
          if(make_it[last_vertex].from==points){
              return make_it_top_sorted;
          }
      }


        return make_it;
    }



#ifndef __PROGTEST__


struct Test {
    unsigned longest_track;
    size_t points;
    std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
      {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
      {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
        {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
//       {38, 8, { {3,2,10}, {3,4,17}, {3,1,1}, {1,2,3}, {1,4,15}, {4,5,21} } },
//      {10, 4, { {0, 1, 5}, {0, 2, 4}, {1, 2, 3}, {2, 3, 2}}} ,
//     {16,7, { {0, 1, 3}, {0, 2, 4}, {1, 3, 5}, {1, 4, 6}, {2, 5, 7}, {3, 6, 8} }},
//     {12,4, { {0, 1, 5}, {0, 1, 7}, {0, 2, 4}, {1, 2, 3}, {2, 3, 2} }},
//      {8,5, { {0, 1, 5}, {1, 2, 3} }},
//     {5,2,{{0,1,2},{0,1,5}}},
//    {9,6,{{0,2,5},{1,2,6},{2,3,1},{3,4,1},{4,5,1}}},
//    {150,10, { {0, 1, 12}, {0, 2, 15}, {1, 2, 13}, {2, 3, 14}, {3, 4, 16}, {4, 5, 17}, {5, 6, 18}, {6, 7, 19}, {7, 8, 20}, {8, 9, 21} }},
//      {6,3,{{0,1,6},{0,2,6}}},
//      {20, 9, {{0,1,1},{7,1,5},{1,2,2},{2,8,13},{2,6,8}}},
    };

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
    auto sol = longest_track(t.points, t.all_paths);

    unsigned length = 0;
    for (auto [ _, __, l ] : sol) length += l;

    CHECK(t.longest_track == length,
          "Wrong length: got %u but expected %u", length, t.longest_track);

    for (size_t i = 0; i < sol.size(); i++) {
        CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
              "Solution contains non-existent path: %zu -> %zu (%u)",
              sol[i].from, sol[i].to, sol[i].length);

        if (i > 0) CHECK(sol[i].from == sol[i-1].to,
                         "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
    }

    return true;
}
#undef CHECK

int main() {
    int ok = 0, fail = 0;

    for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;

    if (!fail) printf("Passed all %i tests!\n", ok);
    else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif

