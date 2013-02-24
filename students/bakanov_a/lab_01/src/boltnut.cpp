#include "include/boltnut.hpp"

std::vector<Pair> findStupid( std::vector<Bolt> bolts, std::vector<Nut> nuts, unsigned int& cmp )
{
	std::vector<Pair> result;
	
	// По-порядку перебираем все болты
	for (std::vector<Bolt>::iterator bolt = bolts.begin(); bolt != bolts.end(); ++bolt)
	{
		for (std::vector<Nut>::iterator nut = nuts.begin(); nut != nuts.end(); ++nut)
		{
			++cmp;
			if ((*bolt).size == (*nut).size)
			{
				Pair pair;
				pair.bolt = *bolt;
				pair.nut = *nut;
				result.push_back(pair);
				nuts.erase(nut);
				break;
			}
		}
	}
	return result;
}

void findNode( Node* node, Bolt bolt, std::vector<Pair>& result, unsigned int& cmp )
{
	// Если болт меньше гайки в текущем узле, то нужно посмотреть есть ли слева
	// пара.
	if (bolt.size < node->pair.nut.size)
	{
		++cmp;
		// Если пара есть, то вызываем findNode для нее.
		if (node->left)
		{
			findNode(node->left, bolt, result, cmp);
		}
		// Если же пары нет, то это значит, что мы достигли листа дерева. Значит
		// нужно разделить находящуюся здесь кучку гаек на две.
		else
		{
			Node* newNode = new Node();
			
			// Между прочим, для уменьшения количества сравнений можно сделать
			// дополнительный цикл, который будет запускаться после того, как
			// соответствующая гайка будет найдена. Тогда нам не придется проверять
			// два условия (> и <), а можно будет проверять только одно (например, >),
			// ибо среди оставшихся гаек не найдется еще одной равной текущему болту.
			std::vector<Nut>::iterator beginFrom;
			
			// Начинаем разбирать кучку гаек.
			for (std::vector<Nut>::iterator nut = node->lower.begin(); nut != node->lower.end(); ++nut)
			{
				// Если текущий болт больше гайки, то отправляем эту гайку в левую кучку.
				if (bolt.size > (*nut).size)
				{
					cmp += 1;
					newNode->lower.push_back(*nut);
					continue;
				}
				// Иначе, если болт меньше гайки, отправляем ее в правую кучку.
				else if (bolt.size < (*nut).size)
				{
					cmp += 2;
					newNode->upper.push_back(*nut);
					continue;
				}
				// Иначе мы нашли соответствующую гайку. Сохраним пару и прервем
				// цикл, чтобы оставшиеся гайки перебирать уже в другом цикле,
				// с меньшим количеством сравнений.
				else
				{
					newNode->pair.bolt = bolt;
					newNode->pair.nut = *nut;
					result.push_back(newNode->pair);
					beginFrom = ++nut;
					break;
				}
			}
			for (std::vector<Nut>::iterator nut = beginFrom; nut != node->lower.end(); ++nut)
			{
				++cmp;
				if (bolt.size > (*nut).size)
				{
					newNode->lower.push_back(*nut);
					continue;
				}
				else
				{
					newNode->upper.push_back(*nut);
					continue;
				}
			}
			
			// Удаляем гайки из левой кучки текущего узла, чтобы не держать их
			// в памяти за зря.
			node->lower.clear();
			
			// Сохраняем новый узел в дереве
			node->left = newNode;
		}
	}
	
	// Иначе болт больше гайки в текущем узле. То есть смотрим есть ли пара справа.
	else
	{
		++cmp;
		// Если пара есть, то вызываем findNode для нее.
		if (node->right)
		{
			findNode(node->right, bolt, result, cmp);
		}
		// Если же пары нет, то это значит, что мы достигли листа дерева. Значит
		// нужно разделить находящуюся здесь кучку гаек на две.
		else
		{
			Node* newNode = new Node();
			std::vector<Nut>::iterator beginFrom;
			
			for (std::vector<Nut>::iterator nut = node->upper.begin(); nut != node->upper.end(); ++nut)
			{
				if (bolt.size > (*nut).size)
				{
					cmp += 1;
					newNode->lower.push_back(*nut);
					continue;
				}
				else if (bolt.size < (*nut).size)
				{
					cmp += 2;
					newNode->upper.push_back(*nut);
					continue;
				}
				else
				{
					newNode->pair.bolt = bolt;
					newNode->pair.nut = *nut;
					result.push_back(newNode->pair);
					beginFrom = ++nut;
					break;
				}
			}
			for (std::vector<Nut>::iterator nut = beginFrom; nut != node->upper.end(); ++nut)
			{
				++cmp;
				if (bolt.size > (*nut).size)
				{
					newNode->lower.push_back(*nut);
					continue;
				}
				else
				{
					newNode->upper.push_back(*nut);
					continue;
				}
			}
			
			node->upper.clear();
			
			// Сохраняем новый узел в дереве
			node->right = newNode;
		}
	}
}

std::vector<Pair> findTree( std::vector<Bolt> bolts, std::vector<Nut> nuts, unsigned int& cmp )
{
	std::vector<Pair> result;
	
	Node* tree = new Node();
	
	// Инициализируем корень дерева, разделив начальную кучку гаек по первому болту.
	Bolt bolt = bolts[0];
	std::vector<Nut>::iterator beginFrom;
	for (std::vector<Nut>::iterator nut = nuts.begin(); nut != nuts.end(); ++nut)
	{
		if (bolt.size > (*nut).size)
		{
			cmp += 1;
			tree->lower.push_back(*nut);
			continue;
		}
		else if (bolt.size < (*nut).size)
		{
			cmp += 2;
			tree->upper.push_back(*nut);
			continue;
		}
		else
		{
			tree->pair.bolt = bolt;
			tree->pair.nut = *nut;
			result.push_back(tree->pair);
			beginFrom = ++nut;
			break;
		}
	}
	for (std::vector<Nut>::iterator nut = beginFrom; nut != nuts.end(); ++nut)
	{
		++cmp;
		if (bolt.size > (*nut).size)
		{
			tree->lower.push_back(*nut);
			continue;
		}
		else
		{
			tree->upper.push_back(*nut);
			continue;
		}
	}
	
	// По-порядку перебираем все оставшиеся болты
	for (std::vector<Bolt>::iterator bolt = bolts.begin() + 1; bolt != bolts.end(); ++bolt)
	{
		findNode(tree, *bolt, result, cmp);
	}
	
	delete tree;
	
	return result;
}

bool equalPairVectors( std::vector<Pair>& a, std::vector<Pair>& b)
{
	if (a.size() != b.size())
		return false;
	for (unsigned int i = 0; i < a.size(); ++i)
		if (a[i].bolt.size != b[i].bolt.size || a[i].nut.size != b[i].nut.size)
			return false;
	return true;
}
