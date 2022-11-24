#pragma once

#ifdef _USE_PROFILER_

#define SCOPE_PROFILE(name, key)    scopeProfiler key(name)
#define PROFILE_START(name)         startProfile(name)
#define PROFILE_END(name)           endProfile(name)
#define PROFILE_CLEAR               clearProfile()
#define PROFILE_WRITE_DEFAULT_DIR   writeProfiles()
#define PROFILE_WRITE(dir)          writeProfiles(dir)

#else

#define SCOPE_PROFILE(name, key)       
#define PROFILE_START(name)     
#define PROFILE_END(name)       
#define PROFILE_CLEAR           
#define PROFILE_WRITE_DEFAULT_DIR      
#define PROFILE_WRITE(dir)      

#endif


#include <Windows.h>
#include <string>

struct profileStruct
{
    LARGE_INTEGER start;

    unsigned long long int sum;
    unsigned long long int min[2];
    unsigned long long int max[2];

    unsigned long long int count;
};

class profilerException : public std::exception {
public:
    profilerException(const char* msg) {
        strcpy_s(message, 256, msg);
    }
    char* what() {
        return message;
    }

private:
    char message[256];
};

class performanceProfiler
{
public:
    performanceProfiler();
    ~performanceProfiler();

};


class scopeProfiler
{
public:
    scopeProfiler(const std::string& _name);
    ~scopeProfiler();

private:
    std::string name;
};

void profilerInit();
DWORD WINAPI profileThreadStart(LPVOID arg);

void startProfile(const std::string& name);
void endProfile(const std::string& name);
void clearProfile();

void setDirProfiles(const std::string& _dir);

void writeProfiles();
void writeProfiles(const std::string& _dir);