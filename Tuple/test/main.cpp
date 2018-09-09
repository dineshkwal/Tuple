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

void test_copy_construction()
{
	tuple<int, std::string> t { 1, "Dinesh"s };
	auto t2 = t;
	assert(get<1>(t2) == "Dinesh"s);
}

int main()
{
	test_construction();
	test_copy_construction();
}