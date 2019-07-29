#include "Ether.h"

Ether::Ether()
{
	this->Init(140);
	this->m_name = "Ether";
	this->m_gold = 10;
	this->m_id = 3;
	this->m_number = 1;
	this->m_describe = "Fully restores the PP";
}

Ether::~Ether()
{
}