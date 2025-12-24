---
title: Các thuật toán tìm đường đi ngắn nhất - Phần 1
description: 
published: true
date: 2025-03-11T08:03:06.682Z
tags: 
editor: markdown
dateCreated: 2023-12-25T11:03:37.625Z
---

# Các thuật toán tìm đường đi ngắn nhất - Phần 1
**Tác giả:**
- Trần Hoài An - THPT Hoàng Lê Kha, Tây Ninh
- Nguyễn Đức Kiên - Đại học Công nghệ - ĐHQGHN

**Reviewer:**
- Nguyễn Xuân Tùng - Đại học Quốc Tế, Đại học Quốc gia Thành phố Hồ Chí Minh

Chuỗi bài viết: [**Phần 1**](/algo/graph-theory/shortest-path) • [Phần 2](/algo/graph-theory/shortest-path-2) • [Phần 3](/algo/graph-theory/spfa)
## Giới thiệu

Bài toán tìm đường đi ngắn nhất trên đồ thị là một trong những bài toán đa dạng, có nhiều ứng dụng thực tế như trong Google Maps, các bài toán networking, .... Các dạng bài về tìm đường đi ngắn nhất cũng thường xuyên có mặt trong các kì thi lập trình.

Chuỗi bài viết này sẽ giới thiệu một số thuật toán cơ bản của dạng bài tìm đường đi ngắn nhất:
* Sử dụng [Sắp xếp Topo](/algo/graph-theory/topological-sort.md).
* Thuật toán Dijkstra.
* Thuật toán Bellman - Ford.
* Thuật toán Floyd-Warshall (còn gọi là thuật toán Floyd).
* Thuật toán SPFA.

Mỗi thuật toán đều có ưu điểm, hạn chế riêng và phù hợp với các bài toán cụ thể. Cùng tìm hiểu và so sánh để lựa chọn giải pháp tối ưu cho từng bài toán.

Trong bài viết này, ta sẽ đi sâu vào hai thuật toán đầu tiên:
* Sử dụng [Sắp xếp Topo](/algo/graph-theory/topological-sort.md).
* Thuật toán Dijkstra.

## Đường đi ngắn nhất sử dụng [Sắp xếp Topo](/algo/graph-theory/topological-sort.md)

Trong trường hợp đồ thị có hướng và không có chu trình (DAG - Directed Acyclic Graph), ta sử dụng [sắp xếp topo](/algo/graph-theory/topological-sort.md) để xây dựng một thuật toán quy hoạch động tìm đường đi ngắn nhất

### Bài toán

Cho một đồ thị có hướng với $N$ đỉnh (được đánh số từ $0$ đến $N - 1$), $M$ cạnh có hướng, có trọng số, và một đỉnh nguồn $S$. Trọng số cạnh từ $u$ đến $v$ là $W[u, v]$. Biết rằng đồ thị đã cho **không có chu trình**. Yêu cầu tìm ra đường đi ngắn nhất từ đỉnh $S$ tới tất cả các đỉnh còn lại (hoặc cho biết nếu không có đường đi).

### Ý tưởng của thuật toán

#### Thứ tự topo

Nhắc lại, thứ tự topo của một đồ thị có hướng là một thứ tự sắp xếp của các đỉnh sao cho với mọi cung từ đỉnh $u$ đến đỉnh $v$ trong đồ thị, $u$ luôn nằm trước. Để đồ thị tồn tại thứ tự topo, nó phải là DAG. Một DAG có thể có nhiều thứ tự topo khác nhau.

Để tìm thứ tự topo của một DAG, có một cách rất đơn giản là xây dựng danh sách ngược bằng cách tiến hành DFS từ tất cả các đỉnh nếu đỉnh đó chưa được thăm trước đó, và đẩy nó vào danh sách sau khi đã thăm mọi đỉnh có thể thăm từ nó. Chi tiết về cách làm này bạn đọc có thể tham khảo bài viết [sắp xếp topo](/algo/graph-theory/topological-sort.md) của VNOI.

Quá trình tìm thứ tự topo do đó có độ phức tạp là $\mathcal{O}(N + M)$.

#### Tìm đường đi ngắn nhất

Gọi $d[v]$ là đường đi ngắn nhất đến đỉnh $v$. Một cách tự nhiên, ta vẫn sẽ tính $d[v]$ bằng các đỉnh $u$ kề $v$ (có cạnh từ đỉnh $u$ đến đỉnh $v$):

