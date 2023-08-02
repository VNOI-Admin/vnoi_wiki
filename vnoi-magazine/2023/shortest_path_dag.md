# Shortest Path DAG và ứng dụng
**Người viết:** Nguyễn Đăng Quân - Đại học Công nghệ, Đại học Quốc gia Hà Nội

[[_TOC_]]

Trong một số bài toán liên quan đến đường đi ngắn nhất, tính chất của đồ thị khá khó nhận ra và cũng không dễ dàng để áp dụng. Hôm nay mình xin chia sẻ các bạn một kĩ thuật sử dụng phương pháp tính toán trên DAG (Directed Acyclic Graph) để giải một số bài toán về đường đi ngắn nhất.

# Bài toán mở đầu

## Đếm số đường đi trên DAG

Cho đồ thị có hướng không chu trình gồm $n$ đỉnh và $m$ cung. Với mỗi đỉnh, hãy đếm số đường đi từ $1$ tới đỉnh đó trên đồ thị.

### Thuật toán

Bài toán trên khá quen thuộc với đa số mọi người, cách giải là sử dụng qui hoạch động trên [Thứ tự topo](https://vnoi.info/wiki/algo/graph-theory/topological-sort.md):

- Đầu tiên, các bạn sắp xếp các đỉnh theo thứ tự Topo: $v_1,v_2,\dots,v_n$.
- Gọi $f(i)$ là số lượng đường đi từ $1$ tới $i$ trên đồ thị, ta có:
    - $f(1)=1$.
    - $f(v)=\sum{f(u)}$ với mọi cung $u\rightarrow v$ trên đồ thị.

Code mẫu:
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e5 + 5;

// adj[u]: Lưu các đỉnh v mà có cung u->v, nếu có nhiều cung u->v thì lưu đỉnh v nhiều lần

int n, m;
vector < int > adj[N];
int nTopo, v[N];
bool vis[N];
int f[N];

void dfs(int u) {
  vis[u] = true;

  for (auto i: adj[u])
    if (!vis[i])
      dfs(i);

  v[++nTopo] = u;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v);
  }

  /* Sắp xếp topo */
  for (int i = 1; i <= n; ++i)
    if (!vis[i])
      dfs(i);

  // Sau khi dfs xong, ta được thứ tự trong v là thứ tự ngược topo
  reverse(v + 1, v + nTopo + 1);

  /* Qui hoạch động trên DAG */
  for (int i = 1; i <= n; ++i)
    for (auto j: adj[v[i]])
      f[j] += f[v[i]];

  // In đáp án
  for (int i = 1; i <= n; ++i)
    cout << f[i] << " ";
}
```

Khi đó, độ phức tạp của thuật toán là $O(m+n)$, bởi thao tác sắp xếp Topo và thao tác tính hàm mục tiêu đều tốn thời gian $O(m+n)$.

## Bài toán đếm số đường đi ngắn nhất

Cho đồ thị vô hướng không chu trình $S=(V,E)$ gồm $n$ đỉnh và $m$ cạnh có trọng số **dương**. Với mỗi đỉnh, hãy đếm số đường đi ngắn nhất từ $1$ tới đỉnh đó trên đồ thị.

Link bài tập gốc: [https://vjudge.net/problem/Gym-406204J](https://vjudge.net/problem/Gym-406204J)

### Hướng tiếp cận

Trước tiên; để đếm được số đường đi ngắn nhất, ta cần phải nắm được cách tìm giá trị đường đi đó. Mình xin phép không nhắc lại các thuật toán tìm kiếm đường đi ngắn nhất; nếu bạn chưa biết hoặc biết nhưng đã quên thì có thể đọc lại trên [VNOI wiki](https://vnoi.info/wiki/algo/graph-theory/shortest-path.md). 

Trong bài toán này, ta sẽ gọi:
   - $d(i)$ là độ dài đường đi ngắn nhất từ đỉnh $1$ tới đỉnh $i$ trên đồ thị.
   - $f(i)$ là số đường đi ngắn nhất từ đỉnh $1$ tới đỉnh $i$.

Vậy tại sao phải tính được trước độ dài đường đi ngắn nhất? 

Định hướng lại đồ thị $S$ như sau:
- Giữ nguyên các đỉnh
- Với mỗi cạnh $u-v\in E$ 
    - Nếu $d(u)+w(u,v)=d(v)$, cạnh này sẽ biến thành cung $u\rightarrow v$.
    - Nếu $d(v)+w(u,v)=d(u)$, cạnh này sẽ biến thành cung $v\rightarrow v$.
    - Nếu hai điều kiện trên không thỏa mãn, cạnh này bị xóa bỏ khỏi đồ thị.

**Ví dụ:**
![Đồ thị ban đầu](../assets/shortest-path-dag/1-original-graph.png)
    
![Đồ thị đã thay đổi](../assets/shortest-path-dag/2-modifed-graph.png)

Khi đó, $f(i)$ chính là số đường đi từ $1$ đến $i$. Bài toán này trở thành bài _Đếm số đường đi trên DAG_.

Để hiểu rõ hơn, các bạn hãy theo dõi phần tiếp theo.

## Shortest Path DAG

Cho một đồ thị vô hướng $S=(V,E)$. Gọi $d(i,j)$ là **độ dài** đường đi ngắn nhất từ $i$ đến $j$ (Nếu không tồn tại đường đi thì $d(i,j)=\infty$). 

Ta dựng ra một đồ thị *có hướng* $S'_u=(V,E'_u)$ như sau:
- Mỗi đỉnh trong đồ thị $S$ sẽ ứng với một đỉnh trong $S'_u$.
- Mỗi cạnh $i-j\in E$ sẽ biến đổi như sau:
    - Nếu $d(u,i)+w(i,j)=d(u,j)$ thì dựng ra cung $i\rightarrow j$ trong $E'_u$.
    - Nếu $d(u,j)+w(i,j)=d(u,i)$ thì dựng ra cung $j\rightarrow i$ trong $E'_u$.

Khi đó, ta gọi đồ thị $S'_u$ là Shortest Path DAG ứng với đỉnh $u$ trên $S$. 

#### Tính chất

Đồ thị $S'_u$ có một số tính chất khá đặc biệt như sau:


> 1. Nếu tồn tại đường đi từ $u$ đến $v$ trên $S$ (Tức là $d(u,v)<\infty$) thì cũng tồn tại đường đi (có hướng) từ $u$ đến $v$ trên $S'_u$
    
Đây là một nhận xét hiển nhiên, bạn đọc có thể tự suy ngẫm về tính đúng.

> 2. Mọi đường đi trên $S'_u$ đều là đường đi ngắn nhất trên $S$.

*Chứng minh:* 
Gọi $f(i,j)$ là độ dài đường đi **dài nhất** từ $i$ đến $j$ trên $S'_u$ (Nếu không tồn tại thì $f(i,j)=\infty$). Điều kiện trên tương đương với một trong hai điều kiện sau thỏa mãn:
- $f(i,j)=\infty$ (Không tồn tại đường đi)
- $f(i,j)=d(i,j)$ (Nếu tồn tại đường đi thì đó phải là đường đi ngắn nhất)

Trước tiên, ta chứng minh đường đi xuất phát từ đỉnh $u$ đều là đường đi ngắn nhất.
Giả sử nhận xét trên là sai, tức là tồn tại một đỉnh $v$ và đường đi $$u\rightarrow x_1 \rightarrow x_2 \rightarrow\dots\rightarrow x_k$$ mà $w(u,x_1)+w(x_1,x_2) + \dots + w(x_k,v)>d(u,v)$.

Theo đó:

$$
\begin{array}{cl}
& [d(u,x_1)-d(u,u)]+[d(u,x_2)-d(u,x_1)] + \\
& \quad +\dots+ d(u,v)-d(u,x_k)]>d(u,v) \\
\Leftrightarrow & d(u,v)-d(u,u)>d(u,v) \\
\Leftrightarrow & 0>0
\end{array}
$$

$\Rightarrow$ Điều ta giả sử là sai, dẫn đến $f(u,i)=d(u,i) \forall i$

Nếu tồn tại đường đi từ $i$ đến $j$, ta biết $d(u,i)<\infty$; do đó tồn tại đường đi từ $u$ đến $i$ và $d(u,i)+f(i,j)=d(u,j)$.

Mặt khác, theo [bất đẳng thức tam giác](https://sharmaeklavya2.github.io/theoremdep/nodes/graph-theory/shortest-paths/triangle-inequality.html):
$$d(u,i)+d(i,j)\ge d(u,j)$$
hay $$d(u,i)+d(i,j) \ge d(u,i)+f(i,j)$$
suy ra $$d(i,j)\ge f(i,j)$$

Dấu bằng phải xảy ra, hay $f(i,j)=d(i,j)$.
Ta hoàn tất chứng minh.

> 3. $S'$ là đồ thị có hướng **không chu trình** (DAG)

*Chứng minh:*
Nếu đồ thị có chu trình chứa một đỉnh $v$ nào đó, ta có $d(v,v)>0$ do trọng số các cạnh là dương, dẫn đến mâu thuẫn.

> 4. Nếu tồn tại đường đi từ $i$ đến $j$ trên $S'_u$ thì **mọi đường đi ngắn nhất** từ $i$ đến $j$ sẽ đều xuất hiện trong $S'_u$.

*Chứng minh:*
Vì tồn tại một đường đi từ $i$ đến $j$ trên $S'_u$ nên theo tính chất 2: $d(u,i)+d(i,j)=d(u,i)+f(i,j)=d(u,j)$

Xét một **đường đi ngắn nhất** từ $i$ đến $j$ không xuất hiện trong đồ thị: $$i\rightarrow x_1 \rightarrow x_2 \rightarrow \dots \rightarrow x_k \rightarrow j$$

Theo bất đẳng thức tam giác:
$$
\begin{cases} 
d(u,x_1)-d(u,i)\le d(i,x_1)\\
d(u,x_2)-d(u,x_1)\le d(x_1, x_2)\\
\dots \\
d(u,j)-d(u,x_k)\le d(x_k,j) 
\end{cases}
$$
Cộng về với vế ta được:
$$d(u,j)-d(u,i)\le d(i,x_1)+d(x_1,x_2)+\dots+d(x_k,j)$$ $$\Leftrightarrow d(i,j)\le d(i,x_1)+d(x_1,x_2)+\dots+d(x_k,j)$$

Mặt khác ta có đường đi trên là đường đi ngắn nhất nên $d(i,j)=w(i,x_1)+w(x_1,x_2)+\dots+w(x_k,j)$
Theo đó:
$$
\begin{array}{l}
w(i,x_1)+w(x_1,x_2)+\dots+w(x_k,j) \\
\quad \le d(i,x_1)+d(x_1,x_2)+\dots+d(x_k,j)
\end{array}
$$

Dấu bằng phải xảy ra, dẫn đến dấu bằng của bất đẳng thức tam giác phải xảy ra:

$$
\begin{cases} 
d(u,i)+d(i,x_1)=d(u,x_1)\\
d(u,x_1)+d(x_1, x_2)=d(u,x_2)\\
\dots\\
d(u,x_k)+d(x_k,j)=d(u,j) 
\end{cases}
$$

Theo đó, đường đi trên phải nằm trong $S'_u$.
Tính chất số 4 chính là chìa khóa giúp ta giải quyết được *Bài toán đếm số đường đi ngắn nhất_.

### Cài đặt

Shortest Path DAG có ý nghĩa về mặt đưa ra nhận xét, các tính chất hơn thay vì được coi như một cấu trúc dữ liệu.

Vì vậy, thông thường mình sẽ không dựng lại cả một đồ thị mới mà sẽ tận dụng lại tài nguyên (Danh sách đỉnh, danh sách cạnh,...) của đồ thị cũ. Chỉ cần chú ý khi duyệt đồ thị, ta cần kiểm tra tính tồn tại của cung dựa trên điều kiện của DAG.

# Áp dụng

Sử dụng các tính chất trên, ta có thể giải quyết một số bài toán về đường đi ngắn nhất; sẽ khá khó để có thể giải quyết các bài toán sau đây với những công cụ cơ bản.

### VNUOI 2022: DELETE

Cho một đồ thị vô hướng gồm $n$ đỉnh và $m + k$ cạnh với trọng số duonwg; trong đó có $m$ cạnh loại 1 và $k$ cạnh loại 2. Các cạnh loại 2 chỉ nối giữa đỉnh $1$ và một đỉnh khác.

**Yêu cầu:** Hãy đếm số cách xóa một số cạnh loại 2 (Có thể không xóa cạnh nào) sao cho đường đi ngắn nhất từ đỉnh $1$ tới các đỉnh khác là **không đổi**. 

Bài toán có thể xem tại [https://oj.vnoi.info/problem/vnuoi22_delete](https://oj.vnoi.info/problem/vnuoi22_delete)

#### Nhận xét

Trong bài toán trên, điều kiện của các cạnh loại 2 sẽ giúp ta giải bài toán dễ hơn. Tuy nhiên, nếu không có điều kiện ấy thì bài toán vẫn giải được dựa vào _Shortest Path DAG_.

Xét Shortest Path DAG $S'_1$ của đồ thị, $S'_1$ sẽ thay đổi ứng với mỗi thay đổi (thêm/xóa cạnh) trên đồ thị ban đầu; ta có một số nhận xét:
- Nếu một cạnh không tạo ra một cung trong $S'_1$, việc xóa nó không ảnh hưởng đến dường đi ngắn nhất từ $1$ tới các đỉnh. Lượng đóng góp của cạnh này là $2$.
- Nếu vẫn tồn tại đường đi từ đỉnh $1$ đến đỉnh $i$ trên $S'_1$ thì độ dài đường đi ngắn nhất từ $1$ đến $i$ trên đồ thị ban đầu là không đổi. (Tính chất số 1 và Tính chất số 2).

$\Rightarrow$ Ta qui việc đếm cách xóa cạnh trên đồ thị ban đầu về đếm số cách xóa cung trên $S'_1$.

Mặt khác, do $S'_1$ là DAG (Tính chất số 3) $\Rightarrow$ Sau khi xóa cung, các đỉnh ban đầu có bậc vào khác 0 thì sau khi xóa cũng phải có bậc vào khác 0.
$\Rightarrow$ Ta đếm số cách xóa để các đỉnh có bậc vào khác 0 vẫn tiếp tục khác 0.

#### Thuật toán

Trước tiên, ta sẽ dựng đồ thị $S'_1$ của đồ thị đã cho. Xét đỉnh $i$, gọi:
- $deg(i)$ là bậc vào của đỉnh $i$
- $deg_1(i)$ là số cung "loại 1" vào đỉnh $i$
- $deg_2(i)$ là số cung "loại 2" vào đỉnh $i$

Lượng đóng góp của đỉnh $i$, tức là số cách xóa cung vào để bậc của nó tiếp tục bằng 0 hoặc tiếp tục khác 0 là:
- $1$ nếu $deg(i)=0$
- $2^{deg_2(i)}$ nếu $deg_1(i)>0$ vì $deg(i)=deg_1(i)+deg_2(i)\ge deg_1(i)>0$
- $2^{deg_2(i)}-1$ nếu $deg_1(i)=0$ vì $deg(i)=deg_2(i)$

Từ đó, đáp án là **tích** lượng đóng góp của các đỉnh và các cạnh loại 2 sinh ra cung trong $S'_1$.

**Code mẫu:**

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

constexpr int N = 2e5 + 5;
constexpr int M = 5e5;
constexpr ll mod = 998244353;
constexpr ll Inf = 1e17;

struct Edge {
  int u, v, w;
}
s1[M], s2[N];

int n, k, m;
int deg_1[N], deg_2[N];
ll d[N];
// adj[i] = đỉnh kề thông qua các cạnh loại 1
// nadj[i] = đỉnh kề thông qua các cạnh loại 2
vector < pair < int, int >> adj[N], nadj[N];

// Nhập dữ liệu
void Read() {
  cin >> n >> m >> k;
  for (int i = 1; i <= m; ++i) {
    cin >> s1[i].u >> s1[i].v >> s1[i].w;
    adj[s1[i].u].emplace_back(s1[i].v, i);
    adj[s1[i].v].emplace_back(s1[i].u, i);
  }

  for (int i = 1; i <= k; ++i) {
    s2[i].u = 1;
    cin >> s2[i].v >> s2[i].w;
    nadj[s2[i].u].emplace_back(s2[i].v, i);
    nadj[s2[i].v].emplace_back(s2[i].u, i);
  }
}

// Tính a ^ b % mod
ll Pow(ll a, ll b) {
  ll ans(1);

  for (; b; b >>= 1) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
  }

  return ans;
}

// Thuật toán tìm đường đi ngắn nhất
// Kết quả trả về mảng d[], d[i] = đường đi ngắn nhất từ x đến i 
void ShortestPath(int x) {
  // Bạn đọc vui lòng tự cài đặt lại thuật toán
}

// Thực hiện thuật toán
void Solve() {
  ll ans(1);
  ShortestPath(1);

  /* Dựng Shortest Path DAG */

  for (int i = 1; i <= m; ++i)
    if (d[s1[i].u] + s1[i].w == d[s1[i].v])
      ++deg_1[s1[i].v];
    else if (d[s1[i].v] + s1[i].w == d[s1[i].u])
    ++deg_1[s1[i].u] = 1;

  for (int i = 1; i <= k; ++i)
    if (d[s2[i].u] + s2[i].w == d[s2[i].v])
      ++deg_2[s2[i].v];
    else if (d[s2[i].v] + s2[i].w == d[s2[i].u])
    ++deg_2[s2[i].u];
  else
    ans = ans * 2 % mod; // Cạnh này không sinh cung

  /* Kết thúc dựng Shortest Path DAG */

  for (int i = 2; i <= n; ++i)
    if (deg_1[i] > 0)
      ans = ans * Pow(2, deg_2[i]) % mod;
    else if (deg_2[i] > 0)
    ans = ans * (Pow(2, deg_2[i]) - 1) % mod;

  cout << (ans + mod) % mod;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  Read();
  Solve();
}
```

