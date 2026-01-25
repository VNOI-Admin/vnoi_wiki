---
title: Quy hoạch động SOS - Phần 2
description: 
published: true
date: 2026-01-25T10:43:15.275Z
tags: 
editor: markdown
dateCreated: 2025-03-21T13:38:01.273Z
---

# DP Sum over Subsets (DP SoS), phần 2

**Người viết:**

- Phạm Công Minh -- THPT Chuyên Khoa học Tự nhiên, Đại học Quốc gia Hà Nội.
- Nguyễn Tấn Minh -- THPT Chuyên Lê Hồng Phong, TPHCM.

**Reviewer:**

- Trần Xuân Bách -- University of Chicago.
- Nguyễn Minh Hiển -- Đại học Công nghệ, Đại học Quốc gia Hà Nội.
- Đoàn Gia Huy -- THPT Chuyên Khoa học Tự nhiên, Đại học Quốc gia Hà Nội.
- Nguyễn Quang Minh -- Michigan State University.

Ở [phần trước](/algo/dp/dp-sos-1), chúng ta đã được tìm hiểu về DP Sum over Subsets, các biến thể cũng như một số bài tập minh họa. Trong phần tiếp theo, ta sẽ đào sâu hơn vào các dạng bài yêu cầu biến đổi khéo léo hơn để có thể áp dụng DP SoS qua ba phép nhân trên hàm số và tập hợp cũng như một số bài tập khác.

Tương tự phần trước, các kí hiệu của phép toán trên tập hợp sẽ được áp dụng cho cả ngôn ngữ bitmask.

## Phép gộp tập hợp (AND/OR convolution)

### OR convolution

#### Bài toán

Cho hai hàm $f, g : U \rightarrow \mathbb{R}$ với $U$ là ký hiệu tập các tập con của $\{0, 1, \dots, n - 1\}$, ta định nghĩa phép gộp tập hợp $f * g$ cho ra hàm $h$ thỏa:

$$
h(S) = \sum_{T_1 \cup T_2 = S} f(T_1) \cdot g(T_2)
$$

#### Ý tưởng

Trước tiên, ta định nghĩa hàm $\hat{h}(S)$ như sau:

$$
\hat{h}(S) = \sum_{T_1 \cup T_2 \subseteq S} f(T_1) \cdot g(T_2)
$$

Ở phần trước, ta đã biết cách khôi phục hàm $h$ từ hàm $\hat{h}$ bằng DP SoS ngược hoặc Bao hàm loại trừ. Nhiệm vụ của chúng ta bây giờ là tính $\hat{h}$. Dễ thấy, điều kiện $T_1 \cup T_2 \subseteq S$ cũng tương đương với $T_1 \subseteq S$ và $T_2 \subseteq S$, từ đó, ta biến đổi công thức tính:

$$
\hat{h}(S) = \sum_{T_1 \subseteq S, T_2 \subseteq S} f(T_1) \cdot g(T_2) = \left( \sum_{T_1 \subseteq S} f(T_1) \right) \cdot \left( \sum_{T_2 \subseteq S} g(T_2) \right) = \hat{f}(S) \cdot \hat{g}(S)
$$

Chúng ta lại trở về với bài toán Sum over Subsets trên hàm $f, g$. Như vậy, ta đã giải quyết được bài toán trong $\mathcal{O}(2^n \cdot n)$.

### AND convolution

Bằng ý tưởng tương tự, ta có thể giải quyết phép nhân như sau:

$$
h(S) = \sum_{T_1 \cap T_2 = S} f(T_1) \cdot g(T_2)
$$

Định nghĩa hàm $\hat{h}(S)$:

$$
\hat{h}(S) = \sum_{T_1 \cap T_2 \supseteq S} f(T_1) \cdot g(T_2) = \left( \sum_{T_1 \supseteq S} f(T_1) \right) \cdot \left( \sum_{T_2 \supseteq S} g(T_2) \right)
$$

Cuối cùng, ta lại sử dụng DP SoS ngược để khôi phục $h(S)$ từ $\hat{h}(S)$. Độ phức tạp của thuật toán này cũng là $\mathcal{O}(2^n \cdot n)$.

### Cài đặt

Ở phần này, mình chỉ cài đặt OR Convolution, AND Convolution được thực hiện tương tự.

:::spoiler Code tham khảo
```cpp=
vector<int> sos (const vector<int> &f, int n, bool reversed = 0) {
    vector<int> dp = f;
    if (reversed) {
        for (int k = n - 1; k >= 0; k--)
            for (int mask = 0; mask < (1 << n); mask++)
                if (mask & (1 << k)) dp[mask] -= dp[mask ^ (1 << k)];
    }
    else {
        for (int k = 0; k < n; k++)
            for (int mask = 0; mask < (1 << n); mask++)
                if (mask & (1 << k)) dp[mask] += dp[mask ^ (1 << k)];
    }
    return dp;
}

vector<int> orConvolution (const vector<int> &f, const vector<int> &g, int n) {
    vector<int> hhat(1 << n), fhat = sos(f, n), ghat = sos(g, n);
    for (int mask = 0; mask < (1 << n); mask++)
        hhat[mask] = fhat[mask] * ghat[mask];
    return sos(hhat, n, 1);
}
```
:::

### Nhân nhiều hàm

Giả sử, ta cần thực hiện phép nhân nêu trên với ba hàm, tức là tính $f_1(S) * f_2(S) * f_3(S)$. Ta sẽ không thực hiện riêng từng phép nhân mà thực hiện DP SoS trên từng hàm, tính $\hat{h}(S)$ cho cả ba hàm rồi DP SoS ngược. Lúc này, công thức định nghĩa hàm $\hat{h}(S)$ là:

$$
\hat{h}(S) = \left( \sum_{T_1 \subseteq S} f_1(T_1) \right) \cdot \left( \sum_{T_2 \subseteq S} f_2(T_2) \right) \cdot \left( \sum_{T_3 \subseteq S} f_3(T_3) \right)
$$

Ý tưởng tương tự cũng được áp dụng cho phép nhân $M$ hàm.

Tuy không giảm được độ phức tạp nhưng cách làm này tiết kiệm được một số bước và giảm hằng số của độ phức tạp một cách đáng kể.

## Phép nhân tập con (Subset sum convolution)

Cho hai hàm $f, g : U \rightarrow \mathbb{R}$ với $U$ là ký hiệu tập các tập con của $\{0, 1, \dots, n - 1\}$, ta định nghĩa phép nhân tập con $f * g$ cho ra hàm $h$ thỏa:

