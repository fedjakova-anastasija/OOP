#include "stdafx.h"
#include "CLineSegment.h"
#include "CUtils.h"
#include "Config.h"

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, const std::string& lineColor)
	: m_start(start)
	, m_end(end)
	, CShape(lineColor)
{
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "Perimeter: " << GetPerimeter() << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Outline color: " << GetOutlineColor() << std::endl
		<< "Start vertex: {" << m_start.x << ", " << m_start.y << "}" << std::endl
		<< "End vertex: {" << m_end.x << ", " << m_end.y << "}"
		<< std::endl;

	return strm.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetStartPoint(), GetEndPoint(), CUtils::StringToUint32(GetOutlineColor()));
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow((m_end.x - m_start.x), 2) + pow((m_end.y - m_start.y), 2));
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}