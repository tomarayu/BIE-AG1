#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>

using Price = unsigned long long;
using Employee = size_t;
inline constexpr Employee NO_EMPLOYEE = -1;
using Gift = size_t;
// using namespace std;
#endif

void top_sort(const std::vector<Employee> &boss, std::vector<Employee> &sorted_boss,
              size_t &no_of_leaves)
{

  std::queue<Employee> Q;
  for (size_t i = 0; i < boss.size(); i++)
  {
    if (boss[i] != NO_EMPLOYEE)
    {
      // Q.push(i);
      sorted_boss[boss[i]]++;
     // std::cout<< "\n no of leaves are " << no_of_leaves << std::endl;
    }
  }
  for (size_t i = 0; i < boss.size(); i++)
  {

    if (sorted_boss[i] == 0)
    {
      Q.push(i);
     // std::cout<< sorted_boss[i]<< " and i is " <<  i << std::endl;
      no_of_leaves++;
    }
  }
  // std::cout<< "\n no of leaves are " << no_of_leaves << std::endl;

  std::vector<Employee> TSE;
  while (!Q.empty())
  {
    Employee Emp = Q.front();
    TSE.push_back(Emp);
    Q.pop();
    ////std::cout << Emp << "emp \n";
    if (boss[Emp] != NO_EMPLOYEE)
    {
     // std::cout << Emp << "\n";
      sorted_boss[boss[Emp]]--;
      if (sorted_boss[boss[Emp]] == 0)
      {
        Q.push(boss[Emp]);
      }
    }
  }

  sorted_boss = TSE;
  return;
}

void back_track(std::vector<Employee> &TSE, std::vector<std::vector<Employee>> &matrix,

                std::unordered_map<Employee, std::vector<Employee>> &emp_tree,
                const std::vector<Price> &gift_price,
                std::pair<Price, std::vector<Gift>> &optimize_gifts, size_t no_of_leaves)
{
  // size_t min = __LONG_LONG_MAX__;
  size_t index = 0;
  // size_t index_mat = 0;
  // size_t k = 0;
  // size_t m = 0;
  for (size_t i = TSE.size() - 1; i >= no_of_leaves; i--)
  {
    size_t min_ins = 0;
    for (auto e : emp_tree[TSE[i]])
    {
      size_t min = __LONG_LONG_MAX__;
      for (size_t gift = 0; gift < gift_price.size(); gift++)
      {
       
        min_ins = matrix[e][gift];
        // std::cout<< " here in gift and emp and min is " << gift << " "<<e<< " \n";
        if (optimize_gifts.second[TSE[i]] == gift)
        {
          //   std::cout<< "supervisor is " << TSE[i] << " and gift is " << gift << " and subord is " << e << " \n";
          continue;
        }

        else
        {
          if (min_ins < min)
          {
            min = min_ins;
            //  std::cout<<" min is " << min<< " \n";
            index = gift;
          }
        }
      }

      optimize_gifts.second[e] = index;
      // std::cout<< " index is  "<< index << " and emp is "<< e<<  std::endl;
    }
  }
  // for (int i = 0; i < optimize_gifts.second.size(); i++)
  // {
  //   std::cout << optimize_gifts.second[i] << " ";
  // }
  // std::cout << std::endl;

  return;
}
void assign_gifts_to_parents(std::vector<Employee> &TSE, std::vector<std::vector<Employee>> &matrix,
                             size_t &no_of_leaves, const std::vector<Employee> &boss,
                             std::unordered_map<Employee, std::vector<Employee>> &emp_tree,
                             const std::vector<Price> &gift_price,
                             std::pair<Price, std::vector<Gift>> &optimize_gifts)
{
  size_t optimize_gifts_index = 0;

  for (size_t i = no_of_leaves; i < boss.size(); i++)      // MAKING THE MATRIX FOR PARENTS
  {
    size_t minimum_of_All = __LONG_LONG_MAX__;
    size_t min_for_employees = __LONG_LONG_MAX__;

    // size_t m = 0;
    for (size_t gift = 0; gift < gift_price.size(); gift++)   
    {
      //  size_t min = __LONG_LONG_MAX__;
      matrix[TSE[i]][gift] = gift_price[gift];        // TSE[i] here is the place in the matrix, my matrix is topsorted

      for (Employee e : emp_tree[TSE[i]])
      {
        size_t min_gift_emp = __LONG_LONG_MAX__;
        // std::cout<< "e here is" << e << std::endl;
        for (size_t k = 0; k < gift_price.size(); k++)
        {
          if (k == gift)
          {
            continue;
          }
          // for (m = 0; m < TSE.size(); m++)
          // {
          //   if (TSE[m] == e)
          //     break;
          // }

          size_t temp_min_gift_emp = 0;
          temp_min_gift_emp += matrix[e][k];
          if(gif)

          if (temp_min_gift_emp < min_gift_emp)
          {
            min_gift_emp = temp_min_gift_emp;
          }
        }

        matrix[TSE[i]][gift] += min_gift_emp;
      }
      if (matrix[TSE[i]][gift] < minimum_of_All)
      {

        // std::cout<< "changing min_all from "<< minimum_of_All << " to " << matrix[i][gift] << std::endl;;
        //   std::cout<< "optimise indwx is " << optimize_gifts_index<< " and gift is "<< gift << " \n" ;
        minimum_of_All = matrix[TSE[i]][gift];

        optimize_gifts_index = gift;
        optimize_gifts.second[TSE[i]] = optimize_gifts_index;
      }
    //  optimize_gifts.first+=minimum_of_All;
    }
  
   // std::cout<< "parent  is " << TSE[i] << " and putting " << optimize_gifts_index << " in it" <<  std::endl;
      //  if(boss[TSE[i]]==NO_EMPLOYEE){
      //    // std::cout<< " min of all is " << minimum_of_All << std::endl;
      //     optimize_gifts.first+=minimum_of_All;
      //     //std::cout<< "first is " << optimize_gifts.first<< std::endl;
      //   }
  }
  back_track(TSE, matrix, emp_tree, gift_price, optimize_gifts, no_of_leaves);
  return;
}

