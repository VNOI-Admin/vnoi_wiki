# Meet In The Middle (MITM)

[[_TOC_]]

# Giới thiệu
MITM là một kỹ thuật tìm kiếm được sử dụng khi đầu vào nhỏ nhưng không đủ nhỏ để có thể quay lui (backtracking). Trước khi tiếp tục về kỹ thuật MITM, chúng ta cần xem xét bài toán đơn giản sau:

## [CSES - Meet in the Middle](https://cses.fi/problemset/task/1628)

### Đề bài
Cho mảng $t$ có $N$ phần tử. Hỏi có bao nhiêu cách chọn tập con sao cho tổng bằng $x$.

Giới hạn:
- $1\le N\le40$
- $1\le x\le10^9$
- $1\le t_i\le10^9$

### Thuật toán ngây thơ: Quay lui (Backtracking)
#### Ý tưởng
Ta duyệt qua tất cả các tập con có thể có rồi cập nhật kết quả bằng đệ quy (một cách khác để duyệt qua các tập con là sử dụng bitmask <insert bài bitmask>).

#### Cài đặt
```cpp
long long cnt;
// quay lui đến phần tử thứ i
// trong i-1 phần tử đầu, tổng các t[i] trong tập là sum
void Try(int i, int sum) {
    // tiếp tục quay lui với tập có sum > x là không cần thiết
    if (sum > x) return;
 
    if (i > n) {
        if (sum == x) ++cnt;
    }
    else {
        // không lấy phần tử thứ i
        Try(i + 1, sum);
        // lấy phần tử thứ i
        Try(i + 1, sum + t[i]);
    }
}
long long solve() {
    cnt = 0;
    Try(1, 0);
    return cnt;
}
```

Thuật toán trên có độ phức tạp thời gian là $\mathcal{O}(2^N)$, không đủ nhanh để giải bài toán bởi vì $2^{40}$ khá lớn. Do đó, ta cần tìm một phương án tối ưu hơn.

### Thuật toán tối ưu: kỹ thuật MITM
Kỹ thuật MITM được mô tả như sau:
- Đặt $K=N/2$
- Chia $N$ phần tử thành $2$ tập:
	- Tập $X$ bao gồm $K$ phần tử đầu tiên.
	- Tập $Y$ bao gồm tất cả phần tử còn lại.
- Quay lui ở tập $X$ và lưu tổng của tất cả tập con vào mảng $A$. Tương tự, quay lui ở tập $Y$ và lưu tổng của tất cả tập con vào mảng $B$. Do đó, kích thước tối đa của mỗi mảng $A$ và $B$ là $2^K$.
- Bây giờ, ta cần kết hợp $2$ mảng $A$ và $B$:
	- Cách đơn giản nhất là lặp qua từng phần tử của $A$, với mỗi phần tử, ta duyệt qua tất cả phần tử của $B$.
