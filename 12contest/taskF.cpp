#include <complex>
#include <iostream>
#include <vector>

void FFT(std::vector<std::complex<double>>& aa, bool invert) {
  if (aa.size() == 1) {
    return;
  }
  int nn = static_cast<int>(aa.size());
  std::vector<std::complex<double>> a_0(nn / 2);
  std::vector<std::complex<double>> a_1(nn / 2);
  for (int i = 0; i < nn / 2; ++i) {
    a_0[i] = aa[2 * i];
    a_1[i] = aa[2 * i + 1];
  }
  FFT(a_0, invert);
  FFT(a_1, invert);
  double ang = (2 * M_PI) / static_cast<double>(nn) * (invert ? -1 : 1);
  std::complex<double> ww = 1;
  std::complex<double> w_n = std::polar(double(1), ang);
  for (int i = 0; i < nn / 2; ++i) {
    aa[i] = a_0[i] + ww * a_1[i];
    aa[i + nn / 2] = a_0[i] - ww * a_1[i];
    if (invert) {
      aa[i] /= 2;
      aa[i + nn / 2] /= 2;
    }
    ww *= w_n;
  }
}

int main() {
  int nn;
  std::cin >> nn;
  std::vector<std::complex<double>> aa(nn + 1);
  for (int i = nn; i >= 0; --i) {
    std::cin >> aa[i];
  }
  int mm;
  std::cin >> mm;
  std::vector<std::complex<double>> bb(mm + 1);
  for (int i = mm; i >= 0; --i) {
    std::cin >> bb[i];
  }
  int c_deg_2 = nn + mm;
  while ((c_deg_2 & (c_deg_2 + 1)) != 0) {
    ++c_deg_2;
  }
  aa.resize(c_deg_2 + 1);
  bb.resize(c_deg_2 + 1);
  FFT(aa, false);
  FFT(bb, false);
  for (int i = 0; i <= c_deg_2; ++i) {
    aa[i] *= bb[i];
  }
  FFT(aa, true);
  std::cout << nn + mm << ' ';
  for (int i = nn + mm; i >= 0; --i) {
    std::cout << llround(aa[i].real()) << ' ';
  }
  return 0;
}
