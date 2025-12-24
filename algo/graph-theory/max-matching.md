---
title: Cặp ghép cực đại trên đồ thị hai phía
description: 
published: true
date: 2025-03-25T04:19:39.634Z
tags: 
editor: markdown
dateCreated: 2025-03-24T17:38:46.163Z
---

# Cặp ghép cực đại trên đồ thị hai phía

**Author**:
- Trần Quang Trường - Trường đại học Công nghệ Thông tin - ĐHQGHCM.

**Reviewers**:
- Nguyễn Quang Minh - Michigan State University, USA
- Lê Minh Hoàng - Đại học Khoa học Tự nhiên, ĐHQG-HCM
- Nguyễn Tấn Minh - THPT Chuyên Lê Hồng Phong, TPHCM

---
Cặp ghép cực đại trên đồ thị hai phía là một trong những bài toán thuộc lớp bài toán về đồ thị. Bài viết sau đây sẽ giới thiệu nội dung cơ bản của bài toán và các thuật toán liên quan.

## Một số kiến thức cần biết
Trước khi đọc bài viết này, bạn cần trang bị kiến thức về các chủ đề sau:
- [Kiến thức cơ bản của đồ thị.](/algo/graph-theory/graph)
- [Luồng cực đại trên mạng.](/algo/graph-theory/flow)

## Củng cố kiến thức
Để hiểu rõ các định nghĩa và lý thuyết được sử dụng trong bài viết, chúng ta sẽ cùng tìm hiểu một số vấn đề sau:

### Cặp ghép
Cho một độ thị vô hướng $G = (V, E)$ gồm $V$ đỉnh và $E$ cạnh. Một tập cạnh $M \subseteq E$ được gọi là **cặp ghép** nếu không có đỉnh $v \in V$ nào xuất hiện trong nhiều hơn một cạnh của $M$

Ngoài ra, ta gọi một cạnh $e \in E$ là một **cạnh tự do** nếu nó không xuất hiện trong tập cạnh $M$; một đỉnh $v \in V$ là một **đỉnh tự do** nếu không thuộc bất kỳ cạnh nào trong tập cạnh $M$.

Ví dụ, đồ thị sau mô tả một cặp ghép $M$ với các đỉnh và cạnh được tô màu xanh dương là cạnh và đỉnh tự do:

<center>
    <img src="/algo/graph/matching/matching-1.png" width="50%">
    <p><i>Hình 1: Cặp ghép trên một đồ thị vô hướng</i></p>
</center>


### Đường tăng luồng

Một đường tăng luồng là một đường đi bắt đầu và kết thúc bằng cạnh tự do, đồng thời hai đỉnh đầu mút của đường đi cũng là các đỉnh tự do.

Đường đi $\pi = v_1, v_2, \ldots, v_{2k + 2}$ là một **đường tăng luồng** tương ứng với cặp ghép $M$, ta có một số tính chất cơ bản sau:
- Mỗi cạnh thuộc đường đi $\pi$ thuộc tập cạnh $E$. $e_i = (v_i, v_{i + 1}) \in E$ $\forall 1 \le i \le 2k + 1$.
- $v_1, v_{2k + 2}$ là các đỉnh tự do và $v_2, v_3, \ldots v_{2k + 1}$ là các đỉnh được ghép.
- Các cạnh luân phiên giữa trong $M$ và ngoài $M$. $e_1, e_3, \ldots, e_{2k + 1} \not \in M$ và $e_2, e_4, \ldots, e_{2k} \in M$.
    $\Rightarrow$ Có $k$ cạnh được ghép và $k + 1$ cạnh tự do.
- $M \cap \pi = \{e_2, e_4, \ldots, e_{2k}\}$.

Ví dụ, với đồ thị và cặp ghép như trên, ta có đường đi $1 - 2 - 3 - 8 - 9 - 10$ là một đường tăng luồng:

<center>
    <img src="/algo/graph/matching/matching-2.png" width="50%">
    <p><i>Hình 2: Đường tăng luồng</i></p>
</center>


 **Bổ đề 1:** Nếu $M$ là một cặp ghép và $\pi$ là một đường tăng luồng tương ứng với $M$, thì:
 $$M' = M \oplus \pi = \{e \in E \mid e \in (M \setminus \pi) \cup (\pi \setminus M) \}$$
là một cặp ghép và $|M'| = |M| + 1$.

:::spoiler Chứng minh
**Chứng minh 1:** $M' = M \oplus \pi$ là một cặp ghép.
+ Vì $\pi$ là một đường tăng luồng, nó bắt đầu và kết thúc tại các đỉnh tự do, đồng thời luân phiên giữa các cạnh trong $M$ và ngoài $M$. Khi thực hiện $M' = M \oplus \pi$ tại mỗi đỉnh trong $\pi$ vẫn thuộc tối đa một cạnh trong $M'$, do đó đảm bảo rằng $M'$ là một cặp ghép hợp lệ. 