Độ phức tạp là $\mathcal{O}(2^K\times2^K)=\mathcal{O}(2^{N})$ (không đủ nhanh)
	- Để tối ưu, ta sắp xếp mảng $B$ trước. Sau đó, lặp qua từng phần tử của $A$, với mỗi phần tử, ta sử dụng [tìm kiếm nhị phân](https://vnoi.info/wiki/algo/basic/binary-search.md) trong mảng $B$.
Độ phức tạp là $\mathcal{O}(2^K\times\log_2{2^K})=\mathcal{O}(2^KK)$
	- Một cách tối ưu khác là ta sắp xếp cả $2$ mảng $A$ và $B$ trước, sau đó sử dụng [kỹ thuật hai con trỏ](https://vnoi.info/wiki/algo/basic/two-pointers.md).
Độ phức tạp là $\mathcal{O}(\text{sort algorithm})+\mathcal{O}(2^K)$

#### Cài đặt (sử dụng tìm kiếm nhị phân)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 40 + 2;
int n, x;
int t[N];
vector<int> A, B;

void TryX(int i, int sum) {
    if (sum > x) return;

    if (i > n / 2) A.push_back(sum);
    else {
        TryX(i + 1, sum);
        TryX(i + 1, sum + t[i]);
    }
}
void TryY(int i, int sum) {
    if (sum > x) return;

    if (i > n) B.push_back(sum);
    else {
        TryY(i + 1, sum);
        TryY(i + 1, sum + t[i]);
    }
}

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> t[i];

    // Quay lui 2 tập X và Y
    TryX(1, 0);
    TryY(n / 2 + 1, 0);

    // Sắp xếp mảng B
    sort(B.begin(), B.end());

    // Lặp qua mảng A và tìm kiếm nhị phân:
    // - Đếm số lượng phần tử trong B có giá trị bằng x - A[i]
    long long cnt = 0;
    for (int sum : A) {
        cnt += upper_bound(B.begin(), B.end(), x - sum)
             - lower_bound(B.begin(), B.end(), x - sum);
    }
    cout << cnt << '\n';
}
```

#### Cài đặt (sử dụng kỹ thuật hai con trỏ)
```cpp
    // Quay lui 2 tập X và Y
    TryX(1, 0);
    TryY(n / 2 + 1, 0);

    // Sắp xếp mảng A và B
    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end());

    // Sử dụng kỹ thuật 2 con trỏ
    long long cnt = 0;
    for (int i = 0, j1 = 0, j2 = 0; i < A.size(); ++i) {
        int s = x - A[i]; // cần đếm lượng B[j] thoả B[j] = s
        while (j1 < B.size() && B[j1] < s) ++j1;
        while (j2 < B.size() && B[j2] <= s) ++j2;
        cnt += j2 - j1;
    }
    cout << cnt << '\n';
```

# Ứng dụng

## Bài toán 1: [VNOJ - Cái túi 1](https://oj.vnoi.info/problem/dttui1)

Có $N$ cục vàng, mỗi cục vàng có trọng lượng $W_i$ và giá trị $V_i$. Bạn có một cái túi có tải trọng tối đa là $M$. Hỏi tổng giá trị vàng lớn nhất có thể thu được mà không làm rách túi.

Giới hạn:
- $1\le N\le40$
- $1\le M\le10^9$
- $1\le W_i, V_i\le10^8$

### Ý tưởng
Áp dụng MITM, ta tách $N$ cục vàng thành $2$ tập $X$ và $Y$, tập $X$ chứa $N/2$ cục vàng đầu tiên và tập $Y$ chứa phần còn lại.

Bây giờ, quay lui cho với mỗi tập $X$ và $Y$, ta được $2$ tập $A$ và $B$ chứa các cặp (tổng trọng lượng $sumW$, tổng giá trị $sumV$) của các tập con.

Để kết hợp $2$ tập $A$ và $B$, ta cần giải quyết bài toán con: Với mỗi cặp $(sumW_i, sumV_i)$ của tập $A$, ta cần tìm một cặp $(sumW_j, sumV_j)$ trong tập $B$ sao cho $sumW_j\le M-sumW_i$ và $sumV_j$ là lớn nhất.

Để giải bài toán con này, gợi ý là sắp xếp lại mảng $B$ theo thứ tự tăng dần của $sumW_j$ và đặt $maxSumV_j=max(sumV_1, \ldots,sumV_j)$ (phần này có thể tính nhanh bằng [mảng cộng dồn](https://vnoi.info/wiki/algo/data-structures/prefix-sum-and-difference-array.md)).

### Cài đặt
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 40 + 2, MaxSize = (1 << 20) + 10;
int n, m;
int w[N], v[N];

long long sumVA[MaxSize];
int sumWA[MaxSize];
int sizeA;

pair<int, long long> B[MaxSize];
int sizeB;
int sumWB[MaxSize];
long long maxSumVB[MaxSize];

void TryX(int i, int sumW, long long sumV) {
    if (sumW > m) return;
    if (i > n / 2) {
        ++sizeA;
        sumWA[sizeA] = sumW;
        sumVA[sizeA] = sumV;
        return;
    }
    TryX(i + 1, sumW, sumV);
    TryX(i + 1, sumW + w[i], sumV + v[i]);
}

void TryY(int i, int sumW, long long sumV) {
    if (sumW > m) return;
    if (i > n) {
        ++sizeB;
        B[sizeB].first  = sumW;
        B[sizeB].second = sumV;
        return;
    }
    TryY(i + 1, sumW, sumV);
    TryY(i + 1, sumW + w[i], sumV + v[i]);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];

    TryX(1, 0, 0);
    TryY(n / 2 + 1, 0, 0);
    sort(B + 1, B + sizeB + 1);
    for (int i = 1; i <= sizeB; ++i) {
        sumWB[i]    = B[i].first;
        maxSumVB[i] = max(maxSumVB[i - 1], B[i].second);
    }

    long long maxValue = 0;
    for (int i = 1; i <= sizeA; ++i) {
        int j    = upper_bound(sumWB + 1, sumWB + sizeB + 1, m - sumWA[i]) - sumWB - 1;
        maxValue = max(maxValue, sumVA[i] + maxSumVB[j]);
    }
    cout << maxValue;
}
```

