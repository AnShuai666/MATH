//
// Created by yhl on 19-4-22.
//

#include <iostream>
#include <Util/file_system.h>
#include <fstream>
int main()
{
    std::string filename = "a";
#if 0
    std::ifstream in;
    in.open("./a");
    if (!in)
    {
        //in=NULL;
        in.close();
        return 1;
    }
    char buf[1024] = {0};
    in.seekg(0,std::ios::beg);
    in.read(buf, sizeof(buf));
    std::cout<<buf<<std::endl;
    in.clear();
    in.close();
#endif

    char buf[100];
    char* name=util::file_system::get_cwd(buf,100);
    std::cout<<buf<<std::endl;
    std::string  cwd =util::file_system::get_cwd_string();
    std::cout<<util::file_system::get_cwd_string()<<std::endl;
    std::cout<<util::file_system::get_binary_path()<<std::endl;
    std::cout<<util::file_system::is_absolute_path("/home/as/MATH/examples_bin")<<std::endl;
    std::cout<<util::file_system::sanitize_path("//home/as/MATH/examples_bin")<<std::endl;
    std::cout<<util::file_system::sanitize_path("//home//as/MATH/examples_bin")<<std::endl;
    std::cout<<util::file_system::join_path(util::file_system::get_cwd_string() , "file_main")<<std::endl;

    std::cout<<util::file_system::get_absolute_path("a")<<std::endl;

    std::cout<<util::file_system::get_directory_name(cwd /*+ "/" + "a"*/)<<std::endl;
    std::cout<<util::file_system::basename(cwd + "/" )<<std::endl;
    std::cout<<util::file_system::replace_extension(cwd+"/"+"a","txt")<<std::endl;

    std::string data;
    util::file_system::read_file_to_string(filename,data);
    std::cout<<data<<std::endl;

    util::file_system::write_string_to_file("abskk","a");

    std::cout<<"文件结构体操作"<<std::endl;
    struct util::file_system::File file(cwd,"a.txt", false);
    std::cout<<file.get_absolute_name()<<std::endl;
    std::cout<<"path: "<< file.path<<std::endl;
    std::cout<<"name: "<< file.name<<std::endl;
    std::cout<<"is_directory: "<< file.is_directory<<std::endl;
    util::file_system::File file1(cwd,"a", false);
    util::file_system::Directory directory(cwd);
    directory.scan(cwd);
    for (util::file_system::File& f:directory)
    {
        std::cout << f.name << "\t";
    }
    std::cout<<std::endl;

    std::cout<<(file1<file)<<std::endl;


    return 0;

}