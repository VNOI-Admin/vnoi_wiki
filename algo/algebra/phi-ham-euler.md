---
title: Phi hàm Euler
description: 
published: true
date: 2025-10-08T01:11:41.605Z
tags: 
editor: markdown
dateCreated: 2025-10-07T03:54:37.458Z
---

# Phi hàm Euler

**Tác giả:**

- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.

**Reviewer:**

- Phạm Vũ Phương - THPT Chuyên Hà Tĩnh, Hà Tĩnh.
- Nguyễn Quang Minh - Michigan State University.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

## Giới thiệu

**Hàm số Euler** hay **phi hàm Euler** của một số nguyên dương $n$ là số lượng số bé hơn hoặc bằng $n$ và nguyên tố cùng nhau với $n$. Kí hiệu của hàm số Euler là $\phi(n)$ (hoặc $\varphi(n)$).

## Cách tính

Từ định nghĩa, ta có thể tính được $\phi(p) = p - 1$ và $\phi(p^k) = p^k - p^{k-1}$ với $p$ là một số nguyên tố.

:::spoiler *Chứng minh*
Đối với $\phi(p) = p - 1$, ta dễ dàng thấy được rằng với các số $x$ từ $1$ đến $p-1$: $\text{UCLN}(x, p) = 1$ với $\text{UCLN}$ là hàm ước chung lớn nhất của hai số nguyên.

Đối với $\phi(p^k) = p^k - p^{k-1}$, ta thấy các số $x$ thoả mãn $\text{UCLN}(x, p^k) > 1$ chỉ có thể là các bội số của $p$, tức là các số thuộc tập hợp $\{p, 2p, 3p, \cdots, p^{k-1}p\}$. Vì trong $p^k$ số từ $1$ đến $p$ có $p^{k-1}$ số là bội số của $p$ nên ta có $p^k - p^{k-1}$ số nguyên tố cùng nhau với $p^k$.
:::

Nếu như ta đã biết trước giá trị phi hàm Euler của hai số $a$ và $b$, ta có thể tính được giá trị $\phi(ab)$.
- Nếu $a, b$ nguyên tố cùng nhau:
$$\phi(ab) = \phi(a) \times \phi(b)$$
- Nếu $a, b$ không nguyên tố cùng nhau, với $d = \text{UCLN}(a, b)$: 
$$\phi(ab) = \phi(a) \times \phi(b) \times \frac{d}{\phi(d)}$$

Từ các công thức trên, ta có thể tính giá trị phi hàm Euler của các số $n = p_1^{q_1}p_2^{q_2}\cdots p_k^{q_k}$ với $p$ là các số nguyên tố, $q$ là luỹ thừa tương ứng:

$$
\begin{align*}
\phi(n) &= \phi\left(\prod_{i = 1}^{k}p_i^{q_i}\right) \\
        &= \prod_{i = 1}^{k}\phi(p_i^{q_i}) \\
        &= \prod_{i = 1}^{k}(p_i^{q_i} - p_i^{q_i-1}) \\
		&= \prod_{i = 1}^{k} p_i^{q_i-1} (p_i - 1)
\end{align*}
$$

Ví dụ, $\phi(24) = \phi(2^3 \times 3^1) = 2^2 \times (2 - 1) \times 3^0 \times (3 - 1) = 8$.

Để đưa công thức trên vào chương trình, ta đơn giản hoá công thức để tăng tốc thuật toán. Ta có:

$$
\begin{align*}
\phi(n) &= \prod_{i = 1}^{k} p_i^{k_i-1} (p_i - 1) \\
		&= \prod_{i = 1}^{k} p_i^{k_i} \left (1 - \frac{1}{p_i}\right) \\
		&= n \times \prod_{i = 1}^{k} \left (1 - \frac{1}{p_i} \right)
\end{align*}
$$

Từ đây, ta có công thức tính $\phi(n)$ bằng:

$$\phi(n) = n \times \prod_{p|n} \left(1 - \frac{1}{p} \right)$$

Với $p$ là các ước nguyên tố của $n$.

