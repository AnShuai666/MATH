/*
 * @desc    图像文件读取异常类
 * @author  安帅
 * @date    2018-12-12
 * @email   1028792866@qq.com
*/

#ifndef IMAGE_EXCEPTION_H
#define IMAGE_EXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include "define.h"

UTIL_NAMESPACE_BEGIN

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~~~~Exception类的声明与实现~~~~~~~~~~~~~~~~~~~~~
********************************************************************/

class Exception : public std::exception,public std::string
{
public:
    Exception() noexcept
    {

    };

    Exception(std::string const& msg) noexcept
        :std::string(msg)
    {}

    Exception(std::string const& msg1,std::string const& msg2)
    noexcept : std::string(msg1)
    {
        this->append(msg2);
    }

    virtual ~Exception(void) noexcept
    {

    };
    virtual const char* what() const noexcept
    {
        std::cout<<"Got an Exception!"<<std::endl;
    }
};

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~FileException类的声明与实现~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
class FileException : public std::exception
{
public:
    FileException(const std::string errMsg = "",const std::string errInfo = "")
        :_errMsg(errMsg),_errInfo(errInfo){}
    virtual ~FileException(void) noexcept
    {
        
    };
    //noexcept c11关键字代替原来的throw
    virtual const char* what() const noexcept
    {
        std::cout<<"File Exception at: "<<_errMsg<<std::endl;
        std::cout<<"Exception content "<<_errInfo<<std::endl;

    }
    std::string _errMsg;
    std::string _errInfo;
};
UTIL_NAMESPACE_END

#endif //IMAGE_EXCEPTION_H
