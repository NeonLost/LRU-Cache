#include "lru_cache.hpp"
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
	NeonLost::lru_cache<std::string, int> cache(3);

	cache.put("one", 1);
	cache.put("two", 2);
	cache.put("three", 3);

	std::cout << "add three elements" << std::endl;
	std::cout << "one containts with value = " << cache.get_value("one") << std::endl;
	std::cout << "two containts with value = " << cache.get_value("two") << std::endl;
	std::cout << "three containts with value = " << cache.get_value("three") << std::endl;

	std::cout << std::endl;

	cache.put("four", 4);

	std::cout << "add fourth element" << std::endl;
	std::cout << "now chache containts" << std::endl;
	std::cout << "two containts with value = " << cache.get_value("two") << std::endl;
	std::cout << "three containts with value = " << cache.get_value("three") << std::endl;
	std::cout << "four containts with value = " << cache.get_value("four") << std::endl;

	std::cout << std::endl;

	std::cout << "one containts? - " << (cache.containts("one") == true ? "true" : "false") << std::endl;
	std::cout << "one key was removed as oldest" << std::endl;

	getchar();

	return 0;
}