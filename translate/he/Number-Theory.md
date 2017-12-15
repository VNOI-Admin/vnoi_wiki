# Số học

[_TOC_]

# Phi hàm Euler (Euler's totient function)

**Định nghĩa:** $\phi(N)$ là số số nguyên tố cùng nhau với $N$ trong đoạn từ 1 đến $N$.

**Cách tính:**

Ta đã biết **phân tích một số ra thừa số nguyên tố (factorization)** là biểu diễn số đó dưới dạng tích của các số nguyên tố. Dễ dàng chứng minh rằng cách biểu diễn là duy nhất. Ví dụ:

- $8 = 2^3$.

- $11 = 11$.

- $36 = 2^2.3^3$.

- $935 = 5.11.17$.

- $5136 = 2^4.3.107$.

Từ cách phân tích một số ra thừa số nguyên tố, ta tính được phi hàm Euler của số đó.

```cpp
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
```

**Độ phức tạp của thuật toán:** $O(\sqrt{N})$. Để tăng tốc cho thuật toán này, hãy đọc các phần tiếp theo.

# Lí thuyết tập hợp (Set Theory)

## Tập hợp (Set) là gì?

Trong toán học, tập hợp là một nhóm các phần tử, mỗi phần tử phân biệt với nhau.

Ví dụ, 2, 4, 6 được coi là các phần tử phân biệt khi ta xét từng số một, nhưng khi chúng ta nhóm ba số ấy thì ta được một tập hợp gồm ba phần tử được kí hiệu là {2;4;6}.

Tập hợp là một trong những khái niệm cơ bản trong Toán học.

[[/uploads/number-theory-set-1.png]]

Tập hợp các hình đa giác được biểu diễn trong biểu đồ Venn.

## Tập con (Subset)

Nếu mọi phần tử thuộc tập $A$ cũng thuộc tập hợp $B$, thì tập $A$ là **tập con** của tập $B$, kí hiệu là $A \subset B$.

Tương tự, ta có thể viết $B \supset A$, đọc là $B$ là **tập cha (superset)** của tập $A$.

Quan hệ cha-con giữa các tập hợp còn được gọi là **quan hệ chứa nhau (containment)** hay **quan hệ bao hàm (inclusion)**.

Nếu $A$ là tập con của tập $B$ nhưng không bằng tập $B$, thì $A$ được gọi là **tập con không tầm thường (proper subset)** của tập $B$, kí hiệu là $A \subsetneq B$, hay $B \supsetneq A$ (đọc là $B$ là **tập cha không tầm thường (proper superset)** của tập $A$).

Ví dụ:

- {1;3} $\subset$ {1;2;3;4}

- {1;2;3;4} $\subset$ {1;2;3;4}

**Tập rỗng (empty set, kí hiệu $\varnothing$)** là tập con của tất că các tập và tất cả các tập là tập con của chính nó:

- $\varnothing \subset A$.

- $A \subset A$.

[[/uploads/number-theory-set-2.png]]

$A$ là tập con của tập $B$.

## Các phép toán với tập hợp

Có nhiều phép toán có khả năng xây dựng một tập hợp mới dựa trên các tập hợp đã cho.

### Phép hợp (Union)

Hai tập hợp có thể được ghép vào nhau. Hợp của hai tập hợp $A$ và $B$, kí hiệu là $A \cup B$, là một tập hợp gồm các phần tử thuộc tập $A$ hoặc thuộc tập $B$.

Ví dụ:

- {1;2} $\cup$ {1;2} = {1;2}

- {1;2} $\cup$ {2;3} = {1;2;3}

- {1;2;3} $\cup$ {3;4;5} = {1;2;3;4;5}

[[/uploads/number-theory-set-3.png]]

Hợp của hai tập hợp $A$ và $B$, kí hiệu là $A \cup B$.

Một vài tính chất cơ bản của phép hợp:

- $A \cup B = B \cup A$.

- $(A \cup B) \cup C = A \cup (B \cup C)$.

- $A \subset (A \cup B)$.

- $A \cup A = A$.

- $A \subset B$ khi và chỉ khi $A \cup B = B$.

### Phép giao (Intersection)

Một tập hợp mới có thể được xây dựng từ các phẩn tử mà cả hai tập đều có. Giao cuả hai tập hợp $A$ và $B$, kí hiệu $A \cap B$, là tập hợp các phần tử cùng thuộc tập $A$ và tập $B$. Nếu $A \cap B = \varnothing$, tập $A$ và tập $B$ là hai **tập rời nhau (disjoint)**.

Ví dụ:

- {1;2} $\cap$ {1;2} = {1;2}.

- {1;2} $\cap$ {2;3} = {2}.

[[/uploads/number-theory-set-intersection.png]]

Giao của hai tập hợp $A$ và $B$, kí hiệu là $A \cap B$.

Một vài tính chất cơ bản của phép hợp:

- $A \cap B = B \cap A$.

- $(A \cap B) \cap C = A \cap (B \cap C)$.

