#include "Ellipse4D.h"
#include <iostream>

void main() {
	std::vector<Point4D> data;

	data.reserve(20);
	data.push_back(Point4D(0.060905,	0.660874,	-0.955038,	-0.875515));
	data.push_back(Point4D(-0.675492,	0.78161,	-1.013233,	-1.658898));
	data.push_back(Point4D(-0.681584,	0.970035,	-1.091154,	-2.072076));
	data.push_back(Point4D(-0.373724,	0.960406,	-1.124858,	-1.689329));
	data.push_back(Point4D(-0.143531,	1.044515,	-1.308608,	-1.648673));
	data.push_back(Point4D(-0.349186,	0.868177,	-1.157326,	-1.560304));
	data.push_back(Point4D(-0.3673,	0.791983,	-1.20852,	-1.464714));
	data.push_back(Point4D(-0.856677,	0.658633,	-0.934258,	-1.583919));
	data.push_back(Point4D(-0.454712,	1.052269,	-0.992531,	-1.662215));
	data.push_back(Point4D(-0.455274,	0.81608,	-1.114955,	-1.523104));
	data.push_back(Point4D(-0.480464,	0.790652,	-1.092949,	-1.53903));
	data.push_back(Point4D(-0.208073,	0.940952,	-1.181106,	-1.591485));
	data.push_back(Point4D(-0.81971,	0.626491,	-1.328554,	-1.617442));
	data.push_back(Point4D(-0.566876,	0.898828,	-1.374172,	-1.751158));
	data.push_back(Point4D(0.013447,	1.245827,	-1.305017,	-1.676644));
	data.push_back(Point4D(-0.245934,	1.074844,	-1.375037,	-1.729248));
	data.push_back(Point4D(-0.116347,	1.18061,	-1.37058,	-1.683726));
	data.push_back(Point4D(-0.310571,	1.1505,	-1.325387,	-2.011929));
	data.push_back(Point4D(-0.073809,	1.418769,	-1.3345,	-2.026365));
	data.push_back(Point4D(-0.257854,	1.545044,	-1.185167,	-2.217592));

	Ellipse4D ellipse(data);

	for (int i = 0; i < data.size(); ++i) {
		std::cout<<ellipse.contains(data[i])<<std::endl;
	}
}