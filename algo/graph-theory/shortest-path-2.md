---
title: Các thuật toán tìm đường đi ngắn nhất - Phần 2
description: 
published: true
date: 2024-12-08T15:24:44.064Z
tags: 
editor: markdown
dateCreated: 2024-12-08T15:24:44.064Z
---

# Các thuật toán tìm đường đi ngắn nhất - Phần 2 - Chu trình âm

**Tác giả:**
- Trần Hoài An - THPT Hoàng Lê Kha, Tây Ninh
- Nguyễn Đức Kiên - Đại học Công nghệ - ĐHQGHN

**Reviewer:**
- Nguyễn Xuân Tùng - Đại học Quốc Tế, Đại học Quốc gia Thành phố Hồ Chí Minh

Chuỗi bài viết: [Phần 1](/algo/graph-theory/shortest-path) • [**Phần 2**](/algo/graph-theory/shortest-path-2) • [Phần 3](/algo/graph-theory/spfa)
## Giới thiệu

Tiếp tục [phần 1](/algo/graph-theory/shortest-path), trong bài viết này, ta sẽ đi sâu vào hai thuật toán tiếp theo:
* Thuật toán Bellman - Ford.
* Thuật toán Floyd-Warshall (còn gọi là thuật toán Floyd).

Khác với hai thuật toán bài trước, hai thuật toán này có thể giúp tìm được "chu trình âm" của đồ thị. Do vậy, chúng ta hãy đi đến khái niệm này đầu tiên.


## Khái niệm về chu trình âm

* Chu trình âm là một chu trình trong đó tổng trọng số các cạnh là số âm. Ví dụ trong hình dưới, ta có một chu trình âm $0 \rightarrow 1 \rightarrow 2$ có tổng trọng số là $7-9+1 = -1$

