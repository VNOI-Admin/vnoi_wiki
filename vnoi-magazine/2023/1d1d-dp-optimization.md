# Tối ưu quy hoạch động 1 chiều
**Người viết**: Nguyễn Tuấn Tài - Trường Đại học Khoa học Tự nhiên, Đại học Quốc gia TP.HCM

[[_TOC_]]

> *Giới thiệu: đây là kiến thức xuất hiện trong đề thi TST 2022, và đã lấy đi rất nhiều nước mắt của thí sinh. Nếu bạn muốn thử học một thuật toán mới lạ mà nhiều người chưa biết (ngay cả Trần Xuân Bách!), thì đây chính là bài viết dành cho bạn!*

Khi làm những bài toán quy hoạch động, đôi khi ta sẽ nghĩ ra những thuật toán có độ phức tạp rất lớn, ví dụ:

- $f[i][j] = \min \limits_{0 \le k < j} f[i - 1][k] + w(k, j)$ 
Công thức trên có độ phức tạp $O(n^3)$, có thể cải tiến xuống $O(n^2)$ hoặc $O(n^2 \log{n})$ bằng quy hoạch động bao lồi/chia để trị (trong một số điều kiện nhất định).
- $f[i] = \min \limits_{0 \le j < i} f[j] + w(j, i)$
Công thức trên có độ phức tạp $O(n^2)$, có thể cải tiến xuống $O(n \log{n})$ hoặc $O(n)$ (trong một số điều kiện nhất định).

Ở bài viết này, chúng ta sẽ tìm hiểu về cách tối ưu công thức thứ $2$, hay còn gọi là *phương pháp tối ưu quy hoạch động $1$ chiều*.

# Giới thiệu bài toán

Gọi $w(j, i)$ là một hàm tính cost thỏa mãn bất đẳng thức tứ giác (quadrangle inequality):
$$w(a, c) + w(b, d) \le w(a, d) + w(b, c)$$ với mọi $a < b \le c < d$. Ta sẽ tính toán công thức quy hoạch động sau với độ phức tạp nhanh hơn $O(n^2)$:$$f[i] = \min \limits_{0 \le j < i} f[j] + w(j, i)$$

Một số ví dụ về hàm $w$ thỏa mãn bất đẳng thức tứ giác (bạn đọc có thể tự chứng minh):

- $w(j, i) = i - j$
- $w(j, i) = b[j] \cdot a[i]$ (với $a[j] \le a[i]$ và $b[j] \ge b[i]\ \forall\ j < i$)
- $w(j, i) = (a[i] - a[j])^2$ (với $a[j] \le a[i]\ \forall\ j < i$)

# Thuật toán

> *Nhưng... làm sao để tối ưu công thức quy hoạch động trên? Có cách nào để nhanh chóng tìm được vị trí mà $f[j] + w(j, i)$ đạt giá trị nhỏ nhất không?*

Ta định nghĩa mảng $h$ như sau
$$h[i] = \mathop{\arg\min} \limits_{0 \le j < i} f[j] + w(j, i)$$

Nói cách khác, $h[i]$ là vị trí $j$ nhỏ nhất thỏa mãn $f[j] + w(j, i)$ đạt giá trị cực tiểu.

Để thuận tiện cho việc biểu diễn thuật toán, ta sẽ quy ước

$f[0] = 0$, $f[1] = f[2] = \ldots = f[n] = \infty$.

## Ý tưởng "ngây thơ"

Trước khi đi vào thuật toán chính, chúng ta sẽ xem xét qua thuật toán "ngây thơ" sau:

- Ở thời điểm đầu tiên,
    
  $h[1] = h[2] = \ldots = h[n] = 0$.
- Ở thời điểm thứ $i$:
    - Vì $h[i]$ đã được cập nhật hoàn toàn, ta tính được $f[i] = f[h[i]] + w(h[i], i)$.
    - Sau khi tính được $f[i]$, ta sẽ cập nhật lại $h[i + 1], h[i + 2], \ldots, h[n]$.
    
Chúng ta có thể cài đặt thuật toán trên một cách đơn giản như sau:

