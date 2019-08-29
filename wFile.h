#include <fstream>

class wFile {
 public:
  wFile(const char *fileName) : output_(fileName) {}
  ~wFile() { output_.close(); }
  std::ofstream &operator()() { return output_; }
 private:
  std::ofstream output_;
};
