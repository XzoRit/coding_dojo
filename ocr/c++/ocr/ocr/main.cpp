#include <libocr/ocr.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>

namespace po = boost::program_options;

int main(int ac, char *av[])
{
    std::cout << "Hello ocr\n";

  try
  {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
      std::cout << desc << "\n";
    }
  }
  catch (std::exception &e)
  {
      std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
      std::cerr << "Exception of unknown type!\n";
  }

  return xzr::ocr::add(0, 0);
}
