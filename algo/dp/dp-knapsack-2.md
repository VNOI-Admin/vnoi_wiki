---
title: Quy hoạch động cái túi, phần 2
description: 
published: true
date: 2025-12-21T09:21:38.161Z
tags: 
editor: markdown
dateCreated: 2025-11-27T14:26:54.031Z
---

# Quy hoạch động cái túi (DP Knapsack), phần 2

**Tác giả:**

- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

**Reviewer:**

- Nguyễn Quang Minh - Michigan State University.
- Võ Khắc Triệu - National University of Singapore.
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.
- Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN.

## Giới thiệu

Trong phần 1 của bài viết này, ta đã tìm hiểu một số lời giải cơ bản và phổ biến của hai bài toán **0/1 Knapsack** và **Subset Sum** của lớp bài toán cái túi.

Trong phần này, chúng ta sẽ tìm hiểu thêm hai thuật toán cải tiến các bài toán nêu trên.

## Bài toán Subset sum trên tập số nguyên liên tiếp

Khi xử lý bài toán kiểm tra sự tồn tại của một tập con có tổng $C$ trên tập số nguyên liên tiếp, ta hoàn toàn có thể dùng thuật toán tham lam để giải trong $\mathcal{O}(1)$. Do đó, trong phần này, ta chỉ tập trung vào bài toán đếm số tập con có tổng $C$.

### Bài toán không có cận

#### Đề bài

> Cho số nguyên $C$, đếm số tập con của tập số tự nhiên có tổng là $C$.

Giới hạn:
- $1 \leq C \leq 10^5$

#### Thuật toán $\mathcal{O}(C^2)$

Nếu áp dụng thuật toán quy hoạch động truyền thống với $\texttt{dp}(i, j)$ là số tập con của $\{1, 2, \dots, i\}$ có tổng là $j$, ta có thuật toán có độ phức tạp $\mathcal{O}(C^2)$ với công thức truy hồi là:

$$
\texttt{dp}(i, j) = \texttt{dp}(i - 1, j) + \texttt{dp}(i - 1, j - i)
$$

Tuy nhiên, với giới hạn $C \leq 10^5$, đây rõ ràng là một lời giải chưa tối ưu.

#### Thay đổi hướng tiếp cận

Đối với các dạng quy hoạch động cái túi được nêu trên, ta có thể hình dung mô hình bài toán đang là tuần tự thêm phần tử vào **cuối dãy trạng thái**. Nói cách khác, ta mở rộng từ trạng thái $x_1, x_2, \dots, x_i$ sang $x_1, x_2, \dots, x_i, x_{i+1}$ (với $x_i \in \{0, 1\}$ cho biết món đồ thứ $i$ được chọn hay không chọn). Tuy nhiên, với bài toán nêu trên, ta có thể tận dụng tính **liên tiếp** của tập số để tuần tự thêm phần tử vào **đầu dãy trạng thái**, sau đó đánh số lại toàn bộ dãy.

Ví dụ, với tập $\{2, 4, 5\}$ ứng với dãy trạng thái $[0, 1, 0, 1, 1]$. Nếu thêm trạng thái mới vào cuối dãy, ta có:

- Dãy $[0, 1, 0, 1, 1, 0]$ ứng với tập $\{2, 4, 5\}$.
- Dãy $[0, 1, 0, 1, 1, 1]$ ứng với tập $\{2, 4, 5, 6\}$.

Tuy nhiên, với việc thêm trạng thái mới vào đầu dãy, ta có hai tập mới là $\{3, 5, 6\}$ và $\{1, 3, 5, 6\}$.

![state_prepend.png](/algo/dp_/knapsack/state_prepend.png)

Nói một cách toán học hơn, từ tập $S = \{1\}$, ta sẽ sinh ra tất cả các tập số tự nhiên khác rỗng theo hai thao tác sau:

- Gán $S \leftarrow S + 1$, tức thêm trạng thái **không chọn** vào đầu dãy trạng thái.
- Gán $S \leftarrow (S + 1) \cup \{1\}$, tức thêm trạng thái **chọn** vào đầu dãy trạng thái.

Ở đây, ta định nghĩa phép cộng một tập hợp với một số nguyên $S + x$ cho ra tập hợp:

$$
S' = \{u + x \mid u \in S\}
$$

#### Ý tưởng quy hoạch động

Lúc này, với mọi tập số tự nhiên, ta chỉ cần quan tâm hai tham số là tổng các giá trị thuộc tập (ký hiệu $\sigma$) và kích thước của tập (ký hiệu $\ell$). Khi áp dụng các thao tác nêu trên, hai tham số này thay đổi như sau:

