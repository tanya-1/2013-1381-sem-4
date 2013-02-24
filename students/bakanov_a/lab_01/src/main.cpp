#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "include/boltnut.hpp"

int main()
{
	std::srand ( unsigned ( std::time(0) ) );
	// Флаг просмотра результата сортировки. При большом количестве элементов
	// лучше отключать, так как вывод 10000 пар просто создаст много мусора
	// в консоли. Можно посмотреть на 100 элементах.
	bool viewResult = false;
	
	// Количество элементов
	int count = 1000;
	// Количество циклов прогонки теста.
	int cycles = 10;
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
	
	std::cout << count << " elements, " << cycles << " cycles." << std::endl;
	
	unsigned int totalCmpCount = 0;
	
	//==========================================================================
	// Сравнение в лоб
	
	for (int i = 0; i < cycles; ++i)
	{
		unsigned int cmp = 0;
		std::random_shuffle ( bolts.begin(), bolts.end() );
		std::random_shuffle ( nuts.begin(), nuts.end() );
		std::vector<Pair> pairs = findStupid(bolts, nuts, cmp);
		totalCmpCount += cmp;
	}
	std::cout << "Mean value of compares (stupid): " << (totalCmpCount / cycles) << std::endl;
	
	//==========================================================================
	// Сравнение с построением дерева
	
	totalCmpCount = 0;
	for (int i = 0; i < cycles; ++i)
	{
		unsigned int cmp = 0;
		std::random_shuffle ( bolts.begin(), bolts.end() );
		std::random_shuffle ( nuts.begin(), nuts.end() );
		std::vector<Pair> pairs = findTree(bolts, nuts, cmp);
		
		if (viewResult && i == 0)
		{
			std::cout << "pairs:";
			for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it)
				std::cout << ' ' << (*it).bolt.size << "|" << (*it).nut.size;
			std::cout << std::endl;
		}
		
		totalCmpCount += cmp;
	}
	std::cout << "  Mean value of compares (tree): " << (totalCmpCount / cycles) << std::endl;
	
	return 0;
}
