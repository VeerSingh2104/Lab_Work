#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/resource.h>
using namespace std;

int main() {
  pid_t pid = getpid();
  pid_t ppid = getppid();
  
  cout<<"Process ID: "<<pid<<endl;
  cout<<"Parent Process ID: "<<ppid<<endl;
  
  int priority = getpriority(PRIO_PROCESS, 0);
  if(priority==-1 && errno!=0)
  {
    cerr<<"Error retrieving nice value: "<<strerror(errno)<<endl;
  }
  cout<<"Nice value of the current process: "<<priority<<endl;
  return 0; 
}
