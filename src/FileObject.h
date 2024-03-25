#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <thread>
#include <mutex>
typedef std::vector<std::string> buffer;
class FileObject
{
public:
    FileObject();
    ~FileObject();

    int readFile(const std::string& filePath);

    int writeFile(const std::string& filePath);

    int loadFromDirectory(const char * name, int level);

    void executeRead();
    
    void displayData();

private:
    std::string m_filePath;

  
    std::vector<buffer> m_buffers;
    std::vector<std::thread> m_threads;

    std::mutex m_values_mutex;

    int count = 0;
};

#endif