- $A \cap B \subset A$.

- $A \cap A = A$.

- $A \cap \varnothing = \varnothing$.

- $A \subset B$ khi và chỉ khi $A \cap B = A$.

### Phép lấy hiệu (Relative complement)

Ta có thể thực hiên phép trừ với hai tập hợp. Hiệu của hai tập hợp $A$ và $B$, kí hiệu là $A \backslash B$, là tập hợp bao gồm tất cả các phần tử thuộc $A$ nhưng không thuộc $B$. Lưu ý rằng ta có thể trừ phần tử mà không thuộc tập hợp, ví dụ như bỏ phần tử 'xanh' khỏi tập hợp {1;2;3}, khi đó tập hợp {1;2;3} không bị thay đổi.

Trong một số trường hợp tập $A$ được coi là tập con của một tập $U$ lớn hơn. Trong trường hợp đó, $U \backslash A$ được gọi là **phần bù hoàn toàn (absolute complement)** của tập $A$, và được kí hiệu là $A'$.

Ví dụ:

- {1;2} $\backslash$ {1;2} = $\varnothing$.

- {1;2;3;4} $\backslash$ {1;3} = {2;4}. 

- Nếu $U$ là tập hợp các số nguyên, $E$ là tập hợp các số nguyên chẵn, $O$ là tập hợp các số nguyên lẻ, khi đó $U \backslash E = E' = O$.

[[/uploads/number-theory-set-diff-1.png]]

Hiệu của hai tập hợp $A$ và $B$.

[[/uploads/number-theory-set-diff-2.png]]

Phần bù của $A$ trong $U$.

Một vài tính chất cơ bản của phép lấy hiệu

- $A \backslash B \ne B \backslash A$ với $A \ne B$.

- $A \cup A' = U$.

- $A \cap A' = \varnothing$.