- Khi áp dụng thao tác gán $S \leftarrow S + 1$ lên các tập có tổng $\sigma$ và kích thước $\ell$, chúng sẽ biến thành các tập có tổng $\sigma + \ell$ và kích thước $\ell$. Ví dụ, với tập $S = \{2, 3, 5\}$ có tổng $\sigma = 10$ và kích thước $\ell = 3$, thao tác này sẽ tạo ra tập $S' = \{3, 4, 6\}$ có tổng $\sigma + \ell = 13$ và kích thước giữ nguyên.
- Khi áp dụng thao tác gán $S \leftarrow (S + 1) \cup \{1\}$ lên các tập có tổng $\sigma$ và kích thước $\ell$, chúng sẽ biến thành các tập có tổng $\sigma + \ell + 1$ và kích thước $\ell + 1$. Ví dụ, với tập $S = \{2, 3, 5\}$ có tổng $\sigma = 10$ và kích thước $\ell = 3$, thao tác này sẽ tạo ra tập $S' = \{1, 3, 4, 6\}$ có tổng $\sigma + \ell + 1 = 14$ và kích thước $\ell + 1 = 4$.

Từ đó, ta có thể đặt $\texttt{dp}(\sigma, \ell)$ (với $\sigma \geq \ell \geq 1$) là số tập số tự nhiên có tổng giá trị là $\sigma$ và kích thước là $\ell$. Để lập công thức truy hồi, ta có thể suy ngược lại:

- Với các tập không chứa phần tử $1$, ta có $\texttt{dp}(\sigma - \ell, \ell)$ tập hợp như vậy.
- Với các tập chứa phần tử $1$, ta có $\texttt{dp}(\sigma - \ell, \ell - 1)$ tập hợp như vậy.

Như vậy, ta có:

$$
\texttt{dp}(\sigma, \ell) = \begin{cases}
1 & \sigma = \ell = 1 \\
\texttt{dp}(\sigma - \ell, \ell) + \texttt{dp}(\sigma - \ell, \ell - 1) & \sigma, \ell > 1
\end{cases}
$$

#### Độ phức tạp

Thoạt nhìn qua, ta có cảm giác như lời giải này cũng có độ phức tạp $\mathcal{O}(C^2)$ như lời giải trước đó. Tuy nhiên, dựa vào nhận xét rằng với mọi tập số nguyên, tổng $\sigma$ của nó tối thiểu là $1 + 2 + \dots + \ell$, tức là:

$$
\begin{align*}
1 + 2 + \dots + \ell &\leq \sigma \\
\Longleftrightarrow \frac{\ell(\ell+1)}{2} &\leq \sigma \\
\Longrightarrow \ell^2 &\leq 2 \sigma \\
\Longrightarrow \ell &\leq \sqrt{2 \sigma} \\
\end{align*}
$$

Như vậy, kích thước của một tập con không thể vượt quá căn bậc hai của hai lần tổng của nó. Nói cách khác, số trạng thái mà ta cần xét trong thuật toán quy hoạch động này là $\mathcal{O}(C \sqrt{C})$ -- đủ để xử lý giới hạn $10^5$.

:::spoiler Code tham khảo
Trước tiên, ta khai báo hai hàm giúp tính phép cộng có modulo và kiểm tra tính hợp lệ của một trạng thái như sau:

```cpp=
const int MOD = 1e9 + 7;

int add (int a, int b) {
    return a + b - (a + b < MOD ? 0 : MOD);
}

bool validState (int sigma, int len) {
    return 1LL * len * len <= 2 * sigma;
}
```

Sau đó, thuật toán nêu trên có thể được cài đặt như sau:

```cpp=
int C; cin >> C;
vector<vector<int>> dp(C + 1);

dp[1] = {0, 1};
for (int sigma = 2; sigma <= C; sigma++) {
    dp[sigma].push_back(0); // phần tử đệm
    for (int len = 1; validState(sigma, len); len++) {
        int cur = 0;
        if (validState(sigma - len, len))
            cur = add(cur, dp[sigma - len][len]);
        if (validState(sigma - len, len - 1))
            cur = add(cur, dp[sigma - len][len - 1]);
        dp[sigma].push_back(cur);
    }
}

int ans = 0;
for (int len = 1; validState(C, len); len++) ans = add(ans, dp[C][len]);
cout << ans;
```
:::

### Bài toán có cận dưới

