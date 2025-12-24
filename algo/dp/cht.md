---
title: Kĩ thuật Bao lồi (Convex Hull Trick)
description: 
published: true
date: 2024-12-24T15:15:11.019Z
tags: 
editor: markdown
dateCreated: 2024-12-24T15:06:18.818Z
---

# Kĩ thuật Bao lồi (Convex Hull Trick)
###### `VNOI_DP_Convex_Hull`

**Nguồn:** [P3G](https://wcipeg.com/wiki/Convex_hull_trick), Phan Minh Hoàng + Lê Anh Đức

**Tác giả:**
- Lê Minh Hoàng - Đại học Khoa học Tự nhiên, ĐHQG-HCM

**Reviewer:**
- Cao Thanh Hậu - Đại học Khoa học Tự nhiên, ĐHQG-HCM
- Đặng Đoàn Đức Trung - UT Austin
- Nguyễn Minh Nhật - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Nguyễn Tấn Minh - Trường THPT chuyên Lê Hồng Phong

## Giới thiệu
**Kĩ thuật bao lồi** là kĩ thuật (hoặc cấu trúc dữ liệu) dùng để tìm ra giá trị nhỏ nhất (hoặc lớn nhất) của một tập các đường thẳng $y=ax+b$ tại một giá trị cụ thể của biến độc lập $x$. Mặc dù có tên gọi gần giống với [**thuật toán bao lồi**](/translate/wcipeg/Convex-Hull) của hình học tính toán nhưng giữa chúng lại có nhiều điểm khác biệt.

Ngoài ra, có một kĩ thuật liên quan đến kĩ thuật bao lồi là [**IT đoạn thẳng**](/algo/data-structures/interval-tree-tap-doan-thang).

## Bài toán cơ bản
Cho một tập $N$ các đường thẳng có dạng $y = a_i x + b_i$ và một số lượng lớn $Q$ truy vấn.
Mỗi truy vấn gồm một số $x$ và hỏi giá trị nhỏ nhất $y$ có thể đạt được nếu ta thế $x$ vào một trong các đường thẳng đã cho.

Ví dụ, cho các đường thẳng $y=4$ (đỏ), $y=\frac{2}{3}x+\frac{4}{3}$ (xanh dương), $y=-3x+12$ (xanh lá), $y=-\frac{1}{2}x+3$ (tím) và truy vấn $x=1$ (đen). Ta phải tìm đường thẳng trả về giá trị $y$ nhỏ nhất với $x=1$.
Sau khi vẽ các đường thẳng lên hệ trục tọa độ (Hình 1), bài toán trở thành: với $x=1$ thì đường thẳng nào trả về tọa độ $y$ nhỏ nhất. Trong trường hợp này là đường màu xanh dương $y=\frac{2}{3}x+\frac{4}{3}$ với giá trị $y$ nhỏ nhất là $2$.

<!-- https://i.imgur.com/rCYJk3W.png -->
|![cht1.png](/algo/dp_/cht/cht1.png)|
|:-:|
|**Hình 1:** hình vẽ chứa 5 đường thẳng $y=4$ (đỏ), $y=\frac{2}{3}x+\frac{4}{3}$ (xanh dương), $y=-3x+12$ (xanh lá), $y=-\frac{1}{2}x+3$ (tím) và $x=1$ (đen).<br>Không tính đường thẳng $x=1$ (đen), phần thuộc bao lồi dưới là phần được vẽ bằng nét liền, còn lại (không thuộc bao lồi dưới) được vẽ bằng nét đứt.|

## Thuật toán ngây thơ
Với mỗi truy vấn trong $Q$ truy vấn, ta duyệt qua từng đường thẳng và xem thử đường thẳng nào trả về giá trị $y$ nhỏ nhất với giá trị $x$ đã cho. Nếu có $N$ đường thẳng và $Q$ truy vấn, độ phức tạp của thuật toán sẽ là $\mathcal{O}(NQ)$.
Kĩ thuật bao lồi sẽ giúp giảm độ phức tạp xuống còn $\mathcal{O}((Q+N)\log N)$, một độ phức tạp hiệu quả hơn nhiều.

## Kĩ thuật Bao lồi

### Ý nghĩa của tên kĩ thuật
Cụm từ *bao lồi* được sử dụng để chỉ *hình bao trên/dưới* (upper/lower envelope). Trong ví dụ, nếu ta chỉ xét các đoạn thẳng tối ưu của các đường thẳng (bỏ qua đường thẳng $y=4$), ta sẽ thấy những đoạn thẳng đó tạo thành một *hình bao dưới* (lower envelope), một tập các đoạn thẳng chứa tất cả điểm $y$ nhỏ nhất cho mọi giá trị của $x$ (hình bao dưới là phần được nối bằng nét liền trong hình 1). Cái tên *kĩ thuật bao lồi* xuất phát từ việc đường bao trên tạo thành một đường lồi, từ đó thành bao lồi của một tập điểm.

### Nhận xét 1
Xét hình vẽ ở trên, dễ thấy rằng đường thẳng $y=4$ sẽ không bao giờ trả về giá trị $y$ nhỏ nhất với mọi giá trị của $x$. Mỗi đường thẳng còn lại sẽ trả về giá trị $y$ nhỏ nhất nếu $x$ thuộc chính xác một đoạn liên tiếp nào đó (có thể có một biên là $+\infty$ hoặc $-\infty$).
- Đường màu xanh dương sẽ trả về giá trị $y$ nhỏ nhất với tất cả giá trị $x$ nằm bên trái giao điểm của nó với đường màu tím.
- Đường màu tím sẽ trả về giá trị $y$ nhỏ nhất với tất cả giá trị $x$ giữa giao điểm của nó với đường màu xanh dương và đường màu xanh lá.
- Đường màu xanh lá sẽ trả về giá trị $y$ nhỏ nhất với tất cả giá trị $x$ nằm bên phải giao điểm của nó với đường màu tím.

### Nhận xét 2
Một nhận xét nữa là với giá trị của $x$ càng tăng thì hệ số góc của các đường thẳng sẽ càng giảm, $\frac{2}{3}, \frac{-1}{2}, -3$. Ta có thể chứng minh điều này ngắn gọn như sau:
- Tận dụng hình 1, ta gọi đường màu tím là $d_1: y_1=a_1x+b_1$ và đường màu xanh lá là $d_2: y_2=a_2x+b_2$. Tại vị trí giao của $d_1$ và $d_2$, ta biết rằng $y_1=y_2$. Khi tăng $x$, để $y_1>y_2$ (thoả mãn như trong hình) thì rõ ràng rằng $a_1>a_2$ vì $b_1$ và $b_2$ là hằng số.

### Ý tưởng
Hai nhận xét trên giúp ta hiểu phần nào ý tưởng của thuật toán này:
- Bỏ đi các đường thẳng không "tiềm năng" như $y=4$ trong ví dụ (những đường thẳng không trả về giá trị $y$ nhỏ nhất với mọi giá trị của $x$).
- Sắp xếp $N'$ đường thẳng còn lại theo hệ số góc, ta sẽ có được một tập $N'$ đoạn thẳng với biên 2 đầu của mỗi đoạn thẳng là giao điểm của đường thẳng chứa đoạn với đường thẳng liền trước và đường thẳng liền sau. Từ đây, mỗi đường thẳng sẽ trả về giá trị $y$ nhỏ nhất nếu $x$ thuộc đoạn thẳng tương ứng.
- Dùng thuật toán tìm kiếm nhị phân cơ bản để có thể tìm kiếm đáp án cho từng truy vấn.

Tóm lại, nếu ta có một tập đường thẳng đã được sắp xếp sẵn, ta có thể dễ dàng trả lời bất kỳ truy vấn nào với độ phức tạp $\mathcal{O}(\log N)$. Bây giờ, nếu ta có thể tìm ra cách để thêm một đường thẳng vào tập **một cách hiệu quả** thì ta sẽ có được thuật toán hoàn chỉnh.

## Kĩ thuật Bao lồi: Thuật toán Offline

Trong phần này, ta giới thiệu một thuật toán đơn giản sử dụng [Stack](/algo/data-structures/Stack).
**Điều kiện áp dụng** của thuật toán là các đường thẳng phải được sắp xếp sẵn theo hệ số góc.

### Thuật toán

Đầu tiên, ta cần tiền xử lý để tập các đường thẳng được sắp xếp theo hệ số góc. Với bài toán tìm giá trị nhỏ nhất, ta cần hệ số góc được sắp xếp theo thứ tự giảm dần.

Tiếp theo, ta lần lượt thêm từng đường thẳng đã được sắp xếp vào Stack.
Khi thêm đường thẳng mới, một vài (có thể là không có) đường thẳng ở cuối Stack sẽ không còn "tiềm năng" (không trả về giá trị $y$ nhỏ nhất ở bất kỳ giá trị $x$ nào) và cần bị loại bỏ khỏi Stack (minh hoạ ở Hình 2).
Rõ ràng rằng đường thẳng cuối cùng trong Stack luôn "tiềm năng".

|![cht2.png](/algo/dp_/cht/cht2.png)|
|:-:|
|**Hình 2:** Sau khi thêm $l3$, $l2$ cần bị loại bỏ khỏi Stack vì $l2$ không còn "tiềm năng" nữa.|

Giả sử rằng không có ba đường thẳng nào trùng hay song song với nhau (có thể giải quyết một cách đơn giản). Vậy làm sao để có thể xác định rằng đường thẳng ở cuối Stack còn "tiềm năng" hay không?
Giả sử $l_1$, $l_2$ và $l_3$ lần lượt là đường thẳng áp chót (gần cuối) trong Stack, đường thẳng cuối cùng trong Stack, và đường thẳng sắp được thêm vào Stack.
Đường thẳng $l_2$ trở thành không "tiềm năng" khi và chỉ khi giao điểm của $l_1$ và $l_3$ nằm bên trái giao điểm của $l_1$ và $l_2$ (Đoạn mà $l_3$ trả về giá trị $y$ nhỏ nhất đã nằm đè lên đoạn của $l_2$).

### Phân tích thuật toán
Độ phức tạp bộ nhớ sẽ là $\mathcal{O}(N)$: ta cần một danh sách lưu lại các đoạn thẳng, biểu diễn bởi hai số thực là 2 biên của đoạn thẳng.

Độ phức tạp thời gian cho phần tiền xử lý:
- Sắp xếp các đoạn thẳng theo hệ số góc giảm dần sẽ tốn  $\mathcal{O}(N\log{N})$.
- Duyệt qua các đường thẳng, mỗi đường thẳng được thêm vào stack và bị loại bỏ khỏi Stack tối đa một lần nên sẽ tốn $\mathcal{O}(N)$ cho bước này.

Vậy độ phức tạp thời gian cho phần tiền xử lý sẽ là $\mathcal{O}(N\log{N})$.
Với mỗi truy vấn, ta dùng chặt nhị phân nên độ phức tạp thời gian là $\mathcal{O}(\log N)$.
Tổng độ phức tạp thời gian của $Q$ truy vấn là $\mathcal{O}(Q\log N)$.

### Ứng dụng

#### Ví dụ 1: [VNOJ - Phân nhóm](https://oj.vnoi.info/problem/group)

##### Bài toán
Cho $N(N \le 3\times10^5)$ hình chữ nhật khác nhau về hình dạng (có cùng góc trái dưới ở $O(0, 0)$), mục tiêu của bài toán là phải lấy được tất cả hình chữ nhật. Một tập hình chữ nhật có thể thu được với chi phí bằng tích của chiều ngang dài nhất và chiều dọc dài nhất. Ta cần phân hoạch tập các hình chữ nhật này một cách khôn khéo sao cho tổng chi phí có thể được tối thiểu hóa và tính chi phí này. Hình chữ nhật không thể được xoay (đổi chiều ngang và chiều dọc).

##### Nhận xét 1: Tồn tại các hình chữ nhật không quan trọng

Giả sử tồn tại hai hình chữ nhật A và B mà mà cả chiều ngang và chiều dọc của hình B đều bé hơn hình A thì ta có thể nói hình B là không quan trọng vì ta có thể để hình B chung với hình A từ đó chi phí của hình B không còn quan trọng. Sau khi đã loại hết tất cả hình không quan trọng đi và sắp xếp lại các hình theo chiều ngang giảm dần thì chiều dọc các hình đã được sắp xếp sẽ theo chiều tăng dần.

|![cht3.png](/algo/dp_/cht/cht3.png)|
|:-:|
|**Hình 3:** Sau khi loại bỏ hình chữ nhật không quan trọng (xanh lá) và sắp xếp 3 hình chữ nhật còn lại theo chiều ngang giảm dần (đỏ, xanh dương, đen) thì (đỏ, xanh dương, đen) cũng là thứ tự tăng dần theo chiều dọc.|

##### Nhận xét 2: Đoạn liên tiếp
Sau khi sắp xếp, ta có thể hình dung được rằng nếu ta chọn hai hình chữ nhật ở vị trí $i$ và ở vị trí $j$ thì ta có thể chọn tất cả hình chữ nhật từ $i+1$ đến $j-1$ mà không tốn chi phí nào cả. Vậy ta có thể thấy rằng cách phân hoạch tối ưu là một cách phân dãy thành các đoạn liên tiếp và chi phí của một đoạn là bằng tích của chiều ngang của hình chữ nhật đầu tiên và chiều dọc của hình chữ nhật cuối cùng.

##### Lời giải Quy Hoạch Động

Vậy bài toán trở về bài toán phân dãy sao cho tổng chi phí của các dãy là tối ưu. Đây là một dạng bài quy hoạch động hay gặp và ta có thể dễ dàng nghĩ ra thuật toán $\mathcal{O}(N^2)$ như mã giả phía dưới. (Giả sử các hình đã được sắp xếp và bỏ đi những hình chữ nhật không quan trọng)

```
input N
for i in [1..N]
    input h[i] // chiều  dọc  của hình chữ nhật thứ i
    input w[i] // chiều ngang của hình chữ nhật thứ i

cost[0] = 0
for i in [1..N]
    cost[i] = INF
    for j in [0..i-1]
        cost[i] = min(cost[i], cost[j] + h[i] * w[j+1])

print cost[N]
```

Ở trên `cost[k]` lưu lại chi phí cực tiểu để lấy được `k` hình chữ nhật đầu tiên. Hiển nhiên, `cost[0] = 0`. Để tính toán được `cost[i]` với $i\neq0$, ta tính tổng chi phí để lấy được các tập trước và cộng nó với chi phí của tập cuối cùng (có chứa $i$). Chi phí của một tập có thể dễ dàng tính bằng cách lấy tích của chiều ngang của hình chữ nhật đầu tiên và chiều dọc của hình chữ nhật cuối cùng. Vậy ta có `cost[i] = min(cost[i], cost[j] + h[i] * w[j+1])` với $j$ là hình chữ nhật đầu tiên của tập cuối cùng. Với $N=300000$ thì thuật toán $\mathcal{O}(N^2)$ này là quá chậm.
 
##### Nhận xét 3: Sử dụng bao lồi

Ta chọn $a_j=w[j+1], b_j=cost[j]$, và $x=h[i]$. Bài toán trở về tìm hàm cực tiểu của $y=a_jx+b_j$ bằng cách tìm $j$ tối ưu. Nó giống hoàn toàn bài toán ta đã đề cập ở trên. Giả sử ta đã hoàn thành việc cài đặt cấu trúc đã đề cập ở trên, ta có thể có mã giả ở dưới đây:

```
input N
for i in [1..N]
    input h[i] // chiều  dọc  của hình chữ nhật thứ i
    input w[i] // chiều ngang của hình chữ nhật thứ i

S = bao lồi dưới rỗng (Stack)
cost[0] = 0
S.add(a=w[1], b=cost[0]) // thêm đường thẳng y=ax+b đầu tiên vào S

for i in [1..N]
    cost[i] = S.query(h[i])
    if i < N
        S.add(a=w[i+1], b=cost[i])

print cost[N]
```

Rõ ràng các đường thẳng đã được sắp xếp giảm dần về độ lớn của hệ số góc do ta đã sắp xếp các chiều ngang giảm dần. Do mỗi truy vấn có thể thực hiện trong thời gian $\mathcal{O}(\log N)$ nên thời gian thực hiện của cả bài toán là $\mathcal{O}(N\log N)$. Và vì các truy vấn của ta cũng tăng dần (chiều dọc đã được sắp xếp tăng dần) nên ta có thể thay thế việc chặt nhị phân bằng một con trỏ chạy song song với việc quy hoạch động, đưa bước quy hoạch động còn $\mathcal{O}(N)$ nhưng tổng độ phức tạp vẫn là $\mathcal{O}(N\log N)$ do chi phí sắp xếp.

##### Cài đặt

```cpp=1
// Tham khảo: https://wcipeg.com/wiki/Convex_hull_trick/acquire.cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e5 + 7;
int n;
pair<int, int> p[N];

int ptr; // Con trỏ lưu vị trí của đường thẳng trả về kết quả của truy vấn trước đó
vector<ll> A; //  Hệ số góc  của các đường thẳng trong bao lồi
vector<ll> B; // Tung độ gốc của các đường thẳng trong bao lồi

// Trả về true nếu l1 hoặc l3 luôn tốt hơn l2
bool bad(int l1, int l2, int l3) {
    /*
    l1 và l2 giao ở x = (b1 - b2) / (a2 - a1)
    l1 và l3 giao ở x = (b1 - b3) / (a3 - a1)
    Nhân chéo để loại bỏ phép chia
    */
    return (B[l3] - B[l1]) * (A[l1] - A[l2]) < (B[l2] - B[l1]) * (A[l1] - A[l3]);
}

// Thêm đường thẳng mới (có hệ số góc nhỏ nhất)
void add(ll a, ll b) {
    // Đầu tiên, thêm đường thẳng vào cuối
    A.push_back(a);
    B.push_back(b);
    // Nếu đường thẳng áp chót không còn "tiềm năng" thì loại bỏ
    // Lặp lại nhiều lần nếu cần thiết
    while (A.size() >= 3 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
        A.erase(A.end() - 2);
        B.erase(B.end() - 2);
    }
}

// Trả về tọa độ y nhỏ nhất với giá trị x cho trước
ll query(ll x) {
    // Nếu ta đã loại bỏ đường thẳng tốt nhất cho truy vấn trước đó
    // thì đường thẳng vừa được thêm vào sẽ là đường thẳng tốt nhất mới
    if (ptr >= A.size())
        ptr = A.size() - 1;
    // Đường thẳng tốt hơn luôn ở bên phải, vì giá trị truy vấn không giảm
    while (ptr < A.size() - 1 && A[ptr + 1] * x + B[ptr + 1] < A[ptr] * x + B[ptr])
        ++ptr;
    return A[ptr] * x + B[ptr];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> p[i].first >> p[i].second;

    sort(p, p + n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        // Loại bỏ các hình chữ nhật không quan trọng
        while (cnt > 0 && p[cnt - 1].second <= p[i].second)
            --cnt;
        p[cnt++] = p[i];
    }

    ll cost;
    add(p[0].second, 0);
    // Ban đầu, đường thẳng tốt nhất có thể là
    // bất kỳ đường thẳng nào trong trong bao lồi
    ptr = 0;
    for (int i = 0; i < n; ++i) {
        cost = query(p[i].first);
        if (i < n - 1)
            add(p[i + 1].second, cost);
    }
    cout << cost << '\n';
}
```

#### Ví dụ 2: APIO 2010 Commando

##### Bài toán

Bạn được cho:
- Một dãy có **$N$ số nguyên dương** ($1\le N \le 10^6$)
- Một hàm số bậc 2 với hệ số nguyên dương $f(x)= ax^2 + bx +c$, $a\lt0$.
- Mục tiêu của bài toán là phân dãy này ra thành các đoạn liên tiếp sao tổng các hàm $f$ trên các dãy là lớn nhất (giá trị của hàm $f$ lên dãy là $f(x)$ với $x$ là tổng dãy đó).

Tương tự bài trên, ta dễ dàng thấy được công thức quy hoạch động $\mathcal{O}(N^2)$.

Định nghĩa rằng:

- `sum(i,j) = x[i] + x[i+1] + ... + x[j]` 
- `adjust(i,j) = a*sum(i,j)^2 + b*sum(i,j) + c` 

Ta có:

$dp(n) = \max\limits_{k=0}^{n-1}[dp(k)+adjust(k+1,n)]$

Mã giả:

```
dp[0] = 0
for n in [1..N]
    for k in [0..n-1]
        dp[n] = max(dp[n], dp[k] + adjust(k+1, n))
```

Hãy thử biến đổi hàm "adjust" một tí.
Định nghĩa $sum(1,x)$ là $\delta(x)$. Vậy với một số $k$ bất kì ta có thể viết là:

$dp(n)=dp(k)+a(\delta(n)-\delta(k))^2+b(\delta(n)-\delta(k))+c$
$dp(n)=dp(k)+a(\delta(n)^2+\delta(k)^2-2\delta(n)\delta(k))+b(\delta(n)-\delta(k))+c$
$dp(n)=(a\delta(n)^2 +b\delta(n) +c)+dp(k)-2a\delta(n)\delta(k)+a\delta(k)^2-b\delta(k)$

Nếu:

- $z=\delta(n)$
- $m=-2a\delta(k)$
- $p=dp(k)+a\delta(k)^2-b\delta(k)$

Ta có thể thấy $mz+p$ là đại lượng mà ta cần tối ưu hóa bằng cách chọn $k$. $dp(n)$ sẽ bằng đại lượng đó cộng thêm với $a\delta(n)+b\delta(n)+c$ (độc lập so với $k$). Trong đó $z$ cũng độc lập với $k$, và $m$ và $p$ phụ thuộc vào $k$.

Ngược với bài "Phân nhóm" khi ta phải tối thiểu hóa hàm quy hoạch động thì bài này ta phải cực đại hóa nó. Do đó, trong bài này, ta phải xây dựng một hình bao trên với các đường thẳng tăng dần theo hệ số góc.
Vì đề bài đã cho $a\lt0$ và dễ thấy $\delta(n)>\delta(n-1)$, nên hệ số góc $m$ của ta sẽ tăng dần.

Tương tự bài "Phân nhóm", các truy vấn của ta cũng tăng dần theo thứ tự. Do vậy, ta có thể khởi tạo một biến chạy để chạy song song khi làm quy hoạch động (bỏ được phần chặt nhị phân).

##### Cài đặt

Phần cài đặt của ví dụ này tương tự với phần cài đặt của ví dụ 1.
Bạn đọc có thể tham khảo code mẫu ở [đây (Code C++ cho "commando")](http://wcipeg.com/wiki/Convex_hull_trick/commando.cpp).


#### Ví dụ 3: HARBINGERS ([CEOI 2009](https://oj.vnoi.info/problem/harbinge))

##### Bài toán

Ngày xửa ngày xưa, có $N$ trị trấn kiểu trung cổ trong khu tự trị Moldavian. Các thị trấn này được đánh số từ $1$ đến $N$. Thị trấn $1$ là thủ đô. Các thị trấn được nối với nhau bằng $N-1$ con đường hai chiều, mỗi con đường có độ dài được đo bằng km. Có duy nhất một tuyến đường nối giữa hai điểm bất kỳ (đồ thị các con đường là hình cây). Mỗi thị trấn không phải trung tâm có một người truyền tin.

Khi một thị trấn bị tấn công, tình hình chiến sự cần được báo về thủ đô càng sớm càng tốt. Một thông điệp được truyền bằng các người truyền tin. Mỗi người truyền tin được đặc trưng bởi lượng thời gian khởi động và vận tốc không đổi sau khi xuất phát.

Thông điệp luôn được truyền trên con đường ngắn nhất đến trung tâm. Ban đầu, thông tin chiến sự được đưa cho người truyền tin tại thị trấn bị tấn công. Từ thị trấn đó người truyền tin sẽ đi theo con đường về gần thủ đô hơn. Khi đến một thị trấn mới vừa đến. Lưu ý rằng khi chuyển sang người truyền tin mới thì người này cần một lượng thời gian để khởi động rồi mới đi chuyển tin. Như vậy, thông điệp sẽ được chuyển bằng một số người truyền tin trước khi đến thử đô.

Hãy xác định thời gian ít nhất cần chuyển tin từ các thị trấn về thủ đô.

**Input**
 - Dòng đầu ghi số N.
 - $N-1$ dòng tiếp theo, mỗi dòng ghi ba số $u$, $v$, và $d$ thể hiện một con đường nối từ $u$ đến $v$ với độ dài bằng $d$.
 - $N-1$ dòng tiếp theo, dòng thứ $i$ gồm hai số $S_i$ và $V_i$ thể hiện thời gian cần để khởi động và số lượng phút để đi được $1$ km của người truyền tin ở thị trấn $i+1$.

**Output**
 - Ghi $N-1$ số trên một dòng. Số thứ $i$ thể hiện thời gian ít nhất cần truyền tin từ thành phố $i+1$ về thủ đô.

**Giới hạn**
 - $3 \le N \le 100 000$
 - $0 \le S_i, V_i \le 10^9$
 - Độ dài mỗi con đường không vượt quá $10000$

##### Lời giải

**Thuật toán QHĐ**

Gọi $F(i)$ là thời gian ít nhất để truyền tin từ thành phố thứ $i$ đến thủ đô, ta có công thức truy hồi:

$F(i) = \min[ F(j) + dist(j, i) * V_i + S_i ]$

với $j$ là một nút trên đường từ thành phố $i$ đến thành phố $1$. Trong đó $dist(j, i)$ là khoảng cách giữa 2 thành phố $i$ và $j$, có thể tính trong $O(1)$ sử dụng mảng cộng dồn $D[]$ với $D[i]$ là khoảng cách từ thành phố $i$ tới thủ đô. Thuật toán này có thể dễ dàng cài đặt với độ phức tạp là $O(N^2)$.

**Áp dụng kĩ thuật bao lồi**

Công thức truy hồi có thể viết lại thành

$F(i) = \min[ F(j) - D_j * V_i + D_i * V_i + S_i ]$

Khi ta tính $F(i)$, thì giá trị $D_i*V_i + S_i$ là hằng số với mọi $j$, vì vậy

$F(i) = \min[ F(j) - D_j * V_i ] + D_i * V_i + S_i$

Có thể thấy rằng ta cần tìm giá trị nhỏ nhất của hàm bậc nhất $y = -D_j*x + F(j)$ <dạng $y = ax + b$>.
Với trường hợp cây là đường thẳng, ta có thể trực tiếp áp dụng kĩ thuật bao lồi. Trong trường hợp tổng quát, ta cần một cấu trúc dữ liệu cho phép xử lí hai thao tác:

 - Khi DFS xuống một nút con, ta cần thêm một đường thẳng.
 - Khi quá trình DFS tính $F[]$ cho gốc cây con đã hoàn tất, ta cần xóa một đường thẳng, trả cấu trúc dữ liệu về trạng thái ban đầu.

Các thao tác này có thể được thực hiện hiệu quả trong $O(\log N)$. Cụ thể ta sẽ biểu diễn Stack bằng một mảng cùng một biến $size$ (kích thước Stack). Khi thêm một đường thẳng vào, ta sẽ tìm kiếm nhị phân vị trí mới của nó, rồi chỉnh sửa biến $size$ cho phù hợp, chú ý là sẽ có tối đa một đường thẳng bị ghi đè, nên ta chỉ cần lưu lại nó. Khi cần trả về trạng thái ban đầu, ta chỉ cần chỉnh sửa lại biến $size$ đồng thời ghi lại đường thẳng đã bị ghi đè trước đó. Để quản lí lịch sử các thao tác ta sử dụng một $vector$ lưu lại chúng.
Độ phức tạp cho toàn bộ thuật toán là $O(N\log N)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> Line;
#define X first
#define Y second

const int N = 1e5 + 9;
const ll INF = (ll)1e18;

struct operation {
    int pos, top;
    Line overwrite;
    operation(int _p, int _t, Line _o) {
        pos = _p; top = _t; overwrite = _o;
    }
};
vector<operation> undoLst;
Line lines[N];
int n, top;

ll eval(Line line, ll x) { return line.X * x + line.Y; }
bool bad(Line a, Line b, Line c) {
    return (double)(b.Y - a.Y) / (a.X - b.X) >= (double)(c.Y - a.Y) / (a.X - c.X);
}

ll getMin(ll coord) {
    int l = 0, r = top - 1; ll ans = eval(lines[l], coord);
    while (l < r) {
        int mid = l + r >> 1;
        ll x = eval(lines[mid], coord);
        ll y = eval(lines[mid + 1], coord);
        if (x > y) l = mid + 1; else r = mid;
        ans = min(ans, min(x, y));
    }
    return ans;
}

bool insertLine(Line newLine) {
    int l = 1, r = top - 1, k = top;
    while (l <= r) {
        int mid = l + r >> 1;
        if (bad(lines[mid - 1], lines[mid], newLine)) {
            k = mid; r = mid - 1;
        }
        else l = mid + 1;
    }
    undoLst.push_back(operation(k, top, lines[k]));
    top = k + 1;
    lines[k] = newLine;
    return true;
}

void undo() {
    operation ope = undoLst.back(); undoLst.pop_back();
    top = ope.top; lines[ope.pos] = ope.overwrite;
}

ll f[N], S[N], V[N], d[N];
vector<Line> a[N];

void dfs(int u, int par) {
    if (u > 1)
        f[u] = getMin(V[u]) + S[u] + V[u] * d[u];
    insertLine(make_pair(-d[u], f[u]));
    for (vector<Line>::iterator it = a[u].begin(); it != a[u].end(); ++it) {
        int v = it->X;
        int uv = it->Y;
        if (v == par) continue;
        d[v] = d[u] + uv;
        dfs(v, u);
    }
    undo();
}

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].emplace_back(v, c);
        a[v].emplace_back(u, c);
    }
    for (int i = 2; i <= n; ++i) cin >> S[i] >> V[i];
    dfs(1, 0);
    for (int i = 2; i <= n; ++i) cout << f[i] << ' ';
}
```

### Bài tập áp dụng

- [**Bài J - ACM ICPC Vietnam Regional 2017**](https://open.kattis.com/problems/joiningnetwork)
- [**VNOJ - NKLEAVES**](https://oj.vnoi.info/problem/nkleaves/)

---

## Kĩ thuật Bao lồi: Thuật toán Online (sử dụng LineContainer)
Lưu ý:
- **LineContainer** của [KTH's ICPC notebook](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h) chỉ **hoạt động với C++14 trở lên** (vì sử dụng `less<void>` - sẽ đề cập trong bước 3 của phần cài đặt LineContainer), vậy nên các bạn thi HSGQG có thể bị **Compile Error**.
- Ở bước 3 của phần cài đặt LineContainer, ta sẽ sửa đổi code một chút để LineContainer có thể hoạt động với C++11.

Trong phần trước của bài viết, các tác giả đã giới thiệu một kĩ thuật được sử dụng để giải các bài toán có dạng:
- Cho một tập các đường thẳng $y=a_ix+b_i$ và các truy vấn, mỗi truy vấn gồm một số $x$.
- Với mỗi truy vấn, hỏi giá trị lớn nhất/nhỏ nhất $y$ có thể đạt được nếu thay $x$ vào các đường thẳng đã cho.

Điểm yếu của cách cài đặt bằng Stack trong nửa trước của bài viết là: độ phức tạp thời gian để ta thêm một đường thẳng có hệ số góc $a_i$ **bất kỳ** là $\mathcal{O}(N)$ (cho thao tác chèn một phần tử).

Do đó, trong nửa sau của bài viết này, ta sẽ tiếp cận một cách cài đặt khác có thể thêm một đường thẳng có hệ số góc $a_i$ **bất kỳ** vào tập với độ phức tạp thời gian $\mathcal{O}(\log N)$, mà độ phức tạp thời gian cho thao tác truy vấn vẫn giữ nguyên là $\mathcal{O}(\log N)$.

### LineContainer

Bạn đọc có thể tham khảo cách cài đặt **LineContainer** được triển khai trong [KTH's ICPC notebook](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h). Đây là một cài đặt hỗ trợ thao tác thêm đường thẳng có dạng $y=ax+b$ và thao tác truy vấn **giá trị tối đa** tại các điểm x.
Cách cài đặt trên thường được các team ICPC tin tưởng và sử dụng vì độ đơn giản và hiệu quả của nó.

Trong phần này, ta sẽ tự cài đặt một LineContainer để có thể hiểu được nguyên lý đằng sau nó.

#### Ý tưởng
Ta sử dụng `std::multiset` để duy trì tập các đường thẳng theo thứ tự hệ số góc tăng dần, cũng như thêm và xoá một đường thẳng bất kỳ với độ phức tạp thời gian $\mathcal{O}(\log N)$.
Để tiện cho việc truy vấn, với mỗi đường thẳng, ta tạo một biến `p` dùng để lưu "vị trí phải cùng" của đoạn mà đường thẳng đó "quản lý", tức là vị trí giao nhau với đường thẳng ở ngay bên phải.

#### Cài đặt

##### Bước 1: Tạo struct Line

Đầu tiên, ta cần một `struct Line` chứa `a`, `b` để biểu diễn một đường thẳng $y=ax+b$. Ta cũng cần một `std::multiset<Line>` để có được nơi quản lý các đường thẳng theo thứ tự hệ số góc tăng dần.

```cpp=1
struct Line {
    // Line: y = ax + b
    int a, b;
    // các đường thẳng được sắp xếp theo hệ số góc a
    bool operator<(const Line& o) const { return a < o.a; }
};
multiset<Line> myLC;
```

Để đơn giản hoá quá trình cài đặt, ta sẽ thêm vào `struct Line` một biến `p` kèm từ khoá `mutable` để lưu "vị trí phải cùng" của đoạn mà đường thẳng này "quản lý".
Từ khoá `mutable` cho phép ta thay đổi giá trị biến `p` kể cả khi `Line` là `const` (ta cần cập nhật giá trị của `p` liên tục nhưng `Line` trong `std::multiset<Line>` là `const`).

```cpp=1
const double INF = 1/.0;
struct Line {
    int a, b;
    mutable double p; // như định nghĩa, p trong myLC cũng sẽ có thứ tự tăng dần
    bool operator<(const Line& o) const { return a < o.a; }
};
multiset<Line> myLC;
```

##### Bước 2: Hàm add(a, b)

Tiếp theo, ta cần một hàm `add(int a, int b)` để thêm đường thẳng $y=ax+b$ vào `myLC` và xoá đi tất cả đường thẳng "không tiềm năng".

Hàm `add(int a, int b)` sẽ hoạt động như sau:
- Đầu tiên, thêm $y=ax+b$ vào `myLC`.
- Nếu $y=ax+b$ vừa thêm vào là "không tiềm năng", ta chỉ cần xoá đường thẳng này đi để khôi phục `myLC` ban đầu (chắc chắn `myLC` ban đầu không chứa hàm "không tiềm năng").
- Ngược lại, một số (**có thể không có**) đường thẳng liền trước và liền sau $y=ax+b$ có sẵn trong `myLC` sẽ trở thành "không tiềm năng" (ứng với Hình 4 và Hình 5 là các đường thẳng trở thành "không tiềm năng" liền sau và liền trước "x" sau khi thêm "x") và ta cần phải xoá chúng.

Để đơn giản hoá quá trình cài đặt, ta xây dựng hàm `bool isect(x, y)` với `x` và `y` là 2 con trỏ `multiset<Line>::iterator` liền kề (`x` là liền trước của `y`).
Hàm trả về `true` nếu `x->p >= y->p`, tức là `y` không còn là một đường thẳng "tiềm năng" nữa (Hình 4).

|![cht4.png](/algo/dp_/cht/cht4.png)|
|:-:|
|**Hình 4:** Sau khi thêm $x$, $y$ không còn "tiềm năng" nữa (vì `y->p < x->p`).|

Vì mục đích thuận tiện, hàm sẽ tính lại `x->p` trước khi thực hiện phép so sánh cuối cùng.

```cpp=1
const double INF = 1/.0;
struct Line {
    int a, b;
    mutable double p;
    bool operator<(const Line& o) const { return a < o.a; }
};
multiset<Line> myLC;

