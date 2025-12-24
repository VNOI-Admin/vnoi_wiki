---
title: Quy hoạch động cái túi, phần 1
description: 
published: true
date: 2025-12-21T09:16:21.388Z
tags: 
editor: markdown
dateCreated: 2025-11-27T14:24:13.740Z
---

# Quy hoạch động cái túi (DP Knapsack), phần 1

**Tác giả:**

- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

**Reviewer:**

- Nguyễn Quang Minh - Michigan State University.
- Võ Khắc Triệu - National University of Singapore.
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.
- Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN.

## Giới thiệu

**Quy hoạch động cái túi** hay **DP Knapsack** là thuật ngữ dùng để gọi chung các thuật toán dùng để xử lý lớp bài toán cái túi (knapsack problem), chủ yếu tập trung vào việc xử lý hai dạng bài toán sau:

1. **0/1 Knapsack Problem:** Cho $n$ món đồ và một giới hạn $C$, mỗi món đồ được gán trọng số và giá trị. Tìm một tập con các món đồ sao cho tổng trọng số không quá $C$ và tổng giá trị được cực đại hóa.
2. **Subset sum:** Cho $n$ món đồ và một số nguyên $C$, mỗi món đồ được gán trọng số. Kiểm tra sự tồn tại hoặc đếm số tập con các món đồ có tổng giá trị $C$.

Tùy vào yêu cầu và giới hạn các tham số của từng bài toán, ta có rất nhiều lời giải khác nhau. Trong bài viết này, mình sẽ giới thiệu đến các bạn đọc một vài thuật toán quy hoạch động cái túi tiêu biểu cũng như ứng dụng của chúng trong các bài toán Lập trình thi đấu thực tế.

Trong cả 2 phần của bài viết này, ta sẽ giả sử rằng trọng số và giá trị của các món đồ đều là **số nguyên**.

## Bài toán 0/1 Knapsack

Để bắt đầu, chúng ta cùng tìm hiểu thuật toán quy hoạch động cái túi mà gần như lập trình viên nào cũng được tìm hiểu khi bắt đầu nghiên cứu các thuật toán quy hoạch động cơ bản.

### Bài toán

#### [Đề bài](https://oj.vnoi.info/problem/atcoder_dp_d)

> Cho $n$ món đồ và một giới hạn $C$, mỗi món đồ được gán trọng số $w_i$ và giá trị $v_i$. Tìm một tập con các món đồ sao cho tổng trọng số không quá $C$ và tổng giá trị được cực đại hóa.
> 
> Nói cách khác, tìm $S \subseteq \{1, 2, \dots, n\}$ sao cho $\sum_{i \in S} w_i \leq C$ và $\sum_{i \in S} v_i$ được cực đại hóa.

#### Giới hạn

- $1 \leq n \leq 100$
- $1 \leq w_i \leq C \leq 10^5$
- $1 \leq v_i \leq 10^9$

### Xây dựng trạng thái quy hoạch động

Để xây dựng trạng thái quy hoạch động cho bài toán trên, ta xác định $3$ tham số cần quan tâm như sau:

- *Tham số chia để trị:* Phạm vi bài toán con hay số món đồ đầu tiên đang xét.
- Tổng trọng số của tập con.
- Tổng giá trị của tập con.

Với giới hạn của bài toán, ta chọn hai tham số đầu tiên để đặt trạng thái và tham số còn lại làm giá trị cần tính. Cụ thể, định nghĩa $\texttt{dp}(i, j)$ là tổng giá trị tối đa của một tập con có tổng trọng số $j$ nếu chỉ xét $i$ món đồ đầu tiên.

### Xây dựng công thức truy hồi & trường hợp cơ sở

Để tính $\texttt{dp}(i, j)$, ta tìm cách rút gọn về bài toán con chỉ xét $i - 1$ món đồ đầu tiên rồi xét riêng việc chọn hay không chọn món đồ thứ $i$. Cụ thể:

- Nếu món đồ thứ $i$ được chọn, nghĩa là tổng trọng số $j$ sẽ được chia thành $2$ phần, tổng trọng số của tập con của $i - 1$ phần tử đầu tiên là $j - w_i$ và trọng số của món đồ thứ $i$ là $w_i$. Tổng giá trị trong trường hợp này là $\texttt{dp}(i - 1, j - w_i) + v_i$.
- Nếu món đồ thứ $i$ không được chọn, nghĩa là tổng trọng số $j$ cũng chính là tổng trọng số của tập con của $i - 1$ phần tử đầu tiên. Tổng giá trị trong trường hợp này là $\texttt{dp}(i - 1, j)$.

Đến đây, ta chọn giá trị lớn hơn làm giá trị cuối cùng cho $\texttt{dp}(i, j)$. Nói cách khác, ta có công thức truy hồi:

$$
\texttt{dp}(i, j) = \max(\texttt{dp}(i - 1, j - w_i) + v_i, \texttt{dp}(i - 1, j))
$$

Trường hợp cơ sở của bài toán trên là $\texttt{dp}(0, 0) = 0$ vì giá trị của một tập rỗng là $0$, $\texttt{dp}(0, j) = -\infty$ với $j > 0$ vì ta không thể chọn một tập rỗng có giá trị khác $0$. Như vậy, công thức đầy đủ cho $\texttt{dp}(i, j)$ là:

