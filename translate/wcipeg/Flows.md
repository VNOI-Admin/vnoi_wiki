# Bài toán luồng cực đại

**Nguồn:** [WCIPEG](http://wcipeg.com/wiki/Maximum_flow)

[[_TOC_]]

Trong bài viết này, tác giả sẽ giới thiệu với bạn 2 bài toán cơ bản: Bài toán luồng cực đại trên mạng và bài toán lát cắt hẹp nhất, cũng như mối liên hệ giữa 2 bài toán này.

# Mạng luồng (Flow network)

Mạng luồng là một đồ thị có hướng thỏa mãn:

* Có 2 đỉnh đặc biệt là **đỉnh phát** (**source**-ký hiệu $s$) và **đỉnh thu** (**sink**-ký hiệu $t$)
* Không có cung đi vào đỉnh phát hay ra từ đỉnh thu
* Với mỗi cung $(u,v)$ gọi một số thực dương $c(u,v)$ là sức chứa

Ta biểu diễn mạng luồng bằng $G=(V,s,t,c)$ với $s,t \in V$, $c:V \times V \rightarrow [0, \infty) $ và $\forall v, c(v,s)=c(t,v)=0$. Tồn tại cung $(u,v)$ khi và chỉ khi $c(u,v)>0$.

# Luồng hợp lệ (Admissible flows)

Một luồng hợp lệ trên mạng $G$ là một hàm $f:V\times V\rightarrow \mathbb{R}$ thỏa:

* Luồng trên mỗi cung không vượt quá sức chứa của nó: $\forall u,v \in V,f(u,v) \leq c(u,v)$
* Đối xứng: $\forall u,v \in V,f(u,v)=-f(v,u)$
* Bảo toàn luồng qua mỗi đỉnh: $\forall u \in V, \sum_{v \in V} f(u,v)=0$

# Mạng thặng dư (Residual network)

Mạng thặng dư cho chúng ta biết sức chứa còn lại trên mạng khi đã gửi một số luồng qua nó.

Từ một mạng $(V,s,t,c)$ và một luồng $f$ ta xây dựng một mạng thặng dư $(V,s,t,r)$ với $r(u,v)=c(u,v)-f(u,v)$.

Mạng thặng dư có thể chứa một số cung mà mạng ban đầu không có. Cụ thể, khi gửi một luồng $f(u,v)>0$ qua cung $(u,v)$ thì ta cũng gửi một luồng $-f(u,v)$ qua cung $(v,u)$, khi đó $r(v,u)=c(v,u)+f(u,v)>0$ có thể tạo ra cung $(v,u)$ mà mạng ban đầu chưa có.

# Bài toán luồng cực đại trên mạng (Maximum flow)

Cho một mạng, chúng ta cần tìm một luồng hợp lệ sao cho tổng luồng ra từ đỉnh phát cũng như đi vào đỉnh thu là cực đại.

**Mệnh đề:** Tổng luồng ra khỏi đỉnh phát bằng tổng luồng đi vào đỉnh thu.

**Chứng minh:** Xét luồng $f$ trên mạng $G$
Ta có:
$\sum_{u \in V} \sum_{v \in V} f(u,v)$
$=\sum_{u \in V} \sum_{v \in V} \frac{1}{2} (f(u,v)+f(u,v))$
$=\sum_{u \in V} \sum_{v \in V} \frac{1}{2} (f(u,v)-f(v,u))$
$=\frac{1}{2}\sum_{u \in V} \sum_{v \in V} f(u,v)-\frac{1}{2}\sum_{u \in V} \sum_{v \in V} f(v,u)$
$=\frac{1}{2}\sum_{u \in V} \sum_{v \in V} f(u,v)-\frac{1}{2}\sum_{u \in V} \sum_{v \in V} f(u,v)$
$=0$

Lại có:
$\sum_{u \in V} \sum_{v \in V} f(u,v)$
$=\sum_{u \in V \setminus \{s,t\}} \sum_{v \in V} f(u,v)+\sum_{v \in V}f(s,v)+\sum_{v \in V}f(t,v)$
$=0+\sum_{v \in V}f(s,v)-\sum_{v \in V}f(v,t)$

Vậy: $\sum_{v \in V}f(s,v)=\sum_{v \in V}f(v,t)$

# Thuật toán

## Phương pháp của Ford–Fulkerson

Ý tưởng chính của phương pháp của Ford-Fulkerson là tăng dần giá trị của luồng trên mạng cho đến khi nó đạt cực đại.

Với mỗi bước, trên mạng $G$ hiện tại, chúng ta tìm một đường đi $s-t$ mà vẫn có thể gửi luồng qua được, đường đi này gọi là **đường tăng luồng** (**augmenting path**). Sau đó tiến hành gửi một luồng qua $G$ sao cho luồng mới vẫn hợp lệ. Thuật toán kết thúc khi không còn tìm thấy đường tăng luồng nữa.

```
foreach (u,v) in E: f[u,v]<-0
while exist(augmenting_path):
    (u[1],u[2],...,u[k])<-augmenting_path
    m=min(c[u[i],u[i+1]]-f[u[i],u[i+1]]) for i=1..k-1
    for i=1..k-1: 
    	f[u[i],u[i+1]]+=m
        f[u[i+1],u[i]]-=m
```

Có nhiều cách tìm đường tăng luồng. Cách đơn giản nhất là chọn đường đi có ít cạnh nhất, cách này cho ta thuật toán của Edmond-Karp. Một cách hiệu quả hơn là phân tầng đồ thị theo khoảng cách tới đỉnh phát và chỉ quan tâm đến những đường đi mà các đỉnh thuộc các tâng khác nhau, đây gọi là thuật toán Dinic.

## Các thuật toán preflow-push

Lớp thuật toán **Preflow-push** khác với thuật toán sử dụng đường tăng luồng ở chỗ nó không duy trì luồng hợp lệ ở mỗi bước, mà thay vào đó duy trì một **preflow**, mà trong đó tổng luồng vào một đỉnh có thể lớn hơn tổng luồng ra từ đỉnh đó ($\sum_{u \in V}f(u,v) \geq \sum_{w \in V}f(v,w)$).

Đầu tiên chúng ta khởi tạo một preflow mà mỗi cung đi ra từ đỉnh phát đều bão hòa ($\forall u \in V, f(s,u)=c(s,u)$).

Với mỗi bước, chúng ta thử xả luồng một số đỉnh bị quá tải bằng cách gửi luồng sang một đỉnh kề của nó. Một số luồng cuối cùng sẽ đi về đỉnh thu, và mọi luồng không đi về đỉnh thu sẽ quay trở lại đỉnh phát.

## Các hướng tiếp cận khác

Một số phương pháp tinh vi hơn đã được giới thiệu bởi King, Rao và Tarjan (1994) và Orlin (2012). Kết hợp hai phương pháp cho ta một thuật toán tổng quát có độ phức tạp $O(VE)$, tối ưu nhất cho đến giờ phút này.

# Bài toán lát cắt hẹp nhất (Minimun $s-t$ cut)

Một lát cắt $s-t$ là một tập con của $E$ mà khi loại bỏ những cạnh này thì không còn đường đi từ $s$ tới $t$.

Trên một đồ thị có trọng số, lát cắt $s-t$ hẹp nhất là lát cắt $s-t$ có tổng trọng số các cạnh nhỏ nhất. Ta biểu diễn đồ thị này bằng $(V,E,s,t,w)$ với $w:E \rightarrow [0,\infty)$ là trọng số các cạnh đồ thị. Với những cạnh âm ta luôn có thể loại bỏ cạnh này ra khỏi đồ thị và thêm vào lát cắt.

Mỗi đồ thị $(V,E,s,t,w)$ tương ứng với một mạng luồng $(V,s,t,c)$, với $c(u,v)=w(u,v)$ nếu $(u,v) \in E$, ngược lại $c(u,v)=0$.

[**Max-flow min-cut theorem**](https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem) là một kết quả nổi tiếng về quan hệ giữa luồng cực đại và lát cắt hẹp nhất. Định lý này cho thấy rằng trên một mạng luồng thì giá trị luồng cực đại bằng với giá trị của lát cắt hẹp nhất. Do đó mà ta có thể sử dụng thuật toán luồng cực đại để giải bài toán lát cắt hẹp nhất (nhưng không ngược lại).

# Các biến thể của bài toán

Một số cạnh của đồ thị có thể không có sức chứa, ta chỉ cần cho cạnh này một sức chứa là một số cực kì lớn. Một cạnh không có sức chứa thì không thuộc lát cắt nhỏ nhất.

Mạng có thể có nhiều đỉnh phát và nhiều đỉnh thu. Ta có thể giải quyết bằng cách thêm một đỉnh phát ảo và một đỉnh thu ảo, và các cung có sức chứa vô hạn đi từ đỉnh phát ảo này tới các đỉnh phát, và từ các đỉnh thu đến đỉnh thu ảo.

Nếu mỗi đỉnh $v$ của mạng có một sức chứa $c(v)$ sao cho $c(v) \geq \sum_{u \in V} f(u,v)$, ta chia mỗi đỉnh $v$ thành một đỉnh vào $v_i$ và một đỉnh ra $v_o$, và khi đó $c(v)=c'(v_i,v_o)$. Với mỗi cạnh $(u,v)$ trên đồ thị gốc, ta tạo cung $(u_o,v_i)$ với $c(u,v)=c'(u_o,v_i)$. Sau đó có thể giải một cách bình thường.

Tương tự, với bài toán lát cắt nhỏ nhất cho phép loại bỏ các đỉnh giống như các cạnh ta cũng giải quyết như trên.

Ta cũng có thể sử dụng thuật toán luồng để giải các bài toán về [**cặp ghép cực đại**](https://en.wikipedia.org/wiki/Matching_(graph_theory)) trên đồ thị hai phía. Ta cũng tạo một đỉnh phát ảo nối với các đỉnh trái của đồ thị, và một đỉnh thu ảo nối từ các đỉnh phải, các cung này có trọng số là 0 (nếu cần). Tất cả các cung có sức chứa là 1. Sau đó ta sẽ tìm giá trị lát cắt hẹp nhất của đồ thị. Gía trị này chính là giá trị của bộ ghép cực đại trên đồ thị.

# Một số bài để luyện tập

- [SPOJ - NKFLOW](http://vn.spoj.com/problems/NKFLOW/)
- [SPOJ - FASTFLOW](http://vn.spoj.com/problems/FASTFLOW/)
- [SPOJ - ASSIGN1](http://vn.spoj.com/problems/ASSIGN1/)
- [SPOJ - KWAY](http://vn.spoj.com/problems/KWAY/)
- [codeforces - flows](http://codeforces.com/problemset/tags/flows)