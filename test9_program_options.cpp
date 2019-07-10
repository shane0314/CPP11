/*
compile command at linux:
g++ test9_program_options.cpp  -o t9 -lboost_program_options
*/

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>
#include "myHfile.h"
#include <vector>

using namespace std;

int main(int argc, char** argv )
{
    string configFilename;
	std::vector<int> 	values;
	bool flag;
	int pos1, pos2;
    namespace po = boost::program_options;
    po::options_description desc( "test program options");
    
    desc.add_options()
        ("help", "produce help messages/haha")
        ("config,c", po::value<std::string>( &configFilename), "config file")
        ("value,v", po::value( &values), "int values, -v 1 -v 2 -v 3")
		("flag,f", po::bool_switch( &flag ), "swith option")
		("pos1,p", po::value( &pos1 ), "positional option 1")
		("pos2,q", po::value( &pos2 ), "positional option 2")
        ;
	
	po::positional_options_description pos;
	pos.add( "pos1", 1 ).add( "pos2", 2 );
		

    po::variables_map vm;
    try{
        po::store( po::command_line_parser( argc, argv ).options(
			po::options_description().add( desc ) ).positional( pos ).run(), vm );
    }
    catch(...){
        std::cout << "unknown options!" << std::endl;
    }

    po::notify( vm );

    if( vm.count("help") ){
        std::cout << desc << std::endl;
    }
    if( vm.count( "cofing") ) { //not work
        std::cout << "config file is:" << vm["config"].as<std::string>() << std::endl;
        std::cout << "config file is:" << configFilename << std::endl;
    }
    std::cout << "config file is:" << vm["config"].as<std::string>() << std::endl;
    std::cout << "config file is:" << configFilename << std::endl;
    if( vm.empty() ) {
        std::cout << "no options found" << std::endl;
    }
	if( !values.empty() ) {
		std::cout << "values: ";
		BOOST_FOREACH( int var, values ) {
			std::cout << var << ",";
		}
		std::cout << std::endl;
	}    
	
	std::cout << "positional options: " << pos1 << ", " << pos2 << std::endl;
    
/*
    for( int idx=0; idx<argc; idx++)
        cout << "agrv[" << idx << "] = " << argv[idx] <<endl;
*/  
    return 0;
}
