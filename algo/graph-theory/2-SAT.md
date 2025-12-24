---
title: 2-SAT
description: 
published: true
date: 2024-12-10T04:36:14.942Z
tags: 
editor: markdown
dateCreated: 2024-09-19T15:20:00.981Z
---

# Bài toán 2-SAT

**Tác giả**:

- Trần Quang Trường - Trường Đại học Công Nghệ Thông tin, ĐHQGHCM

**Reviewer:**
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành - Kon Tum
- Đoàn Gia Huy - HUS High School for Gifted Students
- Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN

## Kiến thức cần biết

Trước khi đọc bài viết này, bạn cần trang bị kiến thức về các chủ đề sau:
- [Sắp xếp Topo](/algo/graph-theory/topological-sort.md)
- [Cây DFS và ứng dụng tìm thành phần liên thông mạnh](/algo/graph-theory/Depth-First-Search-Tree.md)

## Củng cố kiến thức

Để hiểu rõ các kí hiệu và định nghĩa được sử dụng trong bài viết, chúng ta sẽ cùng tìm hiểu một số vấn đề sau:

### Mệnh đề
Mệnh đề hay mệnh đề logic được định nghĩa là một câu khẳng định về một vấn đề nào đó. Một mệnh đề có thể là đúng [$\tt{True}$, $\tt{1}$] hoặc sai [$\tt{False}$, $\tt{0}$], không thể vừa đúng, vừa sai.

Ví dụ: 
+ "$\tt{1 + 1 = 2}$" là một mệnh đề đúng. "$\tt{1 + 1 = 2}$" $= \tt{True}$
+ "$\tt{1 + 1 = 3}$" là một mệnh đề sai. "$\tt{1 + 1 = 3}$" $= \tt{False}$

### Các phép toán logic

#### Phép phủ định
Mệnh đề phủ định của mệnh đề $A$ được định nghĩa là mệnh đề có giá trị đối lập với mệnh đề $A$, kí hiệu $\lnot A$.


#### Phép hội

Kí hiệu phép hội của mệnh đề $A, B$ là $A \land B$.
Mệnh đề $A \land B$ sẽ **đúng** nếu $A, B$ đều đúng, và **sai** trong các trường hợp còn lại.

#### Phép tuyển
Kí hiệu phép tuyển của mệnh đề $A, B$ là $A \lor B$.
Mệnh đề $A \lor B$ sẽ **sai** nếu $A, B$ đều sai, và **đúng** trong các trường hợp còn lại.


#### Phép kéo theo 
Kí hiệu "$A$ kéo theo $B$" là  $A \Rightarrow B$.
Mệnh đề $A \Rightarrow B$ sẽ **sai** nếu $A$ đúng và $B$ sai, và **đúng** trong các trường hợp còn lại.


#### Phép tương đương 
Kí hiệu "$A$ tương đương $B$" là  $A \Leftrightarrow B$.
Mệnh đề $A \Leftrightarrow B$ sẽ **đúng** nếu $A, B$ đều đúng hoặc đều sai, và **sai** trong các trường hợp còn lại.

