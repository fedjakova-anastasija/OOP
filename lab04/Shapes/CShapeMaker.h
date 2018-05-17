#pragma once
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"

class CShapeMaker
{
public:
	CShapeMaker(std::istream& input, std::ostream& output);
	~CShapeMaker() = default;
	bool HandleCommand();

private:
	typedef std::map<std::string, std::function<void(std::istream& args)>> Action;

	void DrawShapes(std::istream& args);
	void AddCircle(std::istream& args);
	void AddLine(std::istream& args);
	void AddRectangle(std::istream& args);
	void AddTriangle(std::istream& args);
	void GetShapeWithMinPerimeter(std::istream& args) const;
	void GetShapeWithMaxArea(std::istream& args) const;
	void AddFFToColorIfNeeded(std::string& color) const;
	void Info(std::istream& args);
	void ArrayVoidCheck() const;

	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::istream& m_input;
	std::ostream& m_output;
	const Action m_action;
};
