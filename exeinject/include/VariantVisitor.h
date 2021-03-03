#pragma once

namespace exe_inject {

template <typename... Args>
struct VariantVisitor : Args... {
  using Args::operator()...;
};

template <typename... Args>
VariantVisitor(Args...) -> VariantVisitor<Args...>;

} // namespace exe_inject
