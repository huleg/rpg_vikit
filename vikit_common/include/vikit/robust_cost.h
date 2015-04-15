#ifndef VIKIT_ROBUST_COST_H_
#define VIKIT_ROBUST_COST_H_

#include <vector>
#include <stdlib.h>
#include <memory>

namespace vk {
namespace robust_cost {

// interface for scale estimators
class ScaleEstimator
{
public:
  virtual ~ScaleEstimator() {};
  virtual float compute(std::vector<float>& errors) const = 0;
};
typedef std::shared_ptr<ScaleEstimator> ScaleEstimatorPtr;

class UnitScaleEstimator : public ScaleEstimator
{
public:
  UnitScaleEstimator() {}
  virtual ~UnitScaleEstimator() {}
  virtual float compute(std::vector<float>& /*errors*/) const { return 1.0f; };
};

// estimates scale by computing the median absolute deviation
class MADScaleEstimator : public ScaleEstimator
{
public:
  MADScaleEstimator() {};
  virtual ~MADScaleEstimator() {};
  virtual float compute(std::vector<float>& errors) const;

private:
  static const float NORMALIZER;;
};

// estimates scale by computing the standard deviation
class NormalDistributionScaleEstimator : public ScaleEstimator
{
public:
  NormalDistributionScaleEstimator() {};
  virtual ~NormalDistributionScaleEstimator() {};
  virtual float compute(std::vector<float>& errors) const;
private:
};

class WeightFunction
{
public:
  virtual ~WeightFunction() {};
  virtual float weight(const float& x) const = 0;
  virtual void configure(const float& /*param*/) {};
};
typedef std::shared_ptr<WeightFunction> WeightFunctionPtr;

class UnitWeightFunction : public WeightFunction
{
public:
  UnitWeightFunction() {};
  virtual ~UnitWeightFunction() {};
  virtual float weight(const float& /*x*/) const { return 1.0f; };
};

class TukeyWeightFunction : public WeightFunction
{
public:
  TukeyWeightFunction(const float b = DEFAULT_B);
  virtual ~TukeyWeightFunction() {};
  virtual float weight(const float& x) const;
  virtual void configure(const float& param);

  static const float DEFAULT_B;
private:
  float b_square;
};

class HuberWeightFunction : public WeightFunction
{
public:
  HuberWeightFunction(const float k = DEFAULT_K);
  virtual ~HuberWeightFunction() {};
  virtual float weight(const float& x) const;
  virtual void configure(const float& param);

  static const float DEFAULT_K;
private:
  float k;
};

} // namespace robust_cost
} // namespace vk

#endif // VIKIT_ROBUST_COST_H_
