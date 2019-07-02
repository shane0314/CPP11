#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include "myHfile.h"

using namespace std;

int main(int argc, char** argv )
{
    string configFilename;
    namespace po = boost::program_options;
    po::options_description desc( "test program options");
    
    desc.add_options()
        ("help", "produce help messages/haha")
        ("config,c", po::value<std::string>( &configFilename), "config file")
        ;
    po::variables_map vm;
    try{
        po::store( po::parse_command_line( argc, argv, desc ), vm );
    }
    catch(...){
        std::cout << "unknown options!" << std::endl;
    }

    po::notify( vm );

    if( vm.count("help") ){
        std::cout << desc << std::endl;
    }
    if( vm.count( "cofing") ) {
        std::cout << "config file is:" << vm["config"].as<std::string>() << std::endl;
    }
    if( vm.empty() ) {
        std::cout << "no options found" << std::endl;
    }
    
    
/*
    for( int idx=0; idx<argc; idx++)
        cout << "agrv[" << idx << "] = " << argv[idx] <<endl;
*/  
    return 0;
}
