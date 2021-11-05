# Mảng cộng dồn và mảng hiệu

**Tác giả:** 
- Bùi Nguyễn Đức Tân - VNU-HCM, High School for the Gifted

**Reviewer:**
- Trần Quang Lộc - ITMO University
- Hoàng Xuân Nhật - VNU-HCM, University of Science
- Nguyễn Phú Bình - Hung Vuong High School for the Gifted, Binh Duong Province

---

[[_TOC_]]

## Khái niệm

### Mảng cộng dồn (prefix sum)

Cho một mảng $A$ có $n$ phần tử được đánh số từ $0$ đến $n - 1$, ta dựng mảng $S(A)$ theo quy tắc sau:

- $S_0 = c$, với $c$ là một hằng số thực
- $S_i = S_{i - 1} + A_{i -1} = \displaystyle c +\sum_{j = 0}^{i - 1} A_j$, với $1 \le i < n$

Mảng $S(A)$ được gọi là **mảng cộng dồn (tiền tố)** theo $c$ của $A$, gọi cách khác là prefix sum của $A$. Từ một mảng $A$, ta có thể sinh ra vô hạn mảng $S(A)$ bằng cách chọn một số thực $c$ tùy ý; trên thực tế, ta thường chọn $c = 0$ để thuận tiện hơn khi tính toán.