```cpp=
int phi(int n){
	int totient = n;
	for(int i = 2; 1ll * i * i <= n; ++i){
		if(n % i == 0){ // i là số nguyên tố
			while(n % i == 0) n /= i;
			totient -= totient / i; // tương đương totient * (1 - 1/i)
		}
	}
	if(n != 1) totient -= totient / n;

	return totient;
}
```

Độ phức tạp của thuật toán bằng $O(\sqrt{n})$.

### Sàng phi hàm Euler

Ta có thể chỉnh sửa thuật toán [sàng số nguyên tố](https://wiki.vnoi.info/algo/algebra/prime_sieve.md) để tính giá trị phi hàm Euler của các số từ $1$ đến $n$.

```cpp=
int phi[N];

void sievePhi(int n){
    for(int i = 1; i <= n; ++i) phi[i] = i;
    for(int i = 2; i <= n; ++i){
        if(phi[i] == i){ // i là số nguyên tố
            for(int j = i; j <= n; j += i){
               phi[j] -= phi[j] / i;  // tương đương phi[j] * (1 - 1/i)
            }
        }
    }
}
```

Vì phi hàm Euler là một [hàm nhân tính](https://wiki.vnoi.info/algo/math/multiplicative-function), ta có thể tính giá trị phi hàm Euler dựa trên công thức

$$\phi(n) = n - \sum_{d|n}\phi(d)$$

Với $d$ là các ước của $n$ nhỏ hơn $n$.

```cpp=
int phi[N];

void sievePhi(int n){
    for(int i = 1; i <= n; ++i) phi[i] = i;
    for(int i = 1; i <= n; ++i){
        for(int j = i + i; j <= n; j += i){
           phi[j] -= phi[i];
        }
    }
}
```

## Ứng dụng

### Định lí Euler

Phi hàm Euler xuất hiện trong [định lí Euler](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%8Bnh_l%C3%BD_Euler): với hai số $a$ và $p$ nguyên tố cùng nhau, ta có:

$$a^{\phi(p)} \equiv 1 \pmod p$$

Từ đây, ta dễ dàng tính được giá trị [nghịch đảo modulo](https://wiki.vnoi.info/algo/math/modular-inverse#ngh%E1%BB%8Bch-%C4%91%E1%BA%A3o-modulo-1) của $a$ bằng $a^{\phi(p)-1} \bmod p$.

### Luỹ thừa

Với hai số $a$ và $p$ nguyên tố cùng nhau, nếu $c \equiv d \pmod{\phi(p)}$, thì:

$$a^c \equiv a^d \pmod p$$

Tính chất này rất hữu dụng khi ta muốn tính luỹ thừa bậc $b$ của $a$ với số mũ $b$ rất lớn:

$$a^b \equiv a^{b \bmod \phi(p)} \pmod p$$

## Bài toán ví dụ

### [ICPC 2023 miền Bắc - L: Euler](https://oj.vnoi.info/problem/icpc23_mb_l)

Tóm tắt đề: cho hai số $a$ và $b$ ($a, b \le 5\times 10^6$), tính:

$$\sum_{i = 1}^b \phi(a\times i)$$

với $a \times i$ là bội số thứ $i$ của $a$.

Dễ thấy, việc tính các $a \times i$ trước và tính giá trị phi hàm Euler của nó sẽ không hiệu quả, khi có tới tận $b$ bội số và giá trị các bội số có thể lên tới $25\times 10^{12}$.

Thay vì thế, ta có thể tính trước giá trị phi hàm Euler của các $i$ từ $1$ đến $b$ và giá trị $a$, sau đó áp dụng công thức tính phi hàm Euler của tích hai số để giải quyết bài toán.

```cpp=
#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
const int MOD = 998'244'353;
int phi[N];

int calcPhi(int n); // tính phi hàm Euler của n
void sievePhi(int n); // sàng phi hàm Euler từ 1 đến n
int mul(int a, int b); // tính (a * b) % MOD

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a, b; cin >> a >> b;
	sievePhi(b);
	int phiA = calcPhi(a); 
	long long sum = 0;
	for(int i = 1; i <= b; ++i){ 
		int g = __gcd(a, i);
		// phi(ab) = phi(a) * phi(b) * d / phi(d), g = UCLN(a, b)
		sum = sum + ((1ll * phi[i] * phiA / phi[g] * g) % MOD);
		sum %= MOD;
	}
	cout << sum;
	return 0;
}

int calcPhi(int n){
	int totient = n;
	for(int i = 2; 1ll * i * i <= n; ++i){
		if(n % i == 0){
			while(n % i == 0) n /= i;
			totient -= totient / i;
		}
	}
	if(n != 1) totient -= totient / n;

	return totient;
}


void sievePhi(int n) {
	for (int i = 0; i <= n; ++i) phi[i] = i;
	for (int i = 2; i <= n; ++i) {
		if (phi[i] == i) {
			for (int j = i; j <= n; j += i) {
				phi[j] -= phi[j] / i; 
			}
		}
	}
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}
```

Độ phức tạp thuật toán bằng $O(b\log{\log{b}} + \sqrt{a})$.

### [Tổng các ước chung lớn nhất](https://oj.vnoi.info/problem/gcdsum)

Tóm tắt đề: Cho nhiều số $N \le 10^6$. Với mỗi số $N$, tính giá trị của:

$$
\sum_{i-1}^{N-1} \sum_{j = i + 1}^{N} \text{UCLN}(i, j)
$$

Tất nhiên, chương trình trâu $O(n^2 \log n)$ sẽ không thể giải quyết bài toán này được. Ta cần tìm một tính chất nào đó của công thức trên giúp ta giải quyết bài toán nhanh hơn.

Đầu tiên, ta viết lại công thức như sau:

$$
\sum_{i-1}^{N-1} \sum_{j = i + 1}^{N} \text{UCLN}(i, j) = \sum_{i = 1}^{n} \text{sum}(i)
$$

Với $\text{sum}(i) = \sum_{j = 1}^{i-1} \text{UCLN}(i, j)$

Ta thấy, với $g = \text{UCLN}(i, j)$, ta suy ra được rằng: $\text{UCLN}\left(\frac{i}{g}, \frac{j}{g}\right) = 1$.

Từ đây, hàm $\text{sum}(n)$ có thể được viết lại bằng $\text{sum}(n) = \sum_{d | n} d \times \phi\left(\frac{n}{d}\right)$ với $d$ là các ước nguyên dương của $n$.

Kết luận, với mỗi số $N$, giá trị của công thức mà đề cho sẽ bằng:

$$
\begin{align*}
\sum_{i-1}^{N-1} \sum_{j = i + 1}^{N} \text{UCLN}(i, j) &= \sum_{i = 1}^{n} \text{sum}(i) \\
&= \sum_{i = 1}^{n} \sum_{j|i} j \times \phi\left(\frac{i}{j}\right)
\end{align*}
$$

```cpp=
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
ll phi[N];
ll sum[N];

void init();

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	int n;
	while(cin >> n, n){
		cout << sum[n] << '\n';
	}
	
	return 0;
}
void init(){
	for (int i = 0; i < N; ++i) phi[i] = i;
	for (int i = 2; i < N; ++i) {
		if (phi[i] == i) {
			for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
		}
	}
	for(int i = 1; i < N; ++i){
		for(int j = 2; i * j < N; ++j){
			sum[i * j] += i * phi[j];
		}
		sum[i] += sum[i - 1];
	}
}
```

Độ phức tạp thuật toán sẽ là $O(N \log \log {N})$ cho việc tính tất cả các trường hợp của $N$, và $O(1)$ cho mỗi số $N$ trong các truy vấn.

## Luyện tập

- [CSES - Exponentation II](https://cses.fi/problemset/task/1712)
- [Codeforces - The Holmes Children](https://codeforces.com/problemset/problem/776/E)
- [Codeforces - Please, another Queries on Array?](https://codeforces.com/contest/1114/problem/F)
- [Codeforces - REQ](https://codeforces.com/contest/594/problem/D)
- [SPOJ - INVPHI - Smallest Inverse Euler Totient Function](https://www.spoj.com/problems/INVPHI/)
- [SPOJ - DCEPCA03 - Totient Extreme](https://www.spoj.com/problems/DCEPCA03/)
- [VNOJ - Độ bá đạo của đội hình](https://oj.vnoi.info/problem/vospow)

