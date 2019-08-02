#include "Ether.h"

Ether::Ether()
{
	this->Init(140);
	this->m_name = "Ether";
	this->m_gold = 10;
	this->m_id = 3;
	this->m_number = 999;
	this->m_describe = "It fully restores the PP of a single selected move that has been learned by the target Pokemon.";
}

Ether::~Ether()
{
}