**Chứng minh 2:** $|M'| = |M| + 1$. 
+ Do $\pi$ có số cạnh lẻ và bắt đầu, kết thúc tại các đỉnh chưa ghép, số cạnh mới thêm vào ($\pi \setminus M$) luôn nhiều hơn số cạnh bị loại bỏ ($M \setminus \pi$) đúng một đơn vị. Do đó, $|M'| = |M| + 1$.
:::

Hình ảnh minh họa của cặp ghép $M'$ được tạo từ cặp ghép $M$ và đường tăng luồng $\pi$ như hình trên:

<center>
    <img src="/algo/graph/matching/matching-3.png" width="60%">
    <p><i>Hình 3: Cặp ghép sau khi thực hiện phép hiệu đối xứng với đường tăng luồng</i></p>
</center>



## [Bài toán](https://judge.yosupo.jp/problem/bipartitematching)
Cho một [đồ thị hai phía vô hướng](/algo/graph-theory/graph#%C4%91%E1%BB%93-th%E1%BB%8B-hai-ph%C3%ADa):
$$
G(X, Y, E), V = X \cup Y
$$
Tập đỉnh $X = x_1, x_2, \ldots, x_m$ là tập bên trái của đồ thị.
Tập đỉnh $Y = y_1, y_2, \ldots, y_n$ là tập bên phải của đồ thị.
Tập cạnh $E = \{e = (u, v) \mid u \in X, v \in Y\}$.

Hãy tìm cặp ghép cực đại của đồ thị $G$.

Ràng buộc: $1 \le X, Y \le 10^5, 1 \le E \le 2 \cdot 10^5$.


## Thuật toán luồng cực đại
Tất cả những bài toán có thể giải được bằng cặp ghép cực đại trên đồ thị hai phía thì đều có thể giải bằng luồng cực đại.

### Xây dựng đồ thị luồng
:::success
Đầu tiên, ta nối đỉnh nguồn $S$ tới các đỉnh thuộc tập $X$ với dung lượng là $1$.
Sau đó, với mỗi cạnh $(u, v) \in E$, ta nối đỉnh $u \in X$ tới đỉnh $v \in Y$ với dung lượng là $1$.
Cuối cùng, ta nối các đỉnh thuộc tập $Y$ tới đỉnh thu $T$ với dung lượng là $1$. 
:::

<!-- ![image](https://hackmd.io/_uploads/HJpvxAEKye.png) -->

<center>
    <img src="/algo/graph/matching/matching-4.png" width="50%">
    <p><i>Hình 4: Đồ thị luồng cho bài toán cặp ghép cực đại</i></p>
</center>


Hình minh hoạ đồ thị luồng của đồ thị có tập $E = \{
(x_1, y_1), (x_1, y_2), (x_1, y_3), (x_2, y_1), (x_3, y_1)\}$

Cặp ghép cực đại sẽ bằng luồng cực đại đi từ đỉnh nguồn $S$ tới đỉnh thu $T$.

### Cài đặt

Có rất nhiều thuật toán luồng cực đại nhưng chung quy đều phải có hai hàm `addEdge(u, v, cap)` (Thêm cạnh $(u, v)$ với dung lượng $cap$) và `calc(s, t)` (Trả về luồng cực đại đi từ $s$ tới $t$). 

Ta dễ dàng xây dựng đồ thị luồng với đoạn mã giả dưới đây:
```=
// Quy ước S = 0 là đỉnh source, T = M + N + 1 là đỉnh sink.
// Các đỉnh 1..M là các đỉnh thuộc tập X.
// Các đỉnh M+1..M+N là các đỉnh thuộc tập Y.

S = 0, T = M + N + 1
for i=1..M:
    addEdge(S, i, 1)
foreach (u, v) in E:
    addEdge(u, M + v, 1)
for i=1..N:
    addEdge(M + i, T, 1)
return calc(S, T)
```

### Độ phức tạp

Độ phức tạp của bài toán tuỳ thuộc vào thuật toán luồng cực đại đã sử dụng. Ví dụ:
+ Trong đồ thị có dạng mạng đơn vị, [thuật toán Dinic](/algo/graph-theory/flow#thu%E1%BA%ADt-to%C3%A1n-dinic) sẽ giải quyết bài toán với độ phức tạp $\mathcal{O}(E\sqrt{V})$. 
Để hiểu rõ tại sao có độ phức tạp này, độc giả có thể tìm hiểu thêm về [thuật toán Dinic trong mạng đơn vị](https://en.wikipedia.org/wiki/Dinic%27s_algorithm#Analysis).
+ Do giá trị của luồng cực đại $f$ không quá $O(V)$ nên với [thuật toán Edmonds-Karp](/algo/graph-theory/flow#ph%C6%B0%C6%A1ng-ph%C3%A1p-ford-fulkerson-thu%E1%BA%ADt-to%C3%A1n-edmonds-karp) ta đạt độ phức tạp thuật toán là $\mathcal{O}(Ef)$ hay $\mathcal{O}(EV)$

## Thuật toán Kuhn 

Dù các thuật toán luồng cực đại có thể đạt độ phức tạp tốt như thuật toán Dinic nhưng các thuật toán về luồng cực đại chung quy đều rất khó trong việc cài đặt. Với một hàm gọi đệ quy ngắn gọn cùng vài vòng lặp for đơn giản, thuật toán Kuhn giúp ta cải thiện thời gian cài đặt thuật toán.

### Thuật toán
Mô hình thuật toán Kuhn hoạt động như sau:

:::success
**Bước 1**: Tìm kiếm đường tăng luồng.
**Bước 2**: Cập nhật cặp ghép dựa vào đường tăng luồng tìm được.
**Bước 3**: Kết thúc thuật toán nếu không còn đường tăng luồng nào nữa. Ngược lại, quay lại bước $1$.
:::

#### Chứng minh tính đúng đắn của thuật toán

Vậy tại sao đồ thị đạt cực đại khi không tìm được thêm đường tăng luồng nào nữa? Câu trả lời nằm ở định lý Berge.

Định lý phát biểu: Cặp ghép $M$ đạt cực đại khi và chỉ khi đồ thị không còn chứa đường tăng luồng nào tương ứng với $M$.
:::spoiler  Chứng minh
**Chứng minh 1**: Nếu đồ thị tồn tại một đường tăng luồng $\pi$ tương ứng với cặp ghép $M$, thì cặp ghép $M$ không đạt cực đại.
+ Xét một đồ thị tồn tại một đường tăng luồng $\pi$ tương ứng với cặp ghép $M$.

    Theo **Bổ đề 1**, ta có $|M'| = |M|+ 1 \gt |M|$, với $M' = M \oplus \pi$.
    
+ Do đó, cặp ghép $M$ không phải là cặp ghép cực đại. Giả thiết được chứng minh.

**Chứng minh 2**: Nếu cặp ghép $M$ của đồ thị chưa đặt cực đại, thì đồ thị vẫn còn đường tăng luồng. 
+ Xét đồ thị có cặp ghép hiện tại $M$ chưa đạt cực đại và cặp ghép cực đại $M'$. 

    Xét đồ thị $H$ gồm tập cạnh $M \oplus M'$. Mỗi đỉnh của đồ thị $H$ có thể có tối đa $2$ cạnh chứa nó, gồm một cạnh trong $M$ và một cạnh trong $M'$. Do đó, mỗi thành phần liên thông của đồ thị sẽ có dạng một chu trình chẵn đi xen kẽ các cạnh trong $M$ và trong $M'$ hoặc sẽ có dạng một đường đi đơn xen kẽ các cạnh trong $M$ và trong $M'$.

    Vì $|M'| \gt |M|$ nên tồn tại ít nhất một thành phần liên thông $P$ có dạng đường đi của $H$ phải bắt đầu và kết thúc là các cạnh trong $M'$. Vì cạnh bắt đầu và cạnh kết thúc của $P$ nằm trong $M'$ nên hai cạnh này sẽ không nằm trong $M$. Nói cách khác, nó là những cạnh tự do. 
    
+ Do đó, đường đi $P$ trong đồ thị $H$ là một đường tăng luồng tương ứng với cặp ghép hiện tại $M$. Giả thiết được chứng minh.
:::

#### Thuật toán

Ý tưởng chính của thuật toán là duyệt qua **tất cả các đỉnh** thuộc một phía của đồ thị và thực hiện tìm kiếm đường tăng luồng bắt đầu từ những đỉnh đấy. Trong bài viết này, ta quy định việc tìm kiếm đường tăng luồng sẽ bắt đầu từ các đỉnh thuộc tập bên trái.

Vì chúng ta luôn cố gắng tìm đường tăng luồng tại từng đỉnh thuộc tập bên trái, nên sau khi tìm kiếm tại tất cả các đỉnh này thì đồ thị không còn bất cứ đường tăng luồng nào. Nói cách khác, số cặp ghép tìm được lúc này là cực đại.

<figure align="center">
    <img src="/algo/graph/matching/matching-gif.gif" width="70%">
    <figcaption>Minh hoạ quy trình thuật toán Kuhn</figcaption>
</figure>

Vậy làm sao để tìm kiếm đường tăng luồng? Ta sẽ dễ dàng tìm kiếm chúng bằng các thuật toán tìm kiếm theo chiều sâu (DFS) / tìm kiếm theo chiều rộng (BFS) (Trong bài viết này sẽ chỉ nói về cách tìm kiếm theo chiều sâu). 

Bắt đầu tìm kiếm đường tăng luồng từ đỉnh $u \in X$, ta sẽ duyệt qua các cạnh kề đỉnh $u$. Gọi cạnh này là $(u, v)$, ta có hai trường hợp của $v \in Y$:
- **Trường hợp 1**: $v$ là một đỉnh tự do. Ta tìm được đường tăng luồng chứa cạnh $(u, v)$ và kết thúc quá trình tìm kiếm đường tăng luồng. 
- **Trường hợp 2**: $v$ là đỉnh được ghép. Gọi $p \in X$ là đỉnh đã ghép với đỉnh $v$. Mục tiêu là cố gắng tìm đường tăng luồng đi qua các cạnh $(u, v), (v, p), \ldots$. Để làm điều đó, ta sẽ tiếp tục tìm kiếm đường tăng luồng bắt đầu từ đỉnh $p$. Lúc này, ta sẽ có hai trường hợp xảy ra: hoặc là tìm kiếm được đường tăng luồng đi từ $p$ và kết thúc quá trình tìm kiếm đường tăng luồng, hoặc là thông báo không tìm được đường tăng luồng nếu không tồn tại đường tăng luồng nào đi từ mọi $p$ thoả mãn.

Gọi $M$ là cặp ghép hiện tại và $\pi$ là đường tăng luồng tương ứng với $M$ tìm được. Ta cập nhật cặp ghép $M' = M \oplus \pi$ bằng cách:
+ Loại bỏ các cạnh trong $M$ thuộc đường tăng luồng khỏi cặp ghép.
+ Thêm các cạnh ngoài $M$ thuộc đường tăng luồng vào cặp ghép.


### Cài đặt

Ở đây, ta có một số mảng như `G`, `matchL`, `matchR`, `seen`:
- `G[u]` lưu tập các đỉnh kề cạnh với đỉnh $u \in X$.
- `matchL[u]` lưu đỉnh kề cạnh ghép với đỉnh $u \in X$, nếu không tồn tại, giá trị này bằng $-1$.
- `matchR[v]` lưu đỉnh kề cạnh ghép với đỉnh $v \in Y$, nếu không tồn tại, giá trị này bằng $-1$.
- `seen[u]` lưu lại "thời gian" cuối cùng thực hiện việc tìm kiếm tại đỉnh $u \in X$.

Hàm `kuhn(u)` là hàm tìm kiếm theo chiều sâu. Hàm trả về $\tt{True}$ nếu tìm được đường tăng luồng từ $u \in X$, và ngược lại.

Trong hàm `kuhn`, ta duyệt qua các đỉnh $v \in Y$ kề cạnh đỉnh $u$. Trong  hai trường hợp: hoặc là $v$ là đỉnh tự do, hoặc là $v$ là đỉnh được ghép nhưng có thể tìm được đường tăng luồng đi từ đỉnh đang ghép với $v$. Lúc này, ta tìm được đường tăng luồng đi từ $u$, và trước khi trả về $\tt{True}$ ta sẽ thêm cặp cạnh $(u, v)$ vào cặp ghép.

Biến `iteration` lưu "thời gian" hiện tại. Cụ thể, vì trước khi tìm kiếm đường tăng luồng tại đỉnh $u$, ta phải khởi tạo lại mảng đánh dấu lưu các đỉnh đã thăm trong lúc thực hiện hàm `kuhn` ở lần tìm kiếm đường tăng luồng tại đỉnh $u - 1$. Và để giảm độ phức tạp khởi tạo lại mảng đánh dấu này từ $\mathcal{O}(V)$ xuống $\mathcal{O}(1)$, ta sử dụng mảng `seen` và biến `iteration` với định nghĩa như đã nói ở trên. 

```cpp=
const int N = 100100;

vector<int> G[N];
int seen[N], iteration = 0;
int matchL[N], matchR[N];

// Tìm kiếm đường tăng luồng bắt đầu từ u
bool kuhn(int u) {

    // Nếu "thời gian" lần cuối thăm đỉnh u bằng với "thời gian" hiện tại.
    // Ta nói u đã được thăm trước đó và không tìm kiếm lần nữa.
    // Ngược lại, lưu lại "thời gian" cuối cùng thăm đỉnh u bằng "thời gian" hiện tại.
    // và thực hiện tìm kiếm tại u.
    if(seen[u] == iteration) return 0;
    seen[u] = iteration;
    
    for(int v : G[u]) {
        // Kiểm tra đỉnh v có phải là đỉnh tự do
        // hoặc có cách nối khác từ đỉnh đang ghép với v
        if(matchR[v] == -1 || kuhn(matchR[v])) {
            // Ghi nhận cặp ghép (u, v) và thông báo có cách ghép từ đỉnh u
            matchL[u] = v; matchR[v] = u;
            return 1;
        }
    }

    // Thông báo không tìm được cách ghép từ đỉnh u
    return 0;
}

int matching(int M, int N, vector<pair<int, int>> E) {
    
    // Trạng thái ban đầu chưa có cặp ghép
    fill(matchL + 1, matchL + M + 1, -1);
    fill(matchR + 1, matchR + N + 1, -1);
    
    // Xây dựng danh sách kề
    for(int i = 0; i < (int) E.size(); ++i) { 
        int u = E[i].first, v = E[i].second;
        G[u].push_back(v);
    }
    
    for(int u = 1; u <= M; ++u) {
        // Khởi tạo nhanh mảng đánh dấu
        ++iteration;
        // Với mỗi đỉnh ta sẽ tìm cặp ghép từ đỉnh u
        kuhn(u);
    }
    
    // Tính số cặp ghép lớn nhất
    int ans = 0;
    for(int u = 1; u <= M; ++u) {
        if(matchL[u] != -1) { ++ans; }
    }
    return ans;
}
```

### Cải tiến thuật toán

Thứ tự tập cạnh quyết định rất lớn tới việc ta có nhanh chóng tìm được đường tăng luồng hay không. Do đó có một trick tối ưu thuật toán Kuhn bằng heuristic thường được sử dụng, đó là dùng `random_shuffle` để thay đổi thứ tự của tập cạnh ban đầu:
```cpp
// Xây dựng danh sách kề
random_shuffle(E.begin(), E.end());
for(int i = 0; i < (int) E.size(); ++i) {
    int u = E[i].first, v = E[i].second;
    G[u].push_back(v);
}
```

Với cách tối ưu này, giúp thuật toán chạy đủ nhanh trong đa phần các trường hợp.

### Độ phức tạp

Thuật toán Kuhn sẽ thực hiện $V$ lần tìm kiếm theo chiều sâu, do đó độ phức tạp của thuật toán là $\mathcal{O}(E \cdot V)$.

## Thuật toán Hopcroft–Karp

Được cải tiến từ thuật toán Kuhn, thuật toán Hopcroft-Karp tối ưu độ phức tạp thuật toán lên đáng kể bằng việc giảm bớt số lần thực hiện tìm kiếm chiều sâu.

### Thuật toán

Mô hình thuật toán Hopcroft-Karp sẽ hoạt động như sau:
:::success
**Bước 1**: Tìm kiếm nhiều nhất số đường tăng luồng có đường đi ngắn nhất.
**Bước 2**: Cập nhật cặp ghép dựa vào các đường tăng luồng tìm được.
**Bước 3**: Kết thúc thuật toán nếu không còn đường tăng luồng nào nữa. Ngược lại, quay lại bước $1$.
:::

#### Thuật toán

Giả sử ta có đồ thị $G$, một cặp ghép $M$ và một tham số $k$, trong đó $k$ là một số lẻ. Giả sử đường tăng luồng ngắn nhất của $M$ trong $G$ có độ dài $k$. Ý tưởng chính của thuật toán là tìm kiếm nhiều nhất các đường tăng luồng có độ dài $k$ với $k = 1, 3, \ldots$. Để làm điều đó, ta sử dụng thuật toán **BFS đa nguồn**.

Vậy BFS đa nguồn là gì? BFS đa nguồn là một nhánh mở rộng từ thuật toán BFS. Ta sẽ bắt đầu từ nhiều đỉnh nguồn thay vì chỉ một đỉnh như BFS truyền thống. Cây thu được từ thuật toán là một đồ thị có hướng không chu trình (DAG) trong đó nếu biến đổi các cạnh của đồ thị thành vô hướng ta sẽ được một cây.

Cụ thể trong bài toán này, ta sử dụng thuật toán BFS đa nguồn để tìm kiếm khoảng cách ngắn nhất từ các đỉnh tự do thuộc tập bên trái của đồ thị tới mọi đỉnh của đồ thị.

Ta sẽ thực hiện thuật toán BFS đa nguồn trên đồ thị $H(X, Y, E')$. Trong đó, $E'$ là tập cạnh có hướng gồm hai loại:
+ Các cạnh có hướng $(u, v) \in E$, $u \in X, v \in Y$ mà cạnh $(u, v) \not \in M$.
+ Các cạnh có hướng $(v, u) \in E$, $u \in X, v \in Y$ mà cạnh $(u, v) \in M$.

<center>
    <img src="/algo/graph/matching/matching-5.png" width="40%">
    <p><i>Hình 5: Thực hiện BFS đa nguồn trên đồ thị hai phía</i></p>
</center>

Nếu sắp xếp lại các đỉnh của đồ thị, ta có thể thấy rõ hơn hình ảnh của một DAG như sau:

<center>
    <img src="/algo/graph/matching/matching-6.png" width="70%">
    <p><i>Hình 6: Đồ thị sau khi sắp xếp</i></p>
</center>


Cuối cùng, ta sẽ tìm kiếm các đường tăng luồng trên cây BFS đa nguồn xây dựng được giống thuật toán Kuhn.

#### Chứng minh các bổ đề của thuật toán 

**Bổ đề 2:** Nếu $\pi$ là đường tăng luồng ngắn nhất tương ứng với cặp ghép $M$ và $\pi'$ là đường tăng luồng bất kỳ tương ứng với $M' = M \oplus \pi$. Thì $|\pi'| \ge |\pi|$. Cụ thể hơn, ta sẽ có $|\pi'| \ge |\pi| + 2|\pi \cap \pi'|$.
<br>
<center>
    <img src="/algo/graph/matching/matching-7.jpg" width="80%">
    <p><i>Hình 7: Hai đường tăng luồng ngắn nhất tương ứng cặp ghép M và M'</i></p>
</center>


:::spoiler Chứng minh
Xét cặp ghép $N = M \oplus \pi \oplus \pi'$. Dễ thấy, $|N| = |M| + 2$ và $M \oplus N$ sẽ chứa hai đường tăng luồng không giao nhau gọi là $\delta_1$ và $\delta_2$ - Cả $\delta_1$ và $\delta_2$ đều là đường tăng luồng tương ứng với cặp ghép $M$. 
Dựa vào tính chất giao hoán, ta có:
$$M \oplus N = M \oplus (M \oplus \pi \oplus \pi') = \pi \oplus \pi'$$
Mặc khác, ta lại có:
$$|\pi \oplus \pi'| = |M \oplus N| \ge |\delta_1| + |\delta_2|$$
Mà bởi vì $\pi$ là đường tăng luồng có độ dài ngắn nhất tương ứng với $M$ nên $|\delta_1| \ge |\pi|$ và $|\delta_2| \ge |\pi|$. Chúng ta có thể kết luận được:
$$|\pi \oplus \pi'| \ge |\delta_1| + |\delta_2| \ge |\pi| + |\pi| = 2 |\pi|$$
Theo định nghĩa, ta có công thức $|\pi \oplus \pi'| = |\pi| + |\pi'| - 2|\pi \cap \pi'|$. Kết hợp với điều trên, ta được:
$$|\pi| + |\pi'| - 2|\pi \cap \pi'| \ge 2|\pi| \Rightarrow |\pi'| \ge |\pi| + 2|\pi \cap \pi'|$$ 
Bổ đề được chứng minh.
:::

Từ bổ đề 2, ta rút ra được hai hệ quả sau:
+ **Hệ quả 2.1**: Gọi $\pi_1, \pi_2, \ldots, \pi_t$ là các đường tăng luồng ngắn nhất theo thứ tự tìm được của mô hình thuật toán. Ta có $|\pi_1| \le |\pi_2| \le \ldots \le |\pi_t|$.
+ **Hệ quả 2.2**: Ở lần thứ $l$, khi tìm kiếm độ dài đường tăng luồng độ dài bằng $k$ với $k = 2 \cdot l + 1$, thì độ dài đường tăng luồng ngắn nhất là $k$.

    **Nhận xét 2.2.1**: Ở lần tìm kiếm độ dài đường tăng luồng độ dài bằng $\sqrt{V}$, thì độ dài đường tăng luồng ngắn nhất là $\sqrt{V}$.

**Bổ đề 3:** Với mọi $i, j$ mà $|\pi_i| = \ldots = |\pi_j|$, thì ta có $\pi_i$ và $\pi_j$ rời nhau.

:::spoiler Chứng minh
Ta giả sử rằng $|\pi_i| = |\pi_j|, i \lt j$ nhưng $\pi_i$ và $\pi_j$ giao nhau. Để tiện trong việc chứng minh, giả sử thêm rằng rằng $j - i$ là nhỏ nhất. Khi đó, với mọi $k$ sao cho $i \lt k \lt j$, ta có $\pi_k$ không có đỉnh chung với $\pi_i$ và $\pi_j$.

Xét $M_i$ là cặp ghép sau khi thêm thêm đường tăng luồng $\pi_i$. Lúc này, $\pi_j$ là một đường tăng luồng tương ứng với $M_i$. Vì $\pi_i$ và $\pi_j$ giao nhau nhưng không thể có cùng hai đỉnh ở đầu mút (vì đó là các đỉnh tự do), nên những đỉnh chung này là một số đỉnh ở khoảng giữa.

Gọi đỉnh $v$ là một đỉnh giao của $\pi_i$ và $\pi_j$. Vì đỉnh $v$ - một đỉnh trong $\pi_j$, sẽ nằm ở giữa đường đi trong $\pi_j$ nên $v$ sẽ có hai cạnh kề đỉnh $e_1, e_2$. Ngoài ra, đường tăng luồng $\pi_i$ có một cạnh kề đỉnh $v$ trong $M$, gọi cạnh này là $e$. 

Vì $M_i$ là một cặp ghép, nên mỗi đỉnh chỉ có thể xuất hiện tối đa trong một cạnh trong $M_i$. Để đảm bảo tính chất cặp ghép, sau khi thêm đường tăng luồng $\pi_j$ vào cặp ghép thì đỉnh $v$ chỉ có tối đa **một** cạnh kề đỉnh. Tuy nhiên, vì đỉnh $v$ trong $\pi_j$ có hai cạnh kề $e_1$ và $e_2$ nên cạnh $e$ kề $v$ trong $M$ phải là $e_1$ hoặc $e_2$. Nói cách khác, $\pi_i$ và $\pi_j$ sẽ có ít nhất một cạnh chung $e$ ($e = e_1$ hoặc $e = e_2$). Viết lại bằng công thức, ta có $|\pi_i \cap \pi_j| \ge 1$.

Từ bổ đề $2$, ta có công thức: 
$$
|\pi_j| \geq |\pi_i| + 2|\pi_i \cap \pi_j| > |\pi_i|.
$$

Điều này mâu thuẫn với giả thiết rằng $|\pi_i| = |\pi_j|$. Do đó, giả sử ban đầu rằng $\pi_i$ và $\pi_j$ có đỉnh chung là sai. Bổ đề được chứng minh.
:::

**Bổ đề 4**: $|M'| - |M| \le \frac{2|V|}{l + 1}$ với $M'$ là cặp ghép cực đại, và $M$ là cặp ghép hiện tại ở lần thực hiện tìm kiếm đường tăng luồng thứ $l$.

:::spoiler Chứng minh

Từ hệ quả 2.2, ta biết được độ dài ngắn nhất đường tăng luồng tìm kiếm được là $2 \cdot l + 1$. Do đó, số đỉnh tối thiểu để tìm kiếm được đường tăng luồng là $2 \cdot l + 2$.

Mặc khác, ta lại có tổng số lượng đỉnh của đồ thị là $|V|$, vì thế số đường tăng luồng còn lại cần tìm hay cũng chính là số cặp ghép còn lại bằng:
$$|M'| - |M| \le \frac{|V|}{2 \cdot l + 2} = \frac{2|V|}{l + 1}$$
:::

### Cài đặt

Để đơn giản hoá cài đặt thuật toán, ta sử dụng mảng `dist` với định nghĩa: 
+ `dist[u]` lưu lại khoảng cách ngắn nhất giữa đỉnh $u \in X$ tới các đỉnh tự do thuộc tập $X$.

Ta không cần quan tâm khoảng cách ngắn nhất giữa các đỉnh thuộc tập $v \in Y$ và các đỉnh tự do thuộc tập $X$ vì ta có thể đi trực tiếp từ đỉnh $u \in X$ tới đỉnh $p \in X$ qua hai cạnh $(u, v)$ và $(p, v)$.

```cpp=
const int N = 100100;

vector<int> G[N];
int seen[N], iteration = 0;
int dist[N], matchL[N], matchR[N];

// Tìm kiếm đường tăng luồng bắt đầu từ u
bool dfs(int u) {

    // Nếu đỉnh u đã được thăm trước đó, ta sẽ không thăm lại nữa
    if(seen[u] == iteration) return 0;
    seen[u] = iteration;

    for(int v : G[u])
        // Kiểm tra đỉnh v có phải là đỉnh tự do hay không
        if(matchR[v] == -1) { 
            matchL[u] = v; matchR[v] = u; 
            return 1; 
        }

    for(int v : G[u]) 
        // Kiểm tra đỉnh đang được ghép với v có đi được từ đỉnh u không
        // và có cách nối khác từ đỉnh đang ghép với v không
        if(dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) { 
            // Ghi nhận cặp ghép (u, v) và thông báo có cách ghép từ đỉnh u
            matchL[u] = v; matchR[v] = u; 
            return 1; 
        }

    return 0;
}

int matching(int M, int N, vector<pair<int, int>> E) {

    // Trạng thái ban đầu chưa có cặp ghép
    fill(matchL + 1, matchL + M + 1, -1);
    fill(matchR + 1, matchR + N + 1, -1);

    // Xây dựng danh sách kề
    for(int i = 0; i < (int) E.size(); ++i) { 
        int u = E[i].first, v = E[i].second;
        G[u].push_back(v);
    }

    int ans = 0;

    while(true) {
        // Xây dựng các đỉnh nguồn
        queue<int> q;
        for(int u = 1; u <= M; ++u) {
            if(matchL[u] == -1) {
                dist[u] = 0; q.push(u); 
            } else {
                dist[u] = -1;
            }
        }
        
        // Thuật toán loang (BFS)
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int v : G[u]) {
                if(matchR[v] != -1 && dist[matchR[v]] == -1) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        
        // Tìm đường tăng luồng
        int newMatches = 0;
        ++iteration;
        for(int u = 1; u <= M; ++u) {
            if(matchL[u] == -1) newMatches += dfs(u);
        }
        if(newMatches == 0) break;
        // Cập nhật số lượng cặp ghép mới vào số cặp ghép hiện tại
        ans += newMatches;
    }

    return ans;
}
```

### Độ phức tạp

Từ nhận xét 2.2.1 và bổ đề 4, ta nói kết luận rằng: số cặp ghép còn lại cần tìm không quá $\frac{2|V|}{\sqrt{|V| + 1}}$ hay $2\sqrt{|V|}$ ở lần tìm kiếm thứ $\sqrt{|V|}$. Vì thế, ta sẽ đạt được cặp ghép cực đại sau thêm nhiều nhất $3 \sqrt{|V|}$ lần thực hiện tìm kiếm đường tăng luồng. Do vậy, cặp ghép đạt cực đại trong nhiều nhất $4 \sqrt{|V|}$ lần tìm kiếm đường tăng luồng.

Ngoài ra, ta biết rằng độ phức tạp để thực hiện tìm kiếm đường tăng luồng ở mỗi lần tìm là $\mathcal{O}(E)$. Do đó, độ phức tạp của thuật toán là $\mathcal{O}(E \cdot \sqrt{V})$.

## Một số bài toán liên quan
### [Bài toán tìm tập bao phủ cực tiểu](https://en.wikipedia.org/wiki/Vertex_cover) 
Tập bao phủ cực tiểu là tập các đỉnh mà mọi cạnh trong đồ thị chứa ít nhất một đỉnh kề thuộc tập.

Trong đồ thị bình thường, bài toán tìm kiếm tập bao phủ cực tiểu thuộc lớp NP-khó. Tuy nhiên, trong đồ thị hai phía, bài toán có thể giải quyết trong thời gian đa thức.

Thêm vào đó, bài toán tìm tập bao phủ cực tiểu và bài toán tìm cặp ghép cực đại được coi là hai bài toán liên quan tới nhau và được chứng minh bằng định lý Kőnig.

Định lý phát biểu: Số lượng cạnh trong cặp ghép cực đại đúng bằng số lượng đỉnh trong tập bao phủ cực tiểu.

### [Bài toán phân việc](https://oj.vnoi.info/problem/assign1)
Bài toán: Cho $n$ công nhân và $n$ công việc. Thời gian người thứ $i$ hoàn thành công việc thứ $j$ là $c_{i,j}$. Mỗi người chỉ làm một việc, và mỗi việc chỉ được làm bởi một người. Hỏi làm sao để phân $n$ người làm $n$ công việc để tổng thời gian hoàn thành của mọi người là nhỏ nhất.
**Ràng buộc**: $n \le 500$, $1 \le c_{i, j} \le 2 \cdot 10^9$.

Đưa bài toán về dạng đồ thị, ta thấy rằng bài toán trở thành tìm cặp ghép cực đại với tổng chi phí cực tiểu trên đồ thị hai phía. Bằng cách sử dụng thuật toán Hungarian, ta có thể giải quyết bài toán trong $\mathcal{O}(n^3)$.

## Luyện tập

- [VNOJ - Company3](https://oj.vnoi.info/problem/company3)
- [VNOJ - Match1](https://oj.vnoi.info/problem/match1)
- [VNOJ - Match2](https://oj.vnoi.info/problem/match2)
- [VNOJ - Sflowerf](https://oj.vnoi.info/problem/sflowerf)
- [ICPC - 2020 Problem J. Evacuation](https://icpcvn.github.io/2020/northern-central/problems.pdf)
- [CS academy - No Prime Sum](https://csacademy.com/contest/archive/task/no-prime-sum/)
- [CF - Session in BSU](https://codeforces.com/contest/1027/problem/F)
- [CF - Easter Eggs](https://codeforces.com/gym/101666/problem/E)
- [CF - Heavy Chain Clusterization](https://codeforces.com/gym/100269/attachments)
- [CF - Birthday](https://codeforces.com/contest/590/problem/E)
- [CF - Matching Reduction](https://codeforces.com/contest/1721/problem/F)

## Tham khảo

Bài viết được tham khảo từ các bài viết sau:
- [Yinan Rao - Proof of Berge’s Theorem
](https://www.math.nagoya-u.ac.jp/~richard/teaching/s2024/SML_Rao_2.pdf)
- [Cp-algorithm - Kuhn's Algorithm](https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html)
- [Sariel Har-Peled - Matchings](https://courses.grainger.illinois.edu/cs498to1/sp2021/lectures/14/matchings.pdf)
- [John E. Hopcroft" và Richard M. Karp - Matchings](https://cse.unl.edu/~choueiry/Documents/MaxMatching-HopdcroftKarp.pdf)
- [ DeMen100ns - Kuhn Algorithm $O(N * sqrt(M))$!](https://www.facebook.com/pagedemen100ns/posts/kuhn-algorithm-on-sqrtmspoiler-bait-th%C3%B4i-ch%E1%BB%A9-l%C3%A0m-g%C3%AC-c%C3%B3-b%C3%A0i-to%C3%A1n-t%C3%ACm-b%E1%BB%99-c%E1%BA%B7p-gh%C3%A9p-/529966502715166/)