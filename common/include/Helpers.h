namespace common {

class Helpers {
 public:
  using Ms = std::chrono::milliseconds;
  using Seconds = std::chrono::seconds;
  using Clock = std::chrono::system_clock;

  template <typename Clock, typename Resolution>
  using TimePoint = std::chrono::time_point<Clock, Resolution>;

  static auto SetCurrentThreadName(const std::string& name) noexcept -> void;
  static auto FromUtcMs(uint64_t utc) noexcept -> TimePoint<Clock, Ms>;
  static auto FromUtcSec(uint64_t utc) noexcept -> TimePoint<Clock, Seconds>;
};

}
