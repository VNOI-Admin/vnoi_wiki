---
title: Tổng quan về lý thuyết đồ thị
description: 
published: true
date: 2024-09-21T10:16:09.205Z
tags: 
editor: markdown
dateCreated: 2024-09-19T11:09:15.064Z
---

# Tổng quan về lý thuyết đồ thị
- **Tác giả:** Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành - Kon Tum
- **Reviewer:** Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN
## Giới thiệu

Trước khi đến với lí thuyết đồ thị, ta có một câu hỏi nhỏ như sau:

> Thành phố Königsberg thuộc Phổ, nay là Kaliningrad thuộc Nga, là một thành phố nằm ở 2 bên sông Pregel và có 2 hòn đảo lớn Kneiphof và Lomse. Trước kia, 2 hòn đảo được kết nối với nhau và với 2 bên bờ sông bằng 7 cây cầu.
> ![graph1.png](/algo/graph/graph1.png)
>
> Bài toán đặt ra ở đây là: Hãy tìm một con đường đi qua 7 cây cầu ít nhất một lần và chỉ một lần duy nhất.

Bài toán này - bài toán 7 cầu ở Königsberg, đã được giải bởi nhà toán học [Leonhard Euler](https://en.wikipedia.org/wiki/Leonhard_Euler) vào thế kỉ XVIII và đã cho ra đời định lý đầu tiên về lý thuyết đồ thị. 

Trong bài viết này, ta sẽ tìm hiểu về lý thuyết đồ thị: định nghĩa, các dạng của đồ thị, một số khái niệm, tính chất liên quan, cách lưu trữ đồ thị trong chương trình và một số thuật toán liên quan đến đồ thị.

## Định nghĩa

Hình ảnh dưới đây là một ví dụ về một đồ thị:

<center>
<img src="/algo/graph/graph2.png" alt="Đồ thị"/>
</center>

Những vòng tròn được gọi là các **đỉnh (vertices)** hoặc các **nút (nodes)**, và những đường thẳng nối những vòng tròn được gọi là các **cạnh (edges)**.

Về cơ bản: Đồ thị là một tập hợp hữu hạn gồm các **đỉnh** và được nối với nhau bởi các **cạnh**. 

Một đồ thị $G$ sẽ được kí hiệu:

$$G = (V, E)$$

Với $V$ là tập hợp chứa các đỉnh, và $E$ là tập hợp chứa các cạnh, mỗi cạnh có dạng một cặp giá trị $\{ u, v \}$ (có thể được viết thành $uv$). Ví dụ:

$$G = \{ \{1, 2, 3, 4, 5, 6\}, \{\{1, 2\}, \{1, 5\}, \{2, 5\}, \{2, 3\}, \{3, 4\}, \{4, 5\}, \{4, 6\} \} \} $$

chính là đồ thị ở hình ví dụ trên.

Tập hợp đỉnh $V$ của đồ thị $G$ được kí hiệu $V(G)$, tập hợp cạnh được kí hiệu $E(G)$. 

## Các dạng đồ thị

Các dạng đồ thị được nói đến dưới đây là một số dạng đồ thị phổ biến trong lập trình thi đấu.

### Đơn đồ thị

Một đồ thị không có **khuyên**, không có các cạnh song song, vô hướng và không có trọng số được gọi là **đơn đồ thị** (hay chỉ đơn giản là đồ thị).

<center>
<img src="/algo/graph/graph3.png" alt="Đơn đồ thị"/>
</center>

Note: 
- **Khuyên** là các cạnh có dạng $uu$.
- Hai hoặc nhiều cạnh **song song** với nhau khi các cạnh có chung hai điểm đầu mút.

### Đa đồ thị

Một đồ thị tồn tại các cạnh song song được gọi là **đa đồ thị**. 

Đơn đồ thị là một dạng đặc biệt của đa đồ thị.

<center>
<img src="/algo/graph/graph4.png" alt="Đa đồ thị"/>
</center>

### Đồ thị vô hướng

Một đồ thị là **vô hướng (undirected)** khi cạnh không được chỉ định hướng. Nếu đồ thị tồn tại một cạnh $uv$, ta có thể đi theo hướng $u \rightarrow v$ và hướng $v \rightarrow u$. Khi này, việc viết 2 cạnh $uv$ và $vu$ là như nhau và ta chỉ cần viết 1 trong 2 cạnh.

<center>
<img src="/algo/graph/graph5.png" alt="Đồ thị vô hướng"/>
</center>

### Đồ thị có hướng

Một đồ thị là **có hướng (directed)** khi cạnh được chỉ định hướng. Điều này có nghĩa rằng nếu đồ thị tồn tại một cạnh $uv$, ta chỉ có thể đi theo hướng $u \rightarrow v$. Khi này, 2 cạnh $uv$ và $vu$ phân biệt.

<center>
<img src="/algo/graph/graph6.png" alt="Đồ thị có hướng"/>
</center>

### Đồ thị có trọng số

Một đồ thị **có trọng số (weighted)** là một đồ thị có các cạnh được gán một giá trị. Các giá trị có thể tượng trưng cho khoảng cách, chi phí di chuyển,... 

<center>
<img src="/algo/graph/graph7.png" alt="Đồ thị có trọng số"/>
</center>

### Đồ thị không có trọng số

Một đồ thị **không có trọng số (unweighted)** là một đồ thị các cạnh không được gán giá trị. Trong một số bài toán, có thể xem đồ thị không trọng số là một đồ thị có trọng số với các cạnh được gán giá trị bằng nhau (Ví dụ như có trọng số bằng 1).

### Đồ thị con

Một đồ thị $G_s = (V_s, E_s)$ là **đồ thị con (subgraph)** của một đồ thị $G = (V, E)$ khi tập đỉnh và tập cạnh của $G_s$ là tập con của các tập hợp tương ứng của $G$, hay $V_s \subseteq V$ và $E_s \subseteq E$ thỏa mãn.

## Các dạng đồ thị đặc biệt

Một số dạng đồ thị đặc biệt ta cần biết.

### Đồ thị đầy đủ

Một đồ thị là **đầy đủ** khi tất cả các cặp đỉnh của đồ thị được nối với nhau bởi một cạnh.

Nếu một đồ thị $G$ có $|V|$ đỉnh vô hướng và đầy đủ, số cạnh của $G$ sẽ là $|E| = \frac{|V| \times (|V| - 1)}{2}$.

<center>
<img src="/algo/graph/graph8.png" alt="Đồ thị đầy đủ"/>
</center>

### Đồ thị hai phía

Một đồ thị là **hai phía (bipartite)** khi tập đỉnh của nó có thể chia làm hai tập $X$ và $Y$ rời nhau sao cho mỗi cạnh trong đồ thị phải nối một đỉnh trong tập $X$ với một đỉnh trong tập $Y$, và không cặp đỉnh nào liên thông nhau với mỗi tập. 

<center>
<img src="/algo/graph/graph9.png" alt="Đồ thị hai phía"/>
</center>

### Directed acyclic graph (DAG)

**DAG** là một đồ thị *có hướng __không có chu trình__* . Một đồ thị có hướng được gọi là một DAG khi và chỉ khi đồ thị tồn tại [thứ tự tô pô](/algo/graph-theory/topological-sort.md).

<center>
<img src="/algo/graph/graph10.png" alt="DAG"/>
</center>

### Cây

Một đồ thị được gọi là một **cây** khi nó là một đồ thị *vô hướng, liên thông và không có chu trình*.

<center>
<img src="/algo/graph/graph11.png" alt="Cây"/>
</center>

## Các khái niệm, tính chất

Ta cùng điểm qua một số khái niệm, tính chất liên quan đến đồ thị.

### Đỉnh kề, cạnh liền thuộc, đỉnh

> Cho một đồ thị $G = (V, E)$:
> 
> 1. Hai đỉnh $u$ và $v$ của $G$ **kề nhau (adjacent)** khi $uv \in E$, hay $uv$ là một cạnh của $G$. Khi này, ta nói cạnh $uv$ là cạnh **liên thuộc (incident)** với hai đỉnh $u$ và $v$, đồng thời $u$, $v$ là hai **đỉnh đầu mút (endpoints)** của cạnh $uv$.
> 
> 1. Cho đỉnh $u \in V$, các đỉnh **hàng xóm (neighbours)** với đỉnh $u$ là tất cả các đỉnh $v \in V$ thỏa mãn $uv \in E$, hay tất cả các đỉnh $v$ kề với $u$.
> 
> 1. Cho đỉnh $u \in V$, **bậc (degree)** của đỉnh $u$ chính là số lượng hàng xóm của đỉnh $u$. Kí hiệu: $deg(u)$. Ta có một số bổ đề về bậc như [bổ đề bắt tay](https://en.wikipedia.org/wiki/Handshaking_lemma): 
> $$\sum_{u \in V} deg(u) = 2|E|$$
> 	Nếu $G$ là một đồ thị có hướng, ta định nghĩa: 
> 		- **Bán bậc ra (out-degree)** của đỉnh $u$, kí hiệu $deg^+(u)$, là số lượng cạnh xuất phát từ đỉnh $u$, hay giá trị của $|\{v \in V | uv \in E\}|$.
> 		- **Bán bậc vào (in-degree)** của đỉnh $u$ kí hiệu $deg^-(u)$, là số lượng cạnh kết thúc tại đỉnh $u$, hay giá trị của $|\{v \in V | vu \in E\}|$.
> 	Trong đồ thị có hướng, tổng bán bậc vào của tất cả các đỉnh luôn bằng tổng bán bậc ra của tất cả các đỉnh (vì mỗi cạnh có một đỉnh bắt đầu và một đỉnh kết thúc).

### Đường đi, chu trình

> Cho một đồ thị $G = (V, E)$:
> 
> 1. Một **đường đi (walk)** (trong $G$) là một dãy các đỉnh $(v_0, v_1, v_2,..., v_k)$ thuộc $G$ và các cạnh $(v_0v_1, v_1v_2,..., v_{k - 1}v_k)$ là các cạnh thuộc đồ thị.
> 
>     Một **trail** là một đường đi trong đó tất cả các cạnh trên đường đi đôi một phân biệt.
>     
>     Một **path** là một đường đi trong đó tất cả các đỉnh trên đường đi đôi một phân biệt (suy ra các cạnh trên đường đi cũng đôi một phân biệt).
> 
> 1. Với $w = (v_0, v_1, v_2,..., v_k)$ là một đường đi trong $G$, ta có:
> 		- $v_0, v_1, v_2,..., v_k$ là các **đỉnh** của $w$.
> 		- $v_0v_1, v_1v_2,..., v_{k - 1}v_k$ là các **cạnh** của $w$.
> 		- **Độ dài (khoảng cách)** của đường đi $w$ là một số nguyên không âm $k$ ($k$ tương đương với số cạnh trên đường đi, và $k + 1$ tương đương với số đỉnh). Nếu $G$ có trọng số, độ dài của đường đi là tổng trọng số của các cạnh trên đường đi.
> 		- $v_0$ được gọi là **đỉnh đầu (starting point)** của $w$, ta nói $w$ *bắt đầu* tại tại đỉnh $v_0$.
> 		- $v_k$ được gọi là **đỉnh cuối (ending point)** của $w$, ta nói $w$ *kết thúc* tại tại đỉnh $v_k$.
> 		- Cho hai đỉnh $p$ và $q$ thuộc $G$, ta nói **đường đi từ** $p$ **đến** $q$ là đường đi bắt đầu từ đỉnh $p$ và kết thúc tại đỉnh $q$.
>
> 1. Một **đường đi khép kín (closed walk)** của $G$ một đường đi mà đỉnh cuối trùng với đỉnh đầu. Hay nói cách khác, là một dãy các đỉnh $(v_0, v_1, v_2,..., v_k)$ với $v_0 = v_k$. 
>
> 1. Một **chu trình (cycle)** của $G$ là một đường đi khép kín $(v_0, v_1, v_2,..., v_k)$ với $k \ge 3$ và các đỉnh $(v_0, v_1, v_2,..., v_{k - 1})$ đôi một phân biệt.
>      Một số trường hợp đặc biệt:
>      - Nếu $G$ là một đồ thị có hướng hoặc là một đa đồ thị, $G$ tồn tại chu trình có 2 đỉnh khi trong đồ thị tồn tại hai đỉnh $a$ và $b$ được nối với nhau bởi 2 cạnh song song. Ví dụ: ![2_node_cycle](/algo/graph/graph12.png)
>      - $G$ tồn tại chu trình có 1 đỉnh nếu trong đồ thị tồn tại cạnh khuyên. Ví dụ: ![1_node_cycle](/algo/graph/graph13.png)
>
> 1. Một đường đi (chu trình) là *sơ cấp* nếu nó không đi qua đỉnh nào hai lần trở lên. Một đường đi (chu trình) là *đơn giản* nếu nó không đi qua cạnh nào hai lần trở lên.

### Tính liên thông, khớp, cầu

> Cho một đồ thị $G = (V, E)$:
> 
> 1. Hai đỉnh $u$ và $v$ của $G$ **liên thông** nếu tồn tại ít nhất 1 đường đi từ $u$ đến $v$.
>
> 1. $G$ **liên thông (connected)** khi mọi cặp đỉnh của $G$ tồn tại đường đi. 
>       $G$ **song liên thông (biconnected)** nếu nó liên thông và không có đỉnh khớp, nghĩa là nếu xóa một đỉnh bất kì thì đồ thị vẫn liên thông.
>
> 1. Đối với một đồ thị có hướng:
> 		- Một đồ thị có hướng $G$ được gọi là **liên thông mạnh (strongly connected)** nếu mọi cặp đỉnh của $G$ tồn tại đường đi.
> 		- Một đồ thị có hướng $G$ được gọi là **liên thông yếu (weakly connected)** nếu khi ta xem đồ thị $G$ là một đồ thị vô hướng thì $G$ liên thông.
> 
> 1. Đỉnh $u$ thuộc $G$ được gọi là **khớp (articulation point)** nếu khi ta xóa bỏ đỉnh $u$ khỏi đồ thị thì $G$ không còn liên thông.
>
> 1. Cạnh $uv$ thuộc $G$ được gọi là **cầu (bridge)** nếu khi ta xóa bỏ cạnh $uv$ khỏi đồ thị thì $G$ không còn liên thông.
>
> 1. Nếu $G$ không liên thông, $G$ sẽ tồn tại nhiều đồ thị con liên thông, rời nhau. Mỗi đồ thị con đó được gọi là một **thành phần liên thông (TPLT) (connected component)** của $G$.

### Cây

Đối với các đồ thị cây, ta có thêm một số định nghĩa và tính chất:

> Cho một đồ thị $G = (V, E)$:
> 
> 1. $G$ là cây khi nó thỏa mãn ít nhất 2 điều kiện dưới đây:
> 		- $G$ không có chu trình
> 		- $G$ liên thông
> 		- Số cạnh bằng số đỉnh trừ 1 hay $|E(G)| = |V(G)| - 1$ 
> 
> 1. $G$ là một **rừng cây (forest)** khi $G$ có nhiều hơn 1 TPLT, mỗi TPLT là một cây.
> 
> 1. Chỉ tồn tại **một** đường đi độc nhất nối 2 đỉnh bất kì trên $G$.
> 
> 1. Thêm một cạnh bất kì chưa có trong $G$ sẽ xuất hiện một chu trình. 
>
> 		Đồng thời, việc xóa một cạnh bất kì trong $G$ sẽ làm tăng số TPLT của cây $\rightarrow$ tất cả các cạnh trên $G$ đều là cạnh cầu.

#### Gốc, lá, quan hệ giữa các đỉnh trong cây

> Cho một đồ thị cây $T = (V, E)$:
> 
> 1. **Gốc (root)** của $T$ là một đỉnh thuộc $T$ được lựa chọn làm gốc. Thông thường, các bài toán đều chọn đỉnh 1 làm gốc của cây, nếu bài toán không chỉ rõ gốc của cây là đỉnh nào, hãy giả sử nó là đỉnh 1. Một số cây có thể không có gốc.
> 
> 1. **Đỉnh lá (leaf)** của $T$ là các đỉnh có bậc bằng 1.
>  
> 1. Nếu $T$ có gốc, các đỉnh thuộc $T$ sẽ hình thành quan hệ **cha/con (parent/child)**. 
> Cụ thể:
> 		- Với mỗi cặp cạnh $uv$ bất kì: nếu khoảng cách tới gốc của $v$ ngắn hơn hơn khoảng cách tới gốc của $u$, đỉnh $v$ sẽ là **cha (parent)** của đỉnh $u$. Nếu khoảng cách tới gốc của $v$ dài hơn thì đỉnh $v$ sẽ là **con (child)** của đỉnh $u$.
> 		- Một đỉnh có thể có nhiều con, nhưng chỉ có một cha.
> 		- Đỉnh gốc không có cha, đỉnh lá không có con.
> 		- Đỉnh có khoảng cách tới gốc ngắn hơn sẽ là **tổ tiên (ancestor)** của đỉnh có khoảng cách tới gốc xa hơn. Ngược lại, đỉnh xa hơn sẽ là **hậu duệ (descendant)** của đỉnh gần hơn.
> 		- **Tổ tiên thứ k (Kth-ancestor)** của một đỉnh $u$ là một đỉnh $v$ có hậu duệ là đỉnh $u$ và khoảng cách của 2 đỉnh đúng bằng k.
>
> 1. Khoảng cách từ gốc đến một đỉnh được gọi là **chiều cao (height)** hoặc **chiều sâu (depth)** của đỉnh. Chiều cao của cây $T$ là giá trị của đỉnh có chiều cao lớn nhất.
>
> 1. **Đường kính (diameter)** của cây $T$ là khoảng cách lớn nhất giữa hai đỉnh trong cây.
 
## Tổ chức dữ liệu

Có 3 cách phổ biến để biểu diễn đồ thị trong chương trình: ma trận kề, danh sách kề và danh sách cạnh. Tùy theo đề bài mà ta sẽ áp dụng các cách lưu trữ khác nhau.

Ta giả sử dữ liệu nhập của một đồ thị là một danh sách cạnh.

Đồ thị ví dụ:

<center>
<img src="/algo/graph/graph2.png" alt="Đồ thị"/>
</center>


### Ma trận kề (Adjacency matrix)

Ma trận kề là một cấu trúc đơn giản được dùng để lưu một đồ thị bất kì.

Để biểu diễn đồ thị $G(V, E)$ trong ma trận kề, ta xây dựng ma trận vuông $A$ với:
- $A[u][v] = 1$ nếu $uv \in E(G)$
- $A[u][v] = 0$ nếu $uv \notin E(G)$

| |1|2|3|4|5|6|
|---|---|---|---|---|---|---|
|**1**|0|1|0|0|1|0|
|**2**|1|0|1|0|1|0|
|**3**|0|1|0|1|0|0|
|**4**|0|0|1|0|1|1|
|**5**|1|1|0|1|0|0|
|**6**|0|0|0|1|0|0|

Ngoài ra:
- Nếu đồ thị **có trọng số**, ta thay 1 bằng trọng số của cạnh tương ứng.
- Nếu đồ thị **vô hướng**, ta đánh dấu cả $A[x][y]$ và $A[y][x]$, còn nếu **có hướng** thì chỉ đánh dấu $A[x][y]$.

```C++
const int N = 1010; 
int n, m;
int adj[N][N];
int main() {
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int a, b; cin >> a >> b;
		adj[a][b] = 1; // Nếu đồ thị có trọng số thì đổi 1 thành w
		adj[b][a] = 1; // Nếu đồ thị có hướng thì không cần viết dòng này
	}
	return 0;
}
```
### Danh sách kề (Adjacency list)

Danh sách kề là cách lưu trữ đồ thị phổ biến trong lập trình thi đấu. Để biểu diễn đồ thị bằng danh sách kề, ta tạo $N$ mảng giá trị, mảng giá trị thứ $u$ lưu danh sách các đỉnh kề với đỉnh $u$.

|Mảng danh sách kề|Các đỉnh kề|
|---|---|
|`adj[1]`|2, 5|
|`adj[2]`|1, 3, 5|
|`adj[3]`|2, 4|
|`adj[4]`|3, 5, 6|
|`adj[5]`|1, 2, 5|
|`adj[6]`|4|


```C++
const int N = 1e5 + 10; 
int n, m;
vector<int> adj[N];
int main() {
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int a, b; cin >> a >> b;
		adj[a].push_back(b); 
		adj[b].push_back(a); // Nếu đồ thị có hướng thì không cần viết dòng này
	}
	return 0;
}
```

Nếu đồ thị *có trọng số* thì với mỗi cạnh `(a, b)` có trọng số `w`, ta lưu cặp giá trị `(b, w)` trong `adj[a]`. Có thể lưu cặp giá trị `(b, w)` bằng kiểu dữ liệu `pair`.

```C++
vector<pair<int, int>> adj[N];
adj[1].push_back({2, 3}); // lưu cạnh (1, 2) có trọng số 3
```

### Danh sách cạnh (Edge list)

Danh sách cạnh được dùng để lưu các cạnh trong đồ thị.

Ta có thể lưu các cạnh của đồ thị bằng `pair` hoặc tạo một cấu trúc `struct` tùy ý để lưu cặp giá trị có trong cạnh của đồ thị.

```C++
struct Edge{
	int a, b, w; // w được dùng cho đồ thị có trọng số
	Edge(int u, int v, int weight): a(u), b(v), w(weight){}
	bool operator<(const Edge &e) const{
		return w < e.w; // Sắp xếp theo trọng số các cạnh
	}
};

int main() {
	int n, m; cin >> n >> m;
	vector<Edge> edges;
	for(int i = 0; i < m; ++i){
		int a, b, w; cin >> a >> b >> w;
		edges.push_back(Edge(a, b, w));
	}
	return 0;
}
```

## Một số thuật toán liên quan đến đồ thị

### Duyệt đồ thị

Khi giải quyết các bài toán lí thuyết đồ thị, ta cần phải duyệt các đỉnh có trong đồ thị. Vì vậy việc biết các thuật toán duyệt đồ thị là việc vô cùng quan trọng.

Hai thuật toán duyệt đồ thị phổ biến là [**thuật toán duyệt theo chiều sâu (Depth-First Search - DFS)**](/algo/graph-theory/Depth-First-Search-Tree.md) và [**duyệt theo chiều rộng (Breadth-First Search - BFS)**](/algo/graph-theory/breadth-first-search.md).

### Sắp xếp Tô-pô

Để xác định và tìm thứ tự tô-pô của một đồ thị có hướng, ta sử dụng thuật toán [sắp xếp tô-pô](/algo/graph-theory/topological-sort.md).

### Tìm đường đi ngắn nhất

Bài toán **tìm đường đi ngắn nhất trên đồ thị** là loại bài toán đa dạng, có nhiều ứng dụng thực tế. Các dạng bài toán này xuất hiện thường xuyên trong lập trình thi đấu.

Ta có một số thuật toán tìm đường đi ngắn nhất như:
- [Thuật toán Bellman-Ford](/algo/graph-theory/shortest-path#1-thu%E1%BA%ADt-to%C3%A1n-bellman-ford)
- [Thuật toán Dijkstra](/algo/graph-theory/shortest-path#2-thu%E1%BA%ADt-to%C3%A1n-dijkstra)
- [Thuật toán Floyd-Warshall](/algo/graph-theory/shortest-path#3-thu%E1%BA%ADt-to%C3%A1n-floyd-warshall)
- ...

Nếu đồ thị là DAG, ta có thể tìm được đi ngắn nhất một cách tối ưu bằng cách áp dụng DFS + sắp xếp Tô-pô - [Shortest Path DAG](/vnoi-magazine/2023/shortest-path-dag).

Ngoài ra, BFS có thể được dùng để tìm đường đi ngắn nhất trên đồ thị không có trọng số hoặc đồ thị có hướng với các cạnh có trọng số bằng 0 hoặc 1 - [BFS 0 -1](/algo/graph-theory/bfs-01). 

### Bài toán 2-SAT

**Bài toán 2-SAT** được phát biểu như sau:

Cho $m$ biến logic: $a_1, a_2,..., a_m$ và 1 biểu thức logic $C$ có dạng:

$$C = (u_1 \lor v_1) \land (u_2 \lor v_2) \land \ ... \land \ (u_n \lor v_n)$$

Trong đó $u_i$ và $v_i$ $(1 \le i \le n)$ được thay bằng biển logic $a_j$ hoặc $\lnot a_j$ nào đó. $(1 \le j \le m)$.

Ta sẽ gán các $a_j$ với một trong hai giá trị $true/false \ (1/0)$ sao cho biểu thức $C$ hợp lệ, hoặc thông báo rằng không thể có cách gán hợp lệ.

Ví dụ với biểu thức:

$$C = (a_1 \lor \lnot a_2) \land (\lnot a_1 \lor \lnot a_3) \land (a_1 \lor a_2) \land (a_4 \lor \lnot a_1)$$

nếu ta gán $a_1 = True$, $a_2 = False$, $a_3 = False$, $a_4 = True$ thì biểu thức trên hợp lệ.

Bài toán này có thể được giải bằng cách xét duyệt trâu, hoặc giải quyết một cách tối ưu bằng lý thuyết đồ thị: [bài viết](https://drive.google.com/file/d/15UbO4GWo1G6cUBDnV6uWk0KxjuEdurCG/view?usp=sharing).

### Luồng cực đại/lát cắt cực tiểu

Thông tin về luồng cực đại/lát cắt cực tiểu sẽ được cập nhật sau.

### Đường đi Euler trên cây

**[Đường đi Euler trên cây](/algo/graph-theory/euler-tour-on-tree.md) (Euler tour on tree)** là một phương pháp xử lí các bài toán có đồ thị cây bằng cách trải phẳng cây, từ đó các thao tác trên cây có thể được chuyển thành các thao tác trên mảng 1 chiều.

### Tổ tiên chung gần nhất

**Lowest Common Ancestor (LCA)** hay *tổ tiên chung gần nhất* của hai hay nhiều đỉnh là đỉnh sâu nhất là tổ tiên của tất cả các đỉnh.

<center>
<img src="/algo/graph/translate_topcoder_lca_rmq.png" alt="LCA"/>
</center>

Bạn có thể đọc thêm một số phương pháp giải LCA qua bài viết [sau](/algo/data-structures/lca).

### Heavy-Light Decomposition (HLD)

**Heavy-Light Decomposition (HLD)** là kĩ thuật phân tách một cây thành tập hợp các chuỗi đường đi.

Đây là kĩ thuật có ý tưởng khá tự nhiên và có tính dụng cao trong nhiều bài toán. Bạn có thể đọc thêm tại bài viết [này](/algo/data-structures/heavy-light-decomposition).

### Thuật toán phân tách trọng tâm

**Thuật toán phân tách trọng tâm** có thể hiểu là thuật toán "chia để trị" trên cây. Thuật toán này hoạt động bằng cách liên tục chia nhỏ cây và xử lý trên mỗi cây được chia.

Bạn có thể đọc thêm về thuật toán qua bài viết [sau](/algo/graph-theory/centroid-decomposition).


## Tham khảo

Bài viết này tham khảo thông tin về định nghĩa, các tính chất từ: [An introduction to graph theory](https://arxiv.org/pdf/2308.04512) bởi Darij Grinberg.