- $(A')' = A$.

- $A \backslash A = \varnothing$.

- $A \backslash B = A \cap B'$.

- $U' = \varnothing$ và $\varnothing' = U$.

# Các kiến thức cơ bản về Tổ hợp (Combinatorics)

Kí hiệu $|A|$ là số phần tử của tập $A$ (hay còn được gọi là lực lượng của tập $A$).

Một vài quy tắc về tổ hợp cần nhớ:

1. **Quy tắc nhân (The Rule of Product):**
Giả sử có hai tập hợp $A$ và $B$. Khi đó số cách chọn cặp gồm một phần tử thuộc tập $A$ và một phần tử thuộc tập $B$ là $|A|.|B|$

2. **Quy tắc cộng (The Rule of Sum):** Giả sử có hai tập hợp $A$ và $B$. Khi đó số cách chọn một phần tử thuộc tập $A$ hoặc thuộc tập $B$ là $|A|+|B|$ nếu hai tập $A$ và $B$ rời nhau.

3. **Quy tắc cộng mở rộng (sieve principle)** (còn gọi là **công thức bao hàm - loại trừ (Inclusion-Exclusion Formula)**): $|A \cup B| = |A| + |B| - |A \cap B|$.

Trong trường hợp tổng quát, ta có:

$|\bigcup_{i=1}^n A_i| = \sum_{i=1}^n |A_i| - \sum_{i \ne j} |A_i \cap A_j| + |A_1 \cap A_2 \cap A_3| + |A_1 \cap A_2 \cap A_4| + ... + |A_{n-2} \cap A_{n-1} \cap A_n| - ... -$
$ (-1)^n|A_1 \cap A_2 \cap ... \cap A_n|$

Lí do ta phải cộng trừ giao của một số tập hợp vì nếu ta không làm như vậy, ta có thể đếm nhiều lần các phần tử xuất hiện tại nhiều tập hợp khác nhau.

Các quy tắc trên cũng đúng khi ta có ba hay nhiều tập hợp.

## Các kiến thức cơ bản về Chỉnh hợp và Hoán vị (Permutation)

### Chỉnh hợp không lặp (Permutation of Distinct Objects)

Cho tập hợp $A$ gồm $n$ phần tử. Mỗi bộ gồm $k$ ($0 \leq k \leq n$) phần tử được sắp thứ tự của tập hợp $A$ được gọi là một chỉnh hợp chập $k$ của $n$ phần tử thuộc $A$.

Ví dụ: Trong trận chung kết bóng đá phải phân định thắng thua bằng đá luân lưu 11 mét. Huấn luyện viên của mỗi đội cần trình với trọng tài một danh sách sắp thứ tự 5 cầu thủ trong số 11 cầu thủ để đá luân lưu 5 quả 11 mét.

Mỗi danh sách có xếp thứ tự 5 cầu thủ được gọi là một chỉnh hợp chập 5 của 11 cầu thủ.

Kí hiệu số chỉnh hợp chập $k$ của $n$ phần tử là $A_n^k$.

Số chỉnh hợp chập $k$ của $n$ phần tử được tính bởi công thức

$A_n^k = n(n-1)...(n-k+1) = \frac{n!}{(n-k)!}$.

với $n!=1.2.3...n$ và $0! = 1$.

### Hoán vị không lặp

Mỗi một chỉnh hợp chập $n$ của $n$ phần tử là một hoán vị của $n$ phần tử đó.

Kí hiệu số hoán vị của $n$ phần tử là $P_n$.

Số hoán vị của $n$ được tính bởi công thức:

$P_n = n!$.

### Hoán vị lặp (Permutation with Repetition)

Hoán vị trong đó mỗi phần tử xuất hiện ít nhất một lần được gọi là hoán vị lặp.

Số hoán vị lặp của $n$ phần tử thuộc $k$ loại, mà các phần tử loại $i$ ($1 \leq i \leq k$) xuất hiện $n_i$ lần được kí hiệu là $P(n_1,n_2,...,n_k)$ và được tính bằng công thức

$P(n_1,n_2,...,n_k) = \frac{n!}{n_1!n_2!...n_k!}$

## Các đối tượng tổ hợp (Combinatorial Objects)

Một **song ánh (bijection)** là tương ứng một-một giữa hai tập hợp, ví dụ tập hợp những người chồng và tập hợp những người vợ (một chồng chỉ có một vợ, và một vợ chỉ có đúng một chồng). Do đó, nếu bạn biết được lực lượng của một tập hợp, bạn có thể biết được lực lượng của tập kia. Ta có thể sử dụng tính chất này trong nhiều bài toán Tổ hợp, đặc biệt là các bài toán đếm, nhưng trước tiên, ta phải biết tính lực lượng của một tập các đối tượng tổ hợp.

### Tổ hợp không lặp (Combinations without repetition)

Trong tổ hợp, ta thường phải chọn một tập các phần tử nào đó và không quan tâm đến thứ tự của chúng. Số lượng tập con $k$ phần tử của một tập $n$ phần tử (còn gọi là số tổ hợp chập $k$ của $n$ phần tử) là:

$\binom{n}{k} = C^k_n = \frac{n!}{k!(n-k)!}$

### Tổ hợp có lặp (Combinations with repetition)

Giả sử ta cần chọn $k$ phần tử từ một tập $n$ phần tử, không quan trọng thứ tự và một phần tử có thể được chọn nhiều lần. Khi đó, số cách chọn là số tổ hợp lặp chập $k$ của $n$ phần tử và có giá trị là:

$\overline{C^k_n} = \binom{n+k-1}{k} = \frac{(n+k-1)!}{k!(n-1)!}$

Một tính chất thú vị về số tổ hợp có lặp: $\overline{C^k_n}$ là số nghiệm nguyên không âm của phương trình: $x_1+x_2+...+x_n = k$ với $k$ là hằng số nguyên dương.

## Vector nhị phân (Binary Vectors)

Vector nhị phân là kiểu dữ liệu ``<bitset>`` trong C++ STL.

Ngoài ra, các tính chất về tổ hợp của vector nhị phân cũng rất quan trọng. Sau đây là một số tính chất hay được sử dụng của vector nhị phân.

1. Số lượng vector nhị phân độ dài $n$ là $2^n$.

2. Số lượng vector nhị phân độ dài $n$ có $k$ số 1 là $\binom{n}{k}$, vì ta chọn $k$ vị trí có số 1 trong $n$ vị trí.

3. Số lượng cặp vector nhị phân $(a;b)$ (có quan tâm đến thứ tự) thỏa mãn điều kiện khoảng cách giữa $a$ và $b$ là $k$ là $\binom{n}{k}.2^n$.

Khoảng cách giữa hai vector nhị phân $a$ và $b$ là số lượng giá trị $i$ nguyên không âm thỏa mãn $a_i \ne b_i$

## Hệ thức truy hồi (Recurrence Relations)

Hệ thức truy hồi là công cụ hỗ trợ đắc lực trong các bài toán đếm. Truy hồi còn giúp ta định nghĩa được nhiều cấu trúc như cây, danh sách, công thức quy hoạch động hay các thuật toán "chia để trị", nên truy hồi được sử dụng rất nhiều trong tin học.

Hệ thức truy hồi là một phương trình dùng để xác định dãy số hoặc hàm số bằng cách dùng các số hạng trước để định nghĩa số hạng sau. Nó rất hữu dụng vì nhiều dãy số có thể dễ dàng được định nghĩa bằng hệ thức truy hồi:

- **Hàm đa thức (Polynomials)**: $a_n=a_{n-1}+1, a_1=1 \rightarrow a_n=n$.

- **Hàm mũ (Exponentials)**: $a_n=2a_{n-1}, a_1=2 \rightarrow a_n=2^n$.

- Giai thừa: $a_n=n.a_{n-1}, a_1 = 1 \rightarrow a_n=n!$.

Ta thường dễ dàng tìm được hệ thức truy hồi để giải các bài toán đếm. Giải hệ thức truy hồi để có được dạng công thức cần tìm là cả một nghệ thuật, tuy vậy ta có thể sử dụng trực tiếp hệ thức truy hồi để giải một số bài toán đơn giản.

## Hệ số nhị thức (Binomial Coefficients)

Hệ số nhị thức $\binom{n}{k}$ được sử dụng để đếm số cách chọn $k$ vật trong số $n$ vật.

### Đếm số đường đi trên lưới (Paths Across a Grid)

Có bao nhiêu cách để đi từ góc trái trên của một bảng $n * m$ ô đến góc phải dưới của ô đó, nếu ta chỉ được phép đi về bên phải hoặc đi xuống dưới. Ta thấy mọi đường đi hợp lệ có $n+m$ bước, và hai đường đi khác nhau nếu và chỉ nếu chúng có một bước đi xuống dưới khác nhau, vậy ta có $\binom{n+m}{n}$ cách đi.

Tính hệ số nhị thức có thể gây tràn số ở các bước trung gian, vì vậy ta nên tính hệ số nhị thức bằng công thức: $\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$

```cpp
//Computing Binomial Coefficients i.e. N choose R using dynamic programming!
/*
using the recurrent formula	nCr=(n-1)C(r)+(n-1)C(r-1)
we can use dynamic programming type approach to precompute all the binomial coefficients in O(n^2) and answer queries in O(1)
use this method when n<=5000 only.
also use this method when nCr%non-prime is required.
*/
//by Tanmay Chaudhari
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
long long ncr[5005][5005];

void precompute()
{
	int k;
	for (int i = 0; i < 5001; i++)
	{
		ncr[i][0] = ncr[i][i] = 1;
		k = i >> 1;
		for (int j = 1; j < k + 1; j++)
			ncr[i][j] = ncr[i][i - j] = (ncr[i - 1][j] + ncr[i - 1][j - 1]) % MOD;
	}
}

int main()
{
	precompute();
	cout << ncr[4892][231] << endl;
	return 0;
}
```

Chương trình trên chỉ tính được $\binom{n}{k}$ với $n$ nhỏ. Bạn có thể tham khảo chương trình sau để tính $\binom{n}{k} \% p$ với $p$ là một số nguyên tố và $n$ lớn.

```cpp
/*
	computing binomial coefficients i.e. N choose R using O(n) precomputation.
	use this for large value of N and whem (NchooseR)%prime is used;
*/
//by Tanmay Chaudhari
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
#define N 2123456
#define LL long long

LL fac[N], ifac[N];

LL PowerMod(LL a, LL n){
	LL ret = 1;
	while (n){
		if (n & 1){
			ret *= a;
			ret %= MOD;
		}
		a *= a;
		a %= MOD;
		n /= 2;
	}
	return ret;
}

inline void precompute(){
	int i;
	fac[0] = 1;
	for (i = 1; i < N; i++){
		fac[i] = (i * fac[i - 1]) % MOD;
	}
	ifac[N - 1] = PowerMod(fac[N - 1], MOD - 2);
	for (i = N - 2; i >= 0; i--){
		ifac[i] = ((i + 1) * ifac[i + 1]) % MOD;
	}
}

LL com(int n, int r){
	LL ret = fac[n];
	ret *= ifac[r];
	ret %= MOD;
	ret *= ifac[n - r];
	ret %= MOD;
	return ret;
}

int main()
{
	precompute();
	cout << com(4892,231) << endl;
	return 0;
}
```

## Một vài dãy số đếm khác (Counting Sequences)

### Dãy số Catalan

Định nghĩa: $C_n=\sum_{k=0}^{n-1} C_kC_{n-1-k}=\frac{1}{n+1}\binom{2n}{n}$

Các ứng dụng của dãy số Catalan:

- Cho một đa giác lồi $n+2$ đỉnh, ta chia đa giác thành các tam giác bằng cách vẽ các đường chéo không cắt nhau trong đa giác. $C_n$ là số cách chia như vậy.

- $C_n$ là số các từ Dyck có độ dài $2n$. Từ Dyck là từ gồm $n$ chữ X và $n$ chữ Y sao cho với mọi tiền tố của từ đó, số lượng chữ X không ít hơn số lượng chữ Y. Ví dụ, $C_3 = 5$ từ sau đây là từ Dyck độ dài 6: XXXYYY, XYXXYY, XYXYXY, XXYYXY, XXYXYY.

- Thay mỗi chữ X trong từ Dyck thành dấu mở ngoặc đơn, mỗi chữ Y thành dấu đóng ngoặc đơn, khi đó mỗi từ Dyck trở thành một dãy ngoặc hợp lệ. Vậy $C_n$ còn đếm số dãy ngoặc hợp lệ gồm $n$ cặp ngoặc: ((())), ()(()), ()()(), (())(), (()()).

- $C_n$ còn là số cách đặt ngoặc cho một biểu thức gồm $n+1$ thừa số. Ví dụ với $n=3$, ta có 5 cách đặt ngoặc cho 4 thừa số: $((ab)c)d, (a(bc))d, (ab)(cd), a((bc)d), a(b(cd))$.

- $C_n$ còn là số cây nhị phân đầy đủ có $n$ là (một cây nhị phân được gọi là đầy đủ nếu mọi nút của nó có hai nút con hoặc không có nút con nào). 

![](https://upload.wikimedia.org/wikipedia/commons/0/01/Catalan_number_binary_tree_example.png)

[Và còn nhiều ứng dụng khác...](https://en.wikipedia.org/wiki/Catalan_number#Applications_in_combinatorics)

### Số Euler 

Số Euler $\big \langle^n_k \big \rangle$ là số lượng hoán vị các số từ 1 đến $n$ mà có đúng $k$ phần tử lớn hơn phần tử đứng trước nó. Hệ thức truy hồi tính số Euler được lập bằng cách xét mỗi hoán vị $p$ của 1,2,...,$n-1$. Có $n$ vị trí để thêm số $n$ vào hoán vị, và một cách thêm số $n$ có thể làm tăng số phần tử lớn hơn phần tử đứng trước nó của $p$, hoặc bảo toàn số phần tử lớn hơn phần tử đứng trước nó. Vì vậy, 

[[/uploads/number-theory-euler-number.gif]]

### Bài toán phân tích một số nguyên (Integer Partitions) 

Ta xét bài toán sau:

Cho một số nguyên $n$. Hãy cho biết có bao nhiêu cách phân tích số $n$ thành tổng của dãy các số nguyên dương, các cách phân tích là hoán vị của nhau chỉ tính là một cách.

Ví dụ: $n=5$ có 7 cách phân tích:

1. $5 = 1+1+1+1+1$

2. $5 = 1+1+1+2$

3. $5=1+1+3$

4. $5=1+2+2$

5. $5=1+4$

6. $5=2+3$

7. $5=5$

Cách dễ nhất để đếm số cách phân tích số $n$ là định nghĩa hàm $f(n,k)$ là số cách phân tích số $n$ thành tổng của các số nguyên dương nhỏ hơn hoặc bằng $k$. Các cách phân tích số $n$ thành tổng cách số nguyên dương nhỏ hơn hoặc bằng $k$ có thể chia làm hai loại: chứa số $k$ trong phép phân tích và không chứa số $k$ trong phép phân tích, vì thế ta có $f(n,k)=f(n-k,k)+f(n,k-1)$. Ngoài ra, ta còn dễ dàng có được $f(1,1)=1$ và $f(n,k)=0$ với $k>n$. 

# Các kiến thức cơ bản về Xác suất (Probabilities)

Làm việc với xác suất giống như làm một thí nghiệm. Một **kết quả (outcome)** là một kết quả của một phép thử hay sự xảy ra hay không xảy ra của một hiện tượng nào đó. Tập hợp tất cả các kết qủa có thể xảy ra của một phép thử được gọi là **không gian mẫu (sample space)**, thường được kí hiệu là $\Omega$. Mỗi kết quả có thể của một phép thử được biểu diễn bởi một và chỉ một điểm trong không gian mẫu.

Một số phép thử ví dụ:

- Gieo một con súc sắc một lần: Không gian mẫu là $\Omega$ = {1; 2; 3; 4; 5; 6}.

- Gieo hai đồng xu phân biệt: Không gian mẫu là $\Omega$ = {(Ngửa, Ngửa), (Ngửa, Sấp), (Sấp, Ngửa), (Sấp, Sấp)}.

Ta định nghĩa **biến cố (event)** là một tập hợp các kết quả của một phép thử. Do đó, một biến cố là một tập con của không gian mẫu. Nếu ta kí hiệu một biến cố là $\Omega_A$, thì $\Omega_A \subset \Omega$. Nếu một biến cố chỉ gồm một kết quả trong không gian mẫu, thì nó được gọi là biến cố đơn. Nếu một biến cố gồm nhiều kết quả trong không gian mẫu thì nó được gọi là biến cố phức.

Thứ mà ta quan tâm nhất là xác suất xảy ra của một biến cố, kí hiệu là $P(A)$. Theo định nghĩa, $P(A)$ là một số thực nằm trong đoạn từ 0 đến 1, với 0 nghĩa là biến cố không thể xảy ra và 1 nghĩa là biến cố chắc chắn xảy ra (nghĩa là biến cố bằng không gian mẫu).

Như đã nói ở trước, mỗi kết qủa được biểu diễn bằng đúng một điểm trong không gian mẫu. Vì thế ta có công thức: $P(A) = \frac{|\Omega_A|}{|\Omega|}$.

## Biến cố độc lập (Independent Events)

Hai biến cố được gọi là độc lập với nhau nếu việc xảy ra hay không xảy ra của biến cố này không làm ảnh hưởng tới xác suất xảy ra của biến cố kia.

Ví dụ bạn gieo một con súc sắc và một đồng xu. Xác suất nhận được một số nào đó từ con súc sắc không làm ảnh hưởng đến xác suất đồng xu lật sấp hay lật ngửa. Do đó biến cố gieo con súc sắc được 6 điểm và biến cố đồng xu lật ngửa là hai biến cố độc lập với nhau.

[[/uploads/number-theory-prob-1.gif]]

Nếu hai biến cố $A$ và $B$ độc lập với nhau, không biến cố nào ảnh hưởng đến biến cố nào, khi đó ta có thể viết: $P(AB) = P(A).P(B)$.

## Xác suất có điều kiện (Conditional Probability)

Xác suất có điều kiện là xác suất của một biến cố $B$ nào đó, biết rằng một biến cố $A$ khác xảy ra. Kí hiệu là $P(B|A)$, đọc là xác suất của $B$, biết $A$.

Sử dụng toán học, ta định nghĩa $P(B|A) = \frac{P(AB)}{P(A)}$.


## Các quy tắc tính xác suất (Rules of Probability)

Khi ta phải làm việc với nhiều biến cố, có một vài quy tắc ta phải tuân theo khi tính xác suất của các biến cố này. Các quy tắc này đều phụ thuộc rất lớn vào việc các biến cố này có độc lập với nhau hay không. Đầu tiên, cho ba biến cố $A, B, C$, biến cố $S :$ "$A$ hoặc $B$ hoặc $C$ xảy ra" được kí hiệu là $A \cup B \cup C$, có xác suất $P(S) = P(A \cup B \cup C)$.

### Quy tắc nhân xác suất (Multiplication Rule) ($AB$)
$AB$ có nghĩa là giao của hai biến cố $A$ và $B$, và trong xác suất, $AB$ là biến cố "Cả $A$ và $B$ cùng xảy ra". Khi ta sử dụng từ "và", ta nghĩ đến phép nhân, vì vậy "$A$ và $B$" có thể được viết dưới dạng $A \times B$ và $A.B$.

Nếu $A$ và $B$ là hai biến cố phụ thuộc, xác suất của biến cố $AB$ được tính bằng công thức: $P(AB) = P(A \cup B) - (P(\text{chỉ } A) + P(\text{chỉ } B))$ 

Nếu $A$ và $B$ là hai biến cố phụ thuộc, xác suất của biến cố $AB$ được tính bằng công thức: $P(AB) = P(A).P(B)$.

Do đó, xác suất có điều kiện của hai biến cố độc lập có thể được tính bằng công thức: $P(B|A) = \frac{P(AB)}{P(A)} \Leftrightarrow P(B|A) = \frac{P(A).P(B)}{P(A)} \Leftrightarrow P(B|A) = P(B)$.

Công thức trên phù hợp với định nghĩa xác suất có điều kiện, biến cố $A$ có xảy ra hay không không làm ảnh hưởng đến xác suất xảy ra biến cố $B$, do đó xác suất biến cố $B$ xảy ra biết biến cố $A$ xảy ra bằng xác suất xảy ra biến cố $B$.

### Quy tắc cộng xác suất (Additive Rule) ($A \cup B$)

Trong xác suất, ta liên tưởng phép cộng như từ "hoặc". Gọi biến cố $A \cup B$ là biến cố "$A$ hoặc $B$ xảy ra", xác suất của biến cố $A \cup B$ được tính bằng công thức: $P(A \cup B) = P(A) + P(B) - P(AB)$ do $|A \cup B| = |A| + |B| - |A \cap B|$.

Nhưng hãy nhớ lại phần lí thuyết tập hợp và cách chúng ta định nghĩa không gian mẫu ở trên, gọi $C = (A \cap B)'$, khi đó ta có $P(A \cup B) = 1 - P(C)$.

## Biến cố xung khắc (Mutually Exclusive Events)

Hai biến cố được gọi là xung khắc hoặc rời nhau nếu không có một kết quả nào của phép thử làm chúng cùng lúc xảy ra. Nếu $A$ và $B$ là hai biến cố xung khắc, thì $A \cap B = \varnothing $

Nếu ba biến cố $A$, $B$, $C$ xung khắc với nhau, ta cũng có $A \cap B \cap C = \varnothing$.

[[/uploads/number-theory-mutually-exclusive-img.png]]

## Quy tắc tính xác suất của các biến cố xung khắc

### Quy tắc nhân xác suất

Từ định nghĩa các biến cố xung khắc, dễ dàng có được $P(AB) = 0$.

### Quy tắc cộng xác suất

Như chúng ta đã định nghĩa ở trên, công thức cộng xác suất hai biến cố xung khắc có dạng: $P(A \cup B) = P(A) + P(B)$.

### Quy tắc trừ xác suất (Subtraction Rule)

Từ quy tắc cộng, ta suy ra được quy tắc trừ hai biến cố xung khắc: $P(A \cup B)' = 1 - P(A) - P(B)$.

## Xác suất có điều kiện của hai biến cố xung khắc

Ta đã định nghĩa xác suất có điều kiện bằng công thức sau: $P(B|A) = \frac{P(AB)}{P(A)}$

Mà với hai biến cố xung khắc $A$ và $B$, ta lại có: $P(AB) = 0$

Do đó $P(B|A) = \frac{0}{P(A)} = 0$.

## Định lí Bayes (Bayes’ Theorem)

Trong xác suất và thống kê, định lí Bayes mô tả xác suất của một biến cố dựa trên các biến cố có liên quan đến biến cố đó.

Công thức của định lí Bayes như sau: $P(A|B) = \frac{P(A).P(B|A)}{P(B)}$, với $A$, $B$ là hai biến cố, $P(A)$, $P(B)$ là xác suất của hai biến cố, $P(A|B)$ là xác suất có điều kiện: xác suất của $A$ biết $B$ xảy ra, $P(B|A)$ là xác suất của $B$ biết $A$ xảy ra.

### Dạng mở rộng (Extended Form)

Cho $n$ biến cố $A_1, A_2, ..., A_n$, khi đó nếu $P(B) = \sum_{i=1}^n P(B|A_i)P(A_i)$ thì $P(A_i|B) = \frac{P(B|A_i)P(A_i)}{\sum_{j=1}^n P(B|A_j)P(A_j)}$.

## Thuật toán ngẫu nhiên (Randomized Algorithms)

Ta gọi thuật toán ngẫu nhiên là thuật toán sử dụng các số ngẫu nhiên để quyết định trong lúc chạy. Không giống **thuật toán tất định (deterministic algorithms)** mà với một bộ dữ liệu nhất định, thuật toán luôn ra một kết quả và chạy trong cùng một lượng thời gian, thuật toán ngẫu nhiên chạy ra kết quả khác nhau ở những lần chạy khác nhau. Ta thường chia thuật toán ngẫu nhiên ra làm hai loại:

- **Thuật toán Monte Carlo (Monte Carlo algorithms)**: Có thể ra kết quả sai - chúng ta sẽ tính xác suất ra kết quả sai để quyết định có dùng nó hay không.

- **Thuật toán Las Vegas (Las Vegas algorithms)**: Luôn chạy ra kết quả đúng, nhưng thời gian chạy sẽ khác nhau với cùng một bộ dữ liệu.

Mục tiêu của việc xây dựng các thuật toán ngẫu nhiên là giảm thời gian cài đặt thuật toán và đôi khi tạo ra những lời giải ngắn gọn hơn trong bài toán. Thuât toán ngẫu nhiên còn có khả năng giải các bài toán cực khó. Vì vậy, các thuật toán ngẫu nhiên đã trở thành một vấn đề được nhiều nhà khoa học nghiên cứu và đã được ứng dụng để giải nhiều bài toán khác nhau.

Một bài toán có thể có nhiều lời giải, một số lời giải trong số đó là tối ưu. Phương pháp làm cổ điển là xét từng phần tử một, theo thứ tự trong dữ liệu vào. Tuy nhiên, ta không thể chắc chắn các phần tử thuận lợi được phân bố đều trong dữ liệu vào. Vì vậy, thuật toán định tất có thể không tìm ra lời giải trong thời gian đủ nhanh. Lợi thế của thuật toán ngẫu nhiên là không có thứ tự duyệt các phần tử cố định và trong mọi trường hợp, thuật toán ngẫu nhiên có thể hoạt động tốt hơn.

# Các kiến thức nâng cao về công thức bao hàm - loại trừ (Principle of Inclusion-Exclusion)

## Phát biểu công thức

Công thức bao hàm - loại trừ được phát biểu như sau: 

Để tính lực lượng của hợp của nhiều tập hợp, ta tính tổng lực lượng các tập hợp đó, rồi trừ đi lực lượng của giao của **các cặp hai** tập hợp khác nhau, rồi cộng lực lượng của giao các **bộ ba** tập hợp khác nhau, rồi trừ đi lực lượng của các **bộ bốn** tập hợp, và cứ thế cho đến khi ta xét đến giao của **tất cả các tập hợp**.

## Công thức dành cho tập hợp

Công thức bao hàm - loại trừ có dạng như sau:

$|\bigcup_{i=1}^n A_i| = \sum_{i=1}^n |A_i| - \sum_{i \ne j} |A_i \cap A_j| + |A_1 \cap A_2 \cap A_3| + |A_1 \cap A_2 \cap A_4| + ... + |A_{n-2} \cap A_{n-1} \cap A_n| - ... -$
$ (-1)^n|A_1 \cap A_2 \cap ... \cap A_n|$

Ta có thể viết công thức này một cách gọn hơn bằng cách tính tổng của các tập con. Gọi $B$ là tập hợp các tập hợp $A_i$. Khi đó công thức bao hàm - loại trừ có dạng:

$|\bigcup_{i=1}^n A_i| = \sum_{C \subset B} (-1)^{|C|-1} | \bigcap_{e \in C} e |$

## Lập công thức bằng biểu đồ Venn (Venn diagrams)

Ta có biểu đồ sau biểu diễn ba tập hợp $A$, $B$ và $C$.

[[/uploads/number-theory-venn-diagram.png]]

Khi đó ta thấy lực lượng của $A \cup B \cup C$ bằng lực lượng của $A$, $B$, $C$ trừ đi lực lượng của $A \cap B$, $B \cap C$, $C \cap A$ rồi cộng thêm lực lượng của $A \cap B \cap C$.

$| A \cup B \cup C | = |A| + |B| + |C| - |A \cap B| - |B \cap C| - |C \cap A| + |A \cap B \cap C|$

Tương tự, ta có thể lập công thức với $n$ tập hợp.

## Công thức dành cho xác suất

Nếu ta có $n$ biến cố $A_1, A_2,...,A_n$, $P(A_i)$ là xác suất của biến cố $A_i$, xác suất của biến cố hợp của chúng (nghĩa là biến cố "có ít nhất một trong số $n$ biến cố $A_1, A_2, ..., A_n$ xảy ra") là

$P(\bigcup_{i=1}^n A_i) = $ $\sum_{i=1}^n$ $ P(A_i) - $$\sum_{i \ne j}$$ P(A_i A_j) + P(A_1 A_2 A_3) + P(A_1 A_2 A_4) +... + P(A_{n-2} A_{n-1} A_n) $$- ... -$ $(-1)^n.P(A_1 A_2 ... A_n)$

Nếu gọi $B$ là tập hợp các tập hợp $A_i$, công thức này cũng có thể viết gọn như sau:

$P(\bigcup_{i=1}^n A_i) = \sum_{C \subset B} (-1)^{|C|-1}. P(\bigcap_{e \in C} e)$

## Chứng minh công thức bao hàm - loại trừ

Để thuật tiện trong chứng minh, ta sử dụng công thức viết gọn sau:

$|\bigcup_{i=1}^n A_i| = \sum_{C \subset B} (-1)^{|C|-1} | \bigcap_{e \in C} e |$

với $B$ là tập hợp các tập hợp $A_i$.

Ta cần chứng minh một phần tử bất kì thuộc ít nhất một tập $A_i$, sẽ chỉ được đếm một lần trong công thức.

Xét một phần tử $x$ bất kì thuộc $k \geq 1$ tập hợp $A_i$. Ta thấy

- Trong công thức, khi $|C| = 1$, $x$ được đếm thêm $k$ lần.

- Trong công thức, khi $|C| = 2$, $x$ được đếm bớt đi $\binom{k}{2}$ lần bởi $x$ bị đếm bớt đi khi ta xét một cặp 2 tập hợp khác nhau trong số $k$ tập hợp chứa phần tử $x$.

- Trong công thức, khi $|C| = 3$, $x$ được đếm thêm $\binom{k}{3}$ lần.

- ...

- Trong công thức, khi $|C| = k$, $x$ được đếm $\binom{k}{k}$ lần. Nếu $k$ lẻ thì $x$ được đếm thêm, nếu $k$ chẵn thì $x$ được đếm bớt.

- Trong công thức, khi $|C| > k$, $x$ không được đếm.

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

# Bài tập áp dụng

## Các bài tập về đồng dư thức

[Hackerearth - The Magical Shop](https://www.hackerearth.com/problem/algorithm/the-magical-shop/)

[Hackerearth - Chandu and his Interns](https://www.hackerearth.com/problem/algorithm/chandu-and-his-interns/)

[Hackerearth - The Confused Monk](https://www.hackerearth.com/problem/algorithm/the-confused-monk/)

## Các bài tập về tổ hợp

[Hackerearth - Utkarsh and Jumps](https://www.hackerearth.com/problem/algorithm/utkarsh-and-jumps/)

[Hackerearth - Ankit and Race Team](https://www.hackerearth.com/problem/algorithm/ankit-and-race-team-10/description/)

[Hackerearth - Tic Tac Toe](https://www.hackerearth.com/problem/algorithm/tic-tac-toe/)

[Hackerearth - Roy and Little Mario](https://www.hackerearth.com/problem/algorithm/roy-and-little-mario-4/description/)

[Hackerearth - So Random](https://www.hackerearth.com/problem/algorithm/so-random/)

# Các tài liệu tham khảo

- Các bài viết về Số học trên Hackerearth: [Bài I](https://www.hackerearth.com/notes/number-theory-1/), [Bài II](https://www.hackerearth.com/notes/number-theory-ii/), [Bài III](https://www.hackerearth.com/notes/number-theory-iii/)

- Quyển "Một số vấn đề Số học chọn lọc" và "Chuyên đề chọn lọc Tổ hợp và Toán rời rạc", chủ biên Vũ Đình Mậu.

- Sách giáo khoa "Đại số và Giải tích 11" của NXB Giáo dục.

- Một số bài viết trên Wikipedia.