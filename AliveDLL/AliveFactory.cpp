#include "stdafx.h"
#include "AliveFactory.h"
#include "AliveInput.h"
#include "AliveOutput.h"
#include "AliveSave.h"
#include "AliveLoad.h"

AliveFactory::AliveFactory() : m_pInputAlive(nullptr), m_pOutputAlive(nullptr), 
	m_pLoadAlive(nullptr), m_pSaveAlive(nullptr)
{
	
#ifdef test_cout_aliveFactory
	std::cout << "I'm Constructor by AliveFactory   " << this << std::endl;
#endif
}

AliveFactory::~AliveFactory()
{
	if (m_pInputAlive != NULL)
		delete m_pInputAlive;

	if (m_pOutputAlive != NULL)
		delete [] m_pOutputAlive;

	if (m_pLoadAlive != NULL)
		delete [] m_pLoadAlive;

	if (m_pSaveAlive != NULL)
		delete [] m_pSaveAlive;

#ifdef test_cout_aliveFactory
	std::cout << "I'm Destructor  by AliveFactory\t  " << this << std::endl;
#endif
}

BaseInput * AliveFactory::CreateBaseInput()
{
	if (!m_pInputAlive)
		m_pInputAlive = new AliveInput;

	return m_pInputAlive;
}

BaseOutput * AliveFactory::CreateBaseOutput()
{
	if (!m_pOutputAlive)
		m_pOutputAlive = new AliveOutput;

	return m_pOutputAlive;
}

BaseSave * AliveFactory::CreateBaseSave()
{
	if (!m_pSaveAlive)
		m_pSaveAlive = new AliveSave;

	return m_pSaveAlive;
}

BaseLoad * AliveFactory::CreateBaseLoad()
{
	if (!m_pLoadAlive)
		m_pLoadAlive = new AliveLoad;

	return m_pLoadAlive;
}
