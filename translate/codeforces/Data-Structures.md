# Cấu Trúc Dữ Liệu
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

---

##Fibonacci Heap
Fibonacci Heap là một dạng heap có **độ phức tạp** bé hơn. Chúng ta không cần quan tâm Fibonacci Heap là gì vì trong thư viện **STL C++** đã có sẵn, được gọi là **priority_queue**.