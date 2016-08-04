# Range Minimum Query và Lowest Common Ancestor

[Bài viết chưa hoàn thiện]

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

### Thuật toán $< O(Nlog_N),O(log_N) >$

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