```cpp
const int N = 1e5 + 3;
int n, h[N];
long long f[N];

long long w(int j, int i) {
  // một hàm cost bất kì thỏa mãn
  // bất đẳng thức tứ giác
}

void solve() {
  for (int i = 1; i <= n; ++i) {
    // cập nhật f[i]
    f[i] = f[h[i]] + w(h[i], i); 
    
    for (int j = i + 1; j <= n; ++j) {
      // cập nhật lại h[i + 1..n]
      if (
        f[i] + w(i, j) < f[h[j]] + w(h[j], j)
      ) {
        h[j] = i;
      }
    }
  }
}
```

## Ý tưởng chính

> *Dễ thấy thuật toán "ngây thơ" trên có độ phức tạp $O(n^2)$. Làm sao để cải tiến thuật toán? Liệu mảng $h$ có một tính chất đặc biệt nào có thể giúp ta dễ dàng cập nhật được không?*

**Nhận xét $\dagger$.** *Ở mọi thời điểm, mảng $h$ luôn là dãy đơn điệu tăng (tức $h[1] \le h[2] \le \ldots \le h[n])$.* (chứng minh ở phần Phụ lục)

> *Việc mảng $h$ luôn là dãy đơn điệu tăng sẽ có ý nghĩa gì?*

Khi cập nhật đến $f[i]$, nếu tồn tại một vị trí $j$ thỏa mãn $f[h[j]] + w(h[j], j) \le f[i] + w(i, j)$, điều đó đồng nghĩa với việc $h[j]$ sẽ không thay đổi. Không chỉ thế, vì $h[i + 1] \le h[i + 2] \le \ldots \le h[j - 1] \le h[j]$, nên cả đoạn $h[i + 1 \ldots j]$ cũng sẽ không thay đổi.

**Hệ quả.** *Nếu tồn tại vị trí $j$ thỏa mãn $f[h[j]] + w(h[j], j) \le f[i] + w(i, j)$, ta được $f[h[p]] + w(h[p], p) \le f[i] + w(i, p)$ với mọi $i < p \le j$.*

Chính vì thế, để cập nhật mảng $h$, ta sẽ tìm vị trí $z$ nhỏ nhất thỏa mãn $f[h[z]] + w(h[z], z) > f[i] + w(i, z)$, và cập nhật $h[z] = h[z + 1] = \ldots = h[n] = i$. Từ đây, ta có ý tưởng thuật toán sau:

**Thuật toán.**

