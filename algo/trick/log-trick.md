---
title: Log trick
description: 
published: true
date: 2025-12-15T16:17:54.114Z
tags: 
editor: markdown
dateCreated: 2025-12-15T16:17:54.114Z
---

# Kĩ thuật xử lý số mũ

Trong lập trình thi đấu, khi giải các bài thuộc chủ đề Toán, Tổ hợp và Lý thuyết số, ta thường sẽ phải xử lý các biểu thức có chứa số mũ, thậm chí là số mũ thực. Bài viết này sẽ đề cập một số bài toán mẫu mực, cùng các kĩ thuật giúp các bạn có thể xử lý thuận tay và chinh phục được các bài toán như vậy.

## Kĩ thuật số học cơ bản

### Lý thuyết

Trước khi vào bài, các bạn cần nắm được các kiến thức trong các bài viết sau của VNOI Wiki:

1. [Phi hàm Euler](https://wiki.vnoi.info/algo/algebra/phi-ham-euler)
2. [Định lý số dư Trung Hoa (CRT)](https://wiki.vnoi.info/algo/math/crt)

> [!Important] Định lý Euler và các tính chất
> Định lý Euler cho chúng ta biết rằng với $\gcd(a, n) = 1$, $a^x \bmod n$ tuần hoàn với chu kì là $\phi(n)$. Đây là công cụ đắc lực để giản lược số mũ trong tháp luỹ thừa.
> 1. Hàm hợp phi $\phi^k(n) = \phi(\phi(\dots \phi(n) \dots))$ sẽ hội tụ về $1$ sau khoảng $\mathcal{O}(\log n)$ bước.
> 2. Từ tính chất 1, bất cứ một tháp luỹ thừa ($a^{b^{c^{\dots}}}$) nào cũng đều sẽ hội tụ theo modulo $m$ sau $\mathcal{O}(\log m)$ tầng.
> 
> > [!info]- Chứng minh tính chất 1
> > Ta sẽ xem xét tốc độ giảm giá trị của $n$ qua mỗi lần áp dụng hàm $\phi$.
> > 1. **Trường hợp 1: $n$ chẵn ($n > 2$):**
> > Theo công thức tính hàm phi Euler: $\phi(n) = n \prod_{p|n} (1 - \frac{1}{p})$.Vì $n$ chẵn nên $n$ có ước nguyên tố là 2. Trong tích trên sẽ chứa thừa số $(1 - \frac{1}{2}) = \frac{1}{2}$. Các thừa số còn lại $(1 - \frac{1}{p})$ đều nhỏ hơn hoặc bằng 1. Do đó:$$\phi(n) \le n \cdot \frac{1}{2} = \frac{n}{2}$$
> > 2. **Trường hợp 2: Nếu $n$ là số lẻ ($n > 1$)**
> > Nếu $n$ là số lẻ, thì mọi ước nguyên tố $p$ của $n$ đều là số lẻ. Khi đó ta có: $\phi(n) = \prod p_i^{k_i-1}(p_i - 1)$.
> > Vì $p_i$ là lẻ nên $(p_i - 1)$ là số chẵn. $\Rightarrow$ $\phi(n)$ với $n$ lẻ luôn là số chẵn với mọi $n > 2$.
> > 
> > Kết hợp 2 trường hợp:
> > 1. Nếu $n$ chẵn: $\phi(n) \le n/2$.
> > 2. Nếu $n$ lẻ: $\phi(\phi(n)) \le \phi(n)/2 < n/2$.
> > 
> > Như vậy, tối đa sau 2 lần áp dụng hàm $\phi$, giá trị của $n$ sẽ giảm đi ít nhất một nửa. Gọi $T(n)$ là số bước để $n$ giảm về 1. Ta có bất đẳng thức truy hồi:$$T(n) \le T(n/2) + 2$$
> > 
> > Áp dụng Định lý tổng quát (Master theorem), ta tính được $T(n) \approx 2 \log_2 n$. Nên số bước để dãy hội tụ về 1 là $O(\log n)$.
>
> > [!info]- Chứng minh tính chất 2
> > Chứng minh khá hiển nhiên sau khi đã có tính chất 1, xin được để lại cho bạn đọc như một bài tập.

### Vận dụng

#### [ICPC Quốc gia Đài Loan 2024 - F: Fibonacci Lucky Numbers](https://codeforces.com/gym/105383/problem/F)

Cho số $n$. Tìm 10 chữ số cuối của số Fibonacci thứ $7^{7^{7^n}}$. Giải $T$ test.

Giới hạn: $T \le 20, n \le 10^9$.

> [!tip]- Gợi ý
> Dãy Fibonacci tuần hoàn theo modulo $m$ theo [chu kì Pisano](https://en.wikipedia.org/wiki/Pisano_period) $\pi(m)$.

> [!example]- Lời giải
> Ta cần tính đáp án theo modulo $m = 10^{10}$. Trước tiên, ta tính chu kì Pisano của $m$ và có $\pi(m) = 1.5 \times 10^9$. Bài toán khi đó chuyển về tính $7^{7^{7^n}} \bmod \pi(m)$. Ta có thể áp dụng được định lý Euler do $\gcd(7, \phi(\pi(m))) = \gcd(7, \phi^2(\pi(m)) = \gcd(7, \phi^3(\pi(m))) = 1$ để tính được tháp luỹ thừa này, sau đó nhân ma trận để tính ra đáp án.
> 
> Lưu ý đáp án in ra phải có đủ 10 chữ số, nếu thiếu phải thêm số 0 ở đầu.

> [!note]- Bonus
> Mọi dãy truy hồi tuyến tính đều có chu kì theo modulo $m$ (bạn đọc tự chứng minh như một bài tập, gợi ý là sử dụng nguyên lý Dirichlet). 
> 
> Chu kì đó thuộc 1 trong 2 loại:
> 
> 1. **Tuần hoàn thuần túy**: Lặp lại ngay từ đầu (chẳng hạn Fibonacci theo modulo 3: $0, 1, 1, 2, ..., 0, 1, ...$).
> 2. **Tuần hoàn đuôi**: Có một đoạn đầu bất thường rồi sau đó mới đi vào vòng lặp.

> [!note]- Bonus 2
> Dãy Fibonacci có tính chất đặc biệt là **chạy lùi**, tức là ta có thể biểu diễn số hạng một cách duy nhất theo các số hạng sau nó.
> 
> 1. Công thức xuôi: $F_n = F_{n-1} + F_{n-2}$.
> 2. Công thức ngược: $F_{n-2} = F_n - F_{n-1}$.
> 
> Các phần tử của dãy có thể được xác định duy nhất theo cả 2 chiều, nên nếu có hai vị trí $i, j$ trong dãy truy hồi modulo $m$ là $F_i = F_j$, ta suy ngược lại thì $F_{i-1} = F_{j-1}$, cứ thế cho đến khi về $F_0$. Do đó, chu kì bắt đầu ngay từ $F_0$.
> 
> **Điều kiện tổng quát:** Cho dãy truy hồi cấp $k$: $u_n = c_1 u_{n-1} + \dots + c_k u_{n-k} \pmod m$. Dãy sẽ tuần hoàn thuần túy khi và chỉ khi hệ số của số hạng xa nhất ($c_k$) là nguyên tố cùng nhau với $m$ ($\gcd(c_k, m) = 1$). Khi đó $c_k$ có nghịch đảo modulo $m$, cho phép ta biểu diễn $u_{n-k}$ một cách duy nhất theo các số hạng sau nó.

#### [VNOJ - VMYT](https://oj.vnoi.info/problem/vmyt)

Cho các số $a_1, \dots, a_k$. Với $i > k$ ta định nghĩa $a_i = a_{i - 1} \times a_{i - 2} \times \dots \times a_{i - k}$. Tính $a_n \bmod 10^9 + 7$.

Giới hạn: $k \le 50, n \le 10^9$.

#### [DTL Contest 2021 - Bài 6: Số dư](https://oj.vnoi.info/problem/dtl_modeq)

Cho các số nguyên dương $a, m$. Tìm $x \le 10^{18}$ bất kì sao cho $a^x \equiv x \pmod m$. Nếu không tồn tại in ra $-1$.

> [!example]- Lời giải
> Giá trị hội tụ của tháp lũy thừa $H = a^{a^{a^{\dots}}}$ chính là một nghiệm "lý tưởng" của phương trình. Số $x$ cần tìm sẽ có cùng tính chất với $H$ trong modulo $m$.
> 
> Theo định lý Euler, ta có:
> 
> $$a^H \equiv a^{H \bmod{\phi(m)}} \equiv H \pmod m$$
> 
> Thay $H$ trong phương trình trên bởi $x$, ta có hệ phương trình đồng dư:
> 
> $$\begin{cases} x \equiv H \pmod m \\ x \equiv H \pmod {\phi(m)} \end{cases}$$
> 
> Ta có thể giải hệ trên bằng định lý số dư Trung Hoa tổng quát.

> [!example]- Cài đặt
> ```cpp
> #include <bits/stdc++.h>
> 
> using namespace std;
> 
> typedef long long ll;
> 
> // Hàm lũy thừa: a^b % m
> ll power(ll a, ll b, ll m) {
>     ll res = 1;
>     a %= m;
>     while (b > 0) {
>         if (b & 1) res = (__int128)res * a % m;
>         a = (__int128)a * a % m;
>         b >>= 1;
>     }
>     return res;
> }
> 
> // Hàm tính Phi Euler: O(sqrt(n))
> ll get_phi(ll n) {
>     ll res = n;
>     for (ll i = 2; i * i <= n; ++i) {
>         if (n % i == 0) {
>             while (n % i == 0) n /= i;
>             res -= res / i;
>         }
>     }
>     if (n > 1) res -= res / n;
>     return res;
> }
> 
> // Code CRT tổng quát (cre: chemthan)
> template <typename T>
> struct CRT {
>     T res;
>     T prd;
> 
>     CRT() { res = 0, prd = 1; }
> 
>     T mul(T a, T b, T p) {
>         return (__int128)a * b % p;
>     }
> 
>     // Thuật toán Euclid mở rộng: trả về {x, y} sao cho ax + by = gcd(a, b)
>     pair<T, T> euclid(T a, T b) {
>         if (!b) return make_pair(1, 0);
>         pair<T, T> r = euclid(b, a % b);
>         return make_pair(r.second, r.first - a / b * r.second);
>     }
> 
>     // Thêm phương trình: x = r (mod p)
>     bool add(T p, T r) {
>         
>         T g = gcd(prd, p);
>         if ((r - res) % g != 0) return false; 
>         
>         T p_reduced = prd / g;
>         T m_reduced = p / g;
>         T rhs = (r - res) % p;
>         if (rhs < 0) rhs += p;
>         rhs /= g;
> 
>         pair<T, T> eg = euclid(p_reduced, m_reduced);
>         T inv = eg.first % m_reduced;
>         if (inv < 0) inv += m_reduced;
> 
>         T k = mul(rhs, inv, m_reduced);
> 
>         // Cập nhật nghiệm tổng quát
>         // x_new = res + k * prd
>         // LCM mới = prd * (p / g)
>         res += k * prd;
>         prd *= m_reduced;
>         res %= prd;
>         
>         return true;
>     }
> };
> 
> // Tính giá trị tháp lũy thừa vô hạn modulo m
> // H mod m = a^(H mod phi(m) + phi(m)) mod m
> ll tower(ll a, ll m) {
>     if (m == 1) return 0;
>     ll ph = get_phi(m);
>     ll ex = tower(a, ph);
>     return power(a, ex + ph, m);
> }
> 
> void solve() {
>     ll a, m;
>     cin >> a >> m;
> 
>     if (m == 1) {
>         cout << 1 << endl;
>         return;
>     }
>     ll p = get_phi(m);
>     ll val_p = tower(a, p); // H mod phi(m)
>     
>     // val_m = a^(val_p + p) mod m
>     // Đây là giá trị H mod m
>     ll val_m = power(a, val_p + p, m);
> 
>     // 2. Sử dụng CRT để giải hệ phương trình
>     // x = val_m (mod m)
>     // x = val_p (mod p)
>     
>     CRT<ll> crt;
>     // Phương trình 1: x = val_m (mod m)
>     crt.add(m, val_m); 
>     
>     // Phương trình 2: x = val_p (mod p)
>     if (!crt.add(p, val_p)) {
>         cout << -1 << endl;
>         return;
>     }
>     ll x = crt.res;
>     if (x == 0) x += crt.prd;
>     cout << x << endl;
> }
> 
> int main() {
>     ios_base::sync_with_stdio(false);
>     cin.tie(NULL);
>     solve();
>     return 0;
> }
> ```

## Giá trị kì vọng

## Kết hợp cấu trúc dữ liệu

### [ICPC NWERC Regional 2023 - E: Exponentiation](https://codeforces.com/gym/105112/problem/E)

Cho $n$ biến $x_1 = x_2 = \dots = x_n = 2023$. Có $m$ truy vấn, mỗi truy vấn thuộc 1 trong 2 loại sau với $i \ne j$:

1. `! i j`: Gán $x_i$ thành $x_i^{x_j}$.
2. `? i j`: So sánh $x_i$ và $x_j$ và in ra dấu của phép so sánh.

In ra đáp án cho tất cả các truy vấn loại 2.

### [ICPC 2022 vòng Quốc gia - E: Estate Construction](https://oj.vnoi.info/problem/icpc22_national_e)

Cho $n$ hình chữ nhật trên mặt phẳng 2 chiều, các góc ở các toạ độ nguyên dương và song song với 2 trục toạ độ. Mỗi toạ độ $(i, j)$ có trọng số là $(i \times j)^k$. Tính tổng trọng số của tất cả các toạ độ được phủ bởi ít nhất một hình chữ nhật theo modulo $10^9 + 7$.

## Căn nguyên thuỷ và logarit rời rạc

### [2020-2021 Winter Petrozavodsk - M. Discrete Logarithm is a Joke](https://codeforces.com/problemset/gymProblem/103260/M)

Cho $M = 10^{18} + 31$ là số nguyên tố và $g = 42$ là căn nguyên thuỷ trong trường modulo $M$. Gọi $f(x)$ là hàm trả về $p$ nhỏ nhất mà $g^p \equiv x \pmod M$. Ta cũng định nghĩa thêm dãy $a$ sau:

1. $a_0 = 960002411612632915$
2. $a_{i + 1} = f(a_i)$.

Cho $n$, tính $a_n$.

## Số mũ thực

### [ICPC Asia Bangkok Regional 2025 - J: Joyeuse](https://codeforces.com/gym/106164/problem/J)

Cho các số nguyên dương $a_1, \dots, a_n$. Tính tổng $\sqrt{a_i + a_j}$ với mọi $1 \le i < j \le n$. In ra đáp án với sai số tuyệt đối hoặc tương đối không quá $10^{-6}$.

## Hàm sinh

### [Tuyển sinh 10 LQDDN 2023 - Cây tre trăm đốt](https://lqdoj.edu.vn/problem/23ts10dna4)

Cho mảng $a$ gồm $n$ phần tử nguyên dương và số nguyên dương $k$. Đếm số **dãy con (không nhất thiết liên tiếp)** của $a$ có tổng bằng $k$.

Giới hạn: $1 \le n, k, a_i \le 10^5$.

### [ICPC HCMC Regional 2022 - H: Hardest Problem](https://oj.vnoi.info/problem/icpc22_regional_h)

Cho 2 số $n, d$. Định nghĩa $f(k)$ là số hoán vị độ dài $n$ thoả mãn:

1. Số nghịch thế của hoán vị là $k$.
2. Các số từ $1$ đến $d$ trong hoán vị tạo thành 1 dãy con theo đúng thứ tự từ nhỏ đến lớn.

Tính $f(k)$ với mỗi $k$ chạy từ $1$ đến $\min \left(250 000, \frac{n(n - 1)}{2} \right)$.

Giới hạn: $2 \le n \le 10^6, 1 \le d \le n$.

## Vận dụng

1. [CSES - Exponentiation II](https://cses.fi/problemset/task/1712)
2. [CF1106F - Lunar New Year and a Recursive Sequence](https://codeforces.com/problemset/problem/1106/F)
3. [CF906D - Power Tower](https://codeforces.com/problemset/problem/906/D)
4. [DTL Contest 2021 - Bài 7: Mũ hoá cực mạnh](https://oj.vnoi.info/problem/dtl_suppower)
5. [ICPC 2025 vòng Quốc gia - E: Extended Fermat Theorem
](https://oj.vnoi.info/problem/icpc25_national_e)
6. [ABC335G - Discrete Logarithm Problems](https://atcoder.jp/contests/abc335/tasks/abc335_g)
7. [AGC047C - Product Modulo](https://atcoder.jp/contests/agc047/tasks/agc047_c)
8. [CodeChef - SERSUM](https://www.codechef.com/problems/SERSUM)
9. [VNOJ - kinvper](https://oj.vnoi.info/problem/dp_advanced_p2_j)
10. [CF1310F - Bad Cryptography](https://codeforces.com/contest/1310/problem/F)
11. [CF623E - Transforming Sequence](https://codeforces.com/problemset/problem/623/E)
12. [CF1278F - Cards](https://codeforces.com/problemset/problem/1278/F)
13. [ICPC 2018 Xuzhou Regional - D. Rikka with Subsequences](https://codeforces.com/gym/102012/problem/D)
14. [CF1187F - Expected Square Beauty](https://codeforces.com/problemset/problem/1187/F)
15. [ARC180F - Yet Another Expected Value](https://atcoder.jp/contests/arc180/tasks/arc180_f)