# Luồng cực đại trên mạng - Maxflow network

[[_TOC_]]

# 0. Kiến thức cần biết

# 1. Ứng dụng

# 2. Phát biểu bài toán

Cho một mạng (network) có dạng một đồ thị vô hướng $G=(E,V)$ (V là tập đỉnh, E là tập cạnh) mỗi cạnh trên đồ thị $e=(u,v) thuộc E$ như một kênh chuyển tải nước giữa 2 đỉnh riêng biệt u, v trong đồ thị và có sức chứa là $c(e)=c[u,v]$. Trong mạng lưới có một đỉnh phát $s$ và một đỉnh thu $t$

**Yêu cầu**: với mỗi kênh truyền tải (e=(u,v) thuộc E) từ u đến v cần xác định giá trị $f[u,v] (f[u,v] <= c[u,v])$ được gọi là luồng (flow) trên kênh e sao cho với mọi $u thuộc tập V/{s,t}$ tổng $f(v,u)=f(u,w)$ v,w thuộc tập V/{s,t}$(tổng luồng đi vào u bằng tổng luồng đi ra). Hơn thế nữa ta cần tìm các giá trị f sao tổng luồng ra $f(s,v) v thuộc V$ là lớn nhất.

hình dưới đây biểu diễn một luồng cực đại trên mạng và mỗi cạnh của nó được gán nhãn là $f/c$ (giá trị dòng chảy và sức chứa của kênh)

![alt text](http://community.topcoder.com/i/education/maxFlow01.gif "Luồng cực đại figure 1.a")

# 3. cách giải bài toán

Trước hết để giải được bài toán ta biết hai khái hiệm mạng thằng dư (residual network) và đường tăng luồng (augment path)

## 3.1 mạng thặng dư - residual network

Mạng thặng dư G'(E',V') của mạng G(E,V) cho biết sức chứa còn lại trên mạng G(E,V) khi đã gửi một số luồng f* qua nó và được xây dựng như sau:
tập đỉnh V'= V và mỗi cạnh e(u,v) thuộc E có giá trị luồng là f[u,v] và sức chứa c[u,v] tương ứng với 2 cạnh e'(u,v)(cạnh xuôi) có f'[u,v]=f[u,v],c'[u,v]=c[u,v] và e'(v,u)(cạnh ngược) có f'[v,u]=-f[u,v] và c'[v,u]=0 (Có thể thấy tập cạnh xuôi trên G' chính là tập cạnh của G). Hình dưới đây sẽ diễn tả một đồ thị G và mạng thặng dư G' của nó


