# Cấu Trúc Dữ Liệu
***Bài viết chưa hoàn thiện***
dd
**Nguồn:** [Codeforces](http://codeforces.com/blog/entry/15729)

**Tác giả:** [amd](http://codeforces.com/profile/amd)

[[_TOC_]]

## Giới thiệu
Hôm nay, mình muốn giới thiệu tới các bạn một số Cấu trúc dữ liệu hữu ích.
Qua bài viết này, ta sẽ cố gắng nâng cao kỹ năng sử dụng chúng.
Một số CTDL quan trọng:

## Cây
Cây là một trong những CTDL thông dụng và hữu ích nhất. Cây là một đồ thị liên thông không có chu trình. Có nhiều dạng cây như **Cây Có Gốc ( Rooted Trees )**, **Cây Có Hướng ( Directed Trees )**,… 

## Partial Sum
Có 2 dạng bài có thể giải được bằng cách áp dụng Partial Sum.

**Những bài đưa ra các truy vấn yêu cầu cho biết tổng một số phần tử.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho một mảng **a1,a2,a3,…,aN**. Mỗi truy vấn cho biết 2 số L và R, yêu cầu in ra tổng **aL + a(L+1) + … + aR**. 
**Cách giải:** Tạo một mảng S, với mỗi phần tử **S(i) = a1 + a2 + ..+ a(i) **. Xuất ra:  sR – S(l-1) .


**Những bài yêu cầu thay đổi giá trị các phần tử trong một đoạn.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho mảng **a1,a2,….aN**. Mỗi truy vấn cho 3 số L,R,V. với mỗi **i ( L<=i<=R )**, cộng **V** vào **a(i)**. Sau khi hoàn thành, in toàn bộ mảng ra.
**Cách giải:**  Tạo một mảng P: **p1,p2,…pN** với mỗi phần tử được khởi tạo với giá trị **0**. Mỗi truy vấn, tăng **p(L)** lên **V** và trừ **p(R+1)** đi V. Sau đó, với mỗi i ( chạy từ 1 ), **p(i) += p (i–1).**

## Disjoints Sets
Disjoint Sets là 1 CTDL rất hữu dụng, sử dụng rất nhanh, gọn và dễ dàng. Nó được dùng làm nền tảng cho một số thuật toán, như Kruskal’s và Prim’s, 2 thuật toán tìm cây khung nhỏ nhất trên đồ thị.

Disjoint Sets, hoặc DSU ( Disjoint Sets Union ) như tên gọi của, là một tập hợp các tổng. Hãy tưởng tượng chúng ta có một vài cái hộp cũng như một vài bộ dụng cụ và ban đầu mỗi bộ dụng cụ nằm trong một cái hộp. Thông thường, ta sẽ nhận được các truy vấn để hợp 2 hộp lại với nhau hoặc in ra các bộ dụng cụ có trong hộp hoặc tìm hộp có các bộ dụng cụ nhất định.

Giả sử, chỉ có duy nhất 1 bộ dụng cụ trong 1 hộp. Ta có n bộ dụng cụ, n hộp, và ban đầu, bộ thứ i sẽ nằm trong hộp thứ i.

Với những yêu cầu trên, ta có thể sử dụng nhiều cấu trúc, như:

### Cây
Cây là cấu trúc hữu hiệu nhất dùng cho DSU. Với mỗi đỉnh, ta lưu lại đỉnh cha của nó ( đỉnh cha của đỉnh gốc là -1 ). Ban đầu, mọi đỉnh cha được set là -1. Có các truy vấn **tìm đỉnh gốc** của mỗi hộp ( có được gốc, ta có thể truy ra vị trí của hộp ) và các truy vấn yêu cầu **hợp** 2 cây lại. Để thuật toán nhanh hơn, mỗi lần tìm gốc của mỗi đỉnh, ta đặt đỉnh cha của nó là gốc cho truy vấn tiếp theo. Luôn muốn độ cao của cây là nhỏ nhất có thể, vì vậy, mỗi khi nhập các hộp lại với nhau, ta bỏ các bộ dụng cụ trong hộp có ít bộ hơn vào hộp còn lại.

[[/uploads/tree1.png|tree1]]

_Code C++ ( [bmerry](http://codeforces.com/profile/bmerry) )_

```cpp
int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}
void merge(int x,int y){	//	x and y are some tools (vertices)
        if((x = root(x)) == (y = root(y))     return ;
	if(par[y] < par[x])	// balancing the height of the tree
		swap(x, y);
	par[x] += par[y];
	par[y] = x;
}
```

### Mảng, Vector
Ta lưu vị trí các bộ dụng cụ trong một **vector** ( hoặc **mảng** ) và mỗi khi có truy vấn yêu cầu **nhập** hai hộp, ta bỏ các bộ dụng cụ ở hộp có ít bộ hơn vào hộp còn lại.

Độ phức tạp không cao vì với mỗi bộ dụng cụ, lấy và bỏ nó vào hộp chỉ có độ phức tạp cao nhất là **log(n)**.
Độ phức tạp sẽ là **O(n.log(n))**.

### Sets ( Cây Đỏ Đen; Red-Black Trees )
Một cách khác là lưu chúng trong một cây đỏ đen ( trong C++ là **set** thư viện **STL** ). Ta làm y như đã làm với vectors, độ phức tạp sẽ là **O(n.log^2.n)**. ( 1 log cho việc nhập vào ).

_Bài tập: (Phải tham gia nhóm [ACM-OI](http://codeforces.com/group/L1Sf9F4uBt) )_

- [Hamro & Tools](http://codeforces.com/group/L1Sf9F4uBt/contest/200499/problem/E )
- [TROY Query](http://codeforces.com/gym/100571/problem/F)

## Cây Tiền Tố ( Tries )
Trong khoa học máy tính, trie, hay cây tiền tố, là một cấu trúc dữ liệu sử dụng cây có thứ tự, dùng để lưu trữ một mảng liên kết của các xâu kí tự.

Cây Tiền Tố là một dạng  **DFA** (**Determining Finite Automata**) (**Automat Hữu Hạn **). Với các chuỗi xâu, Cây Tiền Tố là **cây có gốc nhỏ nhất** với một ký tự trên mỗi cạnh và mỗi chuỗi có thể được biểu diễn bằng cách viết các ký tự theo đường từ gốc đến các node.

**Mảng tiền tố chung lớn nhất** (**LCP Longest Common Prefix ** ) của mỗi 2 trong các chuỗi là **Tổ Tiên Chung Thấp Nhất** (** LCA Lowest Common Ancestor **) của các node trong Cây Tiền Tố.

_ Khởi tạo Cây Tiền Tố: (0-based code) _
```cpp
int x[MAX_NUMBER_OF_NODES][MAX_ASCII_CODE], next = 1; //initially all numbers in x are -1
void build(string s){
	int i = 0, v = 0;
	while(i < s.size()){
		if(x[v][s[i]] == -1)
			v = x[v][s[i++]] = next ++;
		else
			v = x[v][s[i++]];
	}
}
```

_Bài tập: [A lot of games](http://codeforces.com/contest/456/problem/D ) _

---

## Mảng Hậu Tố (Suffix Array)
**Mảng Hậu Tố** là một CTDL giúp **sort** các **hậu tố** theo **thứ tự từ điển**.

Mảng này chứa các số nguyên, khởi đầu của các hậu tố.

Có 2 cách để xây dựng một mảng hậu tố:

1. **Thuật toán không xác định:** Sử dụng thuật toán **Rabin-Karp** và kiểm tra nếu một hậu tố có thứ tự từ điển nhỏ hơn một hậu tố khác,tìm **mảng tiền tố chung lớn nhất** ( **LCP** ), sau đó sử dụng **Tìm Kiếm Nhị Phân** và **hàm băm** ( **Hash** ) và kiểm tra ký tự tiếp theo sau **LCP** của chúng.

_Code C++:_


```cpp

  namespace HashSuffixArray
{

	const int

		MAXN = 1 << 21;

	typedef unsigned long long hash;

	const hash BASE = 137;

	int N;
	char * S;
	int sa[MAXN];
	hash h[MAXN], hPow[MAXN];

	#define getHash(lo, size) (h[lo] - h[(lo) + (size)] * hPow[size])

	inline bool sufCmp(int i, int j)
	{
		int lo = 1, hi = min(N - i, N - j);
		while (lo <= hi)
		{
			int mid = (lo + hi) >> 1;
			if (getHash(i, mid) == getHash(j, mid))
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		return S[i + hi] < S[j + hi];
	}

	void buildSA()
	{
		N = strlen(S);
		hPow[0] = 1;
		for (int i = 1; i <= N; ++i)
			hPow[i] = hPow[i - 1] * BASE;
		h[N] = 0;
		for (int i = N - 1; i >= 0; --i)
			h[i] = h[i + 1] * BASE + S[i], sa[i] = i;

		stable_sort(sa, sa + N, sufCmp);
	}

} // end namespace HashSuffixArray

```

2. **Thuật toán xác định:** Sort log(Độ dài lớn nhất) bước, với bước thứ i ( tính từ 0 ), sort chúng theo 2^i ký tự đầu tiên và đưa hậu tố có cùng tiền tố với 2^i ký tự vào cùng một bucket.

_Code:_

```cpp

/*
Suffix array O(n lg^2 n)
LCP table O(n)
*/
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

namespace SuffixArray
{
	const int MAXN = 1 << 21;
	char * S;
	int N, gap;
	int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

	bool sufCmp(int i, int j)
	{
		if (pos[i] != pos[j])
			return pos[i] < pos[j];
		i += gap;
		j += gap;
		return (i < N && j < N) ? pos[i] < pos[j] : i > j;
	}

	void buildSA()
	{
		N = strlen(S);
		REP(i, N) sa[i] = i, pos[i] = S[i];
		for (gap = 1;; gap *= 2)
		{
			sort(sa, sa + N, sufCmp);
			REP(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
			REP(i, N) pos[sa[i]] = tmp[i];
			if (tmp[N - 1] == N - 1) break;
		}
	}

	void buildLCP()
	{
		for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1)
		{
			for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
			++k;
			lcp[pos[i]] = k;
			if (k)--k;
		}
	}
} // end namespace SuffixArray

```

Source: [mukel](# Cấu Trúc Dữ Liệu
***Bài viết chưa hoàn thiện***

**Nguồn:** [Codeforces](http://codeforces.com/blog/entry/15729)

**Tác giả:** [amd](http://codeforces.com/profile/amd)

[[_TOC_]]

## Giới thiệu
Hôm nay, mình muốn giới thiệu tới các bạn một số Cấu trúc dữ liệu hữu ích.
Qua bài viết này, ta sẽ cố gắng nâng cao kỹ năng sử dụng chúng.
Một số CTDL quan trọng:

## Cây
Cây là một trong những CTDL thông dụng và hữu ích nhất. Cây là một đồ thị liên thông không có chu trình. Có nhiều dạng cây như **Cây Có Gốc ( Rooted Trees )**, **Cây Có Hướng ( Directed Trees )**,… 

## Partial Sum
Có 2 dạng bài có thể giải được bằng cách áp dụng Partial Sum.

**Những bài đưa ra các truy vấn yêu cầu cho biết tổng một số phần tử.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho một mảng **a1,a2,a3,…,aN**. Mỗi truy vấn cho biết 2 số L và R, yêu cầu in ra tổng **aL + a(L+1) + … + aR**. 
**Cách giải:** Tạo một mảng S, với mỗi phần tử **S(i) = a1 + a2 + ..+ a(i) **. Xuất ra:  sR – S(l-1) .


**Những bài yêu cầu thay đổi giá trị các phần tử trong một đoạn.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho mảng **a1,a2,….aN**. Mỗi truy vấn cho 3 số L,R,V. với mỗi **i ( L<=i<=R )**, cộng **V** vào **a(i)**. Sau khi hoàn thành, in toàn bộ mảng ra.
**Cách giải:**  Tạo một mảng P: **p1,p2,…pN** với mỗi phần tử được khởi tạo với giá trị **0**. Mỗi truy vấn, tăng **p(L)** lên **V** và trừ **p(R+1)** đi V. Sau đó, với mỗi i ( chạy từ 1 ), **p(i) += p (i–1).**

## Disjoints Sets
Disjoint Sets là 1 CTDL rất hữu dụng, sử dụng rất nhanh, gọn và dễ dàng. Nó được dùng làm nền tảng cho một số thuật toán, như Kruskal’s và Prim’s, 2 thuật toán tìm cây khung nhỏ nhất trên đồ thị.

Disjoint Sets, hoặc DSU ( Disjoint Sets Union ) như tên gọi của, là một tập hợp các tổng. Hãy tưởng tượng chúng ta có một vài cái hộp cũng như một vài bộ dụng cụ và ban đầu mỗi bộ dụng cụ nằm trong một cái hộp. Thông thường, ta sẽ nhận được các truy vấn để hợp 2 hộp lại với nhau hoặc in ra các bộ dụng cụ có trong hộp hoặc tìm hộp có các bộ dụng cụ nhất định.

Giả sử, chỉ có duy nhất 1 bộ dụng cụ trong 1 hộp. Ta có n bộ dụng cụ, n hộp, và ban đầu, bộ thứ i sẽ nằm trong hộp thứ i.

Với những yêu cầu trên, ta có thể sử dụng nhiều cấu trúc, như:

### Cây
Cây là cấu trúc hữu hiệu nhất dùng cho DSU. Với mỗi đỉnh, ta lưu lại đỉnh cha của nó ( đỉnh cha của đỉnh gốc là -1 ). Ban đầu, mọi đỉnh cha được set là -1. Có các truy vấn **tìm đỉnh gốc** của mỗi hộp ( có được gốc, ta có thể truy ra vị trí của hộp ) và các truy vấn yêu cầu **hợp** 2 cây lại. Để thuật toán nhanh hơn, mỗi lần tìm gốc của mỗi đỉnh, ta đặt đỉnh cha của nó là gốc cho truy vấn tiếp theo. Luôn muốn độ cao của cây là nhỏ nhất có thể, vì vậy, mỗi khi nhập các hộp lại với nhau, ta bỏ các bộ dụng cụ trong hộp có ít bộ hơn vào hộp còn lại.

_Code C++ ( [bmerry](http://codeforces.com/profile/bmerry) )_

```cpp
int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}
void merge(int x,int y){	//	x and y are some tools (vertices)
        if((x = root(x)) == (y = root(y))     return ;
	if(par[y] < par[x])	// balancing the height of the tree
		swap(x, y);
	par[x] += par[y];
	par[y] = x;
}
```

### Mảng, Vector
Ta lưu vị trí các bộ dụng cụ trong một **vector** ( hoặc **mảng** ) và mỗi khi có truy vấn yêu cầu **nhập** hai hộp, ta bỏ các bộ dụng cụ ở hộp có ít bộ hơn vào hộp còn lại.

Độ phức tạp không cao vì với mỗi bộ dụng cụ, lấy và bỏ nó vào hộp chỉ có độ phức tạp cao nhất là **log(n)**.
Độ phức tạp sẽ là **O(n.log(n))**.

### Sets ( Cây Đỏ Đen; Red-Black Trees )
Một cách khác là lưu chúng trong một cây đỏ đen ( trong C++ là **set** thư viện **STL** ). Ta làm y như đã làm với vectors, độ phức tạp sẽ là **O(n.log^2.n)**. ( 1 log cho việc nhập vào ).

_Bài tập: (Phải tham gia nhóm [ACM-OI](http://codeforces.com/group/L1Sf9F4uBt) )_

- [Hamro & Tools](http://codeforces.com/group/L1Sf9F4uBt/contest/200499/problem/E )
- [TROY Query](http://codeforces.com/gym/100571/problem/F)

---

## Cây Tiền Tố ( Tries )
Trong khoa học máy tính, trie, hay cây tiền tố, là một cấu trúc dữ liệu sử dụng cây có thứ tự, dùng để lưu trữ một mảng liên kết của các xâu kí tự.

Cây Tiền Tố là một dạng  **DFA** (**Determining Finite Automata**) (**Automat Hữu Hạn **). Với các chuỗi xâu, Cây Tiền Tố là **cây có gốc nhỏ nhất** với một ký tự trên mỗi cạnh và mỗi chuỗi có thể được biểu diễn bằng cách viết các ký tự theo đường từ gốc đến các node.

**Mảng tiền tố chung lớn nhất** (**LCP Longest Common Prefix ** ) của mỗi 2 trong các chuỗi là **Tổ Tiên Chung Thấp Nhất** (** LCA Lowest Common Ancestor **) của các node trong Cây Tiền Tố.

_ Khởi tạo Cây Tiền Tố: (0-based code) _
```cpp
int x[MAX_NUMBER_OF_NODES][MAX_ASCII_CODE], next = 1; //initially all numbers in x are -1
void build(string s){
	int i = 0, v = 0;
	while(i < s.size()){
		if(x[v][s[i]] == -1)
			v = x[v][s[i++]] = next ++;
		else
			v = x[v][s[i++]];
	}
}
```

_Bài tập: [A lot of games](http://codeforces.com/contest/456/problem/D ) _

---

## Mảng Hậu Tố (Suffix Array)
**Mảng Hậu Tố** là một CTDL giúp **sort** các **hậu tố** theo **thứ tự từ điển**.

Mảng này chứa các số nguyên, khởi đầu của các hậu tố.

Có 2 cách để xây dựng một mảng hậu tố:

1. **Thuật toán không xác định:** Sử dụng thuật toán **Rabin-Karp** và kiểm tra nếu một hậu tố có thứ tự từ điển nhỏ hơn một hậu tố khác,tìm **mảng tiền tố chung lớn nhất** ( **LCP** ), sau đó sử dụng **Tìm Kiếm Nhị Phân** và **hàm băm** ( **Hash** ) và kiểm tra ký tự tiếp theo sau **LCP** của chúng.

_Code C++:_


```cpp

  namespace HashSuffixArray
{

	const int

		MAXN = 1 << 21;

	typedef unsigned long long hash;

	const hash BASE = 137;

	int N;
	char * S;
	int sa[MAXN];
	hash h[MAXN], hPow[MAXN];

	#define getHash(lo, size) (h[lo] - h[(lo) + (size)] * hPow[size])

	inline bool sufCmp(int i, int j)
	{
		int lo = 1, hi = min(N - i, N - j);
		while (lo <= hi)
		{
			int mid = (lo + hi) >> 1;
			if (getHash(i, mid) == getHash(j, mid))
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		return S[i + hi] < S[j + hi];
	}

	void buildSA()
	{
		N = strlen(S);
		hPow[0] = 1;
		for (int i = 1; i <= N; ++i)
			hPow[i] = hPow[i - 1] * BASE;
		h[N] = 0;
		for (int i = N - 1; i >= 0; --i)
			h[i] = h[i + 1] * BASE + S[i], sa[i] = i;

		stable_sort(sa, sa + N, sufCmp);
	}

} // end namespace HashSuffixArray

```

2. **Thuật toán xác định:** Sort log(Độ dài lớn nhất) bước, với bước thứ i ( tính từ 0 ), sort chúng theo 2^i ký tự đầu tiên và đưa hậu tố có cùng tiền tố với 2^i ký tự vào cùng một bucket.

_Code:_

```cpp

/*
Suffix array O(n lg^2 n)
LCP table O(n)
*/
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

namespace SuffixArray
{
	const int MAXN = 1 << 21;
	char * S;
	int N, gap;
	int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

	bool sufCmp(int i, int j)
	{
		if (pos[i] != pos[j])
			return pos[i] < pos[j];
		i += gap;
		j += gap;
		return (i < N && j < N) ? pos[i] < pos[j] : i > j;
	}

	void buildSA()
	{
		N = strlen(S);
		REP(i, N) sa[i] = i, pos[i] = S[i];
		for (gap = 1;; gap *= 2)
		{
			sort(sa, sa + N, sufCmp);
			REP(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
			REP(i, N) pos[sa[i]] = tmp[i];
			if (tmp[N - 1] == N - 1) break;
		}
	}

	void buildLCP()
	{
		for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1)
		{
			for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
			++k;
			lcp[pos[i]] = k;
			if (k)--k;
		}
	}
} // end namespace SuffixArray

```

Source: [mukel](http://codeforces.com/profile/mukel)

---

##Heap

**Heap** là một **cây nhị phân** ( **cây có gốc** mà mỗi đỉnh có **không quá hai con** ) và mỗi đỉnh mang một giá trị.

**Tính chất của Heap:** Giá trị trên một đỉnh luôn **lớn hơn hoặc bằng** giá trị **đỉnh con** của nó. Ta có thể dùng heap trong **Heap Sort* ( **Sắp xếp vun đống** ).

[[/uploads/heap1.png|heap1]]

---

##Fibonacci Heap
Fibonacci Heap là một dạng heap có **độ phức tạp** bé hơn. Chúng ta không cần quan tâm Fibonacci Heap là gì vì trong thư viện **STL C++** đã có sẵn, được gọi là **priority_queue**.

---

## Cây Tìm Kiếm Nhị Phân 
**Cây Tìm Kiếm Nhị Phân** ( **BST Binary Search Tree** ) là một cây nhị phân có tính chất: Với mỗi giá trị trên node đang xét, giá trị của mọi node trên cây con trái luôn nhỏ hơn node đang xét và giá trị của mọi node trên cây con phải luôn lớn hơn node đang xét.

[[/uploads/bst1.png|bst1]]

---

##Cây Đỏ Đen ( Red-Black Tree )
Cây đỏ đen là một dạng **cây tìm kiếm nhị phân** (**BST**) mà sau mỗi truy vấn được thực hiện, cây tự cân bằng theo đúng tính chất của nó với độ phức tạp **O(log(N))**.
Thư viện **STL C++** có sẵn CTDL này, dưới dạng **set**.

[[/uploads/redblack1.png\red****
---

##SQRT Decomposition

Giả sử, ta có một mảng **a1,a2,…,aN**  và k = $\sqrt{N}$    sqrt (N) . Ta chia mảng này thành k phần, mỗi phần chứa k phần tử a. Với việc này, ta có thể làm nhiều việc với độ phức tạp **O(sqrt(N))**. Thông thường sử dụng **sqrt decomposition** đối với truy vấn yêu cầu chỉnh sửa phần tử mảng hoặc hỏi.

_Bài tập:_

1. [HOLES](http://codeforces.com/problemset/problem/13/E)

2. [DZY LOVES COLORS](http://codeforces.com/contest/444/problem/C)

3. Các bài toán dạng **RMQ** ( **range minimum query** )

---

##Sparse Table

Có mảng **a1,a2,…,aN** và các truy vấn. Mỗi truy vấn cho chúng ta 2 số **L** và **R** ( **L<=R** ) và bạn phải in ra giá trị **nhỏ nhất** của (**aL,aL+1….,aR** ). 

**Cách giải** sử dụng **Sparse Table**: Với mỗi giá trị i ( **1<=i<=N** ) và với mỗi j với điều kiện j>=0 và ( **i + $2^j$ – 1** ) <= n, ta lưu giá trị **min( Ai, Ai+1, …. , A(i+ 2^i) **) trong phần tử **st[i][j]** ( khởi tạo các phần tử mảng st = 0 ).

_Code:_

```cpp
for(int j = 0;j < MAX_LOG;j++)
	for(int i = 0; i < n;i ++)if(i + (1 << j) - 1 < n)
		st[i][j] = (j ? min(st[i][j-1], st[i + (1 << (j-1)) - 1][j-1]): a[i]);
```

Và với mỗi truy vấn, đầu tiên, tìm giá x lớn nhất sao cho 2^x < (r-l+1) và xuất ra min ( st[l][x], st[r-2^x+1][x] ).

Vậy, ý tưởng chính của Sparse Table là lưu lại giá trị cho mỗi đoạn độ dài 2^k ( với mỗi k ).

Có thể dùng ý tưởng tương tự cho việc cài đặt LCA và các thuật toán khác.

Độ phức tạp của sẽ là O ( n*log(n) ) và các truy vấn sẽ được xử lý với độ phức tạp O(1).

_Bài tập:_ 

1. [Strip](http://codeforces.com/contest/487/problem/B)

2. [GCDSSQ](http://codeforces.com/contest/475/problem/D)

3. [LCM Query](http://codeforces.com/gym/100570/problem/A)

---

##Fenwick
**Fenwick** hay ở Việt Nam được gọi là **Cây Chỉ Số Nhị Phân** ( ** BIT Binary Indexed Tree** ) là một CTDL với n node và mỗi node thứ i chứa thông tin về các phần tử trong đoạn [ i – i& - i, i]. 

**Ví dụ: ** Có một mảng **a1,a2,…..,aN** và được mặc định bằng 0. Chúng ta nhận được các truy vấn, 1 là tăng phần tử **aP** lên **VAL**, 2 là in ra **a1+a2+…+aP**.

Giờ chúng ta chỉ cần quan tâm cách giải bài toán này với Fenwick ( nhưng sau đó bạn có thể tìm tòi và áp dụng nó cho nhiều bài tập khác ).

**Độ phức tạp** khi xử lý các truy vấn là **O(log(n))**. 

_Code ( 1-based ):_

```cpp
int fen[MAX_N];
void update(int p,int val){
	for(int i = p;i <= n;i += i & -i)
		fen[i] += val;
}
int sum(int p){
	int ans = 0;
	for(int i = p;i;i -= i & -i)
		ans += fen[i];
	return ans;
}
```

Mảng bắt buộc phải là 1-based, không thể chạy với 0-based.

_Bài tập: _

1. [Inversions](http://acm.sgu.ru/problem.php?contest=0&problem=180)

2. [Pashmak and Parmida’s problem](http://codeforces.com/contest/459/problem/D)

3. [BST](http://hsin.hr/coci/archive/2008_2009/contest3_tasks.pdf)

---

##Cây Đoạn ( Segment Tree )
Có một mảng gồm các phần tử và các truy vấn trong đoạn. Nếu có thể chia đoạn thành các đoạn nhỏ với độ phức tạp **O(log(n))** thì sẽ rất tốt.

**Segment Tree** (**Cây Đoạn**) sinh ra để làm việc đó.  **Segment Tree** là một cây mà mỗi node của nó thuộc một đoạn.

Gốc của cây thuộc đoạn **[0,n)** (**0-based**).

Mỗi node có 0 hoặc 2 node con, trái và phải. Nếu đoạn của một node là **[L,r)** cùng điều kiện **L+1 # R** thì đoạn node con của node đó sẽ là **[L,mid)** và **[mid,R)** với mid=$/frac{L+R}{2} , độ cao của cây là **O(log(n))**.

Mỗi node có một chỉ số, quy định rằng, gốc có chỉ số là 1, và các node con của đỉnh chỉ số X sẽ có chỉ số là **2X** và **2X+1**.

**Segment Tree** là một CTDL phổ biến và hữu hiệu. Tất cả các bài tập có thể giải bằng **Fenwick** ( **Cây chỉ số nhị phân BIT** ) thì có thể giải được bằng **Segment Tree**.
Nếu kích thước đoạn của gốc là **N**, Segment Tree có thể có tới **4N** Node.

Để chia một đoạn thành nhiều node, làm như sau:
Giả sử rằng S là một **set** các node mà **hợp** đoạn của nó là **[x,y)** và không có 2 node khác nhau trong S có giao.

Một node i với đoạn **[L,r)** trong S khi và chỉ khi **X<=L<=R<=Y** và nếu node cha có đoạn **[B,e)**, **X>L**  và **R>Y**.

_Code C++: _

```cpp

vector<int> s;
void split(int x,int y, int id = 1,int l = 0, int r = n){//	id is the index of the node
	if(x >= r or l >= y)	return ;	// in this case, intersect of [l,r) and [x,y) is empty
	if(x <= l && r <= y){
		s.push_back(id); 
		return ;
	}
	int mid = (l+r)/2;
	split(x,y,id * 2,l,mid);
	split(x,y,id * 2 + 1,mid,r);
}

```

**Ví dụ: **

Ta có một mảng **a1,a2,…,aN** và q truy vấn. Có 2 loại truy vấn:

1.	**S L R : In ra **aL + a(L+1) + …. + aR**.

2.	**M p x** : Thay đổi giá trị của **aP** = **X**.

Đầu tiên cần xây dựng **Segment Tree**, với mỗi node ta lưu lại tổng đoạn của nó, với node i ta gọi đó là s[i], nên ta sẽ xây Segment Tree ban đầu như sau.

Trước khi xử lý các truy vấn, ta sẽ gọi hàm build():

```cpp
void build(int id = 1,int l = 0,int r = n){
	if(r - l < 2){	//	l + 1 == r
		s[id] = a[l];
		return ;
	}
	int mid = (l+r)/2;
	build(id * 2, l, mid);
	build(id * 2 + 1, mid, r);
	s[id] = s[id * 2] + s[id * 2 + 1];
}

```

Hàm modify:

```cpp
void modify(int p,int x,int id = 1,int l = 0,int r = n){
	s[id] += x - a[p];
	if(r - l < 2){	//	l = r - 1 = p
		a[p] = x;
		return ;
	}
	int mid = (l + r)/2;
	if(p < mid)
		modify(p, x, id * 2, l, mid);
	else
		modify(p, x, id * 2 + 1, mid, r);
}
```

Hàm sum:

```cpp
int sum(int x,int y,int id = 1,int l = 0,int r = n){
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)	return s[id];
	int mid = (l+r)/2;
	return sum(x, y, id * 2, l, mid) +
	       sum(x, y, id * 2 + 1, mid, r);
}

```

###Lazy Propagation
Tưởng tượng ta cần cập nhật, thay đổi giá trị trên các đoạn, ta phải làm gì bây giờ ?

**Ví dụ: **
Có một mảng a1,a2,…,aN và các truy vấn. Có 2 loại truy vấn:

1.	**S L R** : In ra **aL + a(L+1) + …. + aR**.

2.	**I L R X** : với mỗi i từ **L<=i<=R**, tăng **a(i)** lên **x**.

Ta không nên cập nhật toàn bộ node trong đoạn này, chỉ cập nhật node lớn nhất, rồi chuyển nó sang node con khi ta cần. Thủ thuật này gọi là **Lazy Propagation**, ta nên tạo một mảng **lazy** (cho node) với mặc định là 0 và mỗi khi thực hiện yêu cầu của truy vấn, tăng **lazy[id]** lên **x**.

Như trên, ta cần một mảng S cho các node.

Vậy, hàm **build** phải giống như trên. Nhưng ta cần thêm một số hàm nữa:

Hàm cập nhật một node:

```cpp
void upd(int id,int l,int r,int x){//	increase all members in this interval by x
	lazy[id] += x;
	s[id] += (r - l) * x;
}
```

Hàm chuyển các thông tin đã cập nhật sang node con:

```cpp

void shift(int id,int l,int r){//pass update information to the children
	int mid = (l+r)/2;
	upd(id * 2, l, mid, lazy[id]);
	upd(id * 2 + 1, mid, r, lazy[id]);
	lazy[id] = 0;// passing is done
}
```

Hàm để chuyển các thông tin đã cập nhật sang node con:

```cpp

void shift(int id,int l,int r){//pass update information to the children
	int mid = (l+r)/2;
	upd(id * 2, l, mid, lazy[id]);
	upd(id * 2 + 1, mid, r, lazy[id]);
	lazy[id] = 0;// passing is done
}
```


Hàm để thực hiện truy vấn yêu cầu tăng giá trị:

```cpp
void increase(int x,int y,int v,int id = 1,int l = 0,int r = n){
	if(x >= r or l >= y)	return ;
	if(x <= l && r <= y){
		upd(id, l, r, v);
		return ;
	}
	shift(id, l, r);
	int mid = (l+r)/2;
	increase(x, y, v, id * 2, l, mid);
	increase(x, y, v, id*2+1, mid, r);
	s[id] = s[id * 2] + s[id * 2 + 1];
}
```

Hàm để trả lời các truy vấn hỏi tổng đoạn:

```cpp

int sum(int x,int y,int id = 1,int l = 0,int r = n){
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)	return s[id];
	shift(id, l, r);
	int mid = (l+r)/2;
	return sum(x, y, id * 2, l, mid) +
	       sum(x, y, id * 2 + 1, mid, r);
}

```


_Bài tập:_

-	[GSS1](http://www.spoj.com/problems/GSS1/)
-	[GSS3](http://www.spoj.com/problems/GSS3/)
-	[MULTQ3](http://www.spoj.com/problems/MULTQ3)
-	[DQUERY](http://www.spoj.com/problems/DQUERY )
-	[KQUERY](http://www.spoj.com/problems/KQUERY)
-       [POSTERS](http://www.spoj.com/problems/POSTERS) 
-	[PATULJCI](http://www.spoj.com/problems/PATULJCI) 
-	[New Year Domino](http://codeforces.com/problemset/problem/500/E) 
-	[Copying Data](http://codeforces.com/problemset/problem/292/E )
-	[DZY Loves Fibonacci Numbers](http://codeforces.com/problemset/problem/446/)C
-	[FRBSUM](http://www.codechef.com/JAN14/problems/FRBSUM)


