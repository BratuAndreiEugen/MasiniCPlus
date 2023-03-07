#include "testVector.h"
#include "myVector.h"
#include "Masina.h"
#include <assert.h>
#include <iostream>

void testVectorInt()
{
	myVector<int> v;
	assert(v.size() == 0);
	v.add(1);
	v.add(2);
	v.add(3);
	v.add(4);
	v.add(5);
	v.add(6);
	assert(v.size() == 6);

	
	IteratorVector<int> i(v);
	int j = 1;
	for (i = 0; i < v.size(); ++i)
	{
		assert(*i == j);
		assert(i.element() == j);
		j++;
	}

	i = v.begin();
	j = 1;
	while (i.valid())
	{
		assert(*i == j);
		i.next();
		j++;
	}

	myVector<int> v1(v); // constructor de copiere;
	assert(v1.size() == 6);

	myVector<int> v2 = v; // assignment
	assert(v2.size() == 6);

	// myVector<int> v3; // move constructor
	// myVector<int> v4 = { 0, 1, 2, 3, 4, 5 };

	assert(v.get(0) == 1);
	assert(v.get(3) == 4);
	v.set(0, 10);
	v.set(3, 10);
	assert(v.get(0) == 10);
	assert(v.get(3) == 10);

	i = v.begin();
	assert(*i == 10);
	i = v.end();
	assert(*i == 6);

	v.remove(2);
	assert(v.get(2) == 10 && v.size() == 5);

}

void testVectorMasini()
{
	myVector<Masina> v;
	assert(v.size() == 0);
	Masina m1(101, "Mercedes-Benz", "Clasa G", "SUV");
	Masina m2(102, "Audi", "A7", "Sport");
	Masina m3(103, "Range Rover", "Velar", "SUV");
	Masina m4(104, "BMW", "Seria 3", "Sedan");
	Masina m5(105, "Toyota", "Proace", "Dubita");
	Masina m6(106, "Mercedes-Benz", "EQS", "Limuzina");

	v.add(m1);
	v.add(m2);
	v.add(m3);
	v.add(m4);
	v.add(m5);
	v.add(m6);
	assert(v.size() == 6);


	IteratorVector<Masina> i(v);
	int j = 101;
	for (i = 0; i < v.size(); ++i)
	{
		assert((*i).getNumar() == j);
		j++;
	}

	i = v.begin();
	j = 101;
	while (i.valid())
	{
		assert((*i).getNumar() == j);
		j++;
		i.next();
	}

	myVector<Masina> v1(v); // constructor de copiere;
	assert(v1.size() == 6);

	myVector<Masina> v2 = v; // assignment
	assert(v2.size() == 6);


	assert(v.get(0) == m1);
	assert(v.get(3) == m4);
	v.set(0, m6);
	v.set(3, m6);
	assert(v.get(0) == m6);
	assert(v.get(3) == m6);

	i = v.begin();
	assert(*i == m6);
	i = v.end();
	assert(*i == m6);

	v.remove(2);
	assert(v.get(2) == m6 && v.size() == 5);
}

void testVector()
{
	testVectorInt();
	testVectorMasini();

}