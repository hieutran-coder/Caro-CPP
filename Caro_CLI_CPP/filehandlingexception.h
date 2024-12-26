#ifndef FILEHANDLINGEXCEPTION_H
#define FILEHANDLINGEXCEPTION_H
#include<fstream>
#include<stdexcept>
#include<iostream>
#include"player.h"
#include<vector>
class FileHandlingException:public std::runtime_error
{
public:
    FileHandlingException(const std::string& msg): std::runtime_error(msg){};


};



#endif // FILEHANDLINGEXCEPTION_H
