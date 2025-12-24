---
title: Chia để trị Chen Danqi
description: 
published: true
date: 2025-03-25T04:47:10.085Z
tags: 
editor: markdown
dateCreated: 2025-03-22T16:24:57.377Z
---

# Chen Danqi D&C
Tác giả: 
- Đoàn Gia Huy - HUS High School for Gifted Students.

Reviewer:
- Lê Minh Hoàng - Phổ thông Năng khiếu, ĐHQG-HCM
- Nguyễn Tấn Minh – THPT Chuyên Lê Hồng Phong, TPHCM.
- Trần Quang Trường - Trường Đại học Công Nghệ Thông tin, ĐHQGHCM.
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Kon Tum

Hiệu đính:
- Nguyễn Minh Nhật - Georgia Institute of Technology.

## Kiến Thức Cần Biết

Để hiểu được bài viết, độc giả nên kiến thức về các phần sau:

- **[Chia để trị](/algo/basic/divide-and-conquer)**: Đây là kiến thức chủ chốt để hiểu được bài viết. Kỹ thuật này xoay quanh việc chia nhỏ bài toán ra thành các bài toán bé hơn để xử lý rồi hoàn thiện bằng cách ghép các bài toán con lại.
- **[Sweep Line](/algo/geometry/Sweep-Line.md)**: Thuật toán giúp sắp xếp lại thứ tự các điểm để có thể dễ dàng kết hợp với các cấu trúc dữ liệu như Segment Tree, Fenwick Tree.
- **Một số cấu trúc dữ liệu như [Fenwick Tree](/algo/data-structures/fenwick), [Segment Tree](/algo/data-structures/segment-tree-basic.md), ...**: Thường các bài toán CDQ sẽ sử dụng các cấu trúc dữ liệu này. 

## Giới Thiệu
**Chen, DanQi D&C (CDQ D&C)** là kĩ thuật tối ưu bằng chia để trị thường được áp dụng trong các bài toán có dạng tương tự bài toán sau:

:::info 
Cho tập điểm ba chiều $V$. Với mỗi điểm $P_i \in V$, đếm số điểm $P_j \in V$ sao cho $x_j < x_i, y_j < y_i, z_j < z_i$.
:::

Bài toán trên có thể được giải bằng CDQ D&C với độ phức tạp $O(n \log^2{n})$ với $n$ là số điểm.
## Ý Tưởng
### Các Bước Thực Hiện
Giả sử ta giảm số chiều của bài toán trên xuống còn $2$ chiều, lúc này bài toán này có thể giải bằng thuật toán **Sweep Line**. Cụ thể, ta sắp xếp tập điểm theo chiều đầu tiên, sau đó duyệt tập điểm rồi cập nhật và lấy đáp án bằng một số cấu trúc dữ liệu như Segment Tree, Fenwick Tree.

Khi tăng số chiều của bài toán lên $3$, ta có thể dễ dàng xử lý bằng cách tăng chiều của Segment Tree/Fenwick Tree lên thành $2$ chiều để giải trong độ phức tạp $O(n \log^2{n})$. Tuy nhiên, hệ số thời gian chạy của thuật toán này đôi lúc không đủ tốt, kèm theo độ phức tạp không gian lớn. Lúc này ta có thể áp dụng CDQ D&C để giải bài toán cũng trong $O(n \log^2{n})$ nhưng có thời gian chạy và độ phức tạp không gian tốt hơn.

Các bước giải bằng CDQ trên tập điểm $3$ chiều có dạng như sau:

:::success
- Tiền xử lý: Sắp xếp tập $P$ theo chiều $x$.
- Chia: Xét đoạn $[l..r]$ của tập $P$, ta chia đoạn này thành $2$ đoạn $[l...m]$ và $[m+1..r]$ (lấy $m$ là vị trí chính giữa của đoạn).
- Đệ quy: Xử lý bài toán trên đoạn $[l..m]$ và $[m+1..r]$.
- Kết hợp: Tính phần đóng góp của đoạn $[l..m]$ cho đoạn $[m+1..r]$ và gộp hai đoạn sao cho kết quả **sắp xếp theo chiều $y$**.
:::

Khi đã sắp xếp tập $P$ theo chiều $x$, việc tính phần đóng góp của đoạn $[l..m]$ cho đoạn $[m+1..r]$ lúc này được đơn giản hóa xuống bài toán gần giống bài toán hai chiều. Để tối ưu thuật toán "Kết hợp", sau khi thực hiện hàm chia để trị trên đoạn $[l..r]$, ta cần đảm bảo đoạn được sắp xếp lại theo chiều $y$ (xem phần dưới).

