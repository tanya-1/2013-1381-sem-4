#include "include/boltnut.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

TEST(BoltNutTest, First) {

	std::srand ( unsigned ( std::time(0) ) );
	// Количество элементов
	int count = 10;
	// Создаем списки болтов и гаек
	std::vector<Bolt> bolts;
	std::vector<Nut> nuts;
	for (int i = 1; i <= count; ++i)
	{
		Bolt bolt;
		Nut nut;
		bolt.size = nut.size = i;
		bolts.push_back(bolt);
		nuts.push_back(nut);
	}

	unsigned int cmp = 0;
	// Перемешиваем болты
	std::random_shuffle ( bolts.begin(), bolts.end() );

	// Эталонный список пар, с которым будет сравниваться результат,
	// возвращенный функцией findTree.
	std::vector<Pair> p;
	for (unsigned int k = 0; k < bolts.size(); ++k)
	{
		Pair pr;
		pr.bolt.size = pr.nut.size = bolts[k].size;
		p.push_back(pr);
	}
	// Uncomment next line to fail test.
	// p[0].bolt.size = -1;

	// Перемешиваем гайки
	std::random_shuffle ( nuts.begin(), nuts.end() );
	// Находим пары болтов и гаек
	std::vector<Pair> pairs = findTree(bolts, nuts, cmp);
	
	// Тестируем.
	EXPECT_TRUE( equalPairVectors(p, pairs) );

}