#### Đề bài

> Cho hai số nguyên $C$ và $L$, đếm số tập con của tập số $\{L, L + 1, L + 2, \dots\}$ có tổng là $C$.

Giới hạn:
- $1 \leq C, L \leq 10^5$

#### Ý tưởng

Khi bài toán có cận dưới, ta có thể xử lý theo một trong hai hướng sau:
- Biến đổi thao tác sinh tập số thành $S \leftarrow S + 1$ và $S \leftarrow (S + 1) \cup \{L\}$. Sau đó bắt đầu sinh với tập $S = \{L\}$.
- Với tập số có kích thước $\ell$, ta giảm toàn bộ các phần tử xuống $L - 1$ đơn vị. Nói cách khác, ta sử dụng thuật toán không có cận dưới nhưng tìm các tập số có tổng là $C - \ell \cdot (L - 1)$.

### Bài toán có cận trên

#### Đề bài

> Cho hai số nguyên $C$ và $n$, đếm số tập con của tập số $\{1, 2, 3, \dots, n\}$ có tổng là $C$.

Giới hạn:
- $1 \leq C, n \leq 10^5$.

#### Ý tưởng

Với việc đặt trạng thái bằng cặp $(\sigma, \ell)$, ta không thể quản lý được giới hạn (cận trên) của tập số đang được tính trong hàm quy hoạch động. Cụ thể, với tập số có chứa $n$, việc áp dụng thao tác $S \leftarrow S + 1$ sẽ sinh ra tập có chứa phần tử $n + 1$.

Cách giải quyết vấn đề này chính là **bù trừ**. Giả sử ta có trạng thái $(\sigma, \ell)$ đang tính dư các tập chứa phần tử $n + 1$, ta cần trừ đi số tập dư. Mặt khác, ta biết rằng số tập có tổng $\sigma$, kích thước $\ell$ chứa phần tử $n + 1$ cũng chính là số tập có tổng $\sigma - n - 1$, kích thước $\ell - 1$ không chứa phần tử $n + 1$, hay chính là $\texttt{dp}(\sigma - n - 1, \ell - 1)$.

Lý do ta chỉ cần bù trừ các tập chứa phần tử $n + 1$ là với cách làm như trên, ta luôn duy trì các tập trong khoảng $[1; n]$. Trong quá trình thực hiện các thao tác nêu trên, phần tử vượt giới hạn duy nhất được sinh ra là $n + 1$ và bị loại ngay lập tức.

Từ đó, ta điều chỉnh công thức truy hồi như sau:

$$
\texttt{dp}(\sigma, \ell) = \begin{cases}
1 & \sigma = \ell = 1 \text{ or } \sigma = \ell = 0 \\
\texttt{dp}(\sigma - \ell, \ell) + \texttt{dp}(\sigma - \ell, \ell - 1) & \sigma, \ell > 1 \text{ and } \sigma \leq n \\
\texttt{dp}(\sigma - \ell, \ell) + \texttt{dp}(\sigma - \ell, \ell - 1) - \texttt{dp}(\sigma - n - 1, \ell - 1) & \sigma, \ell > 1 \text{ and } \sigma > n
\end{cases}
$$

:::spoiler Code tham khảo
Để tiện lợi cho việc bù trừ, ta định nghĩa thêm một hàm tính phép trừ có modulo như sau:

```cpp=
int sub (int a, int b) {
		return a - b + (a - b >= 0 ? 0 : MOD);
}
```

Sau đó, thuật toán nêu trên có thể được cài đặt như sau:

```cpp=
int C, n; cin >> C >> n;
vector<vector<int>> dp(C + 1);

dp[0] = {1}, dp[1] = {0, 1};
for (int sigma = 2; sigma <= C; sigma++) {
    dp[sigma].push_back(0); // phần tử đệm
    for (int len = 1; validState(sigma, len); len++) {
        int cur = 0;
        if (validState(sigma - len, len))
            cur = add(cur, dp[sigma - len][len]);
        if (validState(sigma - len, len - 1))
            cur = add(cur, dp[sigma - len][len - 1]);
        if (sigma > n && validState(sigma - n - 1, len - 1))
            cur = sub(cur, dp[sigma - n - 1][len - 1]);
        dp[sigma].push_back(cur);
    }
}

int ans = 0;
for (int len = 1; validState(C, len); len++) ans = add(ans, dp[C][len]);
cout << ans;
```
:::

## Thuật toán quy hoạch động của David Pisinger

