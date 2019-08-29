#include <cassert>
using type_number = int;
using type_modulo = size_t;

class ResidueModulo {
 private:
  type_number number_;
  type_modulo modulo_;

 public:
  ResidueModulo(type_number number, type_modulo modulo)
      : number_(std::move(number)), modulo_(std::move(modulo)) {};

  type_number getNumber() const { return number_; }

  type_modulo getModulo() const { return modulo_; }

  ResidueModulo getInverseResidue() const {
    type_number number = 1;
    while (number * number_ % modulo_ != 1) {
      ++number;
    }
    return ResidueModulo(number, modulo_);
  }

  ResidueModulo operator-() const {
    ResidueModulo tmp = *this;
    tmp.number_ = -number_;
    return tmp;
  }

  ResidueModulo &operator+=(const ResidueModulo &other) {
    assert(modulo_ == other.modulo_);
    number_ += other.number_;
    number_ %= modulo_;
    return *this;
  }

  ResidueModulo operator+(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    ResidueModulo tmp = *this;
    tmp += other;
    return std::move(tmp);
  }

  ResidueModulo &operator-=(const ResidueModulo &other) {
    assert(modulo_ == other.modulo_);
    number_ = ((number_ - other.number_) % modulo_ + modulo_) % modulo_;
    return *this;
  }

  ResidueModulo operator-(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    ResidueModulo tmp = *this;
    tmp -= other;
    return std::move(tmp);
  }

  ResidueModulo &operator*=(const ResidueModulo &other) {
    assert(modulo_ == other.modulo_);
    number_ = (number_ * other.number_) % modulo_;
    return *this;
  }

  ResidueModulo operator*(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    ResidueModulo tmp = *this;
    tmp *= other;
    return std::move(tmp);
  }

  ResidueModulo &operator/=(const ResidueModulo &other) {
    assert(modulo_ == other.modulo_);
    ResidueModulo tmp = *this;
    *this = *this * other.getInverseResidue();
    return *this;
  }

  ResidueModulo operator/(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    ResidueModulo tmp = *this;
    tmp /= other;
    return std::move(tmp);
  }

  bool operator==(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    return number_ == other.number_;
  }

  bool operator!=(const ResidueModulo &other) const {
    assert(modulo_ == other.modulo_);
    return !(*this == other);
  }

  operator int() const { return number_; }
};

std::ostream &operator<<(std::ostream &os, const ResidueModulo &res) {
  os << res.getNumber();
  return os;
}
