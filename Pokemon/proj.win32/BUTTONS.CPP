#include "..\Classes\Buttons.h"

Buttons * Buttons::getIntance()
{
	if (!m_button)
	{
		m_button = new Buttons();
	}
	return m_button;
}