Năm 1997, David Pisinger đã xuất bản bài báo cáo về thành quả nghiên cứu bài toán cái túi của mình. Trong bài báo cáo ấy, ông đã đề xuất một hướng tiếp cận khác cho QHĐ cái túi, giúp xử lý bài toán Subset sum trong $\mathcal{O}(n \cdot \max w_i)$ và 0/1 Knapsack trong $\mathcal{O}(n \cdot \max w_i \cdot \max v_i)$. Năm 1999, Martello, Pisinger và Toth đã đưa ra nhiều cải tiến quan trọng cho thuật toán 0/1 Knapsack nhưng thuật toán này tương đối phức tạp và không phổ biến trong Lập trình thi đấu.

Độ phức tạp của thuật toán này tốt hơn quy hoạch động truyền thống ở chỗ nó không phụ thuộc vào tổng trọng số cần tìm (trong bài toán Subset Sum) hay giới hạn của cái túi (trong bài toán 0/1 Knapsack). Đây là một cải tiến hữu ích đặc biệt là với các dạng bài có giới hạn $C$ lên đến $\sum w_i$, khi đó độ phức tạp của thuật toán truyền thống tương đương $\mathcal{O}(n^2 \cdot \max w_i)$.

> **Lưu ý**
> Để thuận lợi cho việc giải thích thuật toán, một số thuật ngữ và cách định nghĩa trong bài viết này sẽ có đôi chút khác biệt so với bài báo cáo của Pisinger. Tuy nhiên, những thay đổi này không làm thay đổi hiệu suất của thuật toán.

### Ý tưởng chung

Trong phần này, ta sử dụng một dãy $x_1, x_2, x_3, \dots, x_n$ để biểu diễn trạng thái chọn hay không chọn của các món đồ (với $x_i \in \{0, 1\}$).

**Định nghĩa 1.** Ta định nghĩa một **điểm cắt $b$** là chỉ số của món đồ cuối cùng đặt vừa vào túi, nếu ta liên tục lấy các món đồ từ $1$ đến hết (tạm thời, ta đang không quan tâm thứ tự của các món đồ). Nói cách khác, ta có:

$$
b = \max \left\{ j \, \middle| \, \sum_{1 \leq i \leq j} w_i \leq C \right\}
$$

Bên cạnh đó, ta gọi **lời giải tại điểm cắt** là phương án chọn tất cả các món đồ từ $1$ đến $b$ và không chọn các món đồ còn lại. Ngoài ra, từ điểm cắt $b$, ta tách các món đồ thành hai nhóm $A, B$ lần lượt là các món đồ từ $1$ đến $b$ và từ $b + 1$ đến $n$.

![break_solution.png](/algo/dp_/knapsack/break_solution.png)

**Định nghĩa 2.** Ta định nghĩa một trạng thái chọn/không chọn các món đồ là **trạng thái cân bằng** nếu trạng thái này có thể được biến đổi từ lời giải tại điểm cắt thông qua hai thao tác:

- Xóa món đồ: Khi tổng trọng số của một trạng thái cân bằng lớn hơn $C$, ta có thể bỏ đi một món đồ bất kỳ trong nhóm $A$.
- Thêm món đồ: Khi tổng trọng số của một trạng thái cân bằng không quá $C$, ta có thể chọn thêm một món đồ bất kỳ trong nhóm $B$.

Lưu ý, tại mọi thời điểm, việc chọn loại thao tác để thực hiện phụ thuộc vào tổng trọng số của trạng thái đang xét. Hơn nữa, với định nghĩa như trên, ta đang cho phép tổng trọng số của một số trạng thái vượt quá giới hạn cái túi.

Ví dụ, từ lời giải tại điểm cắt như hình trên, ta có thể thêm một món đồ có trọng số $8$ và bỏ đi hai món đồ có trọng số $1$ và $3$ để cho ra một trạng thái cân bằng như sau:

![balanced_filling.png](/algo/dp_/knapsack/balanced_filling.png)

**Tính chất 1.** Với cách định nghĩa như trên, ta có thể chứng minh rằng mọi lời giải tối ưu/hợp lệ của bài toán 0/1 Knapsack và Subset sum đều là một trạng thái cân bằng.

:::spoiler Chứng minh
Gọi $s_1, s_2, s_3, \dots$ lần lượt là các món đồ cần bỏ đi thuộc nhóm $A$ và $t_1, t_2, t_3, \dots$ lần lượt là các món đồ cần thêm vào thuộc nhóm $B$ để đạt được lời giải tối ưu.

