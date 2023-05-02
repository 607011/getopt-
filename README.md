# getopt++

**A sleek and slender C++'ish alternative to getopt and getopt_long**

This library is header-only. Just `#include` [getopt.hpp](https://github.com/607011/getopt-cpp/blob/main/include/getopt.hpp) and you're done.

The `reg()` method registers a handler for a list of command-line switches. If `argparser` finds one of the switches, it calls the handler with the argument, if the switch requires an argument (`argparser::required_argument`), otherwise it calls the handler with an empty string.

If `argparser` finds command-line parameters without a switch, these can be queried as so-called positional arguments. Handlers for positionals are registered with the `pos()` method.

## Example

```cpp
int main(int argc, char *argv[])
{
  using argparser = argparser::argparser;
  argparser opt(argc, argv);
  opt
    .reg({"-t", "--threads"},
         argparser::required_argument,
         [](std::string const &arg)
         {
            std::cout << "t = " << std::stoul(arg) << "\n";
        })
    .reg({"-v"},
         argparser::no_argument,
         [](std::string const &)
         { std::cout << "-v\n"; })
    .pos([](std::string const &arg)
         { std::cout << "POS 1 = " << arg << "\n"; })
    .pos([](std::string const &arg)
         { std::cout << "POS 2 = " << arg << "\n"; })
    .pos([](std::string const &arg)
         { std::cout << "POS 3 = " << arg << "\n"; });
  try
  {
    // parse command-line and execute handlers accordingly
    opt();
  }
  catch (::argparser::argument_required_exception const &e)
  {
    std::cerr << e.what() << "\n";
  }
  return 0;
}
```

If you call the above program like so:

```
./example blah -v -t 1 -t 3 -v -v -t 2 fasel blubb
```

it will produce the following output:

```
POS 1 = blah
-v
t = 1
t = 3
-v
-v
t = 2
POS 2 = fasel
POS 3 = blubb
```