## Bài toán 2
Cho mảng $a$ gồm $n$ số nguyên, đếm số lượng dãy con tăng có độ dài $3$.

Giới hạn:
- $1\le n\le2000$
- $1\le a_i\le10^9$

## Ý tưởng
Đặt $a_i, a_j, a_k (i<j<k)$ ứng với một dãy con tăng có độ dài $3$.

Theo cách làm ngây thơ, với mỗi $i$, ta đếm số cặp $(j,k)$ thoả mãn trong $\mathcal{O}(n^2)$, tổng độ phức tạp thời gian sẽ là $\mathcal{O}(n^3)$.

Ta có thể ứng dụng "middle" như sau: thay vì xét $i$ đầu tiên, ta xét $j$ đầu tiên.
Với mỗi $j$, ta đếm số lượng $i<j$ thoả $a_i < a_j$ và $k>j$ thoả $a_k>a_j$ trong $\mathcal{O}(n)$, tổng độ phức tạp thời gian lúc này sẽ là $\mathcal{O}(n^2)$.

## Cài đặt
```cpp
for (int j = 0; j < n; ++j) {
    int smaller = 0, bigger = 0;
    for (int i = 0; i < j; ++i) {
        if (a[i] < a[j]) ++smaller;
    }
    for (int k = j + 1; k < n; ++k) {
        if (a[k] > a[j]) ++bigger;
    }
    answer += smaller * bigger;
}
```

## Bài toán 3: [CSES - Sum of Four Values](https://cses.fi/problemset/task/1642/)
<!-- (MITM kiểu prep) -->
Cho mảng $a$ gồm $n$ số nguyên và số nguyên $x$. Ta cần tìm $4$ vị trí **phân biệt** sao cho tổng giá trị ở $4$ vị trí đó bằng $x$.

Giới hạn:
- $1\le n\le1000$
- $1\le x,a_i\le10^9$

### Ý tưởng
Đặt $i,j,k,l$ $(i<j<k<l)$ là $4$ vị trí thoả mãn $a_i+a_j+a_k+a_l=x$.

Thuật toán ngây thơ của bài toán này là sử dụng $4$ vòng lặp lồng nhau với độ phức tạp $\mathcal{O}(n^4)$.
```cpp=1
for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
        for (int k = j + 1; k <= n; ++k)
            for (int l = k + 1; l <= n; ++l)
                if (a[i] + a[j] + a[k] + a[l] == x) { ... }
```
Ta có nhận xét: trong vòng lặp thứ $2$ (biến $j$), ta đang giải bài toán: tìm $2$ vị trí phân biệt **lớn hơn** $j$ sao cho tổng giá trị của $2$ vị trí đó bằng $x-a_i-a_j$.

Ta có thể giải bài toán này trước bằng cách:
- Duyệt qua tất cả cặp $2$ vị trí (đặt $2$ vị trí này là $k$ và $l$, $k < l$), với mỗi cặp vị trí, ta có một tổng $a_k+a_l$.
- Với mỗi giá trị tổng, có thể có nhiều cặp vị trí khác nhau thoả mãn, ta chỉ cần lưu lại cặp có $k$ lớn nhất (vì $k$ càng lớn thì càng có nhiều $j$ thoả mãn).

