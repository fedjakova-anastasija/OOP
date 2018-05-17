#include "stdafx.h"
#include "CCircle.h"
#include "CUtils.h"
#include "Config.h"

CCircle::CCircle(const CPoint& circleCenter, const double circleRadius, const std::string& outlineColor, const std::string& fillColor)
	: m_center(circleCenter)
	, m_radius(circleRadius)
	, CSolidShape(outlineColor, fillColor)
{
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "Perimeter: " << GetPerimeter() << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Fill color: " << GetFillColor() << std::endl
		<< "Outline color: " << GetOutlineColor() << std::endl
		<< "Center.x: " << m_center.x << std::endl
		<< "Center.y: " << m_center.y << std::endl
		<< "Radius: " << m_radius << std::endl;

	return strm.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(GetCenter(), GetRadius(), CUtils::StringToUint32(GetFillColor()));
	canvas.DrawCircle(GetCenter(), GetRadius(), CUtils::StringToUint32(GetOutlineColor()));
}

double CCircle::GetArea() const
{
	return PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return PI * m_radius * 2;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
