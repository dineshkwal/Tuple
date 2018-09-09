#include "tuple.hpp"

#include <string>
#include <iostream>
#include <cassert>

using namespace strike;
using namespace std::string_literals;

void test_construction()
{
	tuple<int, std::string> t { 1, "Dinesh"s };

	assert(get<1>(t) == "Dinesh"s);
}

int main()
{
	test_construction();
}