Với mỗi thao tác xóa, ta chọn một phần tử của $s$, xóa món đồ tương ứng rồi xóa luôn phần tử ra khỏi dãy $s$. Tương tự với thao tác thêm món đồ và dãy $t$.

Với bài toán Subset sum, ta sẽ thực hiện bài toán đến khi:

1. Trạng thái đạt được cũng chính là lời giải hợp lệ. Nói cách khác, cả hai dãy $s, t$ đã được xóa hết phần tử.
2. Dãy $s$ đã được xóa hết phần tử mà tổng trọng số hiện tại lớn hơn $C$. Nói cách khác, lời giải này chắc chắn có tổng trọng số lớn hơn $C$. Điều này vô lý vì lời giải của bài toán Subset sum phải là một tập các món đồ có trọng số đúng bằng $C$.
3. Dãy $t$ đã được xóa hết phần tử mà tổng trọng số hiện tại không quá $C$. Nói cách khác, lời giải này chắc chắn có tổng trọng số bé hơn $C$. Một lần nữa, điều này lại vô lý vì không thỏa yêu cầu của bài toán.

Lưu ý, khi cả hai dãy $s, t$ chưa được xóa hết phần tử, ta luôn có thể tiếp tục xóa bằng thao tác xóa/thêm món đồ.

Tương tự với bài toán 0/1 Knapsack, ta thực hiện bài toán đến khi:

1. Trạng thái đạt được cũng chính là lời giải tối ưu. Nói cách khác, cả hai dãy $s, t$ đã được xóa hết phần tử.
2. Dãy $s$ đã được xóa hết phần tử mà tổng trọng số hiện tại lớn hơn $C$. Nói cách khác, lời giải này chắc chắn có tổng trọng số lớn hơn $C$. Điều này vô lý vì lời giải của bài toán 0/1 Knapsack phải có tổng trọng số không quá $C$.
3. Dãy $t$ đã được xóa hết phần tử mà tổng trọng số hiện tại không quá $C$. Nói cách khác, ta đã tìm được một lời giải hợp lệ khác có tập món đồ được chọn là tập cha của tập món đồ được chọn trong lời giải tối ưu. Điều này là vô lý vì lời giải tối ưu phải có tổng giá trị lớn nhất.
:::

**Tính chất 2.** Tổng trọng số của một trạng thái cân bằng luôn nằm trong khoảng $(C - W; C + W]$ với $W = \max w_i$.

:::spoiler Chứng minh
Ta chỉ có thể đạt được tổng trọng số không quá $C - W$ khi thực hiện thao tác xóa món đồ trên trạng thái có tổng trọng số không quá $C$. Tương tự, ta chỉ có thể đạt được tổng trọng số lớn hơn $C + W$ khi thực hiện thao tác thêm món đồ trên trạng thái có tổng trọng số lớn hơn $C$.
:::

Có thể thấy, ý tưởng của thuật toán quy hoạch động của David Pisinger là duy trì một trạng thái cân bằng có trọng số trong khoảng $(C - W; C + W]$ thay vì xét hết tất cả các trạng thái hợp lệ có trọng số trong khoảng $[0; C]$ như cách làm truyền thống. Điều này cũng giúp số lượng giá trị tổng trọng số phân biệt cần xét giảm từ $\mathcal{O}(C)$ xuống $\mathcal{O}(W)$.

Đây là đồ thị mô phỏng sự thay đổi của tổng trọng số theo hướng tiếp cận của thuật toán này so với hướng tiếp cận của lời giải quy hoạch động truyền thống:

![weight_to_time_graph.png](/algo/dp_/knapsack/weight_to_time_graph.png)

### Lời giải cho bài toán Subset sum

#### Quy hoạch động $\mathcal{O}(n^2W)$

Gọi $\texttt{exist}(i, j, \sigma)$ là một giá trị boolean cho biết sự tồn tại của một trạng thái cân bằng có tổng trọng số $\sigma$ nếu chỉ áp dụng thao tác xóa món đồ cho $i$ phần tử đầu tiên của nhóm $A$ và thao tác thêm món đồ cho $j$ phần tử đầu tiên của nhóm $B$.

Dễ thấy, nếu $\texttt{exist}(i - 1, j, \sigma) = 1$ hoặc $\texttt{exist}(i, j - 1, \sigma) = 1$ thì $\texttt{exist}(i, j, \sigma)$ cũng phải trả về $1$. Ngoài ra, ta xét thêm hai trường hợp chuyển trạng thái:

