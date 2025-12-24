---
title: Disjoint Set Union Rollback
description: 
published: true
date: 2025-02-19T11:19:40.206Z
tags: 
editor: markdown
dateCreated: 2025-02-19T11:19:40.206Z
---

# Disjoint Set Union Rollback

- **Tác giả:**
	- Nguyễn Quang Minh - HUS High School for Gifted Students
  
- **Reviewer:**
	- Đoàn Gia Huy - HUS High School for Gifted Students
  - Nguyễn Đức Kiên - Đại học Công nghệ, Đại học Quốc gia Hà Nội
  - Nguyễn Minh Nhật - HUS High School for Gifted Students
  - Nguyễn Tấn Minh - THPT Chuyên Lê Hồng Phong, TPHCM

## Kiến thức cần biết
*Note:* Để hiểu được bài viết này, các bạn cần có kiến thức về:
- [Disjoint set union (DSU)](https://wiki.vnoi.info/algo/data-structures/disjoint-set-union)

## Bài toán DSU Roll-back

### Bài toán

Cho một đồ thị $N \le 2 \times 10^5$ đỉnh, và hiện tại thì chưa có cạnh nào. Có $Q (Q \le 10^5)$ truy vấn, mỗi truy vấn có dạng $type \space u \space v$ biểu thị rằng
- Nếu $type = 1$, thêm cạnh $(u, v)$ vào đồ thị
- Nếu $type = 2$, xoá cạnh $(u, v)$ ra khỏi đồ thị

Sau mỗi truy vấn, hãy in ra số thành phần liên thông trong đồ thị hiện tại.

### Lời giải

Nếu làm như bình thường (thêm/xóa cạnh rồi sau mỗi truy vấn lại BFS/DFS), thì đpt là $O((N + Q)*Q)$. 

Để có thể giải quyết bài toán với giới hạn $N, Q \le 2 \times 10^5$ như trên, ta có cách làm duới đây:

Định nghĩa việc một cạnh xuất hiện sau "thời điểm $i$" là việc cạnh này đang ở trong đồ thị sau truy vấn thứ $i$.

- Buớc 1: Tính toán với mỗi cạnh những khoảng thời gian mà nó xuất hiện trong đồ thị.
- Buớc 2: Xây dựng một Segment Tree theo thời gian: Nút gốc sẽ quản lý các thời điểm từ $1$ tới $Q$, nút $id$ (quản lý các thời điểm từ $l$ đến $r$) sẽ có $2$ nút con là nút ($id \times 2$) (quản lý các thời điểm từ $l$ đến $mid$) và nút ($id \times 2 + 1$) (quản lý các thời điểm từ $mid + 1$ đến $r$) với $mid = \left\lfloor\frac{l + r}{2}\right\rfloor$
- Buớc 3: Với một cạnh $x$ xuất hiện từ thời điểm $l_x$ tới thời điểm $r_x$, update tương tự như update đoạn $[l_x, r_x]$ trong Segment Tree. Mỗi nút của Segment Tree lưu một danh sách các cạnh đã được update vào nút. Khi đó, nút quản lý các thời điểm trong khoảng thời gian $[l, r]$ sẽ chứa tất cả các cạnh tồn tại trong toàn bộ khoảng thời gian này.
- Buớc 4: DFS xuống tất cả các nút của cây. Ở mỗi nút $id$, thêm vào những cạnh mà nút $id$ chứa. Khi xử lý xong nút $id$ và các con của nút này, xóa đi những cạnh đã thêm vào (hay còn gọi là thao tác rollback). Khi đó, mỗi khi thăm một nút lá quản lý thời điểm $[i, i]$, ta có được đáp án cho thời điểm $i$.

### Ví dụ

Xem xét ví dụ với bộ dữ liệu như sau

```
5 10

1 1 2
1 1 3
1 1 4
1 2 5
2 1 2
1 4 5
1 1 2
2 1 4
2 2 5
2 1 2
```

- Cạnh $(1, 2)$ lần lượt được thêm vào ở các thời điểm 1, 7 và bị xóa ở các thời điểm 5, 10. Điều đó có nghĩa là cạnh $(1, 2)$ tồn tại trong các khoảng thời gian $[1, 4]$ và $[7, 9]$.
- Cạnh $(1, 3)$ được thêm vào ở thời điểm $2$ và ở lại đến cuối cùng. Điều đó có nghĩa là cạnh $(1, 3)$ tồn tại trong khoảng thời gian $[2, 10]$.
- Cạnh $(1, 4)$ được thêm vào ở thời điểm $3$ và bị xóa ở thời điểm $8$. Điều đó có nghĩa là cạnh $(1, 4)$ tồn tại trong khoảng thời gian $[3, 7]$.
- Tương tự với các cạnh còn lại

Dưới đây là Segment Tree khi ta thêm cạnh $(1, 2)$ các khoảng thời gian $[1, 4]$ và $[7, 9]$ (Những đỉnh ta thêm cạnh được tô màu xanh lá cây)
![image](https://hackmd.io/_uploads/SJambv_j0.png)
![image](https://hackmd.io/_uploads/S1FLfvdiR.png)

### Code mẫu

```cpp 

struct edge
{
    int u, v;
    edge() {}
    edge(int _u, int _v) : u(_u), v(_v) {}
};
 
// những cạnh được update
int answer[MAXQ];
vector<edge> nw_edges[MAXQ << 2];
 
// root[x] là gốc của thành phần liên thông chứa đỉnh x
// sz[x] là số đỉnh trong thành phần liên thông với gốc là đỉnh x
int sz[MAXN], root[MAXN];
 
// với mỗi lần cập nhật, ta lưu lại đỉnh được thay đổi size hoặc root để lúc sau cập nhật lại
// lưu ý rằng ta không cần lưu root cũ vì root cũ cảu một đỉnh trước khi merge là chính nó
struct update
{
    int node, old_size;
    update() {}
    update(int _node, int _old_size) : node(_node), old_size(_old_size) {}
};
 
stack<update> rollback;
 
int total_rollback[MAXQ << 2]; // với mỗi đỉnh trong segment tree, ta lưu số lần cập nhật để lúc sau có thể rollback
 
int rt(int x)
{ // ta không dùng path compression và chấp nhận đpt O(log2(n)) cho mỗi lần tìm root
    return (x == root[x] ? x : rt(root[x]));
}
 
// lưu lại số tplt hiện tại
int cur_comp;
 
void merge(int id, int x, int y)
{ // chúng ta merge như bình thường
    x = rt(x);
    y = rt(y);
    if(x == y) return;
    if (sz[x] < sz[y])
        swap(x, y);
    // lưu lại size cũ của các đỉnh để rollback lại
    rollback.push({x, sz[x]});
    rollback.push({y, sz[y]});
    total_rollback[id] += 2;
    sz[x] += sz[y];
    root[y] = x;
}
 
// cập nhật một cạnh tồn tại trong khoảng (l, r)
void upd(int id, int l, int r, int L, int R, edge cur_edge)
{
    if (l > R || r < L)
        return;
    if (l >= L && r <= R)
    {
        nw_edges[id].push_back(cur_edge);
        return;
    }
    int mid = (l + r) >> 1;
    upd(id << 1, l, mid, L, R, cur_edge);
    upd(id << 1 | 1, mid + 1, r, L, R, cur_edge);
}
 
void get_ans(int id, int l, int r)
{ 
    // giả sử ta đang ở đoạn (l, r)
    // thêm vào những cạnh được lưu trong đỉnh này
    // ngoài ra lưu những node thay đổi root và size trong DSU
    for (auto e : nw_edges[id])
    {
        merge(id, e.u, e.v);
    }
    // mỗi lần merge chúng ta cộng total_rollback[id] lên 2
    cur_comp -= ((int)total_rollback[id] >> 1);
    if (l == r)
    {
        answer[l] = cur_comp; // đáp án cho query thứ l là số component hiện tại
        // lưu đáp án
    }
    // đi xuống các node con
    else{
        int mid = (l + r) >> 1;
        get_ans(id << 1, l, mid);
        get_ans(id << 1 | 1, mid + 1, r);
    }
    // update lại đáp án
    cur_comp += ((int)total_rollback[id] >> 1);
    // xóa đi những cạnh vừa được thêm vào theo thứ tự ngược lại.
    // lưu ý rằng sau khi ra khỏi node hiện tại thì ta
    // quay về trạng thái trước khi vào node
    while (total_rollback[id])
    {
        int node = rollback.top().node, old_size = rollback.top().old_size;
        rollback.pop();
        root[node] = node;
        sz[node] = old_size;
        total_rollback[id]--;
    }
}
```

Bằng cách làm như trên
- Khi xóa một cạnh, ta quay lại chính xác trạng thái trước khi thêm vào cạnh này.
- Mỗi lần ta chỉ thay đổi root của một phần tử và size của một phần tử khác. Khi undo lại thay đổi này ("rollback") ta cập nhật lại hai thông tin này. 

### Độ phức tạp của thuật toán

- Về mặt thời gian: 
    - Với mỗi truy vấn, ta mất $O(log(n))$ để cập nhật segment tree (việc cập nhật một nút mất $O(1)$).  
    - Tuy nhiên, khi nhìn lại vào code mẫu trên, ta thấy hàm $rt()$ không hề sử đặt $root[x] = rt(root[x])$ để giảm độ phức tạp thuật toán xuống như DSU thông thường. Lý do ta không làm như vậy là do ta sẽ gặp rất nhiều khó khăn trong việc thay đổi trở lại $root[x]$, thay vì chỉ cần thay đổi $root[]$ của $2$ đỉnh trong cạnh bị xoá. Vì vậy, độ phức tạp của mỗi lần DSU (cũng như mỗi lần thêm cạnh khi DFS xuống) trong thuật toán này là $O(log(n))$, và do đó tổng độ phức tạp của thuật toán là $O((n + q) \times log(n + q)^2)$

- Về mặt không gian: $O(\max(N, Q) \times log(N + Q))$, đây chính là tổng số cạnh chúng ta thêm vào các vector 

## Bài tập

- [Connected Components](https://oj.vnoi.info/problem/voscomps)
- [Codeforces - Connect and disconnect](https://codeforces.com/gym/100551/problem/A)
- [Extending Set of Points](https://codeforces.com/contest/1140/problem/F)