$$
h(S) = \sum_{T \subseteq S} f(T) \cdot g(S \setminus T)
$$

### Ý tưởng

Ta biến đổi công thức định nghĩa như sau:

$$
h(S) = \sum_{\substack{T_1 \cup T_2 = S \\ T_1 \cap T_2 = \varnothing}} f(T_1) \cdot g(T_2)
$$

Với $T_1 \cup T_2 = S$, ta có thể biến đổi điều kiện $T_1 \cap T_2 = \varnothing$ thành $|T_1| + |T_2| = |S|$, vì nếu $T_1, T_2$ có phần giao thì $|T_1| + |T_2| < |S|$. Do đó, ta cần thêm một chiều để kiểm soát kích thước của các tập con. Ta định nghĩa lại hàm $h(S)$ thành hàm $h_i(S)$ là:

$$
h_i(S) = \sum_{\substack{T_1 \cup T_2 = S \\ |T_1| + |T_2| = i}} f(T_1) \cdot g(T_2)
$$

Khi đó, mục tiêu của chúng ta là tính $h_{|S|}(S)$ với mọi tập $S$. Và để làm điều này, ta lại sử dụng ý tưởng tương tự phép nhân gộp tập hợp, định nghĩa hàm $\hat{h}_i(S)$:

$$
\hat{h}_i(S) = \sum_{\substack{T_1, T_2 \subseteq S \\ |T_1| + |T_2| = i}} f(T_1) \cdot g(T_2)
$$

Để tính $\hat{h}_i(S)$, ta cần tính hai hàm khác:

$$
\begin{align*}
F_i(S) &= \sum_{\substack{T \subseteq S \\ |T| = i}} f(T) \\
G_i(S) &= \sum_{\substack{T \subseteq S \\ |T| = i}} g(T) \\
\end{align*}
$$

Sau đó, ta có thể tính $\hat{h}_i(S)$ bằng công thức:

$$
\hat{h}_i(S) = \sum_{0 \leq j \leq i} F_j(S) \cdot G_{i - j}(S)
$$

Ta lại sử dụng DP SoS ngược để khôi phục từng hàm $h_i(S)$ từ $\hat{h}_i(S)$ để đưa ra đáp án cuối cùng. Như vậy, thuật toán có độ phức tạp $\mathcal{O}(2^n \cdot n^2)$.

### Cài đặt

Trước tiên, ta cần tính các hàm $F_i(S)$ và $G_i(S)$, việc tính toán được thực hiện tương tự DP SoS truyền thống: Gọi $\texttt{dpF}_i(\texttt{mask}, k)$ và $\texttt{dpG}_i(\texttt{mask}, k)$ lần lượt là hàm DP SoS trên hàm $F_i(S), G_i(S)$. Ở đây, ta chỉ lưu ý trường hợp cơ sở sẽ có một chút thay đổi:

$$
\texttt{dpF}_i(\texttt{mask}, 0) =
\begin{cases}
f(\texttt{mask}) & |\texttt{mask}| = i \\
0 & |\texttt{mask}| \neq i \\
\end{cases}
$$

Sau khi đã có hàm $F_i(S), G_i(S)$, ta thực hiện các bước còn lại như mô tả ở trên.

:::spoiler Code tham khảo
```cpp=
vector<int> sos (const vector<int> &f, int n, bool reversed = 0) {
    vector<int> dp = f;
    if (reversed) {
        for (int k = n - 1; k >= 0; k--)
            for (int mask = 0; mask < (1 << n); mask++)
                if (mask & (1 << k)) dp[mask] -= dp[mask ^ (1 << k)];
    }
    else {
        for (int k = 0; k < n; k++)
            for (int mask = 0; mask < (1 << n); mask++)
                if (mask & (1 << k)) dp[mask] += dp[mask ^ (1 << k)];
    }
    return dp;
}

vector<int> subsetConvolution (const vector<int> &f, const vector<int> &g, int n) {
    vector<vector<int>> fhat(n + 1, vector<int>(1 << n)), ghat(n + 1, vector<int>(1 << n));
    for (int mask = 0; mask < (1 << n); mask++) {
        fhat[__builtin_popcount(mask)][mask] = f[mask];
        ghat[__builtin_popcount(mask)][mask] = g[mask];
    }
    for (int i = 0; i <= n; i++)
        fhat[i] = sos(fhat[i], n), ghat[i] = sos(ghat[i], n);

    vector<vector<int>> hhat(n + 1, vector<int>(1 << n));
    for (int i = 0; i <= n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            for (int j = 0; j <= i; j++)
                hhat[i][mask] += fhat[j][mask] * ghat[i - j][mask];
    for (int i = 0; i <= n; i++)
        hhat[i] = sos(hhat[i], n, 1);

    vector<int> h(1 << n);
    for (int mask = 0; mask < (1 << n); mask++)
        h[mask] = hhat[__builtin_popcount(mask)][mask];
    return h;
}
```
:::

Để kiểm tra code, bạn đọc có thể tìm bài Subset Convolution ở phần *Phụ lục*.

## Phép hiệu đối xứng (XOR Convolution)

