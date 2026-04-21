#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <variant>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;