![alt text](http://community.topcoder.com/i/education/maxFlow02.gif "Luồng cực đại figure 2a")

![alt text](http://community.topcoder.com/i/education/maxFlow03.gif "Luồng cực đại figure 2b")

## 3.2 đường tăng luồng - augment path

Đường tăng luồng là một đường đi đơn từ đỉnh phát $s$ đến đỉnh thu $t$ trong mạng thặng dư G' mà kênh trên đường đi chưa bị bão hòa ( f'[u,v] < c'[u,v], một kênh e'(u,v) được gọi là bão hòa nếu f'(u,v)=c'(u,v)).

## 3.3 ví dụ

bằng việc xem xét đường tăng luồng s_A_C_t trên mạng thặng dư $?$ chúng ta có thể tăng luồng lên 1 vì s_A và A_C có thể cho một luồng có giá trị là 3 nhưng C_t chỉ có thể cho một luồng 1 đi qua, do đó ta sẽ lấy giá trị nhỏ nhất trên đường đi để thực hiện tăng giá trị luồng. Sau khi tăng luồng lên một ta có hình như sau:

![alt text](http://community.topcoder.com/i/education/maxFlow04.gif "Luồng cực đại figure 3a")

sau khi tăng luồng ta được một mạng mới với tổng giá trị luồng là 2 nhưng trong ví dụ 1.a ta thấy tổng luồng là 3 do đó luồng như trên vẫn có thể tăng luồng thêm nữa. Vậy một câu hỏi là ta sẽ tăng luồng như thế nào? hãy nhìn vào mạng thặng dư 3.b của đồ thị 3.a dưới đây

![alt text](http://community.topcoder.com/i/education/maxFlow05.gif "Luồng cực đại figure 3b")

Ta có thể thấy từ s đến t tồn tại một đường đi đơn (đường tăng luồn): s_A_C_B_D_E_t, ta sẽ sử dụng đường đi này để tăng các giá trị trên đường đi này một lượng bằng sức chứa nhỏ nhất (sức chứa của C_B nhỏ nhất và bằng 1), hình 1.b dưới đây là mạng thặng dư tương ứng của 3.a sau khi được tăng luồng

![alt text](http://community.topcoder.com/i/education/maxFlow06.gif "Luồng cực đại figure 1b")

## 3.4 thuật toán

Từ ví dụ trên ta có thể đi đến thuật toán như sau:
bước (1): Tạo mạng thặng dư G' tương ứng cho mạng G ban đầu
bước (2): tìm một đường tăng luồng trên mạng thặng dư G'
  - nếu không tồn tại đường tăng luồng ta kết thúc thuật toán
  - nếu tồn một đường tăng luồng ta thực hiện tăng luồng trên mạng thặng dư và cập nhật mạng thặng dư và quay trở lại (2)
Khi thuật toán kết thức giá trị tổng f(x,V') của các cạnh xuôi chính là giá trị luồng cực đại cần tìm.

Đến đây bạn đã có thể dùng thuật toán tìm kiếm trên đồ thị DFS (deep first search) hoặc BDF(breath first search) để tìm đường mở và cập nhật mạng thặng dư thuật toán này có độ phức tạp bằng *số lần tăng luồng* (f*) nhân với *độ phức tạp của thật toán tìm kiếm đồ thị-O(E)* và bằng $O(|f*|.E)$. Để hiểu rõ hơn về thuật toán và cách chứng minh bạn có thể đọc tiếp các phần sau

## 3.5 tính đúng dắn

### 3.5.1 Lát cắt s-t

Lát cắt là một các phân hoạch tập các đỉnh V trong mạng G thành 2 tập X và Y thỏa mãn đỉnh phát (đỉnh s) thuộc X và đỉnh thu (đỉnh t) thuộc Y. Ta có f(X, Y) = Tổng f(u,v) (u thuộc X và v thuộc Y). Ta có c(X, Y) = tổng c(u,v) (u thuộc X và v thuộc Y) ta có thể chứng mình được 2 điều sau:
    - f(X, Y) <= c(X, Y)
    - Giá trị luồng f* = f(X,Y)

### 3.5.2 Lát cắt s-t hẹp nhất

lát cắt hẹp nhất là lát cắt có f(X, Y) = c(X, Y). Từ khái niệm lát cắt và lát cắt nhỏ nhất ta có thể dẫn đến cách chứng minh sau

### 3.5.3 chứng minh

ta có thể chứng minh 3 nhận định sau là tương đương
(1) f là luồng cực đại trên mạng
(2) Mạng thặng dư G không có đường tăng luồng
(3) tồn tại (X,Y) là lát cắt hẹp nhất

(1) => (2): vì nếu tồn tại đường tăng luồng thì (1) sai
(2) => (3): nếu giả sử không tồn tại lát cắt hẹp nhất ta có thể tìm được đường tăng luồng
(3) => (1): Ta có thể thấy luôn f* = f(X, Y) <= c(X, Y), do đó f* là luồng cực đại vì nếu tồn tại một luồng ff* lớn hớn f* sẽ vô lý với nhận xét trong mục lát cắt s-t 3.5.1

## 3.6 Các thuật toán tìm đường mở

# 4. Bài toán liên quan