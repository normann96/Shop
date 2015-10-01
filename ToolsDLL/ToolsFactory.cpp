#include "stdafx.h"
#include "ToolsFactory.h"
#include "ToolsInput.h"
#include "ToolsOutput.h"
#include "ToolsSave.h"
#include "ToolsLoad.h"

ToolsFactory::ToolsFactory() : m_pInputTools(nullptr), m_pOutputTools(nullptr), m_pLoadTools(nullptr), m_pSaveTools(nullptr)
{

#ifdef test_cout_toolsFactory
	std::cout << "I'm Constructor by ToolsFactory   " << this << std::endl;
#endif
}

ToolsFactory::~ToolsFactory()
{
 	if (m_pInputTools != NULL)
 		delete m_pInputTools;

	if (m_pOutputTools != NULL)
		delete [] m_pOutputTools;

	if (m_pLoadTools != NULL)
		delete [] m_pLoadTools;

	if (m_pSaveTools != NULL)
		delete [] m_pSaveTools;

#ifdef test_cout_toolsFactory
		std::cout << "I'm Destructor  by ToolsFactory\t  " << this << std::endl;
#endif
}

BaseInput	* ToolsFactory::CreateBaseInput()
{
	try
	{
		if (!m_pInputTools)
			m_pInputTools = new ToolsInput;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

	return m_pInputTools;
}

BaseOutput * ToolsFactory::CreateBaseOutput()
{
	try
	{
		if(!m_pOutputTools)
			m_pOutputTools = new ToolsOutput;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

	return m_pOutputTools;
}

BaseSave * ToolsFactory::CreateBaseSave()
{
	try
	{
		if (!m_pSaveTools)
			m_pSaveTools = new ToolsSave;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

	return m_pSaveTools;
}

BaseLoad * ToolsFactory::CreateBaseLoad()
{
	try
	{
		if (!m_pLoadTools)
			m_pLoadTools = new ToolsLoad;
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		throw ba;
	}

	return m_pLoadTools;
}