- Nếu $\sigma > C$ và $\texttt{exist}(i, j, \sigma) = 1$, ta có thể xóa phần tử thứ $i + 1$ của nhóm $A$, suy ra $\texttt{exist}(i + 1, j, \sigma - w_{i+1}) = 1$.
- Nếu $\sigma \leq C$ và $\texttt{exist}(i, j, \sigma) = 1$, ta có thể thêm phần tử thứ $j + 1$ của nhóm $B$, suy ra $\texttt{exist}(i, j + 1, \sigma + w_{b+j+1}) = 1$.

Từ đó, ta có công thức truy hồi cho $\texttt{exist}$ như sau:

$$
\texttt{exist}(i, j, \sigma) =
\texttt{exist}(i - 1, j, \sigma) \lor \texttt{exist}(i, j - 1, \sigma) \lor
\max \begin{cases}
\texttt{exist}(i - 1, j, \sigma + w_i) & C < \sigma + w_i \leq C + W \\
\texttt{exist}(i, j - 1, \sigma - w_{b+j}) & C - W < \sigma - w_{b+j} \leq C \\
\end{cases}
$$

Lưu ý, khi $i = j = 0$, chỉ có $\texttt{exist}(0, 0, \overline{w}) = 1$ với $\overline{w}$ là tổng trọng số của lời giải tại điểm cắt.

:::spoiler Code tham khảo
```cpp=
/// tìm điểm cắt
int breakPoint = 0, curSum = 0;
for (int i = 1; i <= n && curSum + w[i] <= C; i++)
    curSum += w[i], breakPoint = i;

/// chuẩn bị các tham số liên quan & trường hơp cơ sở
int W = *max_element(w + 1, w + 1 + n), offset = C - W;
exist[0][0][curSum - offset] = 1;

/// thực hiện QHĐ
for (int i = 0; i <= breakPoint; i++) {
    for (int j = 0; j <= n - breakPoint; j++) {
        for (int sigma = C - W; sigma <= C + W; sigma++) {
            int cur = sigma - offset;
            if (!exist[i][j][cur]) continue;
            if (i < breakPoint) {
                exist[i + 1][j][cur] = 1;
                if (sigma > C) exist[i + 1][j][cur - w[i + 1]] = 1;
            }
            if (j < n - breakPoint) {
                exist[i][j + 1][cur] = 1;
                if (sigma <= C) exist[i][j + 1][cur + w[breakPoint + j + 1]] = 1;
            }
        }
    }
}
cout << exist[breakPoint][n - breakPoint][C - offset];
```
:::

<!-- :::spoiler Code tham khảo 2
```cpp=
/// tìm điểm cắt
int breakPoint = 0, curSum = 0;
for (int i = 1; i <= n && curSum + w[i] <= C; i++)
    curSum += w[i], breakPoint = i;

/// chuẩn bị các tham số liên quan & trường hơp cơ sở
int W = *max_element(w + 1, w + 1 + n), offset = C - W;
exist[0][0][curSum - offset] = 1;

/// thực hiện QHĐ
for (int i = 0; i <= breakPoint; i++) {
    for (int j = 0; j <= n - breakPoint; j++) {
        if (max(i, j) == 0) continue;
        for (int sigma = C - W; sigma <= C + W; sigma++) {
            int cur = sigma - offset;
            exist[i][j][cur] = (i ? exist[i - 1][j][cur] : 0) | (j ? exist[i][j - 1][cur] : 0);

            if (i && C < sigma + w[i] && sigma + w[i] <= C + W)
                exist[i][j][cur] |= exist[i - 1][j][cur + w[i]];
            if (j && C - W < sigma - w[breakPoint + j] && sigma - w[breakPoint + j] <= C)
                exist[i][j][cur] |= exist[i][j - 1][cur - w[breakPoint + j]];
        }
    }
}
cout << exist[breakPoint][n - breakPoint][C - offset];
```
::: -->

#### Quy hoạch động $\mathcal{O}(nW)$

Khi cố định hai tham số $i$ và $\sigma$, ta có hai tính chất sau đây:

$$
\begin{align*}
\texttt{exist}(i, j, \sigma) = 1 &\Longrightarrow \texttt{exist}(i, j + 1, \sigma) = 1 \\
\texttt{exist}(i, j, \sigma) = 0 &\Longrightarrow \texttt{exist}(i, j - 1, \sigma) = 0 \\
\end{align*}
$$

