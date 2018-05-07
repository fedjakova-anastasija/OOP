#include "stdafx.h"
#include "CRectangle.h"
#include "CUtils.h"
#include "Config.h"

CRectangle::CRectangle(const CPoint& leftTop, const double width, const double height, const std::string& outlineColor, const std::string& fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
	SetFillColor(fillColor);
	SetOutlineColor(outlineColor);
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "Perimeter: " << GetPerimeter() << std::endl
		 << "Area: " << GetArea() << std::endl
		 << "Fill color: " << GetFillColor() << std::endl
		 << "Outline color: " << GetOutlineColor() << std::endl
		 << "Widht: " << m_width << std::endl
		 << "Height: " << m_height << std::endl
		 << "Left top vertex: {" << m_leftTop.x << ", " << m_leftTop.y << "}" << std::endl;

	return strm.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		GetLeftTop(),
		GetRightTop(),
		GetRightBottom(),
		GetLeftBottom(),
	};

	canvas.FillPolygon(points, CUtils::StringToUint32(GetFillColor()));

	uint32_t outlineColor = CUtils::StringToUint32(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[2], points[3], outlineColor);
	canvas.DrawLine(points[3], points[0], outlineColor);
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightTop() const
{
	return { m_leftTop.x + m_width, m_leftTop.y };
}

CPoint CRectangle::GetLeftBottom() const
{
	return { m_leftTop.x, m_leftTop.y + m_height };
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y + m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}