![](https://i.imgur.com/lzBYJ89.gif)

### Mảng hiệu (difference array)

Cũng với mảng $A$, ta có thể dựng mảng $D(A)$ theo quy tắc: $D_i = A_{i + 1} - A_i\;(0 \le i < n - 1)$.

Mảng $D(A)$ được gọi là **mảng hiệu** của $A$, có tên tiếng Anh là difference array.

![](https://i.imgur.com/3IQ1YlB.gif)

## Cài đặt

### Mảng cộng dồn

Để dựng mảng cộng dồn, ta có thể áp dụng định nghĩa ở trên để dựng trực tiếp mảng:

```c++
vector<int> buildPrefixSum(const vector<int>& a, int C = 0) {
    int n = (int)a.size();
    vector<int> prefixSum(n + 1);

    prefixSum[0] = C;

    for (int i = 0; i < n; i++)
        prefixSum[i + 1] = prefixSum[i] + a[i];

    return prefixSum;
}
```

<!-- giải thích lại partial_sum -->

Ngoài ra, thư viện C++ STL cũng cung cấp hàm `partial_sum` để phục vụ quá trình dựng mảng cộng dồn, cú pháp của hàm như sau:

```c++
partial_sum(first, last, result, binary_op)
```

Hàm trên sẽ thực hiện tính mảng cộng dồn với toán tử `binary_op` trên các container của C++ có iterator trỏ từ `[first, last)` và trả mảng cộng dồn sang container bắt đầu từ iterator trỏ về `result`.

Có hai lưu ý quan trọng khi sử dụng hàm này:

- Hàm `partial_sum` duyệt qua các phần tử của container theo tính chất của iterator của container đó; vì thế giá trị của mảng cộng dồn sẽ phụ thuộc vào thứ tự xuất hiện của các phần tử trong container đó.
- Tham số `binary_op` có thể được để trống. Khi này, toán tử mặc định là phép cộng (`+`).

Bạn đọc có thể tham khảo thêm về hàm này tại trang [cppreference](https://en.cppreference.com/w/cpp/algorithm/partial_sum).

Code minh họa:

```cpp
void printArray(const vector<int>& arr) {
  for (int v : arr) cout << v << " ";
  cout << endl;
}

vector<int> a = {3, -1, -4, 1, 5, 9, -2, -6};
int n = (int)a.size();

// Dựng thủ công
vector<int> prefOne = buildPrefixSum(a);
printArray(prefOne); // 0 3 2 -2 -1 4 13 11 5

// Dựng bằng partial_sum
vector<int> prefTwo(n);
partial_sum(a.begin(), a.end(), prefTwo.begin());
printArray(prefTwo); // 3 2 -2 -1 4 13 11 5
```

Trong cả hai cách trên, độ phức tạp của quá trình dựng là $\mathcal{O}(n)$.

### Mảng hiệu

Tương tự, ta cũng có thể áp dụng định nghĩa để dựng trực tiếp mảng hiệu:

```cpp
vector<int> buildDifferenceArray(const vector<int>& a) {
    int n = (int)a.size();

    vector<int> differenceArray(n - 1);

    for (int i = 0; i < n - 1; i++)
        differenceArray[i] = a[i + 1] - a[i];

    return differenceArray;
}
```

Ngoài ra, thư viện C++ STL cũng cung cấp hàm `adjacent_difference` để phục vụ quá trình dựng mảng cộng dồn, cú pháp của hàm như sau:

```cpp
adjacent_difference(first, last, result, binary_op)
```

Hàm trên sẽ thực hiện tính mảng hiệu với toán tử `binary_op` trên các container của C++ có iterator trỏ từ `[first, last)` và trả mảng hiệu sang container bắt đầu từ iterator trỏ về `result`.

Các lưu ý ở phần `partial_sum` cũng được áp dụng cho hàm này.

Bạn đọc có thể tham khảo thêm về hàm này tại trang [cppreference](https://en.cppreference.com/w/cpp/algorithm/difference_array).
Code minh họa:

```cpp
// Dựng thủ công
vector<int> diffOne = buildDifferenceArray(a);
printArray(diffOne);
// -4 -3 5 4 4 -11 -4

// Dựng bằng partial_sum
vector<int> diffTwo(n);
adjacent_difference(a.begin(), a.end(), diffTwo.begin());
printArray(diffTwo);
// 3 -4 -3 5 4 4 -11 -4
```

Trong cả hai cách trên, độ phức tạp của quá trình dựng là $\mathcal{O}(n)$.

## Tính chất

### Độ dài mảng

- Đối với **mảng cộng dồn**, do ta cần thêm một hằng số $c$ ở đầu mảng, độ dài của mảng $S(c, A)$ là $n + 1$, nhiều hơn 1 phần tử so với mảng $A$ gốc.
- Ngược lại, **mảng hiệu** được dựng dựa trên hiệu của hai phần tử liền kề nhau. Tuy nhiên, trong mảng $A$ chỉ có $n - 1$ cặp như vậy, vì thế độ dài của $D(A)$ là $n - 1$, ít hơn 1 phần tử so với mảng $A$ gốc.

### Tính riêng biệt

- Từ một mảng $A$ bất kỳ, ta sinh được vô hạn mảng cộng dồn $S(c, A)$ từ $A$. Tuy nhiên, các mảng cộng dồn này chỉ khác nhau ở giá trị $c$ được chọn.
- Cũng với mảng $A$ đó, ta sinh được **một và chỉ một** mảng hiệu $D(A)$ từ $A$.

### Liên hệ giữa mảng cộng dồn và mảng hiệu

Cho mảng cộng dồn $S(c, A)$ và mảng hiệu $D(A)$, ta có thể dễ dàng khôi phục nội dung của mảng $A$ thông qua các phép sau:

- $S(A_0, D(A)) = A$
- $D(S(c, A)) = A$ với mọi $c$ thực

Hình dưới đây mô tả rõ hơn mối liên hệ giữa mảng gốc, mảng hiệu và mảng cộng dồn sinh ra từ nó:
![](https://i.imgur.com/agrVFdU.png)

Hàm `partial_sum` và `adjacent_difference` trong C++ STL cũng tuân theo quy tắc này trên. Tuy nhiên, các thao tác trên hai hàm này có phần phức tạp hơn so với thao tác trên mảng mà ta cài đặt thủ công.

## Ứng dụng của mảng cộng dồn

Mảng cộng dồn có một tính chất quan trọng: các phần tử được cộng lại chồng chất lên nhau một cách liên tiếp, vì thế, với mọi nửa khoảng $[l, r)$ $(0 \le l < r \le n)$, ta chỉ cần tính $S_r - S_l$ để tính tổng của các phần tử $A_l, A_{l + 1},\dots, A_{r - 2}, A_{r - 1}$. Việc trừ này cũng sẽ khử đi hằng số $c$ của $S$, vì thế ta có thể dùng bất kỳ mảng $S$ nào được sinh từ $A$ để tính tổng.

**Chứng minh:**

Theo định nghĩa: $S_i = c + \displaystyle \sum_{j = 0}^{i - 1} A_j$

Khi này: 

$$
\begin{align*}
S_r - S_l &= c + \displaystyle \sum_{j = 0}^{r - 1} A_j - \bigg(c + \displaystyle \sum_{j = 0}^{l - 1} A_j\bigg) \\
&= c + \displaystyle \sum_{j = 0}^{r - 1} A_j - c - \displaystyle \sum_{j = 0}^{l - 1} A_j \\
&= c - c + \displaystyle \sum_{j = 0}^{r - 1} A_j - \displaystyle \sum_{j = 0}^{l - 1} A_j \\
&= \displaystyle \sum_{j = l}^{r - 1} A_j + \displaystyle \sum_{j = 0}^{l - 1} A_j - \displaystyle \sum_{j = 0}^{l - 1} A_j \\
&= \displaystyle \sum_{j = l}^{r - 1} A_j \quad \blacksquare
\end{align*}
$$

Trong đa số trường hợp, mảng cộng dồn thường được sử dụng nếu bài toán yêu cầu tính tổng một đoạn cao nhiều lần liên tiếp. Dưới đây, ta sẽ đề cập một số bài toán có điều kiện trên.

### Bài toán minh họa

Nguồn: [CSES - Maximum Subarray Sum](https://cses.fi/problemset/task/1643)

Đề bài: Cho một mảng $A$ gồm $n$ phần tử. Tìm đoạn con khác rỗng có tổng lớn nhất. Giới hạn: $1 \le n \le 2 \cdot 10^5$, $\lvert A_i \rvert \le 10^9$

Trước hết, ta tạo mảng $pref = S(0, A)$ để lưu mảng cộng dồn của $A$. Giả sử với $r$ cố định, ta cần tìm $l < r$ sao cho tổng các phần tử trong nửa khoảng $[l, r)$ đạt cực đại. Ta viết lại bài toán theo công thức sau:

$$
\begin{align*}
ans_r &= \max_{0 \, \le \, l \, < \, r} (pref_r - pref_l) \\ 
&= pref_r + \max_{0 \, \le \, l \, < \, r} (- pref_l) \\ 
&= pref_r - \min_{0 \, \le \, l \, < \, r} pref_l \\ 
\end{align*}
$$

Nếu ta chạy $r$ từ $1$ đến $n$, ta có thể cập nhật cuốn chiếu $\min$ theo từng $pref_r$; việc này cho phép chúng ta tính $ans_r$ với độ phức tạp $O(1)$. Đáp án của bài toán là $\displaystyle \max_{r} ans_r$ với $1 \le r \le n$.

Độ phức tạp của cách trên là $\mathcal{O}(n)$. Code tham khảo:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200003;
const long long INF = 1e18;

int n, a[MAXN];
long long prefSum[MAXN], prefMin[MAXN], ans = -INF;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    prefSum[0] = prefMin[0] = 0;
    for (int i = 1; i <= n; i++)
      prefSum[i] = prefSum[i - 1] + a[i], prefMin[i] = min(prefMin[i - 1], prefSum[i]);
    for (int i = 1; i <= n; i++)
        ans = max(ans, prefSum[i] - prefMin[i]);
    cout << ans;
}
```

Lưu ý, ta có thể thu gọn `prefSum` và `prefMin` thành một biến duy nhất để tối ưu bộ nhớ sử dụng.
Bên cạnh cách giải đã đề cập, bài toán này cũng có thể giải bằng phương pháp quy hoạch động hoặc chia để trị.

## Ứng dụng của mảng hiệu

Giả sử, ta cần cộng thêm một lượng $k$ vào một đoạn con $[l, r]$ của mảng $A$. Thay vì cộng lần lượt từng phần tử với độ phức tạp $\mathcal{O}(n)$, ta có thể dựng mảng hiệu $D(A)$ và cập nhật trên đó với độ phức tạp $\mathcal{O}(1)$. Dựng mảng hiệu $D$ từ $A$ lưu trữ chênh lệch của các cặp phần tử liền kề nhau, ta chia các trường hợp sau để nhận xét:

- Nếu $A_i$ và $A_{i + 1}$ đều nằm ngoài $[l, r]$ $\Rightarrow$ Giá trị của hai phần tử không đổi $\Rightarrow$ $D_i$ không đổi
- Nếu $A_i$ và $A_{i + 1}$ đều nằm trong $[l, r]$ $\Rightarrow$ Giá trị của hai phần tử đều được cộng một lượng $k$ $\Rightarrow$ $D_i$ không đổi
- Nếu chỉ một trong $A_i$ hoặc $A_{i + 1}$ nằm trong $[l, r]$ $\Rightarrow$ Giá trị của một phần tử giữ nguyên còn phần tử còn lại được cộng một lượng $k$ $\Rightarrow$ **$D_i$ thay đổi**

Chỉ duy nhất trường hợp cuối cùng ta cần tác động trực tiếp lên $D$. Nhận thấy, trường hợp cuối chỉ thỏa khi $i = l - 1$ hoặc $i = r$, ta chỉ cần tác động trực tiếp lên $D_{l - 1}$ và $D_{r}$ để cập nhật đoạn. Sau khi cập nhật hoàn tất, ta áp dụng tính chất $S(D, A_0) = A$ để lấy giá trị cuối cùng của $A$.

### Bài toán minh họa

Nguồn: [Codeforces - Karen and Coffee](https://codeforces.com/contest/816/problem/B)

Đề bài: Cho một mảng $A$ có vô số phần tử mang giá trị $0$. Có $n$ truy vấn cập nhật, mỗi truy vấn yêu cầu cập nhật toàn bộ phần tử từ $l_i$ đến $r_i$ thêm $1$.

Sau khi cập nhật xong, trả lời $q$ câu hỏi với nội dung sau: có bao nhiêu vị trí $i$ thỏa $a \le i \le b$ và $A_i \ge k$?

Giới hạn: $k \le n \le 2 \cdot 10^5, q \le 2 \cdot 10^5, 1 \le l_i \le r_i \le 2 \cdot 10^5, 1 \le a \le b \le 2 \cdot 10^5$

Do điều kiện $l_i, r_i, a, b$ của đề bài, mảng $A$ sẽ chỉ lưu trữ tối đa 200 nghìn phần tử, toàn bộ phần tử này đều có chỉ số dương, vì thế ta sẽ đơn thuần lưu 2 mảng này dưới dạng mảng thường.

Gọi $D$ là mảng hiệu của $A$. Để xử lý truy vấn cập nhật, ta chỉ cần cập nhật giá trị của mảng $D$ tại 2 biên $l$ và $r + 1$ bằng cách tăng $D_l$ thêm $1$ và trừ $1$ khỏi $D_{r + 1}$. Sau khi xử lý toàn bộ truy vấn cập nhật, ta sử dụng hệ thức $S(D, 0) = A$ để cập nhật lại giá trị của mảng $A$.

Để trả lời câu hỏi, ta có thể hình dung mỗi chỉ số trong đoạn $[a, b]$ mang giá trị $1$ nếu thỏa điều kiện đề bài và $0$ nếu không thỏa; số chỉ số thỏa mãn cũng chỉ là tổng của các phần tử nằm trong đoạn $[a, b]$. Từ tính chất này, ta có thể ứng dụng mảng cộng dồn để trả lời nhau câu hỏi trong $\mathcal{O}(1)$. Ta đặt mảng $A'$ đánh dấu giá trị $A_i$ tương ứng có thỏa điều kiện $\ge k$ không, rồi dựng mảng cộng dồn $S$ trên $A'$. Đáp án của mỗi câu hỏi sẽ là kết quả của phép tính $S_{b} - S_{a - 1}$.

Độ phức tạp thời gian và không gian của cách này đều là $\mathcal{O}(n)$. Code tham khảo:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200003;

int n, k, q, d[MAXN], a[MAXN], s[MAXN];

void update(int l, int r) {
    ++d[l], --d[r + 1];
}

void buildPrefixSum() {
    a[0] = s[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        a[i] = a[i - 1] + d[i];
        s[i] = s[i - 1] + (a[i] >= k);
    }
}

int query(int a, int b) {
    return s[b] - s[a - 1];
}

int main() {
    cin >> n >> k >> q;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        update(l, r);
    }
    buildPrefixSum();
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << query(a, b) << endl;
    }
}
```

## Mở rộng sang mảng nhiều chiều

Ta có thể mở rộng mảng cộng dồn và mảng hiệu để thao tác trên mảng nhiều chiều.

### Mảng cộng dồn hai chiều

Cho mảng hai chiều $A$ có kích thước $m \times n$ (chỉ số hàng và cột đầu tiên đều là 1), mảng cộng dồn $S(A)$ được dựng theo công thức sau: $$S_{i,j}=\displaystyle \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i,t_j}$$

Các phần tử trong mảng cộng dồn lưu tổng của toàn bộ phần tử chứa trong hình chữ nhật $[1, i] \times [1, j]$.
Điểm khác biệt so với mảng cộng dồn 1 chiều ở đây là sự lược bỏ của hằng số $C$, ta ngầm quy ước: $S_{0,x} = S_{y,0} = 0$ với $x, y$ nguyên không âm khi dựng mảng cộng dồn.

![](https://i.imgur.com/FhmEVv3.png)

Từ công thức quy ước trên, ta thực hiện biến đổi sau để dựng mảng cộng dồn:

$$
\begin{alignat*}{2}
\displaystyle
S_{i,j} & =\sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i,t_j}\\
&=\sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j} + \sum_{t_i\,=\,1}^{i - 1} A_{t_i,j} + \sum_{t_j\,=\,1}^{j - 1} A_{i,t_j} + A_{i, j}\\
&=\sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j} + \sum_{t_i\,=\,1}^{i - 1} A_{t_i,j} + \sum_{t_j\,=\,1}^{j - 1} A_{i,t_j} + A_{i, j}\\
&=\sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j} + \Bigg(\sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j} A_{t_i,t_j} - \sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j}\Bigg) + \Bigg(\sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j} - \sum_{t_i\,=\,1}^{i - 1} \sum_{t_j\,=\,1}^{j - 1} A_{t_i,t_j}\Bigg) + A_{i, j}\\
&= S_{i-1,j-1} + S_{i-1,j} - S_{i-1,j-1} + S_{i,j-1} - S_{i-1,j-1} + A_{i, j} \\
&= S_{i-1,j} + S_{i,j-1} - S_{i-1,j-1} + A_{i, j}
\end{alignat*}
$$

