---
title: Persistent Data Structures
description: 
published: true
date: 2025-02-19T11:23:02.127Z
tags: 
editor: markdown
dateCreated: 2025-02-19T11:23:02.127Z
---

# Persistent Data Structures

- **Tác giả:**
	- Nguyễn Quang Minh - HUS High School for Gifted Students
  
- **Reviewer:**
	- Đoàn Gia Huy - HUS High School for Gifted Students
  - Nguyễn Đức Kiên - Đại học Công nghệ, Đại học Quốc gia Hà Nội
  - Nguyễn Minh Nhật - HUS High School for Gifted Students
  - Nguyễn Tấn Minh - THPT Chuyên Lê Hồng Phong, TPHCM

## Kiến thức cần biết
*Note:* Để hiểu được bài viết này, các bạn cần có kiến thức về:
- [Segment tree](https://wiki.vnoi.info/algo/data-structures/segment-tree-extend)


## Persistent Segment Tree

### Bài toán

Xét bài toán sau đây:
Cho một dãy $A_1, A_2, ..., A_N$ gồm $N$ phần tử, và ta cần làm $2$ loại thao tác sau đây:
- $1 \space i \space k$: Cập nhật $A_i := k$ 
- $2 \space l \space r \space k$: Hỏi tổng đoạn $(l, r)$ sau thao tác thứ $k$.

Lưu ý rằng chúng ta cần làm bài toán này online - cần đưa ra đáp án ngay sau khi được hỏi.

### Lời giải

Nếu bỏ cụm từ "sau thao tác thứ $k$" thì đây là một bài ứng dụng segment tree cơ bản. Tuy nhiên bài này yêu cầu chúng ta lưu lại lịch sử những lần update. 

Chúng ta có thể sử dụng Persistent Data Structures để giải bài toán này. Lưu ý rằng đây không phải là một cấu trúc dữ liệu mới, mà là một kĩ thuật giúp chúng ta lưu lại thông tin về lịch sử của cấu trúc dữ liệu. 

Ví dụ như dưới đây chúng ta vẫn dùng Segment Tree nhưng có thêm một số thay đổi để có thể lưu lại những trạng thái cũ của dãy trước khi thay đổi, và thêm vào trạng thái mới nhất của dãy. 

Ta xử lý bài toán trên như sau:
- Phần persistent: Với mỗi lần cập nhật, ta tạo ra $O(\log(n))$ node lưu giá trị mới của các node được cập nhật. Ngoài ra chúng ta lưu lại node $root$ - gốc của mỗi bản cập nhật - để tiện cho việc truy vấn. 
- Nhận thấy rằng mỗi khi update ta thay đổi đường đi từ gốc đến một lá, nên không xảy ra việc node con lưu giá trị tại thời điểm $k$ mà node cha lại không lưu.
- Khi ta hỏi giá trị của đoạn sau thời điểm $k$, ta bắt đầu đi tìm từ root tương ứng với truy vấn $k$ và làm như bình thường

Ta thấy rằng chúng ta chỉ thay đổi giá trị của một phần tử trong Segment Tree $O(n \times \log(n))$ lần, và do đó độ phức tạp của thuật toán này là $O(q \times \log(n))$

### Code mẫu

```cpp= 
const long long infty = 1e18 + 7;
const int MAXN = 3e5 + 5;

int n;

int a[MAXN];
// val: giá trị của node i
// le, ri: các node con của node i
// con số 20 ở đây đại diện cho log2(N), và những mảng có kích thước N * 20 là những mảng cần N * log2(N) memory
long long val[MAXN * 20];
int le[MAXN * 20], ri[MAXN * 20];

// rood_idx[i]: node gốc được tạo ra ở query thứ i
int root_idx[MAXN];

// cur[id]: node chứa version mới nhất của node id trong segment tree ban đầu
int cur[MAXN * 20];

// tol_node lưu tổng số node hiện tại
int tolnode;

long long init(int id, int l, int r){
    tolnode++;
    // version ban đầu của node id là node id :)
    cur[id] = id;
    if(l == r){
        val[id] = a[l];
        return a[l];
    }
    le[id] = (id << 1), ri[id] = (id << 1 | 1);
    int mid = (l + r) >> 1;
    // tính tổng đoạn (l, r)
    long long sum = init(id << 1, l, mid) + init(id << 1 | 1, mid + 1, r);
    val[id] = sum;
    return sum;
}


void upd(int id, int l, int r, int pos, long long v){
    if(l == r){
        tolnode++;
        val[tolnode] = v;
        return;
    }
    tolnode++;
    int nw_id = tolnode;
    // trạng thái mới nhất của node id trở thành nw_id
    cur[id] = nw_id;
    int mid = (l + r) >> 1;
    // Trong TH này, ta sẽ tạo ra một node mới là con bên trái của node hiện tại, và node con bên phải sẽ là cur[id << 1 | 1]
    if(pos <= mid){
        upd(id << 1, l, mid, pos, v);
        // lưu ý rằng index của node con sẽ được tạo ra ngay sau node này nên index của nó là nw_id + 1
        le[nw_id] = nw_id + 1;
        ri[nw_id] = cur[id << 1 | 1];
        val[nw_id] = val[le[nw_id]] + val[ri[nw_id]];
    }
    // Trong TH này, ta sẽ tạo ra một node mới là con bên phải của node hiện tại, và node con bên trái sẽ là cur[id << 1]
    else{
        upd(id << 1 | 1, mid + 1, r, pos, v);
        le[nw_id] = cur[id << 1];
        ri[nw_id] = nw_id + 1;
        val[nw_id] = val[le[nw_id]] + val[ri[nw_id]];
    }
}

// gọi k là thời điểm hỏi
// id ở đây, thay vì là id của segment tree ban đầu, thì là cur[id] ở thời điểm k

long long get(int id, int l, int r, int L, int R){
    if(R < l || r < L) return 0;
    if(l >= L && r <= R) return val[id];
    int mid = (l + r) >> 1;
    return get(le[id], l, mid, L, R) + get(ri[id], mid + 1, r, L, R);
}

// lưu thời điểm của lần thay đổi hiện tại
int cnt_que;

void update(int p, long long v){
    cnt_que++;
    root_idx[cnt_que] = tolnode + 1;
    upd(1, 1, n, p, v);
}

// ta bắt đầu tại root_idx[k]
long long ans(int l, int r, int k){
    return get(root_idx[k], 1, n, l, r);
}
```

## Persistent BIT

### Bài toán

Xét phiên bản 2D của bài toán trên

Cho một bảng $A_{1, 1}, A_{1, 2}, ..., A_{N, M}$ gồm $N \times M$ phần tử, và ta cần làm $2$ loại thao tác sau đây:
- $1 \space i \space k$: Cập nhật $A_{i, j} := A_{i, j} + k$ 
- $2 \space x_1 \space y_1 \space x_2 \space y_2 \space k$: Hỏi tổng các phần tử trong hình chữ nhật con có góc trên trái là $(x_1, y_1)$ và góc dưới phải là $(x_2, y_2)$ sau thao tác thứ $k$.

### Lời giải

Việc áp dụng phương pháp tạo node mới như trên với BIT là khá khó khăn, và thay vào đó chúng ta có thể làm như dưới đây:

Với mỗi node trong BIT ta sẽ lưu lại lịch sử những lần thay đổi của node này.
- Ta lưu với mỗi phần tử trên BIT một vector $updates$. Mỗi lần cập nhật phần tử $(i, j)$ thêm $val$ ở truy vấn thứ $t_i$, ta thêm vào $updates[i][j]$ cặp $(t_i, val + last)$ với $last$ là giá trị của phần tử $(i, j)$ trước lần cập nhật này.
- Khi được hỏi, với mỗi node ta chặt nhị phân trên tập updates để tìm phần tử có $t_i$ lớn nhất sao cho $t_i \leq k$.

### Code mẫu: 
```cpp=
// y1 là tên một biến trong C++ nên mình sử dụng tạm cách này
// tuy nhiên không khuyến khích mọi người làm theo
#define y1 y11 

const long long infty = 1e18 + 7;
const int MAXN = 3e3 + 5;

// kích thước bảng
int N, M;

int a[MAXN][MAXN];

vector<pair<int, long long>> updates[MAXN][MAXN];

// tính giá trị ban đầu
long long pref[MAXN][MAXN];
int range[MAXN];
void init(){
    // xác định khoảng mà vị trí i quản lý trong BIT
    for(int i = 1; i <= max(N, M); i++){
        range[i] = (i & (i - 1)) + 1;
    }    
    // ta dùng prefix sum để có được ĐPT O(n * m)
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++) pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            int x1 = range[i], y1 = range[j], x2 = i, y2 = j;
            long long startval = pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
            updates[i][j].push_back({0, startval});
        }
    }
}

void upd(int x, int y, int k, long long val){
    for(int i = x; i <= N; i += i & -i){
        for(int j = y; j <= M; j += j & -j){
            // giá trị gần nhất của phần tử (i, j)
            long long lst = updates[i][j].back().second;
            lst += val;
            updates[i][j].push_back(make_pair(k, val));
        }
    }
}

// hàm get() sẽ tính giá trị của hcn con (1, 1), (x, y)
long long get(int x, int y, int k){
    long long ans = 0;
    for(int i = x; i; i -= i & -i){
        for(int j = y; j; j -= j & -j){
            // ta lower_bound cặp (k, oo) để chắc chắn ra được vị trí nhỏ nhất có thời gian > k, và sau đó ta -1 để ra vị trí cần tìm.
            int pos = lower_bound(updates[i][j].begin(), updates[i][j].end(), make_pair(k, infty)) - updates[i][j].begin() - 1;
            ans += updates[i][j][pos].second;
        }
    }
    return ans;
}

long long ans(int x1, int y1, int x2, int y2, int k){
    return get(x2, y2, k) - get(x1 - 1, y2, k) - get(x2, y1 - 1, k) + get(x1 - 1, y1 - 1, k);
}
```

Độ phức tạp của thuật toán này là:

- Về mặt thời gian:
    - $O(N \times M)$ cho việc khởi tạo bảng
    - $O(\log(N) \times \log(M))$ cho mỗi truy vấn update
    - $O(\log(N) \times \log(M) \times \log(Q))$ cho mỗi truy vấn hỏi.

- Về mặt không gian: $O(N \times M + Q \times log(N) \times log(M))$
    - $O(N \times M)$ là số vector mà ta tạo ra để lưu lại các truy vấn
    - $Q \times log(N) \times log(M)$ là tổng số lần ta cập nhật các vector

Cách làm này tuy độ phức tạp cao hơn nhưng lại tổng quát hơn khi có thể dùng cho BIT, IT và nhiều cấu trúc dữ liệu khác.

## Bài tập

- [SPOJ - COT](http://www.spoj.com/problems/COT/)
- [SPOJ - MKTHNUM](http://www.spoj.com/problems/MKTHNUM/)
- [Codechef - QUERY](https://www.codechef.com/problems/QUERY)
- [Codechef - SORTING](https://www.codechef.com/problems/SORTING)
- [Codeforces - Round 140 Div 1 - E](http://codeforces.com/problemset/problem/226/E)
- [Codeforces - Round 265 Div 1 - E](http://codeforces.com/contest/464/problem/E)
- [IPSC 2011 - Grid Surveillance](http://ipsc.ksp.sk/2011/real/problems/g.html)