Như vậy, với mọi cặp $(i, \sigma)$, tồn tại một giá trị $\delta$ thỏa $\texttt{exist}(i, j, \sigma) = [j \geq \delta]$. Nói cách khác, $\delta$ là $j$ nhỏ nhất thỏa $\texttt{exist}(i, j, \sigma) = 1$, ta gọi giá trị này là $\texttt{change}(i, \sigma)$. Trong trường hợp không tồn tại $j$ thỏa mãn, ta quy ước $\texttt{change}(i, \sigma) = \infty$.

| $\texttt{exist}(i, 0, \sigma)$ | $\texttt{exist}(i, 1, \sigma)$ | $\dots$ | $\texttt{exist}(i, \delta, \sigma)$ | $\dots$ | $\texttt{exist}(i, n - b, \sigma)$ |
| :--: | :--: | :--: | :--: | :--: | :--: |
| $0$ | $0$ | $\dots$ | $1$ | $\dots$ | $1$ |


Không khó để chứng minh khi cố định $\sigma$ thì $\texttt{change}(i, \sigma)$ là hàm nghịch biến (tức $i$ tăng thì $\texttt{change}(i, \sigma)$ giảm).

Từ công thức truy hồi cho $\texttt{exist}$ ở lời giải  $\mathcal{O}(n^2W)$, ta thấy, khi một trạng thái $(i, j, \sigma)$ có $\texttt{exist}(i, j, \sigma) = 1$, nó sẽ kéo theo:

- $\texttt{exist}(i + 1, j, \sigma) = 1$.
- $\texttt{exist}(i, j + 1, \sigma) = 1$.
- $\texttt{exist}(i + 1, j, \sigma - w_{i+1}) = 1$, nếu $\sigma > C$.
- $\texttt{exist}(i, j + 1, \sigma + w_{b+j+1}) = 1$, nếu $\sigma \leq C$.

![transition_2.png](/algo/dp_/knapsack/transition_2.png)

Từ đó, nếu cố định $i, \sigma$ và cùng lúc các vị trí $\texttt{exist}(i, j, \sigma) = 1$ với $j \in [\delta; n - b]$, nó sẽ kéo theo:

- $\texttt{exist}(i + 1, j, \sigma) = 1$ với $j \in [\delta; n - b]$.
- $\texttt{exist}(i + 1, j, \sigma - w_{i+1}) = 1$ với $j \in [\delta; n - b]$, nếu $\sigma > C$.
- $\texttt{exist}(i, j, \sigma + w_{b+j}) = 1$, với $j \in [\delta + 1; n - b]$, nếu $\sigma \leq C$.

Ở hai trường hợp đầu tiên, ta đều có các trạng thái thái di động theo tham số $j$, hai tham số $i$ và $\sigma$ được cố định cùng một giá trị. Tuy nhiên, ở trường hợp cuối cùng, tham số $\sigma$ lại phụ thuộc vào $j$, do đó, ta phải xét mọi $j$ thỏa mãn để tính. Việc xét mọi $j$ từ $\delta + 1$ đến $n - b$ sẽ khiến thuật toán quay về độ phức tạp $\mathcal{O}(n^2W)$. Do đó, ta cần dùng đến nhận xét rằng nếu:

