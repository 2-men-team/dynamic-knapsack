#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// prototypes
void readIn(const char*, int&, vector<vector<int>>&);
int execute(int, const vector<vector<int>>&);
void writeOut(const char*, int);

// implementation
int main(int argc, char* argv[]) {
  const char* infile = argv[1];
  const char* outfile = "ip71_teliman_08_output.txt";

  int capacity;
  vector<vector<int>> data;
  readIn(infile, capacity, data);
  int sum = execute(capacity, data);
  writeOut(outfile, sum);

  return 0;
}

void readIn(const char* infile, int& cap, vector<vector<int>>& data) {
  ifstream fin(infile);

  int num;
  fin >> cap >> num;

  data.resize(num, vector<int>(2, 0));
  for (auto& elem : data) fin >> elem[0] >> elem[1];

  fin.close();
}

void writeOut(const char* outfile, int sum) {
  ofstream fout(outfile);
  fout << sum;
  fout.close();
}

int execute(int cap, const vector<vector<int>>& data) {
  vector<vector<int>> memo(data.size() + 1, vector<int>(cap + 1, 0));
  int minWeight = (*min_element(data.begin(), data.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
  }))[1];

  for (int n = 1, size = data.size() + 1; n < size; n++) {
    auto elem = data[n - 1];
    for (int w = minWeight; w < cap + 1; w++) {
      if (elem[1] > w) memo[n][w] = memo[n - 1][w];
      else memo[n][w] = max(memo[n - 1][w], elem[0] + memo[n - 1][w - elem[1]]);
    }
  }

  return memo[data.size()][cap];
}
