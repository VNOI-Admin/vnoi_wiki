---
title: Giai thừa modulo p
description: 
published: true
date: 2025-03-23T03:26:07.629Z
tags: 
editor: markdown
dateCreated: 2024-04-08T11:13:28.577Z
---

# Giai thừa modulo p
**Người viết:**
- Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN

**Reviewer:**
- Phạm Công Minh - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Phạm Hoàng Hiệp - University of Georgia

# Giai thừa modulo p

## **Giới thiệu**
Khi giải các bài toán, đôi khi chúng ta sẽ gặp phải những công thức liên quan đến giai thừa, có thể ở trên tử, cũng có thể ở dưới mẫu như hệ số nhị thức. $n!$ là một hàm số nguyên tăng khá nhanh, nên thường chúng ta được yêu cầu tính toán nó theo một modulo $p$ nguyên tố nào đó.
Để giải quyết vấn đề đó trong bài viết này, trước hết chúng ta đi đến một số ký hiệu sau:
- $n!$ ($n$ giai thừa) là tích các số từ $1$ đến $n$:
    $$n! = 1 \cdot 2 \cdot 3 \cdots n$$
- $v_p(n)$ là số nguyên lớn nhất để $p^{v_p(n)}$ là ước của $n$.
<!-- $n!_{\%p}$ bằng $n!$ sau khi chia tất cả thừa số $p$:
    $$n!_{\%p} = \dfrac{n!}{v_p(n!)}$$
- $n!_p$ là tích các số từ $1$ đến $n$, không tính các số chia hết cho $p$: $\require{cancel}$
    $$n!_p = 1 \cdot 2 \cdots (p-1) \cancel{p} (p+1) \cdots (2p-1) \cancel{2p} (2p+1) \cdots n$$
- $$n!_{\%p}=\left(n\right)!_p \left(\left\lfloor\frac{n}{p}\right\rfloor\right)!_p \left(\left\lfloor\frac{n}{p^2}\right\rfloor\right)!_p\ldots$$
Như vậy, khi tính được $n!_p, \ldots$ ta hoàn toàn tính được $n!_{\%p}$.-->

## **Thuật toán "ngây thơ"**
Cách đơn giản nhất để tính $n! \bmod p$ là ta lần lượt nhân các số từ $1$ đến $n$:

```cpp=
factorial[0] = 1;
for (int i = 1; i <= n; i++) {
    factorial[i] = factorial[i - 1] * i % p;
}
```
Chú ý rằng nếu $n \ge p$ thì $n!$ luôn chia hết cho $p$.

Độ phức tạp: $O(n)$.

<!--Tuy nhiên, nếu $n \ge p$ thì $n!$ luôn chia hết cho $p$. Điều này sẽ gây bất lợi khi $n!$ ở dưới mẫu. Vì vậy, chúng ta sẽ tính $n!_p$ thay thế.
Ở đây, xin giới thiệu với bạn đọc **định lý Wilson**:
    $$(p - 1)! \equiv -1 \pmod p$$
    Áp dụng, ta có:
    $$n!_p \equiv (-1)^{\left\lfloor\frac{n}{p}\right\rfloor} \cdot (n \bmod p)! \pmod p$$
Nếu chuẩn bị trước $0!,~ 1!,~ 2!,~ \dots,~ (p-1)!$ ta có thể tính $n!_p$ trong thời gian $O(1)$ và $n!_{\%p}$ trong thời gian $O(\log_pn)$.

*Dưới đây là code C++ minh họa việc tính $n!_{\%p} \bmod p$*

```cpp=
int factmod(int n, int p) {
    vector<int> f(p);
    f[0] = 1;
    for (int i = 1; i < p; i++)
        f[i] = f[i-1] * i % p;

    int res = 1;
    while (n > 1) {
        if ((n/p) % 2)
            res = p - res;
        res = res * f[n%p] % p;
        n /= p;
    }
    return res;
}
```
-->

