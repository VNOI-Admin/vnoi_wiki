#Tất tần tật về Cây Phân Đoạn (Segment Tree)

Nguồn: [Codeforces](http://codeforces.com/blog/entry/15890)

[[_TOC_]]

**LƯU Ý**: Tất cả hàm trong bài đều đánh số từ 0. Các nút của cây phân đoạn sẽ quản lý đoạn $[l,r)$

Ở trong bài viết này chúng ta sẽ chủ yếu nói về một số ứng dụng và cùng nhau giải quyết một số bài toán về cây phân đoạn. Để thuận tiện mình xin gọi cây phân đoạn là Segment Tree (ST) trong bài viết này. Sau đây là một số loại Segment Tree:

## Segment Tree cổ điển

Tại sao lại gọi là cổ điển ? Đây là dạng ST đơn giản nhất, chúng ta chỉ giải quyết truy vấn update một phần tử và truy vấn đoạn, mỗi nút lưu một loại dữ liệu cơ bản như biến số hay biến luận lý (boolean). 

#### Ví dụ 1:

Bài toán : [380C-Codeforces](http://codeforces.com/contest/380/problem/C)
Tóm đề: Cho một dãy ngoặc độ dài $N$ $(N\le10^6)$, cho $M$ truy vấn có dạng $l_i, r_i (1\le l_i\le r_i \le N)$. Yêu cầu của bài toán là với mỗi truy vấn tìm một chuỗi con (không cần liên tiếp) của chuỗi từ $l_i$ đến $r_i$ dài nhất mà tạo thành dãy ngoặc đúng.
Lời giải:
Với mỗi nút(ví dụ như nút $x$) chúng ta lưu ba biến nguyên:
- `t[x]`= Là kết quả trong đoạn đang xét.
- `o[x]`= Sô lượng dấu $($ sau khi đã xóa hết các phần tử thuộc dãy ngoặc đúng độ dài `t[x]` trong đoạn.
- `c[x]`= Số lượng dấu $)$ sau khi đã xóa hết các phần tử thuộc dãy ngoặc đúng độ dài `t[x]` trong đoạn.

Định lý 1 : Khi ghép hai nút con lại ta chỉ cần thao tác sau
```cpp
    tmp = min(o[2 * x], c[2 * x + 1])
    t[x] = t[2 * x] + t[2 * x + 1] + tmp
    o[x] = o[2 * x] + o[2 * x + 1] - tmp
    c[x] = c[2 * x] + c[2 * x + 1] - tmp
   ///Và chúng ta cần làm một hàm xây cây như thế này

       void build(int id = 1,int l = 0,int r = n){
        if(r - l < 2){
            if(s[l] == '(')
                o[id] = 1;
            else
                c[id] = 1;
            return ;
        }
        int mid = (l+r)/2;
        build(2 * id,l,mid);
        build(2 * id + 1,mid,r);
        int tmp = min(o[2 * id],c[2 * id + 1]);
        t[id] = t[2 * id] + t[2 * id + 1] + tmp;
        o[id] = o[2 * id] + o[2 * id + 1] - tmp;
        c[id] = c[2 * id] + c[2 * id + 1] - tmp;
    }
```
Với mỗi truy vấn ta trả về ba giá trị là $t, o, c$ như đã nói ở trên, và ta có thể làm điều này dễ dàng trong C++ bằng `pair<int,pair<int,int> >`:

``` cpp
    typedef pair<int,int>pii;
    typedef pair<int,pii>   node;
    node segment(int x,int y,int id = 1,int l = 0,int r = n){
        if(l >= y || x >= r)   return node(0,pii(0,0));
        if(x <= l && r <= y)
            return node(t[id],pii(o[id],c[id]));
        int mid = (l+r)/2;
        node a = segment(x,y,2 * id,l,mid), b = segment(x,y,2 * id + 1,mid,r);
        int T, temp, O, C;
        temp = min(a.y.x , b.y.y);
        T = a.x + b.x + temp;
        O = a.y.x + b.y.x - temp;
            C = a.y.y + b.y.y - temp;
        return node(T,pii(O,C));    
    }
```

Ví dụ 2:

Bài toán: [SPOJ-KQUERY](http://www.spoj.com/problems/KQUERY/)
Tóm đề: Cho một dãy số $a_i(1\le a_i \le 10^9)$ có $N(1\le N \le 30000)$ phần tử và $Q(1\le Q \le 200000)$ truy vấn có dạng 3 số nguyên là $l_i, r_i, k_i$ $(1\le l_i\le r_i\le N, 1\le k \le 10^9)$. Yêu cầu của bài toán là đếm số lượng số $a_j (l_i\le j \le r_i)$ mà $a_j\ge k$.

Giả sử chúng ta có một mảng $b$ với $b_i=1$ nếu $a_i>k$ và bằng $0$ nếu ngược lại. Thì chúng ta có thể dễ dàng trả lời truy vấn $(i, j, k)$ bằng cách lấy tổng từ $i$ đến $j$. 

Điều này hoàn toàn là có thể nếu chúng ta xử lý trước các truy vấn này. Lưu lại các truy vấn, sắp xếp chúng lại theo thứ tự tăng dần theo $k$ đây sẽ là thứ tự chúng ta sẽ trả lời truy vấn. Lúc đầu chúng ta lưu tất cả phần tử mảng $b$ là $1$ và sẽ từ từ tắt các vị trí.

Vậy ta đã sắp xếp lại thứ tự các truy vấn sao cho giá trị $k$ tăng dần ta sẽ xử lý theo thứ tự này và đồng thời lưu lại số thứ tự các truy vấn để lưu vào một mảng $ans$.

Mã giả (theo hệ 0)
```cpp
    po = 0
    for j = 0 to q-1
    	while po < n and a[p[po]] <= k[w[j]]
    		b[p[po]] = 0, po = po + 1
```
   Vậy ta có thể viết hàm xây dựng cây như sau:
   So, build function would be like this (s[x] is the sum of b in the interval of node x) :
```cpp
    void build(int id = 1,int l = 0,int r = n){
    	if(r - l < 2){
    		s[id] = 1;
    		return ;
    	}
    	int mid = (l+r)/2;
    	build(2 * id, l, mid);
    	build(2 * id + 1, mid, r);
    	s[id] = s[2 * id] + s[2 * id + 1];
    }
```

Một hàm cập nhật khi ta muốn gán lại một vị trí bằng 0:
```cpp
    void update(int p,int id = 1,int l = 0,int r = n){
    	if(r - l < 2){
    		s[id] = 0;
    		return ;
    	}
    	int mid = (l+r)/2;
    	if(p < mid)
    		update(p, 2 * id, l, mid);
    	else
    		update(p, 2 * id + 1, mid, r);
    	s[id] = s[2 * id] + s[2 * id + 1];
    }
```

Và cuối cùng là thực hiện truy vấn lấy tổng một đoạn:
```cpp
    int sum(int x,int y,int id = 1,int l = 0,int r = n){// [x, y)
	if(x >= r or l >= y)	return 0;// [x, y) không giao [l,r) 
	if(x <= l && r <= y)	// [l,r) là tập con [x,y)
		return s[id];
	int mid = (l + r)/2;
	return sum(x, y, id * 2, l, mid) +
	       sum(x, y, id*2+1, mid, r) ;
	}
```

Trong thủ tục chính sẽ là như sau:
```cpp
    build();
    int po = 0;
    for(int y = 0;y < q;++ y){
    	int x = w[y];
    	while(po < n && a[p[po]] <= k[x])
    		update(p[po ++]);
    	ans[x] = sum(i[x], j[x] + 1); // đoạn [i[x], j[x] + 1)
    }
```

## Cập nhật lười (Lazy Propagation)

Đây là kĩ thuật được sử dụng trong ST để giảm độ phức tạp của cấu trúc dữ liệu đi với các truy vấn cập nhật đoạn.

Ví dụ 1:
Bài toán: [SPOJ-POSTERS]( http://www.spoj.com/problems/POSTERS/)
Tóm đề: 
Cho $N$ băng rôn $(1\le N \le 40000)$ có chiều cao là 1 được treo trên một chiếc bảng có chiều cao cũng là 1, băng rôn thứ $i$ phủ từ đoạn $l_i$ tới $r_i$ $(1\le l_r \lt r_i \le 10^7)$. Các băng rôn được cho theo thứ tự sắp xếp lên bảng. Yêu cầu của bài toán là phải đếm số lượng băng rôn không bị che hoàn toàn bởi các băng rôn khác sau khi đã gắn tất cả băng rôn lên.

Chúng ta không cần lưu tất cả giá trị $[1,10^7]$. Chúng ta chỉ cần lưu lại một tập các $s_i$ mà trong đó mỗi $s_i$ xuất hiện trong ít nhất một truy vấn $l$ hoặc $r$. Sau đó ta dùng chính những giá trị này để cập nhật cây phân đoạn.

Với mỗi nút nếu tất cả nút trong đó chung màu, ta có thể lưu nó lại theo cập nhật lười. Vậy mỗi nút chúng ta sẽ lưu lại một giá trị $lazy$ và không có hàm xây cây (nếu $lazy[i]\ne 0$ thì tất cả phần tử đoạn mà nó quản lý có cùng một màu là màu $lazy[i]$ vì màu $lazy[i]$ chưa đẩy cập nhật của nó xuống nút con)

Đây là hàm đẩy cập nhật xuống nút con:
```cpp
    void shift(int id){
		if(lazy[id])
			lazy[2 * is] = lazy[2 * id + 1] = lazy[id];
		lazy[id] = 0;
	}
```
Hàm update với từng nút:
```cpp
    void upd(int x,int y,int color, int id = 0,int l = 0,int r = n){
    //Tô đoạn từ [l,r) bằng color
		if(x >= r or l >= y)	return ;
		if(x <= l && r <= y){
			lazy[id] = color;
			return ;
		}
		int mid = (l+r)/2;
		shift(id);
		upd(x, y, color, 2 * id, l, mid);
		upd(x, y, color, 2*id+1, mid, r);
	}
```
Vậy với mỗi lần update ta nên gọi hàm $upd(x,y+1,i)$ với $i$ là màu cần tô. 
Và cuối cùng là hàm lấy truy vấn:
```cpp
    set <int> se;
	void cnt(int id = 1,int l = 0,int r = n){
		if(lazy[id]){
			se.insert(lazy[id]);
			return ; 
			// không cần xét các con do cả đoạn là giống màu
		}
		if(r - l < 2)	return ;
		int mid = (l+r)/2;
		cnt(2 * id, l, mid);
		cnt(2*id+1, mid, r);
	}
```

## Ứng dụng với cấu trúc mảng động

Trong loại bài toán này với mỗi nút của cây ta lưu lại một `vector` và một số biến khác.

Ví du: Cách xử lý online cho bài toán **[KQUERY0](http://w...content-available-to-author-only...j.com/problems/KQUERYO/)** (bài toán yêu cầu xử lý online của bài **KQUERY**)

Nếu trên mỗi nút chúng ta có thể lưu lại danh sách các phần tử đó theo thứ tự tăng dần ta có thể dễ dàng tìm ra kết quả bằng tìm kiếm nhị phân. Vì thế với mỗi nút ta lưu lại một `vector` chứa các phần tử từ $l$ đến $r$ theo thứ tự tăng dần. Điều này có thể được thực hiện với bộ phức tạp bộ nhớ là $\mathcal{O}(N\log{N})$ do mỗi phần tử có thể ở tối đa $\log{N}$ nút. Với nút cha có ta có thể gộp hai nút con vào nút cha bằng phương pháp giống như **Merge Sort** ( lưu lại hai biến chạy và so sánh lần lượt từng phần tử ở hai mảng) để có thể xây dựng cây trong $\mathcal{O}(N\log{N})$.

Hàm xây cây có thể được như sau:
```cpp
    void build(int id = 1,int l = 0,int r = n){
	if(r - l < 2){
		v[id].push_back(a[l]);
		return ;
	}
	int mid = (l+r)/2;
	build(2 * id, l, mid);
	build(2*id+1, mid, r);
	merge(v[2 * id].begin(), v[2 * id].end(), v[2 * id + 1].begin(), v[2 * id + 1].end(), back_inserter(v[id])); // read more about back_inserter in http://w...content-available-to-author-only...s.com/reference/iterator/back_inserter/
	}
```
Và hàm truy vấn có thể như sau:
```cpp
    int cnt(int x,int y,int k,int id = 1,int l = 0,int r  = n){// solve the query (x,y-1,k)
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= n)
		return v[id].size() - (upper_bound(v[id].begin(), v[id].end(), k) - v[id].begin());
	int mid = (l+r)/2;
	return cnt(x, y, k, 2 * id, l, mid) +
		   cnt(x, y, k, 2*id+1, mid, r) ;
	}
```
Một ví dụ khác là : [Component Tree](codeforces.com/gym/100513/problem/C)

## Ứng dụng với cấu trúc set 

Ở cấu trúc này mỗi nút chúng ta lưu một `set`,`multiset`, `hashmap`, hoặc `unodered map` và một só biến khác.

Đây là một bài toán ví dụ:
Cho $n$ vector $a_1, a_2, a_3,...,a_n$ rỗng ban đầu. Chúng ta có thể thực hiện $m$ truy vấn trên những vector này:
1. Truy vấn $A$ $p$ $k$ là thêm số $k$ vào cuối vector $a_p$.
2. Truy vấn $C$ $l$ $r$ $k$ là xuất ra $\sum_{i=l}^rcount(a_i,k)$, với $count(a_i,k)$ là số lần xuất hiện của số $k$ trong vector $a_i$.

Bài toán này chúng ta lưu lại mỗi nút của cây là một `multiset` $s$, với mỗi nút lưu số $k$ đúng $\sum_{i=l}^rcount(a_i,k)$ lần với độ phức tạp bộ nhớ chỉ $\mathcal{O}(q\log(n))$.

Với mỗi truy vấn  $C$ $x$ $y$ $k$ chúng ta sẽ in ra tổng của tất cả dùng cây phân đoạn và truy vấn trên set trong mỗi đoạn thuộc đoạn $x$ đến $y$ như truy trên truy vấn cây phân đoạn bình thường. 

Chúng ta sẽ không có hàm xây cây do các vector ban đầu đang là rỗng, nhưng chúng ta sẽ có thêm hàm cộng phần tử vào như sau:
```cpp
    void add(int p,int k,int id = 1,int l = 0,int r = n){//	thực hiện A p k
	s[id].insert(k);
	if(r - l < 2)	return ;
	int mid = (l+r)/2;
	if(p < mid)
		add(p, k, id * 2, l, mid);
	else
		add(p, k, id*2+1, mid, r);
	}
```
Và một hàm cho truy vấn 2:
```cpp
    int ask(int x,int y,int k,int id = 1,int l = 0,int r = n){// Trả lời C x y-1 k
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)
		return s[id].count(k);
	int mid = (l+r)/2;
	return ask(x, y, k, 2 * id, l, mid) + 
		   ask(x, y, k, 2*id+1, mid, r) ;
	}
```	

##Ứng dụng với các cấu trúc dữ liệu khác 

Cây phân đoạn còn có thể có thể sử dụng một cách linh hoạt với các cấu trúc dữ liệu khác như ở trên. Sử dụng một cây phân đoạn khác trên từng nút có thể giúp chúng ta truy vấn dễ dàng hơn trên mảng hai chiều. Trên đây cũng có thể là các loại cây như **Cây tiền tố(Trie)** hoặc cũng có thể là cấu trúc **Disjoint Set**. Sau đây mình xin giới thiệu một loại cây khác cũng sử dụng nhiều trong cây phân đoạn đó chính là **Cây Fenwick (Binary Indexed Tree)**:

Như trên mỗi nút của cây sẽ là một cây **Fenwick** và có thể một số biến khác. Dưới đây là một bài toán ví dụ:
Cho $n$ vectors $a_1,a_2,a_3,...,a_n$ rỗng ban đầu. Chúng ta cần thực hiện hai loại truy vấn:
1. Truy vấn $A$ $p$ $k$ là thêm số $k$ vào đằng sau vector $a_p$.
2. Truy vấn $C$ $l$ $r$ $k$ là xuất ra $\sum_{i=l}^rcount(a_i,j)$ với $j\le k$ với $count(a_i,j)$ là số lần xuất hiện $k$ trong $a_i$.

Với bài toán này, ta cũng lưu lại ở một nút là một `vector` $v$ chứa số $k$ khi và chỉ khi $\sum_{i=l}^rcount(a_i,j)\ne 0$ (độ phức tạp bộ nhớ sẽ là $\mathcal{O}(q\log{n})$ ) (các số theo theo thứ tự tăng dần)

Đầu tiên, đọc và lưu các truy vấn lại với mỗi truy vấn loại 1 ta sẽ thêm $v$ vào tất cả vector có chứa phần tử $p$. Sau đó ta tiến hành sắp xếp các truy vấn theo phương pháp **Merge Sort** đã nói ở trên và dùng hàm `unique` để loại các phần tử trùng. 

Sau đó chúng ta sẽ xây dụng ở mỗi nút một cây Fenwick có độ lớn bằng độ dài vector. Sau đây là hàm thêm giá trị:
```cpp
    void insert(int p,int k,int id = 1,int l = 0,int r = n){//	Thực hiện A p k
		if(r - l < 2){
			v[id].push_back(k);
			return ;
		}
		int mid = (l+r)/2;
		if(p < mid)
			insert(p, k, id * 2, l, mid);
		else
			insert(p, k, id*2+1, mid, r);
		}
```
Hàm sắp xếp sau khi đã đọc hết các truy vấn:
```cpp
    void SORT(int id = 1,int l = 0,int r = n){
		if(r - l < 2)
			return ;
		int mid = (l+r)/2;
		SORT(2 * id, l, mid);
		SORT(2*id+1, mid, r);
		merge(v[2 * id].begin(), v[2 * id].end(), v[2 * id + 1].begin(), v[2 * id +1].end(), back_inserter(v[id])); 
		//đọc thêm http://www.cplusplus.com/reference/iterator/back_inserter/
		v[id].resize(unique(v[id].begin(), v[id].end()) - v[id].begin());
		fen[id] = vector<int> (v[id].size() + 1, 0);
	}
```
Với mỗi truy vấn loại 1 ta làm như sau với mỗi nút x:
```cpp
    for(int i = a + 1;i < fen[x].size(); i += i & -i) fen[x][i] ++;
```
Với tất cả $v[x][a]=k$:
```cpp
    void upd(int p,int k, int id = 1,int l = 0,int r = n){
		int a = lower_bound(v[id].begin(), v[id].end(), k) - v[id].begin();
		for(int i = a + 1; i < fen[id].size(); i += i & -i )
			fen[id][i] ++ ;
		if(r - l < 2)	return;
		int mid = (l+r)/2;
		if(p < mid)
			upd(p, k, 2 * id, l, mid);
		else
			upd(p, k, 2*id+1, mid, r);
	}
```
Còn lại việc tính toán truy vấn loại 2 trở nên dễ dàng hơn:
```cpp
    int ask(int x,int y,int k,int id = 1,int l = 0,int r = n){// Trả lời C x y-1 k
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y){
		int a = lower_bound(v[id].begin(), v[id].end(), k) - v[id].begin();
		int ans = 0;
		for(int i = a + 1; i > 0; i -= i & -i)
			ans += fen[id][i];
		return ans;
	}
	int mid = (l+r)/2;
	return ask(x, y, k, 2 * id, l, mid) + 
		   ask(x, y, k, 2*id+1, mid, r) ;
	}
```

##Ứng dụng trong cây có gốc

Ta có thể thấy cây phân đoạn là một ứng dụng trong mảng, vì lí do đó nếu chúng ta có thể đổi cây thành cấu trúc mảng ta có thể dễ dàng xử lý các truy vấn trên cây. Với **DFS** và đánh dấu lại các nút theo thứ tự đến các nút trong một nút con bất kì sẽ thành một đoạn liên tiếp.

Bài tập ví dụ: [396C - On Changing Tree](http://codeforces.com/contest/396/problem/C)

Gọi $h_v$ là độ cao tương ứng của nút $v$. Ta có với mỗi nút $u$ trong cây con gốc $v$ sau truy vấn một giá trị của nó sẽ tăng một lượng là $ x+(h_u-h_v)\*-k=x+k\* h_v-k\* h $. Kết quả của truy vấn 2 sẽ là $\sum_{i\in s}(k_i\*h_{v_i}+x_i)-h_u\*\sum_{i\in s}k_i$. Vì vậy ta chỉ cần tính hai giá trị là $\sum_{i\in s}(k_i\* h_{v_i}+x_i)$ và $\sum_{i\in s}k_i$. Vậy với mỗi nút ta có thể lưu lại hai giá trị là $hkx=\sum x +h*k$ và $sk=\sum k$ ( không cần cập nhật lười do chúng ta chỉ update nút đầu tiên thỏa việc nằm trong đoạn.

Với truy vấn cập nhật:
```cpp
    void update(int x,int k,int v,int id = 1,int l = 0,int r = n){
		if(s[v] >= r or l >= f[v])	return ;
		if(s[v] <= l && r <= f[v]){
			hkx[id] = (hkx[id] + x) % mod;
			int a = (1LL * h[v] * k) % mod;
			hkx[id] = (hkx[id] + a) % mod;
			sk[id] = (sk[id] + k) % mod;
			return ;
		}
		int mid = (l+r)/2;
		update(x, k, v, 2 * id, l, mid);
		update(x, k, v, 2*id+1, mid, r);
	}
```
và truy vấn :
```cpp
    int ask(int v,int id = 1,int l = 0,int r = n){
		int a = (1LL * h[v] * sk[id]) % mod;
		int ans = (hkx[id] + mod - a) % mod;
		if(r - l < 2)	return ans;
		int mid = (l+r)/2;
		if(s[v] < mid)
			return (ans + ask(v, 2 * id, l, mid)) % mod;
			return (ans + ask(v, 2*id+1, mid, r)) % mod;
	}
```

##Cây phân đoạn ổn định (Persistent Segment Trees)

Hãy đọc bài này trước [Persistent Data Structures](http://vnoi.info/contributor/algo/data-structures/persistent-data-structures)
Chúng ta đã nói sơ qua về loại cây này trong bài trước bây giờ hãy tìm hiểu nó kĩ hơn qua một bài toán:
Đó chính là [MKTHNUM](http://www.spoj.com/problems/MKTHNUM/). Bài này có thể sử dụng chặt nhị phân cùng cây phân đoạn với vector để giải ra với độ phức tạp là $\mathcal{O}((m+n)\log^2n)$ nhưng hướng tiếp cận đó sẽ dễ bị quá thời gian với bài toán này. Hãy đến một cách tiếp cận nhanh hơn với độ phức tạp $\mathcal{O}((m+n)\log n)$. Đây là cách tiếp cận hiệu quả và khá hữu ích.

Sắp xếp các phần tử của $a$ lại để tính được hoán vị $p_1,p_2,...,p_n$ sao cho $a_{p_1}<a_{p_2}<....<a_{p_n}$ và với mỗi $i$ thì tìm $q_i$ sao cho $p_{q_i}=i$.

Chúng ta thực hiện $n$ bước biến đổi, với mỗi bước $b_{q_i}=1$(mảng $b$ lúc đầu 0 hết). Gọi $sum(l,r,k)$ là tổng mảng $b$ từ $l$ đến $r $ (bằng 0 nếu $ k=0$).

Đây là hàm xây dựng cây:
```cpp
    void build(int id = ir,int l = 0,int r = n){
		s[id] = 0;
		if(r - l < 2)
			return ;
		int mid = (l+r)/2;
		L[id] = NEXT_FREE_INDEX ++;
		R[id] = NEXT_FREE_INDEX ++;
		build(L[id], l, mid);
		build(R[id], mid, r);
		s[id] = s[L[id]] + s[R[id]];
	}
```
Hàm update:
```cpp
    int upd(int p, int v,int id,int l = 0,int r = n){
		// chỉ số phiên bản mới của nút
		s[ID] = s[id] + 1;
		if(r - l < 2)
			return ID;
		int mid = (l+r)/2;
		L[ID] = L[id], R[ID] = R[id]; 
		// trường hợp không cập nhật cả nút trái và phải
		if(p < mid)
			L[ID] = upd(p, v, L[ID], l, mid);
		else
			R[ID] = upd(p, v, R[ID], mid, r);
		return ID;
	}
```	
Hàm trả lời truy vấn( trả lời $i$, đáp án sẽ là $a_{p_i}$):
```cpp
    int ask(int id, int ID, int k, int l = 0,int r = n){
    //  id là chỉ số của nút sau lần cập nhật thứ l-1 và ID sẽ là chỉ số nút sau lần cập nhật r
		if(r - l < 2)	return l;
		int mid = (l+r)/2;
		if(s[L[ID]] - s[L[id]] >= k)// câu trả lời ở nút con bên trái
			return ask(L[id], L[ID], k, l, mid);
		else
			return ask(R[id], R[ID], k - (s[L[ID]] - s[L[id]] ), mid, r);
			// đã có s[L[ID]] - s[L[id]] ở nút trái
	}
```