// trả về 'true' nếu x->p >= y->p
bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
    //// tính x->p
    if (y == myLC.end()) {
        // không tồn tại y
        // => x là đường thẳng cuối cùng
        // => x->p = +inf
        x->p = INF;
        return false; // trả về 'false' vì mục đích cài đặt
    }
    if (x->a == y->a) {
        // x và y song song
        // => hàm nào có b lớn hơn thì "tiềm năng"
        if (x->b > y->b)
            x->p = INF;
        else x->p = -INF;
    }
    else {
        // 2 đường thẳng giao nhau
        // => x->p là vị trí giao nhau đó
        x->p = (double)(y->b - x->b) / (x->a - y->a);
    }
    return x->p >= y->p;
}

void add(int a, int b) {
    ...
}
```

Cài đặt hàm `add(int a, int b)` gồm 4 bước:
- Bước 1: Thêm đường thẳng $y=ax+b$, biến trỏ tới đường thẳng này gọi là `x`.
- Bước 2: **Tính `x->p`** và xoá các đường thẳng trở nên "không tiềm năng" **liền sau** `x` (Hình 4).
- Bước 3: Kiểm tra đường thẳng `x` có "tiềm năng" hay không.
- Bước 4: Nếu `x` là "tiềm năng", xoá các đường thẳng trở nên "không tiềm năng" **liền trước** `x` (Hình 5).

**Lưu ý:** Lý do ta thực hiện bước 3 sau bước 2 là vì khi ở bước 2, ta chưa có `x->p` nên không thể kiểm tra tính "tiềm năng" của `x` được. Hơn nữa, nếu `x` là "không tiềm năng" thì dễ thấy rằng `x` sẽ không ảnh hưởng đến các đường thẳng "tiềm năng" liền sau `x` (vì chỉ có `x->p` được tính trong bước 2). Do đó, hàm `add` sẽ vẫn hoạt động bình thường.

<!-- |![image](https://i.imgur.com/t40h27O.png)| -->

|![cht5.png](/algo/dp_/cht/cht5.png)|
|:-:|
|**Hình 5:** Sau khi thêm $x$, $pre1$ và $pre2$ lần lượt không còn "tiềm năng" nữa (vì `pre1->p < pre2->p`, sau đó, `pre2->p < pre3->p`).|

```cpp=1
const double INF = 1/.0;
struct Line {
    int a, b;
    mutable double p;
    bool operator<(const Line& o) const { return a < o.a; }
};
multiset<Line> myLC;

bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
    // rút gọn cài đặt nhưng ý nghĩa vẫn không thay đổi
    if (y == myLC.end()) return x->p = INF, false;
    if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
    else x->p = (double)(y->b - x->b) / (x->a - y->a);
    return x->p >= y->p;
}

void add(int a, int b) {
    //// đầu tiên, ta thêm y=ax+b vào 'myLC'
    // từ C++11 trở đi, ta có thể sử dụng từ khoá 'auto' để thay thế
    // 'multiset<Line>::iterator' vì sự tiện lợi và ngắn gọn
    multiset<Line>::iterator x = myLC.insert({ a, b, 0 }); // p=0 là không có 
    // 'multiset::insert' trả về con trỏ đến vị trí mà Line được thêm vào
    
    //// tiếp theo, ta cần xoá các đường thẳng "không tiềm năng"
    //// liền sau 'x' và tính `x->p`
    // hàm 'next' trả về con trỏ đến vị trí liền sau của 'x' trong myLC
    multiset<Line>::iterator y = next(x);
    // "isect(x, y)" trả về 'true' nếu 'y' không còn
    // là hàm "tiềm năng" => xoá 'y' và tiếp tục vòng lặp
    while (isect(x, y)) y = myLC.erase(y);
    // hàm 'erase' sẽ xoá 'y' và trả về con trỏ đến vị trí liền sau
    // của 'y' trong myLC
    //// sau bước này, các liền sau của 'x' đều là các hàm "tiềm năng"
    
    //// sau khi đã tính được 'x->p'
    //// ta cần kiểm tra xem 'x' có phải một "hàm tiềm năng" hay không
    if (x != myLC.begin()) {
        // hàm 'prev' trả về con trỏ đến vị trí liền trước của 'x' trong myLC
        y = prev(x);
        if (isect(y, x)) isect(y, myLC.erase(x));
        // sau bước này, 'y->p' đã được tính lại dù có xoá 'x' hay không
    }

    //// cuối cùng, ta cần xoá các đường thẳng "không tiềm năng" trước 'x'
    //// NOTE: 'y' là con trỏ đến vị trí liền trước của 'x', có 2 trường hợp:
    //// - 'x' là một đường thẳng "không tiềm năng":
    ////   + sau khi xoá 'x', myLC vẫn duy trì các 'p' tăng dần như cũ
    ////     => các dòng code tiếp theo sẽ không thay đổi bất cứ thứ gì
    //// - 'x' là một đường thẳng "tiềm năng":
    ////   + như ở phần mô tả cài đặt, ta cần xoá một số đường thẳng
    ////     trở nên "không tiềm năng" sau khi thêm 'x'
    while (y != myLC.begin()) {
        // lưu ý, từ đây sẽ ta tận dụng lại biến 'x' nên 'x' không còn là
        // đường thẳng được thêm vào nữa
        x = prev(y);
        if (x->p >= y->p) {
            // 'y' trở nên "không tiềm năng" => xoá 'y' và tính lại 'x->p'
            isect(x, myLC.erase(y));
            y = x; // đặt lại 'y' là đường thẳng liền trước của 'y' cũ
        }
        else {
            // 'y' và các đường thẳng phía trước là "tiềm năng"
            // => thoát khỏi vòng lặp
            break;
        }
    }
}
```

##### Bước 3: Hàm query(x)

Cuối cùng, ta cần một hàm `int query(int x)` để truy vấn tìm **giá trị lớn nhất** tại vị trí $x$.

Trong phần cài đặt của [KTH's ICPC notebook](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h), tác giả sử dụng `less<void>` (**hoạt động với C++14 trở lên**) để có thể tuỳ chỉnh kiểu tham số của hàm `multiset::lower_bound` và chặt nhị phân theo `p` (nếu không có `less<void>`, `multiset::lower_bound` sẽ chỉ nhận `Line` làm tham số đầu vào và ta sẽ không thể chặt nhị phân theo `p` được). Bạn đọc có thể đọc thêm về `less<void>` tại [cppreference](https://en.cppreference.com/w/cpp/utility/functional/less_void).

Để cài đặt một LineContainer hoạt động với C++11, ta sử dụng trick sau:
Giả sử rằng không có đường thẳng nào có dạng $y=+\infty\times x+\infty$ với $a=b=+\infty$. Khi đó, để chặt nhị phân theo `p`, ta truyền vào cho `multiset::lower_bound` giá trị `{ INT_MAX, INT_MAX, x }` và thực hiện phép so sánh theo `p`.

```cpp=1
const double INF = 1/.0;
struct Line {
    int a, b;
    mutable double p;
    bool operator<(const Line& o) const {
        // nếu a = b = INT_MAX thì so sánh theo p
        // o.p lúc này chính là x đã được truyền vào hàm
        if (o.a == INT_MAX && o.b == INT_MAX) return p < o.p;
        return a < o.a;
    }
};
multiset<Line> myLC;

bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
    if (y == myLC.end()) return x->p = INF, false;
    if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
    else x->p = (double)(y->b - x->b) / (x->a - y->a);
    return x->p >= y->p;
}

void add(int a, int b) {
    // rút gọn cài đặt nhưng ý nghĩa vẫn không thay đổi
    auto x = myLC.insert({ a, b, 0 }), y = next(x);
    while (isect(x, y)) y = myLC.erase(y);
    if ((y = x) != myLC.begin() && isect(--y, x)) isect(y, myLC.erase(x));
    // ở đây, ta có thể tiếp tục rút gọn bằng cách hoán đổi
    // ý nghĩa của 'x' và 'y' => giảm 1 lần gán 'x=y' hoặc 'y=x'
    while ((x = y) != myLC.begin() && (--x)->p >= y->p)
        isect(x, myLC.erase(y)), y = x;
}

int query(int x) {
    // tìm đường thẳng đầu tiên có it->p >= x
    // => đoạn thẳng mà đường thẳng này "quản lý" chắc chắn chứa x
    Line l = *myLC.lower_bound({ INT_MAX, INT_MAX, x });
    return l.a * x + l.b;
}
```

Để dễ dàng sử dụng khi cần nhiều LineContainer (như trong [Bài toán 2](#Bài-toán-2-Codeforces---455E-Function)), ta tạo `struct LineContainer`

```cpp=1
const double INF = 1/.0;
struct Line {
    int a, b;
    mutable double p;
    bool operator<(const Line& o) const {
        if (o.a == INT_MAX && o.b == INT_MAX) return p < o.p;
        return a < o.a;
    }
};
struct LineContainer {
    multiset<Line> myLC;
    bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
        if (y == myLC.end()) return x->p = INF, false;
        if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
        else x->p = (double)(y->b - x->b) / (x->a - y->a);
        return x->p >= y->p;
    }
    void add(int a, int b) {
        auto x = myLC.insert({ a, b, 0 }), y = next(x);
        while (isect(x, y)) y = myLC.erase(y);
        if ((y = x) != myLC.begin() && isect(--y, x)) isect(y, myLC.erase(x));
        while ((x = y) != myLC.begin() && (--x)->p >= y->p)
            isect(x, myLC.erase(y)), y = x;
    }
    int query(int x) {
        Line l = *myLC.lower_bound({ INT_MAX, INT_MAX, x });
        return l.a * x + l.b;
    }
};
```

##### Bước 4: Trick làm tròn xuống cho phép chia

Khi cài đặt, đôi khi ta cần đảm bảo tất cả các biến được sử dụng đều có kiểu dữ liệu số nguyên nhằm giảm thiểu sai số (cụ thể là chỉ có biến `p` đang có kiểu dữ liệu `double`).
Do đó, trong bước này, ta sẽ thay đổi cài đặt một chút để có thể sử dụng `p` với kiểu dữ liệu số nguyên.

Nhắc lại định nghĩa của `p` ở bước 1, `p` lưu "vị trí phải cùng" của đoạn mà đường thẳng "quản lý". Do đó, ta cần giá trị của `p` phải được **làm tròn xuống bắt kể giá trị là âm hay dương** ($-1.5\rightarrow-2$ và $1.5\rightarrow1$).
Đương nhiên, ta cũng có thể làm tròn lên tuỳ theo cách giải. Do đó, bài viết này sẽ chỉ đề cập đến làm tròn xuống.

Ta biết rằng, phép chia `a/b` mặc định sẽ làm tròn đến số gần số 0 hơn (`3/2 = 1` và `-3/2 = -1`).

Ta có nhận xét sau:
- Nếu `a` chia hết cho `b` thì kết quả `a/b` là kết quả cần tìm (vì không cần làm tròn).
- Ngược lại, có 2 trường hợp:
    - Nếu `a/b > 0` thì làm tròn mặc định đã đúng (làm tròn xuống).
    - Nếu `a/b < 0` thì ta cần thêm -1 vào kết quả (vì phép chia mặc định `a/b` sẽ làm tròn lên với số âm - gần 0 hơn).

Từ đó, ta dựng hàm `f` có khả năng thực hiện phép chia và làm tròn xuống (thoả mãn `f(3,2) = 1` và `f(-3,2) = -2`) một cách ngây thơ như sau:

```cpp=1
int f(int a, int b) {
    int res = a / b;
    if (a % b) {
        if (a > 0 && b < 0) --res;
        if (a < 0 && b > 0) --res;
    }
    return res;
}
```

Ta có thể kiểm tra `a` và `b` đối dấu nhanh hơn bằng phép xor `(a ^ b) < 0`.
Giải thích đơn giản:
- Trong biểu diễn bù 2 (two's complement), nếu bit đầu tiên là 0 thì đó là số không âm, ngược lại, nếu bit đầu tiên là 1 thì đó là số âm. Do giới hạn của bài viết, ta sẽ không đi sâu hơn vào loại biểu diễn này.
- Từ đó, kết quả xor của 2 số khác dấu trong biểu diễn bù 2 sẽ có bit đầu là 1, tức là số âm.
- Ngược lại, kết quả xor của 2 số cùng dấu trong biểu diễn bù 2 sẽ có bit đầu là 0, tức là số không âm.

Ta viết lại hàm `f` như sau:

```cpp=1
int f(int a, int b) {
    int res = a / b;
    if (a % b && (a ^ b) < 0) --res;
    return res;
}
```

Viết lại hàm `f` không sử dụng `res` và đảo thứ tự logic trong hàm điều kiện (phép mod chậm hơn nhiều so với phép xor nên ta có thể ưu tiên kiểm tra phép xor trước).

```cpp=1
int f(int a, int b) {
    return a / b - ((a ^ b) < 0 && a % b);
}
```

Sau khi đã có hàm `f`, ta thêm nó vào code ở bước 3:

```cpp=1
// với double, sử dụng INF = 1/.0 và div(a,b) = a/b
const int INF = INT_MAX;
struct Line {
    int a, b;
    mutable int p;
    bool operator<(const Line& o) const {
        if (o.a == INT_MAX && o.b == INT_MAX) return p < o.p;
        return a < o.a;
    }
};
struct LineContainer {
    multiset<Line> myLC;
    int div(int a, int b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
        if (y == myLC.end()) return x->p = INF, false;
        if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(int a, int b) {
        auto x = myLC.insert({ a, b, 0 }), y = next(x);
        while (isect(x, y)) y = myLC.erase(y);
        if ((y = x) != myLC.begin() && isect(--y, x)) isect(y, myLC.erase(x));
        while ((x = y) != myLC.begin() && (--x)->p >= y->p)
            isect(x, myLC.erase(y)), y = x;
    }
    int query(int x) {
        Line l = *myLC.lower_bound({ INT_MAX, INT_MAX, x });
        return l.a * x + l.b;
    }
};
```

### Ứng dụng
#### Bài toán 1: [**Codeforces - 660F (Bear and Bowling 4)**](https://codeforces.com/contest/660/problem/F)

##### Tóm tắt
Cho mảng $a$ độ dài $n$. Ta định nghĩa hàm $score(l,r)$ của đoạn $[l,r]$ bằng công thức $score(l,r)=\sum\limits_{i=l}^r(a_i\times(i-l+1))$ nếu $l\le r$, và $score(l,r)=0$ nếu $l\gt r$.
Hỏi giá trị lớn nhất của $score(l,r)$ với $1\le l,r\le n$.

Giới hạn:
- $1\le n\le 2\times10^5$
- $|a_i|\le10^7$

##### Ý tưởng
Ý tưởng chung cho các bài toán sử dụng kĩ thuật bao lồi là ta sẽ cố gắng biến đổi công thức về dạng phương trình đường thẳng $(kx+m)+const$ với:
- $k$ và $m$ là phần ứng với phương trình đường thẳng, đã được tính và thêm vào tập hợp trước đó.
- $x$ và $const$ là phần được tính vào lúc truy vấn.

Trong bài toán này, mục tiêu biến đổi là đưa công thức về dạng $k(l)\times x(r)+m(l)+const(r)$, ứng với 3 phần:
- $k(l)\times x(r)$ ứng với nhóm phụ thuộc vào cả $l$ và $r$.
- $m(l)$ ứng với nhóm chỉ phụ thuộc vào $l$.
- $const(r)$ ứng với nhóm chỉ phụ thuộc vào $r$.

Cụ thể, ta có thể biến đổi hàm $score(l,r)$ của đoạn $[l,r]$ (với $l\le r$) như sau:

$$\begin{align*}
score(l,r)&=\sum\limits_{i=l}^r(a_i\times(i-l+1)) \\
&=\sum\limits_{i=l}^r(a_i\times i)+\sum\limits_{i=l}^r(a_i\times(-l+1)) \\
&=\sum\limits_{i=l}^r(a_i\times i)+(1-l)\sum\limits_{i=l}^ra_i \\
&=\left[\sum\limits_{i=1}^r(a_i\times i)-\sum\limits_{i=1}^{l-1}(a_i\times i)\right]+\left[(1-l)\sum\limits_{i=1}^ra_i-(1-l)\sum\limits_{i=1}^{l-1}a_i\right] \\
&=\left[\sum\limits_{i=1}^r(a_i\times i)-\sum\limits_{i=1}^{l-1}(a_i\times i)\right]+\left[(1-l)\sum\limits_{i=1}^ra_i+(l-1)\sum\limits_{i=1}^{l-1}a_i\right] \\
\end{align*}$$

Đặt $prf_1(r)=\sum\limits_{i=1}^r(a_i\times i)$ và $prf_2(r)=\sum\limits_{i=1}^ra_i$, công thức trên trở thành:

$$\begin{align*}
score(l,r)
&=\left[prf_1(r)-prf_1(l-1)\right]+\left[(1-l)\times prf_2(r)+(l-1)\times prf_2(l-1)\right] \\
\\
&=(1-l)\times prf_2(r)+(l-1)\times prf_2(l-1)-prf_1(l-1)+prf_1(r) \\
\end{align*}$$

Đặt $k(l)=1-l$, $m(l)=(l-1)\times prf_2(l-1)-prf_1(l-1)$, công thức trên trở thành:

$$\begin{align*}
score(l,r)=k(l)\times prf_2(r)+m(l)+prf_1(r)
\end{align*}$$

##### Thuật toán
Xét $r$ từ $1$ đến $n$.
Với mỗi $r$, để tính $\max\limits_{l=1}^r\left[score(l,r)\right]$, ta thêm đường thẳng thứ $r$: $y=k(r)\times x+m(r)$ vào LineContainer, sau đó truy vấn với $x=prf_2(r)$ để có được giá trị lớn nhất của $k(l)\times prf_2(r)+m(l)$, rồi thêm $prf_1(r)$ vào.

##### Cài đặt
```cpp=1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 8;
int n, a[N];
ll prf1[N], prf2[N];

// với double, sử dụng INF = 1/.0 và div(a,b) = a/b
const ll INF = LLONG_MAX;
struct Line {
    ll a, b;
    mutable ll p;
    bool operator<(const Line& o) const {
        if (o.a == LLONG_MAX && o.b == LLONG_MAX) return p < o.p;
        return a < o.a;
    }
};
struct LineContainer {
    multiset<Line> myLC;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
        if (y == myLC.end()) return x->p = INF, false;
        if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(ll a, ll b) {
        auto x = myLC.insert({ a, b, 0 }), y = next(x);
        while (isect(x, y)) y = myLC.erase(y);
        if ((y = x) != myLC.begin() && isect(--y, x)) isect(y, myLC.erase(x));
        while ((x = y) != myLC.begin() && (--x)->p >= y->p)
            isect(x, myLC.erase(y)), y = x;
    }
    ll query(ll x) {
        Line l = *myLC.lower_bound({ LLONG_MAX, LLONG_MAX, x });
        return l.a * x + l.b;
    }
};

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        prf1[i] = prf1[i - 1] + 1LL * a[i] * i;
        prf2[i] = prf2[i - 1] + a[i];
    }

    LineContainer cht;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ll k = 1 - i;
        ll m = (i - 1) * prf2[i - 1] - prf1[i - 1];
        cht.add(k, m);
        ans = max(ans, cht.query(prf2[i]) + prf1[i]);
    }
    cout << ans << '\n';
}
```

Độ phức tạp thời gian: $\mathcal{O}(N\log N)$
Độ phức tạp không gian: $\mathcal{O}(N)$

#### Bài toán 2: [**Codeforces - 455E (Function)**](https://codeforces.com/contest/455/problem/E)
##### Tóm tắt
Cho mảng $a$ độ dài $n$ và hàm $f(i,j)$ ($i\le j\le n$) được định nghĩa như sau:

$$
f(i,j)=a[j]+
\begin{cases}
0                           &,i=1 \\
\min(f(i - 1, j), f(i - 1, j - 1)) &,2\le i\le n
\end{cases}
$$

Cho $m$ truy vấn $(x_i,y_i)$. Với mỗi truy vấn, in ra giá trị của $f(x_i,y_i)$.

Giới hạn:
- $1\le n,m\le 10^5$
- $0\le a_i\le 10^4$
- $1\le x_i\le y_i\le n$

##### Ý tưởng
Ta có thể phát biểu lại bài toán như sau:
- Với truy vấn $(i,j)$, ta sẽ bắt đầu tại vị trí $j$ và di chuyển $i$ bước.
- Với mỗi bước, ta có thể di chuyển sang trái $1$ đơn vị hoặc giữ nguyên vị trí. Giả sử vị trí trước khi di chuyển là $y$, thì bước này có chi phí là $a_y$.
- Hỏi tổng chi phí tối thiểu cho $i$ bước.

Ta có thể viết lại $f(i,j)$ như sau:
$$
f(i,j)=\min\limits_{j-i+1\le k\le j}\left(\sum\limits_{l=k}^{j}(a_l\times cnt_l)\right)
$$

với $k$ là vị trí trái cùng sau $i$ bước và $cnt_l$ là số lần vị trí $l$ xuất hiện trong dãy vị trí.

Dễ thấy rằng, để $f(i,j)$ tối ưu thì $a_k=\min\limits_{k\le l\le j}a_l$ nên được thoả mãn. Điều này có nghĩa là, ta nên di chuyển sang trái liên tục để đến vị trí $k$ sớm nhất có thể và ở yên tại đó.

Do đó, ta có thể viết lại $f(i,j)$ như sau:
$$
f(i,j)
=\min\limits_{j-i+1\le k\le j}\left(\sum\limits_{l=k+1}^{j}a_l + a_k\times(i-(j-k))\right)
$$

Từ đây, vì khi truy vấn ta biết được $i$ và $j$, mục tiêu biến đổi công thức tương tự như ở [Bài toán 1](##Bài-toán-1-Codeforces---660F-Bear-and-Bowling-4) là đưa công thức về dạng $K(k)\times X(i,j)+M(k)+const(i,j)$:

$$\begin{align*}
f(i,j)
&=\min\limits_{j-i+1\le k\le j}\left(\left[\sum\limits_{l=1}^{j}a_l - \sum\limits_{l=1}^{k}a_l\right] + a_k\times(i-j+k)\right) \\
&=\min\limits_{j-i+1\le k\le j}\left(prf_j - prf_k + a_k\times(i-j) + a_k\times k\right) \\
&=prf_j+\min\limits_{j-i+1\le k\le j}\left(a_k\times(i-j) + a_k\times k-prf_k\right)
\end{align*}$$

với $k$ là vị trí trái cùng sau $i$ bước và $prf_j=\sum\limits_{i=1}^ja_i$.

Đặt $K_k=a_k$ và $M_k=a_k\times k-prf_k$, $f(i,j)$ trở thành:
$$
f(i,j)=prf_j+\min\limits_{j-i+1\le k\le j}\left(K_k\times(i-j) + M_k\right)
$$

Đến đây, ta có thể áp dụng kĩ thuật bao lồi để giải. Để truy vấn trên tập các đường thẳng thuộc đoạn $[j-i+1,j]$, ta dựng cây [Segment Tree](/algo/data-structures/segment-tree-basic) với mỗi nút là 1 cấu trúc LineContainer.

##### Cài đặt
```cpp=1
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n;
int a[N];
int prf[N];