$$
\texttt{dp}(i, j) = \begin{cases}
0 & i = j = 0 \\
-\infty & i = 0, j > 0 \\
\texttt{dp}(i - 1, j) & i > 0, j < w_i \\
\max(\texttt{dp}(i - 1, j - w_i) + v_i, \texttt{dp}(i - 1, j)) & i > 0, j \geq w_i \\
\end{cases}
$$

Đáp án cuối cùng cho bài toán là:

$$
\max_{0 \leq j \leq C} \texttt{dp}(n, j)
$$

Như vậy, ta đã đưa ra lời giải cho bài toán quy hoạch động cái túi kinh điển và cơ bản nhất với độ phức tạp $\mathcal{O}(nC)$.

### Cài đặt

Sau đây là code tham khảo cho lời giải trên theo kiểu cài đặt Top-down:

```cpp=
using ll = long long;

bool ready[110][100010];
ll dp[110][100010], w[110], v[110];

ll solve (int i, int j) {
    if (i == 0)
        return (j == 0 ? 0 : LLONG_MIN);
    if (ready[i][j]) return dp[i][j];

    ready[i][j] = 1, dp[i][j] = solve(i - 1, j);
    if (j >= w[i] && solve(i - 1, j - w[i]) != LLONG_MIN)
        dp[i][j] = max(dp[i][j], solve(i - 1, j - w[i]) + v[i]);
    return dp[i][j];
}
```

Để khử đệ quy và bỏ bảng `ready`, ta có thể chuyển sang kiểu cài đặt Bottom-up:

```cpp=
// khởi tạo bảng dp & trường hợp cơ sở
for (int i = 0; i <= n; i++)
    fill(dp[i], dp[i] + C + 1, LLONG_MIN);
dp[0][0] = 0;

// tính giá trị cho mọi trạng thái
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= C; j++) {
        dp[i][j] = dp[i - 1][j];
        if (j >= w[i] && dp[i - 1][j - w[i]] != LLONG_MIN)
            dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
    }
}

// tính đáp án cuối cùng
cout << *max_element(dp[n], dp[n] + C + 1);
```

Do sự tiện lợi cũng như hiệu quả về cả mặt thời gian và bộ nhớ, cách cài đặt này thường được ưu tiên hơn so với Top-down.

### Tối ưu bộ nhớ

#### Sử dụng mảng $2C$ phần tử

Phân tích công thức quy hoạch động như trên, ta thấy rằng việc tính toán các giá trị $\texttt{dp}(i, \dots)$ chỉ phụ thuộc vào giá trị của $\texttt{dp}(i - 1, \dots)$. Do đó, ta chỉ cần duy trì giá trị của $2$ dòng liên tiếp của bảng $\texttt{dp}$. Từ đây, ta có thể giảm độ phức tạp bộ nhớ bằng cách chỉ sử dụng bảng $\texttt{dp}$ có $2$ dòng rồi thay phiên nhau đóng vai trò là dòng được tính (dòng thứ $i$) và dòng được truy hồi (dòng thứ $i - 1$).

:::spoiler Code tham khảo 1
```cpp=
for (int i = 0; i < 2; i++)
    fill(dp[i], dp[i] + C + 1, LLONG_MIN);
dp[0][0] = 0;

for (int i = 1; i <= n; i++) {
    int t = i & 1;
    for (int j = 0; j <= C; j++) {
        dp[t][j] = dp[t ^ 1][j];
        if (j >= w[i] && dp[t ^ 1][j - w[i]] != LLONG_MIN)
            dp[t][j] = max(dp[t][j], dp[t ^ 1][j - w[i]] + v[i]);
    }
}

cout << *max_element(dp[n & 1], dp[n & 1] + C + 1);
```
:::

#### Sử dụng mảng $C$ phần tử

Ta thậm chí còn có thể bỏ hẳn một chiều của bảng `dp` bằng cách duyệt biến $j$ ngược từ $C$ về $0$. Lúc này, ta có thể hiểu rằng tại mọi thời điểm, các ô trong khoảng $[j; C]$ của mảng $\texttt{dp}$ lưu giá trị của dòng được tính còn các ô trong khoảng $[0; j - 1]$ lưu giá trị của dòng được truy hồi.

Lưu ý rằng việc duyệt $j$ từ $0$ đến $C$ sẽ cho ra giá trị sai, ta có thể quan sát ví dụ sau: do trạng thái $\texttt{dp}(i, j - w_i)$ đã được xử lý trước nên việc lấy lại ô nhớ thứ $j - w_i$ để cập nhật ô nhớ $j$ lại trở thành lấy $\texttt{dp}(i, j - w_i)$ để tính $\texttt{dp}(i, j)$.

![dp_knapsack_opt_mem_1.png](/algo/dp_/knapsack/dp_knapsack_opt_mem_1.png)

Thay vào đó, ta cần lấy $\texttt{dp}(i - 1, j - w_i)$ để tính $\texttt{dp}(i, j)$.

![dp_knapsack_opt_mem_2.png](/algo/dp_/knapsack/dp_knapsack_opt_mem_2.png)