#### Đánh Giá Độ Phức Tạp

- Tiền xử lý: Ở bước này ta sẽ thực hiện việc sort theo một chiều của bài toán, do đó độ phức tạp sẽ là $O(n \log{n})$.
- $3$ bước còn lại có cách hoạt động giống với Merge Sort kết hợp cùng cấu trúc dữ liệu như Segment Tree hoặc Fenwick Tree. Do đó ở $3$ bước này sẽ có độ phức tạp là $O(n \log{n} * f)$ (với $f$ là độ phức tạp của cấu trúc dữ liệu được sử dụng) (để chứng minh độ phức tạp này ta có thể sử dụng Master Theorem: $T(n) = 2T(n/2) + O(N * f) = O(N \log N * f)$).

### Cách Thức Hoạt Động
Đầu tiên, ta sắp xếp theo chiều $x$. Với mọi vị trí $i < j$, ta có $x_i \leq x_j$. Khi thực hiện ``dnc(l, r)``, ta gọi $2$ bài toán con ``dnc(l, m)`` và ``dnc(m + 1, r)``.

Khi này, đoạn $[l..m]$ và $[m+1..r]$ đã được sắp xếp theo $y$. Do thao tác sắp xếp $2$ đoạn $[l..m]$ và $[m+1..r]$ được thực hiện độc lập, nên mỗi phần tử trong đoạn $[m+1..r]$ vẫn có chiều $x$ lớn hơn hoặc bằng mọi phần tử trong đoạn $[l..m]$.

:::info
Trong bài viết, các chiều $x$, $y$, $z$ chỉ mang tính tượng trưng. Nói cách khác, khi làm các bài sử dụng CDQ, ta thường sắp xếp các chiều có khoảng lớn để ưu tiên chiều có kích thước bé nhất cho cấu trúc dữ liệu.
:::

Để tính được phần đóng góp của đoạn $[l..m]$ cho đoạn $[m+1..r]$, ta sẽ duyệt qua cả $2$ đoạn tương tự Merge Sort theo chiều $y$ kết hợp cùng cấu trúc dữ liệu (ví dụ như Segment Tree). Cụ thể, ta so sánh hai phần tử đứng đầu hai đoạn và ưu tiên duyệt phần tử có chiều $y$ nhỏ hơn.

Khi duyệt qua phần tử thuộc $[l..m]$, ta sẽ tiến hành cập nhật lên cấu trúc dữ liệu. Khi duyệt qua $1$ phần tử thuộc đoạn $[m+1..r]$, ta sẽ cập nhật đáp án cho phần tử này dựa theo cấu trúc dữ liệu.

Do ta chỉ cần tính đóng góp của đoạn $[l..m]$ cho đoạn $[m+1..r]$ và chiều $x$ đã được sort từ ban đầu, chiều $y$ đã được sort qua việc thực hiện hàm `dnc()` trên $2$ đoạn, khi này từ $3$ chiều ta đã có thể rút gọn còn $1$ chiều $z$. 

## Cài Đặt
Trước hết, ta khai báo kiểu dữ liệu:
```cpp
struct point {
    int x, y, z, i;
    // Ta lưu lại i là vị trí cập nhật các điểm
};

struct cmp {
    bool operator() (point a, point b) {
        if (a.x != b.x) return a.x > b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.z != b.z) return a.z < b.z;
        return a.i < b.i;
    }
};
```
:::danger
Hàm so sánh trên vô cùng quan trọng. Độc giả nên chú ý về thứ tự sắp xếp của các phần tử cần dùng trong bài, đặc biệt trường hợp hai phần tử có thứ tự bằng nhau. Cụ thể

- Nếu đề bài yêu cầu $x_j < x_i$, các phần tử truy vấn phải nằm trước các phần tử cập nhật có cùng thứ tự.
- Nếu đề bài yêu cầu $x_j \leq x_i$, các phần tử truy vấn phải nằm sau các phần tử cập nhật có cùng thứ tự.

Việc cài đặt hàm so sánh không đúng có thể tạo ra lỗi **rất** khó debug.
:::

