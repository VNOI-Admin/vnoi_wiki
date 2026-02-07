---
title: Bao hàm loại trừ
description: 
published: true
date: 2026-02-07T15:28:59.507Z
tags: 
editor: markdown
dateCreated: 2026-02-07T15:28:59.507Z
---

# Bao hàm loại trừ

**Người viết**:
- Phạm Vũ Phương - Trường THPT Chuyên Hà Tĩnh.

**Reviewer:**
- Đoàn Quang Huy - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

Trong giới lập trình thi đấu, nguyên lý **Bao hàm – Loại trừ** (*Principle of Inclusion-Exclusion*, viết tắt là PIE) là một công cụ toán học rất hữu ích để giải các bài toán đếm, đặc biệt là các bài toán có sự xuất hiện của các tập hợp có phần chung chồng chất nhau.

Qua bài viết này, bạn đọc sẽ được tìm hiểu kỹ hơn về nguyên lý Bao hàm -- Loại trừ và cách lập luận dựa trên phương pháp này để giải quyết các bài tập Lập trình thi đấu liên quan qua một số bài toán minh họa.

## Bài toán mở đầu

Giả sử ta có một tập hữu hạn $X$ và ba tập con $A, B, C$. Để tính $|A \cup B \cup C|$ khi $A, B, C$ đôi một rời rạc nhau, ta chỉ việc cộng $|A| + |B| + |C|$. Tuy nhiên, khi các tập hợp này tồn tại phần chung, phép cộng này sẽ **đếm thừa**, vì các phần tử thuộc $A \cap B$, $A \cap C$, $B \cap C$ đã bị đếm hai lần và các phần tử thuộc $A \cap B \cap C$ bị đếm ba lần.

Để giải quyết các phần bị đếm thừa, ta có thể trừ đi:

$$
|A \cap B| + |A \cap C| + |B \cap C|
$$

![pie_3_element_1.png](/algo/pie/pie_3_element_1.png)

Lúc này phép đếm đã gần đúng, ngoại trừ các phần tử thuộc $A \cap B \cap C$ — sau khi được cộng 3 lần lại bị trừ ba lần. Do đó, ta cần cộng lại một lần nữa. Kết quả là:

$$
|A \cup B \cup C| = |A| + |B| + |C| - |A \cap B| - |A \cap C| - |B \cap C| + |A \cap B \cap C|
$$

![pie_3_element_2.png](/algo/pie/pie_3_element_2.png)

<!--Hoặc, viết tương đương:
$$
|X \setminus (A \cup B \cup C)| = |X| - |A| - |B| - |C| + |A \cap B| + |A \cap C| + |B \cap C| - |A \cap B \cap C|
$$-->

:::spoiler *Ví dụ minh họa*

Trong một lớp học có:
* 30 học sinh thích Toán (tập $A$)
* 25 học sinh thích Lý (tập $B$)
* 20 học sinh thích Hóa (tập $C$)

Ngoài ra:
- Có 10 học sinh thích cả Toán và Lý (ký hiệu: $|A\cap B| = 10$).
- Có 8 học sinh thích cả Toán và Hóa (ký hiệu: $|A\cap C| = 8$).
- Có 5 học sinh thích cả Lý và Hóa (ký hiệu: $|B\cap C| = 5$).
- Có 3 học sinh thích cả ba môn (ký hiệu: $|A\cap B\cap C| = 3$).

Hỏi có bao nhiêu học sinh thích ít nhất một trong ba môn Toán, Lý, Hóa? ($|A \cup B \cup C|$)

Ta áp dụng công thức vừa nêu ở trên:

$$
|A \cup B \cup C| = 30 + 25 + 20 − 10 − 8 − 5 + 3 = 55
$$

Vậy có 55 học sinh thích ít nhất một trong ba môn Toán, Lý, Hóa.

:::

Nguyên lý bao hàm – loại trừ giúp ta mở rộng cách tính này để giải quyết các trường hợp tổng quát hơn, khi có nhiều tập hợp cùng tham gia.

## Nguyên lý Bao hàm - Loại trừ
### Công thức dạng tập hợp
Khi tổng quát lên $n$ tập, gọi $A_0, A_1, \dots, A_{n-1}$ là các tập con của $X$. Ta có công thức:

$$
\begin{align*}
\left|\bigcup_{0 \leq i < n} A_i \right|
    &= \sum_{\substack{S \subseteq \{0, 1, \dots, n-1\} \\ S \neq \varnothing}}
      (-1)^{|S| + 1} \cdot 
      \left| A_{S_0} \cap A_{S_1} \cap \dots \cap A_{S_{|S|-1}} \right| \\
&= \sum_{\substack{S \subseteq \{0, 1, \dots, n - 1\} \\ S \neq \varnothing}} (-1)^{|S| + 1} \cdot \left| \bigcap_{i \leq S} A_i \right|
\end{align*}
$$

Công thức này phát biểu rằng để tính kích thước của hợp các tập $A_i$, ta xét tất cả các tập con $S$ khác rỗng của $\{0,1,\dots,n-1\}$. Mỗi tập con $S$ tương ứng với giao giữa các tập có chỉ số thuộc $S$.

Dấu của mỗi số hạng được xác định bởi lực lượng của $|S|$:
- Nếu $|S|$ lẻ, thì số hạng đó được cộng vào tổng.
- Nếu $|S|$ chẵn, thì số hạng đó được trừ ra.


Nhờ vậy, phép tính kích thước của một hợp lớn được chuyển thành việc tính kích thước các giao nhỏ hơn.