#### Bảng chân trị
<!-- |$A$|$B$|$\lnot A$|$\lnot B$|$A \land B$|$A \lor B$|$A \Rightarrow B$|$A \Leftrightarrow B$|
|---|---|---|---|---|---|---|---|
|$\tt{True}$|$\tt{True}$|$\tt{False}$|$\tt{True}$|$\tt{True}$|$\tt{True}$|$\tt{True}$|
|$\tt{True}$|$\tt{False}$|$\tt{False}$|$\tt{False}$|$\tt{True}$|$\tt{False}$|$\tt{False}$|
|$\tt{False}$|$\tt{True}$|$\tt{True}$|$\tt{False}$|$\tt{True}$|$\tt{True}$|$\tt{False}$|
|$\tt{False}$|$\tt{False}$|$\tt{True}$|$\tt{False}$|$\tt{False}$|$\tt{True}$|$\tt{True}$| -->
|$A$|$B$|$\lnot A$|$\lnot B$|$A \land B$|$A \lor B$|$A \Rightarrow B$|$A \Leftrightarrow B$|
|---|---|---|---|---|---|---|---|
|$\tt{1}$|$\tt{1}$|$\tt{0}$|$\tt{0}$|$\tt{1}$|$\tt{1}$|$\tt{1}$|$\tt{1}$|
|$\tt{1}$|$\tt{0}$|$\tt{0}$|$\tt{1}$|$\tt{0}$|$\tt{1}$|$\tt{0}$|$\tt{0}$|
|$\tt{0}$|$\tt{1}$|$\tt{1}$|$\tt{0}$|$\tt{0}$|$\tt{1}$|$\tt{1}$|$\tt{0}$|
|$\tt{0}$|$\tt{0}$|$\tt{1}$|$\tt{1}$|$\tt{0}$|$\tt{0}$|$\tt{1}$|$\tt{1}$|

### Dạng chuẩn hội (CNF)
Dạng chuẩn hội (CNF) hay Conjunctive Normal Form là hội ($\land$) của một hoặc nhiều mệnh đề. Các mệnh đề này có dạng là tuyển ($\lor$) của các giá trị ($\tt{True} / \tt{False}$).
Ví dụ: 
- $x_1 \land (x_2 \lor \lnot x_3)$ là một dạng chuẩn hội. Với:
    - $x_1, (x_2 \lor \lnot x_3)$ là các mệnh đề.
    - $x_1, x_2, x_3$ là các giá trị.

### Bài toán SAT
SAT hay Boolean satisfiability problem là một bài toán kiểm tra tồn tại cách gán $\tt{True}/\tt{False}$ cho một tập giá trị, sao cho thoả mãn CNF cho trước.
Ví dụ: 
+ Cho dạng chuẩn hội $C = (x_1 \lor \lnot x_2) \land (x_1 \lor x_2 \lor x_3)$
+ Với cách gán $x_1 = \tt{False}$, $x_2 = \tt{False}$, $x_3 = \tt{True}$. $C = (\tt{False} \lor \tt{True}) \land (\tt{False} \lor \tt{False} \lor \tt{True})$ $= \tt{True} \land \tt{True}$ $= \tt{True}$ $\Rightarrow$ Thoả mãn CNF.
+ Với cách gán $x_1 = \tt{False}$, $x_2 = \tt{False}$, $x_3 = \tt{False}$. $C = (\tt{False} \lor \tt{True}) \land (\tt{False} \lor \tt{False} \lor \tt{False})$ $= \tt{True} \land \tt{False}$ $= \tt{False}$ $\Rightarrow$ Không thoả mãn CNF.