void assign_gifts_to_leaves(std::vector<Employee> &TSE, std::vector<std::vector<Employee>> &matrix,
                            size_t &no_of_leaves, const std::vector<Employee> &boss,
                            std::unordered_map<Employee, std::vector<Employee>> &emp_tree,
                            const std::vector<Price> &gift_price,
                            std::pair<Price, std::vector<Gift>> &optimize_gifts)
{

  for (size_t i = 0; i < no_of_leaves; i++)
  {
    //  //std::cout<< "I is " <<i << "\n";
    size_t min = __LONG_LONG_MAX__;
    size_t min_index = 0;
    for (size_t j = 0; j < gift_price.size(); j++)
    {
      //  //std::cout<< "gift size is "<< gift_price.size()<< " and el is "<< matrix[i][j];
      matrix[TSE[i]][j] = gift_price[j];
      if (gift_price[j] < min)
      {
        min = gift_price[j];
        min_index = j;
      }
      //   //std::cout<< "pushing j"<< gift_price[j];
    }
    optimize_gifts.second[i]=min_index;
  }
  // for (size_t i = 0; i < matrix.size(); i++)
  // {
  //   for (size_t j = 0; j < gift_price.size(); j++)
  //   {

  //     std::cout << matrix[i][j] << " ";
  //   }
  //   std::cout << " \n";
  // }
  assign_gifts_to_parents(TSE, matrix, no_of_leaves, boss, emp_tree, gift_price, optimize_gifts);
  return;
}

std::pair<Price, std::vector<Gift>> optimize_gifts(
    const std::vector<Employee> &boss,
    const std::vector<Price> &gift_price)
{
  // TODO

  std::unordered_map<Employee, std::vector<Employee>> emp_tree(boss.size());
  std::vector<Employee> roots;
  //bool only_bosses=true;
  for (size_t i = 0; i < boss.size(); i++)
  {

    if (boss[i] == NO_EMPLOYEE)
    {
      roots.push_back(boss[i]);
    }
    for (size_t j = 0; j < boss.size(); j++)
    {
      // cout<< "\n j is " << j << " and i is "<< i << "\n";
      if (boss[j] == i)
      {
        emp_tree[i].push_back(j);
        // cout<< "\n pushing back in "<< i <<" " << j ;
      }
    }
    // if(boss[i]!=NO_EMPLOYEE){
    //   only_bosses=false;
    // }
  }

  std::vector<Employee> TSE(boss.size(), 0);
  ////std::cout << boss.size() << "   \n";
  size_t no_of_leaves = 0;

  std::vector<std::vector<Employee>> matrix(boss.size(), std::vector<Gift>(gift_price.size()));

  std::pair<Price, std::vector<Gift>> optimize_gifts(0, std::vector<Gift>(boss.size()));
  // if(only_bosses){
  //   size_t min_index=0;
  //    std::vector<long long unsigned int> mutableGifts(gift_price.begin(), gift_price.end());
  //     sort(mutableGifts.begin(), mutableGifts.end());
      
      
  //     for(size_t j =0; j<gift_price.size(); j++){
  //       if(gift_price[j]==mutableGifts[0])min_index=j;
  //     }
  //     for(size_t i = 0; i< boss.size(); i++){
  //       optimize_gifts.second[i]=min_index;
  //       optimize_gifts.first += mutableGifts[0];
  //       //std::cout<< "opti_ind is "<< optimize_gifts.first<< std::endl;
  //     }
  //     return optimize_gifts;
  // }
  // for(size_t i = 0; i<roots.size(); i++){
  top_sort(boss, TSE, no_of_leaves);
  // std::cout << "SORTED VECTOR IS ";
  // for (auto emp : TSE)
  // {
  //   std::cout << emp << " ";
  // }
  // std::cout << std::endl;
  // std::cout << std::endl
  //           << "and leaves  is " << no_of_leaves << std::endl;
  // if(roots.size()==1){
  //   size_t minnnnn = __LONG_LONG_MAX__;
  // for(size_t i = 0; i< gift_price.size(); i++){
  //   if(matrix[matrix.size()-1][i]<minnnnn){
  //     minnnnn=matrix[matrix.size()-1][i];
  //   }
  // }
  // optimize_gifts.first=minnnnn;
  // }
  // ;

  assign_gifts_to_leaves(TSE, matrix, no_of_leaves, boss, emp_tree, gift_price, optimize_gifts);
  optimize_gifts.first=0;
  for(size_t i = 0; i<boss.size(); i++){
   // if(boss[i]==NO_EMPLOYEE){
      optimize_gifts.first += gift_price[optimize_gifts.second[i]];
    
  }

  return optimize_gifts;
}

