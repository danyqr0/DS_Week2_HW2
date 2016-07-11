//============================================================================
// Name        : DS_Week2_HW2.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <functional>

#define type_ul unsigned long long

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::greater;
using std::queue;


class Compare{
 public:
   bool operator()(pair<type_ul,type_ul> const&a, pair<type_ul,type_ul> const&b){
      if(a.second == b.second)
          return b.first < a.first;
      return b.second < a.second;
   }
};

class JobQueue {
 private:
   priority_queue <type_ul, vector<type_ul>, greater<type_ul> > threads;
   priority_queue < pair<type_ul,type_ul>, vector< pair<type_ul, type_ul> >, Compare > output;
   queue < pair<type_ul,type_ul> > pq;
   queue <type_ul> jobs_scheduled;
   type_ul jobs_done;

  void WriteResponse() {
    while(!pq.empty()){
        pair <type_ul, type_ul> temp;
        temp = pq.front();
        cout << temp.first<<" "<<temp.second<<std::endl;
        pq.pop();
    }
  }

  void ReadData() {
    pair <type_ul,type_ul> thread_time;
    type_ul m; type_ul num_workers_;type_ul job_ith;
    jobs_done=0;
    cin >> num_workers_ >> m;
    for(type_ul i = 0; i < m; ++i){
      cin >> job_ith;
      jobs_scheduled.push(job_ith);
      if(i<num_workers_){
         thread_time=std::make_pair(i,0);
         output.push(thread_time);
      }
    }
  }

  void AssignJobs() {
      type_ul vector_size=jobs_scheduled.size();
      pair <type_ul, type_ul> pair_output;
      pair <type_ul, type_ul> pair_b;
      while(pq.size() < vector_size){
          pair_output=output.top();
          pq.push(pair_output);
          threads.push(pair_output.first);
          if(jobs_done < vector_size){
              pair_b=std::make_pair(threads.top(), jobs_scheduled.front()+pair_output.second);
              output.push(pair_b);
              jobs_done++;
          }
          threads.pop();
          output.pop();
          jobs_scheduled.pop();
      }
  }

  void Clear_pq(){
       while(!output.empty())
            output.pop();
  }

  public:
    void Solve() {
      ReadData();
      AssignJobs();
      WriteResponse();
      Clear_pq();
    }

};

int  main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();

}