// với double, sử dụng INF = 1/.0 và div(a,b) = a/b
const int INF = INT_MAX;
struct Line {
    int a, b;
    mutable int p;
    bool operator<(const Line& o) const {
        if (o.a == INT_MAX && o.b == INT_MAX) return p < o.p;
        return a < o.a;
    }
};
struct LineContainer {
    multiset<Line> myLC;
    int div(int a, int b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(multiset<Line>::iterator x, multiset<Line>::iterator y) {
        if (y == myLC.end()) return x->p = INF, false;
        if (x->a == y->a) x->p = (x->b > y->b) ? INF : -INF;
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(int a, int b) {
        auto x = myLC.insert({ a, b, 0 }), y = next(x);
        while (isect(x, y)) y = myLC.erase(y);
        if ((y = x) != myLC.begin() && isect(--y, x)) isect(y, myLC.erase(x));
        while ((x = y) != myLC.begin() && (--x)->p >= y->p)
            isect(x, myLC.erase(y)), y = x;
    }
    int query(int x) {
        Line l = *myLC.lower_bound({ INT_MAX, INT_MAX, x });
        return l.a * x + l.b;
    }
} seg[N << 2];

void addLine(int u, int l, int r, int p, int k, int m) {
    seg[u].add(k, m);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (p <= mid)
            addLine(u << 1, l, mid, p, k, m);
        else addLine(u << 1 | 1, mid + 1, r, p, k, m);
    }
}
void init() {
    for (int i = 1; i <= n; ++i) {
        int k = a[i];
        int m = a[i] * i - prf[i];
        // đổi dấu tham số để truy vấn min
        addLine(1, 1, n, i, -k, -m);
    }
}
int query(int u, int l, int r, int a, int b, int x) {
    if (a <= l && r <= b) {
        // đổi dấu kết quả để truy vấn min
        return -seg[u].query(x);
    }
    if (b < l || r < a) return INT_MAX;

    int mid = (l + r) >> 1, u1 = u << 1, u2 = u1 | 1;
    return min(query(u1, l, mid, a, b, x), query(u2, mid + 1, r, a, b, x));
}

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        prf[i] = prf[i - 1] + a[i];
    }
    init();

    int m;
    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << prf[y] + query(1, 1, n, y - x + 1, y, x - y) << '\n';
    }
}
```

Độ phức tạp thời gian: $\mathcal{O}(N\log^2 N)$
Độ phức tạp không gian: $\mathcal{O}(N\log N)$

### Bài tập áp dụng
- [**Codeforces - 631E (Product Sum)**](https://codeforces.com/contest/631/problem/E)
- [**Codeforces - 311B (Cats Transport)**](https://codeforces.com/contest/311/problem/B)
- [**Codeforces - 673E (Levels and Regions)**](https://codeforces.com/contest/673/problem/E)
- [**Codeforces - 1179D (Fedor Runs for President)**](https://codeforces.com/contest/1179/problem/D)
- [**Codeforces Gym - 105383G (Game of Rounding)**](https://codeforces.com/gym/105383/problem/G)