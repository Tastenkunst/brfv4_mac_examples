#ifndef __brf__DrawingUtils_hpp
#define __brf__DrawingUtils_hpp

namespace brf {

class DrawingUtils {

public: cv::Mat graphics;

public: DrawingUtils() :
	graphics()
{
}

public: void updateLayout(unsigned int width, unsigned int height) {
	graphics.create(height, width, CV_8UC4);
}

public: void clear() {
}

public: cv::Scalar getColor(uint32_t color, double alpha) {
	return cv::Scalar(color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff, (uint8_t)(alpha * 255.0));
}

public: void drawVertices(std::vector< double >& vertices, int radius = 2, bool _clear = false,
		uint32_t fillColor = 0x00a0ff, double fillAlpha = 1.00) {

	cv::Scalar _fillColor = getColor(fillColor, fillAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	int i = 0;
	int l = (int)vertices.size();

	for(; i < l; i+=2) {
		cv::circle(g,
			cv::Point2d(vertices[i], vertices[i + 1]), radius,
			_fillColor, -1, cv::LINE_AA, 0);
	}
}

public: void drawTriangles(std::vector< double >& vertices, std::vector< int >& triangles, bool _clear = false,
		int lineThickness = 1,
		uint32_t lineColor = 0x00a0ff, double lineAlpha = 0.85) {

	cv::Scalar _lineColor = getColor(lineColor, lineAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	int i = 0;
	int l = (int)triangles.size();

	while(i < l) {
		int ti0 = triangles[i];
		int ti1 = triangles[i + 1];
		int ti2 = triangles[i + 2];

		double x0 = vertices[ti0 * 2];
		double y0 = vertices[ti0 * 2 + 1];
		double x1 = vertices[ti1 * 2];
		double y1 = vertices[ti1 * 2 + 1];
		double x2 = vertices[ti2 * 2];
		double y2 = vertices[ti2 * 2 + 1];

		cv::line(g, cv::Point2d(x0, y0), cv::Point2d(x1, y1),
			_lineColor, lineThickness, cv::LINE_AA, 0);

		cv::line(g, cv::Point2d(x0, y0), cv::Point2d(x2, y2),
			_lineColor, lineThickness, cv::LINE_AA, 0);

		cv::line(g, cv::Point2d(x1, y1), cv::Point2d(x2, y2),
			_lineColor, lineThickness, cv::LINE_AA, 0);

		i+=3;
	}
}

public: void fillTriangles(std::vector< double >& vertices, std::vector< int >& triangles, bool _clear = false,
		uint32_t fillColor = 0x00a0ff, double fillAlpha = 0.85) {

	cv::Scalar _fillColor = getColor(fillColor, fillAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	int i = 0;
	int l = (int)triangles.size();

	std::vector<std::vector<cv::Point> > fillContAll;

	while(i < l) {
		int ti0 = triangles[i];
		int ti1 = triangles[i + 1];
		int ti2 = triangles[i + 2];

		double x0 = vertices[ti0 * 2];
		double y0 = vertices[ti0 * 2 + 1];
		double x1 = vertices[ti1 * 2];
		double y1 = vertices[ti1 * 2 + 1];
		double x2 = vertices[ti2 * 2];
		double y2 = vertices[ti2 * 2 + 1];

		std::vector<cv::Point> contour;

		contour.push_back(cv::Point(x0, y0));
		contour.push_back(cv::Point(x1, y1));
		contour.push_back(cv::Point(x2, y2));

		fillContAll.push_back(contour);

		i+=3;
	}

	cv::fillPoly(g, fillContAll, _fillColor);
}

//drawing.drawTexture = function(vertices, triangles, uvData, texture) {
//
//}

public: void drawRect(std::shared_ptr<brf::Rectangle> rect, bool clear = false,
		int lineThickness = 1, uint lineColor = 0x00a0ff, double lineAlpha = 1.00) {

	if(rect != nullptr) {
		drawRect(*rect, clear, lineThickness, lineColor, lineAlpha);
	}
}

public: void drawRect(brf::Rectangle& rect, bool _clear = false,
		int lineThickness = 1, uint lineColor = 0x00a0ff, double lineAlpha = 1.00) {

	cv::Scalar _lineColor = getColor(lineColor, lineAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	cv::rectangle(g,
		cv::Rect(rect.x, rect.y, rect.width, rect.height),
		_lineColor, lineThickness, cv::LINE_AA, 0);
}

public: void drawRects(std::vector< std::shared_ptr<brf::Rectangle> >& rects, bool _clear = false,
		int lineThickness = 1, uint lineColor = 0x00a0ff, double lineAlpha = 1.00) {

	cv::Scalar _lineColor = getColor(lineColor, lineAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	int i = 0;
	int l = (int)rects.size();
	std::shared_ptr<brf::Rectangle> rect;

	for(; i < l; i++) {
		rect = rects[i];

		cv::rectangle(g,
			cv::Rect(rect->x, rect->y, rect->width, rect->height),
			_lineColor, lineThickness, cv::LINE_AA, 0);
	}
}

public: void drawPoint(std::shared_ptr<brf::Point> point, int radius, bool _clear = false,
		uint32_t fillColor = 0x00a0ff, double fillAlpha = 1.0) {

	cv::Scalar _fillColor = getColor(fillColor, fillAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	cv::circle(g,
		cv::Point2d(point->x, point->y), radius,
		_fillColor, -1, cv::LINE_AA, 0);
}

public: void drawPoints(std::vector< std::shared_ptr<brf::Point> >& points, int radius, bool _clear = false,
		uint32_t fillColor = 0x00a0ff, double fillAlpha = 1.0) {

	cv::Scalar _fillColor = getColor(fillColor, fillAlpha);

	cv::Mat& g = graphics;

	if(_clear) clear();

	int i = 0;
	int l = (int)points.size();
	std::shared_ptr<brf::Point> point;

	for(; i < l; i++) {
		point = points[i];

		cv::circle(g,
			cv::Point2d(point->x, point->y), radius,
			_fillColor, -1, cv::LINE_AA, 0);
	}
}

};

}

#endif // __brf__DrawingUtils_hpp
