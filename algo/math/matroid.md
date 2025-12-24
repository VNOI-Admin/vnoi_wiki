---
title: Matroid
description: 
published: true
date: 2025-03-13T15:32:05.609Z
tags: 
editor: markdown
dateCreated: 2025-01-05T09:55:50.109Z
---

# Matroid
- **Tác giả:**
	- Đặng Đoàn Đức Trung - UT Austin
 
- **Reviewer:**
	- Trần Xuân Bách - University of Chicago

## Giới thiệu

Mục đích của bài viết này là để giới thiệu với các bạn đọc về matroid, vốn là một cấu trúc trong đại số trừu tượng nhưng lại được sử dụng ở một số bài nâng cao trong lập trình thi đấu. Bài viết này sẽ chỉ giới thiệu về định nghĩa của matroid, cùng với một số tính chất đặc biệt của matroid giúp việc xây dựng các thuật toán tham lam trên matroid trở nên dễ hơn rất nhiều so với các bài khác không có matroid.

*Bài viết này là phần 1 của chuỗi bài viết về các thuật toán liên quan tới matroid.*

### Lưu ý trước khi đọc

Bài viết này cần người đọc vững về các toán tử trên tập hợp, ví dụ như phép giao $\cap$, phép hợp $\cup$, phép hiệu $\setminus$, toán tử tập con $\subset$ và $\subseteq$, v.v.

Mình sẽ dùng kí hiệu $A + v = A \cup \{v\}$ cho việc thêm một phần tử vào tập, và $A - v = A \setminus \{v\}$ cho việc loại một phần tử khỏi tập.

## Một số ví dụ xây dựng

Với các bạn đã làm một số bài về xor basis, với một tập $S = \{s_1, s_2, \dots, s_n\}$ gồm các số tự nhiên, ta có một số định nghĩa sau đây. Với một tập con $T \subseteq S$ bất kì:
- $T$ được gọi là tập độc lập (independent set) nếu không có bất kì tập con không rỗng nào của $T$ mà tổng xor của tập con này bằng $0$.
- $T$ được gọi là cơ sở (basis) của $S$ nếu với mọi phần tử $s$ thuộc $S \setminus T$, $T + s$ không còn là tập độc lập. Nói cách khác, cơ sở có thể được coi như là một tập độc lập cực đại, khi thêm bất kì phần tử nào vào sẽ làm tập mất tính độc lập.

Ở đây, khái niệm độc lập được định nghĩa dựa trên việc tồn tại một tập con các phần tử có tổng xor bằng $0$. Tuy nhiên, ta không nhất thiết phải ép buộc vào một định nghĩa của độc lập như thế.

Xét ví dụ sau: cho đồ thị vô hướng liên thông $G$ gồm $n$ đỉnh và $m$ cạnh. Gọi tập tất cả các cạnh trên $G$ là tập $E$. Ta có thể dựng một định nghĩa về tập độc lập của $E$ như sau. Với một tập con $T \subseteq E$ bất kì:
- $T$ được gọi là tập độc lập nếu các cạnh trong $T$ không dựng nên bất kì chu trình nào.
- $T$ được gọi là cơ sở với định nghĩa y hệt như trường hợp trên: không tồn tại cạnh $e$ nào thuộc $E \setminus T$ sao cho $T + e$ là tập độc lập.

Ta dễ dàng nhận ra được là dưới định nghĩa tập độc lập như trên, nếu tập $T$ là cở sở của $E$, các cạnh trong $T$ dựng nên một cây khung của đồ thị $G$. Nói cách khác, các cây khung của $G$ dựng nên các cơ sở cho định nghĩa tập độc lập như trên. Đây là một cách định nghĩa tập độc lập trên tập các cạnh của đồ thị khá hữu ích.

|![Figure_1](/algo/math/matroid1.png) |
|:--:|
|*Một tập cạnh độc lập. Đây còn là một cơ sở.*|

|![Figure_2](/algo/math/matroid2.png)|
|:--:|
|*Một tập cạnh không độc lập.*|

