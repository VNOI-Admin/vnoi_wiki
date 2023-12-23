# Số học 4 - Phi hàm Euler

Nguồn: [HackerEarth](https://www.hackerearth.com/practice/notes/number-theory-iii/) và 1 số bài viết trên Wikipedia

Người dịch: Bùi Việt Dũng

[[_TOC_]]

# Phi hàm Euler (Euler's totient function)

**Định nghĩa:** $\phi(N)$ là số số nguyên tố cùng nhau với $N$ trong đoạn từ 1 đến $N$.

**Cách tính:**

Ta đã biết **phân tích một số ra thừa số nguyên tố (factorization)** là biểu diễn số đó dưới dạng tích của các số nguyên tố. Dễ dàng chứng minh rằng cách biểu diễn là duy nhất. Ví dụ:

- $8 = 2^3$.

- $11 = 11$.

- $36 = 2^2.3^3$.

- $935 = 5.11.17$.

- $5136 = 2^4.3.107$.

Từ cách phân tích một số ra thừa số nguyên tố, ta tính được phi hàm Euler của số đó.

```cpp
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
```

**Độ phức tạp của thuật toán:** $O(\sqrt{N})$.

# Công thức

Một công thức thường gặp để tính phi:

$\phi(N) = n \* \prod_{p\|n}(1 - 1/p) $

(p là các ước nguyên tố của n).

Ví dụ:

$\phi(6) = 6 \* (1 - 1/2) \* (1 - 1/3) = 2$

Cài đặt:

```cpp
int eulerPhi(int n) { // = n (1-1/p1) ... (1-1/pn)
    if (n == 0) return 0;
    int ans = n;
    for (int x = 2; x*x <= n; ++x) {
        if (n % x == 0) {
            ans -= ans / x;
            while (n % x == 0) n /= x;
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}
```

Trong trường hợp đặc biệt, $N = p^{k}, \phi(N) = p^{k-1} \* (p-1)$.

# Hàm Nhân tính

Để tính Phi hàm Euler nhanh hơn, các bạn cần biết về [Hàm Nhân Tính](/algo/math/multiplicative-function).

# Bài tập áp dụng:

- [VNOJ - VOSPOW](http://vnoi.info/problems/VOSPOW)
- [VNOJ - GCDSUM](http://vnoi.info/problems/GCDSUM/)