#ifndef __PROGTEST__

// const std::tuple<Price, std::vector<Employee>, std::vector<Price>> EXAMPLES[] = {
//     {17, {1, 2, 3, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
//     {16, {4, 4, 4, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
//     {17, {4, 4, 3, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
//     {24, {4, 4, 3, 4, NO_EMPLOYEE, 3, 3}, {25, 4, 18, 3}},
//     // { 38, {4,4,4,4,NO_EMPLOYEE,3,3,4,7,7,1}, {25,4,18,3}},

// };
const std::tuple<Price, std::vector<Employee>, std::vector<Price>> EXAMPLES[] = {
    {12, {2, 2, 4, 4, NO_EMPLOYEE, NO_EMPLOYEE, 5, 5, 5}, {4, 6, 8, 3, 1, 2}},
    {11, {2, 2, 4, 4, NO_EMPLOYEE}, {4, 1, 5}},
   {17, {1, 2, 3, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
    {16, {4, 4, 4, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
    {17, {4, 4, 3, 4, NO_EMPLOYEE}, {25, 4, 18, 3}},
    {24, {4, 4, 3, 4, NO_EMPLOYEE, 3, 3}, {25, 4, 18, 3}},
    {34, {4, 4, 3, 4, NO_EMPLOYEE, 3, 3, NO_EMPLOYEE, 7, 7}, {25, 4, 18, 3}},
    {15, {5, 5, 5, 5, 6, 10, 10, 10, 10, 10, NO_EMPLOYEE}, {1, 2, 3, 4}},
    {19, {2, 2, 4, 4, NO_EMPLOYEE, 1, 1, 4, 3, 3}, {1, 4, 5, 3}},
    {34, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, NO_EMPLOYEE}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28}},
   // {1, {NO_EMPLOYEE}, {1,3,4}},
   {7, {5, 5, 5,5,5,NO_EMPLOYEE}, {2, 1, 4}},
   //{14, {4,4,1,2,NO_EMPLOYEE, 2, NO_EMPLOYEE,6, NO_EMPLOYEE,NO_EMPLOYEE,NO_EMPLOYEE}, {2,1,4}},
    };

#define CHECK(cond, ...)                 \
  do                                     \
  {                                      \
    if (cond)                            \
      break;                             \
    printf("Test failed: " __VA_ARGS__); \
    printf("\n");                        \
    return false;                        \
  } while (0)

bool test(Price p, const std::vector<Employee> &boss, const std::vector<Price> &gp)
{
  auto &&[sol_p, sol_g] = optimize_gifts(boss, gp);
  CHECK(sol_g.size() == boss.size(),
        "Size of the solution: expected %zu but got %zu.", boss.size(), sol_g.size());

  Price real_p = 0;
  for (Gift g : sol_g)
    real_p += gp[g];

  CHECK(real_p == sol_p, "Sum of gift prices is %llu but reported price is %llu.", real_p, sol_p);

  if (0)
  {
    for (Employee e = 0; e < boss.size(); e++)
      printf(" (%zu)%zu", e, sol_g[e]);
    printf("\n");
  }

  for (Employee e = 0; e < boss.size(); e++)
    CHECK(boss[e] == NO_EMPLOYEE || sol_g[boss[e]] != sol_g[e],
          "Employee %zu and their boss %zu has same gift %zu.", e, boss[e], sol_g[e]);

  CHECK(p == sol_p, "Wrong price: expected %llu got %llu.", p, sol_p);

  return true;
}
#undef CHECK

int main()
{
  int ok = 0, fail = 0;
  for (auto &&[p, b, gp] : EXAMPLES)
    (test(p, b, gp) ? ok : fail)++;

  if (!fail)
    printf("Passed all %d tests!\n", ok);
  else
    printf("Failed %d of %d tests.", fail, fail + ok);
}

#endif