:::spoiler Code tham khảo 2
```cpp=
fill(dp, dp + C + 1, LLONG_MIN);
dp[0] = 0; // trường hợp cơ sở

for (int i = 1; i <= n; i++)
    for (int j = C; j >= w[i]; j--)
        if (dp[j - w[i]] != LLONG_MIN)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
cout << *max_element(dp, dp + C + 1);
```
:::

Tuy có cùng độ phức tạp nhưng sau khi áp dụng các tối ưu bộ nhớ, tốc độ của thuật toán cũng được tối ưu một cách đáng kể. Cụ thể, với mấy chấm của VNOJ, độ hiệu quả (theo test có kết quả tệ nhất) của ba cách cài đặt được thể hiện qua bảng sau:

| Tiêu chí đánh giá | Top-down | Bottom-up | Bottom-up có tối ưu bộ nhớ (code tham khảo 2) |
| :-: | :-: | :-: | :-: |
| Thời gian chạy | $0,31$ giây | $0,12$ giây | $0,04$ giây |
| Bộ nhớ | $88,94$ MB | $80,16$ MB | $3,87$ MB |

### Đảo nhãn

Trong trường hợp giới hạn của trọng số lớn nhưng giá trị của các món đồ lại nhỏ (ví dụ như bài [Knapsack 2](https://oj.vnoi.info/problem/atcoder_dp_e)), ta có thể dùng tham số giá trị để đặt trạng thái còn trọng số để tính. Khi đó, hàm Quy hoạch động sẽ là $\texttt{dp}(i, j)$ là trọng số nhỏ nhất nếu chọn ra tập các món đồ có tổng giá trị $j$ từ $i$ món đồ đầu tiên.

Với định nghĩa mới, ta có công thức truy hồi như sau:

$$
\texttt{dp}(i, j) = \begin{cases}
0 & i = j = 0 \\
\infty & i = 0, j > 0 \\
\texttt{dp}(i - 1, j) & i > 0, j < v_i \\
\min(\texttt{dp}(i - 1, j), \texttt{dp}(i - 1, j - v_i) + w_i) & i > 0, j \geq v_i \\
\end{cases}
$$

Cuối cùng, ta tìm giá trị $j$ lớn nhất sao cho $\texttt{dp}(n, j) \leq C$, tức là mức giá trị lớn nhất sao cho tồn tại một cách chọn có tổng trọng số không quá $C$. Độ phức tạp của thuật toán lúc này là $\mathcal{O}(n \cdot \sum v)$.

## Bài toán Subset sum

### Bài toán

#### Đề bài

> Cho $n$ món đồ và một số nguyên $C$, mỗi món đồ được gán trọng số $w_i$. Đếm số tập con các món đồ có tổng đúng bằng $C$, modulo $10^9 + 7$.
> 
> Nói cách khác, đếm số tập $S \subseteq \{1, 2, \dots, n\}$ sao cho $\sum_{i \in S} w_i = C$, rồi in đáp án modulo $10^9 + 7$.

#### Giới hạn

- $1 \leq n \leq 100$.
- $1 \leq w_i \leq C \leq 10^5$.

### Lời giải Quy hoạch động

Với ý tưởng đặt trạng thái tương tự với bài toán 0/1 Knapsack, ta gọi $\texttt{dp}(i, j)$ là số tập con các món đồ có tổng đúng bằng $j$, nếu chỉ xét $i$ món đồ đầu tiên. Nói cách khác, $\texttt{dp}(i, j)$ là số tập $S \subseteq \{1, 2, \dots, i\}$ sao cho $\sum_{i \in S} w_i = j$. Để tìm công thức truy hồi, ta cũng xét hai trường hợp cho việc chọn hay không chọn món đồ thứ $i$:

- Nếu món đồ thứ $i$ không được chọn, tức toàn bộ tổng $j$ là của $i - 1$ món đồ đầu tiên. Số cách chọn theo trường hợp này là $\texttt{dp}(i - 1, j)$.
- Nếu món đồ thứ $i$ được chọn, tức nó đóng góp $w_i$ đơn vị vào tổng $j$, phần còn lại $j - w_i$ sẽ là của $i - 1$ món đồ đầu tiên. Số cách chọn theo trường hợp này là $\texttt{dp}(i - 1, j - w_i)$.

Kết hợp các trường hợp cơ sở, ta có công thức truy hồi:

$$
\texttt{dp}(i, j) = \begin{cases}
1 & i = j = 0 \\
0 & i = 0, j > 0 \\
\texttt{dp}(i - 1, j) & i > 0, j < w_i \\
\texttt{dp}(i - 1, j) + \texttt{dp}(i - 1, j - w_i) & i >  0, j \geq w_i \\
\end{cases}
$$

Tương tự, nếu bài toán là kiểm tra sự tồn tại của một tập con có tổng là $C$ thay vì đếm số tập, ta có thể thay đổi công thức truy hồi như sau:

$$
\texttt{exist}(i, j) = \begin{cases}
\text{true} & i = j = 0 \\
\text{false} & i = 0, j > 0 \\
\texttt{exist}(i - 1, j) & i > 0, j < w_i \\
\texttt{exist}(i - 1, j) \lor \texttt{exist}(i - 1, j - w_i) & i >  0, j \geq w_i \\
\end{cases}
$$

Với $\lor$ là ký hiệu của phép [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Tương tự lời giải cho bài toán 0/1 Knapsack như trên, độ phức tạp của thuật toán này là $\mathcal{O}(nC)$.

### Cài đặt

```cpp=
dp[0] = 1;
for (int i = 1; i <= n; i++)
    for (int j = C; j >= w[i]; j--)
        dp[j] += dp[j - w[i]]; // thêm modulo khi cần
cout << dp[C];
```

### Tối ưu bài toán kiểm tra sự tồn tại

#### Đề bài

> Cho $n$ món đồ và một số nguyên $C$, mỗi món đồ được gán trọng số $w_i$. Kiểm tra sự tồn tại của một tập con các món đồ có tổng đúng bằng $C$.
> 
> Nói cách khác, kiểm tra xem có tồn tại một tập $S \subseteq \{1, 2, \dots, n\}$ sao cho $\sum_{i \in S} w_i = C$ hay không.

#### Giới hạn (thay đổi)

- $1 \leq n \leq 10^6$
- $1 \leq w_i \leq 10^6$
- $1 \leq C \leq \sum w_i \leq 2 \cdot 10^6$

#### Tối ưu 1

Xét các truy hồi trên dòng thứ $i$ của bảng Quy hoạch động, ta thấy mọi ô ở dòng $i$ cột $j$ đều lấy giá trị từ dòng $i - 1$ cột $j$ và $j - w_i$ theo công thức truy hồi $\texttt{exist}(i - 1, j) \lor \texttt{exist}(i - 1, j - w_i)$:

![dp_transition.png](/algo/dp_/knapsack/dp_transition.png)

Điều này cũng tương tự với việc dịch chuyển toàn bộ các phần tử của $\texttt{dp}_{i-1}$ sang phải $w_i$ lần, rồi thực hiện bitwise OR với các phần tử ban đầu:

![bitset_transition.png](/algo/dp_/knapsack/bitset_transition.png)

Nếu lưu mỗi dòng của bảng Quy hoạch động dưới dạng cấu trúc dữ liệu [`bitset`](http://www.en.cppreference.com/w/cpp/utility/bitset.html), ta có thể biến đổi thao tác dịch chuyển các phần tử thành phép dịch bit sang trái. Khi đó, công thức truy hồi là:

$$
\texttt{dp}_i = \texttt{dp}_{i-1} \mid (\texttt{dp}_{i-1} \mathrel{\texttt{<<}} w_i)
$$

Việc sử dụng cấu trúc dữ liệu `bitset` sẽ giúp giảm cả độ phức tạp thời gian lẫn bộ nhớ xuống $32$ hoặc $64$ lần.

:::spoiler Code tham khảo 3
```cpp=
bitset<2'000'001> exist;
exist.set(0); // gán exsit[0] = 1, trường hợp cơ sở
for (int u : w)
    exist |= (exist << u);
cout << exist[C];
```
:::

#### Tối ưu 2

Xét hai danh sách món đồ $[1, 1, 1, 1, 1, 1, 1]$ ($7$ phần tử) và danh sách $[1, 2, 4]$ ($3$ phần tử), cả hai đều có thể tạo ra mọi số nguyên từ $1$ đến $7$ bằng cách lấy tổng một tập con bất kỳ. Tuy nhiên, danh sách thứ hai lại có số phần tử chưa đến một nửa danh sách đầu tiên.

Từ đó, ta có thể đưa ra ý tưởng rút gọn một số phần tử trong danh sách món đồ mà vẫn không ảnh hưởng kết quả của bài toán. Cụ thể, với một giá trị $w$ bất kỳ xuất hiện $3$ lần, ta thay $3$ phần tử này thành $1$ phần tử $w$ và $1$ phần tử $2w$.

:::spoiler Chứng minh
Với một danh sách $A$ có giá trị $w$ xuất hiện tối thiểu $3$ lần, ta tách chúng ra thành hai danh sách con $A_1 = [w, w, w]$ và danh sách $A_2$ là phần còn lại. Gọi $g(B)$ là tập các tổng tập con của dãy $B$. Dễ thấy

$$
g(A) = g(A_1) + g(A_2)
$$

Với phép $+$ hai tập hợp là ký hiệu của [tổng Minkowski](https://en.wikipedia.org/wiki/Minkowski_addition).

Mặt khác, ta có:

$$
g([w, w, w]) = g([w, 2w]) = \{0, w, 2w, 3w\}
$$

Do đó:

$$
g(A) = g(A_1) + g(A_2) = g([w, 2w]) + g(A_2)
$$
:::

Sau các bước biến đổi, chúng ta còn lại một mảng có độ dài $\mathcal{O}(\sqrt{S})$ với $S = \sum w$.

:::spoiler Chứng minh
Dễ thấy, nếu có một giá trị xuất hiện ít nhất $3$ lần, nghĩa là các bước biến đổi vẫn chưa được thực hiện xong. Do đó, ta có thể chắc chắn rằng một giá trị chỉ xuất hiện ít nhất $2$ lần. Khi đó, tổng của một danh sách món đồ phải có giá trị tối thiểu là:

$$
2 \cdot \left(1 + 2 + 3 + \dots + \frac{n}{2} \right)
$$

Nói cách khác:

$$
\begin{align*}
1 + 2 + 3 + \dots + \frac{n}{2} &\leq \frac{S}{2} \\
\Longleftrightarrow \frac{\frac{n}{2} \cdot (\frac{n}{2} + 1)}{2} &\leq \frac{S}{2} \\
\Longrightarrow \left( \frac{n}{2} \right)^2 &\leq S \\
\Longrightarrow n &\leq 2 \sqrt{S}
\end{align*}
$$

Do đó, cận trên của độ dài mảng là $2 \sqrt{S}$.
:::

Để thực hiện thao tác biến đổi danh sách món đồ thuận tiện hơn, ta sử dụng thuật toán sau: Ta duy trì mảng thống kê $f$ của dãy $w$ rồi duyệt mọi mức trọng lượng từ $1$ đến $S$. Với mức trọng lượng $i$ nào đó, đặt:

$$
\Delta = \left\lfloor \frac{f_i - 1}{2} \right\rfloor
$$

Ta thực hiện xóa đi $2\Delta$ phần tử có trọng lượng $i$ rồi thêm $\Delta$ phần tử có trọng lượng $2i$, sau đó, đưa các phần tử có trọng lượng $i$ còn lại vào danh sách món đồ mới.

:::spoiler Code tham khảo 4
```cpp=
// chuẩn bị mảng thống kê
for (int u : components) cnt[u]++;
exist.set(0);
         
for (int i = 1; i <= S; i++) {
    if (!cnt[i]) continue;
    int delta = (cnt[i] - 1) / 2;
    cnt[i] -= (delta * 2);
    if (i * 2 <= S) cnt[i * 2] += delta;
    for (int j = 0; j < cnt[i]; j++) exist |= (exist << i);
}
```
:::

Như vậy, ta đã có thuật toán Quy hoạch động tối ưu với độ phức tạp $\mathcal{O} \left( \frac{C \sqrt{S}}{64} \right)$.

### Bỏ phần tử với bài toán đếm

Giả sử ta cần xử lý bài toán Subset Sum theo dạng "online" với ba loại truy vấn sau:

1. Thêm một phần tử có trọng số $w$ vào cái túi.
2. Bỏ một phần tử có trọng số $w$ khỏi cái túi.
3. Cho biết số tập con có tổng đúng bằng $j \leq C$.

Với thao tác thêm, ta thực hiện tương tự ý tưởng Quy hoạch động cái túi được trình bày như trên:

```cpp=
for (int j = C; j >= weight; j--)
    dp[j] += dp[j - weight]; // thêm modulo khi cần
```

Đối với thao tác bỏ phần, để ý rằng thứ tự thêm các món đồ vào cái túi không ảnh hưởng đến kết quả bài toán, do đó, ta giả sử phần tử cần bỏ cũng là phần tử cuối cùng được thêm. Khi đó, ta chỉ cần thiết kế thao tác "undo" -- hủy bỏ thay đổi của vòng lặp trên:

```cpp=
for (int j = weight; j <= C; j++)
    dp[j] -= dp[j - weight]; // thêm modulo khi cần
```

> **Lưu ý khi cài đặt**
>
> Đối với các bài toán đếm liên quan đến Subset Sum, ta thường được yêu cầu in ra đáp án modulo một số nguyên tố (như $10^9 + 7$ hoặc $998 \space 244 \space 353$). Do đó, quá trình tính toán Quy hoạch động sẽ gọi toán tử modulo rất nhiều. Điều này có thể làm chậm tốc độ của chương trình.
>
> Ta thường phải khử phép modulo bằng cách:
> - Viết hàm `add(a, b)` và `sub(a, b)` để tính $(a + b) \bmod \texttt{MOD}$ và $(a - b) \bmod \texttt{MOD}$ với $0 \leq a, b < \texttt{MOD}$ (chỉ sử dụng phép cộng/trừ và `if`/`else`).
> - Sử dụng `ModInt`, bạn đọc có thể tham khảo [template này](https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/modint.h).

## Bài tập ứng dụng

### [Singapore NOI 2018 - Knapsack](https://oj.uz/problem/view/NOI18_knapsack) (0/1 Knapsack có bản sao)

#### Đề bài

> Cho $n$ loại món đồ và một giới hạn $C$, loại thứ $i$ có trọng lượng $w_i$, giá trị $v_i$ và số lượng $k_i$. Tìm một tập con các món đồ sao cho tổng trọng số không quá $C$ và tổng giá trị đạt cực đại.
> 
> Nói cách khác, tìm một dãy $a_1, a_2, \dots, a_n$ sao cho $0 \leq a_i \leq k_i$ với mọi $1 \leq i \leq n$, $\sum_{1 \leq i \leq n} a_i \cdot w_i \leq C$ và $\sum_{1 \leq i \leq n} a_i \cdot v_i$ đạt cực đại.

#### Giới hạn

- $1 \leq n \leq 10^5$
- $1 \leq w_i \leq C \leq 2000$
- $1 \leq v_i \leq 10^6$
- $1 \leq k_i \leq 10^9$

*(Lưu ý, biến $S$ trong đề bài gốc đã được thay thế thành biến $C$ để đồng nhất với cách đặt tên biến trong bài viết này)*

#### Lời giải quy về quy hoạch động cái túi kinh điển

Nhận xét rằng với mỗi mức cân nặng $w$, ta chỉ có thể chọn tối đa $\left\lfloor \frac{C}{w} \right\rfloor$ món đồ. Hơn nữa, khi đã cố định các một mức cân nặng, ta chỉ việc tham lam chọn món đồ có giá trị lớn nhất. Nói cách khác, với mỗi mức cân nặng $w$, món đồ có giá trị lớn thứ $\left\lfloor \frac{C}{w} \right\rfloor + 1$ trở đi sẽ không bao giờ được chọn vào tập tối ưu.

Dựa vào nhận xét trên, ta "lọc" lại các món đồ và chỉ xét các *món đồ tiềm năng*, tức $\left\lfloor \frac{C}{w} \right\rfloor$ món đồ có giá trị lớn nhất với mỗi mức cân nặng $w$. Khi đó, số món đồ ta cần xét chỉ còn:

$$
\left\lfloor \frac{C}{1} \right\rfloor + \left\lfloor \frac{C}{2} \right\rfloor + \left\lfloor \frac{C}{1} \right\rfloor + \dots + \left\lfloor \frac{C}{C} \right\rfloor = \mathcal{O}(C \log C)
$$

Khi đó, nếu thực hiện quy hoạch động trên tập *món đồ tiềm năng*, độ phức tạp thời gian sẽ là $\mathcal{O}(C^2 \log C)$.

:::spoiler Code tham khảo 5
```cpp=
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll,ll>;
using pii = pair<int,int>;
using tpl = tuple<int,int,int>;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int mn = 1e5 + 5;
ll V[mn], W[mn], K[mn], dp[2020], used[2020];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int S, n; cin >> S >> n;
    for (int i = 1; i <= n; i++) cin >> V[i] >> W[i] >> K[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(all(ord), [&] (int a, int b) { return V[a] > V[b]; });

    int t = 0, counter = 0;
    for (int i : ord) {
        for (int iter = 0; iter < K[i]; iter++) {
            if (used[W[i]] * W[i] > S) break;
            for (int j = S; j >= W[i]; j--)
                dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
            used[W[i]]++;
        }
    }
    cout << dp[S];

    return 0;
}
```
:::

#### Lời giải sử dụng deque trick

Tuy nhiên, trong trường hợp giới hạn của $C$ lớn (ví dụ, $1 \leq C \leq 10^5$ và $1 \leq n \leq 200$), cách làm như trên là chưa hợp lý. Thay vào đó, ta có thể xử lý bài toán trên với lời giải thứ hai đó là sử dụng kỹ thuật [tìm max-min trong đoạn tịnh tiến](https://wiki.vnoi.info/vi/algo/data-structures/deque-min-max) hay deque trick.

Vẫn giữ nguyên cách đặt trạng thái $\texttt{dp}(i, j)$ là tổng giá trị lớn nhất có thể đạt được nếu chọn tập có tổng trọng lượng $j$ và chỉ xét $i$ loại đồ đầu tiên. Nếu chọn $a$ (với $1 \leq a \leq k_i$) món đồ cho loại đồ thứ $i$, tổng giá trị tối đa mà ta có là $\texttt{dp}(i - 1, j - w_i \cdot a) + v_i \cdot a$. Do đó, công thức truy hồi trong trường hợp này là:

$$
\texttt{dp}(i, j) = \max_{1 \leq a \leq k_i} \left( \texttt{dp}(i - 1, j - w_i \cdot a) + v_i \cdot a \right)
$$

Để đơn giản hóa bài toán, ta tạm bỏ qua giới hạn $k_i$. Khi đó, với mỗi trạng thái $(i, j)$ trên bảng quy hoạch động, ta truy hồi về các trạng thái trên dòng $i - 1$, cột $j - w_i, j - 2w_i, j - 3w_i, \dots$ tức các cột có chỉ số đồng dư với $j$ theo modulo $w_i$.

![dp_transition_2.png](/algo/dp_/knapsack/dp_transition_2.png)

Như vậy, ta có thể biến đổi công thức lại thành:

$$
\texttt{dp}(i, j) = \max_{\substack{u \equiv j \pmod {w_i} \\ u \leq j}} \left( \texttt{dp}(i - 1, u) + v_i \cdot \left( \left\lfloor \frac{j}{w_i} \right\rfloor - \left\lfloor \frac{u}{w_i} \right\rfloor \right) \right)
$$

Tách công thức độc lập theo $j, u$, ta có:

$$
\texttt{dp}(i, j) = v_i \cdot \left\lfloor \frac{j}{w_i} \right\rfloor + \max_{\substack{u \equiv j \pmod {w_i} \\ u \leq j}} \left( \texttt{dp}(i - 1, u) - v_i \cdot \left\lfloor \frac{u}{w_i} \right\rfloor \right)
$$

Như vậy, ý tưởng chung của thuật toán là với mọi $i$, ta chia các trạng thái quy hoạch động ở dòng $i - 1$ thành $w_i$ theo modulo $w_i$. Ở nhóm thứ $j$, ta tạo dãy gồm các giá trị $\delta_{i-1}(t)$ sao cho $t \equiv j \pmod {w_i}$ và:

$$
\delta_i(t) = \texttt{dp}(i, t) - v_{i+1} \cdot \left\lfloor \frac{t}{w_{i+1}} \right\rfloor
$$

Để tính $\texttt{dp}(i, j)$, xét nhóm thứ $j \bmod w_i$, ta tính giá trị $\delta$ nhỏ nhất của đoạn con liên tiếp có độ dài $k_i + 1$ kết thúc tại phần tử có chỉ số (theo cột của bảng quy hoạch động) là $j$. Để hỗ trợ tính toán giá trị nhỏ nhất của các đoạn tịnh tiến, ta sử dụng deque trick giúp truy vấn trong $\mathcal{O}(1)$.

Như vậy, ta đã có một lời giải khác cho bài toán nêu trên có độ phức tạp $\mathcal{O}(nC)$.

:::spoiler Code tham khảo 6
Lưu ý, đây chỉ là lời giải đạt $73$ điểm trên nền tảng oj.uz do giới hạn của bài tập không thích hợp với độ phức tạp thuật toán.

```cpp=
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll,ll>;
using pii = pair<int,int>;
using tpl = tuple<int,int,int>;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int mn = 1e5 + 5;
ll V[mn], W[mn], K[mn], dp[2][2020], used[2020];

struct dqTrick {
    deque<ll> dq;

    void push (ll x) {
        while (dq.size() && dq.back() < x) dq.pop_back();
        dq.push_back(x);
    }

    void pop (ll x) {
        if (dq.size() && dq.front() == x) dq.pop_front();
    }

    ll best() { return (dq.empty() ? LLONG_MIN : dq.front()); }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int S, n; cin >> S >> n;
    for (int i = 1; i <= n; i++) cin >> V[i] >> W[i] >> K[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(all(ord), [&] (int a, int b) { return V[a] > V[b]; });

    int t = 0;
    for (int i : ord) {
        if (used[W[i]] * W[i] > S) continue;
        vector<dqTrick> opt(W[i]);
        for (int j = 0; j <= S; j++) {
            int R = j % W[i], D = j / W[i];
            opt[R].push(dp[t ^ 1][j] - D * V[i]);
            if (j >= W[i] * (K[i] + 1))
                opt[R].pop(dp[t ^ 1][j - W[i] * (K[i] + 1)] - (D - K[i] - 1) * V[i]);

            dp[t][j] = opt[R].best() + D * V[i];
        }
        t ^= 1, used[W[i]] += K[i];
    }
    cout << dp[t ^ 1][S];

    return 0;
}
```
:::

### [Codeforces 755F - PolandBall and Gifts](https://codeforces.com/contest/755/problem/F)

#### Giới hạn

Cho một hoán vị $p$ độ dài $n$ và một số nguyên $k$, đảm bảo $p_i \neq i$ với mọi $1 \leq i \leq n$. Biết rằng sẽ có $k$ phần tử bị xóa đi (không đánh số lại các phần tử chưa bị xóa). Ta gọi phần tử thứ $i$ là đặc biệt khi thỏa đồng thời:

- Phần tử thứ $i$ chưa bị xóa.
- Phần tử thứ $x$ thỏa $p_x = i$ chưa bị xóa.

Đếm số phần tử **không** đặc biệt **ít nhất** và **nhiều nhất** ($2$ yêu cầu riêng biệt) khi xóa $k$ phần tử của hoán vị $p$.

#### Giới hạn

- $2 \leq n \leq 10^6$
- $0 \leq k \leq n$

#### Biến đổi thành đồ thị

Với mọi phần tử $i$, ta dựng cạnh có hướng $i \rightarrow p_i$. Khi đó, ta có một đồ thị mà mỗi thành phần liên thông là một chu trình. Do sự độc lập giữa các thành phần liên thông, với cả hai yêu cầu, ta sẽ xử lý riêng từng thành phần liên thông rồi kết hợp các kết quả lại với nhau.

Lúc này, bài toán của chúng ta là cho một chu trình gồm $n$ đỉnh. Tìm cách xóa $k$ cạnh sao cho số đỉnh không có cạnh vào/ra là ít nhất và nhiều nhất.

#### Bài toán cực đại hóa

Ta sẽ lần lượt giải quyết từng yêu cầu của bài toán, bắt đầu với yêu cầu cực đại hóa số đỉnh không có cạnh vào/ra. Dễ thấy, ta có thể tham lam xóa/giữ các cạnh xen kẽ nhau để có phương án tối ưu.

Ví dụ, với chu trình gồm $7$ đỉnh, thứ tự xóa cạnh sau là tối ưu:

![del_edge.png](/algo/dp_/knapsack/del_edge.png)

Cụ thể hơn, xét một chu trình gồm $n$ đỉnh, khi xóa $\left\lfloor \frac{n}{2} \right\rfloor$ cạnh đầu tiên, ta xóa được $2$ đỉnh đặc biệt cho mỗi cạnh. Với $n \bmod 2$ cạnh tiếp theo, ta xóa được $1$ đỉnh đặc biệt cho mỗi cạnh. Các cạnh còn lại không đóng góp gì vào đáp án.

Gọi cạnh loại $x$ là cạnh mà khi xóa đi sẽ kéo theo $x$ đỉnh đặc biệt bị xóa. Ta thống kê được số cạnh loại $1$ và $2$ cho cả đồ thị và đặt là $c_1, c_2$. Sau đó, tiếp tục sử dụng tham lam và xóa $\min(k, c_2)$ cạnh loại $2$ và $\min(c_1, k - \min(k, c_2))$ cạnh loại $1$.

Như vậy, yêu cầu này có thể được xử lý trong $\mathcal{O}(n)$.

#### Bài toán cực tiểu hóa

Đối với bài toán cực tiểu hóa, ta lại dùng ý tưởng tham lam nhưng lần này, ta sẽ xóa các cạnh liên tiếp. Với chiến lược đó, mỗi thành phần liên thông sẽ có đúng $1$ cạnh loại $2$, $n - 2$ cạnh loại $1$ và có $1$ cạnh loại $0$.

Một nhận xét quan trọng đó là một khi đã bắt đầu xóa cạnh cho một thành phần liên thông nào đó, ta sẽ tiến hành xóa tại thành phần liên thông đó cho đến khi hết cạnh. Lý do là số đỉnh đặc biệt bị xóa đi không tăng lên khi ta tiếp tục xóa tại một thành phần liên thông nào đó.

Như vậy, ta xét hai trường hợp:
- Nếu xóa được hết các cạnh thuộc các thành phần liên thông mà ta chọn để xóa, đáp án sẽ là $k$.
- Nếu có một thành phần liên thông đang bị xóa dang dở, đáp án sẽ là $k + 1$.

Để kiểm tra trường hợp, ta lại quy bài toán đồ thị thành bài toán cái túi: mỗi thành phần liên thông được xem như một món đồ có trọng số bằng số đỉnh của nó. Nhiệm vụ của chúng ta là kiểm tra xem tồn tại một tập các thành phần liên thông có tổng số đỉnh là $k$ hay không.

Với thuật toán kết hợp hai tối ưu đã được trình bày ở phần Subset Sum, ta có thể xử lý yêu cầu này trong $\mathcal{O}\left( n + \frac{k \sqrt{n}}{64} \right)$.

#### Cài đặt

Để dễ dàng tách biệt các code xử lý hai yêu cầu khác nhau, mình sẽ sử dụng `namespace`. Ở mỗi `namespace`, mình cài đặt một hàm `solve` nhận vào danh sách kích thước các thành phần liên thông và trả về đáp án.

:::spoiler Code tham khảo 7
```cpp=
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll,ll>;
using pii = pair<int,int>;
using tpl = tuple<int,int,int>;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int mn = 1e6 + 6;
bool vis[mn];
int p[mn], n, k;

namespace solveMin {
    bitset<mn> exist;
    int cnt[mn];

    int solve (const vector<int> &components) {
        for (int u : components) cnt[u]++;
        exist.set(0);
        
        for (int i = 1; i <= n; i++) {
            if (!cnt[i]) continue;
            int merged = (cnt[i] - 1) >> 1;
            cnt[i] -= (merged << 1);
            if ((i << 1) <= n) cnt[i << 1] += merged;
            for (int j = 0; j < cnt[i]; j++) exist |= (exist << i);
        }

        return k + (exist[k] == 0);
    }
};

namespace solveMax {
    int solve (const vector<int> &components) {
        vector<int> cnt(3);
        for (int u : components)
            cnt[2] += u >> 1, cnt[1] += u & 1;

        int pickTwo = min(cnt[2], k);
        return (pickTwo << 1) + min(cnt[1], k - pickTwo);
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> p[i];

    // thực hiện DFS khử đệ quy trên đồ thị hàm
    vector<int> components;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int counter = 0;
        for (int node = i; !vis[node]; node = p[node]) counter++, vis[node] = 1;
        components.push_back(counter);
    }

    cout << solveMin::solve(components) << " "
         << solveMax::solve(components) << "\n";

    return 0;
}
```
:::


## Phụ lục

### Luyện tập thêm

- [VNOJ, Cái túi 2](https://oj.vnoi.info/problem/dttui2)
- [MarisaOJ, Knapsack](https://marisaoj.com/problem/554)
- [2016 USP Try-outs, The Knapsack Problem](https://codeforces.com/gym/101064/problem/L)
- [AtCoder Beginner Contest 221, Jumping Sequence](https://atcoder.jp/contests/abc221/tasks/abc221_g)
- [VNOI Cup 2024, Round 2, Love Charm](https://oj.vnoi.info/problem/vnoicup24_r2_d)
- [JOI 2019, Growing Vegetable is Fun 3](https://oj.uz/problem/view/JOI19_ho_t3)
- [USACO Platinum, Exercise](https://usaco.org/index.php?page=viewproblem2&cpid=1045)


### Tài liệu tham khảo

- [Ashley Khoo (errorgorn). [Tutorial] Knapsack, Subset Sum and the (max, +) Convolution, 2022.](https://codeforces.com/blog/entry/98663)
- [Võ Khắc Triệu. DeMen Blog #2: Bài toán Knapsack và các biến thể (Phần 1). 2023.](https://hackmd.io/@DeMen100ms/DeMenBlog2)
- [Bùi Minh Hoạt, Nguyễn Châu Khanh. Hàng đợi hai đầu (deque) và Bài toán tìm max-min trong đoạn tịnh tiến (VNOI). 2023.](https://wiki.vnoi.info/vi/algo/data-structures/deque-min-max)