Hàm ``dnc(l,r)`` thường có dạng như sau (cài đặt ngắn hơn ở phía dưới):
```cpp!
vector<point> v;

void dnc(int l, int r) {
    if (l == r) return;

    int m = (l + r) >> 1; 
    int lptr = l, rptr = m + 1;
    
    dnc(l, m); dnc(m + 1, r); // Thực hiện trên 2 khoảng
    
    vector<point> tmp; // Mảng lưu lại đoạn [l..r] sau khi sort theo y
    vector<int> revert; // Mảng lưu lại những vị trí đã cập nhật để đảo ngược sau khi kết thúc phần Kết hợp

    while (lptr <= m && rptr <= r) {
        if (v[lptr].y > v[rptr].y) {
            // Cập nhật ctdl
            revert.push_back(v[lptr].z); 
            tmp.push_back(v[lptr++]);
        }
        else {
            // Truy vấn ctdl
            tmp.push_back(v[rptr++]);
        }
    }

    while (lptr <= m) {
        tmp.push_back(v[lptr++]);
    }

    while (rptr <= r) {
        // Truy vấn ctdl 
        tmp.push_back(v[rptr++]);
    }

    // Cập nhật lại phần vừa sort
    for (int i = l; i <= r; i++) v[i] = tmp[i-l]; 

    // Đảo ngược phần đã cập nhật để reset lại ctdl
    for (int i : revert) {
        // ...
    }
}

```

Để ngắn gọn hơn ta có thể viết hàm `dnc(l,r)` như sau:
```cpp!
void dnc(int l, int r) {
    if (l == r) return;

    int m = (l + r) >> 1;
    int lptr = l, rptr = m + 1;

    dnc(l, m); dnc(m + 1, r); // Thực hiện trên 2 khoảng

    vector<point> tmp; // Mảng lưu lại đoạn [l..r] sau khi sort theo y
    vector<int> revert; // Mảng lưu lại những vị trí đã cập nhật để đảo ngược sau khi kết thúc phần Kết hợp

    for (int rptr = m+1; rptr <= r; rptr++) {
        for (; lptr <= m && v[lptr].y <= a[rptr].y; lptr++) {
            // Cập nhật ctdl
            revert.push_back(v[lptr].z);
            tmp.push_back(v[lptr]);
        }
        // Truy vấn ctdl
        tmp.push_back(v[rptr]);
    }
    
    // lptr có thể khác m, nhưng ta không cần cập nhật nữa vì không còn truy vấn
    for (; lptr <= m; lptr++) {
        tmp.push_back(v[lptr]); // Không cần cập nhật ctdl do không còn truy vấn
    }
    
    // Đảo ngược phần đã cập nhật để reset lại ctdl
    for (int i : revert) {
        // ...
    }
}

```
## Bài Toán Ví Dụ
### [Codeforces 12D - Ball](https://codeforces.com/problemset/problem/12/D)
#### Đề Bài
Cho $N$ điểm có dạng $(x,y,z)$. Đếm số điểm $i$ mà tồn tại điểm $j$ sao cho $x_i < x_j, y_i < y_j, z_i < z_j$.

Giới hạn: $1 \leq N \leq 500000, 0 \leq x_i, y_i, z_i \leq 10^9$.
#### Lời Giải
Bài toán này ngược lại với ví dụ, thay vì đếm số điểm ở bên trong thì ta sẽ đếm số điểm ở phía ngoài của $1$ điểm. Ta sẽ giải như sau:

- Trước hết, ta khai báo một số kiểu dữ liệu cần thiết:
    ```cpp
    struct point { int x, y, z, i; };

    struct cmp {
        bool operator() (point a, point b) {
            return a.x > b.x;
            // Ở bài toán này, ta có thể thấy do phép so sánh là <,
            // việc thực hiện sort cho y, z và i không quan trọng
            // nếu ta đã sort đúng cho x.
        }
    };
    ```
- Do $0 \leq x_i, y_i, z_i \leq 10^9$, ta sẽ thực hiện nén số để dễ dàng sử dụng Fenwick Tree hơn:
    ```cpp!
    for (int i = 1; i <= n; i++) {
        v.push_back({x[i], y[i], z[i], i});
        sortX.push_back(x[i]); sortY.push_back(y[i]); sortZ.push_back(z[i]);
    }

    sort(sortX.begin(),sortX.end());
    sort(sortY.begin(),sortY.end());
    sort(sortZ.begin(),sortZ.end());

    for (point& u : v) {
        u.x = lower_bound(sortX.begin(),sortX.end(),u.x) - sortX.begin() + 1;
        u.y = lower_bound(sortY.begin(),sortY.end(),u.y) - sortY.begin() + 1;
        u.z = lower_bound(sortZ.begin(),sortZ.end(),u.z) - sortZ.begin() + 1;
    }
    ```
