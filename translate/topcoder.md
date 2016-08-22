# Luồng cực đại trên mạng - maxflow network

[[_TOC_]]

# 0. Kiến thức cần biết

# 1. Ứng dụng

# 2. Phát biểu bài toán

Cho một mạng có dạng một đồ thị vô hướng $G=(E,V)$ (V là tập đỉnh, E là tập cạnh) mỗi cạnh trên đồ thị như một kênh chuyển tải nước giữa 2 đỉnh riêng biệt trong đồ thị và có sức chứa là $c$. Trong mạng lưới có một đỉnh phát $x$ và một đỉnh thu $y$

**Yêu cầu**: với mỗi kênh truyền tải (e thuộc E) cần xác định giá trị $fe (fe <= ce)$ tương ứng được gọi là giá trị dòng chảy (flow) sao cho với mỗi đỉnh $u thuộc tập V/{s,t}$ tổng $f(V,u)=f(u,V)$ (tổng giá trị dòng chảy đi vào u bằng tổng giá trị dòng chảy đi ra). Hơn thế nữa ta cần tìm các giá trị f sao Tổng $f(x,V)$ là lớn nhất.

hình dưới đây biểu diễn một luồng cực đại trên mạng và mỗi cạnh của nó được gán nhãn là $f/c$ (giá trị dòng chảy và sức chứa của kênh)

![alt text](http://community.topcoder.com/i/education/maxFlow01.gif "Luồng cực đại figure 1.a")

# 3. cách giải bài toán

Trước hết để giải được bài toán ta biết hai khái hiệm mạng thằng dư (residual network) và đường tăng luồng (augment path)

## 3.1 mạng thặng dư - residual network
Mạng thặng dư gồm các đỉnh và cạnh như đồ thị đã cho (ta gọi các cạnh này là các cạnh xuôi) nhưng sức chứa trên mỗi cạnh có thể giảm so với ban đầu và có thêm 1 một cạnh theo chiều ngược lại cho mỗi cạnh( ta gọi các cạnh này là các cạnh ngược). Cụ thể với mỗi cạnh $e thuộc E$ trong $G$ nếu giá trị dòng chảy $f (0 <= f <= c)$ khi đó cạnh xuôi $e$ sẽ chỉ có khả năng tải thêm $c - f$ và tương ứng ta cũng có một cạnh ngược e' theo chiều ngược lại có sức chứa bằng giá trị dòng chảy $c'=fe$. Trong bài này ta đặt mạng thặng dư là $G'$ hình 2b dưới đây miêu tả mạng thặng dư trong hình 2a

![alt text](http://community.topcoder.com/i/education/maxFlow02.gif "Luồng cực đại figure 2a")

![alt text](http://community.topcoder.com/i/education/maxFlow03.gif "Luồng cực đại figure 2b")

**chú ý:** trong một số tài liệu cạnh ngược trong mạng thặng dư có thể có sức chứa c' luôn bằng 0 và giá trị dòng chảy bằng giá trị đối của cạnh xuôi tương ứng hay bằng $-fe$, hai cách trên là tương đương nhau về mặt tính toán.

## 3.2 đường tăng luồng - augment path

Đường tăng luồng là một đường từ đỉnh phát $x$ đến đỉnh thu $y$ trong mạng thặng dư mà các cạnh có sức chứa dương.

## 3.3 ví dụ

bằng việc xem xét đường tăng luồng x_a_c_y trên mạng thặng dư 2b chúng ta có thể tăng luồng lên 1 - x_a và a_c có sức chứa là 3 nhưng c_y chỉ có sức chứa là 1, do đó ta sẽ lấy giá trị nhỏ nhất trên đường đi để thực hiện tăng giá trị luồng. Sau khi tăng luồng lên một ta có hình như sau:

![alt text](http://community.topcoder.com/i/education/maxFlow04.gif "Luồng cực đại figure 3a")

sau khi tăng luồng ta được một mạng mới với tổng giá trị luồng là 2 nhưng trong ví dụ 1.a ta thấy tổng luồng là 3 do đó luồng như trên vẫn có thể tăng luồng thêm nữa. Vậy một câu hỏi là ta sẽ tăng luồng như thế nào? hãy nhìn vào mạng thặng dư 3.b của đồ thị 3.a dưới đây

![alt text](http://community.topcoder.com/i/education/maxFlow05.gif "Luồng cực đại figure 3b")

Ta có thể thấy từ X đến Y tồn tại một đường đi đơn (đường tăng luồn): X_A_C_B_D_E_Y, ta sẽ sử dụng đường đi này để tăng các giá trị trên đường đi này một lượng bằng sức chứa nhỏ nhất (sức chứa của C_B nhỏ nhất và bằng 1), hình 1.b dưới đây là mạng thặng dư tương ứng của 3.a sau khi được tăng luồng

![alt text](http://community.topcoder.com/i/education/maxFlow06.gif "Luồng cực đại figure 1b")

## 3.4 thuật toán

Từ ví dụ trên ta có thể đi đến thuật toán như sau:
bước (1): Tạo mạng thặng dư G' tương ứng cho mạng G ban đầu
bước (2): tìm một đường tăng luồng trên mạng thặng dư G'
  - nếu không tồn tại đường tăng luồng ta kết thúc thuật toán
  - nếu tồn một đường tăng luồng ta thực hiện tăng luồng trên mạng thặng dư và cập nhật mạng thặng dư và quay trở lại (2)
Khi thuật toán kết thức giá trị tổng f(x,V') của các cạnh xuôi chính là giá trị luồng cực đại cần tìm.

Đến đây bạn đã có thể dùng thuật toán tìm kiếm trên đồ thị DFS (deep first search) hoặc BDF(breath first search) để tìm đường mở và cập nhật mạng thặng dư thuật toán này có độ phức tạp bằng số lần tăng luồng nhân với độ phức tạp của thật toán tìm kiếm đồ thị và bằng $O(|f*|.m)$ (|f*| là số lần tăng luồng và m là số cạnh của đồ thị). Để hiểu rõ hơn về thuật toán và cách chứng minh bạn có thể đọc tiếp các phần sau

## 3.5 tính đúng đắn của thật toán

để có thể chứng mình thuật toán trên trước hết ta cần tìm hiểu khái niệm lát cắt s-t và lát cắt s-t hẹp nhất

### 3.5.1 lát cắt s-t

Lát cắt s-t là một các phân hoạch tập các đỉnh E trong mạng thành 2 tập S_X và S_Y thỏa mãn đỉnh phát s(ví dụ trong hình là đỉnh x) thuộc S_X và đỉnh thu t(ví dụ trong hình là đỉnh y) thuộc S_Y. Ta có $f(X, Y) = bằng Tổng giá trị dòng chảy cạnh xuôi - tổng luồng ngược từ S_X sang S_Y trong mạng thặng dư. c(s_X, s_Y) = tổng c(u,v) (u thuộc S_X và v thuộc S_Y) ta có thể thấy f(S_X, S_Y) <= c(S_X, S_Y)

### 3.5.1 lát cắt s-t hẹp nhất

### 3.5.2 chứng minh

## 3.6 Các thuật toán tìm đường mở

# 4. Bài toán liên quan