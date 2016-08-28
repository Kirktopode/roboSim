#include "Log.h"
#include <ctime> //for struct tm
#include <unistd.h> //for readlink
#include <cstring> //for strlen
#include <sys/stat.h> //for mkdir
#include <stdio.h> //for snprintf

char Log::recordPath[256]={0};
void Log::getRecordPath() {
  if(recordPath[0]==0) {
    time_t rawtime;
    struct tm* ptm;
    time(&rawtime);
    ptm=gmtime(&rawtime);
    static char exePath[256];
    readlink("/proc/self/exe",exePath,sizeof(exePath)-1);
    int n=strlen(exePath);
    for(int i=n-1;i>0 && exePath[i]!='/';i--) exePath[i]=0;
    snprintf(recordPath,sizeof(recordPath)-1,"%s/testOutputData/%04d%02d%02dT%02d%02d%02d",exePath,ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    mkdir(recordPath,0755);
  }
}