$$
\begin{align*}
\texttt{exist}(i - 1, j, \sigma) = 1 \space\space\space &\forall j \in [\delta'; n - b] \\
\Longrightarrow \texttt{exist}(i - 1, j, \sigma + w_{b+j}) = 1 \space\space\space &\forall j \in [\delta' + 1; n - b] \\
\Longrightarrow \texttt{exist}(i, j, \sigma + w_{b+j}) = 1 \space\space\space & \forall j \in [\delta' + 1; n - b]
\end{align*}
$$

Nói cách khác, ta chỉ cần xét $j$ từ $\delta + 1$ đến vị trí $\delta'$ đầu tiên thỏa $\texttt{exist}(i - 1, \delta', \sigma) = 1$, tức $\delta' = \texttt{change}(i - 1, \sigma)$. Bây giờ, nếu cố định $\sigma$, ta có thể hình dung biến $j$ chạy trên các đoạn từ $\texttt{change}(i, \sigma) + 1$ đến $\texttt{change}(i - 1, \sigma)$, tổng độ phức tạp tất cả các lần chạy là $\mathcal{O}(n)$ nên lúc này độ phức tạp trung bình của việc truy hồi đã trở thành $\mathcal{O}(1)$.

Tổng kết lại, khi ta biết được giá trị của $\texttt{change}(i, \sigma) = \delta$, ta thực hiện cập nhật các trạng thái khác của quy hoạch động như sau:

1. Gán $\texttt{change}(i + 1, \sigma) \leftarrow \min(\texttt{change}(i + 1, \sigma), \delta)$.
2. Nếu $\sigma > C$, gán $\texttt{change}(i + 1, \sigma - w_{i+1}) \leftarrow \min(\texttt{change}(i + 1, \sigma - w_{i+1}), \delta)$.
3. Nếu $\sigma \leq C$, với mọi $j$ từ $\texttt{change}(i, \sigma) + 1$ đến $\texttt{change}(i - 1, \sigma)$, gán $\texttt{change}(i, \sigma + w_{b+j}) \leftarrow \min(\texttt{change}(i, \sigma + w_{b+j}), j)$.

Để biết đáp án cuối cùng của bài toán, ta kiểm tra $\texttt{change}(b, C) < \infty$. Như vậy, độ phức tạp của thuật toán này là $\mathcal{O}(nW)$. Bên cạnh đó, ta có thể giảm độ phức tạp bộ nhớ xuống $\mathcal{O}(W)$ nếu bỏ đi tham số $i$ trong bảng quy hoạch động.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
// tìm điểm cắt
int breakPoint = 0, curSum = 0;
for (int i = 1; i <= n && curSum + w[i] <= C; i++)
    curSum += w[i], breakPoint = i;

// chuẩn bị các tham số liên quan & trường hơp cơ sở
int W = *max_element(w + 1, w + 1 + n), offset = C - W;
for (int i = 0; i <= n; i++)
    fill(change[i], change[i] + 2 * W + 1, INT_MAX);
change[0][curSum - offset] = 0;

// thực hiện QHĐ
for (int i = 0; i <= breakPoint; i++) {
    for (int sigma = C - W; sigma <= C + W; sigma++) {
        int cur = sigma - offset, delta = change[i][cur];
        if (delta == INT_MAX) continue;

        if (i < breakPoint) // bước 1
            change[i + 1][cur] = min(change[i + 1][cur], delta);
        if (sigma > C && i < breakPoint) // bước 2
            change[i + 1][cur - w[i + 1]] = min(change[i + 1][cur - w[i + 1]], delta);
        if (sigma <= C) { // bước 3
            int dlt = min(n - breakPoint, (i ? change[i - 1][cur] : INT_MAX));
            for (int j = delta + 1; j <= dlt; j++)
                change[i][cur + w[breakPoint + j]] = min(change[i][cur + w[breakPoint + j]], j);
        }
    }
}
cout << (change[breakPoint][C - offset] < INT_MAX);
```
:::

### Lời giải cho bài toán 0/1 Knapsack

Đặt $V = \max v_i$, ta gọi $\texttt{exist}(i, j, \sigma, \rho)$ làm hàm kiểm tra sự tồn tại của một trạng thái cân bằng có tổng trọng số $\sigma$, tổng giá trị $\rho$ khi thực hiện thao tác xóa/thêm món đồ trên lần lượt $i$ và $j$ phần tử đầu tiên của nhóm $A$ và $B$.

Tương tự với lời giải trên, ta cũng định nghĩa $\texttt{change}(i, \sigma, \rho)$ dựa trên sự đồng biến của hàm $\texttt{exist}$ trên biến $j$. Như vậy, ta có lời giải $\mathcal{O}(nWV)$.

Để cải tiến thêm cho thuật toán này, Pisinger đã đưa ra cận trên và cận dưới cho biến $\rho$ nhằm giới hạn số trạng thái cần duyệt. Tuy nhiên, cận trên cho độ phức tạp thời gian của thuật toán này vẫn là $\mathcal{O}(nWV)$.

Nhìn chung, khi so sánh với các thuật toán quy hoạch động hiện tại, thuật toán của Pisinger chỉ phát huy hiệu quả với bài toán Subset Sum.

## Phụ lục

### Tài liệu tham khảo

- [Ashley Khoo (errorgorn). [Tutorial] Knapsack, Subset Sum and the (max, +) Convolution, 2022.](https://codeforces.com/blog/entry/98663)
- [David Pisinger. Linear Time Algorithms for Knapsack Problems with Bounded Weights, 1997.](https://sci-hub.sidesgame.com/10.1006/jagm.1999.1034)
- [Silvano Martello, David Pisinger, Paolo Toth. Dynamic Programming and Strong Bounds for the 0-1 Knapsack Problem, 1999.](https://www3.cs.stonybrook.edu/~sael/teaching/cse548/Sups/MartelloPisinger1999.pdf)