# getopt++

**A sleek and slender C++'ish alternative to getopt and getopt_long**

This library is header-only. Just `#include` [getopt.hpp](https://github.com/607011/getopt-cpp/blob/main/include/getopt.hpp) and you're done.

The `reg()` method registers a handler for a list of command-line switches. If `argparser` finds one of the switches, it calls the handler with the argument, if the switch requires an argument (`argparser::required_argument`), otherwise it calls the handler with an empty string.

If `argparser` finds command-line parameters without a switch, these can be queried as so-called positional arguments. Handlers for positionals are registered with the `pos()` method.

Using `info()` and `help()` you can improve the help output.

## Example

```cpp
#include <cstddef>
#include <string>

// this is the getopt++ specific include directive
#include <getopt.hpp>

int main(int argc, char *argv[])
{
  // variables modified by command-line switches
  unsigned long num_threads = 1;
  int verbosity = 0;
  std::string input_file;
  std::string output_file;

  // definition of command-line switches
  using argparser = argparser::argparser;
  argparser opt(argc, argv);
  opt
    .info("getopt++ demo", argv[0])
    // register command-line switches that execute
    // the built-in help display
    .help({"-?", "--help"}, "Display this help")
    // register command-line switches that modify
    // a variable according to the argument given
    .reg({"-t", "--threads"},
         "NUM_THREADS", // will be used in help to illustrate the argument
         argparser::required_argument,
         "Set number of threads", // will be displayed in help
         [&num_threads](std::string const &arg)
         {
            num_threads = std::stoul(arg);
        })
    // register command-line switche that doesn't
    // expect an argument, i.e. to increase the
    // level of verbosity
    .reg({"-v"},
         argparser::no_argument,
         "Increase verbosity of output",
         [&verbosity](std::string const &)
         {
            ++verbosity;
         })
    // register positional arguments
    .pos("INPUT_FILE", // will be used in help to illustrate the argument
         "Set file to read", // will be displayed in help
         [&input_file](std::string const &arg)
         { input_file = arg; })
    .pos("OUTPUT_FILE", // will be used in help to illustrate the argument
         "Set file to write", // will be displayed in help
         [&output_file](std::string const &arg)
         { output_file = arg; });
  try
  {
    // parse command-line and execute handlers accordingly
    opt();
  }
  // user requested help, help was shown, 
  // everything's fine, so exit smoothly
  catch (::argparser::help_requested_exception const &)
  {
    return EXIT_SUCCESS;
  }
  // handle cases where a required argument was not given
  catch (::argparser::argument_required_exception const &e)
  {
    std::cerr << "\u001b[31;1mERROR: " << e.what() << "\u001b[0m\n";
    return EXIT_FAILURE;
  }
  // handle cases where an unknown switch was given
  catch (::argparser::unknown_option_exception const &e)
  {
    std::cerr << "\u001b[31;1mERROR: " << e.what() << "\u001b[0m\n";
    opt.display_help(); 
    return EXIT_FAILURE;
  }
  // handle all other exceptions
  catch (std::exception const &e)
  {
    std::cerr << "\u001b[31;1mERROR: " << e.what() << "\u001b[0m\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
```


## More examples

  - [txtz](https://github.com/607011/txtz/blob/main/src/mapbuilder.cpp)
  - [sudoku++](https://github.com/607011/sudokuplusplus/blob/main/src/main.cpp)
  - [hibpdl++](https://github.com/607011/hibpdl/blob/main/src/main.cpp)
  - [dirb++](https://github.com/607011/dirbplusplus/blob/main/src/main.cpp)
