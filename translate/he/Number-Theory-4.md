# Số học 4 - Phi hàm Euler

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