Để hình dung rõ hơn công thức biến đổi trên, bạn đọc có thể tham khảo hình ảnh dưới:

| ![](https://i.imgur.com/3vhyF37.gif)                                                            |
| :---------------------------------------------------------------------------------------------: |
| ![](https://i.imgur.com/TlZhWxX.png)                                                            |
| Các phần tử $A_i$ tô màu xanh nhạt được đánh dấu 1 lần, tô màu xanh đậm được đánh dấu tới 2 lần |

Code dưới đây dựng mảng cộng dồn hai chiều:

```cpp
vector< vector<int> > build2DPrefixSum(const vector< vector<int> >& a) {
    int m = (int)a.size(), n = (int)a[0].size();

    vector< vector<int> > prefixSum(m + 1, vector<int> (n + 1, 0));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + a[i - 1][j - 1]; // ta truy cập a(i - 1, j - 1) do mảng A là 0-indexed
    return prefixSum;
}
```

Để tính tổng của toàn bộ các phần tử nằm trong hình chữ nhật có góc trái trên là $(x_1, y_1)$ và góc phải dưới $(x_2, y_2)$, ta biến đổi tương tự để thu được công thức tính sau:

$$
\displaystyle
\sum_{i = x_1}^{x_2} \sum_{j = y_1}^{y_2} A_{i, j} = S_{x_2,\, y_2} - S_{x_1 - 1,\, y_2} - S_{x_2,\, y_1 - 1} + S_{x_1 - 1,\, y_1 - 1}
$$

Phần chứng minh công thức trên xin được nhường lại cho bạn đọc. Hình ảnh dưới minh họa vì sao công thức trên cho kết quả chính xác:

|                   ![](https://i.imgur.com/aqfFaz3.gif)                    |
| :-----------------------------------------------------------------------: |
|                   ![](https://i.imgur.com/3qzbjwL.png)                    |
| Các phần tử $A_i$ tô màu đỏ bị trừ tới 2 lần, vì thế cần phải cộng bù lại |

### Mảng cộng dồn ba chiều

Giả sử ta có mảng $A$ trong không gian 3 chiều với kích thước $m \times n \times p$, ta dựng mảng $S(A)$ theo quy tắc sau: $$S_{i, j, k}=\displaystyle \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} \sum_{t_k\,=\,1}^{k} A_{t_i,t_j,t_k}$$

Công thức sau được sử dụng để dựng mảng cộng dồn 3 chiều:

$$
\begin{align*}
\displaystyle
S_{t_i,t_j,t_k}&=A_{t_i,t_j,t_k} - S_{t_i-1,t_j,t_k} - S_{t_i,t_j-1,t_k} - S_{t_i,t_j,t_k-1} \\
& \hspace{1em}+ S_{t_i-1,t_j-1,t_k} + S_{t_i-1,t_j,t_k-1} + S_{t_i,t_j-1,t_k-1} - S_{t_i-1,t_j-1,t_k-1}
\end{align*}
$$

Tương tự, ta tính tổng các phần tử trong không gian $[x_1, x_2] \times [y_1, y_2] \times [z_1, z_2]$ qua công thức sau:

$$
\begin{align*}
\displaystyle
\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}\sum_{k=z_1}^{z_2} A_{i, j, k}
&=S_{x_2,y_2,z_2}-S_{x_1-1,y_2,z_2}-S_{x_2,y_1-1,z_2}-S_{x_2,y_2,z_1-1}\\
& \, + S_{x_1-1,y_1-1,z_2} + S_{x_1-1,y_2,z_1-1} + S_{x_2,y_1-1,z_1-1} - S_{x_1-1,y_1-1,z_1-1}
\end{align*}
$$

Hai công thức trên được xây dựng thông qua phương pháp bao hàm - loại trừ. Bạn đọc có thể tham khảo bài viết [Bao hàm - Loại trừ](https://vnoi.info/wiki/translate/he/Number-Theory-7.md) trên VNOI Wiki để hiểu rõ hơn lý do có được công thức trên.

Ta cũng có thể áp dụng phương pháp này để mở rộng cho các mảng $n$-chiều. Tuy nhiên, do số lượng bài toán liên quan đến mảng trong không gian từ 4 chiều trở lên là cực hiếm, mảng cộng dồn trong không gian này gần như không có ứng dụng thực tiễn. Vì thế, bài viết xin giới hạn lại tại mảng cộng dồn trong không gian 3 chiều trở xuống.

### Mảng hiệu hai chiều

Trước khi bắt đầu xây dựng mảng hiệu 2 chiều, ta cần định nghĩa thêm 2 khái niệm sau cho một mảng $A$ hai chiều có kích thước $m \times n$:

- $D_{hàng}(A)$ gồm $m$ hàng, hàng thứ $i$ biểu thị mảng hiệu của mảng gồm toàn bộ phần tử nằm trên hàng đó.
- $D_{cột}(A)$ gồm $n$ cột, cột thứ $i$ biểu thị mảng hiệu của mảng gồm toàn bộ phần tử nằm trên cột đó.

Trong không gian 1 chiều, ta thấy được $S(D(A)) = A$. Để tính chất này được áp dụng cho mảng 2 chiều, ta tạo mảng $A'$ thỏa: $A_{i, j}^{'}= A_{i, j}$ với $i, j$ dương và $A_{i, j} = 0$ với $i = 0$ hoặc $j = 0$. Mảng $A'$ này đánh số theo dạng 0-indexed và có kích thước là $(m + 1) \times (n + 1)$. Khi này, mảng hiệu của $A$ sẽ là mảng $D$ thỏa $S(D) = A'$.

Đặt $D = D_{cột}(D_{hàng}(A))$, khi này, ta có:

$$
\begin{align*}
D_{i, j} &= [D_{cột}(D_{hàng}(A))]_{i, j} \\
&= [D_{hàng}(A_i)]_j - [D_{hàng}(A_{i - 1})]_j \\
&= (A_{i, j} - A_{i, j - 1}) - (A_{i - 1, j} - A_{i - 1, j - 1}) \\
&= A_{i, j} - A_{i, j - 1} - A_{i - 1, j} + A_{i - 1, j - 1}
\end{align*}
$$

Mảng $S(D)$ có giá trị như sau:

$$
\begin{align*}
\displaystyle
S(D)_{i,j} &= \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} D_{t_i,t_j}\\
&=\sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} (A_{t_i, t_j} - A_{t_i, t_j - 1} - A_{t_i - 1, t_j} + A_{t_i - 1, t_j - 1})\\
&=\sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i, t_j} - \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i, t_j - 1} - \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i - 1, t_j} + \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i - 1, t_j - 1}\\
&=\sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j} A_{t_i, t_j} - \sum_{t_i\,=\,1}^{i} \sum_{t_j\,=\,1}^{j-1} A_{t_i, t_j} - \sum_{t_i\,=\,1}^{i-1} \sum_{t_j\,=\,1}^{j} A_{t_i, t_j} + \sum_{t_i\,=\,1}^{i-1} \sum_{t_j\,=\,1}^{j-1} A_{t_i, t_j}\\
&= S_{i,j} - S_{i-1,j} - S_{i,j-1} + S_{i-1,j-1} \\
&= {A'}_{i, j} \\
\end{align*}
$$

Ta kết luận rằng $S(D) = A'$, mảng $D$ ta vừa dựng chính là mảng hiệu của $A$.

![](https://i.imgur.com/w7txGHE.png)

Từ các quan sát trên, ta có thể dựng mảng hiệu của $A$ bằng hai cách:

- Sử dụng trực tiếp công thức:
  $D_{i, j} = A_{i, j} - A_{i, j - 1} - A_{i - 1, j} + A_{i - 1, j - 1}$
- Tính $D_{hàng}$ cho từng hàng của $A$ và gán kết quả vào $A'$, sau đó tính $D_{cột}$ cho từng cột của $A'$.

Code dưới đây dựng mảng hiệu 2 chiều $D$ theo $A$ theo cách thứ nhất:

```cpp
vector< vector<int> > build2DDifferenceArray(const vector< vector<int> >& a) {
    int m = (int)a.size(), n = (int)a[0].size();
    vector< vector<int> > differenceArray(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            differenceArray[i][j] = a[i][j];
            if (i > 0) differenceArray[i][j] -= a[i - 1][j];
            if (j > 0) differenceArray[i][j] -= a[i][j - 1];
            if (i > 0 && j > 0) differenceArray[i][j] += a[i - 1][j - 1];
        }
    }

    return differenceArray;
}
```

Quay lại bài toán cũ trong không gian 1 chiều: làm thế nào để ta tăng thêm một lượng $k$ lên toàn bộ phần tử trong lưới $[r_1, r_2] \times [c_1, c_2]$ một cách hiệu quả? Khi ta tính $D_{hàng}$ cho từng hàng của $A$, ta nhận thấy chỉ giá trị của phần tử ở biên trái (tại $c_1$) và biên phải (tại $c_2 + 1$). Tiếp tục tính $D_{cột}$ cho từng cột của mảng $D_{hàng}(A)$, quan sát tương tự cho thấy chỉ phần tử tại $r_1$ và $r_2 + 1$ sẽ bị tác động bởi thao tác cập nhật này.

Từ nhận xét trên, ta thấy chỉ có 4 phần tử của $D(A)$ sẽ bị tác động bởi thao tác này là tọa độ $(r_1, c_1)$, $(r_1, c_2 + 1)$, $(r_2 + 1, c_1)$ và $(r_2 + 1, c_2 + 1)$ - trong đó, phần tử tại $(r_1, c_1)$ và $(r_2 + 1, c_2 + 1)$ tăng thêm lượng $k$, phần tử tại $(r_1, c_2 + 1)$ và $(r_2 + 1, c_1)$ trừ đi lượng $k$. Ta dễ dàng cập nhật đoạn trên mảng hai chiều với độ phức tạp $\mathcal{O}(1)$.

### Mảng hiệu ba chiều

Cũng như mảng cộng dồn, ta cũng có thể dựng mảng hiệu của các mảng trong không gian 3 chiều. Tương tự, nếu ta coi $D$ là mảng sinh ra mảng cộng dồn $A$, ta có công thức dựng $D$ sau:

$$
\begin{align*}
D_{i,j,k} &= A_{i,j,k} - A_{i-1,j,k} - A_{i,j-1,k} - A_{i,j,k-1} \\
& \, + A_{i-1,j-1,k} + A_{i-1,j,k-1} + A_{i,j-1,k-1} - A_{i-1,j-1,k-1}
\end{align*}
$$

Để xử lý truy vấn cập nhật toàn bộ phần tử trong không gian $[x_1, x_2] \times [y_1, y_2] \times [z_1, z_2]$, ta cần cập nhật giá trị tại $8$ vị trí, các vị trí đều nằm tại biên của không gian. Nếu ta coi mảng $n$-chiều như một hình lập phương chứa số, vị trí cần cập nhật sẽ tương ứng với đỉnh của hình lập phương đại diện cho không gian cần cập nhật. Ta sẽ tô xen kẽ các đỉnh này theo hai màu đen - trắng, đỉnh có tọa độ $(x_1, y_1, z_1)$ được tô màu trắng. Phần tử $D$ ứng với các đỉnh trắng được cộng thêm lượng $k$, ngược lại, phần tử ứng với đỉnh đen thì trừ đi lượng $k$.

![](https://i.imgur.com/jO0h9zp.png)

Hình trên minh họa những vị trí mà ta cần cập nhật trên mảng hiệu. Tương tự mảng cộng dồn, phương pháp [bao hàm - loại trừ](https://vnoi.info/wiki/translate/he/Number-Theory-7.md) được áp dụng để đưa đến kết luận này.

## Mở rộng sang mảng động

Trong các ví dụ đã đề cập, các bài toán chúng ta phải giải đều không có truy vấn cập nhật hoặc toàn bộ truy vấn cập nhật được thực hiện trước truy vấn hỏi. Tuy nhiên, trong một số bài toán yêu cầu phải thực hiện xen kẽ hai loại truy vấn này, ta cần sử dụng các cấu trúc dữ liệu để giải quyết hiệu quả các truy vấn này.

Có hai dạng bài toán liên quan đến mảng cộng dồn và mảng hiệu:

- **Dạng 1:** Cập nhật giá trị của $A_i$ hoặc tính tổng của $i$ phần tử đầu tiên.
- **Dạng 2:** Cập nhật toàn bộ giá trị từ $A_i$ đến $A_j$ $(i \le j)$ hoặc cho biết giá trị hiện tại của $A_i$.

Nếu bài toán chỉ xử lý một trong hai dạng nói trên, ta có thể áp dụng cấu trúc dữ liệu [Binary Indexed Tree](https://vnoi.info/wiki/algo/data-structures/fenwick.md) để giải quyết các truy vấn trên. Độ phức tạp của từng truy vấn sẽ phụ thuộc vào số chiều của mảng, thí dụ, thao tác trên mảng 1D sẽ cho độ phức tạp $\mathcal{O}(\log n)$ còn trên mảng 2D sẽ là $\mathcal{O}(\log^2 n)$.

Trong một số bài toán yêu cầu xử lý kết hợp 2 dạng (cập nhật đoạn và tính tổng đoạn), ta thường áp dụng [Segment Tree](https://vnoi.info/wiki/algo/data-structures/segment-tree-extend.md) có lazy propagation (cập nhật lười). Mặc dù có chung độ phức tạp, cách cài đặt này thường khó hơn, có thời gian chạy lâu hơn và dùng nhiều bộ nhớ hơn so với cài đặt Binary Indexed Tree. Nếu ta làm việc trên mảng 1 chiều, ta cũng có thể biến đổi hệ thức giữa mảng hiệu và mảng cộng dồn để cài đặt trực tiếp BIT làm việc trên các truy vấn này. Bạn đọc có thể tham khảo thêm cách cài đặt này tại [đây](https://vnoi.info/wiki/algo/data-structures/fenwick.md#truy-v%E1%BA%A5n-tr%C3%AAn-%C4%91o%E1%BA%A1n).

## Bài tập

### Mảng cộng dồn 1 chiều

[VNOJ - NKSEQ](https://oj.vnoi.info/problem/nkseq)

[CSES - Subarray Sums II](https://cses.fi/problemset/task/1661)

[CSES - Subarray Divisibility](https://cses.fi/problemset/task/1662)

[Codeforces - Good Subarrays](https://codeforces.com/contest/1398/problem/C)

[Codechef - XXOR](https://www.codechef.com/problems/XXOR)

### Mảng hiệu 1 chiều

[Codeforces - Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C)

[Codeforces - Greg and Array](https://codeforces.com/contest/296/problem/C)

[Codeforces Gym - 319055E](https://codeforces.com/group/1rv4rhCsHp/contest/319055/problem/E) (lưu ý: để xem nội dung bài tập cần tham gia nhóm tại [link đây](https://codeforces.com/group/1rv4rhCsHp))

### Mảng cộng dồn nhiều chiều

[CSES - Forest Queries](https://cses.fi/problemset/task/1652)

[USACO - The Lazy Cow](http://www.usaco.org/index.php?page=viewproblem2&cpid=416)

[USACO - Painting the Barn](http://www.usaco.org/index.php?page=viewproblem2&cpid=923)

[VNOJ - MAXCUB](https://oj.vnoi.info/problem/maxcub)

### Mảng hiệu nhiều chiều

[Codechef - COW3E](https://www.codechef.com/COW42020/problems/COW3E)

[WCIPEG - CAKE](https://wcipeg.com/problem/cake)

VNOJ có phân loại riêng các bài tập về mảng cộng dồn, bạn đọc có thể tham khảo tại [đây](https://oj.vnoi.info/tags/?tag_id=prefix_sum).

## References

[WCIPEG - Prefix sum array and difference array](http://wcipeg.com/wiki/Prefix_sum_array_and_difference_array)

[cppreference.com - partial_sum](https://en.cppreference.com/w/cpp/algorithm/partial_sum)

[cppreference.com - adjacent_difference](https://en.cppreference.com/w/cpp/algorithm/adjacent_difference)