![](https://i.ibb.co/jbkzpCB/dijsktra.png)

* Nếu trên đường đi từ $u$ đến $v$ chứa chu trình âm thì độ dài đường đi ngắn nhất từ $u$ đến $v$ sẽ là $-\infty$. Vì vậy nên sự xuất hiện của chu trình âm trong đồ thị sẽ khiến một số cặp đỉnh không tồn tại đường đi ngắn nhất (chỉ tồn tại đường đi có độ dài âm vô cực).
    * Ví dụ: Ở đồ thị trên, đường đi ngắn nhất từ $4$ đến $5$ sẽ có cách đi là vô hạn lần qua chu trình âm đã nhắc đến, sau đó mới đi đến $5$. Như vậy không có đường đi ngắn nhất.

## Thuật toán Bellman - Ford

Thuật toán Bellman-Ford dùng để giải quyết bài toán **đường đi ngắn nhất một nguồn** (Single-source shortest path), đồ thị **có thể có trọng số âm**.

### Bài toán
Cho đồ thị có hướng gồm $N$ đỉnh, $M$ cạnh và một đỉnh nguồn $S$. Mỗi cạnh có trọng số nguyên (có thể âm, dương, hoặc bằng $0$). Yêu cầu xác định đường đi ngắn nhất từ đỉnh nguồn $S$ đến mỗi đỉnh $u$ từ $0$ đến $N-1$, với kết quả được xuất như sau:  
1. Nếu không tồn tại đường đi từ $S$ đến $u$, in ra **Impossible**.  
2. Nếu tồn tại đường đi từ $S$ đến $u$ nhưng không có đường đi ngắn nhất (do chu trình âm), in ra **-Infinity**.  
3. Trong các trường hợp khác, in ra độ dài đường đi ngắn nhất từ $S$ đến $u$.  

**Input:**  
- Dòng đầu tiên gồm ba số nguyên $N, M, S$.  
- $M$ dòng tiếp theo, mỗi dòng gồm ba số nguyên $u, v, W_{u, v}$ đại diện cho một cạnh có hướng từ $u$ đến $v$ với trọng số $W_{u, v}$.  

**Output:**  
- Gồm $N$ dòng, mỗi dòng là kết quả đường đi ngắn nhất từ $S$ đến các đỉnh từ $0$ đến $N-1$.  

**Ràng buộc:**  
- $1 \leq N \leq 1000$, $1 \leq M \leq 5000$  : $1 \le N \le 1000, 1 \le M \le 5000$

**Sample Input**
```
7 6 4
0 1 7
2 0 1
1 2 -9
2 5 1000
3 0 7
4 3 3
```
**Sample Output**
```
-Infinity
-Infinity
-Infinity
3
0
-Infinity
Impossible
```

### Ý tưởng của thuật toán.
Xét trường hợp đơn giản hơn, khi đồ thị không có trọng số âm (tức đường đi ngắn nhất luôn tồn tại).

Thuật toán Bellman-Ford sẽ thực hiện nhiều bước lặp. Ở mỗi bước lặp, ta sẽ duyệt **tất cả** các cạnh $(u, v)$ trên đồ thị, so sánh đường đi $S \rightarrow v$ đã tìm được với đường đi $S \rightarrow u \rightarrow v$

- Ví dụ đồ thị sau:

![](https://i.imgur.com/YMKQtKM.png)

- Giả sử ta tìm được đường đi từ $1\rightarrow 3$ có độ dài là $4$, và đường đi từ $1 \rightarrow 2$ có độ dài là $2$. Như vậy ta có thể sử dụng cạnh $(2, 3)$ để nối dài đường đi $1 \rightarrow 2$ thành $1 \rightarrow 2 \rightarrow 3$ có độ dài bằng $3$, tốt hơn đường đi trực tiếp $1 \rightarrow 3$ ta đã tìm được.

> **Nhận xét:** Vòng lặp trên cần thực hiện $N-1$ lần, mỗi lần đi qua toàn bộ $M$ cạnh, là sẽ đủ để tìm đường đi ngắn nhất.

:::spoiler **Chứng minh**
Nhận xét rằng một đường đi ngắn nhất bất kì sẽ không có đỉnh nào được đi lại quá một lần. Như vậy một đường đi ngắn nhất sẽ không có quá $N-1$ cạnh. Việc thực hiện phép tính $D_v = D_u + W_{u, v}$ cũng đồng nghĩa với thêm một cạnh $u \rightarrow v$ vào hành trình đi từ $S$ đến $v$. Vậy một $D_u$ chỉ có thể được tối ưu tối đa $N-1$ lần, và từ lần thứ $N$ trở đi sẽ không thể tối ưu hơn được nữa.
:::

### Cài đặt
Ở thuật toán này, đồ thị thường được lưu ở dạng **danh sách cạnh**.

* Định nghĩa $W[u, v]$ là trọng số cạnh nối từ đỉnh $u$ đến đỉnh $v$ (nếu có).
* Định nghĩa mảng $D[u]$ là đường đi ngắn nhất từ $S\rightarrow u$.
    Ban đầu, chưa có đường đi nào:
    * $D[u] = \infty$ với mọi $u$ khác $S$
    * $D[S] = 0$
* Nếu cần tìm lại chính đường đi ngắn nhất, ta định nghĩa thêm mảng truy vết $trace[u]$. Ta gán $trace[u]=v$ với ý nghĩa là đường đi ngắn nhất từ $S\rightarrow u$ cần đi qua cạnh $(v, u)$.
    Ban đầu mọi $trace[u]$ bằng $-1$ nghĩa là chưa có đường đi.
* Thực hiện $N-1$ lần:
    Xét lần lượt các cạnh $(u, v)$ trong đồ thị.
    Nếu $D[u] + W[u, v] < D[v]$, cập nhật:
    * $D[v] = D[u] + W[u, v]$
    * $trace[v] = u$.
* **Độ phức tạp**: Có tổng cộng $N-1$ lần lặp, mỗi lần lặp cần duyệt tất cả $M$ cạnh trong đồ thị, như vậy độ phức tạp của thuật toán là $O(N*M)$.

**Code:**
```cpp=
const long long INF = 2000000000000000000LL;
struct Edge {
    int u, v;
    long long w; // cạnh từ u đến v, trọng số w
};
void bellmanFord(int n, int S, vector<Edge> &e,
                 vector<long long> &D, vector<int> &trace) {
    // e: danh sách cạnh
    // n: số đỉnh
    // S: đỉnh bắt đầu
    // D: độ dài đường đi ngắn nhất
    // trace: mảng truy vết đường đi
    // INF nếu không có đường đi
    // -INF nếu có đường đi âm vô tận
    D.resize(n, INF);
    trace.resize(n, -1);

    D[S] = 0;
    for(int T = 1; T < n; T++) {
        for (auto E : e) {
            int u = E.u;
            int v = E.v;
            long long w = E.w;
            if (D[u] != INF && D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
}
```

### Tìm lại đường đi ngắn nhất
Thao tác tìm đường đi ngắn nhất từ $S$ đến $u$ khá đơn giản, ta sẽ bắt đầu từ đỉnh $u$, sau đó truy vết theo mảng $trace$ ngược về $S$.

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

### Tìm chu trình âm

Thuật toán Bellman-Ford có thể xử lí được thêm trường hợp nhận biết chu trình âm, cũng như nhận biết nếu không tồn tại đường đi ngắn nhất đến một đỉnh.

#### Nhận biết đường đi âm vô cực

- Nhận xét tiếp rằng, ta có thể chạy vòng quanh chu trình âm liên tục để được đường đi ngắn hơn. Như vậy thuật toán Bellman-Ford ở vòng lặp thứ $N$ trở đi vẫn sẽ liên tục tối ưu được đường đi, thay vì dừng lại ở lần thứ $N-1$.
- Ta chỉ cần chạy thuật toán Bellman-Ford thêm một lần nữa, những đỉnh nào vẫn còn tối ưu được ở lần chạy thứ hai sẽ tối ưu được mãi mãi, và đó là các đỉnh không tồn tại đường đi ngắn nhất.

**Code:**
```cpp=
// sau khi chạy xong N-1 vòng lặp Bellman-Ford
for(int T = 0; T < n; T++){
    for (auto E : e) {
        int u = E.u;
        int v = E.v;
        long long w = E.w;
        if (D[u] != INF && D[v] > D[u] + w) {
            // vẫn còn tối ưu được --> âm vô cực
            D[v] = -INF;
            trace[v] = u;
        }
    }
}
```

#### Tìm chu trình âm

Một số bài toán có thể yêu cầu ta tìm một chu trình âm bất kì trong đồ thị. Ta có thể chỉnh sửa thuật toán Bellman-Ford lại như sau:
- Thay vì chạy $N$ vòng lặp Bellman-Ford như trường hợp trên, ta chỉ cần chạy một vòng lặp. Như vậy là đủ để phát hiện ít nhất một đỉnh có đường đi bằng $-\infty$ (nếu có).
- Tiến hành truy vết: Bắt đầu từ đỉnh $u$ bất kì có đường đi bằng $-\infty$, ta sẽ truy vết theo mảng $trace$:
    - Trước hết gán $u = trace[u]$ đủ $N$ lần để $u$ chắc chắn thuộc chu trình âm nào đó.
    :::spoiler Giải thích
    Ban đầu có thể đỉnh $u$ có đường đi bằng $-\infty$ nhưng chưa chắc thuộc chu trình âm. Ví dụ trường hợp sau:
    [![](https://i.imgur.com/PblptAC.png)
    ]()
    Ở đây, từ $0$ đến $1$ có độ dài đường đi ngắn nhất bằng $-\infty$, tuy nhiên đỉnh $1$ lại không thuộc chu trình âm nào.
    :::

    - Sau đó, $u$ sẽ thuộc một chu trình âm. Ta chỉ cần truy vết đỉnh $u$ theo mảng $trace$ cho đến khi gặp lại chính nó, sẽ được một chu trình.
- Chu trình vừa truy vết chính là một chu trình âm của đồ thị. Lưu ý ta vẫn phải đảo ngược kết quả truy vết, vì ta đang truy vết ngược so với đồ thị gốc.


```cpp=
bool findNegativeCycle(int n, vector<Edge> &e, vector<long long> &D, 
                       vector<int> &trace, vector<int> &negCycle) {
    // mảng D và trace đã được chạy qua thuật toán Bellman-Ford
    int negStart = -1; // đỉnh bắt đầu
    for (auto E : e) {
        int u = E.u;
        int v = E.v;
        long long w = E.w;
        if (D[u] != INF && D[v] > D[u] + w) {
            trace[v] = u;
            negStart = v; // đã tìm thấy -INF
            break;
        }
    }

    if (negStart == -1) return false; // không có chu trình âm

    int u = negStart;
    for (int i = 0; i < n; i++) {
        u = trace[u]; // đưa u về chu trình âm
    }

    negCycle = vector<int>(1, u);
    for (int v = trace[u]; v != u; v = trace[v]) {
        negCycle.push_back(v); // truy vết một vòng
    }
    reverse(negCycle.begin(), negCycle.end());

    return true;
}
```

## Thuật toán Floyd-Warshall

Thuật toán Floyd-Warshall dùng để giải quyết bài toán **đường đi ngắn nhất mọi cặp đỉnh** (All-pairs shortest path), đồ thị **có thể có trọng số âm**.


### Bài toán

Cho đồ thị gồm $N$ đỉnh và một ma trận trọng số $W$, trong đó ô $(i,j)$ cho biết rằng có một đường đi trực tiếp từ $i\rightarrow j$ với trọng số là $W_{i, j}$. Yêu cầu  tìm đường đi ngắn nhất giữa **mọi cặp đỉnh** trên đồ thị.

**Input**:
- Dòng đầu tiên gồm số nguyên dương $N$.
- $N$ dòng tiếp theo, mỗi dòng gồm $N$ số biểu diễn một ma trận trong đó ô $(i,j)$ cho biết đường đi trực tiếp từ $i\rightarrow j$ có trọng số là $W[i, j]$.

**Output**: 
- Ma trận kết quả trong đó giá trị ô $(i,j)$ là đường đi ngắn nhất từ $i\rightarrow j$.

**Ràng buộc:**
- $1 \leq N \leq 100$

**Sample Input**
```
5
0 4 2 1 6
7 0 1 2 4
2 3 0 1 2
4 5 5 0 1
6 8 7 3 0
```
**Sample Output**
```
0 4 2 1 2
3 0 1 2 3
2 3 0 1 2
4 5 5 0 1
6 8 7 3 0
```

### Ý tưởng của thuật toán.

Ý tưởng của thuật toán này là: "Liệu chúng ta có thể chèn một đỉnh $k$ vào đường đi ngắn nhất giữa 2 đỉnh $u$ và $v$?".

* Ví dụ như có một đường đi ngắn nhất từ $0 \rightarrow 4$ như sau: $0\rightarrow 1\rightarrow 2\rightarrow 3 \rightarrow 4$. Vậy việc tính đường đi ngắn nhất từ $0\rightarrow 4$ hoàn toàn có thể được chia thành tính đường đi ngắn nhất từ $0\rightarrow 2$ sau đó cộng với đường đi ngắn nhất từ $2\rightarrow 4$. Tương tự thế đường đi ngắn nhất từ $0\rightarrow 2$ và $2\rightarrow 4$ lại tiếp tực được phân hoạch thành những đường đi ngắn nhất khác đơn giản hơn và tối ưu hơn.

Ta nhận thấy có một cấu trúc đệ quy, chia nhỏ bài toán ở đây. Ý tưởng này cho phép chúng ta thực hiện một thuật toán mang hương vị quy hoạch động như sau:
- Gọi $D(u, v, k)$ là đường đi ngắn nhất, trong đó ta chỉ được đi qua $k$ đỉnh đầu tiên (có số thứ tự từ $0$ đến $k-1$), ngoại trừ chính $u$ và $v$. Ta có công thức truy hồi:
    - $D(u, v, 0) = W_{u, v}$ (không được dùng đỉnh nào ngoài chính $u, v$).
    - $D(u, u, k) = 0$
    - $D(u, v, k) =$ min của 2 trường hợp:
        - $D(u, v, k-1)$: ta không dùng đỉnh $k$ làm trung gian, giữ nguyên đường đi cũ.
        - $D(u, k, k-1) + D(k, v, k-1)$: ta dùng đỉnh $k$ làm trung gian, từ đường đi $u \rightarrow v$ thành đường đi $u \rightarrow k \rightarrow v$.

Đến đây ta có thể sử dụng trực tiếp công thức quy hoạch động để cài đặt thuật toán.

Để ý rằng, với mọi giá trị $k_0\in[0, N]$, $D(u, v, k_0)$ chỉ phụ thuộc vào $D(u, v, k_0 - 1)$. Hơn nữa, với $k_0$ như trên, $D(u, v, k_0)$ luôn tối ưu hơn $D(u, v, k_0-1)$. Vì vậy, ta hoàn toàn có thể bỏ trạng thái thứ ba của công thức quy hoạch động, và viết lại công thức như sau: $$D(u, v) = \min(D(u, v), D(u, k) + D(k, v))$$

### Cài đặt

- Định nghĩa:

    - $W[u, v]$ là giá trị đường đi trực tiếp từ $u\rightarrow v$.
    - $D[u, v]$ là giá trị đường đi ngắn nhất từ $u\rightarrow v$.
    - $trace[u, v]$ là mảng truy vết đường đi ngắn nhất từ $u\rightarrow v$

- Đồ thị sẽ được lưu dưới dạng **ma trận kề**. Ban đầu sẽ khởi tạo mọi $D[u, v] = W[u, v]$ vì khi chưa tối ưu gì thì đường đi trực tiếp luôn là đường đi ngắn nhất.
    - $trace[u, v]$ sẽ khởi tạo bằng $u$ với mọi cặp $u, v$.
    - Nếu không có cạnh nối giữa $u$ và $v$, coi như $W[u, v] = \infty$ .

- Thuật toán chỉ cần một vòng lặp xét mọi đỉnh $k$ như một đỉnh trung gian. Tiếp theo đến là 2 vòng lặp $u$, $v$, có ý nghĩa thử chèn đỉnh $k$ vào giữa đường đi từ $u$ đến $v$.
    - Nếu như $D[u, v]$ được tối ưu bằng đỉnh $k$, ta cập nhật thêm $trace[u, v] = trace[k, v]$

- Độ phức tạp của thuật toán là $O(N^3)$.

:::warning
**Chú ý:** Thuật toán Floyd-Warshall có thứ tự 3 vòng lặp là $k \rightarrow u \rightarrow v$ thay vì $u\rightarrow v\rightarrow k$ (đỉnh trung gian phải được đặt ở vòng lặp ngoài cùng), đây là một nhầm lẫn tương đối phổ biến khi cài đặt.
:::

**Code mẫu bằng C++:**

Thuật toán có thể được cài đặt rất dễ dàng chỉ với 3 vòng lặp:

```cpp=
void init_trace(vector<vector<int>> &trace) {
    int n = trace.size();
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            trace[u][v] = u;
        }
    }
}

void floydWarshall(int n, vector<vector<long long>> &w, vector<vector<long long>> &D, vector<vector<int>> &trace) {
    D = w;
    init_trace(trace); // nếu cần dò đường đi

    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (D[u][v] > D[u][k] + D[k][v]) {
                    D[u][v] = D[u][k] + D[k][v];
                    trace[u][v] = trace[k][v];
                }
            }
        }
    }
}
```

### Tìm lại đường đi ngắn nhất
Giống như hai thuật toán Bellman-Ford và Dijkstra, để tìm đường đi từ $u$ đến $v$, ta sẽ bắt đầu từ $v$, truy ngược về $u$ theo mảng trace đã tìm được.

```cpp=
vector<int> trace_path(vector<vector<int>> &trace, int u, int v) {
    vector<int> path;
    while (v != u) { // truy vết ngược từ v về u
        path.push_back(v);
        v = trace[u][v];
    }
    path.push_back(u);

    reverse(path.begin(), path.end()); // cần reverse vì đường đi từ v ngược về u

    return path;
}

```

### Trường hợp chu trình âm

Khi đồ thị có chu trình âm, dễ thấy $D[u, u]$ cũng sẽ bị "tối ưu hoá" và sẽ nhận giá trị âm. Đây là cơ sở để ta nhận biết đồ thị có chu trình âm hay không.

Muốn kiểm tra xem đồ thị có chu trình âm hay không, ta chỉ cần chỉ ra một đỉnh $u$ sao cho $D[u, u] < 0$. Còn để tìm một chu trình âm bất kỳ, ta truy vết như bình thường với đường đi là từ $u$ đến $u$. 

Nếu bài toán chỉ yêu cầu kiểm tra xem đồ thị có chu trình âm hay không hoặc chỉ ra một chu trình âm bất kỳ của đồ thị, thuật toán Bellman-Ford sẽ tốt hơn. Nhưng nếu đây là một yêu cầu đi kèm của bài toán tìm đường đi ngắn nhất giữa mọi cặp đỉnh, ta vẫn có thể áp dụng thuật toán Floyd để thực hiện nó.


## Tổng kết

Sau đây là bảng so sánh các thuật toán đã được đề cập:


| **Thuật toán**          | **Bài toán** | **Độ phức tạp**     | **Sử dụng được trọng số âm** | **Tìm được chu trình âm**                  |
| ----------------------- | ------------ | ------------------- | ---------------------------- | ------------------------------------------ |
| **DP theo thứ tự topo** | Một nguồn    | $O(M + N)$          | Có                           | Yêu cầu thuật toán: Đồ thị không chu trình |
| **Dijkstra**            | Một nguồn    | $O(N^2 + M)$        | Không                        | Không                                      |
| **Dijkstra + Min Heap** | Một nguồn    | $O((M + N) \log N)$ | Không                        | Không                                      |
| **Bellman-Ford**        | Một nguồn    | $O(N \cdot M)$      | Có                           | Có                                         |
| **Floyd-Warshall**      | Mọi cặp đỉnh | $O(N^3)$            | Có                           | Có                                         |

Trong trường hợp có chu trình âm, thuật toán Floyd-Warshall có thể phải tính toán đến những giá trị rất nhỏ (về phía số âm), đủ để gây ra hiện tượng tràn số (thậm chí với $N$ tương đối nhỏ). Cần phải chú ý đặc biệt đến trường hợp này khi cài đặt. Một cách thường dùng để giải quyết trường hợp này là gán `D[u][v] = max(D[u][v], -INF)` ngay sau mỗi lần tối ưu, chặn không cho $D[u, v]$ xuống dưới hằng số âm vô tận.

Với đồ thị thưa, không có trọng số âm, thay vì sử dụng thuật toán Floyd, ta có thể chạy thuật toán Dijkstra cải tiến $N$ lần với $N$ đỉnh nguồn để tìm đường đi ngắn nhất giữa mọi cặp đỉnh, với độ phức tạp $O(N \times (M + N)\log N)$.

*[Phần 3](/algo/graph-theory/spfa) của bài viết sẽ tiếp tục giới thiệu với bạn đọc một biến thể của thuật toán Bellman-Ford, hiệu quả đến mức người ta gọi nó là "Shortest Path **Faster** algorithm". Mời bạn đọc tiếp tục theo dõi.*

## Bài tập vận dụng

Thuật toán Bellman-Ford:

- [Kattis - shortestpath3](https://open.kattis.com/problems/shortestpath3)
- [CSES - High Score](https://cses.fi/problemset/task/1673)
- [CSES - Cycle Finding](https://cses.fi/problemset/task/1197) (tìm chu trình âm)
- [Kattis - xyzzy](https://open.kattis.com/problems/xyzzy)

Thuật toán Floyd-Warshall:

- [CSES - Shortest Route II](https://cses.fi/problemset/task/1672) (trọng số không âm)
- [Kattis - allpairspath](https://open.kattis.com/problems/allpairspath) (trọng số có thể âm)
- [Codeforces - Greg and Graph](https://codeforces.com/problemset/problem/295/B)
- [Các bài theo tag trên VNOJ](https://oj.vnoi.info/problems/?type=56&point_start=&point_end=)