- Tới hàm ``dnc()``, ta sẽ thực hiện như sau:
    ```cpp!
    const maxN = 1e5 + 5;

    // TEMPLATE Fenwick Tree
    // luu y day la fenwick tree nguoc, ham get se lay tong tu (u -> maxn)
    long long bit[maxN];

    void upd(ll u, ll v) {
        while (u) {
            bit[u] += v; 
            u -= (u&(-u));
        }
    }

    ll get(ll u) {
        ll sum = 0; 
        while (u < mxn) {
            sum += bit[u];
            u += (u&(-u));
        } 
        return sum;
    }

    bool ans[maxN];

    vector<point> v;

    void dnc(int l, int r) {
        if (l == r) return;

        int m = (l + r) >> 1; 
        int lptr = l, rptr = m + 1;

        dnc(l, m); dnc(m + 1, r);
        vector<point> tmp; 
        vector<int> revert;

        while (lptr <= m && rptr <= r) {
            if (v[lptr].y > v[rptr].y) {
                upd(v[lptr].z,1); // Cập nhật lên Fenwick Tree
                revert.push_back(v[lptr].z); // Lưu lại vị trí vừa cập nhật để đảo ngược
                tmp.push_back(v[lptr++]); // Vị trí mới sau khi Merge Sort
            }
            else {
                ans[v[rptr].i] |= get(v[rptr].z + 1); // Kiểm tra xem có phần tử nào thỏa mãn không
                tmp.push_back(v[rptr++]);
            }
        }

        while (lptr <= m) {
            tmp.push_back(v[lptr++]);
        }

        while (rptr <= r) {
            ans[v[rptr].i] |= get(v[rptr].z + 1); 
            tmp.push_back(v[rptr++]);
        }

        for (int i = l; i <= r; i++) v[i] = tmp[i-l];

        for (int i : revert) upd(i,-1);
    }
    ```
- Cuối cùng ta chỉ cần đếm số ``ans[]`` có giá trị bằng $1$ là kết thúc bài toán.
- Độ phức tạp: $O(N \log^2{N})$.
### [JOI19 - Examination](https://oj.uz/problem/view/JOI19_examination)
#### Đề Bài
Có $N$ học sinh, học sinh thứ $i$ đạt $S_i$ điểm môn Toán học, $T_i$ điểm môn Tin học. Giáo sư $T$ và $I$ sẽ đánh giá xem một học sinh qua hay trượt môn. 
Với giáo sư $T$, giáo sư yêu cầu $\geq A$ điểm môn Toán, $\geq B$ điểm môn Tin.
Với giáo sư $I$, giáo sư yêu cầu $\geq C$ điểm tổng Toán và Tin.
Một học sinh được đánh giá là đạt khi được cả $2$ giáo sư cho qua môn.
Cho $Q$ truy vấn, mỗi truy vấn cho $A,B,C$, yêu cầu tính xem có bao nhiêu học sinh đạt.

Giới hạn: $1 \leq N, Q \leq 100000, 0 \leq S_i, T_i, A_j, B_j, C_j \leq 10^9$.
#### Lời Giải
Thực tế thì bài toán này không khác bài toán trên quá nhiều, với mỗi học sinh, ta chỉ cần lưu lần lượt $x,y,z$ là điểm môn Toán, điểm môn Tin, tổng điểm $2$ môn.

Bài toán này chia ra làm $2$ loại điểm, điểm học sinh và điểm yêu cầu của giáo sư, do đó ta sẽ thêm $1$ biến nữa là $v$ để biết đâu là điểm của học sinh, đâu là điểm của giáo sư.

Ta sẽ giải bài toán này như sau:
- Trước hết, ta khai báo một số kiểu dữ liệu cần thiết:
    ```cpp!
    struct point {long long x, y, z, v, i;};
    // v = 1 là điểm của học sinh
    // v = 0 là điểm yêu cầu của giáo sư

    struct cmp {
        bool operator() (point a, point b) {
            if (a.x != b.x) return a.x > b.x;
            return a.v > b.v;
            // Đây là thứ cần lưu ý đã được nói ở phía trên, 
            // việc ta sort ưu tiên theo v để đảm bảo rằng khi 
            // xét đến một giáo sư thì ta đã xét hết tất cả những điểm
            // của học sinh để tránh sót những điểm thỏa mà chưa được 
            // xét tới do phép so sánh được sử dụng trong bài là <=
        }
    };
    ```
        