Matroid là một cách tổng quát hóa định nghĩa độc lập cho bất kì tập hữu hạn $E$ nhằm giữ lại các tính chất tốt của các định nghĩa tập độc lập như xor basis hay cây khung. Mặc dù định nghĩa mình giới thiệu sau đây có thể nghe trừu tượng, định nghĩa này có thể bao quát rất nhiều cấu trúc quan trọng trong lập trình thi đấu.

## Định nghĩa, các ví dụ điển hình, và một số tính chất của matroid

Với một tập hữu hạn $E$ (tập này còn được gọi là ground set), giả sử ta định nghĩa một tính chất độc lập trên $E$, và ta thu được $\mathcal{I}$ là tập hợp của các tập độc lập của $E$. Khi này $\mathcal{I}$ (hay nói đúng hơn là cặp $\mathcal{M} = (E, \mathcal{I})$) là một matroid khi:
1. Tập rỗng là tập độc lập: $\emptyset \in \mathcal{I}$.
2. Nếu tập con $U$ là tập độc lập thì tập con $V$ của $U$ cũng là tập độc lập. Nói cách khác, nếu $U \subseteq E$ thỏa mãn $U \in \mathcal{I}$ thì $V \subseteq U$ cũng thỏa mãn $V \in \mathcal{I}$.
3. Nếu tập độc lập $U$ có nhiều phần tử hơn tập độc lập $V$, ta có thể tìm phần tử thuộc $U$ mà không thuộc $V$ mà có thể thêm vào $V$ và vẫn làm cho $V$ độc lập. Nói cách khác, nếu $U, V \in \mathcal{I}$ và $|U| > |V|$, tồn tại $x \in U \setminus V$ sao cho $V + x \in \mathcal{I}$.

Để làm định nghĩa tường minh hơn, ta quay lại về ví dụ của tập độc lập trên các cạnh của đồ thị $G$ như trên.
- Định nghĩa tập $E$ là tập các cạnh trên $G$.
- Định nghĩa tập $\mathcal{I}$ là tập của tập con các cạnh thuộc $E$ sao cho không tồn tại chu trình trong tập con các cạnh được chọn. Nói cách khác, một tập con các cạnh là tập độc lập nếu các cạnh này không tạo ra chu trình.

Ta có thể chứng minh được rằng $(E, \mathcal{I})$ là một matroid như sau:
- Rõ ràng tập rỗng là tập độc lập: nếu không có cạnh nào thì không có chu trình.
- Nếu một tập $E' \subseteq E$ là tập độc lập thì các tập con của $E'$ cũng là tập độc lập, vì nếu $E'$ không chứa chu trình nào thì tập con của $E'$ cũng vậy.
- Nếu tập cạnh $X$ và $Y$ là hai tập độc lập (không chứa chu trình), và nếu $|X| > |Y|$, ta có thể tìm được cạnh trong $X$ và đặt vào $Y$ sao cho $Y$ vẫn không có chu trình. Mình xin được dành phần này cho bạn đọc tự chứng minh.

### Một số matroid điển hình

Một số matroid điển hình bao gồm:
- **Matroid đồ thị (graphic matroid).** Cho một đồ thị $G$ vô hướng. Định nghĩa tập $E$ là tập cạnh của $G$, và một tập con của $E$ là tập độc lập nếu cạnh trong tập con này không tạo thành chu trình. Đây là matroid ta vừa nêu ở ví dụ làm rõ trên.
- **Matroid đồng nhất (uniform matroid).** Cho một tập $E$ gồm $n$ phần tử hữu hạn bất kì, và một số nguyên không âm $k \le n$. Nếu ta định nghĩa tập con của $E$ là tập độc lập nếu tập con này chứa không quá $k$ phần tử, thì đây là matroid đồng nhất hạng $k$.
- **Matroid đa sắc (colorful matroid).** Cho một tập $E$ gồm $n$ phần tử, mỗi phần tử $i$ có một màu $c_i$. Nếu ta định nghĩa tập con của $E$ là tập độc lập nếu như không có màu nào được lặp lại trong tập con, thì đây là matroid đa sắc.
- **Matroid tuyến tính (linear/vector matroid).** Cho một tập $E$ gồm $n$ véctơ trên một trường đại số bất kì. Với định nghĩa tập độc lập là các tập con của $E$ độc lập trên trường đại số đã cho, thì ta thu được matroid tuyến tính. Xor basis là điển hình của matroid tuyến tính, với trường đại số ở đây là $\mathbb{F}_2$.
- **Matroid đoạn hoành (transversal matroid).** Cho đồ thị hai phía $G$, với tập $E$ là tập các đỉnh ở phía trái đồ thị. Ta định nghĩa tập con các đỉnh của $E$ là tập độc lập nếu tồn tại một cách ghép tất cả các đỉnh của tập con này với các đỉnh ở phía phải đồ thị. Dưới định nghĩa này, ta thu được matroid đoạn hoành.