Với phép tính cuối cùng cũng như phép tính phức tạp nhất chính là phép hiệu đối xứng. Trước khi nghiên cứu đến phần này, bạn đọc cần biết trước về [Fast Fourier Transform (FFT)](https://wiki.vnoi.info/vi/algo/trick/FFT) và sơ lược về [Fast Walsh-Hadamard Transform (FWHT)](https://en.wikipedia.org/wiki/Fast_Walsh%E2%80%93Hadamard_transform).

Cho hai hàm $f, g : U \rightarrow \mathbb{R}$ với $U$ là ký hiệu tập các tập con của $\{0, 1, \dots, n - 1\}$, ta định nghĩa phép nhân tập con $f * g$ cho ra hàm $h$ thỏa:

$$
h(S) = \sum_{T_1 \oplus T_2 = S} f(T_1) \cdot g(T_2)
$$

Phép hiệu đối xứng $\oplus$ được định nghĩa tương tự phép XOR trên bitmask:

$$
A \oplus B = \{x \mid [x \in A] \oplus [x \in B] \}
$$

với $[P]$ (Iversion bracket) được định nghĩa là:

$$
[P] =
\begin{cases}
1 & \text{if } P \text{ is true;} \\
0 & \text{otherwise.} \\
\end{cases}
$$

### Hướng xử lý

Để xử lý phép hiệu đối xứng một cách hiệu quả, ta cần lấy cảm hứng từ một thuật toán khác: Phép nhân đa thức bằng FFT. Nhìn chung, để nhân đa thức trong $\mathcal{O}(n \log n)$, ta cần thực hiện ba bước là biến đổi hàm bằng cách thế căn đơn vị thứ $n$ vào (Discrete Fourier Transform), nhân hệ số, rồi khôi phục lại tích của hai đa thức (Inversed Discrete Fourier Transform).

Với phép hiệu đối xứng, ta cũng sử dụng mô hình tương tự, nhưng thay vì sử dụng Discrete Fourier Transform (DFT), ta dùng Walsh-Hadamard Transform (WHT). Ta sẽ cùng tìm hiểu Walsh-Hadamard Transform và xây dựng một thuật toán Fast Walsh-Hadamard Transform dựa trên DP SoS.

### Walsh-Hadamard Transform

Với WHT, ta chỉ xét các đa thức bậc $1$.

Sự khác biệt giữa DFT và WHT là khi nhân hai số hạng $ax^i$ và $bx^j$ với nhau, DFT sẽ cho ra $(a \cdot b)x^{i+j}$, còn đối với WHT, ta mong muốn sẽ cho ra $(a \cdot b)x^{i \oplus j}$. Rõ ràng, WHT đang phá đi tính chất tự nhiên của phép nhân và lũy thừa.

Để giải quyết điều này, ta tách $x$ ra thành hàm $n$ thừa số, với số mũ của từng thừa số ứng với trạng thái bật/tắt của bit tương ứng trong biểu diễn nhị phân của $x$ (giả sử cần xét $n$ bit đầu tiên). Nói cách khác, mỗi số hạng bây giờ sẽ có dạng $a \cdot x_0^{z_0}x_1^{z_1} \dots x_{n-1}^{z_{n-1}}$ (với $0 \leq z_i \leq 1$ là trạng thái của bit thứ $i$, $a$ là hệ số của số hạng). Từ đây, ta có thể thấy rằng WHT về bản chất là FFT trên đa thức $n$ chiều bậc $1$.

Với mỗi chiều của đa thức sau khi biến đổi, ta cần tính $2$ điểm phân biệt (tương tự FFT), vậy với cả đa thức, ta cần tính $2^n$ điểm.

Trở lại với vấn đề nêu trên, lúc này, khi số mũ chỉ còn là một bit, ta có thể dễ dàng biến đổi $x^{i \oplus j}$ thành $x^{(i + j) \bmod 2}$. Tức là ta vẫn có thể nhân đa thức bình thường, nhưng hệ số của các số hạng $x^0, x^2, x^4, \dots$ và $x^1, x^3, x^5, \dots$ phải được gộp lại thành một. Nói cách khác, ta cần chọn hai điểm phân biệt để tính có $x$ thỏa:

$$
\begin{cases}
x^0 = x^2 = x^4 = \dots \\
x^1 = x^3 = x^5 = \dots \\
\end{cases}
$$

Dễ thấy, hai giá trị $-1$ và $1$ thỏa mãn điều kiện này.

:::info
Như vậy, với Walsh-Hadamard Transform, ta được cho một đa thức $n$ chiều bậc $1$ có dạng $f(x_0, x_1, \dots, x_{n-1})$. Ta cần tính giá trị đa thức tại $2^n$ điểm có dạng $x = (\pm 1, \pm 1, \dots, \pm 1)$.
:::

### Fast Walsh-Hadamard Transform (sử dụng mô hình DP SoS)

Để ý rằng mỗi điểm cần tính gồm $n$ tham số, mỗi tham số có $2$ cách chọn. Vì thế, ta có thể biểu diễn một bộ tham số dưới dạng một tập con của $\{0, 1, \dots, n - 1\}$ sao cho tham số thứ $i$ của tập biểu diễn $S$ là $(-1)^{[i \in S]}$.

Từ những phân tích trên, ta định nghĩa WHT lại trên ngôn ngữ của hàm số và tập hợp. Cho hàm $f : U \rightarrow \mathbb{R}$ với $U$ là ký hiệu tập các tập con của $\{0, 1, \dots, n - 1\}$, ta định nghĩa phép biển đổi Walsh-Hadamard của hàm $f$ là hàm $\hat{f}(S)$ sao cho:

$$
\hat{f}(S) = \sum_{T \subseteq U} \left( f(T) \cdot \prod_{i \in T} (-1)^{[i \in S]} \right) = \sum_{T \subseteq U} f(T) \cdot (-1)^{|S \cap T|}
$$

#### Ý tưởng đặt trạng thái

Để tính $\hat{f}(S)$, ta xử lý từng bit của hàm. Xét hàm $n$ chiều $f(x_0, x_1, \dots, x_{n-1})$, ta có thể gom các số hạng của nó thành hai nhóm:

- Các số hạng chứa $x_{n-1}^0$, đặt là $f_0(x_0, x_1, \dots, x_{n-2})$.
- Các số hạng chứa $x_{n-1}^1$, đem $x_{n-1}$ ra ngoài làm nhân tử chung rồi đặt nhóm này là $x_{n-1} \cdot f_1(x_0, x_1, \dots, x_{n-2})$.

Tương tự, để tính $f_0, f_1$, ta lại nhóm chúng thành hai nhóm theo số mũ của $x_{n-2}$. Ta sẽ có $4$ nhóm là:

$$
\begin{align*}
x_{n-1}^0 \cdot x_{n-2}^0 \cdot f_{0, 0}(x_0, x_1, \dots, x_{n-3}) \\
x_{n-1}^0 \cdot x_{n-2}^1 \cdot f_{0, 1}(x_0, x_1, \dots, x_{n-3}) \\
x_{n-1}^1 \cdot x_{n-2}^0 \cdot f_{1, 0}(x_0, x_1, \dots, x_{n-3}) \\
x_{n-1}^1 \cdot x_{n-2}^1 \cdot f_{1, 1}(x_0, x_1, \dots, x_{n-3}) \\
\end{align*}
$$

Như vậy, ý tưởng là tại tầng đệ quy thứ $i$, ta nhóm các số hạng theo hậu tố chung độ dài $i$ rồi đem phần hậu tố này ra đặt làm nhân tử chung. Ta có $2^i$ nhóm và ở mỗi nhóm ta cần tính giá trị hàm tại $2^{n-i}$ điểm (do chỉ còn $n-i$ chưa được đặt làm nhân tử chung).

Ta định nghĩa $f_{s_{n-1}, s_{n-2}, \dots, s_k}(x_0, x_1, \dots, x_{k-1})$ là đa thức gồm các số hạng có hậu tố chung là $x_{n-1}^{s_{n-1}} \cdot x_{n-2}^{s_{n-2}} \cdots x_k^{s_k}$ sau khi đã bỏ phần hậu tố chung này đi.

Đến đây, ta có thể lấy ý tưởng chia một bitmask ra làm hai nửa để đặt trạng thái giống như DP SoS để áp dụng vào FWHT. Cụ thể, ta có thể biểu diễn trạng thái bằng cặp $(\texttt{mask}, k)$ với ý nghĩa:

- Các bit trước vị trí $k$ cho biết giá trị $-1$ hoặc $1$ sẽ được thế vào hàm (phần chưa được đặt nhân tử chung).
- Các bit sau hoặc tại vị trí $k$ cho biết số mũ tương ứng của phần đã được đặt nhân tử chung.

Ví dụ, cặp $(\texttt{101}{\color{red}{\texttt{001}}}, 3)$ biểu diễn nhóm $f_{1, 0, 1}(x_0, x_1, x_2)$ sau khi được thế $x_0, x_1, x_2$ lần lượt cho $-1, 1, 1$.

#### Xây dựng Quy hoạch động

Như vậy, ta gọi $\texttt{dp}(\texttt{mask}, k)$ là giá trị hàm $f$ theo định nghĩa như trên. Cụ thể hơn, giả sử bitmask có dạng $\texttt{mask} = s_0 s_1 \dots s_{n-1}$, ta có:

$$
\texttt{dp}(\texttt{mask}, k) = f_{s_{n-1}, s_{n-2}, \dots, s_k} ((-1)^{s_0}, (-1)^{s_1}, \dots, (-1)^{s_{k-1}})
$$

Ta có trường hợp cơ sở là $\texttt{dp}(\texttt{mask}, 0) = f(\texttt{mask})$ (phần nhân tử chung có $n$ bit và hàm không có bit nào).

Để tính $\texttt{dp}(\texttt{mask}, k)$, ta lại xét $2$ trường hợp:

- Giá trị cần thế vào $x_{k-1}$ là $1$, tức bit thứ $k - 1$ của $\texttt{mask}$ tắt, khi đó:

$$
\texttt{dp}(\texttt{mask}, k) = \texttt{dp}(\texttt{mask}, k - 1) + \texttt{dp}(\texttt{mask} \cup \{k - 1\}, k - 1)
$$

- Giá trị cần thế vào $x_{k-1}$ là $-1$, tức bit thứ $k - 1$ của $\texttt{mask}$ bật, nhóm $(\texttt{mask}, k - 1)$ lúc này có nhân tử chung là $-1$ được đặt ra ngoài nên:

$$
\texttt{dp}(\texttt{mask}, k) = \texttt{dp}(\texttt{mask} \setminus \{k - 1\}, k - 1) - \texttt{dp}(\texttt{mask}, k - 1)
$$

Cuối cùng, ta có $\hat{f}(S) = \texttt{dp}(\texttt{mask}, n)$ (phần nhân tử chung không có bit nào và hàm có $n$ bit).

Để rút gọn công thức hơn, ta đặt $u = \texttt{dp}(\texttt{mask} \oplus \{k - 1\}, k - 1)$ và $v = \texttt{dp}(\texttt{mask}, k - 1)$, ta có công thức Quy hoạch động:

$$
\texttt{dp}(\texttt{mask}, k) = \begin{cases}
f(\texttt{mask}) & k = 0 \\
u + v & k - 1 \notin \texttt{mask} \\
u - v & k - 1 \in \texttt{mask} \\
\end{cases}
$$

Như vậy, ta đã có thuật toán biến đổi Walsh-Hadamard trong $\mathcal{O}(2^n \cdot n)$.

### Walsh-Hadamard Transform ngược

Sau khi đã có hàm $\hat{f}(S)$ và $\hat{g}(S)$ bằng FWHT, ta tính $\hat{h}(S)$ bằng cách nhân hệ số:

$$
\hat{h}(S) = \hat{f}(S) \cdot \hat{g}(S)
$$

Vấn đề cuối cùng chưa được giải quyết là làm cách nào để khôi phục $h(S)$ từ $\hat{h}(S)$. Nói cách khác, làm thế nào để biến đổi Walsh-Hadamard ngược.

Để giải quyết bài toán này, ta cần quay về cách giải thích FWHT nguyên thủy là phép nhân ma trận. Quá trình mà ta vừa thực hiện ở phần trên tương đương với việc biến hàm $f$ thành một vector $2^n \times 1$, gọi là $\mathbf{F}$. Khi đó, vector $\mathbf{\hat{F}}$ được tính qua phép nhân ma trận:

$$
\mathbf{\hat{F}} = \mathbf{H}_{2^n} \cdot \mathbf{F}
$$

với $\mathbf{H}_{2^n}$ là [ma trận Hadamard](https://en.wikipedia.org/wiki/Hadamard_matrix) bậc $2^n$.

Để khôi phục $\mathbf{F}$ từ $\mathbf{\hat{F}}$, ta cần tính $\mathbf{H}_{2^n}^{-1}$. May mắn thay, với tính chất đặc biệt của ma trận Hadamard, ma trận Hadamard nghịch đảo chính là ma trận Hadamard chia cho $2^n$. Tức là ta chỉ việc tính:

$$
\mathbf{F} = \frac{1}{2^n} \cdot \mathbf{H}_{2^n} \cdot \mathbf{\hat{F}}
$$

Như vậy, để khôi phục $h(S)$ từ $\hat{h}(S)$, ta thực hiện biến đổi Walsh-Hadamard trên $\hat{h}(S)$ rồi chia mọi hệ số của hàm đã được biến đổi cho $2^n$.

### Cài đặt

#### Sử dụng bảng QHĐ hai dòng

Đối với FWHT, ta không thể cài đặt theo cách tối ưu bộ nhớ của DP SoS được vì các giá trị của dòng hiện tại và dòng trước sẽ bị tính toán lẫn lộn. Do đó, cách xử lý đơn giản nhất là duy trì bảng QHĐ hai dòng rồi trả về dòng $n \mathrel{\&} 1$ làm đáp án.

:::spoiler Code tham khảo
```cpp=
vector<int> fwht (const vector<int> &f, int n, bool inversed = 0) {
    vector<vector<int>> dp(2, vector<int>(1 << n));
    dp[0] = f;

    int sz = 1 << n;
    for (int k = 1; k <= n; k++) {
        int t = k & 1;
        for (int mask = 0; mask < sz; mask++) {
            int u = dp[t ^ 1][mask ^ (1 << (k - 1))], v = dp[t ^ 1][mask];
            if (mask & (1 << (k - 1))) dp[t][mask] = u - v;
            else dp[t][mask] = u + v;
        }
    }
    if (inversed)
        for (int mask = 0; mask < sz; mask++) dp[n & 1][mask] /= sz;

    return dp[n & 1];
}

vector<int> xorConvolution (const vector<int> &f, const vector<int> &g, int n) {
    int sz = 1 << n;
    vector<int> hhat(sz), fhat = fwht(f, n), ghat = fwht(g, n);
    for (int mask = 0; mask < sz; mask++)
        hhat[mask] = fhat[mask] * ghat[mask];
    return fwht(hhat, n, 1);
}
```
:::

#### Sử dụng bảng QHĐ một dòng

Để bỏ bớt một chiều trong bộ nhớ bảng QHĐ, ở mỗi vòng, ta bắt cặp các mask có dạng $\texttt{mask}$ và $\texttt{mask} \oplus \{k-1\}$ để tính cùng một lúc.

:::spoiler Code tham khảo
```cpp=
vector<int> fwht (const vector<int> &f, int n, bool inversed = 0) {
    vector<int> dp = f;

    int sz = 1 << n;
    for (int k = 0; k < n; k++) {
        for (int mask = 0; mask < sz; mask++) {
            if (!(mask & (1 << k))) continue;
            int u = dp[mask ^ (1 << k)], v = dp[mask];
            dp[mask ^ (1 << k)] = u + v, dp[mask] = u - v;
        }
    }
    if (inversed)
        for (int mask = 0; mask < sz; mask++) dp[mask] /= sz;

    return dp;
}

vector<int> xorConvolution (const vector<int> &f, const vector<int> &g, int n) {
    int sz = 1 << n;
    vector<int> hhat(sz), fhat = fwht(f, n), ghat = fwht(g, n);
    for (int mask = 0; mask < sz; mask++)
        hhat[mask] = fhat[mask] * ghat[mask];
    return fwht(hhat, n, 1);
}
```
:::

### Nhân nhiều hàm

Tương tự với phép gộp tập hợp, nếu muốn nhân nhiều hàm theo phép hiệu đối xứng, ta có thể biến đổi Walsh-Hadamard cho từng hàm, nhân giá trị tính được, rồi biến đổi Walsh-Hadamard ngược để nhận được hàm kết quả.

## Tổng kết

Nhìn chung, có thể thấy rằng các phép nhân các hàm trên tập hợp có đặc điểm chung là bao gồm $3$ bước chính: biến đổi (DP SoS), nhân hệ số, biến đổi ngược (DP SoS ngược). Tùy vào đặc điểm và tính chất của từng phép nhân, ta sẽ biến đổi công thức để đưa về các mô hình liên quan đến bài toán Sum over Subsets để tận dụng tốc độ của thuật toán này.

## Bài tập ứng dụng

*Bạn đọc nên tự thử sức trước với các bài tập dưới đây trước khi bước vào phần phân tích ý tưởng và cài đặt nhé.*

### Codeforces 914G - Sum of Fibonacci

[Link đề gốc](https://codeforces.com/contest/914/problem/G)

Cho dãy $s$ gồm $n$ phần tử. Định nghĩa một bộ năm số nguyên $(a, b, c, d, e)$ là hợp lệ nếu:

- $1 \leq a, b, c, d, e \leq n$.
- $(s_a \mid s_b) \mathrel{\&} s_c \mathrel{\&} (s_d \oplus s_e) = 2^i$ (với $i$ là một số nguyên bất kì).
- $s_a \mathrel{\&} s_b = 0$

Với mọi bộ năm hợp lệ, hãy tính tổng:

$$
\left[ \sum f(s_a \mid s_b) \cdot f(s_c) \cdot f(s_d \oplus s_e) \right] \bmod (10^9 + 7)
$$

với $f(i)$ là số Fibonacci thứ $i$ được định nghĩa như sau:

$$
f(i) =
\begin{cases}
i & 0 \leq i \leq 1 \\
f(i - 1) + f(i - 2) & i \geq 2 \\
\end{cases}
$$

#### Giới hạn

- $1 \leq n \leq 10^6$.
- $0 \leq  s_i < 2^{17}$.

#### Ý tưởng

Ta mặc định điều kiện thứ nhất luôn thỏa.

Từ điều kiện thứ hai, ta tách $a, b, c, d, e$ thành 3 nhóm để xử lý riêng, gồm: nhóm $a, b$, nhóm $c$, và nhóm $d, e$.

Gọi $M_1, M_2, M_3$ lần lượt là $s_a \mid s_b$ (với $s_a \mathrel{\&} s_b = 0$), $s_c$ và $s_d \oplus s_e$. Lúc này, ta cần tính:

$$
\sum_{M_1 \mathrel{\&} M_2 \mathrel{\&} M_3 = 2^i} f(M_1) \cdot f(M_2) \cdot f(M_3)
$$

Từ đây, gọi $g_i(S)$ là tổng các $f(M_i)$ thỏa đề bài sao cho $M_i = S$, ta có thể tìm đáp án bằng cách tính hàm $h(S)$:

$$
h(S) = g_1(S) * g_2(S) * g_3(S)
$$

Với $*$ là phép nhân gộp tập hợp theo bitwise AND (AND Convolution) theo định nghĩa ở phần trên. Hàm $h(S)$ cho biết tổng các tích fibonacci thỏa $M_1 \mathrel{\&} M_2 \mathrel{\&} M_3 = S$, nói cách khác:

$$
h(S) = \sum_{M_1 \mathrel{\&} M_2 \mathrel{\&} M_3 = S} f(M_1) \cdot f(M_2) \cdot f(M_3)
$$

Khi đó, đáp án cuối cùng là:

$$
\sum_{0 \leq i < 17} h(2^i)
$$

Bây giờ, ta sẽ tìm cách tính $g_i(S)$ cho từng nhóm:

##### Nhóm $a, b$

Đối với nhóm đầu tiên, ta có công thức định nghĩa $g_1(S)$ là:

$$
g_1(S) = \sum_{s_a \mathrel{\&} s_b = 0} f(s_a \mid s_b) \cdot [s_a \mid s_b = S] = f(S) \cdot \sum_{s_a \mathrel{\&} s_b = 0} [s_a | s_b = S]
$$

Dễ thấy, phần $\sum_{s_a \mathrel{\&} s_b} [s_a \mid s_b = S]$ có thể được tính bằng phép nhân tập con (subset sum convolution) được định nghĩa ở trên trong $\mathcal{O}(s \log^2 s)$.

##### Nhóm $c$

Đây là nhóm dễ xử lý nhất, ta có:

$$
g_2(S) = f(S) \cdot \texttt{cnt}[S]
$$

Với $\texttt{cnt}[]$ là mảng thống kê trên dãy $s$ ban đầu.

##### Nhóm $d, e$

Đối với nhóm thứ ba, ta có định nghĩa $g_3(S)$ là:

$$
g_3(S) = \sum f(s_d \oplus s_e) \cdot [s_d \oplus s_e = S] = f(S) \cdot \sum[s_d \oplus s_e = S]
$$

Tương tự nhóm $a, b$, phần $\sum[s_d \oplus s_e = S]$ có thể được tính bằng phép hiệu đối xứng (XOR convolution) trong $\mathcal{O}(s \log s)$.

##### Tổng kết

Cuối cùng, ta thực hiện phép nhân gộp tập hợp trong $\mathcal{O}(s \log s)$. Như vậy, thuật toán có độ phức tạp $\mathcal{O}(n + s \log^2 s)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const int mn = 1e6 + 6;
const int MOD = 1e9 + 7;

int add (int a, int b) { return a + b - (a + b < MOD ? 0 : MOD); }
int sub (int a, int b) { return a - b + (a - b >= 0 ? 0 : MOD); }
int mul (int a, int b) { return 1LL * a * b % MOD; }

int binpow (int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(ans, a);
    return ans;
}

namespace convolutions {
    // hàm biến đổi Walsh-Hadamard và biến đổi ngược
    vector<int> fwht (const vector<int> &f, int n, bool inversed = 0) {
        vector<int> dp = f;
        for (int k = 0; k < n; k++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (!(mask & (1 << k))) continue;
                int u = dp[mask ^ (1 << k)], v = dp[mask];
                dp[mask ^ (1 << k)] = add(u, v), dp[mask] = sub(u, v);
            }
        }
        if (inversed) {
            int inv = binpow(1 << n, MOD - 2);
            for (int mask = 0; mask < (1 << n); mask++) dp[mask] = mul(dp[mask], inv);
        }

        return dp;
    }

    // hàm DP sum over subset/superset và DP ngược
    vector<int> sos (const vector<int> &f, int n, bool subset, bool reversed = 0) {
        vector<int> dp = f;
        if (reversed) {
            for (int k = n - 1; k >= 0; k--) {
                for (int mask = 0; mask < (1 << n); mask++) {
                    bool flag = ((mask >> k & 1) == subset);
                    if (flag) dp[mask] = sub(dp[mask], dp[mask ^ (1 << k)]);
                }
            }
        }
        else {
            for (int k = 0; k < n; k++) {
                for (int mask = 0; mask < (1 << n); mask++) {
                    bool flag = ((mask >> k & 1) == subset);
                    if (flag) dp[mask] = add(dp[mask], dp[mask ^ (1 << k)]);
                }
            }
        }
        return dp;
    }
    
    // phép gộp tập hợp
    vector<int> andConvolution (const vector<int> &f1, const vector<int> &f2, const vector<int> &f3, int n) {
        vector<int> g1 = sos(f1, n, 0), g2 = sos(f2, n, 0), g3 = sos(f3, n, 0), hhat(1 << n);
        for (int mask = 0; mask < (1 << n); mask++)
            hhat[mask] = mul(g1[mask], mul(g2[mask], g3[mask]));
        return sos(hhat, n, 0, 1);
    }
    
    // phép nhân tập con
    vector<int> subsetConvolution (const vector<int> &f, const vector<int> &g, int n) {
        vector<vector<int>> fhat(n + 1, vector<int>(1 << n)), ghat(n + 1, vector<int>(1 << n));
        for (int mask = 0; mask < (1 << n); mask++) {
            fhat[__builtin_popcount(mask)][mask] = f[mask];
            ghat[__builtin_popcount(mask)][mask] = g[mask];
        }
        for (int i = 0; i <= n; i++)
            fhat[i] = sos(fhat[i], n, 1), ghat[i] = sos(ghat[i], n, 1);

        vector<vector<int>> hhat(n + 1, vector<int>(1 << n));
        for (int i = 0; i <= n; i++)
            for (int mask = 0; mask < (1 << n); mask++)
                for (int j = 0; j <= i; j++)
                    hhat[i][mask] = add(hhat[i][mask], mul(fhat[j][mask], ghat[i - j][mask]));
        for (int i = 0; i <= n; i++)
            hhat[i] = sos(hhat[i], n, 1, 1);

        vector<int> h(1 << n);
        for (int mask = 0; mask < (1 << n); mask++)
            h[mask] = hhat[__builtin_popcount(mask)][mask];
        return h;
    }

    // phép hiệu đối xứng
    vector<int> xorConvolution (const vector<int> &f, const vector<int> &g, int n) {
        int sz = 1 << n;
        vector<int> hhat(sz), fhat = fwht(f, n), ghat = fwht(g, n);
        for (int mask = 0; mask < sz; mask++)
            hhat[mask] = mul(fhat[mask], ghat[mask]);
        return fwht(hhat, n, 1);
    }
}

int fib[mn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // tính số Fibonacci
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < mn; i++) fib[i] = add(fib[i - 1], fib[i - 2]);

    // đọc input và tạo mảng thống kê
    int n = 17, m; cin >> m;
    vector<int> freq(1 << n), g1, g2, g3;

    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        freq[a]++;
    }

    // tính g1(S)
    g1 = convolutions::subsetConvolution(freq, freq, n);
    for (int mask = 0; mask < (1 << n); mask++) g1[mask] = mul(g1[mask], fib[mask]);

    // tính g2(S)
    g2 = freq;
    for (int mask = 0; mask < (1 << n); mask++) g2[mask] = mul(g2[mask], fib[mask]);

    // tính g3(S)
    g3 = convolutions::xorConvolution(freq, freq, n);
    for (int mask = 0; mask < (1 << n); mask++) g3[mask] = mul(g3[mask], fib[mask]);

    // tính h(S) và lấy kết quả
    vector<int> h = convolutions::andConvolution(g1, g2, g3, n);
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = add(ans, h[1 << i]);
    cout << ans;

    return 0;
}
```
:::

### ICPC 23-24 Asia Jakarta Regional Contest - Deck-Building Game

[Link đề gốc](https://codeforces.com/contest/1906/problem/K)

Cho dãy $a$ gồm $n$ phần tử. Đếm số cách chọn hai dãy con không có phần chung (có thể chọn tập rỗng) sao cho tổng XOR$^\dagger$ của hai dãy con này là bằng nhau. In đáp án modulo $998 \space 244 \space 353$.

$\dagger$ Tổng XOR của một dãy $b_1, b_2, \dots, b_m$ là $b_1 \oplus b_2 \oplus \dots \oplus b_m$.

#### Giới hạn

- $2 \leq n \leq 10^5$.
- $1 \leq a_i \leq 10^5$.

#### Các lời giải vét cạn

Để duyệt hai dãy con không có phần chung, ta có thể duyệt mọi tập con làm dãy con đầu tiên, sau đó duyệt mọi tập con của tập các vị trí chưa được chọn làm tập con thứ hai. Có thể thấy, ta đang chia dãy $a$ thành $3$ tập: các phần tử được chọn cho dãy con thứ nhất, các phần tử được chọn cho dãy con thứ hai và các phần tử không được chọn cho tập nào. Độ phức tạp của thuật toán này là $\mathcal{O}(3^n)$.

Ta có thể tối ưu thuật toán hơn bằng cách đưa ra nhận xét là tổng XOR của hai dãy con này luôn bằng $0$. Hơn nữa, khi có một dãy số có tổng XOR bằng $0$, mọi cách tách dãy số này ra thành hai phần không giao nhau đều cho ra hai dãy có tổng XOR bằng nhau. Ta có $2^m$ cách tách một dãy số có $m$ phần tử.

Từ đó, ta có thể tối ưu thuật toán trên thành: Duyệt mọi dãy con của $a$, gọi là $S$, nếu tổng XOR của chúng là $0$, tăng đáp án lên $2^{|S|}$.

#### Định nghĩa chuỗi lũy thừa tập hợp

Để dễ dàng hơn cho việc định nghĩa hàm sinh cho tập hợp, ta viết lại một hàm ánh xạ tập hợp $f: U \rightarrow \mathbb{R}$ (với $U$ là ký hiệu tập các tập con của $\{0, 1, \dots, m - 1\}$) dưới dạng **chuỗi lũy thừa tập hợp (set power series)** như sau:

:::info
Một hàm ánh xạ tập hợp $f: U \rightarrow \mathbb{R}$ có thể được viết lại dưới dạng:

$$
g(x) = \sum_{S \subseteq U} f(S) \cdot x^S
$$

Trong đó, ta gọi $g_S = f(S)$ là hệ số của số hạng $x^S$.

Các phép toán được tìm hiểu ở phần trên (phép gộp tập hợp, nhân tập con và hiệu đối xứng) cũng được định nghĩa tương tự trên chuỗi lũy thừa tập hợp.
:::

Giả sử, với $m = 2$ và hàm ánh xạ là $f(\varnothing) = 10$, $f(\{0\}) = -16$, $f(\{1\}) = 21$ và $f(\{0, 1\}) = 9$. Ta có chuỗi lũy thừa tập hợp tương ứng là:

$$
10x^\varnothing - 16x^{\{0\}} + 21x^{\{1\}} + 9x^{\{0, 1\}}
$$

#### Xây dựng hàm sinh

Như đã phân tích ở phần trên, với mỗi phần tử của dãy $a$, gọi là $a_i$, ta có $3$ cách chọn trạng thái cho nó:

- Chọn $a_i$ cho dãy con thứ nhất, cách chọn này đóng góp vào tổng XOR của hai dãy con bằng $a_i$.
- Chọn $a_i$ cho dãy con thứ hai, cách chọn này cũng đóng góp vào tổng XOR của hai dãy con bằng $a_i$.
- Không chọn $a_i$ cho dãy con nào cả, cách chọn này không đóng góp gì vào tổng XOR.

Từ đây, ta có thể biến đổi các giá trị của dãy $a$ thành tập hợp dựa trên biểu diễn nhị phân và xây dựng hàm sinh cho mỗi phần tử:

$$
g_i(x) = 1x^\varnothing + 2x^{a_i}
$$

Lúc này, ta cần tính số cách chọn sao cho tổng XOR của hai dãy con bằng $0$. Nói cách khác, ta cần tính hàm $G$ là tích của các hàm sinh theo **phép hiệu đối xứng**. Đáp án khi đó sẽ là hệ số của số hạng $x^\varnothing$.

Đến đây ta đã có thuật toán $\mathcal{O}(n \cdot 2^B)$ nếu nhân bằng thuật trâu (với $B = \lceil \log \max a \rceil$). Lưu ý rằng do số lượng số hạng có hệ số khác $0$ của từng hàm sinh là rất thấp nên việc áp dụng Fast Walsh-Hadamard Transform trực tiếp lên hàm sinh trong trường hợp này thậm chí còn làm chậm tốc độ chương trình.

#### Thực hiện Walsh-Hadamard Transform

Tuy không thực hiện thuật toán FWHT nhưng ý tưởng của lời giải vẫn sẽ là thực hiện biến đổi Walsh-Hadamard trên từng hàm sinh $g_i$ nhưng theo một cách khác.

Biến đổi Walsh-Hadamard trên hàm sinh $g_i$ sẽ cho ra hàm $\hat{g}_i$ (được viết dưới dạng hàm ánh xạ) như sau:

$$
\begin{align*}
\hat{g}_i(S) &= \sum_{T \subseteq U} g_T \cdot (-1)^{|S \cap T|} \\
&= 1 \cdot (-1)^{|S \cap \varnothing|} + 2 \cdot (-1)^{|S \cap a_i|} \\
&= 1 + 2 \cdot (-1)^{|S \cap a_i|} \\
\end{align*}
$$

Lúc đó, hàm $\hat{G}$ (được viết dưới dạng hàm ánh xạ) là:

$$
\hat{G}(S) = \prod_{1 \leq i \leq n} \left(1 + 2 \cdot (-1)^{|S \cap a_i|} \right)
$$

Để ý rằng tất cả các thừa số chỉ có thể nhận một trong hai giá trị:

- Nếu kích thước của $S \cap a_i$ là chẵn: thừa số tương ứng là $3$.
- Nếu kích thước của $S \cap a_i$ là lẻ: thừa số tương ứng là $-1$.

Như vậy, với mọi tập $S$ (với $S \subseteq U$), nếu ta tính được số lượng $a_i$ sao cho $|S \cap a_i|$ là chẵn/lẻ, gọi là $c_\texttt{even}$ và $c_\texttt{odd}$, công thức tính $\hat{G}(S)$ trở thành:

$$
\hat{G}(S) = 3^{c_\texttt{even}} \cdot (-1)^{c_\texttt{odd}}
$$

Sau đó, ta khôi phục hàm $G$ từ $\hat{G}$ bằng biến đổi Walsh-Hadamard ngược. Lúc này ta cũng không cần sử dụng FWHT vì ta chỉ cần $G(\varnothing)$, mà:

$$
\begin{align*}
G(\varnothing) &= \frac{1}{2^B} \cdot \sum_{T \subseteq U} \hat{G}(T) \cdot (-1)^{|\varnothing \cap T|} \\
&= \frac{1}{2^B} \cdot \sum_{T \subseteq U} \hat{G}(T)
\end{align*}
$$

Như vậy, nhiệm vụ còn lại chỉ còn là tính $c_\texttt{even}, c_\texttt{odd}$ cho mọi tập $S$.

#### Tính $c_\texttt{even}, c_\texttt{odd}$

Để ý rằng biến đổi Walsh-Hadamard trên hàm $\texttt{freq}$ (với $\texttt{freq}(S)$ là số $i$ sao cho $a_i = S$) sẽ cho ta biết hiệu $c_\texttt{even} - c_\texttt{odd}$ với mọi tập $S$. Điều này đúng vì các số mũ $|S \cap T|$ chẵn sẽ cho ra số hạng dương, và ngược lại, số mũ $|S \cap T|$ lẽ cho ra số hạng âm. Cụ thể

$$
\texttt{diff}(S) = \sum_{T \subseteq U} \texttt{freq}(T) \cdot (-1)^{|S \cap T|} = c_\texttt{even} - c_\texttt{odd}
$$

Hơn nữa, ta biết rằng $c_\texttt{even} + c_\texttt{odd}$ luôn là $n$. Từ đó, ta có thể tính $c_\texttt{even}, c_\texttt{odd}$ như sau:

$$
\begin{cases}
c_\texttt{even} = \frac{\texttt{diff}(S) + n}{2} \\
c_\texttt{odd} = n - c_\texttt{even} \\
\end{cases}
$$

Bên cạnh đó, mình cũng đã viết một lời giải tính $c_\texttt{even}, c_\texttt{odd}$ sử dụng DP SoS và tổ hợp. Bạn đọc có thể tham khảo code [tại đây](https://codeforces.com/contest/1906/submission/303040725).

#### Tổng kết & Cài đặt

Như vậy, chúng ta đã giải bài toán bằng cách xây dựng hàm sinh, tính tích các hàm sinh theo phép hiệu đối xứng theo mô hình biến đổi Walsh-Hadamard. Tuy nhiên, do sự đặc biệt của các hàm sinh, ta không dùng FWHT mà biến đổi kết hợp nhận xét để xử lý.

Từ cách tính $c_\texttt{even}, c_\texttt{odd}$ của bài toán trên, ta có thể đưa ra một nhận xét về biến đổi Walsh-Hadamard như sau:

:::success
Khi biến đổi Walsh-Hadamard trên hàm thống kê của một dãy số. Ta được hàm $f$ sao cho $f(S)$ là số phần tử khi thực hiện bitwise AND với $S$ có số bit bật chẵn trừ đi số phần tử khi thực hiện bitwise AND với $S$ có số bit bật lẻ.
:::

Thuật toán cuối cùng của chúng ta có độ phức tạp $\mathcal{O}(n + 2^B \cdot B)$ và phần cài đặt ngắn (so với lời giải) một cách bất ngờ!

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;

int add (int a, int b) { return a + b - (a + b < MOD ? 0 : MOD); }
int sub (int a, int b) { return a - b + (a - b >= 0 ? 0 : MOD); }
int mul (int a, int b) { return 1LL * a * b % MOD; }

int binpow (int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(ans, a);
    return ans;
}

vector<int> fwht (const vector<int> &f, int n) {
    vector<int> dp = f;
    for (int k = 0; k < n; k++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << k)) continue;
            int u = dp[mask], v = dp[mask ^ (1 << k)];
            dp[mask] = u + v, dp[mask ^ (1 << k)] = u - v;
        }
    }
    return dp;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    /// read input
    int n; cin >> n;
    vector<int> freq(1 << 17);

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        freq[a]++;
    }

    /// Fast Walsh-Hadamard Transform on freq
    vector<int> diff = fwht(freq, 17);

    /// Walsh-Hadamard Transform on generating functions
    int ans = 0;
    for (int mask = 0; mask < (1 << 17); mask++) {
        int even = (n + diff[mask]) >> 1, odd = n - even;
        int wht = binpow(3, even);
        if (odd & 1) wht = sub(0, wht);
        ans = add(ans, wht);
    }

    /// compute answer
    cout << mul(ans, binpow(1 << 17, MOD - 2));

    return 0;
}
```
:::

## Phụ lục

### Luyện tập thêm

- [Library Checker - Subset Convolution](https://judge.yosupo.jp/problem/subset_convolution)
- [CS Academy - And Closure](https://csacademy.com/contest/archive/task/and-closure/)
- [AtCoder 213G - Connectivity 2](https://atcoder.jp/contests/abc213/tasks/abc213_g)
- [Codechef - Winning Ways](https://www.codechef.com/NOV19A/problems/MDSWIN)

### Tham khảo

- [[Codeforces] sidhant - Tutorial on Zeta Transform, Mobius Transform and Subset Sum Convolution](https://codeforces.com/blog/entry/72488)
- [[Codeforces] maxwellzen - Some SOS DP Insights](https://codeforces.com/blog/entry/105247)
- [[Codeforces] upobir - Fast Walsh Hadamard Transforms and it's inner workings](https://codeforces.com/blog/entry/71899)
- [Nhiều tác giả - Fourier Meets Mobius: Fast Subset Convolution](https://people.csail.mit.edu/rrw/presentations/subset-conv.pdf)