#define __GXX_EXPERIMENTAL_CXX0X__ 1


#include <boost/range/irange.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

#include <memory>
#include <bits/shared_ptr.h>

#include <iostream>
#include <fstream>
#include <string>

#include <vector>

class person {
public:
	person() {
	}

	person(int age) :
			m_age(age) {
	}

	virtual ~person() {
	}

	virtual int age() const {
		return m_age;
	}

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & m_age;
	}

	int m_age;
};

class developer: public person {
public:
	developer() :
			m_data({10, 20, 30}) {
	}

	developer(int age, const std::string &language, std::vector<int> vec) :
			person(age),
			m_language(language),
			m_data(vec) {
	}

	std::string language() const {
		return m_language;
	}

	std::shared_ptr<std::vector<int> > data() {
		return std::shared_ptr<std::vector<int> >(&m_data);
	}

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<person>(*this);
		ar & m_language;
		ar & m_data;
	}

	std::string m_language;
	std::vector<int> m_data;
};

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

	std::vector<int> vec;

	srand(time(0));
	for (auto x : boost::irange(1,10)) {
		vec.push_back(rand() % 12 + 1);
		std::cout << vec.back() << std::endl;
	}

	oa.register_type<developer>();

	person *p = new developer(31, "C++", vec);

	std::cout << "developer: age(31), language(\"C++\")" << std::endl;
	std::cout << "person: age(31)" << std::endl;

	std::cout << "Memory dump of object: ";
	dumpobject(p);
	std::cout << std::endl;
	std::cout << "Serializing as person" << std::endl;

	oa << p;
	delete p;
}

void load() {
	std::cout << std::endl;
	std::ifstream file("archiv.txt");
	boost::archive::text_iarchive ia(file);

	std::cout << "Deserializing as person" << std::endl;

	ia.register_type<developer>();
	person *p;
	ia >> p;

	std::cout << "Memory dump of object: ";
	dumpobject(p);
	std::cout << std::endl;

	std::cout << "Age: " << p->age() << std::endl;
	std::cout << "Casting to developer: ";

	developer* d = dynamic_cast<developer*>(p);
	std::cout << d << std::endl;
	std::cout << "Language: " << d->language() << std::endl;

	std::for_each(d->data()->begin(), d->data()->end(), [](int value){
		std::cout << value << std::endl;
	});

	delete p;
}

int main() {
	try {
		save();
		load();
	} catch (...) {
		std::cerr << "Exception!" << std::endl;
	}
}