- Do $0 \leq S_i, T_i, A_j, B_j, C_j \leq 10^9$, ta sẽ thực hiện nén số để dễ dàng sử dụng Fenwick Tree hơn:
    ```cpp!
    vector<long long> sortX, sortY, sortZ;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a,b,a+b,1,i});
        sortX.push_back(a); sortY.push_back(b); sortZ.push_back(a+b);
    }

    for (int i = n; i < n+mm; i++) {
        long long a, b, c; cin >> a >> b >> c;
        v.push_back({a,b,c,0,i});
        sortX.push_back(a); sortY.push_back(b); sortZ.push_back(c);
    }

    sort(sortX.begin(),sortX.end());
    sort(sortY.begin(),sortY.end());
    sort(sortZ.begin(),sortZ.end());

    for (point& i : v) {
        i.x = lower_bound(sortX.begin(),sortX.end(),i.x)-sortX.begin()+1;
        i.y = lower_bound(sortY.begin(),sortY.end(),i.y)-sortY.begin()+1;
        i.z = lower_bound(sortZ.begin(),sortZ.end(),i.z)-sortZ.begin()+1;
    }
    ```

- Cuối cùng ta thực hiện CDQ tương tự như bài trên:
    ```cpp!
    // fenwick tree duoc su dung trong bai la fenwick tree nguoc, 
    // ham get lay tong tu (u->mxn)
    vector<point> v;
    long long n, mm, ans[mxn];

    void cdq(int l, int r) {
        if (l+1 == r) return;
        
        int m = (r+l)>>1;
        
        cdq(l,m); cdq(m,r);
        
        int lptr = l, rptr = m;
        vector<pair<int, int>> record; 
        vector<point> tmp;
        
        while (lptr < m && rptr < r) {
            if (v[lptr].y >= v[rptr].y) {
                bit.upd(v[lptr].z,v[lptr].v); 
                record.push_back({v[lptr].z,v[lptr].v}); 
                tmp.push_back(v[lptr++]);
            }
            else {
                ans[v[rptr].i] += bit.get(v[rptr].z);
                tmp.push_back(v[rptr++]);
            }
        }
        
        while (lptr < m) tmp.push_back(v[lptr++]);
        
        while (rptr < r) {
            ans[v[rptr].i] += bit.get(v[rptr].z); 
            tmp.push_back(v[rptr++]);
        }
        
        for (int i = l; i < r; i++) v[i] = tmp[i-l];
        
        for (pair<int, int> i : record) bit.upd(i.fi,-i.se);
        
        record.clear(); tmp.clear();
    }
    ```
- Độ phức tạp: $O((N+Q) \log^2{(N+Q)})$.

Bài toán đặc biệt ở việc sắp xếp sai thứ tự ưu tiên của các điểm sẽ gây lỗi rất khó debug.

### [Codeforces 293E - Close Vertices](https://codeforces.com/problemset/problem/293/E)
#### Đề Bài
Cho cây $N$ đỉnh, các cạnh của cây có trọng số, đếm số đường đi từ $u$ đến $v$ $(u < v)$ sao cho độ dài đường đi từ $u$ đến $v$ $\leq l$, tổng trọng số trên đường đi $\leq w$.

