# Range Minimum Query và Lowest Common Ancestor

[[_TOC_]]

## Các định nghĩa

Gỉa sử thuật toán có thời gian tiền xử lý là $f(n)$ và thời gian truy vấn $g(n)$. Ta ký hiệu độ phức tạp tổng quát của thuật toán là $< f(n),g(n) >$.

Vị trí của phần tử có giá trị nhỏ nhất trong đoạn từ $i$ đến $j$ của mảng $A$ là $RMQ_A(i,j)$.

Nút xa gốc nhất và là tổ tiên của cả 2 nút $u$ và $v$ trong cây có gốc $T$ là $LCA_T(u,v)$

## Range Minimum Query (RMQ)

Cho mảng $A[0,N-1]$. Tìm vị trí của phần tử có giá trị nhỏ nhất trong một đoạn cho trước.

![](http://community.topcoder.com/i/education/lca/RMQ_001.gif)

### Thuật toán tầm thường

Lưu giá trị của $RMQ_A(i,j)$ trong một bảng $M[0,N-1][0,N-1]$.

Thuật toán sẽ có độ phức tạp $< O(N^3),O(1) >$. Tuy nhiên ta có thể sử dụng quy hoạch động để giảm độ phức tạp xuống $< O(N^2),O(1) >$ như sau:

~~~cpp
void process1(int M[MAXN][MAXN], int A[MAXN], int N)
  {
      int i, j;
      for (i = 0; i < N; i++)
          M[i][i] = i;
      for (i = 0; i < N; i++)
          for (j = i + 1; j < N; j++)
              if (A[M[i][j - 1]] < A[j])
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = j;
  }
~~~

Có thể thấy thuật toán này khá chậm và tốn bộ nhớ $O(N^2)$ nên sẽ không hữu ích với những dữ liệu lớn hơn.

### Thuật toán $< O(N),O(\sqrt N) >$

Một ý tưởng độc đáo là chia mảng thành $\sqrt N$ phần. Ta sử dụng một vector $M[0,\sqrt N]$ để lưu giá trị mỗi phần. $M$ có thể dễ dàng tính được trong $O(N)$:

![](http://community.topcoder.com/i/education/lca/RMQ_002.gif)

Để tính $RMQ_A(i,j)$, chúng ta xét giá trị $M$ của $\sqrt N$ phần nằm trong đoạn $[i,j]$, và những phần tử ở đầu và cuối đoạn $[i,j]$ là giao giữa các phần. Ví dụ, để tính $RMQ_A(2,7)$ ta chỉ cần so sánh $A[2]$, $A[M[1]]$, $A[6]$ và $A[7]$.

Dễ thấy thuật toán không sử dụng quá $3\sqrt N$ phép toán cho mỗi truy vấn.

### Sparse Table (ST)

Đây là một hướng tiếp cận tốt hơn để tiền xử lý $RMQ$ cho các đoạn con có độ dài $2^k$, sử dụng quy hoạch động.

Ta sử dụng mảng $M[0,N-1][0,log_N]$ với $M[i][j]$ là chỉ số của phần tử có giá trị nhỏ nhất trong đoạn có độ dài $2^j$ và bắt đầu ở $i$. Ví dụ:

![](http://community.topcoder.com/i/education/lca/RMQ_003.gif)

Để tính $M[i][j]$, ta xét $M$ của 2 nửa đầu và nửa cuối của đoạn, mỗi phần sẽ có độ dài $2^{j-1}$:

![](http://community.topcoder.com/i/education/lca/RMQ_007.gif)

~~~cpp
 void process2(int M[MAXN][LOGMAXN], int A[MAXN], int N)
  {
      int i, j;

  //initialize M for the intervals with length 1
      for (i = 0; i < N; i++)
          M[i][0] = i;
  //compute values from smaller to bigger intervals
      for (j = 1; 1 << j <= N; j++)
          for (i = 0; i + (1 << j) - 1 < N; i++)
              if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }
~~~

Để tính $RMQ_A(i,j)$ ta dựa vào 2 đoạn con độ dài $2^k$ phủ hết $[i,j]$, với $k=log_{j-i+1}$:

![](http://community.topcoder.com/i/education/lca/RMQ_005.gif)

Độ phức tạp tổng quát của thuật toán này là $< O(Nlog_N),O(1) >$

### Cây phân đoạn (segment tree, interval tree, range tree)

Ta biểu diễn cây bằng một mảng $M[1,2*2^{[log_N]+1}]$ với $M[i]$ là vị trí có giá trị nhỏ nhất trong đoạn mà nút $i$ quản lý.

![](http://community.topcoder.com/i/education/lca/RMQ_004.gif)

Khởi tạo:

~~~cpp
  void initialize(intnode, int b, int e, int M[MAXIND], int A[MAXN], int N)
  {
      if (b == e)
          M[node] = b;
      else
       {
  //compute the values in the left and right subtrees
          initialize(2 * node, b, (b + e) / 2, M, A, N);
          initialize(2 * node + 1, (b + e) / 2 + 1, e, M, A, N);
  //search for the minimum value in the first and 
  //second half of the interval
          if (A[M[2 * node]] <= A[M[2 * node + 1]])
              M[node] = M[2 * node];
          else
              M[node] = M[2 * node + 1];
      }
  }
~~~

Truy vấn:

~~~cpp
int query(int node, int b, int e, int M[MAXIND], int A[MAXN], int i, int j)
  {
      int p1, p2;

  //if the current interval doesn't intersect 
  //the query interval return -1
      if (i > e || j < b)
          return -1;

  //if the current interval is included in 
  //the query interval return M[node]
      if (b >= i && e <= j)
          return M[node];

  //compute the minimum position in the 
  //left and right part of the interval
      p1 = query(2 * node, b, (b + e) / 2, M, A, i, j);
      p2 = query(2 * node + 1, (b + e) / 2 + 1, e, M, A, i, j);

  //return the position where the overall 
  //minimum is
      if (p1 == -1)
          return M[node] = p2;
      if (p2 == -1)
          return M[node] = p1;
      if (A[p1] <= A[p2])
          return M[node] = p1;
      return M[node] = p2;
  }
~~~

Mỗi truy vấn sẽ được thực hiện trong $O(log_N)$ và thuật toán có độ phức tạp tổng quát là $< O(N),O(log_N) >$

## Lowest Common Ancestor (LCA)

Cho cây có gốc $T$ và 2 nút $u$ và $v$ của cây. Tìm nút xa gốc nhất mà là tổ tiên của cả 2 nút $u$ và $v$.

![](http://community.topcoder.com/i/education/lca/LCA_001.gif)

### Thuật toán $< O(N),O(\sqrt N) >$

Ý tưởng chia input thành các phần bằng nhau như trong bài toán $RMQ$ cũng có thể được sử dụng với $LCA$. Chúng ta sẽ chia cây thành $\sqrt H$ phần, với $H$ là chiều cao cây. Phần đầu bao gồm các tầng từ $0$ đến $\sqrt H-1$, phần 2 sẽ gồm các tầng từ $\sqrt H$ đến $2\sqrt H-1$,...:

![](http://community.topcoder.com/i/education/lca/LCA_002.gif)

Giờ với mỗi nút chúng ta có thể biết được nút tổ tiên ở phần ngay trên nó. Ta sẽ tính giá trị này sử dụng mảng $P[1,MAXN]$:

![](http://community.topcoder.com/i/education/lca/LCA_003.gif)

Ta có thể tính $P$ bằng DFS ($T[i]$ là cha của $i$, $nr=\sqrt H$ và $L[i]$ là tầng của nút $i$)

~~~cpp
void dfs(int node, int T[MAXN], int N, int P[MAXN], int L[MAXN], int nr)  {
      int k;

  //if node is situated in the first 
  //section then P[node] = 1
  //if node is situated at the beginning
  //of some section then P[node] = T[node]
  //if none of those two cases occurs, then 
  //P[node] = P[T[node]]
      if (L[node] < nr)
          P[node] = 1;
      else
          if(!(L[node] % nr))
              P[node] = T[node];
          else
              P[node] = P[T[node]];

     for each son k of node
         dfs(k, T, N, P, L, nr);
  }
~~~

Truy vấn:

~~~cpp
 int LCA(int T[MAXN], int P[MAXN], int L[MAXN], int x, int y)
  {
  //as long as the node in the next section of
  //x and y is not one common ancestor
  //we get the node situated on the smaller
  //lever closer
      while (P[x] != P[y])
          if (L[x] > L[y])
             x = P[x];
          else
              y = P[y];

  //now they are in the same section, so we trivially compute the LCA
      while (x != y)
          if (L[x] > L[y])
             x = T[x];
          else
             y = T[y];
      return x;
  }
~~~

Hàm này sử dụng tối đa $2\sqrt H$ phép toán. Với cách tiếp cận này chúng ta có thuật toán $< O(N),O(\sqrt H) >$, trong trường hợp tệ nhất thì $N=H$ nên độ phức tạp tổng quát của thuật toán là $< O(N),O(\sqrt N) >$.

### Thuật toán $< O(NlogN),O(logN) >$

Ứng dụng quy hoạch động chúng ta có một thuật toán nhanh hơn. Đầu tiên chúng ta tính một bảng $P[1,N][1,log_N]$ với $P[i][j]$ là tổ tiên thứ $2^j$ của $i$:

![](https://community.topcoder.com/i/education/lca/LCA_005.gif)

Code:

~~~cpp
 void process3(int N, int T[MAXN], int P[MAXN][LOGMAXN])
  {
      int i, j;

  //we initialize every element in P with -1
      for (i = 0; i < N; i++)
          for (j = 0; 1 << j < N; j++)
              P[i][j] = -1;

  //the first ancestor of every node i is T[i]
      for (i = 0; i < N; i++)
          P[i][0] = T[i];

  //bottom up dynamic programing
      for (j = 1; 1 << j < N; j++)
         for (i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
  }
~~~

Phương pháp này tốn $O(log_N)$ cả về bộ nhớ lẫn thời gian.

Gọi $L[i]$ là tầng của $i$. Để tính $LCA(p,q)$ thì đầu tiên chúng ta cần đảm bảo nó cùng nằm trên một tầng

* Đưa $p$ và $q$ về cùng một tầng: giả sử $L[p]>L[q]$, việc đưa $p$ và $q$ về cùng tầng cũng giống như việc chuyển $L[p]-L[q]$ sang hệ cơ số $2$ vậy. Duyệt $j$ từ $log_{L[p]}$ xuống $0$, nếu tổ tiên thứ $2^j$ của $p$ không cao hơn $q$ thì ta cho $p$ nhảy lên tổ tiên thứ $2^j$ của nó.

* Sau khi $p$ và $q$ đã ở cùng tầng, ta sẽ tính $RMQ(p,q)$: cũng như trên, ta sẽ duyệt $j$ từ $log_{L[p]}$ xuống $0$, nếu tổ tiên thứ $2^j$ của $p$ và $q$ khác nhau thì chắc chắn $RMQ(p,q)$ sẽ ở cao hơn, khi đó ta sẽ cho cả $p$ và $q$ nhảy lên tổ tiên thứ $2^j$ của nó. Cuối cùng thì $p$ và $q$ sẽ có cùng cha, vậy nên khi đó $RMQ(p,q)=T[p]=T[q]$.

Code:

~~~cpp

int query(int N, int P[MAXN][LOGMAXN], int T[MAXN], 
  int L[MAXN], int p, int q)
  {
      int tmp, log, i;
   
  //if p is situated on a higher level than q then we swap them
      if (L[p] < L[q])
          tmp = p, p = q, q = tmp;
  
  //we compute the value of [log(L[p)]
      for (log = 1; 1 << log <= L[p]; log++);
      log--;
   
  //we find the ancestor of node p situated on the same level
  //with q using the values in P
      for (i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q])
              p = P[p][i];
   
      if (p == q)
          return p;
   
  //we compute LCA(p, q) using the values in P
      for (i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i])
              p = P[p][i], q = P[q][i];
   
      return T[p];
  }
~~~

Mỗi lần gọi hàm này chỉ tốn tối đa $2log_H$ phép toán. Trong trường hợp tệ nhất thì $H=N$ nên độ phức tạp tổng quát của thuật toán này là $< O(Nlog_N),O(log_N) >.

## Từ LCA đến RMQ

Ta có thể giảm bài toán LCA lại thành bài toán RMQ trong thời gian tuyến tính, do đó mà mọi thuật toán để giải bài toán RMQ đều có thể sử dụng để giải bài toán LCA. Hãy cùng xét ví dụ sau:

![](http://community.topcoder.com/i/education/lca/LCA_006.gif)

![](http://community.topcoder.com/i/education/lca/LCA_007.gif)

Để ý rằng $LCA_T(u,v)$ là nút gần gốc nhất xuất hiện giữa lúc thăm $u$ và $v$ trong phép duyệt DFS. Vì thế ta có thể xét tất cả các phần tử giữa các cặp chỉ số bất kì của $u$ và $v$ trong dãy Euler Tour và tìm nút cao nhất. Ta xây dựng 3 mảng:

* $E[1,2*N-1]$: dãy thứ tự thăm của các nút trên đường đi Euler, $E[i]$ là nút được thăm thứ $i$ trên đường đi.

* $L[1,2*N-1]$: tầng của các nút, $L[i]$ là tầng của nút $E[i]$

* $H[1,N]$: $H[i]$ là vị trí xuất hiện đầu tiên của nút $i$ trên Euler Tour

Gỉa sử $H[u]<H[v]$. Dễ thấy việc cần làm lúc này là tìm nút có $L$ nhỏ nhất trên $E[H[u]..H[v]]$. Do đó $LCA_T(u,v)=E[RMQ_L(H[u],H[v]))]. Ví dụ:

 ![](http://community.topcoder.com/i/education/lca/LCA_008.gif)

Cũng dễ thấy là mỗi 2 phần tử liên tiếp trong $L$ đều hơn kém nhau đúng 1 đơn vị.

## Từ RMQ đến LCA

Một cây Cartesian của một dãy $A[0,N-1]$ là một cây nhị phân $C(A)$ có gốc là phần tử nhỏ nhất trong $A$ và có vị trí $i$. Cây con trái của $C(A)$ là cây Cartesian của $A[0,i-1]$ nếu $i>0$, ngược lại thì không có. Cây con phải của $C(A)$ là cây Cartesian của $A[i+1,N-1]$.

Dễ thấy rằng $RMQ_A(i,j)=LCA_C(i,j)$.

 ![](http://community.topcoder.com/i/education/lca/LCA_009.gif)

 ![](http://community.topcoder.com/i/education/lca/LCA_010.gif)

Bây giờ việc cần làm chỉ còn là tính $C(A)$ trong thời gian tuyến tính. Chúng ta sẽ sử dụng một cái stack.

* Ban đầu stack rỗng. Ta lần lượt đẩy các phần tử của $A$ vào stack.

* Tại bước thứ $i$, $A[i]$ sẽ được đẩy vào ngay cạnh phần tử cuối cùng không lớn hơn $A[i]$ trong stack, các phần tử lớn hơn $A[i]$ bị loại khỏi stack. Phần tử trong stack ở vị trí của $A[i]$ trước khi chèn $A[i]$ vào sẽ là con trái của $i$, còn $i$ sẽ là con phải của phần tử trước nó trong stack. Ở mỗi bước thì phần tử đầu tiên trong stack sẽ là gốc của cây Cartesian.

Ví dụ đối với cây ở trên:

<div style="font-family: 'Lucida Grande', 'Segoe UI', 'Apple SD Gothic Neo', 'Malgun Gothic', 'Lucida Sans Unicode', Helvetica, Arial, sans-serif; font-size: 0.9em; overflow-x: hidden; overflow-y: auto; margin: 0px !important; padding: 5px 20px 26px !important; background-color: rgb(255, 255, 255);font-family: 'Hiragino Sans GB', 'Microsoft YaHei', STHeiti, SimSun, 'Lucida Grande', 'Lucida Sans Unicode', 'Lucida Sans', 'Segoe UI', AppleSDGothicNeo-Medium, 'Malgun Gothic', Verdana, Tahoma, sans-serif; padding: 20px;padding: 20px; color: rgb(34, 34, 34); font-size: 15px; font-family: 'Roboto Condensed', Tauri, 'Hiragino Sans GB', 'Microsoft YaHei', STHeiti, SimSun, 'Lucida Grande', 'Lucida Sans Unicode', 'Lucida Sans', 'Segoe UI', AppleSDGothicNeo-Medium, 'Malgun Gothic', Verdana, Tahoma, sans-serif; line-height: 1.6; -webkit-font-smoothing: antialiased; background: rgb(255, 255, 255);"><table style="padding: 0px; border-collapse: collapse; border-spacing: 0px; margin-bottom: 16px;background-color: rgb(250, 250, 250);">
<thead>
<tr>
<th style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;font-weight: bold;border: 1px solid rgb(230, 230, 230);">Bước</th>
<th style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;font-weight: bold;border: 1px solid rgb(230, 230, 230);">Stack</th>
<th style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;font-weight: bold;border: 1px solid rgb(230, 230, 230);">Sự hình thành cây</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">0</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">0</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">0 là nút duy nhất trong cây</td>
</tr>
<tr style="background-color: rgb(242, 242, 242);">
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">1</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">0 1</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">1 được đẩy vào cuối stack. Giờ 1 là con phải của 0</td>
</tr>
<tr>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">2</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">0 2</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">2 được đẩy vào cạnh 0, 1 bị xóa vì (<span style="margin-top: 0px;margin-bottom: 0px;"><span class="MathJax_Preview" style="color: rgb(136, 136, 136);"></span><span class="MathJax" id="MathJax-Element-279-Frame" role="textbox" aria-readonly="true" style="display: inline; font-style: normal; font-weight: normal; line-height: normal; font-size: 100%; text-indent: 0px; text-align: left; text-transform: none; letter-spacing: normal; word-spacing: normal; word-wrap: normal; white-space: nowrap; float: none; direction: ltr; max-width: none; max-height: none; min-width: 0px; min-height: 0px; border: 0px; padding: 0px; margin: 0px;"><nobr style="border: 0px; padding: 0px; margin: 0px; max-width: 5000em; max-height: 5000em; min-width: 0px; min-height: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;white-space: nowrap !important;-webkit-transition: none; transition: none;"><span class="math" id="MathJax-Span-2369" style="width: 6.083em; display: inline-block;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span style="display: inline-block; position: relative; width: 4.973em; height: 0px; font-size: 122%;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span style="position: absolute; clip: rect(1.764em 1000em 3.092em -0.457em); top: -2.678em; left: 0em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span class="mrow" id="MathJax-Span-2370" style="display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span class="mi" id="MathJax-Span-2371" style="font-family: MathJax_Math; font-style: italic;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">A</span><span class="mo" id="MathJax-Span-2372" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">[</span><span class="mn" id="MathJax-Span-2373" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">2</span><span class="mo" id="MathJax-Span-2374" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">]</span><span class="mo" id="MathJax-Span-2375" style="font-family: MathJax_Main; padding-left: 0.278em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">&lt;</span><span class="mi" id="MathJax-Span-2376" style="font-family: MathJax_Math; font-style: italic; padding-left: 0.278em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">A</span><span class="mo" id="MathJax-Span-2377" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">[</span><span class="mn" id="MathJax-Span-2378" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">1</span><span class="mo" id="MathJax-Span-2379" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">]</span></span><span style="display: inline-block; width: 0px; height: 2.678em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"></span></span></span><span style="border-left-width: 0em; border-left-style: solid; display: inline-block; overflow: hidden; width: 0px; height: 1.353em; vertical-align: -0.372em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"></span></span></nobr></span><script type="math/tex" id="MathJax-Element-279">A[2] < A[1]</script></span>). Lúc này 2 là con phải của 0 và con trái của 2 là 1</td>
</tr>
<tr style="background-color: rgb(242, 242, 242);">
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);"><span style="margin-top: 0px;margin-bottom: 0px;"><span class="MathJax_Preview" style="color: rgb(136, 136, 136);"></span><span class="MathJax" id="MathJax-Element-280-Frame" role="textbox" aria-readonly="true" style="display: inline; font-style: normal; font-weight: normal; line-height: normal; font-size: 100%; text-indent: 0px; text-align: left; text-transform: none; letter-spacing: normal; word-spacing: normal; word-wrap: normal; white-space: nowrap; float: none; direction: ltr; max-width: none; max-height: none; min-width: 0px; min-height: 0px; border: 0px; padding: 0px; margin: 0px;"><nobr style="border: 0px; padding: 0px; margin: 0px; max-width: 5000em; max-height: 5000em; min-width: 0px; min-height: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;white-space: nowrap !important;-webkit-transition: none; transition: none;"><span class="math" id="MathJax-Span-2380" style="width: 2.283em; display: inline-block;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span style="display: inline-block; position: relative; width: 1.858em; height: 0px; font-size: 122%;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span style="position: absolute; clip: rect(1.764em 1000em 3.092em -0.457em); top: -2.678em; left: 0em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span class="mrow" id="MathJax-Span-2381" style="display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"><span class="mi" id="MathJax-Span-2382" style="font-family: MathJax_Math; font-style: italic;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">A</span><span class="mo" id="MathJax-Span-2383" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">[</span><span class="mn" id="MathJax-Span-2384" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">3</span><span class="mo" id="MathJax-Span-2385" style="font-family: MathJax_Main;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;">]</span></span><span style="display: inline-block; width: 0px; height: 2.678em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"></span></span></span><span style="border-left-width: 0em; border-left-style: solid; display: inline-block; overflow: hidden; width: 0px; height: 1.353em; vertical-align: -0.372em;display: inline; position: static; border: 0px; padding: 0px; margin: 0px; vertical-align: 0px; line-height: normal; text-decoration: none;-webkit-transition: none; transition: none;"></span></span></nobr></span><script type="math/tex" id="MathJax-Element-280">A[3]</script></span> hiện đang là phần tử nhỏ nhất cho nên mọi phần tử của stack bị pop ra và 3 trở thành gốc cây. Con trái của 3 là 0</td>
</tr>
<tr>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">4</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 4</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">4 được thêm vào cạnh 3 và con phải của 3 là 4</td>
</tr>
<tr style="background-color: rgb(242, 242, 242);">
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">5</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 4 5</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">5 được thêm vào cạnh 4, con phải của 4 là 5</td>
</tr>
<tr>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">6</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 4 5 6</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">6 được thêm vào cạnh 5, con phải của 5 là 6</td>
</tr>
<tr style="background-color: rgb(242, 242, 242);">
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">7</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 4 5 6 7</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">7 được thêm vào cạnh 6, con phải của 6 là 7</td>
</tr>
<tr>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">8</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 8</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">8 được thêm vào cạnh 3, các phần tử lớn hơn bị loại bỏ. 8 giờ là con phải của 3 và con trái của 8 là 4</td>
</tr>
<tr style="background-color: rgb(242, 242, 242);">
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">9</td>
<td style="text-align:center; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">3 8 9</td>
<td style="text-align:left; border: 1px solid rgb(204, 204, 204); margin: 0px; padding: 6px 13px;border: 1px solid rgb(230, 230, 230);">9 được thêm vào cạnh 8, con phải của 8 là 9</td>
</tr>
</tbody>
</table></div>

Vì mỗi phần tử của $A$ đều chỉ push và pop 1 lần nên độ phức tạp thuật toán là $O(N)$.

~~~cpp
void computeTree(int A[MAXN], int N, int T[MAXN])  {
      int st[MAXN], i, k, top = -1;
   
  //we start with an empty stack
  //at step i we insert A[i] in the stack
      for (i = 0; i < N; i++)
      {
  //compute the position of the first element that is 
  //equal or smaller than A[i]
          k = top;
          while (k >= 0 && A[st[k]] > A[i])
              k--;
  //we modify the tree as explained above
         if (k != -1)
              T[i] = st[k];
         if (k < top)
              T[st[k + 1]] = i;
  //we insert A[i] in the stack and remove 
  //any bigger elements
          st[++k] = i;
          top = k;
      }
  //the first element in the stack is the root of 
  //the tree, so it has no father
      T[st[0]] = -1;
  }
~~~

## Thuật toán $< O(N),O(1) >$ cho bài toán RMQ thu hẹp

Chúng ta sẽ giải bài toán $RMQ$ cho dãy $A[0,N-1]$ với $|A[i]-A[i-1]|=1$ với mọi $i\in[1,N-1]$.

Hãy biến đổi $A$ thành một dãy nhị phân có $N-1$ phần tử, với $B[i]=A[i]-A[i-1]$. Như vậy $A[i]=A[0]+B[1]+..+B[i]$ và $B[i]$ chỉ nhận giá trị $1$ hoặc $-1$.

Chúng ta chia $A$ thành các block kích thước $l=[logN/2]$. Gọi $M[i]$ là giá trị nhỏ nhất trong block thứ $i$ và $D[i]$ là vị trí của giá trị nhỏ nhất này trong $A$. Cả $M$ và $D$ đều có $N/l$ phần tử. Ta tính $M$ bằng Sparse Table như ở trên, tốn $O(N/l*l*log(l))=O(N)$ về bộ nhớ và thời gian. Bây giờ việc cần làm là tính $RMQ$ giữa 2 vị trí bất kì trong một block, chúng ta lưu những giá trị này vào bảng $P[0,N/l][0,l][0,l]$.

Nhận thấy $B$ là một dãy nhị phân, mà mỗi block có $l$ phần tử. Vì số lượng dãy nhị phân độ dài $l$ là $2^l=\sqrt N$ là một số khá nhỏ nên chúng ta nghĩ đến việc tính trước tất cả các RMQ cho tất cả các dãy nhị phân độ dài $l$.

Ví dụ: với độ dài 3 sẽ có 8 tổ hợp:

~~~
000(=0)
001(=1)
010(=2)
011(=3)
100(=4)
101(=5)
110(=6)
111(=7)
~~~

Với $0$ ứng với $-1$, ta sẽ tính trước được cho các dãy

~~~
[-1,-1,-1]
[-1,-1,1]
[-1,1,-1]
[-1,1,1]
[1,-1,-1]
[1,-1,1]
[1,1,-1]
[1,1,1]
~~~

 Như vậy việc tính $P$ có thể được thực hiện trong $O(\sqrt N*l^2)$. Sau đó chỉ cần dựa vào đó mà tính được RMQ của mỗi block trong $B$. Tuy nhiên ta cần tính trước giá trị thập phân của mỗi block trước và lưu vào một mảng $T[N/l]$. Cuối cùng để tính $RMQ_A(i,j)$ ta chỉ cần dựa vào $T$ và $P$.

## Một số bài để luyện tập

[LCA](http://www.spoj.com/problems/LCA/)

[QTREE2](http://www.spoj.pl/problems/QTREE2/)

[HBTLCA](http://vn.spoj.com/problems/HBTLCA/)

[UPGRANET](http://vn.spoj.com/problems/UPGRANET/)

[VOTREE](http://vn.spoj.com/problems/VOTREE/)

[SRM 310 - Floating Median](http://www.topcoder.com/stat?c=problem_statement&pm=6551&rd=9990)

[http://acm.pku.edu.cn/JudgeOnline/problem?id=1986](http://acm.pku.edu.cn/JudgeOnline/problem?id=1986)

[http://acm.pku.edu.cn/JudgeOnline/problem?id=2374](http://acm.pku.edu.cn/JudgeOnline/problem?id=2374)

[http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=2045](http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=2045)

[http://acm.pku.edu.cn/JudgeOnline/problem?id=2763](http://acm.pku.edu.cn/JudgeOnline/problem?id=2763)

[http://acm.uva.es/p/v109/10938.html](http://acm.uva.es/p/v109/10938.html)

[http://acm.sgu.ru/problem.php?contest=0&problem=155](http://acm.sgu.ru/problem.php?contest=0&problem=155)