Ta sẽ biểu diễn mảng $h$ thành $m$ đoạn $(l[i], r[i], p[i])$ thỏa mãn:
$$\left\{\begin{array}{l}
l[1] = 1\\ 
r[m] = n\\ 
p[i] = h[l[i]] = h[l[i] + 1] = \ldots = h[r[i]]\\
l[i + 1] = r[i] + 1,\ \forall\ 1 \le i < m\\ 
p[i] < p[i + 1],\ \forall\ 1 \le i < m
\end{array}\right.$$

- Ở thời điểm đầu tiên, mảng $h$ chỉ chứa đoạn $(1, n, 0)$.
- Ở thời điểm thứ $i$:
    - Để tính được $f[i]$, ta sẽ tìm đoạn $(l[k], r[k], p[k])$ thỏa mãn $l[k] \le i \le r[k]$.
        - Vì mảng $h$ đã cập nhật đến $f[i - 1]$ nên $h[i]$ đã được cập nhật hoàn toàn (nhắc lại định nghĩa: $h[i] = \mathop{\arg\min} \limits_{0 \le j < i} f[j] + w(j, i)$).
        - Lúc này, ta sẽ cập nhật $f[i] = f[p[k]] + w(p[k], i)$.
    - Sau khi tính được $f[i]$, ta sẽ cập nhật lại mảng $h$. Theo nhận xét phía trên, ta sẽ tìm vị trí $z$ nhỏ nhất thỏa mãn $f[i] + w(i, z) < f[h[z]] + w(h[z], z)$.
    Xét đoạn cuối cùng trong mảng $h$, giả sử đoạn đó là $(l, r, p)$.
        - Nếu $f[i] + w(i, l) < f[p] + w(p, l)$, ta sẽ xóa đoạn đó khỏi mảng $h$ và tiếp tục xét đoạn cuối cùng tiếp theo.
        - Ngược lại, ta sẽ tìm vị trí $z$ nhỏ nhất thỏa mãn $f[i] + w(i, z) < f[p] + w(p, z)$ bằng tìm kiếm nhị phân, sau đó cập nhật lại $(l, r, p)$ thành $(l, z - 1, p)$, và thêm đoạn $(z, n, i)$ vào cuối mảng $h$. 

## Cài đặt mẫu

Ta có thể cài đặt thuật toán trên bằng cách sử dụng deque. Để thuận tiện cho việc cài đặt, ta sẽ không lưu lại các giá trị $h[i]$ đã qua sử dụng.

```cpp
struct item {
  int l, r, p;
};

const int N = 1e5 + 3;
int n;
long long f[N];

long long w(int j, int i) {
  // một hàm cost bất kì thỏa mãn
  // bất đẳng thức tứ giác
}

void solve() {
  deque<item> dq;
  dq.push_back({1, n, 0});
  for (int i = 1; i <= n; ++i) {
    f[i]=f[dq.front().p]+w(dq.front().p,i);
    // deque chỉ lưu giá trị từ h[i + 1]
    // tới h[n]
    ++dq.front().l;
    
    // nếu l > r, ta loại đoạn này khỏi deque
    if (dq.front().l > dq.front().r) {
      dq.pop_front();
    }

    while (!dq.empty()) {
      auto [l, r, p] = dq.back();
      if (f[i] + w(i, l) < f[p] + w(p, l)) {
        dq.pop_back();
        // p không còn là giá trị của
        // h[l], h[l + 1], ..., h[r]
        // lúc này, h[l]=h[l+1]=...=h[r]=i.
      }
      else break;
    }

    if (dq.empty()) {
      dq.push_back({i + 1, n, i});
      // h[i+1]=h[i+2]=...=h[n]=i
    }
    else {
      // tìm nhị phân vị trí pos nhỏ nhất
      // thỏa mãn h[pos] = i
      auto& [l, r, p] = dq.back();
      int low = l, high = r;
      int pos = r + 1, mid;
      while (low <= high) {
        mid = (low + high) / 2;
        if (f[i] + w(i, mid) < f[p] + w(p, mid)) {
          pos = mid, high = mid - 1;
        }
        else {
          low = mid + 1;
        }
      }

      // cập nhật đoạn (l,r,p) thành (l,pos-1,p)
      r = pos - 1;
      if (pos <= n) {
        dq.push_back({pos, n, i});
        // h[pos]=h[pos+1]=...=h[n]=i
      }
    }
  }
}
```

Vì số đoạn tối đa được thêm vào deque trong cả quá trình là $n$, kết hợp với tìm kiếm nhị phân ở cuối mỗi thời điểm, ta được độ phức tạp cuối cùng là $O(n \log n)$.

# Bài toán 1

[Codeforces - 319C](https://codeforces.com/contest/319/problem/C)

## Tóm tắt

Cho $n$ cây được đánh số hiệu từ $1$ tới $n$, mỗi cây có độ cao lần lượt là $a_1, a_2, \ldots, a_n$. Alob và Bice muốn cưa đổ tất cả $n$ cây sao cho tốn ít chi phí nhất.

Alob và Bice có một cái cưa máy, mỗi lần sử dụng cưa có thể giảm độ cao của một cây bất kì xuống $1$. Tuy nhiên, sau mỗi lần sử dụng, cưa máy cần được sạc lại. Chi phí để sạc phụ thuộc vào những cây đã được chặt hoàn toàn (những cây đã được giảm độ cao về $0$): trong những cây đã được chặt hoàn toàn, giả sử cây có số hiệu lớn nhất là $i$, chi phí để sạc cưa máy là $b_i$. Nếu không có cây nào đã được chặt hoàn toàn, ta không thể sạc lại cưa máy.

Điều kiện bài toán:$$\left\{\begin{matrix}
1 \le n \le 10^5\\ 
1 = a_1 < a_2 < \ldots < a_n \le 10^9\\ 
10^9 \ge b_1 > b_2 > \ldots > b_n = 0
\end{matrix}\right.$$

## Ý tưởng

Vì $b_n = 0$, ta sẽ tìm chi phí nhỏ nhất để chặt hoàn toàn cây $n$ (sau đó, ta có thể chặt bất kì cây nào mà không tốn chi phí).

Gọi $f[i]$ là chi phí nhỏ nhất để chặt hoàn toàn cây thứ $i$. Nếu cây gần nhất được chặt hoàn toàn trước đó là $j$, chi phí nhỏ nhất để chặt hoàn toàn cây thứ $i$ sẽ là $f[j] + b_j \cdot a_i$. Vì vậy, ta có được công thức quy hoạch động sau:
$$f[i] = \min \limits_{1 \le j < i} f[j] + b_j \cdot a_i$$

Nếu đặt $w(j, i) = b_j \cdot a_i$, hàm $w$ là một hàm thỏa mãn bất đẳng thức tứ giác.

**Chứng minh.**

Xét $4$ điểm $x < y \le z < t$, ta có:
$$\begin{array}{cl}
  & w(x, z) + w(y, t) - w(x, t) - w(y, z) \\
= & b_x \cdot a_z + b_y \cdot a_t - b_x \cdot a_t - b_y \cdot a_z \\
= & (b_x - b_y)(a_z - a_t) \le 0
\end{array}$$

Vì vậy, 
$$w(x, z) + w(y, t) \le w(x, t) + w(y, z)$$

Từ đây, ta có thể áp dụng thuật toán đã nêu trong bài.

## Cài đặt mẫu

```cpp
#include <bits/stdc++.h>
using namespace std;

struct item {
  int l, r, p;
};

const int N = 1e5 + 3;
int n, a[N], b[N];
long long f[N];

long long w(int j, int i) {
  return 1LL * b[j] * a[i];
}

void solve() {
  deque<item> dq;
  dq.push_back({2, n, 1});
  for (int i = 2; i <= n; ++i) {
    f[i] = f[dq.front().p] + w(dq.front().p, i);
    ++dq.front().l; 
    if (dq.front().l > dq.front().r) {
      dq.pop_front();
    }

    while (!dq.empty()) {
      auto [l, r, p] = dq.back();
      if (f[i] + w(i, l) < f[p] + w(p, l)) {
        dq.pop_back();
      }
      else break;
    }

    if (dq.empty()) {
      dq.push_back({i + 1, n, i});
    }
    else {
      auto& [l, r, p] = dq.back();
      int low = l, high = r, pos = r + 1, mid;
      while (low <= high) {
        mid = (low + high) / 2;
        if (f[i] + w(i, mid) < f[p] + w(p, mid)) {
          pos = mid, high = mid - 1;
        }
        else {
          low = mid + 1;
        }
      }

      r = pos - 1;
      if (pos <= n) {
        dq.push_back({pos, n, i});
      }
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  solve();
  cout << f[n];
}
```

# Bài toán 2

[VNOJ - Lễ hội](https://oj.vnoi.info/problem/lehoi)

## Tóm tắt

Ở ngôi làng nọ, có $n$ ngôi nhà nằm trên một đường thẳng. Biết trưởng làng sống ở nhà thứ $1$, nhà thứ $i$ nằm cách nhà trưởng làng đúng $a_i$ km về phía đông. Trưởng làng muốn chọn ra một số địa điểm trên đường thẳng để chuẩn bị tổ chức lễ hội, biết chi phí tổ chức lễ hội cho một địa điểm là $k$.

Sau khi chuẩn bị xong, tất cả người dân sẽ di chuyển đến địa điểm gần nhà mình nhất để tham gia lễ hội. Nếu một người dân ở cách địa điểm tổ chức $x$ km, chi phí để di chuyển sẽ là $x$.

Hãy tìm cách chọn một số địa điểm sao cho tổng chi phí tổ chức lễ hội và di chuyển là nhỏ nhất.

Nói cách khác, nếu như ta chọn $m$ địa điểm, địa điểm thứ $i$ nằm cách nhà trưởng làng đúng $s_i$ km về phía đông, tổng chi phí tổ chức lễ hội và di chuyển sẽ là $k \cdot m + \sum \limits_{i = 1}^{n} \min \limits_{j = 1}^{m} \|a_i - s_j\|$.

Điều kiện bài toán: 
$$\left\{\begin{array}{l}
1 \le n \le 2 \cdot 10^5, 1 \le k \le 10^9\\ 
0 = a_1 < a_2 < \ldots < a_n \le 10^9
\end{array}\right.$$

## Ý tưởng

Ta có nhận xét sau: tất cả người dân nằm trên một đoạn liên tiếp sẽ đến cùng một địa điểm, vì thế bài toán có thể viết lại thành: chia $n$ người dân thành các đoạn liên tiếp sao cho tổng chi phí là nhỏ nhất, biết chi phí mỗi đoạn gồm chi phí tổ chức $k$ và chi phí di chuyển của người dân trong đoạn.

Gọi $f[i]$ là chi phí nhỏ nhất để chia $i$ người dân thành các đoạn sao cho tổng chi phí là nhỏ nhất. Ta có công thức quy hoạch động sau:
$$f[i] = k + \min \limits_{0 \le j < i} f[j] + w(j, i)$$

với $w(j, i)$ là chi phí di chuyển của người dân nằm trong đoạn $j + 1$ tới $i$.

Ta sẽ chứng minh hàm $w$ thỏa mãn bất đẳng thức tứ giác.

**Chứng minh.**

Đặt số người dân trong đoạn $[l + 1, r]$ là $t = r - l$. 

Đặt $p[i] = a_1 + a_2 + \ldots + a_i$. Ta có $2$ trường hợp sau:

- Nếu $t$ chẵn, phương án đặt địa điểm tập trung tối ưu nhất là ở giữa người thứ $\frac{t}{2}$ và người thứ $\frac{t}{2} + 1$.
Chi phí di chuyển trong trường hợp này là $\sum \limits_{i = r - \frac{t}{2} + 1}^{r} a_i - \sum \limits_{i = l + 1}^{l + \frac{t}{2}} a_i$, hay $(p[r] - p[r - \frac{t}{2}]) - (p[l + \frac{t}{2}] - p[l])$.

- Ngược lại, phương án đặt địa điểm tập trung tối ưu nhất là ở nhà của người thứ $\frac{t + 1}{2}$.
Chi phí di chuyển trong trường hợp này là $\sum \limits_{i = r - \frac{t - 1}{2} + 1}^{r} a_i - \sum \limits_{i = l + 1}^{l + \frac{t - 1}{2}} a_i$, hay $(p[r] - p[r - \frac{t - 1}{2}]) - (p[l + \frac{t - 1}{2}] - p[l])$.

Xét $4$ điểm $x < y \le z < t$. Để thuận tiện cho việc chứng minh, ta sẽ giả sử độ dài các đoạn đều là chẵn. Các trường hợp còn lại cũng có thể chứng minh tương tự.

Với $r - l$ chẵn: $w(l, r) = (p[r] - p[r - \frac{k}{2}]) - (p[l + \frac{k}{2}] - p[l]) = p[l] + p[r] - 2 \cdot p[\frac{l + r}{2}]$.

Đặt $b = \frac{x + z}{2}$, $c = \frac{y + t}{2}$, $d = \frac{x + t}{2}$, $e = \frac{y + z}{2}$. Ta có:
$$\begin{array}{cl}
  & w(x, z) + w(y, t) - w(x, t) - w(y, z) \\
= & 2 \cdot (-p[\frac{x + z}{2}] - p[\frac{y + t}{2}] + p[\frac{x + t}{2}] + p[\frac{y + z}{2}])  \\
= & 2 \cdot (-p[b] - p[c] + p[d] + p[e]) \\
= & 2 \cdot (p[d] - p[b]) - 2 \cdot (p[c] - p[e]) \\
= & 2 \cdot (a_{b + 1} + a_{b + 2} + \ldots + a_d) \\
  & - 2 \cdot (a_{e + 1} + a_{e + 2} + \ldots + a_c) \\
= & 2 \cdot(a_{b + 1} - a_{e + 1}) + 2 \cdot (a_{b + 2} - a_{e + 2}) + \ldots \\
  & + 2 \cdot (a_d - a_c) \le 0
\end{array}$$

Vì vậy, 
$$w(x, z) + w(y, t) \le w(x, t) + w(y, z)$$

## Cài đặt mẫu

```cpp
#include <bits/stdc++.h>
using namespace std;

struct item {
  int l, r, p;
};

const int N = 2e5 + 3;
int n, k, a[N];
long long p[N], f[N];

long long w(int l, int r) {
  int t = (r - l) / 2;
  return (p[r] - p[r - t]) - (p[l + t] - p[l]);
}

void solve() {
  deque<item> dq;
  dq.push_back({1, n, 0});
  for (int i = 1; i <= n; ++i) {
    f[i] = k + f[dq.front().p] + w(dq.front().p, i);
    ++dq.front().l;
    if (dq.front().l > dq.front().r) {
      dq.pop_front();
    }

    while (!dq.empty()) {
      auto [l, r, p] = dq.back();
      if (f[i] + w(i, l) < f[p] + w(p, l)) {
        dq.pop_back();
      }
      else break;
    }

    if (dq.empty()) {
      dq.push_back({i + 1, n, i});
    }
    else {
      auto& [l, r, p] = dq.back();
      int low = l, high = r, pos = r + 1, mid;
      while (low <= high) {
        mid = (low + high) / 2;
        if (f[i] + w(i, mid) < f[p] + w(p, mid)) {
          pos = mid, high = mid - 1;
        }
        else {
          low = mid + 1;
        }
      }

      r = pos - 1;
      if (pos <= n) {
        dq.push_back({pos, n, i});
      }
    }
  }
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    p[i] = p[i - 1] + a[i];
  }
  solve();
  cout << f[n];
}
```

# Phụ lục

## Chứng minh nhận xét $\dagger$.

Ta sẽ chứng minh bằng cách phản chứng: giả sử tồn tại vị trí $i$ thỏa mãn $h[i] > h[i + 1]$. Để thuận tiện cho việc chứng minh, ta sẽ đặt $a = h[i],\ b = h[i + 1]$ ($a > b$). Điều này tương đương với:
$$\left\{\begin{matrix}
f[a] + w(a, i) < f[b] + w(b, i)\\ 
f[a] + w(a, i + 1) > f[b] + w(b, i + 1)
\end{matrix}\right.$$

Trừ hai bất đẳng thức theo vế, ta được:
$$w(a, i) - w(a, i + 1) < w(b, i) - w(b, i + 1)$$
$$\Leftrightarrow w(a, i) + w(b, i + 1) < w(a, i + 1) + w(b, i)$$

Tuy nhiên, theo tính chất của hàm $w$, xét bộ số $b < a < i < i + 1$, ta có:
$$w(b, i) + w(a, i + 1) \le w(b, i + 1) + w(a, i)$$

Điều này là vô lý. Vì vậy, ta có điều phải chứng minh.

## Ứng dụng

Kĩ thuật này thường được sử dụng cùng với kĩ thuật [Aliens' Trick](https://mamnoonsiam.github.io/posts/attack-on-aliens.html), kĩ thuật từng xuất hiện trong đề thi [IOI 2016](https://oj.uz/problem/view/IOI16_aliens). Ngoài ra, hầu hết các bài toán có thể giải bằng QHĐ bao lồi/QHĐ chia để trị đều có thể giải bằng kĩ thuật này.

Bạn đọc có thể luyện tập thêm về kĩ thuật ở những bài sau:

- [VJudge - Batch Scheduling](https://vjudge.net/problem/OpenJ_Bailian-1180)
- [Codeforces - 321E](https://codeforces.com/contest/321/problem/E)