# Số học 7 - Bao hàm - Loại trừ (Inclusion-Exclusion)

[[_TOC_]]


# Bao hàm - loại trừ (Inclusion-Exclusion)

## Phát biểu công thức

Công thức bao hàm - loại trừ được phát biểu như sau: 

Để tính lực lượng của hợp của nhiều tập hợp, ta tính tổng lực lượng các tập hợp đó, rồi trừ đi lực lượng của giao của **các cặp hai** tập hợp khác nhau, rồi cộng lực lượng của giao các **bộ ba** tập hợp khác nhau, rồi trừ đi lực lượng của các **bộ bốn** tập hợp, và cứ thế cho đến khi ta xét đến giao của **tất cả các tập hợp**.

## Công thức dành cho tập hợp

Công thức bao hàm - loại trừ có dạng như sau:

$ \| \bigcup_{i=1}^n A_i\| = \sum_{i=1}^n \|A_i\| - \sum_{i \ne j} \|A_i \cap A_j\| + \|A_1 \cap A_2 \cap A_3\| + \|A_1 \cap A_2 \cap A_4\| + ... + \|A_{n-2} \cap A_{n-1} \cap A_n\| - ... -$
$ (-1)^n\|A_1 \cap A_2 \cap ... \cap A_n\|$

Ta có thể viết công thức này một cách gọn hơn bằng cách tính tổng của các tập con. Gọi $B$ là tập hợp các tập hợp $A_i$. Khi đó công thức bao hàm - loại trừ có dạng:

$\|\bigcup_{i=1}^n A_i\| = \sum_{C \subset B} (-1)^{\|C\|-1} \| \bigcap_{e \in C} e \|$

## Lập công thức bằng biểu đồ Venn (Venn diagrams)

Ta có biểu đồ sau biểu diễn ba tập hợp $A$, $B$ và $C$.

[[/uploads/number-theory-venn-diagram.png]]

Khi đó ta thấy lực lượng của $A \cup B \cup C$ bằng lực lượng của $A$, $B$, $C$ trừ đi lực lượng của $A \cap B$, $B \cap C$, $C \cap A$ rồi cộng thêm lực lượng của $A \cap B \cap C$.

$\| A \cup B \cup C \| = \|A\| + \|B\| + \|C\| - \|A \cap B\| - \|B \cap C\| - \|C \cap A\| + \|A \cap B \cap C\|$

Tương tự, ta có thể lập công thức với $n$ tập hợp.

## Công thức dành cho xác suất

Nếu ta có $n$ biến cố $A_1, A_2,...,A_n$, $P(A_i)$ là xác suất của biến cố $A_i$, xác suất của biến cố hợp của chúng (nghĩa là biến cố "có ít nhất một trong số $n$ biến cố $A_1, A_2, ..., A_n$ xảy ra") là

$P(\bigcup_{i=1}^n A_i) = $ $\sum_{i=1}^n$ $ P(A_i) - $$\sum_{i \ne j}$$ P(A_i A_j) + P(A_1 A_2 A_3) + P(A_1 A_2 A_4) +... + P(A_{n-2} A_{n-1} A_n) $$- ... -$ $(-1)^n.P(A_1 A_2 ... A_n)$

Nếu gọi $B$ là tập hợp các tập hợp $A_i$, công thức này cũng có thể viết gọn như sau:

$P(\bigcup_{i=1}^n A_i) = \sum_{C \subset B} (-1)^{\|C\|-1}. P(\bigcap_{e \in C} e)$

## Chứng minh công thức bao hàm - loại trừ

Để thuật tiện trong chứng minh, ta sử dụng công thức viết gọn sau:

$\|\bigcup_{i=1}^n A_i\| = \sum_{C \subset B} (-1)^{\|C\|-1} \| \bigcap_{e \in C} e \|$

với $B$ là tập hợp các tập hợp $A_i$.

Ta cần chứng minh một phần tử bất kì thuộc ít nhất một tập $A_i$, sẽ chỉ được đếm một lần trong công thức.

Xét một phần tử $x$ bất kì thuộc $k \geq 1$ tập hợp $A_i$. Ta thấy

- Trong công thức, khi $\|C\| = 1$, $x$ được đếm thêm $k$ lần.

- Trong công thức, khi $\|C\| = 2$, $x$ được đếm bớt đi $\binom{k}{2}$ lần bởi $x$ bị đếm bớt đi khi ta xét một cặp 2 tập hợp khác nhau trong số $k$ tập hợp chứa phần tử $x$.

- Trong công thức, khi $\|C\| = 3$, $x$ được đếm thêm $\binom{k}{3}$ lần.

- ...

- Trong công thức, khi $\|C\| = k$, $x$ được đếm $\binom{k}{k}$ lần. Nếu $k$ lẻ thì $x$ được đếm thêm, nếu $k$ chẵn thì $x$ được đếm bớt.

- Trong công thức, khi $\|C\| > k$, $x$ không được đếm.

Vì vậy, số lần $x$ được đếm là $T = \binom{k}{1} - \binom{k}{2} + \binom{k}{3} - ... + (-1)^{i-1}.\binom{k}{i} + ... + (-1)^{k-1}.\binom{k}{k}$.

Để tính $T$, ta khai triển $(1-x)^k$ bằng **nhị thức Niu-tơn (Newton binomial)**:

$(1-x)^k = \binom{k}{0} - \binom{k}{1}.x + \binom{k}{2}.x^2 - \binom{k}{3}.x^3 + ... + (-1)^k.\binom{k}{k}.x^k$.

Ta thấy với $x=1$, $(1-x)^k = T-1$, do đó $T = (1-1)^k+1 = 1$ hay điều phải chứng minh. 

## Ứng dụng: Đếm số số nguyên tố cùng nhau với một số cho trước trong một đoạn

Đây là một bài toán dễ dựa trên công thức bao hàm - loại trừ.

Cho hai số nguyên $n$ và $r$, đếm số số nguyên tố cùng nhau với $n$ trong đoạn $[1;r]$.

Thuật toán: Tìm **phần bù (the inverse)**: Đếm số số không nguyên tố cùng nhau với $n$.

Xét các ước nguyên tố của $n$, đánh số chúng từ 1 đến $k$.

Ta có thể tính số số trong đoạn $[1;r]$ chia hết cho $p_i$ bằng công thức $[\frac{r}{p_i}]$.

Tuy vậy, nếu ta chỉ tính tổng tất cả các số này, ta sẽ ra kết qủa sai. Đó là do một số số có thể chia hết cho nhiều $p_i$. Vì vậy ta cần sử dụng đến công thức bao hàm - loại trừ.

```cpp
int solve (int n, int r) {
 vector<int> p;
	for (int i=2; i*i<=n; ++i)
		if (n % i == 0) {
 p.push_back (i);
			while (n % i == 0)
 n /= i;
		}
	if (n > 1)
 p.push_back (n);
 
	int sum = 0;
	for (int msk=1; msk<(1<<p.size()); ++msk) {
		int mult = 1,
 bits = 0;
		for (int i=0; i<(int)p.size(); ++i)
			if (msk & (1<<i)) {
				++bits;
 mult *= p[i];
			}
 
		int cur = r / mult;
		if (bits % 2 == 1)
 sum += cur;
		else
 sum -= cur;
	}
 
	return r - sum;
}
```  
