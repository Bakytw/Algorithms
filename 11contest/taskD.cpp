#include <iostream>
#include <vector>

const int kSigma = 26;
const int kMax = 20;

std::vector<int> Sufmas(std::string& text) {
  int nn = static_cast<int>(text.size());
  std::vector<int> cnt1(kSigma + 1);
  std::vector<int> pp(nn);
  for (int i = 0; i < nn; ++i) {
    ++cnt1[text[i] - 'a'];
  }
  for (int i = 1; i <= kSigma; ++i) {
    cnt1[i] += cnt1[i - 1];
  }
  for (int i = nn - 1; i >= 0; --i) {
    pp[--cnt1[text[i] - 'a']] = i;
  }
  std::vector<int> cc(nn);
  cc[pp[0]] = 0;
  for (int i = 1; i < nn; ++i) {
    cc[pp[i]] = cc[pp[i - 1]];
    if (text[pp[i]] != text[pp[i - 1]]) {
      ++cc[pp[i]];
    }
  }
  std::vector<int> cn(nn);
  std::vector<int> pn(nn);
  std::vector<int> cnt2(nn);
  for (int k = 0; k < kMax; ++k) {
    for (int i = 0; i < nn; ++i) {
      pn[i] = (pp[i] - (1 << k) % nn + nn) % nn;
    }
    cnt2.assign(nn, 0);
    for (int i = 0; i < nn; ++i) {
      ++cnt2[cc[pn[i]]];
    }
    for (int i = 1; i < nn; ++i) {
      cnt2[i] += cnt2[i - 1];
    }
    for (int i = nn - 1; i >= 0; --i) {
      pp[--cnt2[cc[pn[i]]]] = pn[i];
    }
    cn[pp[0]] = 0;
    for (int i = 1; i < nn; ++i) {
      cn[pp[i]] = cn[pp[i - 1]];
      if (cc[pp[i]] != cc[pp[i - 1]] ||
          cc[(pp[i] + (1 << k)) % nn] != cc[(pp[i - 1] + (1 << k)) % nn]) {
        ++cn[pp[i]];
      }
    }
    cc = cn;
  }
  return pp;
}

std::string BWT(const std::string& text, const std::vector<int>& sufmas) {
  int nn = static_cast<int>(text.size());
  std::string bwtmas(nn, '0');
  for (int i = 0; i < nn; ++i) {
    int jj = (sufmas[i] + nn - 1) % nn;
    bwtmas[i] = text[jj];
  }
  return bwtmas;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string text;
  std::cin >> text;
  std::vector<int> sufmas = Sufmas(text);
  std::string bwtmas = BWT(text, sufmas);
  std::cout << bwtmas;
  return 0;
}
