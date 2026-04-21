#pragma once

namespace nova::core
{

class Resource
{
public:
  virtual ~Resource() = default;

protected:
  Resource() = default;
};

}  // namespace nova::core