### Một số tính chất của matroid
Với tập con $U \subseteq E$, ta định nghĩa hạng của $U$ ($\newcommand{\rank}{\operatorname{rank}} \rank(U)$) là kích cỡ tập con độc lập to nhất của $U$, thì ta thu được một số tính chất sau về hạng của $U$:
- Hạng của $U$ không quá kích cỡ của $U$: $\rank(U) \le |U|$.
- Nếu $U$ là tập độc lập, thì hạng của $U$ chính bằng kích cỡ của $U$: $U \in \mathcal{I} \Leftrightarrow \rank(U) = |U|$.
- Hàm $\rank$ thỏa mãn tính chất môđun thứ (submodular): với $U, V \subseteq E$, ta có $\rank(U) + \rank(V) \ge \rank(U \cup V) + \rank(U \cap V)$.

Ta có thể định nghĩa thêm hạng $r$ của toàn bộ matroid là hạng của toàn bộ tập $E$ ($r = \rank(E)$), và cơ sở là các tập độc lập tối đa của matroid (ta không thể thêm phần tử nào khác vào mà vẫn giữ tập được độc lập), thì ta có tính chất sau:
- Cơ sở của matroid là các tập độc lập $U$ mà $|U| = \rank(U) = r$.
- Với hai cơ sở khác nhau $U$ và $V$, và với mọi $u \in U \setminus V$, ta có thể tìm được $v \in V \setminus U$ sao cho $U - u + v$ vẫn là một cơ sở. Đây được gọi là tính chất trao đổi cơ sở (basis exchange property) của một matroid.

## Thuật toán tham lam tìm cơ sở nhỏ nhất/lớn nhất

Xét bài toán sau:

> Cho matroid $\mathcal{M} = (E, \mathcal{I})$ định nghĩa trên tập $E$ có $n$ phần tử, sao cho mỗi phần tử $e$ trong tập $E$ có một trọng số $w_e$. Hãy tìm cơ sở của matroid có tổng trọng số lớn nhất/nhỏ nhất.

Không mất tính tổng quát, ta sẽ giải bài toán tìm cơ sở lớn nhất. Ta có thuật toán tham lam sau để tìm cơ sở lớn nhất của matroid.
1. Sắp xếp các phần tử của $E$ theo trọng số giảm dần.
2. Bắt đầu bằng tập $S = \emptyset$.
3. Ta lặp qua các phần tử của $E$ sau khi đã sắp xếp. Với phần tử $e$ hiện tại, nếu $S + e$ vẫn còn là tập độc lập, ta thêm $e$ vào $S$ (gán $S := S + e$.)
4. Sau khi lặp, ta trả lại $S$.

Ta có thể chứng minh được thuật toán này trả về cơ sở lớn nhất của matroid. Ngoài ra, giả sử ta được cho một hàm kiểm tra tính độc lập: với tập độc lập $S$ và phần tử $e$ bất kì, ta có thể kiểm tra nếu $S + e$ là tập độc lập trong độ phức tạp $f(\mathcal{M})$, thì thấy rằng độ phức tạp của thuật toán trên là $O(n \log n + n f(\mathcal{M}))$.

