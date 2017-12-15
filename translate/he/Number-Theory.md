# Số học

[[_TOC_]]


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