## **Công thức Legendre**
Phát biểu [công thức Legendre](https://vi.wikipedia.org/wiki/C%C3%B4ng_th%E1%BB%A9c_Legendre#):
$$v_p(n!) = \left\lfloor\frac{n}{p}\right\rfloor + \left\lfloor\frac{n}{p^2}\right\rfloor + \left\lfloor\frac{n}{p^3}\right\rfloor + \ldots$$
>Chú ý rằng khi $p^k > n$ thì $\left\lfloor\frac{n}{p^k}\right\rfloor = 0$, ta không cần tính tiếp

:::spoiler Chứng minh công thức Legendre
$v_p(n!)$ là số mũ của $p$ khi phân tích $n!$ ra thừa số nguyên tố, vì thế ta cần tính xem từ $1$ đến $n$ cho ta bao nhiêu thừa số $p$.
- Trong các số từ $1$ đến $n$, có $\left\lfloor\frac{n}{p}\right\rfloor$ số chia hết cho $p$. Mỗi số cho ta $1$ thừa số $p$.
- Trong các số chia hết cho $p$, lại có $\left\lfloor\frac{n}{p^2}\right\rfloor$ số chia hết cho $p^2$. Mỗi số cho ta thêm $1$ thừa số $p$ nữa.
- Trong các số chia hết cho $p^2$, lại có $\left\lfloor\frac{n}{p^3}\right\rfloor$ số chia hết cho $p^3$. Mỗi số cho ta thêm $1$ thừa số $p$ nữa.
- ... Cứ như vậy cho đến khi $\left\lfloor\frac{n}{p^k}\right\rfloor = 0$ thì ta kết thúc.
:::

*Code minh họa công thức Legendre:*
```cpp=
int vp(int n, int p) {
    int cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}
```
Độ phức tạp: $O(\log_p n)$

Bạn đọc có thể sử dụng công thức Legendre cùng sàng nguyên tố (đã chuẩn bị trước) để phân tích $n! = p_1^{k_1} \cdot p_2^{k_2} \cdots$ rồi tính $n!$ theo modulo bất kỳ với thuật toán lũy thừa nhanh.

Dưới đây là code được tham khảo từ [Geeksforgeeks](https://www.geeksforgeeks.org/compute-n-under-modulo-p/):
```cpp=
#include<bits/stdc++.h>
using namespace std;
const int N = 1000000; // 10^6
vector<int> primes;

// Công thức Legendre
int largestPower(int n, int p){
    int x = 0;
    while (n) {
    	n /= p;
    	x += n;
    }
    return x;
}

int binpow(int x, int y, int mod){
    int res = 1;
    x = x % mod;
    while (y) {
    	if (y & 1)
            res = (1LL * res * x) % mod;
        y >>= 1;
        x = (1LL* x * x) % mod;
    }
    return res;
}

// Sàng nguyên tố
void prepare(){
    bool isPrime[N + 1];
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= N; i++) {
    	if (isPrime[i]) {
    	    for (int j = i * i; j <= N; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    for (int i = 2; i <= N; i++) {
    	if (isPrime[i]) {
            primes.push_back(i);
        }
    }
}

int modFact(int n, int mod){
    int res = 1;
    for (int p : primes) {
    	if (p <= n) {
            int k = largestPower(n, p);
            res = (1LL * res * binpow(p, k, mod)) % mod;
        }
        else {
            break;
        }
    }
    return res;
}

int main(){
    prepare();
    int n, mod;
    cin >> n >> mod;
    cout << modFact(n, mod);
    return 0;
}
```
Độ phức tạp thời gian:
- Chuẩn bị: $O(N \log\log N)$
- Truy vấn: $O(N)$

## **Chia căn**
- *Điều kiện sử dụng:* $n < p \le 2 \cdot 10^9$ ($p$ không cần phải nguyên tố). 
Có thể chạy đến $5 \cdot 10^{10}$ tùy thuộc vào lượng hằng số có thể sử dụng.
- *Ý tưởng:*
    - Chia đoạn $[1;p]$ thành các đoạn riêng biệt có kích thước $S$, ta sẽ có tổng cộng $\text{CNT} = \left\lfloor \frac{p}{S} \right\rfloor + 1$ đoạn.
    - Ta sẽ tính sẵn một mảng gồm $\text{CNT}$ giá trị sau: $0!,\, S!,\, (2S)!,\, \ldots,\, \left(\left\lfloor \frac{p}{S} \right\rfloor \cdot S\right)!$ với độ phức tạp $O(p)$. Điều này không có ý nghĩa lắm. Vì thế, ta chỉ cần chạy code ra chương trình khác rồi lấy kết quả vào bài, bước này sẽ chỉ còn độ phức tạp $O\left(\frac{p}{S}\right)$ nhưng lại tăng độ dài của code!
    - Khi này, chọn $k = \left\lfloor \frac{n}{S} \right\rfloor$, ta có: $n! = (k\cdot S)! \times \underbrace{(k\cdot S + 1) \ldots n}_{{\text{Duyệt mất tối đa }} 10^6 {\text{ phép tính}}}$
- *Code C++ minh họa:*
    - Phần chuẩn bị:
    ```cpp=
    const int MOD = 1e9 + 7;
    const int S = 1e7;

    // Phần này thực hiện ở code khác 
    // và lấy kết quả vào mảng fact[] trong code chính.
    void prepare(){
        int tmp = 1;
        for (int i = 1; i < MOD; i++){
            tmp = 1LL * tmp * i % MOD;
            if (i % S == 0) {
                cout << tmp << ", ";
            }
        }
    }
    ```
    Kết quả in ra màn hình là một dãy: $1, 641102369, 578095319, 5832229, \ldots$
    Độ phức tạp phần chuẩn bị này là :$O(p)$.
    - Phần code chính:

    ```cpp=
    const int MOD = 1e9 + 7;
    const int S = 1e7;

    // Dãy được copy từ kết quả in ra của code bên trên
    int fact[] = {1, 641102369, 578095319, 5832229, ...};

    int get_fact(int n){
        int t = n / S;
        int res = fact[t];
        for (int i = t * S + 1; i <= n; i++)
            res = 1LL * res * i % MOD;
        return res;
    }
    ```
- *Đánh giá*:
    - Độ phức tạp không gian: $O\left(\dfrac{p}{S}\right)$
    - Độ phức tạp thời gian:
        - Tiền xử lý (để lưu mảng `fact[]`): $O\left(\dfrac{p}{S}\right)$ 
        - Truy vấn $O\left(S\right)$

Tùy thuộc vào giới hạn bài toán, giới hạn độ dài của code, ta sẽ chọn $S$ sao cho phù hợp.    

## **Biến đổi Fourier nhanh (FFT)**
>Trong bài này, ta sẽ sử dụng dạng Biến đổi số học - Number-theoretic transform (NTT) của FFT. Bạn đọc tham khảo tại [đây](https://en.wikipedia.org/wiki/Discrete_Fourier_transform_over_a_ring#Number-theoretic_transform).
Đây là thuật toán nhân hai đa thức bậc không vượt quá $n$ với độ phức tạp $O(n \log n)$.
- *Điều kiện sử dụng:* $n < p \le 10^{12}$
- *Ý tưởng:* Ta sẽ tính $n! \bmod p$ như sau:
    Xét $m = \left\lfloor \sqrt n \right\rfloor$ và đa thức $P(x) = (x+1)(x+2)\ldots (x + m) = \prod\limits_{i=1}^m (x+i)$
    Khi này:
    $$n! = \underbrace{P(0) \cdot P(m) \cdot P(2m) \ldots P\Big( (m-1)m \Big)}_{{\large\text{chính là }} 1\cdot 2\cdot 3 \ldots m ^ 2} \cdot \underbrace{(m^2 + 1)\ldots n}_{{\large\text{tính được trong }} O\left(\sqrt n\right)} \pmod p$$
### Cách 1: Sử dụng FFT đa điểm (FFT multipoint evaluation)
> Cách này sử dụng rất nhiều kiến thức khó và mang giá trị về nghiên cứu là chính. Vì thế, để tham khảo chi tiết, bạn đọc tham khảo tại [đây](https://www.cecm.sfu.ca/CAG/theses/justine.pdf). Tuy nhiên, các bài toán nhỏ mà nó sử dụng thật sự đáng để tham khảo và luyện tập.
- *Kiến thức sử dụng:* Biến đổi Fourier nhanh (FFT), chia để trị, chia đa thức.
- Đầu tiên, ta sử dụng **FFT/NTT** để khai triển đa thức $P(x)$ bên trên. Bạn đọc tham khảo bài tương tự của bước này: [960G - Bandit Blues - Codeforces](https://codeforces.com/contest/960/problem/G)
- Sau đó, ta tiếp tục sử dụng **FFT/NTT** để tính giá trị $P(x) \bmod M$ tại $m$ điểm: $k\cdot m$ với $k=0..(m-1)$. Đó cũng chính là bài toán [POLYEVAL - Codechef](https://discuss.codechef.com/t/polyeval-editorial/12771) hoặc [Library Checker - Multipoint Evaluation](https://judge.yosupo.jp/problem/multipoint_evaluation).
- Chú ý rằng [POLYEVAL - Codechef](https://discuss.codechef.com/t/polyeval-editorial/12771) là bài toán dễ hơn, và bạn có thể sử dụng chia để trị với không gian lưu trữ $O(p)$. Để làm được bài [Library Checker - Multipoint Evaluation](https://judge.yosupo.jp/problem/multipoint_evaluation), ta sử dụng thuật toán chia để trị và chia đa thức để đạt được không gian lưu trữ $O\left(\sqrt p\right)$:
    - Ta thấy, $P(x) = Q(x) \cdot (x-k) + P(k) \implies P(k) = P(x) \mod (x - k)$.
    - Giả sử cần tính $P(x)$ tại $x_1, x_2, \ldots, x_n$. Mỗi lần, ta chia $P(x)$ thành $2$ đa thức (*Chú ý rằng, phép chia đa thức sẽ được chuyển thành nhân với đa thức nghịch đảo để sử dụng FFT*):
$$\begin{align*}
P_0(x) &= P(x) \mod \Big((x-x_1)(x-x_2)\cdots(x-x_{\lfloor n/2 \rfloor})\Big)\\
P_1(x) &= P(x) \mod \Big((x-x_{n/2+1})\cdots(x-x_n)\Big)
\end{align*}$$
$$\implies\begin{align*}
P(x) &= \Big((x-x_1)(x-x_2)\cdots(x-x_{\lfloor n/2 \rfloor})\Big) \cdot Q_0(x) + P_0(x)\\
P(x) &= \Big((x-x_{\lfloor n/2 \rfloor+1})\cdots(x-x_n)\Big) \cdot Q_1(x) + P_1(x)
\end{align*}$$
$$\implies\begin{align*} 
P(x_i) = \begin{cases}
											P_0(x_i) &{\large\text{nếu }}i\le \lfloor n/2 \rfloor\\
P_1(x_i) &{\large\text{còn lại}}\end{cases}
\end{align*}$$

- Bài toán trở thành: Tính $P_0(x)$ tại $x_1, \cdots, x_{\lfloor n/2 \rfloor}$ và tính $P_1(x)$ tại $x_{\lfloor n/2 \rfloor+1}, \cdots, x_n$.
- *Đánh giá:*
    - Độ phức tạp không gian: $O\left(\sqrt p\right)$
    - Độ phức tạp thời gian: $O\left(\sqrt p \log^2 p\right)$
### Cách 2: Kết hợp sử dụng nội suy Lagrange
- ***Kiến thức sử dụng:*** Biến đổi Fourier nhanh (FFT), nội suy Lagrange (Lagrange Interpolation).
- ***Ý tưởng***:
  - Tương tự với [thuật toán lũy thừa nhanh](/algo/algebra/binary_exponentation.md), ta chia tích các đa thức cần tính thành 2 phần:
    - *Phần 1*: $P(0) \cdot P(m) \cdot P(2m) \ldots P\Big( \left\lfloor(m-1)/2\right\rfloor \times m \Big)$
    - *Phần 2*: $P\Big( \left\lfloor(m+1)/2\right\rfloor \times m \Big) \ldots P\Big( (m-1) \times m \Big)$
  - Mấu chốt của thuật toán này là ta có thể sử dụng Nội suy Lagrange để tính giá trị *Phần 2* từ việc tính toán *Phần 1*.
- ***Chi tiết thuật toán***:
    - Đặt **đa thức giai thừa** $P_d(x)$ là một đa thức bậc $d$ có dạng:
      $$P_d(x) = \prod\limits_{i=1}^d (x+i)$$
    - Xét tập hợp các đa thức:
      $$G_d(x) = \bigg\{ P_d(x), P_d(m +x), P_d(2m+x), \ldots, P_d\Big( (m-1)m+x \Big) \bigg\}$$
      Mục tiêu của ta là tính $(m^2)!$ hay toàn bộ giá trị của tập $G_m(0)$.
    - Tương tự [thuật toán lũy thừa nhanh](/algo/algebra/binary_exponentation.md), có thể xây dựng $P_d(x)$ một cách **đệ quy** như sau: $P_1(0) = 1$ và
      
      $$P_{d}(x) = \begin{align*}
      \begin{cases}
        P_{d/2}(x) \cdot P_{d/2}(x+d/2) &\text{if } d \text{ is even}\\
      P_{\lfloor d/2 \rfloor}(x) \cdot P_{\lfloor d/2 \rfloor}\big(x+\lfloor d/2 \rfloor\big)\cdot (x + d + 1) &\text{if } d \text{ is odd}
      \end{cases}
      \end{align*}$$
    	
      $\implies$ Như vậy để tính tập $G_{d}(0)$, ta cần tính tập $G_{d/2}(0)$ và $G_{d/2}(d/2)$. Và cứ đệ quy như vậy đến khi dừng.
     - Tuy nhiên, điểm đặc biệt của thuật toán này là để tính tập $G_{d/2}(d/2)$, ta sẽ không đệ quy xuống để tính mà sẽ tận dụng tập $G_{d/2}(0)$ đã tính toán:
       - Trước hết, ta đi đến một bổ đề:
          :::info
          **Bổ đề:** Cho đa thức $h(x)$ có bậc là $d$ và biết $h(0), h(1), \ldots, h(d)$. Ta cần tính $h(x), h(x+1), \dots, h(x+d')$. Với công thức nội suy Lagrange, $\forall k = 1,2,\ldots d'$, ta có:
          $$ \begin{align*} h(x + k) &= \sum_{i = 0}^d h(i) \prod_{j=0, i \neq j}^d \frac{x+k-j}{i-j} \\\ &= \left(\prod_{j=0}^d (x + k - j) \right) \underbrace{\left( \sum_{i=0}^d \underbrace{\frac{h(i)}{i! (d-i)! (-1)^{d-i}}}_{\text{Hệ số bậc } i} \cdot \underbrace{\frac{1}{x + k - i}}_{\text{Hệ số bậc } x+k-i} \right)}_{\text{Sử dụng FFT/NTT ở đây, hệ số bậc }   x+k} \end{align*} $$
          :::
       - Áp dụng bổ để trên với $h(i) = P_d(i \cdot m)$ và $x = d\cdot m^{-1}$ cùng với việc ta đã tính tập sau (bằng đệ quy):
        	$$\begin{align*}G_d(0) = \Big\{h(0), h(1), \ldots, h(d)\Big\}\end{align*}$$ 
        	Ta sẽ tính tiếp được:
        	$$\begin{align*}h(x + i) = P_d((x + i) \cdot m) = P_d(i\cdot m + d)\end{align*}$$
     Và đây cũng chính là tập $G_d(d)$ cần tính!
        
- *Code C++ minh họa (lược bỏ phần FFT)*
```cpp=
int MOD;

// hàm trả về nghịch đảo x modulo MOD
long long inv(long long x);

// hàm trả về đa thức a * b
vector<long long> NTT(vector<long long> a, vector<long long> b);

void mul(long long &x, long long y){
    x = __int128(x) * y % MOD;
}

// Biết h(0), h(1), ..., h(d)
// Hàm trả về h(m), h(m + 1), ..., h(m + cnt - 1)
// m > d
vector<long long> Lagrange(vector<long long> h, long long m, int cnt){
    int d = h.size() - 1;
    // tính h[i] = (-1)^(d-i) h(i)/(i! (d-i)!)
    // hệ số x^i
    for (int i = 0; i <= d; i++){
        mul(h[i], (ifact[i] * ifact[d - i]) % MOD);
        if ((d - i) & 1)
            h[i] = (MOD - h[i]) % MOD;
    }

    //tính f[i] = 1/(m+i-d)
    // hệ số x^(m + cnt - 1 - i)
    vector<long long> f(d + cnt);
    long long now = m - d;

    for (int i = 0; i < d + cnt; i++)
        f[i] = inv(now+i);

    // Nhân 2 đa thức và hệ số được lấy mod p
    h = NTT(f, h);
    h.resize(d + cnt);
    // chỉ lấy hệ số x^(m) đến x^(m+cnt-1)
    h = vector<long long>(h.begin() + d, h.end());
    now = 1;

    for (int i = 0; i <= d; i++)
        mul(now, m - i);

    mul(h[0], now);

    for (int i = 1; i < cnt; i++){
        mul(now, m + i);
        mul(now, inv(m + i - d - 1));
        mul(h[i], now);
    }

    return h;
}

long long factorial(long long n, long long p){
    if (n >= p) return 0;
    if (n < 2) return 1;
    int s = __builtin_sqrtl(n);
    MOD = p;
    vector<long long> h{1, s + 1};
    for (int bit = __lg(s) - 1, d = 1; bit >= 0; bit--){
        // Hiện tại h(i) = (i * s + 1) * (i * s + 1) ... (i * s + d)
        // Tính h(d+1), ..., h(2d)
        auto nh1 = Lagrange(h, d + 1, d);
        // Tính h(d.inv(s)), ..., h(d.inv(s) + 2d)
        // Như vậy, nh2(i) = (i * s + d + 1) * (i * s + d + 2) ... (i * s + d * 2)
        auto nh2 = Lagrange(h, 1LL * inv(s) * d % mod, 2 * d + 1);
        // h giờ đây là h(0), h(1), ..., h(2d)
        h.insert(h.end(), nh1.begin(), nh1.end());
        // d --> d * 2
        d <<= 1;

        // Hiện tại h(i) = (i * s + 1) * (i * s + 2) ... (i * s + d/2)
        // Còn nh2(i) = (i * s + d/2 + 1) * (i * s + d/2 + 2) ... (i * s + d)
        for (int i = 0 ; i <= d; i++)
            h[i] *= nh2[i];
        // Tại đây h(i) = (i * s + 1) * (i * s + 1) ... (i * s + d)

        // Nếu bit hiện tại của s là 1
        if (s >> bit & 1){
            d |= 1;
            long long tmp = d;

            // h[i] *= (d + i * s)
            for (int i = 0; i < d; i++, tmp += s)
                mul(h[i], tmp);

            long long last = 1, tj = 1LL * s * d;

            // last = (d*s+1)(d*s+2)...(d*s+d)
            for (int i = 1; i <= d; i++)
                tj++, last *= tj;
            
            // Thêm biến last vào h
            h.emplace_back(last);
        }
    }
    long long ans = 1;

    for (int i = 0; i < s; i++)
        mul(ans, h[i]);

    for (long long i = 1LL * s * s + 1; i <= n; i++)
        mul(ans, i);

    return ans;
}

```

Bạn đọc có thể tham khảo code đầy đủ của [yosupo](/algo/math/factorial.cpp) hoặc của [tác giả](/algo/math/factorial2.cpp).
    
- ***Đánh giá:***
    - Độ phức tạp không gian: $O(\sqrt n)$
    - Độ phức tạp thời gian: 
        - Hàm Lagrange ở phần sử dụng sử dụng FFT có độ phức tạp $O(N \log N)$ với $N = \deg(h) + \text{cnt}$. 
        Các vòng lặp khác chỉ có độ phức tạp tối đa đến $O(N)$.
        - Hàm factorial có độ phức tạp lớn nhất ở phần sử dụng hàm Lagrange với tổng cộng: $O\left(s\log s + \frac{s}{2}\log\frac{s}{2} + \frac{s}{4}\log\frac{s}{4} + \ldots \right)$ với $s = \lfloor \sqrt n \rfloor$. Chú ý rằng: 
          $$\begin{align}
          s\log s + \frac{s}{2}\log\frac{s}{2} + \frac{s}{4}\log\frac{s}{4} + \ldots &< s\log s + \frac{s}{2}\log s + \frac{s}{4}\log s + \ldots\\
          &= \log s \cdot \left(s+ \frac{s}{2} + \frac{s}{4} + \ldots\right)\\
          &< 2s\log s
          \end{align}$$
        - Điều này có nghĩa là bài toán có tổng độ phức tạp: $O\left(\sqrt n \log n\right)$

    
## Bài tập luyện tập
[Hackerearth - Army Parade](https://www.hackerearth.com/fr/problem/algorithm/army-parade-7bcfea8e/)
[SPOJ - FACTMODP](https://www.spoj.com/problems/FACTMODP/)

## Tài liệu tham khảo
[GeeksforGeeks - Compute n! under modulo p](https://www.geeksforgeeks.org/compute-n-under-modulo-p/)
[FFT - multipoint evaluation](https://cs.stackexchange.com/questions/60239/multi-point-evaluations-of-a-polynomial-mod-p)
[Factorial mod prime - Prabowo Djonatan](https://blog.prabowodjonatan.id/posts/factorial-mod-p/)
[Codeforces - Fastest way to get factorial modulo a prime](https://codeforces.com/blog/entry/63491?#comment-474051)
[Codeforces - How to calculate n!%p for very large 'n' ?](https://codeforces.com/blog/entry/69002)