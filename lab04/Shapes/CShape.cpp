#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const std::string& outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