$$d[v] = \min\limits_{u \text{ kề } v} (d[u] + W[u,v])$$

Ta biết rằng chỉ tồn tại đường đi từ đỉnh có thứ tự topo nhỏ hơn đỉnh có thứ tự topo lớn hơn. Vì vậy, để tìm đường đi ngắn xuất phát từ một đỉnh, ta chỉ cần xét các đỉnh $u$ theo đúng thứ tự topo từ đỉnh xuất phát, và cập nhật các đỉnh $v$ kề với $u$.

Về độ phức tạp, ta mất $O(M)$ thời gian để tìm thứ tự topo và mất thêm $O(M + N)$ thời gian để tiến hành dp, ngoài ra thêm $O(N)$ thời gian nữa cho việc truy vết. Tổng độ phức tạp thời gian là $O(M+N)$. Độ phức tạp không gian nếu cài đặt bằng danh sách kề như ở dưới đây là $O(M+N)$.

### Cài đặt

```cpp=
int n, m, s;
vector<vector<pair <int, int> > > adj;
vector <int> topo, trace, topoId;
vector <long long> d;
vector <bool> visit;

void dfs(int u) {
    visit[u] = 1;
    for (auto p : adj[u]) {
        auto v = p.first;
        if (!visit[v]) {
            dfs(v);
        }
    }
    topo.push_back(u);
}

long long spDAG() {
    for (int u = 0; u < n; u++) {
        if (!visit[u]) {
            dfs(u);
        }
    }
    reverse(topo.begin(), topo.end());
    for (int i = 0; i < n; i++) {
        topoId[topo[i]] = i;
    }

    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    for (int i = topoId[s]; i < n; i++) {
        int u = topo[i];
        for (auto p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                trace[v] = u;
            }
        }
    }
    return *min_element(d.begin(), d.end());
}

vector<int> path() {
    vector<int> ret;
    if (d[t] != INF) {
        return ret;
    }
    int u = t;
    while (u != s) {
        ret.push_back(u);
        u = trace[u];
    }
    ret.push_back(u);
    reverse(ret.begin(), ret.end());
    return ret;
}

```

### Chú ý thêm

Ta thấy rằng, dấu của trọng số không ảnh hưởng đến thuật toán. Miễn đồ thị đã cho là DAG, ta luôn có thể tìm được đường đi ngắn nhất

Ngoài tìm được đường đi ngắn nhất từ một đỉnh, bằng cách quy hoạch động dựa trên thứ tự topo của một DAG ta có thể tìm được:
- Đường đi dài nhất từ một đỉnh đến các đỉnh khác (thay $\min$ thành $\max$)
- Đường đi ngắn nhất hoặc dài nhất trong tất cả các đường đi trên đồ thị (thêm một đỉnh giả nối với các đỉnh có bậc vào bằng $0$ và tìm đường đi ngắn nhất từ đỉnh này)
- Đếm số đường đi từ một đỉnh hoặc trên cả DAG

Tham khảo tại bài viết [Quy hoạch động trên DAG](/vnoi-magazine/2023/shortest-path-dag).

## Thuật toán Dijkstra

Thuật toán Dijkstra dùng để giải quyết bài toán **đường đi ngắn nhất một nguồn** (Single-source shortest path) trên đồ thị có **trọng số không âm**.

### Bài toán.

Cho một đồ thị có hướng với $N$ đỉnh (được đánh số từ $0$ đến $N-1$), $M$ cạnh có hướng, có trọng số, và một đỉnh nguồn $S$. **Trọng số của tất cả các cạnh đều không âm**. Yêu cầu tìm ra đường đi ngắn nhất từ đỉnh $S$ tới tất cả các đỉnh còn lại (hoặc cho biết nếu không có đường đi).


**Sample Input**
```
7 8 0
0 2 7
0 1 1
0 3 4
2 5 8
5 3 3
4 5 6
1 4 3
2 4 3
```
**Sample Output**
```
0
1
7
4
4
10
-1
```

Hình ảnh của Test ví dụ. Ở đồ thị này, đỉnh nguồn là đỉnh $0$, đường đi ngắn nhất từ $0$ đến các đỉnh $0$ đến $5$ là $[0, 1, 7, 4, 4, 10]$. Riêng đỉnh $6$ không có đường đi đến.

