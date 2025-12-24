---
title: Quy hoạch động SOS - Phần 1
description: 
published: true
date: 2025-03-21T15:44:13.885Z
tags: 
editor: markdown
dateCreated: 2025-02-07T16:27:03.015Z
---

# DP Sum over Subsets (DP SoS), phần 1

**Người viết:**

- Phạm Công Minh -- THPT Chuyên Khoa học Tự nhiên, Đại học Quốc gia Hà Nội.
- Nguyễn Tấn Minh -- THPT Chuyên Lê Hồng Phong, TPHCM.

**Reviewer:**

- Trần Xuân Bách -- University of Chicago.
- Nguyễn Minh Hiển -- Đại học Công nghệ, Đại học Quốc gia Hà Nội.
- Đoàn Gia Huy -- THPT Chuyên Khoa học Tự nhiên, Đại học Quốc gia Hà Nội.
- Nguyễn Quang Minh -- Michigan State University.

Trước khi bắt đầu, các bạn độc giả cần nắm được cách biểu diễn tập hợp nhỏ bằng bitmask và kỹ thuật Quy hoạch động bitmask cơ bản được trình bày ở [bài viết này](https://wiki.vnoi.info/algo/dp/dp-bitmask).

Trong bài viết này, các kí hiệu của phép toán trên tập hợp sẽ được áp dụng cho cả ngôn ngữ bitmask.

## Giới thiệu

**Quy hoạch động Sum over Subsets (hay DP SoS)** là một dạng nâng cao của Quy hoạch động bitmask cho phép chúng ta xử lý các bài toán liên quan đến việc tính tổng tập con của từng tập con cần xét một cách nhanh chóng. Không chỉ dừng lại ở việc tính tổng, DP SoS còn có thể được biến đổi linh hoạt để xử lý nhiều bài toán khác nhau.

### Bài toán kinh điển

Trước tiên, chúng ta hãy nghiên cứu cách sử dụng DP SoS để giải quyết bài toán sau: Xét các tập $U$ là tập con của $\{0, 1, 2, \cdots, n-1\}$, với mỗi tập như vậy, ta gán cho nó một giá trị $a[U]$. Ta cần tính giá trị hàm $f$ cho mọi tập con $S$ của tập $\{0, 1, 2, \dots, n - 1\}$ theo công thức:

$$
f(S) = \sum_{T \subseteq S} a[T]
$$

### Các lời giải vét cạn

Đối với phương pháp vét cạn, chúng ta có thể duyệt từng tập $S$ rồi từng tập $T$ và kiểm tra xem $T$ có phải tập con của $S$ hay không, cách làm này tốn độ phức tạp $\mathcal{O}(2^n \cdot 2^n) = \mathcal{O}(4^n)$.

Ngoài ra, có thể tối ưu một chút bằng cách với mỗi tập $S$, ta chỉ duyệt đúng các tập $T$ là tập con của $S$ với [phương pháp duyệt tập con](https://cp-algorithms.com/algebra/all-submasks.html). Lúc này, mỗi bit trong bitmask có $3$ trạng thái: bit tắt ở tập cha, bit bật ở tập cha nhưng không được bật trong tập con, bit bật trong cả tập cha và tập con. Do đó, độ phức tạp thời gian là $\mathcal{O}(3^n)$.

:::spoiler Code tham khảo
```cpp=
fill(f, f + (1 << n), a[0]); // do phương pháp duyệt tập con bỏ qua tập rỗng
for (int mask = 0; mask < (1 << n); mask++) {
    for (int sub = mask; sub; sub = (sub - 1) & mask) f[mask] += a[sub];
}
```
:::

## Ý tưởng & Thuật toán

Một bitmask $T$ là sub-mask của $S$ khi và chỉ khi $S \mathrel{\&} T = T$ (với $\mathrel{\&}$ là kí hiệu của phép bitwise AND). Đối với ngôn ngữ tập hợp, nếu bitmask $T$ biểu diễn một tập con của tập mà bitmask $S$ biểu diễn, thì $T$ là sub-mask của $S$.

### Biểu diễn lại các trạng thái

#### Ý tưởng chính

Ý tưởng dễ nghĩ đến nhất khi tiếp cận bài toán đó là đặt $\texttt{dp}(S)$ là tổng giá trị các sub-mask của mask $S$ (với $S$ là một bitmask biểu diễn tập hợp), rồi tìm cách tính $\texttt{dp}(S)$ từ các giá trị $\texttt{dp}(T)$ (với $T \subseteq S$). Tuy nhiên, cách này không mấy khả quan do các giá trị được truy hồi có thể trùng lắp nhau.

Xét mask $\texttt{001011}$, dễ thấy, các sub-mask của mask này là **các mask chỉ có thể khác mask này tại bit thứ $0, 1, 3$** ---- những bit được bật của mask đang xét. Ta có thể gọi chung những mask như vậy bằng "pattern" $\texttt{00?0??}$.

Từ đó, ta có ý tưởng: Thay vì đặt trạng thái là một bitmask, ta có thể sử dụng pattern mà mỗi phần tử mang một trong ba giá trị $\texttt{0}$, $\texttt{1}$ hoặc $\texttt{?}$. Khi xét một pattern, các giá trị $\texttt{0}$ hoặc $\texttt{1}$ cho biết bit tương ứng của mask được cố định theo giá trị đó, còn dấu $\texttt{?}$ cho biết bit tương ứng mang trạng thái bật/tắt tùy ý.

Khi đó, $\texttt{dp}(P)$ là tổng giá trị các mask thỏa pattern $P$. Ví dụ (các vị trí được tô màu đỏ là các vị trí không được cố định):

$$
\texttt{dp}(\texttt{0}{{\color{red}{\texttt{?}}}}\texttt{10}{{\color{red}{\texttt{?}}}}\texttt{1}) =
a[\texttt{0}{{\color{red}{\texttt{0}}}}\texttt{10}{{\color{red}{\texttt{0}}}}\texttt{1}] +
a[\texttt{0}{{\color{red}{\texttt{0}}}}\texttt{10}{{\color{red}{\texttt{1}}}}\texttt{1}] +
a[\texttt{0}{{\color{red}{\texttt{1}}}}\texttt{10}{{\color{red}{\texttt{0}}}}\texttt{1}] +
a[\texttt{0}{{\color{red}{\texttt{1}}}}\texttt{10}{{\color{red}{\texttt{1}}}\texttt{1}}]
$$

Để tính $\texttt{dp}(P)$, ta tìm một dấu $\texttt{?}$ bất kì trong $P$ rồi truy hồi về hai trạng thái tương ứng được thay dấu $\texttt{?}$ đó bằng $\texttt{0}$ và $\texttt{1}$. Ví dụ:

$$
\texttt{dp}(\texttt{0}{{\color{red}{\texttt{?}}}\texttt{10?1}}) =
\texttt{dp}(\texttt{0}{{\color{red}{\texttt{0}}}}\texttt{10?1}) +
\texttt{dp}(\texttt{0}{{\color{red}{\texttt{1}}}\texttt{10?1}})
$$

:::spoiler Lưu ý
Điểm mạnh của cách làm này là không có mask nào thỏa cả hai pattern $\texttt{0}{\color{red}{\texttt{0}}}\texttt{10?1}$ và $\texttt{0}{\color{red}{\texttt{1}}}\texttt{10?1}$ nên ta hoàn toàn có thể cộng hai giá trị mà không sợ bị tính trùng.
:::

#### Cải tiến ý tưởng

Tuy nhiên, cách làm này vẫn còn 2 điểm yếu lớn:
- Độ phức tạp của chúng ta vẫn là $\mathcal{O}(3^n)$, thậm chí hằng số còn lớn hơn cách duyệt trâu.
- Việc biểu diễn các pattern dưới dạng biểu diễn tam phân rất rắc rối.

Để khắc phục điều này, khi truy hồi thay vì chọn dấu $\texttt{?}$ bất kì, ta quy ước chọn dấu $\texttt{?}$ bên trái nhất (chỉ số cao nhất). Khi đó, ta chỉ cần xét các pattern mà các giá trị $\texttt{1}$ và $\texttt{?}$ nằm ở hai bên của pattern.

![mask example recolored](/algo/dp_/sos/dpsos1.png)

:::info
Ta lưu thêm một biến $k$ cho biết vị trí tách phần chứa $\texttt{1}$ và phần chứa $\texttt{?}$ (giá trị $\texttt{0}$ xuất hiện trong cả hai phần). Lúc này, để biểu diễn một pattern, ta chỉ cần một cặp bitmask và số nguyên $(\texttt{mask}, k)$:

- Các bit tắt của $\texttt{mask}$ biểu diễn các giá trị $\texttt{0}$ của pattern.
- Các bit bật của $\texttt{mask}$ trước vị trí $k$ biểu diễn các giá trị $\texttt{?}$ của pattern.
- Các bit bật của $\texttt{mask}$ sau hoặc tại vị trí $k$ biểu diễn các giá trị $\texttt{1}$ của pattern.
:::

Như vậy, ta đã giải quyết được cả vấn đề về độ phức tạp và việc biểu diễn các pattern.

### Xây dựng hàm Quy hoạch động

Bây giờ, hàm Quy hoạch động của chúng ta là $\texttt{dp}(\texttt{mask}, k)$ tính tổng giá trị của các mask thỏa pattern $(\texttt{mask}, k)$ theo cách đặt trạng thái như trên. Trường hợp cơ sở là $\texttt{dp}(\texttt{mask}, 0) = a[\texttt{mask}]$ (pattern không có dấu $\texttt{?}$).

Với mỗi trạng thái $k > 0$, ta tìm dấu $\texttt{?}$ bên trái nhất để truy hồi. Cụ thể:

- Nếu giá trị thứ $k-1$ trong pattern là $\texttt{?}$, tức bit thứ $k-1$ của $\texttt{mask}$ bật, đây sẽ là dấu $\texttt{?}$ cần tìm nên ta thực hiện truy hồi theo công thức:

$$
\texttt{dp}(\texttt{mask}, k) = \texttt{dp}(\texttt{mask} \setminus \{k-1\}, k - 1) + \texttt{dp}(\texttt{mask}, k - 1)
$$

- Nếu giá trị thứ $k-1$ trong pattern là $\texttt{0}$, tức bit thứ $k - 1$ của $\texttt{mask}$ tắt, ta sẽ tìm tiếp dấu $\texttt{?}$ ở trạng thái $(\texttt{mask}, k - 1)$:

$$
\texttt{dp}(\texttt{mask}, k) = \texttt{dp}(\texttt{mask}, k - 1)
$$

Cuối cùng, ta có $f(\texttt{mask}) = \texttt{dp}(\texttt{mask}, n)$ (pattern chỉ có dấu $\texttt{?}$ và giá trị $\texttt{0}$).

:::info
Như vậy, ta có công thứ truy hồi hoàn chỉnh là:

$$
\texttt{dp}(\texttt{mask}, k) =
\begin{cases}
a[\texttt{mask}] & k = 0 \\
\texttt{dp}(\texttt{mask} \setminus \{k-1\}, k - 1) + \texttt{dp}(\texttt{mask}, k - 1) & k > 0, k - 1 \in \texttt{mask} \\
\texttt{dp}(\texttt{mask}, k - 1) & k > 0, k - 1 \notin \texttt{mask}
\end{cases}
$$
:::

Sau đây là cây biểu diễn các trạng thái mà ta sẽ gọi khi tính $f(\texttt{1011})$:

![sos tree recolored](/algo/dp_/sos/dpsos2.png)

Lưu ý, khi vẽ hết các trạng thái của Quy hoạch động ra, đồ thị không còn là cây nữa mà là một đồ thị có hướng không chu trình (DAG).

:::success
Có tổng cộng là $2^n \cdot (n + 1)$ trạng thái Quy hoạch động, mỗi trạng thái được truy hồi trong $\mathcal{O}(1)$. Như vậy, ta đã có thuật toán Quy hoạch động Sum over Subsets có độ phức tạp:

- **Thời gian:** $\mathcal{O}(2^n \cdot n)$.
- **Bộ nhớ:** $\mathcal{O}(2^n)$ hoặc $\mathcal{O}(2^n \cdot n)$ tùy cách cài đặt.
:::

### Cài đặt

Với công thức truy hồi như trên, khi cài đặt, việc duyệt theo biến $\texttt{mask}$ hay $k$ trước đều đúng. Tuy nhiên, mỗi cách làm có ưu/nhược điểm riêng nên ta sẽ tìm hiểu cả hai.

#### Cách 1

Ta sẽ duyệt theo biến $\texttt{mask}$ trước:

```cpp=
for (int mask = 0; mask < (1 << n); mask++) {
    dp[mask][0] = a[mask]; // trường hợp cơ sở
    for (int k = 1; k <= n; k++) {
        if (mask & (1 << (k - 1)))
            dp[mask][k] = dp[mask ^ (1 << (k - 1))][k - 1] + dp[mask][k - 1];
        else dp[mask][k] = dp[mask][k - 1];
    }
    f[mask] = dp[mask][n];
}
```

Ưu điểm của cách cài đặt này là khi bắt đầu tính cho một $\texttt{mask}$ bất kì, ta đã có kết quả của mọi trạng thái liên quan đến sub-masks của $\texttt{mask}$, do đó, cách này còn được gọi là "online" DP SoS. Điều này vô cùng hữu ích đối với những bài DP SoS có công thức tự gọi lại chính nó.

Tuy nhiên, cách làm này không thể tối ưu bộ nhớ xuống $\mathcal{O}(2^n)$ được.

#### Cách 2

Ta sẽ duyệt theo biến $k$ trước:

```cpp=
for (int mask = 0; mask < (1 << n); mask++) dp[mask][0] = a[mask]; // trường hợp cơ sở
for (int k = 1; k <= n; k++) {
    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask & (1 << (k - 1)))
            dp[mask][k] = dp[mask ^ (1 << (k - 1))][k - 1] + dp[mask][k - 1];
        else dp[mask][k] = dp[mask][k - 1];
    }
}
for (int mask = 0; mask < (1 << n); mask++) f[mask] = dp[mask][n];
```

Với cách này, tất cả các giá trị $f(\texttt{mask})$ sẽ được đồng loạt tính xong ở vòng cuối (khi $k = n$). Do đó, giả sử trong quá trình tính $f(\texttt{mask})$, ta cần biết $f(\texttt{submask})$ thì cách làm này không phù hợp.

Bù lại, từ cách cài đặt này, ta có thể tối ưu bộ nhớ xuống $\mathcal{O}(2^n)$ và rút gọn được phần cài đặt xuống rất ngắn. Do đó, nhìn chung, cách làm này phổ biến hơn cách 1.

#### Tối ưu bộ nhớ

Ở cách 2, có thể thấy rằng khi duyệt đến $k = \texttt{cur}$, ta chỉ cần duy trì các giá trị $\texttt{dp}(\texttt{mask}, \texttt{cur} - 1)$. Từ đó, ta có thể đưa biến $k$ lên trước trong cách đặt trạng thái và chỉ duy trì $2$ dòng của bảng Quy hoạch động, hay thậm chí là $1$ dòng nếu ta duyệt các mask từ lớn đến nhỏ (ý tưởng tương tự DP Knapsack).

```cpp=
for (int k = 1; k <= n; k++)
    for (int mask = (1 << n) - 1; mask >= 0; mask--)
        if (mask & (1 << (k - 1))) dp[mask] += dp[mask ^ (1 << (k - 1))];
```

Để cài đặt ngắn gọn hơn nữa, ta còn có thể đưa ra nhận xét rằng đối với DP SoS, việc duyệt các mask từ nhỏ đến lớn cũng không làm sai kết quả. Hơn nữa, vì không còn cần phải đánh số dòng trên bảng QHĐ, ta có thể duyệt $k$ từ $0$ đến $n - 1$ và coi trường hợp cơ sở là $k = -1$, sẽ thuật tiện hơn cho việc xử lý bitmask. Đến đây, ta đã có code DP SoS rất ngắn, dễ cài đặt, tối ưu bộ nhớ và hằng số thấp:

```cpp=
for (int k = 0; k < n; k++)
    for (int mask = 0; mask < (1 << n); mask++)
        if (mask & (1 << k)) dp[mask] += dp[mask ^ (1 << k)];
```

:::spoiler Tại sao có thể duyệt các mask từ nhỏ đến lớn?
Khi duyệt các mask từ nhỏ đến lớn, ta sẽ vô tình truy hồi về giá trị đã được cập nhật sang dòng mới, từ đó, công thức Quy hoạch động của chúng ta sẽ bị "sai" đi một chút:

$$
\texttt{dp}(\texttt{mask}, k) =
\begin{cases}
a[\texttt{mask}] & k = 0 \\
\texttt{dp}(\texttt{mask} \setminus \{k-1\}, k) + \texttt{dp}(\texttt{mask}, k - 1) & k > 0, k - 1 \in \texttt{mask} \\
\texttt{dp}(\texttt{mask}, k - 1) & k > 0, k - 1 \notin \texttt{mask}
\end{cases}
$$

Điểm khác biệt là ở trường hợp thứ hai, ta truy hồi về $\texttt{dp}(\texttt{mask} \setminus \{k-1\}, k)$ thay vì $\texttt{dp}(\texttt{mask} \setminus \{k-1\}, k - 1)$. Tuy nhiên, để ý rằng vì $k-1 \notin (\texttt{mask} \setminus \{k-1\})$ nên theo công thức truy hồi:

$$
\texttt{dp}(\texttt{mask} \setminus \{k-1\}, k) = \texttt{dp}(\texttt{mask} \setminus \{k-1\}, k - 1)
$$
:::

## Các biến thể của DP SoS

### Bài toán ngược

Cho trước các giá trị của hàm $f(S)$. Khôi phục mảng $a$ ban đầu, nói cách khác, tìm mảng $a$ gồm $2^n$ phần tử sao cho $f(S) = \sum_{T \subseteq S} a[T]$.

#### Công thức truy hồi

Bằng cách đổi vế công thức truy hồi của DP SoS, ta có công thức truy hồi để xử lý bài toán ngược như sau:

$$
\texttt{dp}(\texttt{mask}, k) =
\begin{cases}
f(\texttt{mask}) & k = n \\
\texttt{dp}(\texttt{mask}, k + 1) - \texttt{dp}(\texttt{mask} \setminus \{k\}, k) & k < n, k \in \texttt{mask} \\
\texttt{dp}(\texttt{mask}, k + 1) & k < n, k \notin \texttt{mask} \\
\end{cases}
$$

Đáp án bây giờ là $\texttt{dp}(\texttt{mask}, 0)$.

:::spoiler Code tham khảo
```cpp=
for (int mask = 0; mask < (1 << n); mask++) {
    for (int k = n - 1; k >= 0; k--) {
        if (mask & (1 << k))
            dp[mask][k] = dp[mask][k + 1] - dp[mask ^ (1 << k)][k];
        else dp[mask][k] = dp[mask][k + 1];
    }
}
```
:::

#### Tối ưu bộ nhớ

Tương tự bài toán gốc, ta cũng có thể tối ưu bộ nhớ.

:::spoiler Code tham khảo
```cpp=
for (int k = n - 1; k >= 0; k--)
    for (int mask = 0; mask < (1 << n); mask++)
        if (mask & (1 << k)) sos[mask] -= sos[mask ^ (1 << k)];
```
:::

### Bao hàm loại trừ: Mobius Transform

#### Bài toán kinh điển

Cho $n$ đối tượng $a_0, a_1, \dots, a_{n-1}$, giả sử rằng với mọi tập con của $n$ đối tượng này, ta có thể tính kích thước của **giao của các đối tượng thuộc tập con**, gọi là $\texttt{intersect}[T]$. Sử dụng [bao hàm loại trừ](https://wiki.vnoi.info/vi/translate/he/Number-Theory-7), ta có thể tính kích thước của hợp của $n$ đối tượng này bằng công thức:

$$
\sum \texttt{intersect}[T] \cdot (-1)^{|T| + 1}
$$

Giả sử với mọi tập con của $n$ đối tượng này, ta cần tính kích thước của **hợp của các đối tượng thuộc tập con**, gọi là $\texttt{union}[S]$. Một lần nữa, áp dụng bao hàm loại trừ, ta có:

$$
\texttt{union}[S] = \sum_{T \subseteq S} \texttt{intersect}[T] \cdot (-1)^{|T| + 1}
$$

Ta có thể áp dụng DP SoS để tính mọi giá trị $\texttt{union}[S]$ trong $\mathcal{O}(2^n \cdot n)$.

:::spoiler Code tham khảo
```cpp=
for (int mask = 0; mask < (1 << n); mask++)
    sos[mask] = intersect[mask] * (__builtin_parity(mask) ? 1 : -1);

for (int k = 0; k < n; k++)
    for (int mask = 0; mask < (1 << n); mask++)
        if (mask & (1 << k)) sos[mask] += sos[mask ^ (1 << k)];
```

Ở cuối chương trình, mảng `sos` chứa các giá trị của mảng $\texttt{union}[]$.
:::

#### Biển thể

Ngoài ra, ta có thể sử dụng bao hàm loại trừ để xử lý bài toán DP SoS ngược nêu trên. Trước tiên, khi xét $2$ bit:

$$
a[\texttt{11}] = f(\texttt{11}) - f(\texttt{10}) - f(\texttt{01}) + f(\texttt{00})
$$

Với $3$ bit, ta có:

$$
a[\texttt{111}] = f(\texttt{111}) - f(\texttt{110}) - f(\texttt{101}) - f(\texttt{011}) + f(\texttt{001}) + f(\texttt{010}) + f(\texttt{100}) - f(\texttt{000})
$$

Sử dụng Bao hàm loại trừ, ta có công thức tổng quát:

$$
a[S] = \sum_{T \subseteq S} f(T) \cdot (-1)^{|T| + |S|}
$$

:::spoiler Chứng minh
Để chứng minh công thức trên, ta tính đóng góp của từng giá trị của sub-mask $a[T]$ (với $T \subseteq S$) vào tổng.

Với $T = S$, ta thấy $a[S]$ đóng góp đúng một lần vào tổng vì được tính trong $f(S)$. Hơn nữa, $(-1)^{|S| + |S|} = 1$ nên dấu của $a[S]$ luôn là dương.

Với $T \subset S$, ta thấy đóng góp của $a[T]$ sẽ phụ thuộc vào các $f(Z)$ thỏa $T \subseteq Z \subseteq S$, hay $(Z \setminus T) \subseteq (S \setminus T)$. Cụ thể, đóng góp của $a[T]$ vào tổng là:

$$
\sum_{Z \subseteq (S \setminus T)} a[T] \cdot (-1)^{|Z| + |T| + |S|}
$$

Do ta chỉ quan tâm kích thước của $Z$ nên ta đặt $k = |Z|$ và biến đổi công thức thành:

$$
\sum_{0 \leq k \leq |S| - |T|} a[T] \cdot \binom{|S| - |T|}{k} \cdot (-1)^{k + |T| + |S|}
$$

Đem nhân tử chung $a[T] \cdot (-1)^{|T| + |S|}$ ra ngoài và đặt phần còn lại là $\delta$, ta sử dụng [Nhị thức Newtown](https://en.wikipedia.org/wiki/Binomial_theorem) để biến đổi:

$$
\begin{align*}
\delta &= \sum_{0 \leq k \leq |S| - |T|} \binom{|S| - |T|}{k} \cdot (-1)^k \cdot \underbrace{(1)^{|S| - |T| - k}}_\text{optional} \\
&= (-1 + 1)^{|S| - |T|} \\
&= 0
\end{align*}
$$

Như vậy, đóng góp của mọi giá trị $a[T]$ với $T \subset S$ là $0$.
:::

Đến đây, ta còn phải biến đổi công thức một chút để có thể áp dụng Mobius Transform, cụ thể như sau:

$$
a[S] = \sum_{T \subseteq S} f(T) \cdot (-1)^{|T| + |S|} = \left( \sum_{T \subseteq S} f(T) \cdot (-1)^{|T|} \right) \cdot (-1)^{|S|}
$$

Sau khi biến đổi, từng số hạng trong tổng đã độc lập theo $S, T$, do đó, ta có thể áp dụng DP SoS để tính nhanh $\sum_{T \subseteq S} f(T) \cdot (-1)^{|T|}$ rồi nhân thêm $(-1)^{|S|}$ để được $a[S]$ trong $\mathcal{O}(2^n \cdot n)$.

:::spoiler Code tham khảo
```cpp=
for (int mask = 0; mask < (1 << n); mask++)
    sos[mask] = f[mask] * (__builtin_parity(mask) ? -1 : 1);

for (int k = 0; k < n; k++)
    for (int mask = 0; mask < (1 << n); mask++)
        if (mask & (1 << k)) sos[mask] += sos[mask ^ (1 << k)];

for (int mask = 0; mask < (1 << n); mask++)
    a[mask] = sos[mask] * (__builtin_parity(mask) ? -1 : 1);
```
:::

### Sum over Proper Subsets

Xét bài toán kinh điển của DP SoS, nhưng công thức đổi lại thành:

$$
f(S) = \sum_{T \subset S} a[T]
$$

tức là ta không xét $S$ là tập con của chính nó nữa.

Thông thường, ta có thể giải bài toán Sum over Subsets như bình thường, sau đó trừ đi $a[S]$. Tuy nhiên, đối với một số bài toán, ta cần phải tính toán $f(S)$ khi chưa biết $a[S]$. Khi đó, ta cần xây dựng một công thức Quy hoạch động không dùng đến $a[S]$.

Để làm được điều đó, ta thêm ràng buộc pattern không tính mask được tạo thành bằng cách thay mọi dấu $\texttt{?}$ của nó thành bit bật. Lúc này, công thức truy hồi sẽ được chỉnh sửa thành:

$$
\texttt{dp}(\texttt{mask}, k) =
\begin{cases}
0 & k = 0 \\
\texttt{dp}(\texttt{mask}, k - 1) + \texttt{dp}(\texttt{sub}, k - 1) + a[\texttt{sub}] & k > 0, k - 1 \in \texttt{mask} \\
\texttt{dp}(\texttt{mask}, k - 1) & k > 0, k - 1 \notin \texttt{mask}
\end{cases}
$$

với $\texttt{sub} = \texttt{mask} \setminus \{k - 1\}$.

### Sum over subsets, truy hồi chính nó

Nâng cấp bài toán kinh điển của DP SoS thêm một chút, lúc này, hàm $f$ sẽ tự truy hồi chính nó:

$$
f(S) = h \left( \sum_{T \subset S} f(T) \right) + a[S]
$$

với $h$ là một hàm ánh xạ bất kì.

Ý tưởng chính để giải quyết dạng bài này là ta sẽ duy trì song song giá trị của $f(S)$ và $\texttt{dp}(\texttt{mask}, k)$. Lúc này, ta quay trở lại với cách cài đặt thứ nhất của DP SoS kết hợp với biến thể Sum over Proper Subsets được trình bày ở trên. Điều này giúp ta có thể biết trước mọi giá trị $f(T)$ trước khi bắt đầu tính $f(S)$ (với $T \subset S$).

:::spoiler Code tham khảo
```cpp=
for (int mask = 0; mask < (1 << n); mask++) {
    dp[mask][0] = 0; // trường hợp cơ sở
    for (int k = 1; k <= n; k++) {
        // tính dp
        if (mask & (1 << (k - 1))) {
            int sub = mask ^ (1 << (k - 1));
            dp[mask][k] = dp[mask][k - 1] + dp[sub][k - 1] + f[sub];
        }
        else dp[mask][k] = dp[mask][k - 1];
    }
    f[mask] = h(dp[mask][n]) + a[mask]; // tính f
}
```
:::

### Sum over subsets, hai hàm gọi chéo nhau

Nâng cấp bài tập ở trên thêm một chút nữa, ta cần tính hai hàm $f, g$ có định nghĩa như sau:

$$
\begin{align*}
f(S) &= h_1 \left( \sum_{T \subset S} g(T) \right) + a[S] \\
g(S) &= h_2 \left( \sum_{T \subseteq S} f(T) \right) + b[S] \\
\end{align*}
$$

với hàm $h_1, h_2$ là hai hàm ánh xạ tương tự bài toán ở trên.

Lúc này, ta sẽ duy trì đồng thời $4$ giá trị:
- Hai hàm $f, g$.
- Quy hoạch động trên hàm $f$ là $\texttt{dp}_f(\texttt{mask}, k)$ (theo kiểu sum over subset).
- Quy hoạch động trên hàm $g$ là $\texttt{dp}_g(\texttt{mask}, k)$ (theo kiểu sum over proper subset).

Để tính các giá trị này, ta kết hợp các ý tưởng đã sử dụng ở các phần trên.

:::spoiler Code tham khảo
```cpp=
for (int mask = 0; mask < (1 << n); mask++) {
    // tính dpG và f
    for (int k = 1; k <= n; k++) {
        if (mask & (1 << (k - 1))) { // truy hồi theo kiểu proper subset
            int sub = mask ^ (1 << (k - 1));
            dpG[mask][k] = dpG[mask][k - 1] + dpG[sub][k - 1] + g[sub];
        }
        else dpG[mask][k] = dpG[mask][k - 1];
    }
    f[mask] = h1(dpG[mask][n]) + a[mask];
    
    // tính dpF và g
    dpF[mask][0] = f[mask];
    for (int k = 1; k <= n; k++) {
        if (mask & (1 << (k - 1))) // truy hồi theo kiểu subset
            dpF[mask][k] = dpF[mask][k - 1] + dpF[mask ^ (1 << (k - 1))][k - 1];
        else dpF[mask][k] = dpF[mask][k - 1];
    }
    g[mask] = h2(dpF[mask][n]) + b[mask];
}
```
:::

## Bài tập ứng dụng

*Bạn đọc nên tự thử sức trước với các bài tập dưới đây trước khi bước vào phần phân tích ý tưởng và cài đặt nhé.*

Trong phần này, ta quy ước $\mid$, $\mathrel{\&}$ và $\oplus$ lần lượt là ký hiệu của phép [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR), [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) và [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

### CSES - Bit Problem

[Link đề gốc](https://cses.fi/problemset/task/1654)

Cho một danh sách $n$ số nguyên, với mọi số trong danh sách, gọi là $x$, hãy tính:

1. Số phần tử $y$ thuộc danh sách sao cho $x \mid y = x$.
2. Số phần tử $y$ thuộc danh sách sao cho $x \mathrel{\&} y = x$.
3. Số phần tử $y$ thuộc danh sách sao cho $x \mathrel{\&} y \neq 0$.

#### Giới hạn

- $1 \leq n \leq 2 \cdot 10^5$.
- $1 \leq x_i \leq 10^6$.

#### Ý tưởng

Nếu biến đổi thành ngôn ngữ bitmask thuần túy, các yêu cầu lần lượt là: đếm số mask là sub-mask của $x$; đếm số mask là super-mask của $x$; và đếm số mask có ít nhất một bit bật chung với $x$.

Đối với yêu cầu 1, ta dựng mảng thống kê rồi thực hiện DP SoS căn bản trên mảng thống kê này. Tương tự với yêu cầu loại 2, ta cũng thực hiện DP SoS với định nghĩa DP thay đổi một chút: các bit bật của $\texttt{mask}$ biểu diễn giá trị $\texttt{1}$ của pattern, các bit tắt biểu diễn giá trị $\texttt{0}$ hoặc $\texttt{?}$ tùy theo $k$. Việc xây dựng công thức truy hồi cũng được thực hiện tương tự.

Đối với yêu cầu cuối cùng, ta sẽ đếm số mask không có bit bật chung với $x$ rồi thực hiện bù trừ. Phân tích một chút, khi xét một bitmask $x$, để $y$ không có bit bật chung với $x$ thì:

- Nếu bit thứ $i$ của $x$ được bật, bit tương ứng của $y$ bắt buộc phải tắt.
- Ngược lại, bit tương ứng của $y$ là gì cũng được.

Đến đây, ta có thể thấy rằng $y$ là sub-mask của $x$ sau khi đã lật hết tất cả các bit của $x$.

Nói tóm lại, chúng ta cần tính hai giá trị sau:

- $\texttt{sosSub}(x)$ là số phần tử trong dãy là sub-mask của $x$.
- $\texttt{sosSup}(x)$ là số phần tử trong dãy là super-mask của $x$.

#### Độ phức tạp

- Độ phức tạp thời gian: $\mathcal{O}(n + x \log x)$ với $x = \max x_i$.
- Độ phức tạp bộ nhớ: $\mathcal{O}(n + x)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const int full = (1 << 20) - 1;
int a[1 << 20], sosSub[1 << 20], sosSup[1 << 20];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sosSub[a[i]]++, sosSup[a[i]]++;
    }

    for (int k = 0; k < 20; k++) {
        for (int mask = 0; mask < (1 << 20); mask++) {
            if (mask & (1 << k)) sosSub[mask] += sosSub[mask ^ (1 << k)];
            else sosSup[mask] += sosSup[mask ^ (1 << k)];
        }
    }

    for (int i = 0; i < n; i++)
        cout << sosSub[a[i]] << " " << sosSup[a[i]] << " " << n - sosSub[a[i] ^ full] << "\n";

    return 0;
}
```
:::

### Codeforces 1208F - Bits and Pieces

[Link đề gốc](https://codeforces.com/contest/1208/problem/F)

Cho dãy $a$ gồm $n$ phần tử, hãy tính:

$$
\max_{1 \leq i < j < k \leq n} a_i \mid (a_j \mathrel{\&} a_k)
$$

#### Giới hạn

- $3 \leq n \leq 10^6$.
- $0 \leq a_i \leq 2 \cdot 10^6$.

#### Ý tưởng

Nhận xét quan trọng ta cần đưa ra ở bài toán này là: Nếu tồn tại một phương án là super-mask của $U$ thì cũng tồn tại một phương án là super-mask của $V$ (với $V \subseteq U$). Đến đây, ta sẽ nghĩ đến thuật toán tìm kiếm nhị phân trên bit.

Bên cạnh việc sử dụng trong các bài toán tìm kiếm nhị phân truyền thống để đạt hằng số thấp, thuật toán tìm kiếm nhị phân trên bit còn có thể giải quyết bài toán tìm $x \in R$ lớn nhất sao cho $f(x) = 1$ với $R$ là khoảng tìm kiếm và $f(x)$ là một hàm thỏa:
- Với mọi $x \in R$, ta có $f(x) \in \{0, 1\}$.
- Nếu $f(x) = 1$ thì $f(x') = 1$ với $x' \subseteq x$.

Thuật toán này dựa trên ý tưởng tham lam tương tự thuật toán [Walk on Trie](https://wiki.vnoi.info/vi/algo/string/trie#xử-lí-truy-vấn-tìm-xor-lớn-nhất-với-giá-trị-được-cho) đó là thử bật các bit của đáp án theo thứ tự từ lớn đến bé. Ta có thể đưa ra nhận xét là việc bật bit thứ $i$ và tắt các bit từ $0$ đến $i - 1$ vẫn cho ra kết quả lớn hơn việc tắt bit thứ $i$ và bật tất cả các bit từ $0$ đến $i - 1$. Nói cách khác:

$$
2^i > \sum_{0 \leq j < i} 2^j
$$

Nhìn chung, các thuật toán tìm kiếm nhị phân trên bit có mô hình cài đặt như sau:

```cpp!
int ans = 0;
for (int mask = (1 << B); mask; mask >>= 1) {
    if (f(ans | mask)) ans |= mask;
}
```

Nhiệm vụ còn lại là thiết kế một hàm $\texttt{check}(S)$ để kiểm tra xem liệu có tồn tại một phương án là super-mask của $U$. Để làm điều này, ta cố định trước giá trị $i$ và tìm những bit chưa được bật ở $a_i$ nhưng lại được bật ở $U$ (những bit còn thiếu), gọi là bitmask $M$. Sau đó, ta tìm một cặp $(j, k)$ sao cho $i < j < k$ và $a_j \mathrel{\&} a_k$ là super-mask của $M$.

Dễ thấy, điều kiện duy nhất để $M \subseteq (a_j \mathrel{\&} a_k)$ là cả $a_j$ và $a_k$ phải là super-mask của $M$. Từ đây, ta có thể tham lam chọn hai chỉ số $j, k$ là lớn nhất và lớn nhì sao cho $a_j$ và $a_k$ đều là super-mask của $M$. Ta có thể sử dùng DP SoS để tính trước $\texttt{best}[S]$ là hai chỉ số lớn nhất sao cho phần tử tương ứng là super-mask của $S$, sau đó tìm $(j, k)$ trong $\mathcal{O}(1)$. Lưu ý, nếu $i \geq \min(j, k)$ thì ta coi như không tìm được cặp $(j, k)$ thỏa mãn.

#### Độ phức tạp

- Độ phức tạp thời gian: $\mathcal{O}((n + a) \log a)$ với $a = \max a_i$.
- Độ phức tạp bộ nhớ: $\mathcal{O}(n + a)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

struct helper {
    int best, secBest;
    helper() : best(0), secBest(0) {}

    void push (int cur) {
        if (cur > best) secBest = best, best = cur;
        else secBest = max(secBest, cur);
    }

    void push (const helper &o) {
        if (best >= o.best) secBest = max(secBest, o.best);
        else secBest = max(best, o.secBest), best = o.best;
    }
} sos[1 << 21];
int a[1 << 20], n;

bool ok (int mask) {
    for (int i = 1; i <= n - 2; i++) {
        int miss = mask ^ (mask & a[i]);
        if (i < sos[miss].secBest) return 1;
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sos[a[i]].push(i);
    }

    for (int k = 0; k < 21; k++)
        for (int mask = 0; mask < (1 << 21); mask++)
            if (!(mask & (1 << k))) sos[mask].push(sos[mask ^ (1 << k)]);

    int ans = 0;
    for (int mask = 1 << 20; mask > 0; mask >>= 1)
        if (ok(ans | mask)) ans |= mask;
    cout << ans;

    return 0;
}
```
:::

### VOI 2021 - Phép toán OR

[Link đề gốc](https://oj.vnoi.info/problem/voi21_or)

Cho dãy $a$ gồm $n$ phần tử và ba số nguyên $k, L, R$. Đếm số dãy con (không nhất thiết phải liên tiếp) độ dài $k$ của $a$ thỏa mãn:

- Gọi $v$ là bitwise OR của các số trong dãy con thì $L \leq v \leq R$ và $3 \mid v$.

In ra đáp án modulo $10^9 + 7$.

#### Giới hạn

- $1 \leq k \leq n \leq 10^6$.
- $0 \leq L \leq R \leq 10^6$.

#### Ý tưởng

Thực chất thì để giải bài toán này, ta chỉ cần tính $\texttt{count}[S]$ là số dãy con độ dài $k$ sao cho bitwise OR của chúng là $S$. Sau đó, ta duyệt mọi bội của $3$ trong khoảng $[L; R]$ và tính tổng.

Ta định nghĩa $\texttt{sub}[S]$ là số dãy con độ dài $k$ sao cho bitwise OR của chúng là một sub-mask của $S$. Giá trị mảng $\texttt{sub}[]$ dễ tính hơn nhiều và ta cũng có thể khôi phục mảng $\texttt{count}[]$ từ $\texttt{sub}[]$ sử dụng DP SoS ngược hoặc bao hàm loại trừ.

Dễ thấy, để bitwise OR của một dãy là một sub-mask của $S$ thì mọi phần tử của dãy phải là sub-mask của $S$. Như vậy, gọi $f(S)$ là số phần tử là sub-mask của $S$, ta có thể dùng tổ hợp để tính $\texttt{sub}[]$:

$$
\texttt{sub}[S] =
\begin{cases}
0 & f(S) < k \\
C_{f(S)}^k & f(S) \geq k \\
\end{cases}
$$

Cuối cùng, ta thực hiện DP SoS ngược trên mảng $\texttt{sub}[]$ là đã có mảng $\texttt{count}[]$ trong $\mathcal{O}(a \log a + n)$.

#### Độ phức tạp

- Độ phức tạp thời gian: $\mathcal{O}(a \log a + n + R)$ với $a = \max a_i$.
- Độ phức tạp bộ nhớ: $\mathcal{O}(n + a)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int mn = 1e6 + 6;
int fact[mn], ifac[mn], sos[1 << 20];

int add (int a, int b) { return a + b - (a + b < MOD ? 0 : MOD); }
int sub (int a, int b) { return a - b + (a - b >= 0 ? 0 : MOD); }
int mul (int a, int b) { return 1LL * a * b % MOD; }

int binpow (int a, int b = MOD - 2) {
    int ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = mul(ans, a);
        a = mul(a, a);
    }
    return ans;
}

int C (int n, int k) {
    if (n < k) return 0;
    int ans = mul(fact[n], ifac[k]);
    return mul(ans, ifac[n - k]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // tiền xử lý của tổ hợp
    fact[0] = 1;
    for (int i = 1; i < mn; i++) fact[i] = mul(fact[i - 1], i);
    ifac[mn - 1] = binpow(fact[mn - 1]);
    for (int i = mn - 2; i >= 0; i--) ifac[i] = mul(ifac[i + 1], i + 1);

    // nhập dữ liệu
    int n, k, L, R; cin >> n >> k >> L >> R;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        sos[a]++;
    }

    // tính f bằng DP SoS truyền thống
    for (int k = 0; k < 20; k++)
        for (int mask = 0; mask < (1 << 20); mask++)
            if (mask & (1 << k)) sos[mask] += sos[mask ^ (1 << k)];

    // tính sub bằng tổ hợp
    for (int mask = 0; mask < (1 << 20); mask++) sos[mask] = C(sos[mask], k);

    // tính count bằng DP SoS ngược
    for (int k = 19; k >= 0; k--)
        for (int mask = 0; mask < (1 << 20); mask++)
            if (mask & (1 << k)) sos[mask] = sub(sos[mask], sos[mask ^ (1 << k)]);

    // lấy đáp án
    int ans = 0;
    for (int mask = 3 * (L / 3 + (L % 3 ? 1 : 0)); mask <= R; mask += 3) ans = add(ans, sos[mask]);
    cout << ans;

    return 0;
}
```
:::

### JOI 2018 - Snake Escaping

[Link đề gốc](https://oj.uz/problem/view/JOI18_snake_escaping)

Cho dãy $a$ gồm $2^L$ số nguyên tương ứng giá trị của tập con của $\{0, 1, \dots, L - 1\}$ và $Q$ truy vấn. Với mỗi truy vấn, cho xâu độ dài $L$ là pattern gồm một trong ba ký tự $\texttt{0}, \texttt{1}, \texttt{?}$, tính tổng giá trị tương ứng của các tập thỏa pattern được cho.

#### Giới hạn

- $1 \leq L \leq 20$.
- $1 \leq Q \leq 10^6$.
- $0 \leq a_i \leq 9$.

#### Ý tưởng

Một trong những nhận xét quan trọng nhất mà ta cần đưa ra để xử lý bài toán này là: tần suất xuất hiện của ký tự xuất hiện ít nhất là không quá $6$. Tức là $\min(c_\texttt{0}, c_\texttt{1}, c_\texttt{?}) \leq 6$ với $c_\texttt{0}, c_\texttt{1}, c_\texttt{?}$ lần lượt là tần suất xuất hiện của từng loại ký tự trong xâu.

:::spoiler Chứng minh
Ta có thể sử dụng phản chứng: Giả sử tồn tại một pattern mà mọi ký tự đều xuất hiện ít nhất $7$ lần. Khi đó, tổng số ký tự tối thiểu của pattern sẽ là $21$, không đúng với giới hạn đề bài.
:::

Đây là giới hạn đủ nhỏ để duyệt sub-mask. Từ đó, ta có ý tưởng trả lời truy vấn bằng cách duyệt sub-mask trên ký tự xuất hiện ít nhất trong $\mathcal{O}\left( 2^{\min(c_\texttt{0}, c_\texttt{1}, c_\texttt{?})} \right)$.

##### Trường hợp 1: Ký tự $\texttt{?}$ xuất hiện ít nhất

Đây là trường hợp dễ xử lý nhất, ta đơn giản là duyệt tất cả các bitmask thỏa pattern và tính tổng tương ứng là xong. Độ phức tạp của trường hợp này là $\mathcal{O}(2^{c_\texttt{?}})$.

##### Trường hợp 2: Ký tự $\texttt{1}$ xuất hiện ít nhất

Gọi $S_\texttt{1}, S_\texttt{?}$ lần lượt là tập các vị trí xuất hiện của ký tự $\texttt{1}$ và $\texttt{?}$. Để đảm bảo độ phức tạp, ta chỉ có thể duyệt tập con của $S_\texttt{1}$.

Gọi $f(T)$ là tổng giá trị các mask thỏa $\texttt{mask} \subseteq (T \cup S_\texttt{?})$ (với $T \subseteq S_\texttt{1}$), $f(T)$ có thể được tính bằng DP SoS. Từ hàm $f(T)$, ta có thể tính đáp án bằng Bao hàm loại trừ như sau:

$$
\sum_{T \subseteq S_\texttt{1}} f(T) \cdot (-1)^{|T| + |S_\texttt{1}|}
$$

Như vậy, ta giải quyết được trường hợp này trong $\mathcal{O}(2^{c_\texttt{1}})$.

##### Trường hợp 3: Ký tự $\texttt{0}$ xuất hiện ít nhất

Đối với trường hợp này, ta lại sử dụng Bao hàm loại trừ tương tự trường hợp 2. Gọi $S_\texttt{0}, S_\texttt{1}$ lần lượt là tập các vị trí xuất hiện của ký tự $\texttt{0}$ và $\texttt{1}$, $g(T)$ là tổng giá trị các mask thỏa $\texttt{mask} \supseteq (T \cup S_\texttt{1})$ (với $T \subseteq S_\texttt{0}$). Hàm $g(T)$ cũng có thể được tính bằng DP SoS.

$$
\sum_{T \subseteq S_\texttt{0}} g(T) \cdot (-1)^{|T|}
$$

Độ phức tạp của trường hợp cuối cùng là $\mathcal{O}(2^{c_\texttt{0}})$.


#### Độ phức tạp

- Độ phức tạp thời gian: $\mathcal{O} \left(2^L \cdot L + Q \cdot 2^{\min(c_\texttt{0}, c_\texttt{1}, c_\texttt{?})} \right)$.
- Độ phức tạp bộ nhớ: $\mathcal{O}(2^L)$.


#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

int toxic[1 << 20], sosSub[1 << 20], sosSuper[1 << 20];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int k, Q; cin >> k >> Q;
    for (int i = 0; i < (1 << k); i++) {
        char c; cin >> c;
        toxic[i] = sosSub[i] = sosSuper[i] = c - '0';
    }

    for (int i = 0; i < k; i++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) sosSub[mask] += sosSub[mask ^ (1 << i)];
            else sosSuper[mask] += sosSuper[mask ^ (1 << i)];
        }
    }

    int full = (1 << k) - 1;
    while (Q--) {
        string s; cin >> s;
        reverse(s.begin(), s.end());

        int maskZ = 0, maskO = 0, maskQ = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') maskZ |= (1 << i);
            if (s[i] == '1') maskO |= (1 << i);
            if (s[i] == '?') maskQ |= (1 << i);
        }

        int ans = 0;
        if (__builtin_popcount(maskQ) <= 6) {
            ans = toxic[maskO];
            for (int sub = maskQ; sub; sub = (sub - 1) & maskQ)
                ans += toxic[sub | maskO];
        }
        else if (__builtin_popcount(maskO) <= 6) {
            ans = sosSub[maskQ] * (__builtin_parity(maskO) ? -1 : 1);
            for (int sub = maskO; sub; sub = (sub - 1) & maskO) {
                if (__builtin_parity(sub) ^ __builtin_parity(maskO)) ans -= sosSub[sub | maskQ];
                else ans += sosSub[sub | maskQ];
            }
        }
        else if (__builtin_popcount(maskZ) <= 6) {
            ans = sosSuper[maskO];
            for (int sub = maskZ; sub; sub = (sub - 1) & maskZ) {
                if (__builtin_parity(sub)) ans -= sosSuper[sub | maskO];
                else ans += sosSuper[sub | maskO];
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
```
:::

## Phụ lục

### Luyện tập thêm

- [Codeforces 1185F - Two Pizzas](https://codeforces.com/contest/1185/problem/F)
- [Codeforces 1043F - Make It One](https://codeforces.com/contest/1043/problem/F)
- [Codeforces 986C - AND Graph](https://codeforces.com/contest/986/problem/C)
- [Codechef - Strange Functions](https://www.codechef.com/problems/STR_FUNC)
- [AtCoder 137D - Prefix XORs](https://atcoder.jp/contests/arc137/tasks/arc137_d)
- [Kilonova - XorTransform](https://kilonova.ro/problems/1832)
- [Codeforces 1620G - Subsequences Galore](https://codeforces.com/problemset/problem/1620/G)
- [Codeforces 1326F2 - Wise Men](https://codeforces.com/contest/1326/problem/F2)
- [Codeforces 1713F - Lost Array](https://codeforces.com/problemset/problem/1713/F)
- [AtCoder 136D - Without Carry](https://atcoder.jp/contests/arc136/tasks/arc136_d?lang=en)

Ngoài ra, bạn đọc có thể tìm kiếm thêm những bài tập khác để trau dồi kỹ năng xử lý những dạng toán liên quan [tại đây](https://oj.vnoi.info/tags/?tag_id=dp-sos).

### Tham khảo

- [[USACO Guide] Siyong Huang, Aakash Gokhale - Sum over Subsets DP](https://usaco.guide/adv/dp-sos)
- [[Codeforces] usaxena95 - SOS Dynamic Programming](https://codeforces.com/blog/entry/45223)
- [[Codeforces] sidhant - Tutorial on Zeta Transform, Mobius Transform and Subset Sum Convolution](https://codeforces.com/blog/entry/72488)