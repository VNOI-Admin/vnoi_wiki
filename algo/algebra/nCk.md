# Cách tính số tổ hợp

**Người viết:**
- Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN

**Reviewer:**
- Phạm Công Minh - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Nguyễn Đức Kiên - Trường Đại học Công nghệ, ĐHQGHN
- Nguyễn Minh Nhật - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN

[[_TOC_]]
## Tổ hợp (Combination)
### Giới thiệu về tổ hợp
Trong toán học, tổ hợp là cách chọn các phần tử từ một nhóm mà không phân biệt thứ tự chọn. Mỗi tập con gồm $k$ phần tử khác nhau (không phân biệt thứ tự) của tập hợp $n$ phần tử đã cho ($0 ≤ k ≤ n$) được gọi là một tổ hợp chập $k$ của $n$ phần tử.
Số các tổ hợp chập $k$ của $n$ phần tử khác nhau được kí hiệu là $C_n^k$ hoặc $\dbinom{n}{k}$:

$$C_n^k  = \dbinom{n}{k} = \dfrac{n!}{k! (n - k)!} = \dfrac{n(n-1)\ldots(n - k + 1)}{k!},\, 0 ≤ k ≤ n$$

Để bạn đọc tiện theo dõi, trong bài viết này, chúng ta thống nhất sử dụng ký hiệu $C_n^k$.
Ta quy ước:
- $C_n^0  = 1$ với mọi $n \ge 0$
- Nếu $k > n$ thì $C_n^k  = 0$


### Một số tính chất của tổ hợp
- Với mọi $n ≥ 1$ và $0 ≤ k ≤ n$, ta có:
    - $C_n^k = C_n^{n - k}$
    - $C_n^k = C_{n - 1}^{k - 1} + C_{n - 1}^{k}$
    

- $C_n^k$ còn được gọi là hệ số nhị thức (binomial coefficients) do $C_n^k$ là hệ số trong khai triển:
$$(x + y)^n= \sum\limits_{k = 0}^{n} C_n^k \cdot x^k \cdot y ^ {n - k}$$

## Tính số tổ hợp
### Sử dụng định nghĩa
$$C_n^k = \dfrac{n!}{k! (n - k)!}$$
- Với công thức này, ta nghĩ ngay đến một thuật toán "ngây thơ": Tính $n!$, $k!$ và  $(n - k)!$. Từ đó tính được $C_n^k$.

```cpp
long long res = 1;
for (int i = 1; i <= n; i++) res = res * i;
for (int i = 1; i <= k; i++) res = res / i;
for (int i = 1; i <= n-k; i++) res = res / i;
```

- Mở rộng hơn, ta có thể biến đổi một chút như sau:

$$C_n^k = \dfrac{n}{1} \cdot \dfrac{n - 1}{2} \ldots \dfrac{n - k + 1}{k} = \dfrac{C_{n-1}^{k-1} \cdot (n - k + 1)}{k}$$

Vì $C_n^k$ là số nguyên, nên bạn yên tâm rằng $C_{n-1}^{k-1} \cdot (n - k + 1)$ luôn chia hết cho $k$.

```cpp
long long res = 1;
for (int i = 1; i <= k; i++)
    res = res * (n - i + 1) / i;
```

- Hai cách tiếp cận trên rất tự nhiên, dễ nghĩ, dễ thực hiện nhưng lại có một trở ngại: giá trị của $n!$ có thể rất lớn (khi $n = 20$ thì $n! \approx 2.42\times10^{18}$)

### Sử dụng công thức truy hồi

$$\begin{align*}
C_n^k=\begin{cases}
1 &\text{nếu } k = 0 \text{ và } n \ge 0\\
0 &\text{nếu } k > n\\
C_{n - 1}^{k - 1} + C_{n - 1}^{k} &\text{trong các trường hợp còn lại}
\end{cases}
\end{align*}$$

Với công thức truy hồi này, ta sẽ sử dụng một mảng hai chiều `C[n][k]` để tính $C_n^k$

**Code C++ minh họa**
```cpp
for (int i = 0; i <= n; i++){
    C[i][0] = 1;
    for (int k = 1; k <= i; k++){
        C[i][k] = C[i - 1][k - 1] + C[i - 1][k];
    }
}
```

