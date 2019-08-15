#include "tests.h"

bool check() {
  all_tests();
  std::vector<std::string>
      true_ans = {"(-1/2ac^4)", "(-1/2ac^4)", "(-2/1b)+(-b^2)", "(-c^3)+(-2/1ac^2)+(-a^2)", "(5a^2c^4)"};
  std::ifstream output("output.txt");
  std::string curr_ans;
  for (size_t test_id = 1; test_id <= true_ans.size();
       ++test_id) {
    getline(output, curr_ans);
    if (curr_ans != true_ans[test_id - 1]) {
      std::cout << "WA " << test_id << '\n';
      output.close();
      return false;
    }
  }
  output.close();
  return true;
}

int main() {
  if (check()) {
    std::cout << "OK\n";
  }
  return 0;
}