### Cài đặt
Sử dụng `std::map` để lưu cặp vị trí của mỗi giá trị tổng.

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 3;
int n, x;
int a[N];

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // preprocess
    map<int, pair<int, int>> mp;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            mp[a[i] + a[j]] = make_pair(i, j);

    // solve
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            // thay vì 2 vòng for, bây giờ ta chỉ cần 
            // truy vấn trên std::map
            int X = x - a[i] - a[j];
            if (mp.count(X)) {
                pair<int, int> arr = mp[X];
                if (j < arr.first) {
                    cout << i << ' ' << j << ' ' << arr.first << ' ' << arr.second;
                    return 0;
                }
            }
        }

    cout << "IMPOSSIBLE";
}
```

#### Phân tích
Độ phức tạp tiền xử lý: $\mathcal{O}(n^2\log(n^2))$
Độ phức tạp truy vấn: $\mathcal{O}(\log(n^2))$
Có $\mathcal{O}(n^2)$ truy vấn, vì thế, tổng độ phức tạp thời gian là: $\mathcal{O}(n^2\log(n^2))$

## Bài toán 4: [Kattis - Playlist](https://open.kattis.com/problems/playlist)

Cho đồ thị có hướng $n$ đỉnh ($n\le100$) và **bậc ngoài** của mỗi đỉnh không quá $40$. Tất cả đỉnh đều được tô màu. Tìm một đường đi độ dài $9$ sao cho $9$ đỉnh trong đường đi có màu phân biệt. Nếu có nhiều cách chọn, in ra bất kỳ, ngược lại, in ra "fail".

Giới hạn thời gian là rất lớn (12 giây).

### Ý tưởng
Tương tự [Bài toán 2](#Bài-toán-2), ta có thể ứng dụng "middle" như sau:
- Đặt đỉnh thứ $5$ trong đường đi là $u$.
- Với mỗi $u$:
	- Ta có tập $A$ gồm các đường đi độ dài $4$ ứng với $4$ đỉnh $1,2,3,4$ thoả mãn các màu là phân biệt và khác màu của $u$ (bằng DFS hoặc 4 vòng for từ $u$ **trong đồ thị ngược**)
	- Ta có tập $B$ gồm các đường đi độ dài $4$ ứng với $4$ đỉnh $6,7,8,9$ thoả mãn các màu là phân biệt và khác màu của $u$ (bằng DFS hoặc 4 vòng for từ $u$)
	- Độ phức tạp thời gian: $\mathcal{O}(40^4)$
- Bây giờ, để kết hợp $2$ tập, ta cần giải bài toán:
	- Với mỗi đường đi độ dài $4$ trong $A$, đặt là $X$, ta kiểm tra xem có tồn tại đường đi độ dài $4$ trong $B$ sao cho màu của $8$ đỉnh là phân biệt.
	- Ta có thể giải bài toán này bằng [Bao hàm - loại trừ](https://vnoi.info/wiki/translate/he/Number-Theory-7.md):
Số đường đi độ dài $4$ trong $B$ có màu phân biệt với $X$ = $|B|$ - (số đường đi trùng ít nhất $1$ màu) + (số đường đi trùng ít nhất $2$ màu) - (số đường đi trùng ít nhất $3$ màu) + (số đường đi trùng cả $4$ màu)
	- Độ phức tạp thời gian: $\mathcal{O}(2^4\times40^4)$
- Độ phức tạp thời gian của thuật toán là $\mathcal{O}(N\times2^4\times40^4)$

### Cài đặt
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 2;
int n;
int c[N];
vector<int> g[2][N];

int cntbit[16];
void init() {
    for (int msk = 1; msk < 16; ++msk) {
        cntbit[msk] = cntbit[msk >> 1] + (msk & 1);
    }
}

void readData() {
    cin >> n;
    map<string, int> artist;
    for (int i = 1; i <= n; ++i) {
        string name;
        cin >> name;
        c[i] = artist.count(name) ? artist[name] : (artist[name] = artist.size() + 1);

        int k, to;
        cin >> k;
        while (k--) {
            cin >> to;
            g[0][i].push_back(to);
            g[1][to].push_back(i);
        }
    }
}

vector<int> getAns(vector<int> res) {
    set<int> s;
    for (int u : res) s.insert(c[u]);

    for (int v0 : g[0][res.back()]) {
        if (s.count(c[v0])) continue;
        s.insert(c[v0]);
        for (int v1 : g[0][v0]) {
            if (s.count(c[v1])) continue;
            s.insert(c[v1]);
            for (int v2 : g[0][v1]) {
                if (s.count(c[v2])) continue;
                s.insert(c[v2]);
                for (int v3 : g[0][v2]) {
                    if (s.count(c[v3])) continue;

                    res.push_back(v0);
                    res.push_back(v1);
                    res.push_back(v2);
                    res.push_back(v3);
                    return res;
                }
                s.erase(c[v2]);
            }
            s.erase(c[v1]);
        }
        s.erase(c[v0]);
    }
    return {};
}

int cnt[N * N * N * N];
int getHash(const array<int, 4> &a, int msk) {
    int hsh = 0;
    for (int i = 0; i < 4; ++i) {
        if (msk >> i & 1) hsh = hsh * N + c[a[i]];
    }
    return hsh;
}
vector<int> solve(int u) {
    vector<int> sav(1, 0);

    for (int v0 : g[0][u]) {
        if (c[v0] == c[u]) continue;
        for (int v1 : g[0][v0]) {
            if (c[v1] == c[v0] || c[v1] == c[u]) continue;
            for (int v2 : g[0][v1]) {
                if (c[v2] == c[v1] || c[v2] == c[v0] || c[v2] == c[u]) continue;
                for (int v3 : g[0][v2]) {
                    if (c[v3] == c[v2] || c[v3] == c[v1] || c[v3] == c[v0] || c[v3] == c[u]) continue;

                    array<int, 4> a = { c[v0], c[v1], c[v2], c[v3] };
                    sort(a.begin(), a.end());
                    for (int msk = 0; msk < 16; ++msk) {
                        int hsh = getHash(a, msk);
                        ++cnt[hsh];
                        sav.push_back(hsh);
                    }
                }
            }
        }
    }

    for (int v0 : g[1][u]) {
        if (c[v0] == c[u]) continue;
        for (int v1 : g[1][v0]) {
            if (c[v1] == c[v0] || c[v1] == c[u]) continue;
            for (int v2 : g[1][v1]) {
                if (c[v2] == c[v1] || c[v2] == c[v0] || c[v2] == c[u]) continue;
                for (int v3 : g[1][v2]) {
                    if (c[v3] == c[v2] || c[v3] == c[v1] || c[v3] == c[v0] || c[v3] == c[u]) continue;

                    array<int, 4> a = { c[v0], c[v1], c[v2], c[v3] };
                    sort(a.begin(), a.end());
                    int sum = 0;
                    for (int msk = 0; msk < 16; ++msk) {
                        int hsh = getHash(a, msk);
                        sum += cnt[hsh] * (cntbit[msk] & 1 ? -1 : 1);
                    }
                    if (sum > 0) {
                        vector<int> res = { v3, v2, v1, v0, u };
                        return getAns(res);
                    }
                }
            }
        }
    }

    for (int x : sav) cnt[x] = 0;
    return vector<int>();
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        vector<int> vec = solve(i);
        if (!vec.empty()) {
            for (int x : vec) cout << x << ' ';
            return;
        }
    }
    cout << "fail";
}

int main() {
    init();
    readData();
    solve();
}
```

# Bài tập áp dụng khác
- [**VNOJ - Chia vàng**](https://oj.vnoi.info/problem/dgold) <!--basic-->
- [**VNOJ - Phân tập**](https://oj.vnoi.info/problem/lqddiv) <!--basic-->
- [**VNOJ - Bipalindrome**](https://oj.vnoi.info/problem/mbipalin) <!--basic-->
- [**Codeforces - 888E (Maximum Subsequence)**](https://codeforces.com/contest/888/problem/E) <!--basic-->
- [**Codeforces - 1006F (Xor-Paths)**](https://codeforces.com/contest/1006/problem/F) <!--2d-->
- [**Codeforces - 995E (Number Clicker)**](https://codeforces.com/contest/995/problem/E) <!--paradox - random-->
- [**Atcoder - ARC135F (Delete 1, 4, 7, ...)**](https://atcoder.jp/contests/arc135/tasks/arc135_f)
<!--não to vcl mới nghĩ ra được đoạn trước khi phân tập-->

<!--
https://codeforces.com/blog/entry/95571 - Errichto's blog (seen)
P4 P6 P7 là random paradox nên skip hong viết hihi
-->