![](https://i.imgur.com/UhI67bO.png)

### Ý tưởng của thuật toán.

Ý tưởng chính của thuật toán Dijkstra là tối ưu hóa đường đi bằng cách xét các cạnh $(u, v)$, so sánh hai đường đi $S \rightarrow v$ sẵn có với đường đi $S \rightarrow u \rightarrow v$.

Thuật toán sẽ duy trì một mảng chứa đường đi ngắn nhất từ $S$ đến tất cả các đỉnh. Ở mỗi bước, chọn đỉnh $u$ với đường đi $S \to u$ có trọng số nhỏ nhất trong số các đỉnh chưa được xử lý. Sau đó, thuật toán kiểm tra và cập nhật đường đi $S \rightarrow v$ bằng cách thử đường đi $S \rightarrow u\rightarrow v$. Vì $S \to u$ là đường đi ngắn nhất được chọn nên đường đi này không cần kiểm tra lại và được đánh dấu là đã xử lý xong. Thuật toán tiếp tục lặp các bước trên với các đỉnh còn lại cho đến khi tất cả đỉnh đều được xử lý.

### Minh họa thuật toán
Ta sẽ minh họa thuật toán bằng một đồ thị như hình. Định nghĩa:
- $D_u$ là đường đi ngắn nhất từ đỉnh nguồn đên đỉnh $u$ đã tìm được.
- $P_u$ nhận hai giá trị $true$, $false$ cho biết đỉnh $P_u$ đã được chọn để tối ưu chưa.

**Đỉnh được tô đen (đỉnh 0) sẽ là đỉnh nguồn.**

![](https://i.imgur.com/FPDbyq9.png)

Ban đầu, $D = [0, \infty, \infty, \infty]$, $P = [false, false, false, false]$

* Bước 1: Thuật toán sẽ chọn đỉnh $0$, vì $D_0 = 0$ là nhỏ nhất thỏa mãn $P_0 = false$. Tiến hành tối ưu các cạnh đi ra:
    * Cạnh $(0, 2)$: cập nhật $D_2 = min(D_2, D_0 + W_{0, 2}) = min(\infty, 0+1) = 1$
    * Cạnh $(0, 3)$: cập nhật $D_3 = min(D_3, D_0 + W_{0, 3}) = min(\infty, 0+4) = 4$

Sau bước này, $D = [0, \infty, 1, 4]$, $P = [true, false, false, false]$

* Bước 2: thuật toán sẽ chọn ra đỉnh $2$, có $D_2 = 1$ là nhỏ nhất thỏa mãn $P_2 = false$. Tiến hành tối ưu các cạnh đi ra:
    * Cạnh $(2, 1)$: cập nhật $D_1 = min(D_1, D_2 + W_{2, 1}) = min(\infty, 1+3) = 4$
    * Cạnh $(2, 3)$: cập nhật $D_3 = min(D_3, D_2 + W_{2, 3}) = min(4, 1+2) = 3$

Sau bước này, $D = [0, 4, 1, 3]$, $P = [true, false, true, false]$

* Bước 3: thuật toán sẽ chọn ra đỉnh $3$, có $D_3 = 3$ là nhỏ nhất thỏa mãn $P_3 = false$. Tiến hành tối ưu các cạnh đi ra:
    * Cạnh $(3, 1)$: cập nhật $D_1 = min(D_1, D_3 + W_{3, 1}) = min(4, 3+2) = 4$

Sau bước này, $D = [0, 4, 1, 3]$, $P = [true, false, true, true]$

* Bước 4: thuật toán sẽ chọn đỉnh $1$. Không có cạnh nào đi ra.


Đến đây, tất cả các đỉnh đều đã được đánh dấu. Thuật toán kết thúc. Đường đi ngắn nhất tìm được từ đỉnh $0$ là $D = [0, 4, 1, 3]$.

### Cài đặt
Ở thuật toán này, ta sẽ lưu đồ thị dưới dạng **danh sách kề**. Ta định nghĩa như sau:

- $D[u]$ là đường đi ngắn nhất từ $s\rightarrow u$. Ban đầu khởi tạo $D[u] = \infty$ với mọi $u$, riêng $D[s] = 0$.
- $W[u,v]$ là trọng số cạnh trên đường đi từ $u\rightarrow v$.
- $P[u]$ là mảng đánh dấu các đỉnh $u$ đã được xử lí chưa. Ban đầu tất cả các giá trị đều là **false**.
- Trong trường hợp bài toán yêu cầu chũng ta truy vết, ta có thể định nghĩa thêm một mảng $trace$, trong đó $trace[u]$ là đỉnh nằm trước đỉnh $u$ trên đường đi ngắn nhất từ $s$ đến $u$.

Ta sẽ lặp $N$ lần quá trình sau:
- Tìm đỉnh $u$ có $D[u]$ nhỏ nhất và $P[u] = false$.
- Sau khi tìm được đỉnh $u$, ta xét các đỉnh $v$ kề với đỉnh $u$ và tiến hành tối ưu hóa $D[v]$: nếu $D[v] > D[u] + W[u,v]$ thì $D[v] = D[u] + W[u,v]$.
    - Nếu việc tối ưu hóa diễn ra, ta sẽ cập nhật $trace[v] = u$.
- Đánh dấu $P[u] = true$, nghĩa là đỉnh $u$ đã được xử lí xong

#### Độ phức tạp thuật toán

Trong quá trình tính toán, ta thực hiện $N$ lần lặp:
- Bước đầu tiên có độ phức tạp $O(N)$ **mỗi lần lặp**.
- Bước thứ hai có **tổng độ phức tạp $O(M)$ qua tất cả các lần lặp**

Như vậy độ phức tạp của cách cài đặt cơ bản sẽ là $O(N^2 + M)$.

**Code:**
``` cpp=
const long long INF = 2000000000000000000LL;
struct Edge{
    int v;
    long long w;
};
void dijkstra(int n, int S, vector<vector<Edge>> E, 
              vector<long long> &D, vector<int> &trace) {
    D.resize(n, INF);
    trace.resize(n, -1);

    vector<bool> P(n, 0);
    D[S] = 0;

    for (int i = 0; i < n; i++) {
        int uBest; // tìm đỉnh u chưa dùng, có khoảng cách nhỏ nhất
        long long Max = INF;
        for (int u = 0; u < n; u++) {
            if(D[u] < Max && P[u] == false) {
                uBest = u;
                Max = D[u];
            }
        }

        // cải tiến các đường đi qua u
        int u = uBest;
        P[u] = true;
        for(auto x : E[u]) {
            int v = x.v;
            long long w = x.w;
            if(D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
}
```
### Cải tiến đối với đồ thị thưa

* Nhận xét rằng bước đầu tiên: "Tìm đỉnh $u$ có $D_u$ nhỏ nhất và $P_u = false$", có thể được cải tiến. Ta có thể sử dụng cấu trúc dữ liệu [Heap](/translate/wcipeg/Binary-Heap.md) (cụ thể là Min Heap) hoặc cây nhị phân tìm kiếm để cải tiến bước này.
    * Mỗi lần chọn cạnh $(u, v)$ để tối ưu hóa $D_v$, ta đẩy cặp $\{D_v, v\}$ vào trong Heap. $\implies$ sử dụng $M$ cạnh sẽ có tổng độ phức tạp là $O(M\log N)$
    * Để tìm đỉnh có $D_u$ nhỏ nhất, ta chỉ cần liên tục lấy phần tử trên cùng trong Heap ra, cho đến khi gặp đỉnh $u$ thỏa mãn $P_u = false$. $\implies$ cần lấy ra tối thiểu $N$ lần để lấy được tất cả $N$ đỉnh sẽ có tổng độ phức tạp là $O(N\log N)$

* Do đó, độ phức tạp của thuật toán sau khi cải tiến là $O((M+N)\log N)$.


**Lưu ý rằng với đồ thị dày cạnh $\left(M \sim \frac{N(N-1)}{2}\right)$ thì cải tiến sử dụng Min Heap không tốt hơn cài đặt cơ bản.** Khi đó, độ phức tạp của hai cách cài đặt có dạng như sau:
- Cách cài đặt cơ bản: $O(N^2)$.
- Cách cài đặt cải tiến: $O(N^2\log N)$.

Tuy nhiên, thực tế các bài toán lập trình thi đấu ta thường gặp sẽ giới hạn $N, M \le 10^5$ nên nhìn chung khi thuật toán Min Heap với độ phức tạp $O((M + N)\log N)$ luôn tốt hơn cả.

**Code:**
```cpp=
const long long INF = 2000000000000000000LL;
struct Edge{// kiểu dữ liệu tự tạo để lưu thông số của một cạnh.
    int v;
    long long w;
};
struct Node{// kiểu dữ liệu để lưu đỉnh u và độ dài của đường đi ngắn nhất từ s đến u.
    int u;
    long long Dist_u;
};
struct cmp{
    // Vì priority_queue mặc định để giá trị lớn nhất lên đầu
    // Nên b sẽ đặt lên trước a trong priority_queue chỉ khi a < b
    // Trong trường hợp này, ta cần a.Dist_u > b.Dist_U
    bool operator() (Node a, Node b) {
        return a.Dist_u > b.Dist_u;
    }
};
void dijkstraSparse(int n, int s, vector<vector<Edge>> &E, vector<long long> &D, vector<int> &trace) {
    D.resize(n, INF);
    trace.resize(n, -1);
    vector<bool> P(n, 0);

    D[s] = 0;
    priority_queue<Node, vector<Node>, cmp> h; // hàng đợi ưu tiên, sắp xếp theo dist[u] nhỏ nhất trước
    h.push({s, D[s]});

    while(!h.empty()) {
        Node x = h.top();
        h.pop();

        int u = x.u;
        if(P[u] == true) // Đỉnh u đã được chọn trước đó, bỏ qua
            continue;

        P[u] = true; // Đánh dấu đỉnh u đã được chọn
        for(auto e : E[u]) {
            int v = e.v;
            long long w = e.w;

            if(D[v] > D[u] + w) {
                D[v] = D[u] + w;
                h.push({v, D[v]});
                trace[v] = u;
            }
        }
    }
}
```

### Tìm lại đường đi ngắn nhất
Để tìm lại đường đi ngắn nhất từ $S$ về $u$, ta sẽ bắt đầu từ đỉnh $u$, sau đó truy vết theo mảng $trace$ ngược về $S$.

```cpp=
vector<int> trace_path(vector<int> &trace, int S, int u) {
    if (u != S && trace[u] == -1) return vector<int>(0); // không có đường đi

    vector<int> path;
    while (u != -1) { // truy vết ngược từ u về S
        path.push_back(u);
        u = trace[u];
    }
    reverse(path.begin(), path.end()); // cần reverse vì đường đi lúc này là từ u về S

    return path;
}

```

## Tổng kết

Bảng so sánh các thuật toán được đề cập:

<center>
    
| **Thuật toán**          | **Bài toán** | **Độ phức tạp**     |
| ----------------------- | ------------ | ------------------- |
| **DP theo thứ tự topo** | Một nguồn    | $O(M + N)$          |
| **Dijkstra**            | Một nguồn    | $O(N^2 + M)$        |
| **Dijkstra + Min Heap** | Một nguồn    | $O((M + N) \log N)$ |
</center>

Heap không phải là cấu trúc dữ liệu duy nhất có thể sử dụng khi cài đặt Dijkstra dành cho đồ thị thưa. Ta có thể sử dụng bất cứ cấu trúc dữ liệu nào hỗ trợ các thao tác *"xóa khỏi tập hợp"*, *"cập nhật phần tử trong tập hợp"*, *"tìm phần tử nhỏ nhất trong tập hợp"*. Do đó, các cây tìm kiếm nhị phân (ví dụ như `std::set` trong C++) cũng là một lựa chọn khi cài đặt thuật toán này.

*Để khám phá thêm những thuật toán thú vị khác để tìm đường đi ngắn nhất trên đồ thị, mời bạn tiếp tục theo dõi [phần 2](/algo/graph-theory/shortest-path-2) của chuỗi bài viết này.*

## Bài tập vận dụng
**Đồ thị dạng DAG:**
- [CSES - Longest Flight Route](https://cses.fi/problemset/task/1680)
- [CSES - Game Routes](https://cses.fi/problemset/task/1681)

**Thuật toán Dijkstra:**
- [Kattis - shortestpath1](https://open.kattis.com/problems/shortestpath1)
- [Codeforces - Dijsktra?](https://codeforces.com/problemset/problem/20/C) (truy vết đường đi)
- [CSES - Flight Discount](https://cses.fi/problemset/task/1195)
- [Codeforces - Reducing Delivery Cost](https://codeforces.com/problemset/problem/1433/G)
- [Các bài theo tag trên VNOJ](https://oj.vnoi.info/problems/?type=24&point_start=&point_end=)