Giới hạn: $1 \leq n \leq 10^5, 1 \leq l \leq n, 0 \leq w \leq 10^9$.
#### Lời Giải
Bài toán này có sử dụng thuật toán [Centroid Decomposition](https://wiki.vnoi.info/algo/graph-theory/centroid-decomposition.md), khuyến khích độc giả đọc trước khi tiếp tục bài viết.

Nếu biết về thuật toán Centroid Decomposition, ta dễ dàng nhận thấy rằng $2/3$ chiều mà ta cần xét sẽ lần lượt là độ dài từ $u$ đến centroid và tổng trọng số từ $u$ đến centroid. Vậy chiều thứ $3$ của bài toán này là gì?

Khi xét một centroid (trọng tâm), ta cần đảm bảo rằng các đường đi sẽ đi qua centroid này. Lúc này với mỗi điểm, ta cần xem xem điểm đó có lựa chọn các điểm mà không xuất hiện cùng subtree (cây con) với nó không (root (gốc) là centroid đang xét). 

Lúc này, ta thấy chiều còn lại chính là chiều thời gian - thời điểm/thứ tự của root của subtree mà điểm được thêm vào.

:::info
Với một số bài toán, việc thêm chiều là thời gian cũng khá dễ gặp. Khi gặp một bài toán mà cảm giác sẽ dùng đến CDQ và cần sắp xếp theo thứ tự nào đó, ta thường sẽ chuyển về bài toán CDQ thông thường với chiều thời gian.
:::

<details>
<summary>Code tham khảo</summary>
    
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
const int mxn = 1e5+7;

int n, l, w, l_i[mxn]; 
long long w_i[mxn];
vector<vector<pair<int,int>>> g(mxn);

int sz[mxn];
bool del[mxn];

// template tìm centroid và kích thước subtree
    
void dfs_sz(int u, int v) {} // kích thước
    
int dfs_ctr(int u, int v, int szx) {} // tìm centroid

// điểm và sort dùng trong CDQ
struct point {
    int x, y, z, v, i; 
    
    point() {x = -mod;}
    
    point(int xx, long long yy, int zz, int vv, int ii) {
        x = xx; y = yy; z = zz; v = vv; i = ii;
    }
};
    
struct cmp {
    bool operator() (point a, point b) {
        if (a.x != b.x) return a.x < b.x;
        return a.v > b.v;
    }
};

// template BIT / Fenwick Tree
int bit[mxn];
long long ans[2];
    
void upd(int u, int v) {
    while (u < mxn) {
        bit[u] += v; 
        u += (u&(-u));
    }
}
                   
int get(int u) {
    int sum = 0; 
                   
    while (u) {
        sum += bit[u]; 
        u -= (u&(-u));
    } 
                   
    return sum;
}

// template CDQ
vector<point> v;
    
void cdq(int l_l, int r) {
    if (l_l == r) return;
    
    int m = (r+l_l)>>1; int a = l_l, b = m+1;
    
    cdq(l_l,m); cdq(m+1,r);
    
    vector<point> tmp; vector<pair<int,int>> revert;
    
    while (a <= m && b <= r) {
        if (v[a].y <= v[b].y) {
            if (v[a].v) {
                upd(v[a].z,v[a].v); 
                revert.push_back({v[a].z,v[a].v}); 
            }
            tmp.push_back(v[a++]);
        }
        else {
            if (v[b].i) ans[v[b].i] += get(v[b].z-1); 
            tmp.push_back(v[b++]);
        }
    }
                            
    while (a <= m) tmp.push_back(v[a++]);
    
    while (b <= r) {
        if (v[b].i) ans[v[b].i] += get(v[b].z-1); 
        tmp.push_back(v[b++]);
    }
                 
    for (int i = l_l; i <= r; i++) v[i] = tmp[i-l_l];
    
    for (pair<int,int> i : revert) upd(i.fi,-i.se);
}

// hàm dfs để tính độ dài và tổng trọng số từ gốc đến 1 đỉnh
void dfs_l_w(int u, int vv) {
    for (pair<int,int> i : g[u]) {
        if (i.fi != vv && !del[i.fi]) {
            l_i[i.fi] = l_i[u]+1;
            w_i[i.fi] = w_i[u]+i.se;
    
            dfs_l_w(i.fi,u);
        }
    }
}

// hàm thêm 1 subtree khi Centroid Decomposition
void add(int u, int vv, int time) {
    if (l_i[u] <= l && w_i[u] <= w) {
        ans[1]++; // thêm điểm vào CDQ
        v.push_back({l_i[u],w_i[u],time,1,0}); // điểm này để các điểm khác đếm
        v.push_back({l-l_i[u],w-w_i[u],time,0,1}); // điểm này dùng để đếm các điểm khác
    }
    for (pair<int,int> i : g[u]) {
        if (i.fi != vv && !del[i.fi]) {
		    add(i.fi,u,time);
	    }
    }
}

// hàm cập nhật đáp án khi Centroid Decomposition
void upd(int u) {
    l_i[u] = w_i[u] = 0; 
    
    dfs_l_w(u,u); 
    
    v.clear(); v = {point()};
    
    int cnt = 2;
    // for qua các subtree có cạnh nối trực tiếp với centroid đang xét
    for (pair<int,int> i : g[u]) {
        if (!del[i.fi]) {
            add(i.fi,u,cnt);
            cnt++;
        }
    }
    
    if (v.size() == 1) return;
    
    sort(v.begin(),v.end(),cmp()); // sort theo 1 chiều để thực hiện CDQ
    
    cdq(1,(int)v.size()-1);
}

// hàm thực hiện Centroid Decomposition
void solve(int u) {
    dfs_sz(u,u); 
    
    int n_root = dfs_ctr(u,u,sz[u]);
    
    upd(n_root); 
    
    del[n_root] = 1;
    
    for (pair<int,int> i : g[n_root]) {
        if (!del[i.fi]) solve(i.fi);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> l >> w;
    
    for (int i = 2; i <= n; i++) {
        int a, b; 
	    cin >> a >> b;
        g[a].push_back({i,b}); 
        g[i].push_back({a,b});
    }
    
    solve(1);
    
    cout << ans[1];
}
```

</details>
    
Độ phức tạp: $O(N \log^3{N})$.
    
## CDQ Convolution - Online FFT
    
### Bài toán nền tảng
    
Ta cần tính dãy $c_0,c_1,c_2,...,c_n$ sao cho $c_k = \sum_{i+j=k-1}{a_i b_j}$ nhưng ta sẽ chỉ biết được $a_k$ và $b_k$ sau khi ta tính được $c_k$.
    
Ta có thể viết bài toán này lại thành $C(x) = xA(x)B(x)$ với hệ số bậc $k$ của $A(x)$ và $B(x)$ sẽ được biết sau khi ta tính xong hệ số bậc $k$ của $C(x)$.
    
### Lời giải
    
Để tính $c_k$ với $k \in [l, r)$ và ta đã biết giá trị của $c_{k'}, a_i, b_j$ với $i, j, k \in [l, m)$, ta cần tính sự đóng góp của cặp $(i, j)$ thỏa mãn:

- $m > i, j$: đảm bảo cả hai đều đã được tính ở nửa đầu tiên
- Ít nhất $1$ trong $2$ của $i$ hoặc $j$ lớn hơn hoặc bằng $l$: đảm bảo ta không tính lặp lại.
             
Từ đây, ta có thể thấy với mỗi $a_i$, giá trị $j$ sẽ nằm trong khoảng $[0, min(m, r-l)]$.
Tương tự, với mỗi $b_i$, giá trị $i$ sẽ nằm trong khoảng $[0, min(l, r-l)]$.
             
Lúc này ta có thể áp dụng CDQ để tính toán.
             
### Bài toán ví dụ
             
#### [CSAcademy - Jetpack](https://csacademy.com/contest/archive/task/jetpack/)
             
##### Tóm tắt bài toán

Ta cần đi từ $(0, 0)$ đến $(n, 0)$. Ở mỗi bước, ta sẽ tăng chiều $x$ lên $1$ đơn vị, chiều $y$ sẽ thành $y+1$ (nếu ta sử dụng jetpack) hoặc $max(0, y-1)$ (nếu ta không sử dụng jetpack). Ngoài ra, ta sẽ chỉ có $y > 0$ trong tối đa $2k$ bước liên tục. Hỏi có bao nhiêu cách đi thỏa mãn.
    
##### Lời giải
    
Gọi $dp[i]$ là số cách di chuyển từ $(0, 0)$ đến $(i, 0)$. Nếu điểm hạ cánh trước đó là $i-j$, ta sẽ có $\text{catalan}[j/2-1]$ cách để đi từ $i-j$ đến $i$ và không hạ cánh ở giữa đường nếu $j$ chẵn, ngoài ra ta sẽ không có cách để đi từ $i-j$ đến $i$. Lúc này ta định nghĩa:
    
$$
\text{coef}[j] =
\begin{cases} 
\text{catalan}\left(\frac{j}{2} - 1\right), & 2 \leq j \leq 2k \text{ và } j \text{ chẵn}, \\
0, & j \text{ lẻ hoặc } j \notin [2, 2k].
\end{cases}
$$
    
và
    
$$
\text{sum}[i] = \text{dp}[0] + \cdots + \text{dp}[i].
$$
    
Ta có thể thấy lúc này ta có thể tính $dp[i]$ từ các giá trị $\text{sum}[i-j]$ và $\text{coef}[j]$ với $0 \leq j \leq i$.
    
$$
dp[i] = \sum_{j=0}^{i} \text{sum}[i - j] \cdot \text{coef}[j].
$$

Gọi $D(x)$, $C(x)$, $S(x)$ lần lượt là hàm sinh cho $dp$, $\text{coef}$ và $\text{sum}$. Khi này ta có thể viết lại biểu thức trên thành:
    
$$
D(x) = S(x) C(x) + 1.
$$

Do $C(x)$ chia hết cho $x$, lúc này bài toán có thể chuyển về:
    
$$
D(x) - 1 = x S(x) P(x).
$$

Vậy ta đã có thể áp dụng được CDQ Convolution để hoàn thành bài toán.
    
#### [Gennady Korotkevich Contest 5 - Bin](https://www.acmicpc.net/problem/18743)
    
##### Tóm tắt bài toán
    
Đếm số cây nhị phân đầy đủ với $n$ lá sao cho với mỗi đỉnh có $2$ con, số lá ở cây con bên trái không hơn số lá ở cây con bên phải quá $k$.
    
##### Lời giải
    
Gọi $T_n$ là số cây thỏa mãn có $n$ lá, ta dễ thấy rằng:
    
$$
T_n = \sum_{\substack{i+j=n \\ j \leq i+k}} T_i T_j.
$$

Với trường hợp cơ sở là $T_0 = 0$ và $T_1 = 1$, ta có thể viết lại thành:
    
$$
T_n = \sum_{\substack{i+j=n \\ i>j}} T_i T_j + \sum_{\substack{i+j=n \\ i\leq j\leq i+k}} T_i T_j.
$$

Lấy $T(x)$ là hàm sinh của $T_n$ và $D(x)$ là hàm sinh của $D_n = T_n - \sum_{\substack{i+j=n \\ i\leq j\leq i+k}} T_i T_j$.
    
Khi này ta có liên hệ lặp lại là:
    
$$
D_n = \sum_{\substack{i+j=n \\ i>j}} T_i T_j.
$$

Viết lại theo hàm sinh:
    
$$
D(x) = \frac{T^2(x) - T(x^2)}{2}.
$$

tương đương với:
    
$$
2D(x) + T(x^2) = T^2(x).
$$

Ta có thể thấy $T(x)$ chia hết cho $x$ vì $T_0 = 0$ và biết được hệ số bậc $k$ của $2D(x) + T(x^2)$ khi ta có thể lấy hệ số bậc $k$ của $T(x)$ từ định nghĩa của $D_n$.
    
Qua đây, ta có thể áp dụng CDQ Convolution để hoàn thành bài toán.
    
### Tổng quát hóa bài toán
    
Ta có thể thấy các ví dụ đều có thể có phía phải của phương trình đều có thể biến đổi theo $1$ cách giống với tích chập. Tuy vậy, trên thực tế có rất nhiều hàm mà việc này gần như không thể thực hiện. Ví dụ các trường hợp sau trong điều kiện tương tự bài toán nền tảng (hệ số của $f(x)$ sẽ có sau khi có hệ số của $g(x)$):
    
$$ g(x) = x \cdot e^{f(x)}. $$

$$ g(x) = x \cdot \log \frac{1}{1 - f(x)}. $$

$$ g(x) = x \cdot \frac{1}{1 - f(x)}. $$

Các hàm trên là khá phổ thông trong các chuỗi lũy thừa hình thức (formal power series) (độc giả có thể đọc thêm tại [đây](https://codeforces.com/blog/entry/103979)). Ta có thể viết lại chúng theo dạng tích chập để có thể áp dụng CDQ. Tuy vậy, ta sẽ cần thực hiện một số bước khá "adhoc" cho từng hàm. Việc này là khá bất tiện nên ta cần tìm một hướng giải chung cho các bài toán.
    
Ta có: $g(x) = F(f(x))$ với $F(...)$ là các hàm có thể đạo hàm được (differentiable). 
    
Khi này ta có thể viết $g(x)$ lại theo cách giống với thuật toán Newton:
    
$$
g(x) = F(f_0) + F'(f_0)(f - f_0) + O((f - f_0)^2).
$$
    
Ta có thể thấy công thức này có thể dùng được với mọi $f_0$. Ta có thể thấy rằng với $f_0$ là $n$ hệ số đầu tiên của $f$, khi này $(f - f_0)^2$ có thể chia hết cho $x^{2n}$. Nói theo cách khác:

$$
g(x) \equiv F(f_0) + F'(f_0)(f - f_0) \pmod{x^{2n}}.
$$

Ở công thức này, ta vẫn không biết về $f(x)$, thế nhưng lúc này $f$ không còn là đối số của $F$ nữa. Do đó phía bên phải lúc này là một hàm tuyến tính của $f(x)$. Lúc này ta đã có thể chuyển thành $g(x) = A(x)f(x) + B(x)$ với $A(x) = F'(f_0), B(x) = F(f_0)-f_0F'(f_0)$ để có thể áp dụng CDQ Convolution.
            
   
## Các Bài Toán Ứng Dụng
- [BZOJ - 1176](https://vjudge.net/problem/BZOJ-1176/origin).
- [BZOJ - 3295](https://vjudge.net/problem/BZOJ-3295/origin).
- [Gym - 103870R](https://codeforces.com/gym/103870/problem/R).
- [VNOJ - icpc23_regional_i](https://vjudge.net/problem/VNOJ-icpc23_regional_i/origin).
- [Codeforces - 1093E](https://codeforces.com/contest/1093/problem/E).
- [MarisaOJ - 564](https://marisaoj.com/problem/564) (Bài toán này có cách sử dụng CDQ đặc biệt ở thứ tự sort).
- [Atcoder - abc213_H](https://atcoder.jp/contests/abc213/tasks/abc213_h) (CDQ Convolution).