:::spoiler *Chứng minh*
Việc chứng minh tính đúng đắn của công thức này không khó: ta chỉ cần kiểm tra xem một phần tử $x$ được đếm bao nhiêu lần ở cả hai vế.

- Nếu $x \notin \bigcup_{i=1}^n A_i$, thì nó được đếm đúng một lần ở mỗi vế.
- Giả sử $x \in \bigcup_{i=1}^n A_i$, và cụ thể hơn, $x$ thuộc đúng $(m \geq 1)$  tập trong số $A_i$.

  - Ở vế trái, số lần đếm là $0$.
  - Ở vế phải, số lần đếm là:
    $$
    1 - \binom{m}{1} + \binom{m}{2} - \binom{m}{3} + \cdots + (-1)^m \binom{m}{m} = 0
    $$

Vì vậy, hai vế bằng nhau. 
:::


**Cài đặt**

``` cpp=
int Union = 0;
for (int mask = 0; mask < (1 << n); mask++) {

    // mask biểu diễn một tập con S của {0, 1, ..., n-1}
    // intersect[mask] = | ⋂_{i ∈ S} A_i |

    // __builtin_parity(mask) trả về:
    //   1 nếu số bit bật trong mask là lẻ  (|S| lẻ)
    //   0 nếu số bit bật trong mask là chẵn (|S| chẵn)

    if (__builtin_parity(mask))
        Union += intersect[mask];   // |S| lẻ ⇒ cộng
    else
        Union -= intersect[mask];   // |S| chẵn ⇒ trừ
}
```

Khi không nhất thiết phải lấy hợp của tất cả các tập $A_0, A_1, \dots, A_{n-1}$, ta có thể mở rộng nguyên lý bao hàm–loại trừ cho bất kỳ tập con chỉ số  $T \subseteq \{0,1,\dots,n-1\}$.

Khi đó, ta chỉ xét các tập $A_i$ với $i \in T$. Công thức bao hàm–loại trừ trong trường hợp này trở thành:

$$
\left|\bigcup_{i \in T} A_i \right| = 
\sum_{\substack{S \subseteq T \\ S \neq \varnothing}}
(-1)^{|S| + 1}
\left| \bigcap_{i \in S} A_i \right|
$$



