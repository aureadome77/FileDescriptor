#include "InterFaceDescriptor.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include "Validator.h"
#include <vector>

bool FileDescriptor::openFile(std::string& filepath)
{
    m_file.open(filepath, std::ios::app | std::ios::binary | std::ios::end);

    if(m_file.is_open())
    {
        std::cout << "file Succsessfully openned!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "We cant find file name or file does not exist! " << std::endl;   
        return false;
        FileDescriptor::closeFile();
    }
}

std::vector <std::string> FileDescriptor::readFile()
{
    std::string line;
    while (getline(m_file, line)) {
       // std::cout << line << std::endl;
        m_IpVector.push_back(line);
    }
    size_t vectIpSize = m_IpVector.size();
    std::cout << "Size vector is " << vectIpSize << std::endl;
    return m_IpVector;
}

bool FileDescriptor::writeInNewFile(std::string& newPathFile)
{
    std::ofstream outPutFile(newPathFile, std::ios::out | std::ios::binary);
    size_t bufferIpVecSize = m_IpVector.size();
    std::cout << "size buffer<> is " << bufferIpVecSize << std::endl;  
    if (outPutFile.is_open())
    {
        std::cout << "newPathFile() exists and successfully openned!" << std::endl;
        for (int i = 0; i < bufferIpVecSize; i++)
        {
            if (ValidatorIpAddresses::isValidIp(m_IpVector[i]) == 1)
            {
                outPutFile << " ip is valid! -> " << "\t" << m_IpVector[i] << std::endl;  
            }
            else
            {
                outPutFile << m_IpVector[i] << "\t" << "ip is not valid";
            }
        }
        return true;
        outPutFile.close();
    }
    else
    {
        std::cerr << "We can't open or find your file! " << std::endl; 
        outPutFile.close();
        return false;
    }
}

bool FileDescriptor::closeFile()
{
    if(m_file.is_open())
    {
        m_file.close();
        return true;
    }
    else
    {
        std::cerr << "We can find File name or file does not exist !" << std::endl; 
        return false;
    }
}