:::spoiler Chứng minh thuật toán
Giả sử thuật toán trả về cơ sở $A = \{a_1, a_2, \dots, a_r\}$. Xét bất kì cơ sở nào khác $B = \{b_1, b_2, \dots, b_r\}$, và giả sử là ta đã sắp xếp $A$ và $B$ theo thứ tự trọng số giảm dần, tức là $w_{a_1} \ge w_{a_2} \ge \dots \ge w_{a_r}$ và $w_{b_1} \ge w_{b_2} \ge \dots \ge w_{b_r}$.

Với mọi $k$ từ $1$ tới $r$, xét $A' = \{a_1, \dots, a_{k - 1}\}$ và $B' = \{b_1, \dots, b_k\}$. Vì $A$ và $B$ là tập độc lập, ta có $A'$ và $B'$ cũng là tập độc lập (tiên đề 2 của matroid). Ngoài ra, vì $|A'| = k - 1 < k = |B'|$, theo tiên đề 3 của matroid, tồn tại phần tử $b_j$ nào đó của $B'$ có thể cho vào $A'$ để $A'$ vẫn là tập độc lập (với $1 \le j \le k$). Tuy nhiên, theo thuật toán trên, $a_k$ là phần tử có trọng số lớn nhất có thể cho vào $A'$ để tập vẫn độc lập. Vậy nên ta có $w_{a_k} \ge w_{b_j} \ge w_{b_k}$. Vì ta chứng minh được điều này đúng với mọi $1 \le k \le r$, ta có $\sum_{i=1}^r w_{a_i} \ge \sum_{i=1}^r w_{b_i}$.
:::

Với bài toán tìm cơ sở nhỏ nhất, ta chỉ cần đổi thứ tự sắp xếp của $E$.

Cuối cùng, ta nhận thấy rằng với trường hợp đặc biệt của matroid đồ thị, thuật toán trên chính là thuật toán Kruskal để tìm cây khung lớn nhất, vì cây khung là cơ sở của matroid đồ thị.

### Cài đặt mẫu

Dưới đây là cách cài đặt tìm cơ sở lớn nhất, cùng với cách áp dụng vào bài toán tìm cây khung lớn nhất.

```cpp!
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par;
    DSU(int n) : par(n, -1) {}
    int comp(int u) { return par[u] < 0 ? u : par[u] = comp(par[u]); }
    bool connect(int u, int v) {
        if ((u = comp(u)) == (v = comp(v))) {
            return false;
        }
        if (par[u] > par[v]) {
            swap(u, v);
        }
        par[u] += par[v]; par[v] = u;
        return true;
    }
};

struct GraphMat {
    vector<pair<int, int>> edges;
    int n;
    DSU d;
    GraphMat(int n, vector<pair<int, int>> edges) : n(n), d(n), edges(edges) {}
    bool check(int x) {
        // kiểm tra nếu ta có thể thêm phần tử a vào tập S hiện tại
        auto [u, v] = edges[x];
        return d.comp(u) != d.comp(v);
    }
    void add(int x) {
        // thêm a vào tập S hiện tại
        auto [u, v] = edges[x];
        d.connect(u, v);
    }
    void clear() { d = DSU(n); }
};

template<class M>
vector<int> largestBasis(M mat, int n, vector<int> w) {
    vector<int> elem(n);
    iota(elem.begin(), elem.end(), 0);
    sort(elem.begin(), elem.end(), [&](int u, int v) { return w[u] > w[v]; });
    vector<int> S = {};
    for (int u : elem) {
        if (mat.check(u)) {
            S.push_back(u);
            mat.add(u);
        }
    }
    return S;
}

int main() {
    // tìm cây khung lớn nhất
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    vector<int> w(m);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v >> w[i]; u--; v--; // giả sử đồ thị cho đỉnh từ 1 tới n, ta biến thành từ 0 tới n - 1
        edges.push_back({u, v});
    }
    GraphMat mat(n, edges);
    vector<int> span = largestBasis(mat, m, w);
    for (auto x : span) {
        auto [u, v] = edges[x];
        cout << u + 1 << " " << v + 1 << "\n";
    }
}
```