Nhìn đoạn code trên, ta có thể dễ thấy độ phức tạp thời gian của thuật toán là $O(m+nlog_2{n}+ShortestPath)$. Thuật toán chạy nhanh hay chậm phụ thuộc phần nhiều vào cách cài đặt hàm ShortestPath.

### BIẾN ĐỘNG

Cho một đồ thị vô hướng **liên thông** gồm $n$ đỉnh và $m$ cạnh có trọng số dương. Gọi $d(u,v)$ là độ dài đường đi ngắn nhất giữa $u$ và $v$.
**Yêu cầu:** Với mỗi cạnh, hãy đếm số cặp đỉnh $(u,v)$ mà $d(u,v)$ tăng nếu ta xóa bỏ cạnh này.

Bài toán có thể xem tại [https://vjudge.net/problem/Gym-406204L](https://vjudge.net/problem/Gym-406204L)

#### Nhận xét

Bài toán yêu cầu với mỗi cạnh, đếm số cặp đỉnh $(u,v)$ mà $d(u,v)$ tăng lên khi xóa cạnh đó. Vậy cạnh này có điều kiện gì mà ảnh hưởng được đến đường đi ngắn nhất từ $u$ đến một đỉnh khác? Rõ ràng cạnh này phải thuộc một đường đi ngắn nhất xuất phát từ đỉnh $u$!

Ta dựng ra Shortest Path DAG $S'_u$; gọi $cnt(i,j)$ là số đường đỉ từ đỉnh $i$ đến đỉnh $j$. 
Nếu xóa cung $i\rightarrow j$ làm $d(u,v)$ tăng thì mọi đường đi từ $u$ đến $v$ phải thông qua cung này, tức là: $$cnt(u,i)\times cnt(j,v)=cnt(u,v)_{(*)}$$

Từ nhận xét ở bài _DELETE_ ta có thể xóa bỏ các cung sao cho mỗi đỉnh trên $S'_u$ có bậc tối đa là 1 và đường đi ngắn nhất từ $u$ đến các đỉnh là không đổi. 

$\Rightarrow$ Các "ứng cử viên" là các cung được giữ lại. Có thể chứng minh số cung của $S'_u$ khi ấy không quá $n-1$.

#### Thuật toán

Ta dựng ra các Shortest Path DAG $S'_1,S'_2,\dots,S'_n$. Trên $S'_u$:
- Ta duyệt qua các "ứng cử viên" mà trong phần nhận xét đã nói
- Với mỗi ứng cử viên, ta lại duyệt các đỉnh $v$ nhằm đếm số lượng đường đi $d(u,v)$ bị tăng nếu xóa "ứng cử viên" đó (Dựa vào điều kiện $(*)$)

**Chú ý:** 
- Theo tính chất 4, $cnt(i,j)$ chính là số đường đi ngắn nhất từ $i$ đến $j$ trên đồ thị ban đầu $\Rightarrow$ Ta có thể tính trước đường đi ngắn nhất giữa mọi cặp đỉnh bằng cách thực hiện $n$ lần thuật toán Dijkstra cổ điển (Thuật toán Dijkstra với độ phức tạp $O(n^2+m)$)
- $cnt(i,j)$ có thể rất lớn, nên bạn hãy lưu số này trong modulo một số nào đó (Hoặc có thể trong hai modulo); khi so sánh ta sử dụng đồng dư thay vì bằng nhau hoàn toàn.

Vì số lượng ứng cử viên của mỗi DAG là $n-1$ nên độ phức tạp thời gian khi ấy là $O(n^2\times(n-1))+O(n\times(n^2+m))=O(n^3+nm)$ là chi phí dựng $n$ DAG và chi phí duyệt.

**Code mẫu:**

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int N = 5e2 + 5;
constexpr ll Inf = 1e17;
// Mình tính cnt(i,j) trong hai modulo nguyên tố là 1e9+7 và 998244353
constexpr int mod[2] = {
  1000000007,
  998244353
};

inline void Add(int & x,
  const int & y,
    const int & mod) { // Chỉ là template cộng mod mà thôi
  x += y;
  if (x >= mod)
    x -= mod;
}

int n, m;

struct Edge {
  int u, v, w;
}
e[N * N];
int ans[N * N];

vector < pair < int, int >> adj[N];
vector < int > candidate;

ll d[N][N];
int cnt[N][N][2];
int mark, check[N];

// Thuật toán Dijkstra cổ điển
void Dijkstra(int x, ll d[N]) {
  ++mark;
  fill_n(d, N, Inf);
  d[x] = 0;
  cnt[x][x][0] = cnt[x][x][1] = 1;

  for (int i = 1; i <= n; ++i) {
    pair < ll, int > ans = {
      Inf,
      0
    };

    for (int j = 1; j <= n; ++j) // Thay vì dùng Hàng đợi ưu tiên, ta duyệt lại toàn bộ
      if (check[j] != mark && d[j] < ans.first)
        ans = {
          d[j],
          j
        };

    if (ans.first == Inf)
      break;

    check[ans.second] = mark;

    for (auto i: adj[ans.second])
      if (d[i.first] > ans.first + e[i.second].w) {
        d[i.first] = ans.first + e[i.second].w;
        cnt[x][i.first][0] = cnt[x][ans.second][0];
        cnt[x][i.first][1] = cnt[x][ans.second][1];
      }
    else if (d[i.first] == ans.first + e[i.second].w) {
      Add(cnt[x][i.first][0], cnt[x][ans.second][0], mod[0]);
      Add(cnt[x][i.first][1], cnt[x][ans.second][1], mod[1]);
    }
  }
}

// dfs để tìm tập "ứng cử viên"
void dfs(int v, int p, ll d[N]) {

  for (auto i: adj[v])
    if (i.first != p && d[i.first] == d[v] + e[i.second].w) {
      candidate.emplace_back(i.second);
      dfs(i.first, v, d);
    }
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> e[i].u >> e[i].v >> e[i].w;
    adj[e[i].u].emplace_back(e[i].v, i);
    adj[e[i].v].emplace_back(e[i].u, i);
  }

  // Thực hiện n lần Dijkstra và cho chạy thuật toán đếm đường đi ngắn nhất song song với Dijkstra
  for (int i = 1; i <= n; ++i)
    Dijkstra(i, d[i]);

  for (int i = 1; i <= n; ++i) {
    candidate.clear();

    dfs(i, -1, d[i]);

    for (auto j: candidate) {
      // Xác định chiều của cung
      int v = d[i][e[j].u] > d[i][e[j].v] ? e[j].u : e[j].v;
      int u = e[j].u + e[j].v - v;

      for (int t = 1; t <= n; ++t)
        if (d[i][u] + e[j].w + d[v][t] == d[i][t] && 1 ll * cnt[i][u][0] * cnt[v][t][0] % mod[0] == cnt[i][t][0] && 1 ll * cnt[i][u][1] * cnt[v][t][1] % mod[1] == cnt[i][t][1])
          ++ans[j];
    }
  }

  for (int i = 1; i <= m; ++i)
    cout << ans[i] / 2 << "\n"; // Vì mỗi cặp định được tính hai lần nên kết quả phải chia cho 2
}
```

# Luyện tập

 - [Codeforces 449B - Jzzhu and Cities](https://codeforces.com/problemset/problem/449/B)
 - [COCI 2008 - Najkraci](https://dmoj.ca/problem/coci08c3p6)
 (aka [PVHOI 2020 - CAULUONG](https://1drv.ms/b/s!Asql3vhziCu10CZ5FDu69rbPIDyM?e=6yie4Z))
 - [Gym - Đường ai nấy đi](https://vjudge.net/problem/Gym-406204K)