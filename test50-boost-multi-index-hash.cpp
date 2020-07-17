#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>

using namespace boost::multi_index;

struct animal
{
  std::string name;
  int legs;
};

typedef multi_index_container<
  animal,
  indexed_by<
    hashed_non_unique<
      member<
        animal, std::string, &animal::name
      >
    >,
    hashed_non_unique<
      member<
        animal, int, &animal::legs
      >
    >
  >
> animal_multi;

int main()
{
  animal_multi animals;

  animals.insert({"cat", 4});
  animals.insert({"shark", 0});
  animals.insert({"spider", 8});

  auto &legs_index = animals.get<1>();
  auto it = legs_index.find(4);
  legs_index.modify(it, [](animal &a){ a.name = "dog"; });

  std::cout << animals.count("dog") << '\n';

  auto it1 = animals.find( "shark" );
  if( it1 != animals.end() )
    std::cout << it1->name << "i," << it1->legs << std::endl;
  else
    std::cout << "Not found" << std::endl;

    std::cout << "test hash's lower_bound" << std::endl;
  auto itb = legs_index.lower_bound(4);
  auto ite = legs_index.upper_bound(8);

 for( ; itb != ite; ++itb )
    std::cout << itb->name "," << itb->legs << std::endl;
}
