---
title: Tổng Minkowski
description: 
published: true
date: 2024-09-09T13:27:24.826Z
tags: geometry
editor: markdown
dateCreated: 2024-09-04T07:23:33.043Z
---

# Tổng Minkowski của các bao lồi
**Người viết:**
- Đặng Đoàn Đức Trung - UT Austin

**Reviewer:**
- Nguyễn Hoàng Vũ - Trường Đại học Công nghệ - ĐHQGHN
- Trần Xuân Bách - Đại học Chicago (Mỹ)
## Giới thiệu
Một số bài toán trung bình khó yêu cầu người giải phải thực hiện thao tác *ghép* hai bao lồi như sau: với hai bao lồi $A$ và $B$, dựng một đa giác $C$ chỉ bao gồm các điểm $a + b$ với $a \in A$ và $b \in B$ (ở đây một điểm thuộc bao lồi nếu nó nằm trong/trên bao lồi, và việc cộng điểm được thực hiện như việc cộng véctơ). Đây chính là việc tìm *tổng Minkowski* của hai bao lồi $A$ và $B$.

Ở bài viết sau, chúng ta hãy cùng xem qua cách tìm tổng Minkowski một cách hiệu quả, cũng như một số bài toán có thể được giải thông qua thuật toán này.

*Bài viết này là phần 2 của chuỗi bài viết về các kĩ thuật xử lí bao lồi/hàm lồi; các bạn có thể đọc phần 1 [ở đây](/algo/trick/convex_greedy.md). Một phần của bài viết được tham khảo từ [cp-algorithm](https://cp-algorithms.com/geometry/minkowski.html). Template code hình được lấy từ [kactl](https://github.com/kth-competitive-programming/kactl).*

## Định nghĩa

Để nhắc lại từ phần giới thiệu, ta định nghĩa tổng Minkowski $A + B$ của hai bao lồi $A$ và $B$ như sau:
- Với mọi điểm $c \in A + B$, tồn tại hai điểm $a \in A$ và $b \in B$ sao cho $a + b = c$.

| ![minkowski_1.png](/algo/minkowski_1.png) | 
|:--:| 
| *Ví dụ của tổng Minkowski của hai bao lồi $A$ và $B$* |

Như ta thấy ở ví dụ trên, $A + B$ cũng là một bao lồi và có số lượng điểm là $5$. Một cách tổng quát hơn, ta có thể chứng minh được là tổng $A + B$ cũng là đa giác lồi và có tối đa $|A| + |B|$ đỉnh.

## Thuật toán tìm tổng Minkowski của hai bao lồi

Lấy ví dụ vừa nêu trên, ta có thể nhìn $A + B$ dưới một góc nhìn khác như sau.

![minkowski_2.png](/algo/minkowski_2.png)

Ta có hai nhận xét sau:
- Đỉnh trái dưới của $A + B$ bằng đỉnh trái dưới của $A$ cộng đỉnh trái dưới của $B$.
- Cạnh của $A + B$ được là hợp của các cạnh từ $A$ và các cạnh từ $B$.

Vì thế ta có thể dựng $A + B$ như sau (giả sử rằng $A$ và $B$ đi ngược chiều kim đồng hồ và được xoay lại sao cho $A_1$ và $B_1$ là đỉnh trái dưới của $A$ và $B$):
- Xuất phát với $i = 1$ và $j = 1$. Thêm đỉnh $A_1 + B_1$ vào đáp án.
- Ở mỗi bước, so sánh góc của $\overrightarrow{A_i A_{i + 1}}$ và $\overrightarrow{B_j B_{j + 1}}$. Tăng con trỏ tương ứng với cạnh có góc nhỏ hơn theo hướng ngược chiều kim đồng hồ (tăng cả hai nếu góc của hai cạnh bằng nhau) và thêm $A_i + B_j$ vào đáp án.

Ta có thể coi thuật toán này như việc sắp xếp cạnh của hai bao lồi $A$ và $B$ : do cạnh của $A$ và $B$ đã được sắp xếp sẵn ngược chiều kim đồng hồ, ta chỉ cần chạy thuật toán ghép hai mảng đã được sắp xếp giống như bước ghép trong merge sort.

Dưới đây là một cách cài đặt mẫu:
```cpp!
// rút gọn từ kactl: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    T cross(P p) const { return x*p.y - y*p.x; }
};

template<class P>
vector<P> minkowskiSum(vector<P> a, vector<P> b) {
    // xoay a và b sao cho điểm trái dưới là điểm đầu tiên
    rotate(begin(a), min_element(begin(a), end(a)), end(a));
    rotate(begin(b), min_element(begin(b), end(b)), end(b));
    int n = a.size(), m = b.size();
    vector<P> h(n + m + 1); h[0] = a[0] + b[0];
    int t = 1;
    // ở đây ta cho phép i đi tới n và j đi tới m để thể hiện việc đã duyệt qua hết các cạnh của A và B
    for (int i = 0, j = 0; i < n || j < m; ) {
        if (i == n) j++;
        else if (j == m) i++;
        else {
            P pa = a[(i + 1) % n] - a[i], pb = b[(j + 1) % m] - b[j];
            auto cr = pa.cross(pb);
            if (cr >= 0) i++;
            if (cr <= 0) j++;
        }
        h[t++] = (a[i % n] + b[j % m]);
    }
    return {h.begin(), h.begin() + t - (t >= 2 && h[0] == h[t - 1])};
}
```

Độ phức tạp của thuật toán là $O(|A| + |B|)$.

## Một số bài toán ví dụ

### CF 87E - Mogohu-Rea Idol

Link bài: [CF 87E](https://codeforces.com/problemset/problem/87/E).

#### Đề bài

Cho ba bao lồi $A$, $B$ và $C$ và $q$ truy vấn. Với mỗi truy vấn, ta được nhận một điểm $x$, và ta cần trả lời rằng có tồn tại ba điểm $a \in A$, $b \in B$, và $c \in C$ sao cho điểm $x$ là trọng tâm của tam giác được tạo bởi $a, b, c$ ($1 \le |A|, |B|, |C|, q \le 10^5$).

#### Phân tích

Nhận xét rằng $x$ là trọng tâm của tam giác tạo bởi $a, b, c$ khi và chỉ khi $3x = a + b + c$. Nói cách khác, điểm $3x$ phải thuộc tổng Minkowski $A + B + C$. Vì thế, ta chỉ cần dựng trước $A + B + C$, và với mỗi truy vấn ta chỉ cần kiểm tra nếu điểm $3x$ thuộc bao lồi này không là được.

#### Cài đặt

Các bạn có thể tham khảo cách cài đặt [tại đây](https://codeforces.com/contest/87/submission/228115969). Ở phần cài đặt này, hàm `minkowskiSum` nhận một tập các bao lồi (không nhất thiết chỉ là 2 bao lồi) và trả về tổng Minkowski của tập bao lồi này. Độ phức tạp là $O(p + q \log p)$, với $p \le |A| + |B| + |C|$ là số lượng điểm trong tổng Minkowski.

### Tìm khoảng cách giữa hai bao lồi

#### Đề bài

Cho hai bao lồi $A$ và $B$, tìm khoảng cách ngắn nhất giữa hai điểm bất kì thuộc hai bao lồi này. Nếu $A$ và $B$ có điểm chung thì in ra 0 ($1 \le |A|, |B| \le 2 \cdot 10^5$).

#### Phân tích

Đây là một bài toán kinh điển sử dụng tổng Minkowski. Nhận xét là bài toán có thể được viết như sau (ở đây $||u||_2 = \sqrt{x_u^2 + y_u^2}$ là khoảng cách của $u$ tới gốc tọa độ):
$$\min_{a \in A, b \in B} ||a - b||_2 = \min_{a \in A, b \in B} ||a + (-b)||_2$$

Vì thế, nếu ta gọi $-B$ chứa tất cả các điểm $-b$ khi $b \in B$ thì bài toán tương đương với việc tìm $\min_{a \in A, c \in -B} ||a + c||_2$. Gọi $S = A + (-B)$ là tổng Minkowski của bao lồi $A$ và $-B$, thì bài toán trở thành: tìm điểm trong $S$ gần gốc tọa độ nhất. Bài toán này ta có thể giải một cách dễ dàng: nếu $S$ chứa gốc tọa độ thì đáp án là $0$, ngược lại thì ta có thể lặp qua cạnh của $S$ và tìm khoảng cách ngắn nhất từ gốc tọa độ tới từng cạnh của $S$.

#### Cài đặt
Các bạn có thể tham khảo cách cài đặt dưới đây.
```cpp!
#include <bits/stdc++.h>
using namespace std;

/// KACTL

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

using P = Point<double>;
bool inHull(const vector<P>& l, P p, bool strict = true) {
    int a = 1, b = sz(l) - 1, r = !strict;
    if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}

double segDist(P s, P e, P p) {
    if (s==e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

/// END KACTL

template<class P>
vector<P> minkowskiSum(vector<P> a, vector<P> b) {
    rotate(begin(a), min_element(begin(a), end(a)), end(a));
    rotate(begin(b), min_element(begin(b), end(b)), end(b));
    int n = a.size(), m = b.size();
    vector<P> h(n + m + 1); h[0] = a[0] + b[0];
    int t = 1;
    for (int i = 0, j = 0; i < n || j < m; ) {
        if (i == n) j++;
        else if (j == m) i++;
        else {
            P pa = a[(i + 1) % n] - a[i], pb = b[(j + 1) % m] - b[j];
            auto cr = pa.cross(pb);
            if (cr >= 0) i++;
            if (cr <= 0) j++;
        }
        h[t++] = (a[i % n] + b[j % m]);
    }
    return {h.begin(), h.begin() + t - (t >= 2 && h[0] == h[t - 1])};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<P> a(n), b(m);
    vector<vector<P>> poly(n, {P(0, 0)});
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i].x >> b[i].y;
        b[i] = P(0, 0) - b[i]; // lật B qua gốc tọa độ
    }
    auto sum = minkowskiSum(a, b);
    if (inHull(sum, P(0, 0), false)) {
        cout << "0.0\n";
    } else {
        double ans = numeric_limits<double>::max();
        int s = sum.size();
        for (int i = 0; i < s; i++) {
            ans = min(ans, segDist(sum[i], sum[(i + 1) % s], P(0, 0)));
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
}
```
Độ phức tạp của thuật toán là $O(n + m)$.

## Bài tập áp dụng

- [CF 1195F](https://codeforces.com/problemset/problem/1195/F).
- [CF 1841F](https://codeforces.com/problemset/problem/1841/F).
- [Discover Singapore 2019, 300iq Contest - I](https://qoj.ac/problem/4246).
- [ICPC World Finals 2021 - K](https://qoj.ac/problem/5111).