Bài Toán SAT là một bài toán thuộc lớp [NP-complete](https://en.wikipedia.org/wiki/NP-completeness). Hiện tại chưa có bất cứ thuật toán hiệu quả nào để giải quyết bài toán SAT.

#### Một số điều kiện thường gặp
**1. Ít nhất một giá trị là $\tt{True}$:** $C = (u \lor v)$
**2. 2 giá trị  trái dấu:** $C = (u \lor v) \land (\lnot u \lor \lnot v)$
**3. 2 giá trị cùng dấu:** $C = (\lnot u \lor v) \land (u \lor \lnot v)$
**4. Bắt buộc một giá trị mang giá trị $\tt{True}$:** $C = (u \lor u)$
**5. Bắt buộc một giá trị mang giá trị $\tt{False}$:** $C = (\lnot u \lor \lnot u)$

## Bài toán 2-SAT
Bài toán 2-SAT là một nhánh nhỏ của bài toán SAT, với sự khác biệt nằm ở các mệnh đề của CNF khi lúc này có **chính xác $2$ giá trị** (2-CNF). 

Nhờ ràng buộc này, ta có thể giải quyết bài toán trong thời gian đa thức. Cụ thể hơn, ta sẽ đi vào bài toán 2-SAT:

+ Cho số nguyên $n\ (1 \le n \le 5 \cdot 10^5)$ và tập giá trị $a_1, a_2, \ldots, a_n$ , và dạng chuẩn hội 2-CNF có dạng $C = (u_1 \lor v_1) \land (u_2 \lor v_2) \land \cdots \land (u_m \lor v_m)$ $-$ Với $u_j, v_j$ $(1 \le j \le m \le 5 \cdot 10^5)$ là các giá trị $a_i$ hoặc $\lnot a_i$ $(1 \le i \le n)$.
+ Tìm cách gán $\tt{True/False}$ cho tập $a_1, a_2, \ldots, a_n$ thoả mãn 2-CNF đã cho.
### Quy ước
+ $u \to v$: Tồn tại cung $(u, v)$.
+ $u \twoheadrightarrow v$ : Tồn tại đường đi từ $u$ tới $v$.
+ TPLTM: Thành phần liên thông mạnh
+ $child(u) = \{v\ |\ u \neq v,\ u \twoheadrightarrow v\}$
+ $par(u) = \{v\ |\ u \neq v,\ v \twoheadrightarrow u\}$
+ $scc(u)$: tập tất cả các đỉnh cùng thuộc một TPLTM chứa $u$.

### Ý tưởng

Ta sẽ xây dựng **đồ thị có hướng** với các cung là các mệnh đề chứa phép kéo theo, và các đỉnh là các giá trị.

Xét một mệnh đề $(u, v) \in C$ bất kỳ:

Theo [quy tắc suy luận](https://en.wikipedia.org/wiki/Material_implication_(rule_of_inference)), ta biết rằng, $(u \lor v) \Leftrightarrow (\lnot u \Rightarrow v)$. Như vậy, ta sẽ thêm cung $(\lnot u, v)$ vào đồ thị.
Ngoài ra, ta cũng phải thêm cung $(\lnot v, u)$ vào đồ thị:
+ $(u \lor v) \Leftrightarrow (v \lor u)$ (Tính chất giao hoán)
+ $(v \lor u) \Leftrightarrow (\lnot v \Rightarrow u)$ (Quy tắc suy biến)

### Thuật toán

Viết lại bài toán sau khi xây dựng đồ thị:

Cho đồ thị $G = (V, E)$, trong đó:

+ $G =
  \begin{cases}
      V = \{a_i,\lnot a_i\ |\ 1 \le i \le n\}\\
      E = \{(\lnot u_j, v_j), (\lnot v_j, u_j)\ |\ 1 \le j \le m\}
  \end{cases}$

Tìm cách gán $\tt{True/False}$ cho tập các đỉnh sao cho thoả mãn **$2$ điều kiện**:
+ **Điều kiện 1:** $2$ đỉnh $a_j, \lnot a_j$ phải trái dấu nhau.
+ **Điều kiện 2:** Với $u = \tt{True}$ và $(u, v) \in E$ thì $v = \tt{True}$. 

> Nhận xét: Các đỉnh cùng thuộc TPLTM phải mang cùng giá trị.


<details>
<summary>
    Chứng minh
    </summary>

Để chứng minh, ta cần có các nhận định sau:
+ **Nhận định 1:** Nếu $u = \tt{True}$ thì $\forall v \in child(u)$ ta có $v = \tt{True}$.
+ **Nhận định 2:** Nếu $u = \tt{False}$ thì $\forall v \in par(u)$, ta có $v = \tt{False}$

Khi $u = \tt{True}$ thì $\forall v \in scc(u)$ ta có $u \twoheadrightarrow v \Rightarrow v \in child(u) \Rightarrow v = \tt{True}$. 
Khi $u = \tt{False}$ thì $\forall v \in scc(u)$ ta có $v \twoheadrightarrow u \Rightarrow v \in par(u) \Rightarrow v = \tt{False}$. 
Do đó, với các đỉnh cùng thuộc TPLTM phải mang cùng giá trị $\tt{True/False}$.
</details>

Với nhận xét trên, trước tiên ta sử dụng thuật toán tìm TPLTM như Kosaraju hay Tarjan. Tuy nhiên trong bài viết, ta sẽ chỉ bàn tới **thuật toán Tarjan**. Sau đó, ta sẽ coi mỗi TPLTM như một đỉnh, từ đó thu được một đồ thị có hướng không chu trình (DAG). 

Sau khi thực hiện thuật toán Tarjan, ta sẽ xác định được mảng $id[u]$ $-$ Vị trí của $scc(u)$ trong thứ tự **Tô-pô ngược** bất kỳ (Đối với thuật toán Kosaraju, mảng $id[u]$ là vị trí $scc(u)$ trong thứ tự Tô-pô xuôi bất kỳ):
+ Nếu $id[u] = id[v]$ thì $u, v$ cùng thuộc TPLTM. 
+ Nếu $id[u] \lt id[v]$ thì $scc(u)$ nằm bên trái $scc(v)$ trong thứ tự Tô-pô ngược.
+ Nếu $id[u] \gt id[v]$ thì $scc(u)$ nằm bên phải $scc(v)$ trong thứ tự Tô-pô ngược.
+ Nếu $u \twoheadrightarrow v$ thì $id[u] \ge id[v]$.
 
Với mỗi giá trị $u \in \{ a_1, a_2, \ldots, a_m \}$, ta xét:
+ Nếu $id[u] = id[\lnot u]$ thì thông báo bài toán vô nghiệm và kết thúc.
+ Nếu $id[u] \lt id[\lnot u]$ thì gán $u = \tt{True}$ và $\lnot u = \tt{False}$.
+ Nếu $id[u] \gt id[\lnot u]$ thì gán $u = \tt{False}$ và $\lnot u = \tt{True}$.

### Chứng minh
#### Bổ đề

Trước khi chứng minh tính đúng đắn của thuật toán, ta cần chứng minh bổ đề sau: 
+ *Nếu $u \twoheadrightarrow v$ thì $\lnot v \twoheadrightarrow \lnot u$. Với $u, v \in V$.*

Chứng minh bổ đề: Do $u \twoheadrightarrow v$ ta có đường đi $u \to x_1 \to x_2 \to \cdots \to x_k \to v$. Mặt khác, theo cách xây dựng đồ thị $G$ ta biết rằng nếu $G$ có cung $(u, v)$ thì sẽ có cung $(\lnot v, \lnot u)$. Nên từ đường đi trên ta suy ra $G$ có đường đi $\lnot v \to \lnot x_k \to \cdots \to \lnot x_2 \to \lnot x_1 \to \lnot u$, vậy nên $\lnot v \twoheadrightarrow \lnot u$.

#### Chứng minh tính đúng đắn của thuật toán

Ta sẽ chứng minh các đỉnh của đồ thị $G$ được gán giá trị theo thuật toán nêu trên sẽ thoả mãn $2$ điều kiện của bài toán.

+ ***Chứng minh điều kiện 1: Nếu $u$ và $\lnot u$ cùng thuộc TPLTM thì bài toán vô nghiệm.***
    Dễ dàng nhận thấy nếu $u$ và $\lnot u$ cùng thuộc TPLTM thì $u$ và $\lnot u$ phải mang cùng giá trị, mâu thuẫn với **điều kiện 1** của bài toán. Ta nói bài toán vô nghiệm.

+ ***Chứng minh điều kiện 2: Nếu $u = \tt{True}$ và $(u, v) \in E$ thì $v = \tt{True}$.***
    Ta sẽ chứng minh bằng phản chứng, giả sử tồn tại $u = \tt{True}$ và $(u, v) \in E$ mà $v = \tt{False}$: 
    + Do $u = \tt{True}$ nên $id[\lnot u] \gt id[u]$. Do $v = \tt{False}$ nên $id[v] \gt id[\lnot v]$. Ngoài ra, vì $u \to v$ nên $id[\lnot u] \gt id[u] \ge id[v] \gt id[\lnot v]$. 
    + Mặt khác, theo cách xây dựng đồ thị $G$, ta cũng phải có $\lnot v \to \lnot u \Leftrightarrow id[\lnot v] \ge id[\lnot u]$ và điều này mâu thuẫn điều kiện trên (Giả thiết được chứng minh là sai).
    
    $\Rightarrow$ Nếu $u = \tt{True}$ và $(u, v) \in E$ thì $v = \tt{True}$.

### Cài đặt
```cpp=
#include <bits/stdc++.h>

using namespace std;

const int maxN = 500500;

int n, m;

// Lưu đồ thị G
vector<int> G[maxN << 1];

// Lấy giá trị phủ định của x
int NOT(int x) { 
    return x + (x <= n ? n : -n); // -x
}

// Thêm điều kiện u OR v
void add_clause(int u, int v) {
    G[NOT(u)].push_back(v); // -u -> v
    G[NOT(v)].push_back(u); // -v -> u
}

// Tìm thành phần liên thông mạnh
int id[maxN << 1];
int num[maxN << 1], low[maxN << 1];
int timeDFS = 0, scc = 0;
int st[maxN << 1]; 

void dfs(int u) {
    num[u] = low[u] = ++timeDFS;
    st[++st[0]] = u;
    for(const int& v : G[u]) {
        if(id[v] != 0) continue; 
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }

    if(num[u] == low[u]) {
        for(++scc; true; ) {
            int v = st[st[0]--];
            id[v] = scc;
            if(v == u) break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        add_clause(u, v);
    }

    // Thuật toán Tarjan
    for(int i = 1; i <= 2 * n; ++i) {
        if(!id[i]) dfs(i);
    }

    bool answer = 1;
    for(int i = 1; i <= n; ++i) {
        // Kiểm tra điều kiện tồn tại phương án
        if(id[i] == id[NOT(i)]) answer = 0;
    }
    if(!answer) { 
        cout << "IMPOSSIBLE"; // Thông báo bài toán vô nghiệm
        return 0;
    }
    // In tập giá trị a1, a2, ..., an
    for(int i = 1; i <= n; ++i) cout << (id[i] < id[NOT(i)]) << " ";
    return 0;
}
```

### Phân tích

Độ phức tạp để thực hiện thuật toán Tarjan cũng như cả bài toán là $O(n + q)$

## Bài tập

### [Thi tuyển dụng](https://oj.vnoi.info/problem/bedao_oi4_d)

#### Đề bài

Cho số $n$ là độ dài dãy nhị phân và $q$ tính chất $(3 \le n, q \le 10^5)$. Mỗi tính chất có dạng $i_1, v_1, i_2, v_2, i_3, v_3$ $(1 \le i_1, i_2, i_3 \le n, 0 \le v_1, v_2, v_3 \le 1)$ với ý nghĩa:
+ Giá trị của bit thứ $i_1$ là $v_1$.
+ Giá trị của bit thứ $i_2$ là $v_2$.
+ Giá trị của bit thứ $i_3$ là $v_3$.

Một tính chất gọi là được thoả mãn nếu **ít nhất hai trong ba điều kiện trên là đúng**.

In ra $-1$ nếu không tồn tại dãy nhị phân thoả mãn được tất cả tính chất. Ngược lại, In ra một dãy nhị phân thoả mãn.

#### Phân tích

Với mỗi tính chất:
+ Gọi $u_t$ là một đỉnh thuộc đồ thị. Nếu $v_t = 1$, $u_t = i_t$. Ngược lại, $u_t = \lnot i_t$.
+ Ta cần thoả ít nhất $2$ trong $3$ điều kiện, theo quy tắc suy luận ta có CNF: 
$C = (u_1 \lor u_2) \land (u_1 \lor u_3) \land (u_2 \lor u_3)$

Sử dụng **thuật toán 2-SAT**, ta giải quyết bài toán trong $O(n + q)$.

#### Cài đặt


<details>
<summary>
    Code mẫu (C++)</summary>

```cpp=
#include <bits/stdc++.h>

using namespace std;

const int maxN = 100100;

int n, q;

vector<int> G[maxN << 1];

int NOT(int x) { 
    return x + (x <= n ? n : -n); 
}

void add_clause(int u, int v) {
    G[NOT(u)].push_back(v); 
    G[NOT(v)].push_back(u); 
}

int id[maxN << 1];
int num[maxN << 1], low[maxN << 1];
int timeDFS = 0, scc = 0;
int st[maxN << 1]; 

void dfs(int u) {
    num[u] = low[u] = ++timeDFS;
    st[++st[0]] = u;
    for(const int& v : G[u]) {
        if(id[v] != 0) continue; 
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }

    if(num[u] == low[u]) {
        for(++scc; true; ) {
            int v = st[st[0]--];
            id[v] = scc;
            if(v == u) break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    if(ifstream("recruit.inp")) {
        freopen("recruit.inp", "r", stdin);
        freopen("recruit.out", "w", stdout);
    }

    cin >> n >> q;
    for(int i = 1; i <= q; ++i) {
        vector<int> val;
        for(int j = 0; j < 3; ++j) {
            int u, v; cin >> u >> v;
            if(v == 0) u = NOT(u);
            val.push_back(u);
        }
        add_clause(val[0], val[1]);
        add_clause(val[0], val[2]);
        add_clause(val[1], val[2]);
    }

    for(int i = 1; i <= 2 * n; ++i) {
        if(!id[i]) dfs(i);
    }

    bool answer = 1;
    for(int i = 1; i <= n; ++i) {
        if(id[i] == id[NOT(i)]) answer = 0;
    }
    if(!answer) { 
        cout << "-1";
        return 0;
    }
    for(int i = 1; i <= n; ++i) cout << (id[i] < id[NOT(i)]);
    return 0;
}
```
</details>

### [Thống nhất đất nước](https://oj.vnoi.info/problem/elect)

#### Đề bài

Trong tình trạng đói nghèo, người dân khổ cực trăm bề. Nhận thức được điều đó, các Đảng trong nước $X$ quyết định họp bàn nhau lại, bỏ qua hiềm khích để xây dựng lại đất nước. Việc đầu tiên sẽ là họp để chọn ra các vị đại biểu để lập nên Quốc Hội. Mỗi Đảng đề cử một ứng viên để ứng cử Quốc Hội và hiện tại mỗi Đảng đều có $2$ gương mặt tiêu biểu nhất để ứng cử vị trí đó. Tuy nhiên vì lý do cá nhân trong chiến tranh nên rất căm thù nhau (ví dụ như là ông $A$ của Đảng $P$ ghét ông $B$ của Đảng $Q$ ...). Để đảm bảo Quốc Hội làm việc $1$ cách công minh thì các vị đại biểu Quốc Hội phải được chọn ra sao cho đảm bảo không có ai thù ghét ai cả nếu không rất có thể chiến tranh sẽ lại nổ ra. Bạn hãy xem xét xem liệu có $1$ cách tổ chức Quốc Hội sao cho thoả mãn được các yêu cầu đề ra hay không?

##### Input
Dòng 1: 2 số nguyên $N$ và $M$ $(1 \le N \le 8000, 1 \le M \le 20000)$ tương ứng là số Đảng và só mối quan hệ thù ghét nhau giữa các thành viên của các Đảng. (Các thành viên của Đảng $1$ có số hiệu là $1, 2$; các thành viên của Đảng $2$ có số hiệu là $3, 4$... Thành viên của Đảng $i$ sẽ có số hiệu là $2i - 1$ và $2i$).

$M$ dòng tiếp theo mỗi dòng gồm $2$ số nguyên $u, v$ cho biết người $u$ và người $v$ ghét nhau. $(1 \le u \le v \le 2N)$.

##### Output
Dòng 1: Ghi $0$ nếu không có phương án thoả mãn và $1$ nếu có phương án thoả mãn.

Nếu dòng 1 là $1$ thì dòng thứ 2 ghi ra $N$ số nguyên là số hiệu của các thành viên được chọn vào Quốc Hội.

#### Phân tích

Với mỗi mối quan hệ thù ghét $(u, v)$:
+ Vì $u, v$ không thể cùng lúc có mặt trong Quốc Hội nên ta có $C = (\lnot u \lor \lnot v)$.

Với $2$ đại diện $(a, b)$ của mỗi Đảng: 
+ Vì có thể có mặt $a$ hoặc $b$ trong Quốc hội nên ta có $C = (a \lor b) \land (\lnot a \lor \lnot b)$.

Sử dụng **thuật toán 2-SAT**, ta giải quyết bài toán trong $O(N + Q)$

#### Cài đặt
<details>
<summary>
    Code mẫu (C++)
    </summary>

```cpp=
#include <bits/stdc++.h>

using namespace std;

const int maxN = 16004;

int n, m;

vector<int> G[maxN << 1];

int NOT(int x) { 
    return x + (x <= n ? n : -n);
}

void add_clause(int u, int v) {
    G[NOT(u)].push_back(v);
    G[NOT(v)].push_back(u);
}

int id[maxN << 1];
int num[maxN << 1], low[maxN << 1];
int timeDFS = 0, scc = 0;
int st[maxN << 1]; 

void dfs(int u) {
    num[u] = low[u] = ++timeDFS;
    st[++st[0]] = u;
    for(const int& v : G[u]) {
        if(id[v] != 0) continue; 
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }

    if(num[u] == low[u]) {
        for(++scc; true; ) {
            int v = st[st[0]--];
            id[v] = scc;
            if(v == u) break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    n = n << 1;

    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        add_clause(NOT(u), NOT(v));
    }
    
    for(int i = 1; i <= n; i += 2) {
        add_clause(i, i + 1);
        add_clause(NOT(i), NOT(i + 1));
    }

    for(int i = 1; i <= 2 * n; ++i) {
        if(!id[i]) dfs(i);
    }

    bool answer = 1;
    for(int i = 1; i <= n; ++i) {
        if(id[i] == id[NOT(i)]) answer = 0;
    }
    if(!answer) { 
        cout << "0";
        return 0;
    }
    cout << "1\n";
    for(int i = 1; i <= n; ++i) 
        if(id[i] < id[NOT(i)]) cout << i << " ";
    return 0;
}
```
</details>

## Luyện tập
+ [CSES - Giant Pizza](https://cses.fi/problemset/task/1684)
+ [VNOJ - Du lịch](https://oj.vnoi.info/problem/twosat)
+ [SPOJ - BUGLIFE](https://www.spoj.com/problems/BUGLIFE/)
+ [SPOJ - TORNJEVI](https://www.spoj.com/problems/TORNJEVI/)
+ [CF - Ants](https://codeforces.com/problemset/problem/1007/D)
+ [CF - Catowice City](https://codeforces.com/contest/1239/problem/D)
+ [CF - The Door Problem](https://codeforces.com/contest/776/problem/D)
+ [Atcoder - Coprime Solitaire](https://atcoder.jp/contests/abc210/tasks/abc210_f)

## Tham khảo
Bài viết được dựa trên các bài viết sau:
+ [2-SAT Problem - 2010 - Phạm Lê Quang](https://drive.google.com/file/d/15UbO4GWo1G6cUBDnV6uWk0KxjuEdurCG/view)
+ [[Tutorial] 2-SAT - arujbansal](https://codeforces.com/blog/entry/92977)
