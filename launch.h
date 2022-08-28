struct openfile_error_info
{
    char* info;
    int error_code;
};

#ifdef _WIN32
#include <windows.h>
#include <string>
std::string GetLastErrorAsString();
openfile_error_info openFile(char* path)
{
    openfile_error_info info;
    wchar_t wtext[256];
    std::mbstowcs(wtext, path, strlen(path)+1);
    LPCWSTR pathv2 = wtext;
    info.error_code = (int)ShellExecuteW(NULL, L"open", pathv2, NULL, NULL, 0);
    std::string error = GetLastErrorAsString();
    info.info = (char*)malloc(sizeof(char) * (error.length() + 1));
    strcpy(info.info, error.c_str());
    return info;
}
//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int findExecutable(const char* baseName, char* buf, size_t size)
{
    char* envPath;
    char* part;
    size_t length;
    size_t baseNameLength;
    size_t needTrailingSlash;
    
    if (!baseName || !baseName[0]) {
        return 0;
    }
    
    envPath = getenv("PATH");
    if (!envPath) {
        return 0;
    }
    
    baseNameLength = strlen(baseName);
    while(*envPath) {
        part = strchr(envPath, ':');
        if (part) {
            length = part - envPath;
        } else {
            length = strlen(envPath);
        }
        
        if (length > 0) {
            needTrailingSlash = (envPath[length-1] == '/') ? 0 : 1;
            if (length + baseNameLength + needTrailingSlash < size) {
                strncpy(buf, envPath, length);
                strncpy(buf + length, "/", needTrailingSlash);
                strncpy(buf + length + needTrailingSlash, baseName, baseNameLength);
                buf[length + needTrailingSlash + baseNameLength] = '\0';
                
                if (access(buf, X_OK) == 0) {
                    return 1;
                }
            }
        }
        
        envPath += length;
        if (*envPath == ':') {
            envPath++;
        }
    }
    return 0;
}

void execProcess(const char* executable, char* const args[])
{
    //close all file descriptors
    //Possible optimization: use poll and close only valid descriptors.
    struct rlimit r;
    if (getrlimit(RLIMIT_NOFILE, &r) != 0) {
        int maxDescriptors = (int)r.rlim_cur;
        int i;
        for (i=0; i<maxDescriptors; ++i) {
            close(i);
        }
    }
    
    //set standard streams to /dev/null
    int devNull = open("/dev/null", O_RDWR);
    if (devNull > 0) {
        dup2(devNull, STDIN_FILENO);
        dup2(devNull, STDOUT_FILENO);
        dup2(devNull, STDERR_FILENO);
    }
    close(devNull);
    
    //detach from process group of parent
    setsid();
    
    execv(executable, args);
    _exit(1);
}

openfile_error_info openFile(char* path)
{
    char xdgOpen[256];
    if (findExecutable("xdg-open", xdgOpen, sizeof(xdgOpen))) {
        char* argv[] = {xdgOpen, path, NULL};
        pid_t pid = fork();
        if (pid == 0) {
            pid_t doubleFork = fork();
            if (doubleFork == 0) {
                execProcess(xdgOpen, argv);
            } else if (doubleFork > 0) {
                _exit(0);
            } else {
                _exit(1);
            }
        } else if (pid < 0) {
            perror("Could not fork");
            return 1;
        } else {
            int status;
            //wait for the first fork
            waitpid(pid, &status, 0);
            return status;
        }
    } else {
        fprintf(stderr, "Could not find xdg-open utility\n");
        return 1;
    }
    return 0;
}

#endif