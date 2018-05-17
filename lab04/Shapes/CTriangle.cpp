#include "stdafx.h"
#include "CTriangle.h"
#include "CUtils.h"
#include "Config.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& outlineColor, const std::string& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape(outlineColor, fillColor)
{
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);

	strm << "Perimeter:" << GetPerimeter() << std::endl
		 << "Area:" << GetArea() << std::endl
		 << "Fill color:" << GetFillColor() << std::endl
		 << "Outline color:" << GetOutlineColor() << std::endl
		 << "Vertex 1: {" << m_vertex1.x << ", " << m_vertex1.y << "}" << std::endl
		 << "Vertex 2: {" << m_vertex2.x << ", " << m_vertex2.y << "}" << std::endl
		 << "Vertex 3: {" << m_vertex3.x << ", " << m_vertex3.y << "}" << std::endl;

	return strm.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};

	canvas.FillPolygon(points, CUtils::StringToUint32(GetFillColor()));

	uint32_t outlineColor = CUtils::StringToUint32(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[0], points[2], outlineColor);
}

double CTriangle::GetPerimeter() const
{
	return sqrt(pow((m_vertex2.x - m_vertex1.x), 2) + pow((m_vertex2.y - m_vertex1.y), 2)) + sqrt(pow((m_vertex3.x - m_vertex1.x), 2) + pow((m_vertex3.y - m_vertex1.y), 2)) + sqrt(pow((m_vertex3.x - m_vertex2.x), 2) + pow((m_vertex3.y - m_vertex2.y), 2));
}

double CTriangle::GetArea() const
{
	CPoint vector1 = { m_vertex2.x - m_vertex1.x, m_vertex2.y - m_vertex1.y };
	CPoint vector2 = { m_vertex3.x - m_vertex1.x, m_vertex3.y - m_vertex1.y };
	double result = (vector1.x * vector2.y - vector2.x * vector1.y) / 2;

	return result < 0 ? result * -1 : result;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