Độ phức tạp không gian: $O(n^2)$
Độ phức tạp thời gian:
- Tiền xử lý: $O(n^2)$
- Truy vấn: $O(1)$

## Tính số tổ hợp theo modulo M
Vì kết quả của $C_n^k$ có thể rất lớn nên trong lập trình thi đấu, thí sinh thường được yêu cầu tính $C_n^k$ theo một modulo $M$ nào đó (phần dư của phép chia $C_n^k$ cho $M$).
Dưới đây là một số cách sử dụng để tính $C_n^k$ theo modulo $M$.
*Chú ý rằng độ phức tạp dưới đây được tính toán khi sử dụng một modulo $M$ cho toàn bài!*


|                                     Cách                                      |   Tiền xử lý    |        Truy vấn        |  Bộ nhớ  |   Độ khó   |                  Giới hạn                  |
|:-----------------------------------------------------------------------------:|:---------------:|:----------------------:|:--------:|:----------:|:------------------------------------------:|
|          [Sử dụng công thức truy hồi](#Sử-dụng-công-thức-truy-hồi1)           |    $O(n^2)$     |         $O(1)$         | $O(n^2)$ |   Cơ bản   |         $M$ bất kỳ, $n \sim 5000$          |
|                  [Sử dụng định nghĩa](#Sử-dụng-định-nghĩa1)                   | $O(n + \log M)$ |         $O(1)$         |  $O(n)$  |   Cơ bản   |    $M$ nguyên tố, $n < M, n \sim 10^6$     |
|                [Sử dụng định lý Lucas](#Sử-dụng-định-lý-Lucas)                |     $O(M)$      | $O\big(\log_M(n)\big)$ |  $O(M)$  | Trung bình |        $M$ nguyên tố, $M \sim 10^6$        |
|        [Sử dụng định lý Lucas mở rộng](#Sử-dụng-định-lý-Lucas-mở-rộng)        |     $O(M)$      | $O\big(\log_p(n)\big)$ |  $O(M)$  | Trung bình | $M = p^q$ với $p$ nguyên tố, $M \sim 10^6$ |
| [Sử dụng định lý thặng dư Trung Hoa](#Sử-dụng-định-lý-thặng-dư-Trung-Hoa) |                 |                        |          | Trung bình |                 $M$ bất kỳ                 |

Ngoài ra còn có hai cách tính dựa trên cách tính giai thừa modulo $M$ khá hiệu quả. Tham khảo thêm tại [đây](https://hackmd.io/vEuqGacrS-iS9SCBJ_5anQ?view). Dưới đây là đánh giá về hai cách đó:

|     Cách     |         Tiền xử lý          |           Truy vấn            |           Bộ nhớ            | Độ khó |              Giới hạn              |
|:------------:|:---------------------------:|:-----------------------------:|:---------------------------:|:------:|:----------------------------------:|
|   Chia căn   | $O\left(\frac{M}{S}\right)$ | $O\left(S+\frac{M}{S}\right)$ | $O\left(\frac{M}{S}\right)$ | Cơ bản |      $n < M \le 2 \cdot 10^9$      |
| Biến đổi FFT |            không            | $O\left(\sqrt M\log M\right)$ |   $O\left(\sqrt M\right)$   |  Khó   | $M$ nguyên tố, $n < M \le 10^{12}$ |

---
### Sử dụng công thức truy hồi
Ở đây, ta sẽ sử dụng công thức truy hồi ở trên và thay đổi một chút:
$$C_n^k = (C_{n - 1}^{k - 1} + C_{n - 1}^{k}) \mod M$$

**Code C++ minh họa**
```cpp
for (int i = 0; i <= n; i++){
    C[i][0] = 1 % MOD;
    for (int k = 1; k <= i; k++){
        C[i][k] = (C[i - 1][k - 1] + C[i - 1][k]) % MOD;
    }
}
```

Độ phức tạp không gian: $O(n^2)$
Độ phức tạp thời gian:
- Tiền xử lý: $O(n^2)$
- Truy vấn: $O(1)$

>Nhận xét: Đây là cách đơn giản, dễ nghĩ, dễ code đúng, nên sử dụng trong trường hợp $n$ nhỏ để tiết kiệm thời gian.

---
### Sử dụng định nghĩa
Rào cản lớn nhất cho việc sử dụng định nghĩa $C_n^k = \dfrac{n!}{k! (n - k)!}$ là $n!$ quá lớn. Tuy nhiên khi ta cần lấy kết quả theo modulo $M$, đó lại là vấn đề khác.

- **Điều kiện sử dụng:** $M$ nguyên tố và $n < M$
- **Kiến thức sử dụng:**
    - *Nghịch đảo modulo (Modular Inverse)*: Tham khảo ở bài viết [Số học 4.5 - Nghịch đảo modulo](https://vnoi.info/wiki/algo/math/modular-inverse) của VNOI.
    - *Định lý Fermat nhỏ*
    :::spoiler 
    Cho $p$ là một số nguyên tố và số nguyên $a$ không chia hết cho $p$. Khi đó, ta có:
    $$a^{p - 1} \equiv 1 \pmod p$$
    Từ đó, ta rút ra:
    $$a^{-1} \equiv a^{p-2} \pmod p$$
    :::
    - *Lũy thừa nhanh*
- **Ý tưởng:**
    - Ta viết lại: 
$$C_n^k = n! \times \left( k! \right)^{-1} \times \left( (n - k)! \right)^{-1} \mod M$$
    - Ta sử dụng hai mảng: mảng $\text{fact}[i]$ để lưu $i! \bmod M$ và mảng $\text{ifact}[i]$ để lưu $(i!)^{-1} \bmod M$. Sau đó dùng công thức (sử dụng định lý Fermat nhỏ):

        $$\text{ifact}[i] = (\text{fact}[i]) ^ {-1} \bmod M = (\text{fact}[i])^{M-2} \bmod M$$

        Chú ý rằng $\text{fact}[i] \equiv 0 \pmod M \;\;\forall i \ge M$ nên ta chỉ tính $\text{fact}[i]$ và $\text{ifact}[i]$ với $0 \le i \le M - 1$.
        
    - Ta sẽ tính mảng $\text{fact}[i]$ như sau:
    
    $$\begin{align}
        \begin{cases}
        \text{fact}[0] &= 1\\
        \text{fact}[i] &= (\text{fact}[i - 1] \times i ) \bmod M &\text{ nếu } 1 \le i \le n
        \end{cases}
    \end{align}$$
    
    - Tiếp theo ta sử dụng thuật toán lũy thừa nhanh để tính $\text{ifact}[n] = \left( \text{fact}[n] \right)^{M-2} \mod M$ với độ phức tạp $O(\log M)$.
    - Còn mảng $\text{ifact}[i]$ thì tính như sau:
    
    $$\begin{align}
        \begin{cases}
        \text{ifact}[n] &= \left( \text{fact}[n] \right)^{M-2} &\mod M\\
        \text{ifact}[i - 1] &= \text{ifact}[i] \times i  &\mod M  &\text{nếu } 1 \le i \le n
        \end{cases}
    \end{align}$$
    
    - Cuối cùng, $C_n^k = \text{fact}[n] \times \text{ifact}[k] \times \text{ifact}[n - k] \mod M$.

**Code C++ minh họa**
```cpp
const int MOD = 1e9 + 7;
const int N = 1e6;
int fact[N + 5], ifact[N + 5];

// Hàm lũy thừa nhanh
long long binpow(long long a, long long b) {
    long long ans = 1;
    while (b > 0){
        if (b % 2) ans = ans * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return ans;
}

// Chuẩn bị
void prepare(){
    // Tính fact[]
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = 1LL * fact[i - 1] * i % MOD;
        
    // Tính ifact[]
    ifact[N] = binpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 1; i--)
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
}

// Hàm tính nCk
int C(int n, int k){
    if (k > n) return 0;
    return (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}

int main(){
    prepare();        
    // Truy vấn
    int q; cin >> q;
    while (q--){
        int n, k; cin >> n >> k;
        cout << C(n, k) << '\n';
    }
}
```

Độ phức tạp không gian: $O(n)$
Độ phức tạp thời gian:
- Tiền xử lý: $O(n + \log M)$
- Truy vấn: $O(1)$

### Sử dụng định lý Lucas
Đây là cải tiến của cách sử dụng định nghĩa để có thể sử dụng cho $n > M$
- **Điều kiện sử dụng:** $M$ nguyên tố
- **Ý tưởng:** Các bạn có thể tham khảo tại bài viết [Định lý Lucas của VNOI](https://vnoi.info/wiki/translate/he/Lucas-theorem.md)

**Code C++ minh họa**
```cpp
int C(long long n, long long k){...} // hàm tính Ckn sử dụng định nghĩa bên trên
int comb(long long n, long long k){
    if (k > n) return 0;
    int res = 1;
    while (n > 0){
        res = 1LL * res * C(n % MOD, k % MOD) % MOD;
        n /= MOD; k/= MOD;
    }
    return res;
}
```

<details>
<summary>Bạn đọc tham khảo thêm code đầy đủ ở đây</summary>
```cpp
const int MOD = 1e6 + 3;
int fact[MOD + 5], ifact[MOD + 5];

// Hàm lũy thừa nhanh
long long binpow(long long a, long long b) {
    long long ans = 1;
    while (b > 0){
        if (b % 2) ans = ans * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return ans;
}

// Chuẩn bị
void prepare(){
    // Tính fact[]
    fact[0] = 1;
    for (int i = 1; i < MOD; i++)
        fact[i] = 1LL * fact[i - 1] * i % MOD;
        
    // Tính ifact[]
    ifact[MOD - 1] = binpow(fact[MOD - 1], MOD - 2);
    for (int i = MOD - 2; i >= 0; i--)
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
}

// Hàm tính nCk với n < M
int C(int n, int k){
    if (k > n) return 0;
    return (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}

// Hàm tính nCk với n có thể lớn hơn M
int comb(long long n, long long k){
    if (k > n) return 0;
    int res = 1;
    while (n > 0){
        res = 1LL * res * C(n % MOD, k % MOD) % MOD;
        n /= MOD; k/= MOD;
    }
    return res;
}

int main(){
    prepare();        
    // Truy vấn
    int q; cin >> q;
    while (q--){
        long long n, k; cin >> n >> k;
        cout << comb(n, k) << '\n';
    }
    
}
```
</details>

Độ phức tạp không gian: $O(M)$
Độ phức tạp thời gian:
- Tiền xử lý: $O(M)$
- Truy vấn: $O\big(\log_M(n)\big)$

### Sử dụng định lý Lucas mở rộng
- **Điều kiện sử dụng:** $M$ lũy thừa của số nguyên tố
- **Kiến thức sử dụng:**
    - *Nghịch đảo modulo, lũy thừa nhanh*
    - *Định lý Euler (mở rộng của định lý Fermat nhỏ)*
        Cho $2$ số nguyên $a, m$ nguyên tố cùng nhau. Khi đó, ta có: $a^{\varphi(m)} \equiv 1 \pmod m$.

        Trong đó, $\varphi(m)$ là hàm phi Euler: $\varphi(m) = m \cdot \prod\limits_{p \text{ nguyên tố}, p \mid m} \dfrac{p - 1}{p}$.
        Từ đó, ta rút ra:
        $$a^{-1} \equiv a^{\varphi(m)-1} \pmod p$$
    - *Mở rộng định lý Lucas cho modulo là lũy thừa số nguyên tố*:
        Andrew Granville đã chứng minh được công thức sau: (Xem bài báo tại [đây](https://web.archive.org/web/20170202003812/http://www.dms.umontreal.ca/~andrew/PDF/BinCoeff.pdf) hoặc tại [đây](http://www.cecm.sfu.ca/organics/papers/granville/paper/binomial/html/node2.html))
    
        $$\dfrac{t^{e_q}}{p^{e_1}} C_n^k \equiv \dfrac{(n_0!)_p}{(k_0!)_p(r_0!)_p} \cdot \dfrac{(n_1!)_p}{(k_1!)_p(r_1!)_p} \ldots \dfrac{(n_d!)_p}{(k_d!)_p(r_d!)_p} \,(\bmod p^q)$$

        Trong đó:
        - $t = \begin{align}
        \begin{cases}
        1 &\text{ nếu } p = 2 \text{ và } q \ge 3\\
        -1&\text{ còn lại}
        \end{cases}
        \end{align}$
        - $e_j = \sum\limits_{i \ge j} \left( \left\lfloor \dfrac{n}{p^i} \right\rfloor - \left\lfloor \dfrac{k}{p^i} \right\rfloor - \left\lfloor \dfrac{r}{p^i} \right\rfloor \right)$
        Bạn đọc có thể thấy, $e_1$ là số mũ của $p$ khi phân tích $C_n^k$ ra thừa số nguyên tố.
        - $\left( n! \right)_p$ là tích tất cả các số từ $1$ đến $n$ và không bao gồm các số chia hết cho $p$ (với $p$ là số nguyên tố).
        - $r = n-k$
        - $n_i = \left\lfloor \dfrac{n}{p^i} \right\rfloor \bmod p ^ q$
        - $k_i, r_i$ định nghĩa tương tự $n_i$
        - $d$ là vị trí cuối cùng mà $n_i \neq 0$.  Nghĩa là ta chỉ cần chạy cho đến khi $n_i = 0$.

**Chi tiết các bước:**
```cpp
const int MOD = 27;
const int prime = 3;
long long fact[MOD], ifact[MOD];
```
- Chú ý rằng ở bước chuẩn bị, $\text{fact}[i]$ sử dụng để lưu $\left( i! \right)_p$ (*Xem phần mô tả mở rộng định lý Lucas*) thay vì $i!$ và ta cần sử dụng định lý Euler thay cho định lý Fermat nhỏ.
```cpp
void init(){
    fact[0] = 1;
    for (int i = 1; i < MOD; i++) {
        if (i % prime != 0)
            fact[i] = (fact[i - 1] * i) % MOD;
        else
            fact[i] = fact[i - 1];
    }
    int phi = MOD / prime * (prime - 1) - 1;
    ifact[MOD - 1] = binpow(fact[MOD - 1], phi, MOD);
    for (int i = MOD - 1; i > 0; i--) {
        if (i % prime != 0)
            ifact[i - 1] = (ifact[i] * i) % MOD;
        else
            ifact[i - 1] = ifact[i];
    }
}
```
- Tiếp theo ta sử dụng công thức bên trên
```cpp
long long C(long long N, long long K, long long R){
    return (fact[N] * ifact[R] % MOD) * ifact[K] % MOD;
}

int count_carry(long long n, long long k, long long r, int p, long long t){
    long long res = 0;
    while (n >= t) {
        res += ((n / t) - (k / t) - (r / t));
        t *= p;
    }
    return res;
}

long long calc(long long N, long long K, long long R) {
    if (K > N)
        return 0;
    long long res = 1;
    int vp = count_carry(N, K, R, prime, prime);
    int vp2 = count_carry(N, K, R, prime, MOD);
    while (N > 0) {
        res = (res * C(N % MOD, K % MOD, R % MOD)) % MOD;
        N /= prime; K /= prime; R /= prime;
    }
    res = res * binpow(prime, vp, MOD) % MOD;
    if ((vp2 % 2 == 1) && (prime != 2 || MOD <= 4))
        res = (MOD - res) % MOD;
    return res;
}
```

Độ phức tạp không gian: $O(M)$
Độ phức tạp thời gian:
- Tiền xử lý: $O(M)$
- Truy vấn: $O\big(\log_p(n)\big)$

### Sử dụng định lý thặng dư Trung Hoa
Định lý thặng dư Trung Hoa là cầu nối giúp ta tính toán được khi $M$ không phải là số nguyên tố.
- **Kiến thức sử dụng:**
    - *Định lý Thặng dư trung hoa - Chinese remainder theorem (CRT)*
    
        Xét hệ:
        
        $$\left\{\begin{array}{rcl}
            a & \equiv & a_1 \pmod{m_1} \\
            a & \equiv & a_2 \pmod{m_2} \\
              & \vdots & \\
            a & \equiv & a_k \pmod{m_k}
        \end{array}\right.$$
        
        với $m_1, m_2, \ldots m_k$ đôi một nguyên tố cùng nhau.
    
        Ký hiệu: 
        - $M = m_1 \cdot m_2 \ldots m_k$
        
        - $M_i = \dfrac{M}{m_i}$
        
        - $N_i = M_i^{-1} \mod m_i$
    
        Từ đó nhận thấy:
        
        $$\left\{\begin{array}{rcl}
            a_i M_i N_i & \equiv & a_i \pmod{m_i} \\
            a_j M_j N_j & \equiv & 0 \pmod{m_i} \,\,\forall j \neq i
        \end{array}\right.$$
    
        Khi này chỉ cần cộng tất cả số hạng $a_i M_i N_i$ ta được một nghiệm thỏa mãn hệ:
        $$a = a_1 M_1 N_1 + a_2 M_2 N_2 + \ldots + a_k M_k N_k$$
   

Để minh họa rõ hơn này, ta sẽ giải quyết bài [nCr](https://www.hackerrank.com/challenges/ncr/problem) trên Hackerrank

**Tóm tắt:** Tính $C_n^k \bmod 142857$ với $0 \le k \le n \le 10^{9}$

**Lời giải:**
- Giả sử bằng những cách trên, bạn đã tính được $C_n^k$ modulo là số nguyên tố ([ĐL Lucas](#Định-lý-Lucas)) hoặc lũy thừa của chúng ([ĐL Lucas mở rộng](#Định-lý-Lucas-mở-rộng)). Tiếp theo ta sẽ sử dụng CRT xử lý các phần còn lại.
- Đầu tiên, ta sẽ phân tích modulo $142857 = 3^3 \cdot 11 \cdot 13 \cdot 17$
    ```cpp
    int n_primes = 4;
    int primes[] = {3, 11, 13, 37};
    int primes_pw[] = {27, 11, 13, 37};
    int rem[n_primes];
    vector<long long> fact[n_primes], ifact[n_primes];
    ```

- Ta chuẩn bị sẵn một mảng tính $M_i N_i$ trong công thức $a = \sum a_i M_i N_i$ để tiện cho việc truy vấn.
    ```cpp
    void prepare(){
        for (int i = 0; i < n_primes; i++) {
            // M_i
            int tmp = MOD / primes_pw[i];
            //giá trị phi Euler của primes_pw[i]
            int phi = primes_pw[i] / primes[i] * (primes[i] - 1);
            // M_i * M_i^(-1)
            rem[i] = tmp * binpow(tmp, phi - 1, primes_pw[i]) % MOD;
        }
    }
    ```
- Cuối cùng tính ra kết quả cuối cùng sử dụng CRT
    ```cpp
    long long CRT(long long N, long long K) {
        long long res = 0;
        for (int i = 0; i < n_primes; i++) {
            // C(n, k, MOD) là hàm tính nCk modulo MOD
            int ans = C(N, K, MOD) * rem[i] % MOD;
            res = (res + ans) % MOD;
        }
        return res;
    }
    ```

<details>
<summary> Bạn đọc tham khảo code nộp AC bài nCr ở đây </summary>
```cpp
#include <bits/stdc++.h>
const int MOD = 142857;

using ll = long long;

using namespace std;

int primes[] = {3, 11, 13, 37};
int primes_pw[] = {27, 11, 13, 37};
int phi[] = {18, 10, 12, 36}; // phi = prime_pw * (prime - 1)/prime
int rem[4];
vector<ll> fact[4], ifact[4];
int t;

ll binpow(ll a, ll n, ll mod)
{
    ll res = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

void init(int x)
{
    fact[x].assign(primes_pw[x], 0);
    ifact[x].assign(primes_pw[x], 0);
    fact[x][0] = 1;
    for (int i = 1; i < primes_pw[x]; i++)
    {
        if (i % primes[x] != 0)
            fact[x][i] = (fact[x][i - 1] * i) % primes_pw[x];
        else
            fact[x][i] = fact[x][i - 1];
    }
    ifact[x][primes_pw[x] - 1] = binpow(fact[x][primes_pw[x] - 1],
                                        primes_pw[x] / primes[x] * (primes[x] - 1) - 1,
                                        primes_pw[x]);
    for (int i = primes_pw[x] - 1; i > 0; i--)
    {
        if (i % primes[x] != 0)
            ifact[x][i - 1] = (ifact[x][i] * i) % primes_pw[x];
        else
            ifact[x][i - 1] = ifact[x][i];
    }
}

/*i is the order of prime*/
ll C(ll N, ll K, ll R, int i)
{
    return (fact[i][N] * ifact[i][R] % primes_pw[i]) * ifact[i][K] % primes_pw[i];
}

int count_carry(ll n, ll k, ll r, ll p, ll t)
{
    ll res = 0;
    while (n >= t)
    {
        res += (n / t - k / t - r / t);
        t *= p;
    }
    return res;
}

ll calc(ll N, ll K, ll R, int ord_pr)
{
    if (K > N)
        return 0;
    int prime = primes[ord_pr];
    int mod = primes_pw[ord_pr];
    ll res = 1;
    int vp = count_carry(N, K, R, prime, prime);
    int vp2 = count_carry(N, K, R, prime, mod);
    while (N > 0)
    {
        res = (res * C(N % mod, K % mod, R % mod, ord_pr)) % mod;
        N /= prime;
        K /= prime;
        R /= prime;
    }
    res = res * binpow(prime, vp, mod) % mod;
    if ((vp2 & 1) && (prime != 2 || mod <= 4))
        res = (mod - res) % mod;

    return res;
}

ll CRT(ll N, ll K)
{
    ll res = 0;
    for (int i = 0; i <= 3; i++)
    {
        int ans = calc(N, K, N - K, i) * rem[i] % MOD;
        res = (res + ans) % MOD;
    }
    return res;
}

void solve()
{
    for (int i = 0; i <= 3; i++)
    {
        init(i);
        int tmp = MOD / primes_pw[i];
        rem[i] = tmp * binpow(tmp, phi[i] - 1, primes_pw[i]) % MOD;
    }
    while (t--)
    {
        ll N, K;
        cin >> N >> K;
        cout << CRT(N, K) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> t;
    solve();
}
```
</details>

## Bài tập luyện tập
* [SPOJ - Marbles](https://www.spoj.com/problems/MARBLES/)
* [Codeforces 181C Div.2](https://codeforces.com/contest/300/problem/C)
* [Codechef - Long Sandwich](https://www.codechef.com/MAY17/problems/SANDWICH)
* [Hackerearth - Binomial Coefficient](https://www.hackerearth.com/problem/algorithm/binomial-coefficient-1/)
* [SPOJ - ADATEAMS](https://www.spoj.com/problems/ADATEAMS/)
* [SPOJ - UCV2013E](https://www.spoj.com/problems/UCV2013E/)
* [Codeforces 239C Div. 1](https://codeforces.com/problemset/problem/407/C)
<br/>
* [VNOJ - Xông nhà ngày Tết](https://oj.vnoi.info/problem/c11TCT)
* [LQDOJ - Tổ hợp nCk](https://lqdoj.edu.vn/problem/ckn2)
* [Hackerrank - nCr](https://www.hackerrank.com/challenges/ncr/problem)
* [Hackerearth - Army parade](https://www.hackerearth.com/fr/problem/algorithm/army-parade-7bcfea8e/)
* [Library Checker - Binomial Coefficient](https://judge.yosupo.jp/problem/binomial_coefficient)
* [Libary Checker - Binomial Coefficient (Prime Mod)](https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod)


## Tài liệu tham khảo
* [Codeforces - Binomial Coefficients with Large Mod](https://codeforces.com/blog/entry/111246)
* [Codeforces - nCk for small k](https://codeforces.com/blog/entry/67890)
* [Mở rộng định lý Lucas của Andrew Granville](https://math.stackexchange.com/questions/95491/n-choose-k-bmod-m-using-chinese-remainder-theorem)
* [CP-Algorithms - Binomial Coefficients](https://cp-algorithms.com/combinatorics/binomial-coefficients.html#binomial-coefficient-modulo-large-prime)
