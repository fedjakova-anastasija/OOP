#include "stdafx.h"
#include "CShapeMaker.h"
#include "CCanvas.h"
#include "Config.h"

CShapeMaker::CShapeMaker(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_action({ { ADD_CIRCLE, bind(&CShapeMaker::AddCircle, this, std::placeholders::_1) },
		{ ADD_RECTANGLE, bind(&CShapeMaker::AddRectangle, this, std::placeholders::_1) },
		{ ADD_TRIANGLE, bind(&CShapeMaker::AddTriangle, this, std::placeholders::_1) },
		{ ADD_LINE, bind(&CShapeMaker::AddLine, this, std::placeholders::_1) },
		{ GET_MIN_PERIMETER, bind(&CShapeMaker::GetShapeWithMinPerimeter, this, std::placeholders::_1) },
		{ GET_MAX_AREA, bind(&CShapeMaker::GetShapeWithMaxArea, this, std::placeholders::_1) },
		{ DRAW_SHAPES, bind(&CShapeMaker::DrawShapes, this, std::placeholders::_1) },
		{ INFO, bind(&CShapeMaker::Info, this, std::placeholders::_1) } })
{
}

void CShapeMaker::Info(std::istream& args)
{
	std::cout << "-> Add a circle: " << ADD_CIRCLE << std::endl
		<< "-> Add a rectangle: " << ADD_RECTANGLE << std::endl
		<< "-> Add a triangle: " << ADD_TRIANGLE << std::endl
		<< "-> Add a line: " << ADD_LINE << std::endl
		<< "--> Get min shape perimeter: " << GET_MIN_PERIMETER << std::endl
		<< "--> Get max shape area: " << GET_MAX_AREA << std::endl
		<< "---> Draw shapes: " << DRAW_SHAPES << std::endl
		<< "----> Info: " << INFO << std::endl;
}

bool CShapeMaker::HandleCommand()
{
	std::string str;
	getline(m_input, str);
	std::istringstream strm(str);

	std::string action;
	strm >> action;

	auto it = m_action.find(action);
	if (it != m_action.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CShapeMaker::AddFFToColor(std::string& color) const
{
	if (color.size() == COLOR_LENGTH)
	{
		color += FF;
	}
}

void CShapeMaker::ArrayVoidCheck() const
{
	if (m_shapes.empty())
	{
		m_output << "Array of shapes is empty" << std::endl;
	}
}

void CShapeMaker::DrawShapes(std::istream&)
{
	ArrayVoidCheck();

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		for (auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}

		window.display();
	}
}

void CShapeMaker::GetShapeWithMinPerimeter(std::istream& args) const
{
	ArrayVoidCheck();

	auto GetMinShapePtr = [](const std::shared_ptr<IShape>& shapeFirst, const std::shared_ptr<IShape>& shapeSecond) {
		return shapeFirst->GetPerimeter() < shapeSecond->GetPerimeter();
	};

	auto shapeWithMinPerimeter = *std::min_element(m_shapes.begin(), m_shapes.end(), GetMinShapePtr);
	m_output << std::endl;
	m_output << "Shape with MIN perimeter: " << std::endl;
	m_output << shapeWithMinPerimeter->ToString() << std::endl;
}

void CShapeMaker::GetShapeWithMaxArea(std::istream& args) const
{
	ArrayVoidCheck();

	auto GetMaxShapePtr = [](const std::shared_ptr<IShape>& shapeFirst, const std::shared_ptr<IShape>& shapeSecond) {
		return shapeFirst->GetArea() < shapeSecond->GetArea();
	};

	auto shapeWithMaxArea = *std::max_element(m_shapes.begin(), m_shapes.end(), GetMaxShapePtr);
	m_output << std::endl;
	m_output << "Shape with MAX area: " << std::endl;
	m_output << shapeWithMaxArea->ToString() << std::endl;
}

void CShapeMaker::AddCircle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center;
	double radius;

	if (args >> center.x >> center.y >> radius >> outlineColor >> fillColor)
	{
		if (radius < 0)
		{
			m_output << "Radius less than 0" << std::endl;
		}

		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);

		auto circlePtr = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
		m_shapes.push_back(std::move(circlePtr));
	}
	else
	{
		m_output << "Failed to create a cicle" << std::endl;
	}
}

void CShapeMaker::AddLine(std::istream& args)
{
	std::string outlineColor;
	CPoint start;
	CPoint end;

	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{
		AddFFToColor(outlineColor);

		auto linePtr = std::make_shared<CLineSegment>(start, end, outlineColor);
		m_shapes.push_back(std::move(linePtr));
	}
	else
	{
		m_output << "Failed to create a line" << std::endl;
	}
}

void CShapeMaker::AddRectangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint leftTop;
	double width;
	double height;

	if (args >> leftTop.x >> leftTop.y >> width >> height >> outlineColor >> fillColor)
	{
		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);

		if (width < 0)
		{
			m_output << "Width less than 0" << std::endl;
		}

		if (height < 0)
		{
			m_output << "Height less than 0" << std::endl;
		}

		auto rectanglePtr = std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
		m_shapes.push_back(std::move(rectanglePtr));
	}
	else
	{
		m_output << "Failed to create a rectangle" << std::endl;
	}
}

void CShapeMaker::AddTriangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;

	if (args >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> outlineColor >> fillColor)
	{
		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);

		auto trianglePtr = std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
		m_shapes.push_back(std::move(trianglePtr));
	}
	else
	{
		m_output << "Failed to create a triangle" << std::endl;
	}
}
