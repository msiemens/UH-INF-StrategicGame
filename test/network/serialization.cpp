#include <boost/range/irange.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <memory>
#include <bits/shared_ptr.h>

#include <iostream>
#include <fstream>
#include <string>

#include <gamemodel/GameAction.h>
#include <gamemodel/GameRessource.h>
#include <gamemodel/GameEntity.h>

template<class T>
void dumpobject(T const *t) {
	unsigned char const *p = reinterpret_cast<unsigned char const *>(t);
	for (size_t n = 0; n < sizeof(T); ++n)
		printf("%02d ", p[n]);
}

void save() {
	std::cout << std::endl;

	std::ofstream file("archiv.txt");
	boost::archive::text_oarchive oa(file);

	std::cout << "Creating object" << std::endl;

	GameActionPtr action(new GameAction);

	GameEntityPtr entity(new GameEntity);
	coordinates coords(5, 5);
	entity->coords = coords;
	counter<GameRessource> price(200);
	entity->cost = price;

	action->what = entity;

	std::cout << "Memory dump of object: ";
	dumpobject(&action);
	std::cout << std::endl;
	std::cout << "Serializing as GameActionPtr" << std::endl;

	oa << action;
	int a = 2;
	oa << a;
}

void load() {
	std::cout << std::endl;

	std::cout << "Reading file" << std::endl;
	std::ifstream file("archiv.txt");
	std::cout << "Initializing archive" << std::endl;
	boost::archive::text_iarchive ia(file);

	std::cout << "Deserializing as GameActionPtr" << std::endl;

	std::cout << "Creating target GameActionPtr" << std::endl;
	GameActionPtr action(new GameAction);
	std::cout << "Reading into target" << std::endl;
	try {
		ia >> action;
		std::cout << "Costs: " << action->what->cost.how_many << std::endl;
	} catch (...) {
		std::cout << "Error!" << std::endl;
	}

	std::cout << "Memory dump of object: ";
	dumpobject(&action);
	std::cout << std::endl;
}

int main() {
	// BOOST_SERIALIZATION_SHARED_PTR(GameAction);
	// BOOST_SERIALIZATION_SHARED_PTR(GameEntity);
	try {
		save();
		load();
	} catch (...) {
		std::cerr << "Exception!" << std::endl;
	}
}
