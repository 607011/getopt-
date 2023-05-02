#include <iostream>
#include <string>

#include "getopt.hpp"

int main(int argc, char *argv[])
{
    using argparser = argparser::argparser;
    argparser opt(argc, argv);
    opt
        .reg({"-t", "--threads"},
             argparser::required_argument,
             [](std::string const &arg)
             {
                 std::cout << "t = " << std::stoul(arg) << std::endl;
             })
        .reg({"-v"},
             argparser::no_argument,
             [](std::string const &)
             {
                 std::cout << "-v" << std::endl;
             })
        .pos([](std::string const &arg)
             { std::cout << "POS 1 = " << arg << std::endl; })
        .pos([](std::string const &arg)
             { std::cout << "POS 2 = " << arg << std::endl; })
        .pos([](std::string const &arg)
             { std::cout << "POS 3 = " << arg << std::endl; });
    try
    {
        opt();
    }
    catch (::argparser::argument_required_exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
