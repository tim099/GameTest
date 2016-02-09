#ifndef SOURCE_CLASS_TIM_MATH_PERLINNOISE_H_
#define SOURCE_CLASS_TIM_MATH_PERLINNOISE_H_
#include <vector>
class PerlinNoise {
	static const unsigned char permutation[256];
public:
	PerlinNoise();
	virtual ~PerlinNoise();
	PerlinNoise(unsigned seed);
	void init(unsigned seed);
	double noise(double x, double y, double z,double sample_range=1.0);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);

	std::vector<int> p;
	//unsigned char* permutation;
};

#endif /* SOURCE_CLASS_TIM_MATH_PERLINNOISE_H_ */
