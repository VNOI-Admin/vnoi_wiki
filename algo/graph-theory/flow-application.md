---
title: Ứng dụng của luồng trên mạng
description: 
published: true
date: 2026-02-25T05:55:46.171Z
tags: 
editor: markdown
dateCreated: 2026-02-25T05:49:41.942Z
---

# Ứng dụng của luồng trên mạng

**Tác giả:** 
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.

**Reviewer:**
- Nguyễn Tiến Mạnh - Đại học Bách khoa Hà Nội.
- Phạm Vũ Phương - Trường THPT Chuyên Hà Tĩnh, Hà Tĩnh.
- Nguyễn Hoàng Dương - Trường Đại học Công nghệ, ĐHQGHN.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

## Giới thiệu

Bài viết này nói về một số ứng dụng tiêu biểu và mở rộng của bài toán luồng trên mạng. Để nắm rõ nội dung trong bài viết, ta tham khảo nội dung có trong bài [Bài toán Luồng cực đại trên mạng](https://wiki.vnoi.info/algo/graph-theory/flow).

## Nhiều đỉnh nguồn, đỉnh thu

Giả sử ta được cho một mạng $G = (V, E)$ với vô số đỉnh nguồn ($s_1, s_2, \dots, s_n$) và đỉnh thu ($t_1, t_2, \dots, t_m$) và ta được yêu cầu phải tìm luồng cực đại trên mạng này. Ta có thể thay đổi bài toán trên thành bài toán tìm luồng cực đại trên mạng thông thường bằng cách thêm hai đỉnh có tên gọi là đỉnh **siêu nguồn (supersource)** $S$ và đỉnh **siêu thu (supersink)** $T$. Sau đó, ta thêm các cung nối $S$ với $s_1, s_2, \dots, s_n$ và $t_1, t_2, \dots, t_m$ với $T$ với sức chứa $\infty$. Bằng việc cho luồng đi qua từ đỉnh $S$ đến đỉnh $T$, về cơ bản ta đã tìm được luồng cực đại trên mạng gốc.

## Tìm các đường đi phân biệt cạnh

Ta có một đồ thị có hướng, và nhiệm vụ của ta là tìm $k$ đường đi từ đỉnh $s$ đến đỉnh $t$ sao cho các đường đi phân biệt cạnh (các cung trên đồ thị xuất hiện nhiều nhất một lần trong tất cả các đường đi). Ở ví dụ dưới đây, ta tìm được hai đường đi phân biệt cạnh được tô hai màu lục và đỏ trên đồ thị sau:

<center>
<img src="/algo/flow-application/flow_1.png" alt="Hai đường đi phân biệt cạnh">
</center>

Để giải quyết bài toán, ta xây dựng *mạng đơn vị* từ đồ thị có hướng trên (mạng đơn vị là mạng với các cạnh có sức chứa $1$). Nếu ta có thể cho $k$ luồng đi qua mạng này thì tức là ta đã tìm được $k$ đường đi phân biệt cạnh. 

Nếu ta được yêu cầu in ra các đường đi thì sau khi cho $k$ luồng $0 - 1$ (mỗi cạnh hoặc là không có luồng đi qua, hoặc là có đúng $1$ đơn vị luồng) đi qua mạng, ta có thể sử dụng các cạnh $e$ có $f(e) = 1$ để tìm các đường đi phân biệt cạnh:
- Bắt đầu từ đỉnh nguồn, xét đỉnh $u$ hiện tại, chọn cạnh $\{u, v\}$ có $f(\{u, v\}) = 1$ và di chuyển đến đỉnh $v$.
- Nếu đỉnh hiện tại không phải đỉnh thu, lặp lại bước trên.

Từ giá trị luồng cực đại của mạng đơn vị được xây dựng từ đồ thị gốc, ta có thể biết được số lượng tối đa đường đi phân biệt cạnh trên đồ thị sẽ bằng bao nhiêu từ định lí sau: 
> Tồn tại tối đa $k$ đường đi phân biệt cạnh khi và chỉ khi giá trị luồng cực đại bằng $k$.

Giả sử ta có luồng cực đại $f^*$. Khi $v(f^*) = k$, ta có một danh sách các cạnh $\{u, v\}$ với $f(\{u, v\}) = 1$. Từ danh sách cạnh này, ta có thể tìm được $k$ đường đi phân biệt luồng với phương pháp tìm các đường đi phân biệt luồng đã được nói ở trên.

### Vận dụng 

- [Hai đường đi](https://oj.vnoi.info/problem/hiway) (kết hợp với [luồng với chi phí cực tiểu](https://wiki.vnoi.info/algo/graph-theory/min-cost-flow))

### Mở rộng 

- [POTHOLE](https://www.spoj.com/problems/POTHOLE/)
- [VOI 09 Bài 2 - Nút st - xung yếu](https://oj.vnoi.info/problem/stnode)

## Sức chứa đỉnh

Một số mạng không những có sức chứa cạnh mà nó còn có cả sức chứa đỉnh.

Để giải quyết trường hợp này, ta có thể biến đổi mạng này thành một mạng thông thường bằng cách tạo hai đỉnh mới $u_{in}$, $u_{out}$ với mỗi đỉnh $u$ trong mạng. Ta nối hai đỉnh này bằng một cung có sức chứa bằng với sức chứa đỉnh.

<center>
<img src="/algo/flow-application/flow_2.png" alt="Sức chứa đỉnh">
</center>

Các cạnh $\{u, v\}$ trong mạng từ đây cũng được nối lại thành các cạnh $\{u_{out}, v_{in}\}$.

### Tìm các đường đi phân biệt đỉnh

Để tìm các đường đi từ đỉnh $s$ đến đỉnh $t$ trên đồ thị có hướng sao cho mỗi đỉnh xuất hiện nhiều nhất một lần trên tất cả các đường đi, ta sẽ xây dựng một mạng từ đồ thị có hướng. Ta tạo một mạng từ đồ thị và cho sức chứa của các cạnh với các đỉnh bằng $1$, sau đó ta giải bài toán theo cách tương tự với bài toán tìm các đường đi phân biệt cạnh.

## Cặp ghép trên đồ thị hai phía 

Các **bài toán cặp ghép (matching)** trong lí thuyết đồ thị yêu cầu ta tìm một danh sách cạnh sao cho các đỉnh đầu mút của các cạnh không giống nhau.

Ta sẽ tập trung giải quyết một biến thể của bài toán này: tìm cặp ghép trên [đồ thị hai phía](https://wiki.vnoi.info/algo/graph-theory/graph#%C4%91%E1%BB%93-th%E1%BB%8B-hai-ph%C3%ADa).

Để tìm cặp ghép cực đại trên đồ thị hai phía (Max Cardinality Bipartite Matching - MCBM), ta xây dụng một mạng đơn vị như sau:
- Nối đỉnh nguồn $s$ với các đỉnh $u \in X$ bằng một cung.
- Nối các đỉnh $u \in X$ với các đỉnh $v \in Y$ nếu $\{u, v\}$ là một cạnh trong đồ thị gốc.
- Nối các đỉnh $v \in Y$ với đỉnh thu $t$ bằng một cung.

<center>
<img src="/algo/flow-application/flow_3.png" alt="Cặp ghép cực đại">
</center>

Khi này, giá trị luồng cực đại của đồ thị bằng giá trị cặp ghép cực đại, với các cạnh $\{u, v\}$ thoả mãn $f(\{u, v\}) = 1$ là các cạnh trong cặp ghép.

Vì sức chứa của các cạnh bằng $1$, ta có thể sử dụng các thuật toán luồng cực đại đơn giản hơn như [Ford-Fulkerson](https://wiki.vnoi.info/algo/graph-theory/flow#ph%C6%B0%C6%A1ng-ph%C3%A1p-ford-fulkerson-thu%E1%BA%ADt-to%C3%A1n-edmonds-karp) để tìm luồng cực đại. 

### Vận dụng 
- [COCI 2020/2021 - Contest 3 - Selotejp](https://oj.vnoi.info/problem/coci2021_r3_selotejp)
- [VOI 16 Bài 5 - Tạo đề thi](https://oj.vnoi.info/problem/voiexam)
- [Phân công hoàn thành sớm nhất](https://oj.vnoi.info/problem/assign1)
- [AtCoder Beginner Contest 445 - Knight Placement](https://atcoder.jp/contests/abc445/tasks/abc445_g)

## Bài toán phân việc

Bài toán cặp ghép cực đại trên đồ thị hai phía là một phần nhỏ của **bài toán phân việc (assignment problem)**.

Một bài toán phân việc không trọng số trên đồ thị hai phía sẽ bao gồm hai tập hợp $X$ và $Y$. Nhiệm vụ của ta là tìm số lượng cặp $(x, y)$ nhiều nhất có thể với $x \in X, y \in Y$ với các điều kiện sau:
- Các phần tử $x \in X$ có thể xuất hiện trong tối đa $C(x)$ cặp.
- Các phần tử $y \in Y$ có thể xuất hiện trong tối đa $C(y)$ cặp.
- Các cặp $(x, y) \in X \times Y$ có thể xuất hiện tối đa $C(x, y)$ lần.

Bài toán cặp ghép cực đại trên đồ thị hai phía là một dạng đặc biệt của bài toán phân việc với $C(x), C(y) = 1$ và $C(x, y)$ bằng $0$ hoặc $1$ tuỳ vào việc cạnh $xy$ có tồn tại trong đồ thị hay không.

Ta có thể hình dung với bài toán ví dụ sau: có $n$ học sinh đi đến một thư viện, mỗi học sinh có nhu cầu mượn $C(x)$ cuốn sách. Trong thư viện có $m$ đầu sách khác nhau, mỗi đầu sách thì lại có $C(y)$ cuốn sách. Theo quy định của thư viện, mỗi học sinh chỉ được mượn tối đa $C(x, y)$ cuốn sách với mỗi đầu sách. Bạn, với tư cách là một thủ thư, sẽ cho các bạn học sinh mượn sách từ thư viện sao số số cuốn sách được cho mượn là nhiều nhất có thể.

Để giải bài toán này, ta xây dụng một mạng gần giống với bài toán cặp ghép cực đại, với những thay đổi về sức chứa của các cung như sau:
- Tạo các cung $\{s, x\}$ với sức chứa $C(x)$ với mỗi đỉnh $x \in X$. 
- Tạo các cung $\{y, t\}$ với sức chứa $C(y)$ với mỗi đỉnh $y \in Y$.
- Tạo các cung $\{x, y\}$ với sức chứa $C(x, y)$ với mỗi cặp $(x, y) \in X \times Y$.

Sau khi tìm được luồng cực đại của đồ thị, vì các giá trị luồng đi qua các cạnh là một số nguyên, ta có thể biết được các thông tin như sau:
- Các phần tử $x \in X$ xuất hiện trong $f(\{s, x\})$ cặp.
- Các phần tử $y \in Y$ xuất hiện trong $f(\{y, t\})$ cặp.
- Tồn tại $f(\{x, y\})$ cặp $(x, y) \in X \times Y$.

### Vận dụng

- [Chia nhóm](https://oj.vnoi.info/problem/mpart)

## Vòng loại bóng chày

Bài toán vòng loại bóng chày (baseball elimination) được phát biểu như sau: có một giải đấu bóng chày bao gồm $n$ đội, mỗi đội có $w_i$ trận thắng, $l_i$ trận thua, $r_i$ trận còn lại cần phải chơi, và $g_{i, j}$ trận với các đội $j$. Nhiệm vụ của ta là xét xem những đội nào không còn khả năng vô địch, tức là dù kết quả ra sao thì đội đó cũng không đứng nhất bảng. Ta giả sử không có trận hoà và tất cả trận đấu đều được diễn ra.

Dễ nhất, ta có thể xác định đội $x$ không có khả năng vô địch giải đấu nếu tồn tại một đội $y$ sao cho $w_x + r_x \lt w_y$. Ta không cần luồng để giải quyết trường hợp này.

Đối với các trường hợp còn lại, ta sử dụng luồng trên mạng để kiểm tra. Ta xây dựng mạng như sau:
- Nối đỉnh nguồn $s$ với các đỉnh $(i,j)$ tượng trưng cho trận đấu giữa hai đội bằng một cung có sức chứa $g_{i, j}$. Không tính các trận đấu có sự tham gia của đội $x$. Ta quy ước các đỉnh $(i, j)$ thuộc tập $X$.
- Nối các đỉnh $(i,j)$ với hai đỉnh $i$ và $j$ bằng một cung có sức chứa $\infty$. Ta quy ước các đỉnh $i, j$ thuộc tập $Y$.
- Nối các đỉnh $i$ với đỉnh thu $t$ bằng một cung có sức chứa $w_x + r_x - w_i$.

<center>
<img src="/algo/flow-application/flow_4.png" alt="Vòng loại bóng chày">
</center>

Đội $x$ không có khả năng vô địch nếu tập $S^*$ trong lát cắt cực tiểu $(S^*, T^*)$ (sau khi thực hiện lát cắt cực tiểu $s - t$, tập hợp đỉnh được chia làm $2$ phần: tập $S^*$ là một tập con chứa đỉnh nguồn $s$, tập $T^*$ là tập chứa các đỉnh còn lại) tồn tại một tập con $R$ sao cho $R \subseteq Y$ và điều kiện dưới đây thoả mãn:

$$ \frac{\sum_{i \in R}w_i + \frac{1}{2} \sum_{i,j \in R, \\ i \neq j} g_{i,j}}{|R|} \gt w_x + r_x$$

Đơn giản hơn, ta có thể xác định đội $x$ có khả năng vô địch giải đấu nếu giá trị luồng cực đại $v(f^*)$ bằng tổng sức chứa $g_{i, j}$ các cung $\\{s, (i, j)\\}$ và không thể nếu ngược lại.

Nếu bài toán có điều kiện rằng nhiều đội đồng hạng nhất thì không có nhà vô địch thì ta sửa lại sức chứa các cung $\{i,t\}$ bằng $w_x + r_x - w_i - 1$. 

### Vận dụng

- [Bedao OI Contest 3 - Chess](https://oj.vnoi.info/problem/bedao_oi3_c)
- [Lịch thi đấu bóng đá](https://oj.vnoi.info/problem/bongda)
- [Vòng loại World Cup châu Á](https://oj.vnoi.info/problem/soccer)

## Chọn dự án

Bài toán chọn dự án được phát biểu như sau: hiện tại có một công ty đang thực hiện $n$ dự án $P$, mỗi dự án sẽ đem về số tiền $p_i$. Các dự án có thể sinh lời ($p_i > 0$ - các khoá học, khu vui chơi, mở cửa hàng, v.v.) hoặc thu lỗ ($p_i < 0$ - xây dựng cơ sở hạ tầng, cập nhật trang thiết bị, v.v.). Các dự án có thể phụ thuộc lẫn nhau, được biểu thị bằng các cặp trong $E$, ví dụ: nếu $\{u, v\} \in E$, thì nếu thực hiện dự án $u$ thì trước tiên ta cần phải thực hiện dự án $v$. Nhiệm vụ của ta là chọn các dự án sao cho thoả mãn điều kiện, đồng thời số tiền thu được từ các dự án phải lớn nhất có thể.

<center>
<img src="/algo/flow-application/flow_5.png" alt="Các dự án và các yêu cầu">

<sup>Các dự án sinh lời là các ô tròn, các dự án thu lỗ là các ô vuông, các mũi tên chỉ sự phụ thuộc của các dự án</sup>
</center>

Ta sẽ xây dựng mạng để giải quyết bài toán trên:
- Nối đỉnh nguồn $s$ với các dự án $u$ sinh lời $p_u > 0$ bằng một cung với sức chứa $p_u$.
- Nối các dự án $v$ thu lỗ $p_v < 0$ với đỉnh thu $t$ bằng một cung với sức chứa $-p_v$.
- Nối các cặp dự án phụ thuộc lẫn nhau $\{u, v\} \in E$ bằng một cung với sức chứa $\infty$.

Ta quy ước $p_s = p_t = 0$.

Số tiền ta thu được, đồng thời cũng là lợi nhuận tối đa, bằng:
- $C - c(S^*, T^*)$ với $C = \sum_{p_u > 0} p_u$ và $c(S^*, T^*)$ là giá trị của lát cắt cực tiểu.
- $\sum_{u \in S^*} p_u$ với $S^*$ là tập hợp các đỉnh trong lát cắt cực tiểu $(S^*, T^*)$.

<center>
<img src="/algo/flow-application/flow_6.png" alt="Các dự án được chọn giúp tối ưu hoá lợi nhuận">

<sup>Các dự án sinh lời là các ô tròn, các dự án thu lỗ là các ô vuông, các mũi tên chỉ sự phụ thuộc của các dự án</sup>
</center>

Ta có $C = 17$, $c(S^*, T^*) = 6$, suy ra lợi nhuận tối đa sẽ bằng $11$.

Ta có thể chứng minh lí do vì sao lợi nhuận tối đa của các dự án được chọn lại có giá trị bằng $C - c(S^*, T^*)$ và $\sum_{u \in S^*} p_u$:

:::spoiler Chứng minh
Vì mạng tồn tại các cạnh có sức chứa $\infty$, nên lát cắt cực tiểu sẽ chỉ bao gồm các cung $\{s, u\}$ và $\{v, t\}$. Khi này, $c(S^*, T^*)$ sẽ bằng: 

$$\sum_{u \in T^*, p_u > 0} p_u + \sum_{u \in S^*, p_u < 0} (-p_u)$$
Từ đây, với $C = \sum_{p_u > 0} p_u$, ta suy ra:

$$
\begin{align*}
C - c(S^*, T^*) &= \sum_{p_u > 0} p_u - \left(\sum_{u \in T^*, p_u > 0} p_u + \sum_{u \in S^*, p_u < 0} (-p_u)\right) \\\\
&= \left(\sum_{p_u > 0} p_u - \sum_{u \in T^*, p_u > 0} p_u\right) - \sum_{u \in S^*, p_u < 0} (-p_u) \\\\
&= \sum_{u \in S^*, p_u > 0} p_u - \sum_{u \in S^*, p_u < 0} p_u \\\\
&= \sum_{u \in S^*} p_u
\end{align*}
$$
:::

### Vận dụng

- [VOI 14 Bài 6 - Chọn Công Việc](https://oj.vnoi.info/problem/jobset)
- [Space Shuttle Experiments](https://oj.vnoi.info/problem/spse)
- [Thử nghiệm sản phẩm](https://oj.vnoi.info/problem/codetour24_c3_a)

## Lưu thông theo cung cầu

**Bài toán lưu thông theo cung cầu (circulation with demands)** là một bài toán về một mạng $G = (V, E)$ nhiều đỉnh nguồn và đỉnh thu. Mỗi đỉnh nguồn $s_i$, hay đỉnh "cung" theo cách gọi của bài toán, sẽ có giá trị $d(s_i) < 0$, tức là đỉnh nguồn này có khả năng gửi đi $-d(s_i)$ đơn vị luồng. Các đỉnh thu $t_j$, hay đỉnh "cầu", sẽ có giá trị $d(t_j) > 0$, tức là các đỉnh thu này có khả năng nhận $d(t_j)$ đơn vị luồng. Các đỉnh còn lại trong đồ thị sẽ có giá trị $d = 0$.

<center>
<img src="/algo/flow-application/flow_7.png" alt="lưu thông theo cung cầu">
</center>

Khi thực hiện **lưu thông** trên mạng, ta cần thoả mãn hai điều kiện:
1. Với mỗi cạnh $e \in E$, $0 \le f(e) \le c(e)$
2. Với mỗi đỉnh $u \in V$, $f^{in}(u) - f^{out}(u) = d(u)$
 
Dễ thấy, điều kiện để có lưu thông trên mạng là:

$$\sum_{u, d(u) > 0} d(u) = \sum_{u, d(u) < 0} -d(u) = D$$

Từ đây, ta xây dựng một mạng mới $G^{'} = G$ với các thay đổi:
- Thêm đỉnh siêu nguồn $S$ và đỉnh siêu thu $T$
- Nối đỉnh $S$ với từng đỉnh nguồn $s$ bằng cung có sức chứa $-d_s$.
- Nối các đỉnh thu $t$ với đỉnh $T$ bằng cung có sức chứa $d_t$.

Ta xác định mạng $G$ có thể thực hiện lưu thông nếu giá trị luồng cực đại của $G^{'}$ bằng $D$.

### Trường hợp có cận dưới

Một số bài toán lưu thông theo cung cầu sẽ cho ta thêm điều kiện cận dưới cho các cung trên đồ thị. Cụ thể hơn, gọi giá trị $l(e)$ là cận dưới của cạnh $e = \{u, v\}$. Khi này, lượng luồng $f(e)$ đi qua cạnh $e$ phải thoả mãn: $$l(e) \le f(e) \le c(e)$$

<center>
<img src="/algo/flow-application/flow_8.png" alt="Trường hợp có cận dưới">
</center>

Ý tưởng của bài toán này khá đơn giản: ta sẽ cho đỉnh $u$ cung cấp một lượng luồng $l(e)$ đi qua cạnh $e$. Sau khi đã cho $l(e)$ đơn vị luồng đi qua, ta cập nhật lại các giá trị liên quan: $d(u)$ thành $d(u) - l(e)$, $d(v)$ thành $d(v) + l(e)$, $c(e)$ thành $c(e) - l(e)$.

<center>
<img src="/algo/flow-application/flow_9.png" alt="Giải pháp cho trường hợp có cận dưới">
</center>

Sau khi đã cập nhật xong, ta thực hiện việc giải quyết bài toán này như bình thường.

Giả sử ta có $f^*(e)$ là lượng luồng đi qua cạnh $e$ sau khi cập nhật các giá trị. Từ đây, lượng luồng $f(e)$ đi qua cạnh $e$ ban đầu sẽ bằng:

$$f(e) = f^*(e) + l(e)$$

### Vận dụng 

- [Minimum Cost b-flow](https://judge.yosupo.jp/problem/min_cost_b_flow)