Ta có thể tính giá trị trên với mọi $S$ bằng trick duyệt bitmask trong $\mathcal{O}(3^n)$ hoặc DP SoS (bạn đọc có thể tham khảo cách tính qua bài [VNOI Wiki](https://wiki.vnoi.info/vi/algo/dp/dp-sos-1) này).


### Công thức dành cho xác suất
Nếu ta có $n$ biến cố $A_1, A_2, \ldots, A_n$, $P(A_i)$ là xác suất của biến cố $A_i$, xác suất của biến cố hợp của chúng (nghĩa là biến cố "có ít nhất một trong số $n$ biến cố $A_1, A_2, \ldots, A_n$ xảy ra") là

$$
P\left( \bigcup_{i=1}^{n} A_i \right) 
= \sum_{i=1}^{n} P(A_i) \;-\; \sum_{i\ne j} P(A_i A_j) \;+\; P(A_1 A_2 A_3) \;+\; P(A_1 A_2 A_4) \;+\; \ldots \;+\; P(A_{n-2} A_{n-1} A_n) \;-\; \ldots \;-\; (-1)^n P(A_1 A_2 \ldots A_n)
$$

Nếu gọi $B$ là tập hợp các tập hợp $A_i$, công thức này cũng có thể viết gọn như sau:

$$
P\left( \bigcup_{i=1}^{n} A_i \right)
= \sum_{C \subset B} (-1)^{|C|-1} \, P\left( \bigcap_{e \in C} e \right)
$$



## Mở rộng nguyên lý Bao hàm - Loại trừ

### Khôi phục từ điều kiện phủ định

Một ứng dụng rất điển hình của nguyên lý bao hàm–loại trừ là trong các bài toán đếm số phần tử thỏa một tập điều kiện cho trước khi bản thân các điều kiện này rất khó đếm trực tiếp, nhưng các phủ định của chúng thì lại dễ đếm hơn.

#### Bài toán

Để hiểu rõ hơn về các dạng bài này, ta tìm hiểu bài toán **Chia kẹo Euler có chặn trên** được phát biểu như sau:

> Cho hai số nguyên $N, K$ là số viên kẹo và số người nhận kẹo. Mỗi người có một giới hạn về số kẹo mà người đó được nhận được, được cho bởi dãy $U_1, U_2, \dots, U_K$. Hãy đếm số cách chia $N$ viên kẹo thỏa mãn các giới hạn.
> 
> Nói cách khác, ta cần đếm số dãy $x_1, x_2, \dots, x_K$ sao cho $0 \leq x_i \leq U_i$ với mọi $1 \leq i \leq K$ và tổng $x$ bằng đúng $N$.

Giới hạn:

- $1 \leq U_i \leq N \leq 10^9$.
- $1 \leq K \leq 20$.

<!--**Ví dụ**: Bài toán chia kẹo Euler **có chặn trên**
Cho:
- Một số nguyên $N$ với $0 \le N \le 10^9$ là số viên kẹo cần chia.
- Một số nguyên $K$ với $1 \le K \le 20$ là số người nhận kẹo.
- Một mảng $U = [\,U_1, U_2, \dots, U_K\,]$ với $0 \le U_i \le N$, trong đó $U_i$ là giới hạn tối đa số kẹo mà người thứ $i$ có thể nhận.

Hãy đếm số cách chọn các giá trị $x_1, x_2, \dots, x_K$ sao cho:
$0 \le x_i \le U_i \quad \forall i = 1, 2, \dots, K,$ và $x_1 + x_2 + \cdots + x_K = N.$ Trong đó $x_i$ là số kẹo mà người thứ $i$ nhận.-->

#### Phân tích

Với các công cụ tổ hợp quen thuộc, ta có thể giải quyết bài toán Chia kẹo Euler có chặn dưới một cách dễ dàng, tức người thứ $i$ phải nhận ít nhất $L_i$ viên kẹo. Tuy nhiên, điều tương tự không xảy ra với bài toán được phát biểu như trên.

Do đó, thay vì tìm kết quả trực tiếp cho bài toán Chia kẹo Euler có chặn trên, ta sẽ giải quyết bài toán dễ hơn rồi tìm cách áp dụng Bao hàm loại trừ để bù trừ ra đáp án cần tìm. Trước khi tiếp tục với ý tưởng lời giải, chúng ta tìm hiểu nhanh lời giải của bài toán Chia kẹo Euler có chặn dưới.

#### Bài toán có điều kiện phủ định: Chia kẹo Euler có chặn dưới

> Đếm số dãy $x_1, x_2, \dots, x_K$ sao cho $0 \leq L_i \leq x_i$ với mọi $1 \leq i \leq K$ và tổng $x$ bằng đúng $N$. Trong trường hợp này, ta chọn $L_i = U_i + 1$.

Với bài toán Chia kẹo Euler cơ bản, ta có $L_i = 1$. Khi này, ta có thể biến đổi quá trình chia kẹo thành chọn $K - 1$ "vách ngăn" để chia các viên kẹo thành $K$ nhóm. Do có tổng cộng $N - 1$ cách ngăn, số cách chọn là:

$$
\texttt{eulerCandy}(N, K) = \binom{N - 1}{K - 1}
$$

Với $L_i \geq 1$, ta có thể mô hình quá trình chia kẹo lại với $2$ bước sau:

- Với người nhận thứ $i$, ta đặt trước vào $L_i - 1$ viên kẹo.
- Chia số kẹo còn lại theo bài toán Chia kẹo Euler cơ bản. Khi này, số kẹo mià mỗi người nhận được sẽ là $L_i$.

Dễ thấy, số kẹo còn lại sau bước 1 là $N - \sum L_i + K$, do đó, đáp án của bài toán lúc này là:

$$
\texttt{eulerCandy}\left(N - \sum L_i + K, K\right) = \binom{N - \sum L_i + K - 1}{K - 1}
$$

Lưu ý, cách này vẫn đúng với $L_i = 0$, khi đó, ta hình dung người nhận sẽ "nợ" 1 viên kẹo ở bước đầu tiên. Do mỗi người đều sẽ nhận ít nhất 1 viên kẹo ở bước chia thứ hai nên phần "nợ" sẽ luôn được triệt tiêu.

#### Ý tưởng

Khi đã giải được bài toán với điều kiện phủ định của bài toán ban đầu, ta tìm cách bù trừ để tìm kết quả.

Có thể thấy, nếu bài toán chỉ có một điều kiện cận trên (ví dụ chỉ người $1$ có giới hạn $x_1 \le U_1$) thì ta có thể nghĩ ngay đến cách bù trừ đơn giản: đếm số cách mà người đó nhận ít nhất $U_1 + 1$ viên, rồi trừ khỏi tổng số cách chia không ràng buộc.

Tuy nhiên trong bài toán này ta có tới $K$ điều kiện cận trên $x_i \le U_i$ đồng thời. Việc xử lý từng điều kiện một sẽ khiến việc tính toán là vô cùng phức tạp, do đó, ta phải dùng nguyên lý bao hàm – loại trừ. 

#### Áp dụng Bao hàm -- loại trừ

Ta biến đổi bài toán thành đếm số cách chia kẹo bị vi phạm **ít nhất một** trong các điều kiện $x_i \leq U_i$. Do đây là phần bù của tập nghiệm cần tìm, nên ta chỉ việc lấy tổng số cách chia, trừ đi số lượng cách chia bị vi phạm là có được đáp án cần tìm.

Để mô hình hoá, ta định nghĩa $A_i$ là tập các cách chia mà $x_i > U_i$, tức vi phạm cận trên của người thứ $i$; những người còn lại có thể bị vi phạm hoặc không (không có giới hạn ràng buộc). Có thể thấy, tập các cách chia vi phạm ít nhất một trong các điều kiện là hợp của các $A_i$; nói cách khác, ta cần đếm:

$$
\left| \bigcup_{1 \leq i \leq K} A_i \right|
$$

Nhờ công thức Chia kẹo Euler có chặn dưới đã được trình bày ở phần trên, ta hoàn toàn có thể tính được số cách chia đồng thời vi phạm cận trên của các người nhận thuộc tập $S$, với mọi $S \subseteq \{1, 2, 3, \dots, K\}$. Nói một cách toán học hơn, ta cần tính:

$$
f(S) = \left|\bigcap_{i \in S} A_i\right|
$$

Giá trị của $f(S)$ được xác định bằng kết quả của bài toán Chia kẹo Euler có chặn dưới với mảng $L$ được định nghĩa như sau:

$$
L_i = \begin{cases}
U_i + 1 & i \in S \\
0 & i \notin S \\
\end{cases}
$$

Khi đã tính được các $f(S)$, ta áp dụng bao hàm -- loại trừ để tìm số cách chia có ít nhất một điều kiện bị vi phạm:

$$
\left|\bigcup_{0 \le i < K} A_i\right| = \sum_{\substack{S \subseteq \{0,1,\dots,K-1\} \\ S \neq \varnothing}} (-1)^{|S|+1} \left|\bigcap_{i \in S} A_i\right|
$$

Đây chính là số lượng cách chia kẹo **không hợp lệ**. Để tìm đáp án cuối cùng, ta lấy $f(\varnothing)$ trừ đi kết quả vừa tính được. Cuối cùng, ta có công thức xác định đáp án như sau:

$$
\sum_{S \subseteq \{0, 1, \dots, K - 1\}} (-1)^{|S|} \left| \bigcap_{i \in S} A_i \right|
$$

Như vậy, chỉ cần tính các giao theo công thức chia kẹo Euler rồi áp dụng bao hàm–loại trừ là ta có thể giải được bài toán kể cả khi có tới $K$ điều kiện cùng lúc.

:::spoiler *Cài đặt*
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Hàm tính C(n, k) (số cách chọn k từ n)
ll C(ll n, ll k) {
    if(k < 0 || k > n) return 0;
    ll res = 1;
    for(ll i = 1; i <= k; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// Hàm tính số cách chia m viên kẹo cho n người với cận dưới L[]
ll eulerWays(ll m, int n, vector<int> &L) {
    ll sumL = accumulate(L.begin(), L.end(), 0LL);
    m -= sumL;
    if(m < 0) return 0;
    return C(m + n - 1, n - 1);
}

int main() {
    int K; // số người
    ll M; // tổng số kẹo
    cin >> K >> M;

    vector<int> L(K), U(K);
    for(int i = 0; i < K; i++) cin >> L[i]; // cận dưới
    for(int i = 0; i < K; i++) cin >> U[i]; // cận trên

    // Tính tổng số cách chia tự do (chỉ cận dưới)
    ll total = eulerWays(M, K, L);

    // Bao hàm–loại trừ để trừ các trường hợp vi phạm cận trên
    ll bad = 0;
    for(int mask = 1; mask < (1 << K); mask++) {
        vector<int> Lmod = L;
        int bits = __builtin_popcount(mask);
        ll subtract = 0;

        for(int i = 0; i < K; i++) {
            if(mask & (1 << i)) {
                // Nếu i-th người vi phạm, ta đặt xi > Ui => xi >= Ui+1
                Lmod[i] = U[i] + 1;
            }
        }
        ll ways = eulerWays(M, K, Lmod);
        if(bits % 2 == 1) bad += ways;
        else bad -= ways;
    }

    ll answer = total - bad;
    cout << answer << endl;

    return 0;
}

```
:::

### Bao hàm loại trừ trên các tính chất đồng nhất

Mở rộng từ ví dụ ở phần trước, thay vì mỗi người $i$ có một cận trên riêng $U_i$, ta xét trường hợp đồng nhất với một cận trên chung $V$. Nói cách khác, bài toán trở thành: Đếm số cách chia $N$ viên kẹo cho $K$ người sao cho mỗi người nhận tối đa $V$ viên kẹo. 

Ý tưởng xử lý tương tự như trước, nhưng có một nhận xét quan trọng: các tập $A_0, A_1, ..., A_{K-1}$ là đồng nhất, nên kích thước của giao  $\bigcap_{i \in S} A_i$ chỉ phụ thuộc vào số lượng phần tử của $S$, tức $|S|$, chứ không phụ thuộc vào các chỉ số cụ thể trong $S$.

Do đó, với mỗi $k = |S|$ (với $1 \leq k \leq K$), nếu tính được $\left| \bigcap_{i \in S} A_i \right |$ cho một tập $S$ bất kỳ có $k$ phần tử, ta có thể nhân kết quả với $\binom{K}{k}$ (tức số cách chọn tập $S$ có kích thước $k$) để tính tổng $\sum_{|S| = k} \left| \bigcap_{i \in S} A_i \right|$.

Cuối cùng, ta thay đổi công thức bao hàm loại trừ ở trên để có đáp án cho bài toán mới:

$$
\sum_{0 \leq k \leq K} (-1)^k \cdot \binom{K}{k} \left| \bigcap_{i \in S(k)} A_i \right|
$$

Với $S(k)$ là một tập $S$ bất kỳ có kích thước là $k$, nói cách khác, ta giải bài toán Chia kẹo Euler có chặn dưới với $\sum L = k \cdot (V+1)$

Có thể thấy, phương pháp này cho phép giải được bài toán ngay cả khi $K$ lớn (ví dụ $K \leq 200000$), vì ta không cần duyệt tất cả $2^K$ tập con mà chỉ duyệt $K$ giá trị $k$.

### Bao hàm loại trừ trên số nguyên tố

Một ứng dụng quan trọng khác của bao hàm loại trừ đó là thao tác trên tập các thừa số nguyên tố. Khi này, ta xem một số nguyên là một tập hợp với các phần tử là các thừa số nguyên tố của nó. Với các tính chất số học, ta dễ dàng chứng minh kích thước của các tập hợp như vậy là tương đối nhỏ.

#### Bài toán

Để hiểu rõ hơn về cách hoạt động của mô hình bao hàm loại trừ trên số nguyên tố, ta cùng tìm hiểu bài toán sau đây:

> Cho dãy $A$ gồm $N$ phần tử và $Q$ truy vấn có dạng:
>
> - Cho một số nguyên $x$, đếm số phần tử thuộc mảng $A$ **không** nguyên tố cùng nhau với $x$. Nói cách khác, đếm số giá trị $1 \leq i \leq N$ thỏa $\gcd(A_i, x) > 1$.

Giới hạn:

- $1 \leq N \leq 2 \cdot 10^5$.
- $1 \leq A_i \leq 10^6$.

#### Phân tích

Nhắc lại, để tính ước chung lớn nhất của hai số nguyên, ta tìm tập thừa số nguyên tố của cả hai số (có xét phần tử trùng) rồi lấy giao của hai tập. Để tính ước chung lớn nhất của nhiều số nguyên, ta cũng tìm tập thừa số nguyên tố của mỗi số rồi lấy giao của tất cả các tập.

Với bài toán này, do chỉ cần xét ước chung lớn nhất lớn hơn hay bằng $1$, ta có thể không quan tâm số mũ của thừa số nguyên tố. Nói cách khác, ta bỏ qua các phần tử trùng trong phân tích thừa số nguyên tố của một số bất kỳ.

Ví dụ, số $600$ có tập thừa số nguyên tố là $\{2, 3, 5\}$, số $144$ có tập thừa số nguyên tố là $\{2, 3\}$. Ta biết rằng $\gcd(600, 144)$ có tập thừa số nguyên tố là $\{2, 3\}$ nên hiển nhiên lớn hơn $1$. Trường hợp ước chung lớn nhất bằng $1$ xảy ra khi tập thừa số nguyên tố là rỗng.

#### Xây dựng mô hình Bao hàm loại trừ

Từ phân tích trên, dễ thấy hai số không nguyên tố cùng nhau khi và chỉ khi tập thừa số nguyên tố của chúng có ít nhất một phần tử chung. Nói cách khác, với một số nguyên $x$ có tập thừa số nguyên tố $\mathcal{P}(x) = \{p_1, p_2, \dots, p_k\}$, một số nguyên $y$ không nguyên tố cùng nhau với $x$ khi $y$ là bội của **ít nhất một** giá trị $p_i$.

Gọi $M_p$ là tập các số nguyên thuộc dãy $A$ là bội của $p$ (với $p$ là một số nguyên tố). Dễ thấy, một truy vấn với số nguyên $x$ bây giờ tương đương với việc tính giá trị:

$$
f(x) = \left| \bigcup_{p \in \mathcal{P}(x)} M_p \right|
$$

Mặt khác, ta có thể dễ dàng đếm số phần tử là bội của **toàn bộ giá trị** của một tập thừa số nguyên tố $\mathcal{P}(S)$ nào đó, ta chỉ đơn giản là đếm số bội của tích của tập số. Nói cách khác, ta dễ dàng có giá trị sau với mọi tập thừa số nguyên tố $S$:

$$
g(S) = \left| \bigcap_{p \in S} M_p \right|
$$

Dễ thấy, ta chỉ cần xét các tập $S$ có tích không quá $10^6$ vì các tập còn lại hiển nhiên sẽ có giá trị $g(S) = 0$.

Áp dụng Bao hàm loại trừ, ta có thể tính $f(x)$ dựa trên $g(S)$:

$$
f(x) = \sum_{\substack{T \subseteq \mathcal{P}(x) \\ T \neq \varnothing}} (-1)^{|T| + 1} \cdot \left| \bigcap_{p \in S} M_p \right| = \sum_{\substack{T \subseteq \mathcal{P}(x) \\ T \neq \varnothing}} (-1)^{|T| + 1} \cdot g(T)
$$

Như vậy, nếu biết trước các giá trị $g(S)$, ta hoàn toàn có thể tính $f(x)$ trong $2^k$ với $k$ là số lượng thừa số nguyên tố phân biệt của $x$. Ta có thể chứng minh được rằng giá trị của $k$ không thể vượt quá $7$!

:::spoiler *Chứng minh*
Ta xét $8$ số nguyên tố nhỏ nhất:

$$
2 \cdot 3 \cdot 5 \cdot 7 \cdot 11 \cdot 13 \cdot 17 \cdot 23 \approx 9,6 \cdot 10^6 > 10^6
$$

Trong khi đó $a_i \leq 10^6$, ta thấy rằng không thể tồn tại một số nguyên không quá $10^6$ có nhiều hơn $7$ số nguyên tố phân biệt.

Như vậy, nếu tồn tại đáp án, ta chỉ cần chọn một phần tử rồi chọn thêm tối đa $6$ phần tử khác để "loại bỏ" $6$ ước nguyên tố của phần tử đầu tiên ra khỏi ước chung lớn nhất.
:::

Như vậy, số thao tác duyệt cho mỗi truy vấn là không quá $2^7 = 128$ lần.

#### Tính $g(S)$

Nhiệm vụ còn lại của bài toán là tính $g(S)$ một cách hiệu quả. Ta có hai cách làm đều có độ phức tạp phù hợp với bài toán đang xét như sau:

1. Duyệt tất cả các tập $S$ rồi duyệt tất cả các bội của tích của tập $S$ không quá $10^6$. Độ phức tạp của cách này là $\mathcal{O}(A \ln A)$ được tính bởi [chuỗi điều hòa](https://vi.wikipedia.org/wiki/Chu%E1%BB%97i_%C4%91i%E1%BB%81u_h%C3%B2a).
2. Ta duyệt các phần tử của mảng $A$ rồi duyệt các tập con của $\mathcal{P}(A_i)$. Độ phức tạp của cách này là $\mathcal{O}(N \cdot 2^7)$ đã được chứng minh ở phần trên.

#### Cài đặt

:::spoiler *Cài đặt*
Đầu tiên, ta chuẩn bị hàm `preProcess` để thực hiện các tiền xử lý như Sàng nguyên tố và chuẩn bị hàm $g$ (được lưu ở mảng `countMultiple`):

```cpp=
const int maxN = 1e5 + 5;
const int maxA = 1e6 + 6;
int A[maxN], countMultiple[maxA], freq[maxA], sieve[maxA], N;

void preProcess() {
    // Sàng nguyên tố
    iota(sieve, sieve + maxA, 0);
    for (int p = 2; p * p < maxA; p++) {
        if (sieve[p] < p) continue;
        for (int a = p * p; a < maxA; a += p) sieve[a] = p;
    }

    // Chuẩn bị mảng countMultiple[S]
    for (int i = 0; i < N; i++) freq[A[i]]++;
    for (int p = 1; p < maxA; p++)
        for (int mult = p; mult < maxA; mult += p) countMultiple[p] += freq[mult];
}
```

Sau đó, ta cài đặt hàm truy vấn như sau:
```cpp=
int query (int x) {
    // Phân tích thừa số nguyên tố và giữ lại tập thừa số phân biệt
    vector<int> vec;
    while (x > 1) {
        int curPrime = sieve[x];
        vec.push_back(curPrime);
        while (x % curPrime == 0) x /= curPrime;
    }

    // Tìm bội của từng tập con và thực hiện Bao hàm loại trừ
    vector<int> multiple(1 << vec.size(), 1);
    int ans = 0;
    for (int mask = 1; mask < (1 << vec.size()); mask++) {
        int cur = __builtin_ctz(mask);
        multiple[mask] = multiple[mask ^ (1 << cur)] * vec[cur];
        if (__builtin_parity(mask))
            ans += countMultiple[multiple[mask]];
        else ans -= countMultiple[multiple[mask]];
    }
    return ans;
}
```
:::



## Các bài tập áp dụng

### [HDUOJ - Co-prime](https://acm.hdu.edu.cn/showproblem.php?pid=4135)
Cho $N, L, R$, bạn cần tính số lượng số nguyên $x$ trong đoạn $[L, R]$ sao cho $x$ nguyên tố cùng nhau với $N$, tức là $\gcd(x, N) = 1$.

Có $1 \le \mathcal{T} \le 100$ bộ test.

Giới hạn:
- $1 \le N \le 10^9$.
- $1 \le L \le R \le 10^{15}$.

#### Phân tích

Để ý rằng, nếu chúng ta có thể tính số lượng số nguyên $x$ trong đoạn $[1, X]$ sao cho $x$ nguyên tố cùng nhau với $N$, ký hiệu là $f(X)$, thì đáp án cho bài toán sẽ là: 
$$
f(R) - f(L - 1)
$$

Vậy làm thế nào để tính $f(X)$? Một số $X$ không nguyên tố cùng nhau với $N$ khi và chỉ khi tồn tại thừa số nguyên tố $P$ của $N$ sao cho $P$ chia hết cho $X$. Vì vậy, thay vì đếm số lượng các số nguyên tố cùng nhau với $N$, ta có thể đếm số lượng các số **không** nguyên tố cùng nhau với $N$, tức là các số chia sẻ ít nhất một thừa số nguyên tố với $N$.

Như vậy ta gọi $A_i$ là tập hợp các số chia hết cho $p_i$.

Lúc này, bài toán trở thành tính: 
$$
\left| \bigcup_{i=1}^n A_i \right|
$$
Việc tính hợp này có thể hơi khó, nhưng nhờ **Nguyên lý Bao hàm – Loại trừ có giới hạn**, ta có thể chuyển bài toán về tính kích thước của các giao, vốn đơn giản hơn.

:::spoiler *Cài đặt*
```cpp=
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Thừa số nguyên tố phân biệt của n
vector<long long> facd(long long n) {
    vector<long long> p;
    if (n % 2 == 0) {
        p.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            p.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) p.push_back(n);
    return p;
}

// Đếm số không cùng nhau trong [1..x]
long long cntn(long long x, const vector<long long>& p) {
    if (x <= 0) return 0;
    int k = p.size(); long long s = 0, tot = 1 << k;
    for (int m = 1; m < tot; ++m) {
        long long pr = 1; int b = 0; bool ov = 0;
        for (int i = 0; i < k; ++i) if (m & (1 << i)) {
            ++b;
            if (pr > x / p[i]) { ov = 1; break; }
            pr *= p[i];
        }
        if (ov) continue;
        long long c = x / pr;
        s += (b % 2 ? c : -c);
    }
    return s;
}

// Đếm số cùng nhau trong [1..x]
long long cntc(long long x, const vector<long long>& p) {
    return x <= 0 ? 0 : x - cntn(x, p);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        long long a, b, n; cin >> a >> b >> n;
        vector<long long> p = facd(n);
        long long ans = cntc(b, p) - cntc(a - 1, p);
        cout << "Case #" << t + 1 << ": " << ans << '\n';
    }
    return 0;
}

```
:::

#### Đánh giá
Độ phức tạp: $\mathcal{O} \left( \sqrt{N} + T \cdot 2^k \right)$ với $k < 10$ là số lượng thừa số nguyên tố phân biệt của $N$.


### [HDUOJ - Character Encoding](https://acm.hdu.edu.cn/showproblem.php?pid=6397)

Cho ba số nguyên $n, m, k$, yêu cầu tính số nghiệm của hệ phương trình $x_1 + x_2 + \cdots + x_n = k$ thỏa mãn $0 \le x_i < m$. In đáp án modulo $998 \space 244 \space 353$

Giới hạn:

- $1 \le n, m, k \le 10^5$
- Đây là bài tập multi-testcase có $\mathcal{T} \leq 400$, đảm bảo tổng $m, k$ ở các testcase là không quá $5 \cdot 10^6$.

#### Phân tích
Ta biết rằng số nghiệm nguyên không âm của: $x_1 + x_2 + \cdots + x_n = k$ được tính công thức chia kẹo euler $\binom{n + k - 1}{k} = \binom{n + k - 1}{n - 1}$. Vậy điều duy nhất cần xử lý là loại bỏ ràng buộc $x_i < m$. Để làm điều đó, ta áp dụng **Nguyên lý Bao hàm – Loại trừ**.

Gọi $e_i = [x_i \ge m]$, trong đó $[P]$ là [Iverson bracket](https://en.wikipedia.org/wiki/Iverson_bracket).

Với mỗi dãy $S \subseteq \{1,2,\dots,n\}$, ta định nghĩa:

- $f(S)$ là số dãy sao cho
  $$
  \begin{cases}
  x_i \ge m & i \in S,\\
  x_i < m & i \notin S. \\
  \end{cases}
  $$
- $g(S)$ là số dãy số sao cho $x_i \ge m \;\; \forall i \in S.$

Khi $S$ là tập rỗng, ta không áp đặt điều kiện nào, nên $f(\varnothing)$ chính là tổng số cách hợp lệ cần tìm. Rõ ràng thấy tập các tính chất này là **đồng nhất**.

Không mất tính tổng quát, ta xét tập $T = \{1,2,\dots,j\}$ với $j = |S|$. Khi đó, hệ điều kiện tương ứng với $g(T)$ là:

$$
x_1 \ge m,\; x_2 \ge m,\; \dots,\; x_j \ge m,
$$

các biến còn lại không có ràng buộc.

Ta đặt:

$$
y_i =
\begin{cases}
x_i - m & i \leq j \\
x_i & i > j \\
\end{cases}
$$

Hệ này tương đương với: $y_1 + y_2 + \cdots + y_n = k - j m$. Số nghiệm nguyên không âm của hệ trên là:
$$
g(T) = \binom{n + k - jm - 1}{n - 1}
$$

Áp dụng **Nguyên lý Bao hàm – Loại trừ**, từ quan hệ:

$$
g(S) = \sum_{T \supseteq S} f(T)
$$

Từ đó suy ra:

$$
f(\varnothing)
= \sum_{S \subseteq \{1,2,\dots,n\}} (-1)^{|S|} g(S)
$$

Do $g(S)$ chỉ phụ thuộc vào $|S|$, công thức cuối cùng của ta là:

$$
f(\varnothing)
= \sum_{j=0}^{n} (-1)^j \binom{n}{j}
\binom{n + k - jm - 1}{n - 1}
$$

:::spoiler *Cài đặt*
```cpp=
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

// lũy thừa nhị phân mod MOD
long long pw(long long a, long long e) {
    long long r = 1 % MOD; a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// tiền xử lý giai thừa và nghịch đảo giai thừa
void prep(int n, vector<long long>& f, vector<long long>& inv) {
    f.assign(n + 1, 1);
    inv.assign(n + 1, 1);
    for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % MOD;
    inv[n] = pw(f[n], MOD - 2);
    for (int i = n; i >= 1; --i) inv[i - 1] = inv[i] * i % MOD;
}

// C(n, r) mod MOD
long long C(int n, int r, const vector<long long>& f, const vector<long long>& inv) {
    if (r < 0 || r > n) return 0;
    return f[n] * inv[r] % MOD * inv[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    vector<int> n(T), m(T), k(T);
    int mx = 0;
    for (int i = 0; i < T; ++i) {
        cin >> n[i] >> m[i] >> k[i];
        mx = max(mx, k[i] + m[i]);
    }

    vector<long long> f, inv;
    prep(mx, f, inv);

    for (int t = 0; t < T; ++t) {
        int N = n[t], M = m[t], K = k[t];
        if (1LL * M * (N - 1) < K) {
            cout << 0 << '\n';
            continue;
        }
        long long ans = 0;
        int J = min(M, K / N);
        for (int j = 0; j <= J; ++j) {
            long long w1 = C(M, j, f, inv);
            long long w2 = C(K - j * N + M - 1, M - 1, f, inv);
            long long cur = w1 * w2 % MOD;
            if (j & 1) ans = (ans - cur + MOD) % MOD;
            else ans = (ans + cur) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

:::

#### Đánh giá

Độ phức tạp của thuật toán trên là $\mathcal{O}(n)$, do chỉ cần tiền xử lý giai thừa và nghịch đảo modulo của giai thừa.

### [Codeforces Round 519 - Make It One](https://codeforces.com/contest/1043/problem/F)

Cho dãy $n$ số nguyên dương $a_1,a_2,...,a_n$. Tìm một dãy con (không nhất thiết liên tiếp) gồm ít phần tử nhất sao cho ước chung lớn nhất của dãy này có giá trị là $1$. Nếu không tồn tại thì in ra $-1$.

Giới hạn:
- $1 \leq n \leq 3 \cdot 10^5$.
- $1 \leq a_i \leq 3 \cdot 10^5$.

#### Phân tích

Đầu tiên ta có nhận xét rằng **số phần tử cần chọn không vượt quá $7$**.

:::spoiler *Chứng minh*
Tương tự ví dụ ở phần trước, ta xét $7$ số nguyên tố nhỏ nhất:

$$
2 \cdot 3 \cdot 5 \cdot 7 \cdot 11 \cdot 13 \cdot 17 > 3 \cdot 10^5
$$

Trong khi đó $a_i \leq 3 \cdot 10^5$, ta thấy rằng không thể tồn tại một số nguyên không quá $3 \cdot 10^5$ có nhiều hơn $6$ số nguyên tố phân biệt.

Như vậy, nếu tồn tại đáp án, ta chỉ cần chọn một phần tử rồi chọn thêm tối đa $6$ phần tử khác để "loại bỏ" $6$ ước nguyên tố của phần tử đầu tiên ra khỏi ước chung lớn nhất.
:::

Từ đó, ta định nghĩa:

- $\texttt{dp}[i][j]$ là số cách chọn dãy con gồm $i$ phần tử sao cho ước chung lớn nhất của chúng có giá trị là $j$.
- $\texttt{cnt}[j]$ là số phần tử $a_i$ sao cho $j$ | $a_i$

Chúng ta có thể áp dụng **Nguyên lý Bao Hàm - Loại trừ** để chuyển trạng thái quy hoạch động. Số cách chọn dãy con gồm $i$ phần tử mà cả $i$ phần tử **đều chia hết** cho $j$ là:

$$
\binom{\texttt{cnt}_j}{i}
$$

Ta thấy rằng khi các phần tử của một dãy đều chia hết cho $j$, ước chung lớn nhất của chúng cũng phải chia hết cho $j$. Nói cách khác, các dãy trong số $\binom{\texttt{cnt}_j}{i}$ dãy mà ta đang xét bao gồm các dãy có ước chung lớn nhất là $j$, $2j$, $3j$,... Để giữ lại các dãy có ước chung lớn nhất là đúng $j$, ta sử dụng bao hàm - loại trừ:

$$
\texttt{dp}[i][j] = \binom{\texttt{cnt}_j}{i} - \sum_{k \ge 2} \texttt{dp}[i][k \cdot j]
$$

Chỉ cần xét $k \cdot j \leq M$ với $M = \max(a_i)$. Cách duyệt này có độ phức tạp $\mathcal{O}(M \ln M)$ theo [chuỗi điều hòa](https://vi.wikipedia.org/wiki/Chu%E1%BB%97i_%C4%91i%E1%BB%81u_h%C3%B2a).

Cuối cùng, ta xét hai trường hợp cho đáp án của bài toán:

- Nếu $\texttt{dp}[i][1] = 0$ với mọi $i \leq 7$ thì kết quả là $-1$.
- Ngược lại, đáp án là $i$ nhỏ nhất sao cho $\texttt{dp}[i][1] > 0$

Độ phức tạp: $\mathcal{O}(n + M \ln M)$ với $M = \max(a_i)$.

:::spoiler *Cài đặt*
```cpp=
#include <bits/stdc++.h>
using namespace std;

static const int MAXA = 300000;
static const int MOD = 1000000007;

long long pw(long long a, long long e)
{
    long long r = 1;
    while (e)
    {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long C(int n, int k)
{
    if (n < k || k < 0) return 0;
    static long long fact[MAXA + 1], invfact[MAXA + 1];
    static bool built = false;
    if (!built)
    {
        fact[0] = 1;
        for (int i = 1; i <= MAXA; i++) fact[i] = fact[i - 1] * i % MOD;
        invfact[MAXA] = pw(fact[MAXA], MOD - 2);
        for (int i = MAXA; i > 0; i--) invfact[i - 1] = invfact[i] * i % MOD;
        built = true;
    }
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> freq(MAXA + 1, 0);
    for (int x : a) freq[x]++;

    vector<int> cnt(MAXA + 1, 0);
    for (int i = 1; i <= MAXA; i++)
        for (int j = i; j <= MAXA; j += i)
            cnt[i] += freq[j];

    static long long dp[8][MAXA + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= 7; i++)
    {
        for (int j = MAXA; j >= 1; j--)
        {
            long long val = C(cnt[j], i);
            for (int k = 2; k * j <= MAXA; k++)
                val = (val - dp[i][k * j] + MOD) % MOD;
            dp[i][j] = val;
        }
        if (dp[i][1] > 0)
        {
            cout << i;
            return 0;
        }
    }

    cout << -1;
    return 0;
}
```
:::


## Phụ lục

### Luyện tập thêm

- [SPOJ - Another Game With Numbers](http://www.spoj.com/problems/NGM2/)
- [SPOJ - Sky Code](https://www.spoj.com/problems/MSKYCODE/)
- [SPOJ - Square-free integers](https://www.spoj.com/problems/SQFREE/)
- [SPOJ - Almost Prime Numbers Again](https://www.spoj.com/problems/KPRIMESB/)
- [SPOJ - Find number of Pair of Friends](https://www.spoj.com/problems/IITKWPCH/)
- [SPOJ - Balanced Cow Subsets](https://www.spoj.com/problems/SUBSET/)
- [Educational Codeforces Round 20 - Coprime Subsequence](https://codeforces.com/contest/803/problem/F)
- [Educational Codeforces Round 45 - GCD Counting](https://codeforces.com/contest/990/problem/G)
- [Codeforces Round 534 - Professional Layer](https://codeforces.com/contest/1103/problem/D)
- [JOI 2018 - Snake Escaping](https://oj.uz/problem/view/JOI18_snake_escaping)
- [CSES - Counting Reorders](https://cses.fi/problemset/task/2421)
- [CSES - Counting Coprime Pairs](https://cses.fi/problemset/task/2417)

### Tham khảo

- [Mihnea Brebenl, Rameez Parwez, Inclusion-Exclusion Principle (USACO Guide)](https://usaco.guide/plat/PIE?lang=cpp)
- [Chunyang "Roundgod" Wang, [Tutorial] Inclusion-Exclusion Principle (Codeforces)](https://codeforces.com/blog/entry/64625)
