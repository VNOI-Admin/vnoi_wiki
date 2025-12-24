---
title: Quy hoạch động chia để trị (Divide and Conquer DP)
description: 
published: true
date: 2024-09-05T11:42:31.219Z
tags: 
editor: markdown
dateCreated: 2024-03-30T11:03:39.269Z
---

# Quy hoạch động chia để trị (Divide and Conquer DP)
**Tác giả:**
- Lê Minh Hoàng - Đại học Khoa học Tự nhiên, ĐHQG-HCM

**Reviewer:**
- Ngô Nhật Quang - THPT chuyên Khoa học Tự Nhiên, ĐHQGHN
- Nguyễn Minh Nhật - THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Nguyễn Minh Hiển - Đại học Công nghệ, ĐHQGHN 
- Phạm Hoàng Hiệp - University of Georgia 


## Giới thiệu
Bài viết *"Tối ưu quy hoạch động 1 chiều"* của tác giả *Nguyễn Tuấn Tài* trong [*Tạp chí VNOI Xuân Quý Mão (trang 16)*](https://oj.vnoi.info/post/428-vnoi-magazine-2023) đã đề cập đến một phương pháp tối ưu quy hoạch động rất đặc biệt, đó là *phương pháp tối ưu quy hoạch động 1 chiều*.

Trong bài viết này, ta sẽ tìm hiểu về một phương pháp tối ưu quy hoạch động khác, dùng cho các bài toán mà công thức truy hồi có dạng:
$$
dp(i,j) = \min\limits_{k\le j}\left[dp(i-1,k)+C(k,j)\right]
$$

Công thức trên có độ phức tạp $\mathcal{O}(mn^2)$. Ta có thể tối ưu độ phức tạp xuống còn $\mathcal{O}(mn\log{n})$ bằng phương pháp *quy hoạch động chia để trị* nếu hàm chi phí $C(k, j)$ thoả mãn **điều kiện áp dụng** (được đề cập ở phần tiếp theo).

<!-- Ngoài ra, ta còn có thể tối ưu độ phức tạp của công thức trên xuống còn $\mathcal{O}(mn)$ bằng phương pháp *quy hoạch động bao lồi* nếu hàm chi phí thoả một số điều kiện nhất định (không phải "điều kiện áp dụng" trong bài viết này). Phương pháp này sẽ được đề cập trong một bài viết khác.
 -->

<!-- time update: 11am 16/01/2024 -->
Ngoài ra, ta còn có thể tối ưu độ phức tạp của công thức trên xuống còn $\mathcal{O}(mn)$ bằng [**Kĩ thuật bao lồi (Convex Hull Trick)**](https://vnoi.info/wiki/translate/wcipeg/Convex-Hull-Trick.md) nếu hàm chi phí thoả các điều kiện của kĩ thuật.

## Điều kiện áp dụng
Đầu tiên, ta định nghĩa lại bất đẳng thức tứ giác (quadrangle inequality) và điều kiện đơn điệu (monotonicity condition) như sau:
- Bất đẳng thức tứ giác: $\forall a<b\le c<d$
    - Bất đẳng thức tứ giác xuôi: $f(a,c)+f(b,d)\le f(a,d)+f(b,c)$
    - Bất đẳng thức tứ giác ngược: $f(a,c)+f(b,d)\ge f(a,d)+f(b,c)$
- Điều kiện đơn điệu: $\forall i$
    - Đơn điệu tăng: $f(i)\le f(i+1)$
    - Đơn điệu giảm: $f(i)\ge f(i+1)$

Tiếp theo, ta định nghĩa mảng $opt$ như sau:
$$
opt(i,j) = \mathop{\arg\min}\limits_{k\le j}\left[dp(i-1,k) + C(k, j)\right]
$$

Nói cách khác, $opt(i,j)$ là giá trị $k$ nhỏ nhất sao cho $dp(i-1,k) + C(k, j)$ đạt giá trị cực tiểu.

Cuối cùng, để có thể áp dụng *quy hoạch động chia để trị* cho công thức đã được đề cập ở trên, mảng $opt(i)$ cần phải thoả mãn **điều kiện đơn điệu** (tuỳ bài toán mà ta cần **đơn điệu tăng** hay **đơn điệu giảm**, nhưng vì không mất tính tổng quát nên ta sẽ giả sử là **đơn điệu tăng**):
$$
opt(i,j)\le opt(i,j+1)
$$

Nhưng đôi khi, việc chứng minh điều kiện đơn điệu cho một công thức truy hồi sẽ không hề dễ dàng. Trong một số bài toán, ta có thể chứng minh điều kiện đơn điệu thông qua **bất đẳng thức tứ giác tương ứng** (vì ta đang giả sử **điều kiện đơn điệu** là **đơn điệu tăng** nên **bất đẳng thức tứ giác tương ứng** là **bất đẳng thức tứ giác xuôi**) trên hàm chi phí $C$:
$$
C(a,c)+C(b,d)\le C(a,d)+C(b,c), \text{ với } a<b\le c<d
$$

Ta có thể chứng minh rằng, nếu hàm chi phí thoả mãn **bất đẳng thức tứ giác**, thì $opt(i)$ sẽ thoả mãn **điều kiện đơn điệu tương ứng** (phần chứng minh này sẽ được đặt ở cuối bài viết), tức là:
- Bất đẳng thức tứ giác xuôi $\implies$ Đơn điệu tăng
- Bất đẳng thức tứ giác ngược $\implies$ Đơn điệu giảm

Lưu ý rằng, ta không thể có được **bất đẳng thức tứ giác** từ **điều kiện đơn điệu tương ứng**, tức là mối quan hệ chỉ xảy ra một chiều.

## Thuật toán
### Ý tưởng
Ý tưởng chính của kỹ thuật này là dựa trên điều kiện $opt(i,j)\le opt(i,j+1)$.
Giả sử, ta vừa tính được $opt(i,j)$ trong $\mathcal{O}(n)$ bằng cách xét tất cả vị trí $k$ trong đoạn $\left[1,n\right]$.
Xét $j'<j$, ta biết rằng $opt(i,j')\le opt(i,j)$. Do đó, ta có thể tính $opt(i,j')$ trong $\mathcal{O}(opt(i,j))$, thay vì $\mathcal{O}(n)$, bằng cách xét tất cả vị trí $k$ trong đoạn $\left[1,opt(i,j)\right]$.

### Thuật toán chia để trị
Dựa trên ý tưởng đó, ta có thuật toán chia để trị như sau:
- Đầu tiên, ta tính $opt(i,n/2)$ trong $\mathcal{O}(n)$.
- Tiếp theo, ta tính $opt(i,n/4)$ (biết rằng $opt(i,n/4)\le opt(i,n/2)$) và $opt(i,3n/4)$ (biết rằng $opt(i,3n/4)\ge opt(i,n/2)$), tổng độ phức tạp của "tầng" này là $\mathcal{O}(n)$.
- Tiếp tục đệ quy để tính $opt(i,n/8), opt(i,3n/8),opt(i,5n/8),opt(i,7n/8)$, trong quá trình đệ quy, ta duy trì cận trên và dưới của $opt$.

### Độ phức tạp

:::spoiler Phiên bản cũ

---
Giả sử độ phức tạp để tính chi phí $C(k,j)$ là $\mathcal{O}(1)$.
Vì sau khi xét một đoạn vị trí $k$ để tính $opt(i,mid)$, ta chia đoạn đó thành $2$ đoạn không giao nhau (đoạn bên trái có biên phải là $opt(i, mid)$, đoạn bên phải có biên trái là $opt(i, mid)$) và tiếp tục đệ quy trên $2$ đoạn đó, nên tổng độ dài các đoạn thuộc mỗi "tầng" là $n$ và số "tầng" đệ quy tối đa là $\log n$. Do đó:
- Tổng độ phức tạp để tính $opt(i)$ là $\mathcal{O}(n\log n)$.
- Tổng độ phức tạp của thuật toán sau $m$ lần tính $dp$ là $\mathcal{O}(mn\log n)$.
---
:::

Xét $j\in[l,r]$, giả sử ta cần tính tất cả $opt(i,j)$, biết rằng $optl\le opt(i,j)\le optr$.
Đặt $mid=\left\lfloor\frac{l+r}2\right\rfloor$. Nếu độ phức tạp để tính chi phí $C(k,j)$ là $\mathcal{O}(1)$ thì ta có thể tính $opt(i,mid)$ trong $\mathcal{O}(optr-optl)$.

Tiếp theo, ta gọi đệ quy để tính $opt(i,j)$ của $2$ đoạn:
- $j\in[l,mid-1]$ với $optl\le opt(i,j)\le opt(i,mid)$
- $j\in[mid+1,r]$ với $opt(i,mid)\le opt(i,j)\le optr$

Nếu bỏ qua $opt(i,mid)$ thì rõ ràng là $[optl,opt(i,mid)]$ và $[opt(i,mid),optr]$ không giao nhau, nên tổng chi phí để tính tất cả $opt(i,mid)$ thuộc mỗi "tầng" là $\mathcal{O}(n)$. Và vì ta luôn chia đôi đoạn cần tính $[l,r]$ ở mỗi lần đệ quy nên số "tầng" đệ quy là $\log n$. Do đó:
- Tổng độ phức tạp để tính $opt(i)$ là $\mathcal{O}(n\log n)$.
- Tổng độ phức tạp của thuật toán sau $m$ lần tính $dp$ là $\mathcal{O}(mn\log n)$.

Dưới đây là hình minh hoạ về tổng độ phức tạp để tính $opt(i)$:
![image](https://hackmd.io/_uploads/B1-6YBwIp.png)
<!--
![](https://vnoi.info/wiki/uploads/dp_optimization_img2.png)
 -->
## Cài đặt
Mặc dù việc triển khai có thể khác nhau tùy theo từng bài toán nhưng chúng đều có một cấu trúc chung.
Với mỗi lần tính $dp$, hàm `solve()` gọi `compute(0, n, 0, n)`.
Mỗi khi được gọi, hàm `compute` tính $opt(i)$  và $dp(i)$ (`dp_cur`) dựa vào $dp(i-1)$ (`dp_before`) và hàm chi phí `C`.

```cpp=1
int m, n;
vector<int> dp_before(n + 1), dp_cur(n + 1);

// hàm chi phí
int C(int l, int r);

// tính dp_cur[l], ..., dp_cur[r]
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid             = (l + r) >> 1;
    pair<int, int> best = { INT_MAX, -1 };

    // tính dp_cur[mid] và opt[i][mid] dựa vào dp_before và hàm chi phí
    for (int k = optl; k <= min(mid, optr); ++k) {
        best = min(best, { dp_before[k] + C(k, mid), k });
    }
    dp_cur[mid] = best.first;
    int opt     = best.second;

    // đệ quy để tính dp_cur[l..mid-1] và dp_cur[mid+1..r]
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int solve() {
    for (int i = 0; i <= n; ++i)
        dp_before[i] = C(0, i);

    for (int i = 1; i < m; ++i) {
        compute(0, n, 0, n);
        dp_before = dp_cur;
    }

    return dp_before[n];
}
```

## Ứng dụng
### [**Codeforces - 1601C (Optimal Insertion)**](https://codeforces.com/contest/1601/problem/C) 

Cho $2$ mảng $a_1,a_2,\ldots,a_n$ và $b_1,b_2,\ldots,b_m$.
Ta cần chèn các phần tử của mảng $b$ vào mảng $a$ một cách tuỳ ý (ở đầu, ở giữa, hoặc ở cuối). Kết quả là ta sẽ nhận được mảng $c_1,c_2,\ldots,c_{n+m}$ có kích thước $n+m$.

Nói cách khác, thứ tự của các phần tử của mảng $a$ trong mảng $c$ phải được giữ nguyên. Ngược lại, các phần tử của mảng $b$ có thể xuất hiện trong mảng $c$ theo bất kỳ thứ tự nào.

Hỏi số cặp nghịch thế ít nhất có thể của mảng $c$ là bao nhiêu? Biết rằng một cặp $(i,j)$ được gọi là nghịch thế nếu $i<j$ và $c_i>c_j$.

Giới hạn:
- $1\le n,m\le10^6$
- $1\le a_i, b_i\le 10^9$

#### Ý tưởng
Đầu tiên, ta sắp xếp mảng $b$ tăng dần (để $b_i\le b_{i+1}$).

Với mỗi $i$, gọi $p_i$ là vị trí nhỏ nhất sao cho khi ta chèn $b_i$ vào trước $a_{p_i}$ thì số cặp nghịch thế tăng lên là ít nhất. Nếu chèn $b_i$ ở cuối mảng $a$ thì $p_i=n+1$.

Ta có nhận xét: Nếu tồn tại $i<j$ và $p_i>p_j$ thì ta có thể đổi chỗ $b_i$ và $b_j$ để giảm số cặp nghịch thế (bạn đọc có thể tự chứng minh). Do đó, ta có $p_1\le p_2\le\ldots p_m$.

Từ đây, ta có thể áp dụng *quy hoạch động chia để trị* để tìm giá trị của mảng $p$, sau đó dựng mảng $c$ và tính số cặp nghịch thế.

Bài toán bây giờ là làm thế nào để tính nhanh giá trị $p_{mid}$ khi có $optl$ và $optr$.
Dễ chứng minh, số cặp nghịch thế tăng thêm được xác định bởi biểu thức sau:
$$
\underbrace{\left|a_i\gt b_{mid}\right|}_{\text{ với }i\lt optl}^{(1)} + \underbrace{\left|a_i\gt b_{mid}\right|}_{\text{ với }optl\le i\lt p_{mid}}^{(2)} + \underbrace{\left|b_{mid}\gt a_i\right|}_{\text{ với }p_{mid}\le i\le optr}^{(3)} + \underbrace{\left|b_{mid}\gt a_i\right|}_{\text{ với }optr\lt i}^{(4)}
$$

Nếu biết trước $optl$ và $optr$, rõ ràng $(1)$ và $(4)$ là như nhau với mọi vị trí $p_{mid}\in[optl,optr]$, vậy nên ta có thể bỏ qua. Còn lại $(2)$ và $(3)$, ta dựng $2$ mảng $prf$ và $suf$ để tính nhanh $p_{mid}$ trong $\mathcal{O}(optr-optl)$.

#### Cài đặt
```cpp=1
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;
int n, m;
int a[N], b[N], c[N * 2];

int p[N];
int prf[N], suf[N];

int bit[N * 2];

int calcPos(int optl, int optr, int bi) {
    prf[optl - 1] = suf[optr + 1] = 0;
    for (int i = optl; i <= optr; ++i) prf[i] = prf[i - 1] + (a[i] > bi);
    for (int i = optr; i >= optl; --i) suf[i] = suf[i + 1] + (bi > a[i]);

    int pos = optl;
    for (int i = optl + 1; i <= optr; ++i)
        if (prf[pos - 1] + suf[pos] > prf[i - 1] + suf[i]) pos = i;
    return pos;
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    p[mid]  = calcPos(optl, optr, b[mid]);

    compute(l, mid - 1, optl, p[mid]);
    compute(mid + 1, r, p[mid], optr);
}
void compress_c() {
    vector<int> tmp(c + 1, c + n + 1);
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 1; i <= n; ++i)
        c[i] = lower_bound(tmp.begin(), tmp.end(), c[i]) - tmp.begin() + 1;
}
void upd(int p, int v) {
    for (; p; p ^= p & -p) bit[p] += v;
}
int get(int p) {
    int res = 0;
    for (; p <= n; p += p & -p) res += bit[p];
    return res;
}

long long solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    a[n + 1] = INT_MAX;
    sort(b + 1, b + m + 1);
    compute(1, m, 1, n + 1);

    // dựng mảng c từ mảng a, b và p
    for (int i = 1, j = 1, sz = 0; i <= n + 1; ++i) {
        while (j <= m && p[j] == i) c[++sz] = b[j++];
        if (i <= n) c[++sz] = a[i];
    }
    n += m;
    compress_c();

    fill(bit + 1, bit + n + 1, 0);
    long long res = 0;
    for (int i = 1; i <= n; ++i) {
        res += get(c[i] + 1);
        upd(c[i], 1);
    }
    return res;
}

int main() {
    int test;
    cin >> test;
    while (test--) {
        cout << solve() << '\n';
    }
}
```

Độ phức tạp thời gian: $\mathcal{O}(n\log n)$
Độ phức tạp không gian: $\mathcal{O}(n)$

### [**VNOJ - nkleaves (Leaves)**](https://oj.vnoi.info/problem/nkleaves)

Ta có thể tóm tắt bài toán như sau:
- Cho mảng $w$ độ dài $n$ là trọng lượng của $n$ chiếc lá (đánh số từ $1$ đến $n$) và một số $k$.
- Ta cần chia $n$ chiếc lá thành đúng $k$ đoạn liên tiếp (độ dài đoạn phải khác $0$), mỗi đoạn sẽ gom thành một đống lá ở vị trí trái cùng. Chi phí để di chuyển một chiếc lá bằng tích trọng lượng của chiếc lá và khoảng cách di chuyển. Nói cách khác, chi phí của một đống là $\sum\limits_{i=l}^{r}w_i\times(i-l)$.
- Yêu cầu: tìm chi phí nhỏ nhất để gom $n$ chiếc lá thành đúng $k$ đống lá.

Giới hạn:
- $0<n\le10^5$
- $0<k\le10$, $k<n$
- $w_i\le1000$

#### Ý tưởng
Đầu tiên, gọi $C(l,r)$ là chi phí để gom những chiếc lá liên tiếp trong đoạn $[l,r]$ thành một đống lá ở vị trí trái cùng $l$. Nói cách khác, $C(l,r)=\sum\limits_{i=l}^{r}[w_i\times(i-l)]$.
Để tính nhanh $C(l,r)$, ta viết lại công thức như sau:
$$
\begin{align}
\displaystyle
C(l,r)&=\sum\limits_{i=l}^{r}[w_i\times(i-l)] \\
&=\sum\limits_{i=l}^{r}[w_i\times i- w_i\times l] \\
&=\sum\limits_{i=l}^{r}(w_i\times i)-l\times\sum\limits_{i=l}^{r}w_i
\end{align}
$$
  
Ta tính trước $2$ mảng cộng dồn $prf_1[i]=\sum\limits_{j=1}^{i}w_j$ và $prf_2[i]=\sum\limits_{j=1}^{i}(w_j\times j)$ để có thể tính $C(l,r)$ trong $\mathcal{O}(1)$.

Tiếp theo, đặt $dp(i,j)$ là chi phí tối thiểu để gom $j$ chiếc lá đầu tiên thành $i$ đống lá. Ta có công thức truy hồi với độ phức tạp thời gian $\mathcal{O}(kn^2)$ cho bài toán này là
$$dp(i,j) = \min\limits_{i-1\le k<j}\left[dp(i-1,k)+C(k+1,j)\right],\forall j\ge i$$

Vì hàm chi phí $C$ thoả bất đẳng thức tứ giác xuôi $C(a,c)+C(b,d)\le C(a,d)+C(b,c)$ (bạn đọc có thể tự chứng minh) nên ta có thể áp dụng *quy hoạch động chia để trị*, giảm độ phức tạp thời gian xuống còn $\mathcal{O}(kn\log n)$.

#### Cài đặt
```cpp=1
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n, k;
int w[N], prf1[N];
long long prf2[N];
vector<long long> dp_before, dp_cur;

long long C(int l, int r) {
    return (prf2[r] - prf2[l - 1]) - 1LL * l * (prf1[r] - prf1[l - 1]);
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid                   = (l + r) >> 1;
    pair<long long, int> best = { LONG_LONG_MAX, -1 };

    for (int i = optl; i <= min(mid, optr); ++i) {
        best = min(best, { dp_before[i] + C(i + 1, mid), i });
    }
    dp_cur[mid] = best.first;
    int opt     = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        prf1[i] = prf1[i - 1] + w[i];
        prf2[i] = prf2[i - 1] + w[i] * i;
    }

    dp_before.assign(n + 1, LONG_LONG_MAX / 2);
    dp_before[0] = 0;
    dp_cur.resize(n + 1);
    for (int i = 1; i <= k; ++i) {
        compute(i, n, i - 1, n - 1);
        dp_before.swap(dp_cur);
    }

    cout << dp_before[n];
    return 0;
}
```
Độ phức tạp thời gian: $\mathcal{O}(kn\log n)$
Độ phức tạp không gian: $\mathcal{O}(n)$

## Bài tập áp dụng
- [**Codeforces - 321E (Ciel and Gondolas)**](https://codeforces.com/contest/321/problem/E)
- [**Codeforces - 834D (The Bakery)**](https://codeforces.com/contest/834/problem/D)
- [**Codeforces - 868F (Yet Another Minimization Problem)**](https://codeforces.com/contest/868/problem/F)
- [**Atcoder - ARC067D (Yakiniku Restaurants)**](https://atcoder.jp/contests/arc067/tasks/arc067_d)
- [**Codechef - CHEFAOR (Chef and Bitwise OR Operation)**](https://www.codechef.com/problems/CHEFAOR)
- [**Kattis - Famous Pagoda**](https://open.kattis.com/problems/famouspagoda)
- [**Hackerrank - Guardians of the Lunatics**](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14) <!-- bài tập mẫu 2 vnoi wiki -->
- [**Hackerrank - Mining**](https://www.hackerrank.com/contests/world-codesprint-5/challenges/mining)

## Liên hệ giữa bất đẳng thức tứ giác và điều kiện đơn điệu
Vì không mất tính tổng quát, trong phần này, ta sẽ chứng minh rằng, nếu hàm chi phí $C$ thoả mãn *bất đẳng thức tứ giác xuôi* $C(a,c)+C(b,d)\le C(a,d)+C(b,c)$, thì $opt(i)$ sẽ thoả mãn *đơn điệu tăng* $opt(i,j)\le opt(i,j+1)$.

Ta sẽ chứng minh điều này bằng phép phản chứng: giả sử tồn tại vị trí $j$ thoả $opt(i,j) > opt(i,j+1)$.
Để thuận tiện cho việc chứng minh, ta đặt $p = opt(i,j)$, $q = opt(i,j+1)\Rightarrow p>q$, và $dp_x(i,j)=dp(i-1,x)+C(x,j)$. Ta có:

  $$
\begin{cases}
dp_p(i,j)   &< dp_q(i,j)   &(\text{vì }p = opt(i,j)) \\
dp_p(i,j+1) &> dp_q(i,j+1) &(\text{vì }q = opt(i,j+1))
\end{cases}
$$
  
$$\iff
\begin{cases}
dp(i-1,p)+C(p,j)   &< dp(i-1,q)+C(q,j) &(1) \\
dp(i-1,p)+C(p,j+1) &> dp(i-1,q)+C(q,j+1) &(2)
\end{cases}
$$

Lấy $(1)$ trừ $(2)$, ta được:
$$
\begin{align}
C(p,j)-C(p,j+1) \lt C(q,j)-C(q,j+1) \\
\iff C(p,j)+C(q,j+1) \lt C(q,j)+C(p,j+1)
\end{align}
$$

Áp dụng bất đẳng thức tứ giác cho hàm chi phí $C$ với bộ số $q<p\le j<j+1$, ta có:
$$C(p,j)+C(q,j+1)\ge C(q,j)+C(p,j+1)$$

Điều này là vô lý. Do đó, ta có được điều phải chứng minh.

<!--
# List bài tập
## Solved (đã cho vào "Bài tập áp dụng")
## Not Solved
- https://codeforces.com/contest/673/problem/E
- https://codeforces.com/contest/1527/problem/E
- https://codeforces.com/gym/103536/problem/A
- https://www.spoj.com/problems/LARMY/
- https://www.spoj.com/problems/ADAMOLD/
- http://www.usaco.org/index.php?page=viewproblem2&cpid=616
- https://open.kattis.com/problems/money (cp-algo recommended)
- http://poj.org/problem?id=1741 (from https://codeforces.com/blog/entry/47932)

# Source list problem
## Đã khai thác
- https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
- https://codeforces.com/blog/entry/47932
## Chưa khai thác
- https://usaco.guide/plat/DC-DP?lang=cpp
- https://oj.vnoi.info/tags/?tag_id=dp-dnc

# Reference
## Đã đọc
- https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
- https://vnoi.info/wiki/algo/dp/Mot-so-ky-thuat-toi-uu-hoa-thuat-toan-Quy-Hoach-Dong.md#2-chia-%C4%91%E1%BB%83-tr%E1%BB%8B
- https://codeforces.com/blog/entry/8219
- https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming (sâu hơn 1 tí vì có định nghĩa về convex function)
## Chưa đọc
- https://vnoi.info/wiki/algo/dp/Mot-so-ky-thuat-toi-uu-hoa-thuat-toan-Quy-Hoach-Dong.md#2-chia-%C4%91%E1%BB%83-tr%E1%BB%8B

# CDQ D&C
- https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html
- https://tzaph.blogspot.com/2021/10/tutorial-cdq-dnc.html

# DP 1D1D
- https://codeforces.com/blog/entry/8219#comment-139241
- https://codeforces.com/blog/entry/119855 (có Monge + 1D1D DP)
-->