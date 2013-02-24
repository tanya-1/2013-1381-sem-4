#ifndef _BOLTNUT_HPP
#define _BOLTNUT_HPP

#include <cstdlib>
#include <vector>

// Структура, описывающая болты
struct Bolt
{
	unsigned int size;
};

// Структура, описывающая гайки
struct Nut
{
	unsigned int size;
};

// Структура, описывающая найденные пары.
struct Pair
{
	Bolt bolt;
	Nut nut;
};

/**
 * Функция нахождения пар болтов и гаек (перебор в лоб).
 * @param	bolts	список болтов
 * @param	nuts	список гаек
 * @param	cmp		счетчик сравнений
 * @return	список соответствующих пар.
 */
std::vector<Pair> findStupid( std::vector<Bolt> bolts, std::vector<Nut> nuts, unsigned int& cmp );

/**
 * Класс, описывающий узел дерева, используемого для быстрого поиска
 * соответствующих пар болтов и гаек.
 */
class Node
{
public:
	// Найденная пара
	Pair pair;
	// Кучка гаек больших, чем болт в паре pair.
	std::vector<Nut> upper;
	// Кучка гаек меньших, чем болт в паре pair.
	std::vector<Nut> lower;
	// Указатель на пару меньшую, чем пара в этом узле.
	Node* left;
	// Указатель на большую пару.
	Node* right;
	Node() { left = right = NULL; };
	~Node() { if (left) delete left; if (right) delete right; };
};

/**
 * Рекурсивная функция поиска узла в дереве.
 * @param	node	узел, в котором происходит сравнение текущего болта
 * @param	bolt	текущий болт
 * @param	result	вектор, в который сохраняются найденные пары
 * @param	cmp		счетчик сравнений
 */
void findNode( Node* node, Bolt bolt, std::vector<Pair>& result, unsigned int& cmp );

/**
 * Функция нахождения пар болтов и гаек (используя дерево).
 * @param	bolts	список болтов
 * @param	nuts	список гаек
 * @param	cmp		счетчик сравнений
 * @return	список соответствующих пар.
 */
std::vector<Pair> findTree( std::vector<Bolt> bolts, std::vector<Nut> nuts, unsigned int& cmp );

/**
 * Функция сравнения двух списков пар болтов и гаек.
 */
bool equalPairVectors( std::vector<Pair>& a, std::vector<Pair>& b);

#endif /* _BOLTNUT_HPP */
