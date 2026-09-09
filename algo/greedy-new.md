---
title: Tham lam
description: 
published: true
date: 2026-09-09T13:26:15.624Z
tags: 
editor: markdown
dateCreated: 2025-12-05T15:52:25.934Z
---

# Tham lam

**Người viết:**
- Nguyễn Hoàng Dương - Trường Đại học Công nghệ, ĐHQG-HN.

**Reviewer:**
- Đoàn Quang Huy - Trường THPT Chuyên Nguyễn Tất Thành, Quảng Ngãi.
- Nguyễn Minh Nhật - Georgia Institute of Technology.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

## Giới thiệu

Tham lam là một ý tưởng cơ bản và phổ biến trong giải thuật và lập trình, chủ yếu trong việc giải các bài toán tối ưu hoá. Ở mỗi bước chạy, thuật toán tham lam sẽ luôn chọn lựa chọn "tốt nhất" hiện tại (theo tiêu chí người thiết kế giải thuật đề ra), và không xét đến ảnh hưởng của nó đến những lựa chọn tiếp theo.

Từ những bài dễ cho đến rất khó, trong bất cứ một bước suy luận nào của bài toán, đều có thể xuất hiện tư tưởng tham lam. Điều quan trọng nhất khi áp dụng tham lam vào lời giải, là chứng minh được tính đúng đắn của quy luật tham lam -- đây thường là phần khó và tinh tế nhất, đòi hỏi kinh nghiệm, khả năng suy luận và sự nhạy bén.

:::spoiler Fun fact
Chứng minh bằng thực nghiệm (proof by AC): Trong thi đấu (đặc biệt trong ICPC), nếu ý tưởng tham lam là đủ ngắn, đủ đơn giản và ta tin rằng nó đúng (hoặc nghĩ mãi vẫn không tìm ra cách để nó sai) thì ta sẽ code luôn và chứng minh bằng việc có AC hay không.
:::

Trong bài viết này, ở mỗi mục có các phần Ví dụ và Bài tập. Đối với các phần Bài tập, các bạn hãy cố gắng suy nghĩ thật kỹ và thử giải bài tập trước khi đọc lời giải.

## Những ý tưởng tham lam cơ bản

### Nguyên lý cực hạn

Đặc điểm chính của tham lam là nguyên lý cực hạn: lời giải tối ưu thường sẽ nằm ở các trường hợp biên, hoặc một nhóm nhỏ các trường hợp đặc biệt. Cách làm việc tự nhiên nhất là liệt kê một vài chiến lược ứng với các trường hợp biên đó, rồi tìm phản ví dụ để loại dần. Chiến lược nào sống sót thì ta mới tìm cách chứng minh.

#### Ví dụ: [Movie Festival - CSES](https://cses.fi/problemset/task/1629)

Cho $N$ bộ phim, mỗi bộ phim kéo dài từ thời điểm $s_i$ đến $t_i$. Bạn có thể xem được trọn vẹn nhiều nhất bao nhiêu bộ phim ?

Ta thử nghĩ một số trường hợp biên như vậy:

1. Luôn chọn bộ phim bắt đầu sớm nhất. Ở đây ta sẽ chọn A, rồi chọn D, rồi chọn E.

![schedule-case-1.png](/algo/greedy/schedule-case-1.png)

2. Luôn chọn bộ phim ngắn nhất, nếu có nhiều bộ phim ngắn nhất thì chọn bộ phim bắt đầu sớm hơn. Ở đây ta sẽ chọn bộ phim C, rồi đến A, rồi đến B.

![schedule-case-2.png](/algo/greedy/schedule-case-2.png)

3. Luôn chọn bộ phim kết thúc sớm nhất. Ở đây ta sẽ chọn 3 bộ phim C, rồi đến D, rồi đến E.

![schedule-case-4.png](/algo/greedy/schedule-case-4.png)

:::spoiler Lời giải và chứng minh
Dưới đây là phản ví dụ cho 2 trường hợp 1 và 2:

![counter-case.png](/algo/greedy/counter-case.png)

Ở chiến lược 1, khi xem bộ phim bắt đầu sớm nhất, nó hoàn toàn có thể dài đến mức đè hết lên các bộ phim còn lại, còn ở chiến lược 2, nếu bộ phim ngắn nhất ấy giao nhau với quá nhiều bộ phim khác, thì cũng khiến lựa chọn không tối ưu. Việc xét trường hợp cẩn thận, tự phản biện và tìm ra phản ví dụ là một kĩ năng quan trọng khi tiếp cận bài toán bằng tham lam.

Chiến lược thứ 3 là lời giải đúng cho bài toán cổ điển này.

Thật vậy, xét thời điểm ta đang chọn bộ phim tiếp theo, và gọi $X$ là bộ phim kết thúc sớm nhất trong số các bộ phim còn có thể xem. Giả sử một lời giải nào đó chọn bộ phim $Y \ne X$, tức $Y$ kết thúc muộn hơn $X$. Nếu ta có thể chọn một bộ phim để xem sau $Y$, thì bộ phim đó cũng có thể xem sau $X$, bởi vì $X$ kết thúc trước. Do đó, tập hợp các bộ phim có thể xem sau $Y$ là một tập con của các bộ phim có thể xem sau $X$: thay $Y$ bằng $X$ trong lời giải đó, ta được một lời giải không ít phim hơn. Hay nói cách khác, luôn tồn tại một lời giải tối ưu bắt đầu bằng $X$.

Sau khi chọn $X$, bài toán còn lại trên các bộ phim bắt đầu sau khi $X$ kết thúc có đúng dạng của bài toán ban đầu, nên ta áp dụng lại lập luận trên. Quy nạp theo số bộ phim, ta có điều phải chứng minh.
:::

#### Ví dụ: [Tasks and Deadlines - CSES](https://cses.fi/problemset/task/1630)

Bạn có $n$ công việc cần xử lý. Mỗi công việc có thời lượng $t_i$ và hạn chót $d_i$. Bạn sẽ xử lý chúng liên tiếp và tuần tự theo thứ tự tuỳ chọn, bắt đầu từ thời điểm $0$. Phần thưởng của một công việc là $d_i - f_i$ điểm (có thể âm) với $f_i$ là thời điểm hoàn thành công việc đó. 

Nếu hành động tối ưu, phần thưởng tối đa là bao nhiêu?

:::spoiler Lời giải và chứng minh
Quy luật tham lam đúng là làm các công việc theo thời lượng tăng dần và không quan tâm đến hạn chót. Thật vậy, xét 2 công việc $X, Y$ liên tiếp có thời lượng lần lượt là $a, b$ và $a > b$:

![task_schedule.png](/algo/greedy/task_schedule.png)

Khi này bằng việc đảo thứ tự $X$ và $Y$, ta sẽ thiệt $b$ điểm từ $X$ nhưng sẽ được thêm $a$ điểm từ $Y$ nên tổng điểm sẽ tăng thêm $a - b > 0$, qua đó ta nhận được kết quả tốt hơn. Mọi thứ tự công việc chưa được sắp xếp tăng dần theo thời lượng đều tồn tại ít nhất một cặp công việc kề nhau như vậy, và mỗi lần đổi chỗ như trên thì ta được kết quả tốt hơn. Qua đó ta suy ra được thứ tự sắp xếp tăng dần theo thời lượng cho kết quả tối ưu, tức điều phải chứng minh.
:::

### Tìm cận và dựng nghiệm

Một cách khác để áp dụng nguyên lý cực hạn, là tìm cận trên/cận dưới của đáp án theo yêu cầu đề bài, và chỉ ra cách dựng ra một nghiệm thoả mãn cận đó. Khi đó tính tối ưu của nghiệm là hiển nhiên.

#### Ví dụ: [ARC120D - Bracket Score 2](https://atcoder.jp/contests/arc120/tasks/arc120_d)

Cho dãy số nguyên $a$ có $2N$ phần tử. Xét một dãy ngoặc đúng $S$ bất kì độ dài $2N$, với mỗi vị trí $i$ có ngoặc mở ta tìm vị trí ngoặc đóng $j$ tương ứng với nó và giá trị của $S$ tăng thêm một lượng $|a_i - a_j|$. Dựng dãy ngoặc đúng ứng với dãy $a$ có giá trị lớn nhất.

Ví dụ, với dãy số và dãy ngoặc sau:

![bracket_sample.png](/algo/greedy/bracket_sample.png)

Ta có giá trị là:

$$
v(S) = |3 - 1| + |1 - 9| + |4 - 6| + |8 - 2| + |5 - 9| + |7 - 8| = 23
$$


:::spoiler Lời giải và chứng minh

**Phần 1: Cận trên**

Tổng giá trị của dãy ngoặc là $\sum_{(i, j) \in Pairs} |a_i - a_j|$. Ta biết rằng $|x - y| = \max(x, y) - \min(x, y)$. Do đó, giá trị của dãy ngoặc có thể viết lại thành:

$$
S = \sum_{(i, j) \in Pairs} (\max(a_i, a_j) - \min(a_i, a_j))
$$

Theo đó, giá trị tối đa không thể vượt quá: (Tổng $N$ số lớn nhất) - (Tổng $N$ số nhỏ nhất). Ta chứng minh luôn tồn tại dãy ngoặc đạt được giá trị này.

**Phần 2: Dựng dãy** 

Ta cần chỉ ra một cách phân chia dãy $2N$ phần tử thành tập $\mathbf{0}$ ($N$ phần tử nhỏ nhất) và tập $\mathbf{1}$ ($N$ phần tử lớn nhất) và một dãy ngoặc đúng sao cho mỗi cặp ngoặc $(i, j)$ đều gồm một phần tử thuộc $\mathbf{0}$ và một phần tử thuộc $\mathbf{1}$. 

Ta sử dụng cấu trúc dữ liệu `stack`. Xét phần tử thứ $i$ trong mảng:

1. Nếu stack rỗng, hoặc phần tử hiện tại cùng tập với đỉnh stack, ta thêm chỉ số $i$ vào đỉnh stack, khi này vị trí thứ $i$ sẽ là ngoặc mở.
2. Nếu stack không rỗng và phần tử thứ $i$ khác tập với phần tử ở đỉnh stack có chỉ số $j < i$, ta ghép được $j$ với $i$ là cặp ngoặc tương ứng, với $j$ là ngoặc mở và $i$ là ngoặc đóng.

**Phần 3: Chứng minh** 

Ta chứng minh cách dựng trên cho ra một dãy ngoặc đúng và đạt cận trên.

Trước hết, ở mọi thời điểm stack chỉ chứa các phần tử của cùng một tập, vì ta chỉ đẩy thêm vào khi phần tử mới cùng tập với đỉnh stack. Tiếp theo, khi kết thúc stack phải rỗng. Thật vậy, giả sử còn $t > 0$ phần tử, chúng cùng thuộc một tập, gọi là $T$. Ta đã ghép được $(2N - t)/2$ cặp, mỗi cặp chứa đúng một phần tử của $T$, nên $|T| = (2N - t)/2 + t = N + t/2 > N$, mâu thuẫn với việc mỗi tập có đúng $N$ phần tử.

Thuật toán in ra ngoặc mở mỗi khi đẩy vào stack, ngoặc đóng mỗi khi lấy ra, không bao giờ lấy ra khi stack rỗng, và kết thúc với stack rỗng. Điều này thoả mãn tính chất của dãy ngoặc đúng. Cuối cùng, ta đã ghép đủ $N$ cặp, mỗi cặp gồm hai phần tử thuộc hai tập khác nhau, nên giá trị thu được chính là cận trên của bài toán. Ta có điều phải chứng minh.
:::

:::spoiler Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Lưu giá trị và chỉ số ban đầu để sort
    vector<pair<int, int>> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }

    // Sắp xếp để phân loại N số nhỏ và N số lớn
    sort(a.begin(), a.end());

    // type[i] = 0 nếu a[i] thuộc nhóm nhỏ, 1 nếu thuộc nhóm lớn
    vector<int> type(2 * n);
    for (int i = 0; i < n; ++i) type[a[i].second] = 0;     // N số nhỏ nhất
    for (int i = n; i < 2 * n; ++i) type[a[i].second] = 1; // N số lớn nhất

    stack<int> st; // Lưu loại (0 hoặc 1) của ngoặc mở chưa được ghép
    string ans = "";

    for (int i = 0; i < 2 * n; ++i) {
        // Nếu stack không rỗng và phần tử hiện tại khác loại với đỉnh stack
        // => Ghép được cặp |nhỏ - lớn| => Đóng ngoặc
        if (!st.empty() && st.top() != type[i]) {
            ans += ')';
            st.pop();
        } 
        // Ngược lại: Cùng loại hoặc stack rỗng => Phải mở ngoặc mới
        else {
            ans += '(';
            st.push(type[i]);
        }
    }

    cout << ans << endl;

    return 0;
}
```

:::

### Các kết quả thường dùng

#### Ví dụ: Bất đẳng thức hoán vị

Cho hai dãy $a_1 \le a_2 \le \dots \le a_n$ và $b_1 \le b_2 \le \dots \le b_n$. Trong mọi cách ghép cặp $a_i$ với $b_{\sigma(i)}$ ($\sigma$ là một hoán vị), tổng $\sum a_i b_{\sigma(i)}$ lớn nhất khi ghép cùng chiều ($\sigma$ là hoán vị đồng nhất) và nhỏ nhất khi ghép ngược chiều ($a_i$ với $b_{n-i+1}$).

:::spoiler Chứng minh
Giả sử trong cách ghép có $i < j$ mà $a_i$ ghép với $b_p$, $a_j$ ghép với $b_q$ với $p > q$ (ghép chéo). Đổi lại cho $a_i$ ghép $b_q$, $a_j$ ghép $b_p$, tổng thay đổi một lượng $(a_i b_q + a_j b_p) - (a_i b_p + a_j b_q) = (a_j - a_i)(b_p - b_q) \ge 0$. Vậy mỗi khi ta tháo một cặp chéo thì tổng không giảm, và khi không còn cặp chéo nào thì ta đang ghép hai dãy tăng cùng chiều và có điều phải chứng minh. Ý nhỏ nhất chứng minh tương tự.
:::

#### Ví dụ: Cực tiểu hoá tổng

Cho một mảng $N$ số $a_1 \le a_2 \le \dots \le a_n$. Tìm $x$ sao cho biểu thức sau đạt giá trị nhỏ nhất:

$$S = \sum_{i = 1}^{N} |a_i - x|^k$$

Ta sẽ tập trung vào hai trường hợp cơ bản và phổ biến nhất, có nhiều ứng dụng trong các bài toán: $k = 1$ và $k = 2$.

**Trường hợp 1:** $k = 1, S = \sum_{i = 1}^{N} |a_i - x|$

Giá trị $x$ tối ưu khi này nằm trong **khoảng trung vị** của mảng $a$. Nói như vậy vì khi $n$ chẵn thì mảng sẽ có 2 trung vị, khi này tất cả $x$ nằm giữa 2 trung vị này cũng sẽ tối ưu. Nếu $n$ lẻ thì $x$ là trung vị đúng của mảng.

:::spoiler Chứng minh
Ta viết lại tổng $S$ bằng cách gom cặp các phần tử đầu và cuối:

$$
S = (|x - a_1| + |x - a_n|) + (|x - a_2| + |x - a_{n-1}|) + \dots
$$

Xét một cặp bất kỳ $(a_i, a_j)$ với $a_i \le a_j$. Theo bất đẳng thức giá trị tuyệt đối, ta luôn có:

$$
|x - a_i| + |x - a_j| = |x - a_i| + |a_j - x| \ge |a_j - a_i|
$$

Dấu "$=$" xảy ra khi và chỉ khi $a_i \le x \le a_j$. Do đó để $S$ nhỏ nhất toàn cục, $x$ phải thỏa mãn dấu bằng xảy ra cho tất cả các cặp $(a_1, a_n), (a_2, a_{n-1}), \dots$ 

Điều này nghĩa là $x$ phải thuộc giao của tất cả các đoạn $[a_i, a_{n-i+1}]$. Giao của các đoạn lồng nhau này chính là trung vị của mảng (nếu $n$ lẻ) hoặc khoảng trung vị của mảng (nếu $n$ chẵn). Tổng kết lại, ta có $x$ phải nằm trong khoảng trung vị của dãy $a$, tức điều phải chứng minh.
:::

<center>
<img src="https://hackmd.io/_uploads/ByeQnGSCxl.png">


<i>Giá trị của $S$ khi $x$ thay đổi với mảng $a$ gồm $50$ số nguyên ngẫu nhiên trong khoảng $[1; 1000]$, hai đường thẳng màu xanh thể hiện hai trung vị của dãy</i>
</center>

**Trường hợp 2:** $k = 2, S = \sum_{i = 1}^{N} (a_i - x)^2$

Giá trị $x$ tối ưu khi này sẽ là **trung bình cộng** của mảng $a$. 

:::spoiler Chứng minh
Thật vậy, ta khai triển $S$ thành

$$S = nx^2 - 2x \sum a_i + \sum a_i^2$$

Đây là tam thức bậc hai dạng $S = Ax^2 + Bx + C$ với $A = n > 0$ và có dạng một parabol với bề lõm quay lên trên. Theo kiến thức toán lớp 9, đỉnh của parabol ứng với cực tiểu của $S$ đạt tại:

$$
x = \frac{-B}{2A} = \frac{-(-2 \sum a_i)}{2n} = \frac{2 \sum a_i}{2n} = \frac{\sum a_i}{n}
$$
:::

<center>
<img src="https://hackmd.io/_uploads/rJPE2zrCge.png">

<i>Giá trị của $S$ khi $x$ thay đổi với mảng $a$ gồm $50$ số nguyên ngẫu nhiên trong khoảng $[1; 1000]$, đường thẳng màu xanh thể hiện trung bình cộng của dãy</i>
</center>

## Cấu trúc con tối ưu và tính chất lựa chọn tham lam

Một bài toán có tính chất **cấu trúc con tối ưu** nếu như nghiệm tối ưu của nó có thể thu được từ nghiệm tối ưu của các bài toán con. Tính chất này là nền của cả quy hoạch động lẫn tham lam. Điều quyết định tính đúng đắn của thuật toán tham lam là tính chất thứ hai, **tính chất lựa chọn tham lam**: ở mỗi bước, tồn tại một nghiệm tối ưu toàn cục chứa lựa chọn tối ưu cục bộ mà ta đang định thực hiện. 

### Tham lam vs. quy hoạch động

Tham lam có thể xem như một lớp trường hợp đặc biệt của lớp các bài toán Quy hoạch động. Quy hoạch động chỉ cần tính chất cấu trúc con tối ưu: ở mỗi bước nó *giải mọi bài toán con ứng với mọi lựa chọn, rồi mới quyết định*. Tham lam ngoài điều kiện đó sử dụng thêm tính chất lựa chọn tham lam để đảo ngược thứ tự ấy: *quyết định lựa chọn trước, rồi giải đúng bài toán con ứng với lựa chọn đó*. Do đó về lý thuyết, một bài toán có thể giải được bằng tham lam cũng có thể giải được bằng quy hoạch động, nhưng không phải ngược lại. 

Tính chất lựa chọn tham lam chính là mấu chốt giúp giảm không gian trạng thái của bài toán xuống đáng kể, nên một lời giải tham lam đúng sẽ có độ phức tạp thấp hơn và nhanh hơn so với lời giải quy hoạch động cho cùng một bài toán. Đối với các bài toán tối ưu tổ hợp ở mức NP-khó (như bài toán Người giao hàng), các thuật toán tham lam dù không thể đưa ra lời giải tối ưu toàn cục, nhưng cũng có thể đưa ra những xấp xỉ tốt và nhanh, có thể áp dụng trong thực tế.

> Ví dụ, bài toán tìm đường đi ngắn nhất trên đồ thị trọng số không âm có thể giải bằng tham lam sử dụng thuật toán Dijkstra với độ phức tạp $\mathcal{O}((V + E) \log V)$, cũng như có thể giải bằng quy hoạch động sử dụng thuật toán Bellman-Ford với độ phức tạp $\mathcal{O}(E V)$. Ta biết rằng thuật toán Dijkstra sẽ luôn chạy nhanh hơn, tuy nhiên nếu đồ thị có trọng số âm thì Dijkstra sẽ không thể giải được mà phải sử dụng Bellman-Ford.

Ta cùng đến với một số ví dụ khác.

### Ví dụ: Chia tiền xu

Tìm số đồng xu ít nhất cần để trả được $x$ đồng bằng các đồng tiền có mệnh giá $c = [1, 2, 5]$.

:::spoiler Lời giải
Với tập $c$ như trên, việc tham lam luôn chọn mệnh giá lớn nhất để trả sẽ cho kết quả tối ưu. Chẳng hạn với mệnh giá $n$, chừng nào $n \ge 5$ thì ta sẽ luôn trả bằng 5 đồng, đưa về bài toán con với mệnh giá $n - 5$. Rồi ta làm tương tự với các mệnh giá nhỏ hơn cho đến hết.

Bây giờ đổi tập mệnh giá thành $c = [1, 3, 4]$ và trả 6 đồng. Tham lam cho $4 + 1 + 1$, ta cần 3 đồng; còn tối ưu là $3 + 3$, chỉ cần hai đồng. Cấu trúc con tối ưu vẫn còn nguyên -- trả $n$ tối ưu vẫn bao gồm trả $n - c$ tối ưu với $c$ là đồng đầu tiên nào đó, và đó là lý do quy hoạch động vẫn giải được -- nhưng tính chất lựa chọn tham lam đã mất: không có nghiệm tối ưu nào chứa đồng 4.

Tập các mệnh giá mà ta có thể tham lam để trả được ít đồng xu nhất gọi là hệ chuẩn tắc (canonical system), các bạn có thể dễ thấy sự hữu ích và tiện lợi của nó trong hệ thống tiền tệ của các quốc gia hiện tại. Việc kiểm tra một hệ mệnh giá có chuẩn tắc hay không cũng là một bài toán thú vị (các bạn có thể đọc thêm trong Phụ lục), còn với các tập mệnh giá không chuẩn tắc thì ta phải sử dụng Quy hoạch động.
:::

### Ví dụ: Cái túi phân số và cái túi 0/1

Có $n$ món đồ, món $i$ có khối lượng $w_i$ và giá trị $v_i$, và một cái túi sức chứa $W$. Ở bài toán **cái túi phân số**, ta được lấy một phần bất kỳ của mỗi món (lấy tỉ lệ $x$ của món $i$ thì được $x v_i$ giá trị và tốn $x w_i$ sức chứa); ở bài toán **cái túi 0/1**, mỗi món chỉ được lấy nguyên hoặc không lấy. Cả hai đều hỏi giá trị lớn nhất bỏ được vào túi.

:::spoiler Lời giải và chứng minh

Với bài toán cái túi phân số, ta có thuật toán sau: 

1. Sắp xếp các món đồ theo tỉ lệ giá trị trên khối lượng $v_i / w_i$ giảm dần
2. Với mỗi món, nếu còn đủ chỗ thì ta lấy hết cả món đó, nếu không thì lấy một phần. 

**Chứng minh:** Gọi món $1$ là món có tỉ lệ cao nhất. Giả sử một nghiệm tối ưu chưa lấy hết món $1$ dù túi đã đầy; khi đó nó có lấy một lượng khối lượng $\delta > 0$ nào đó của một món $j$ khác. Bỏ $\delta$ khối lượng của món $j$, thay bằng $\delta$ khối lượng của món $1$, giá trị thay đổi một lượng $\delta (v_1 / w_1 - v_j / w_j) \ge 0$. Vậy tồn tại nghiệm tối ưu lấy hết món $1$ (hoặc lấy đầy túi bằng món $1$ nếu $w_1 \ge W$), phần còn lại là bài toán con cùng dạng.

Với cái túi 0/1, lập luận trên sẽ sai ở chỗ "thay $\delta$ khối lượng" vì khi này ta không còn được lấy một phần nữa. Với phản ví dụ sau: $W = 50$, ba món $(w, v) = (10, 60), (20, 100), (30, 120)$. Tỉ lệ giảm dần là $6, 5, 4$, tham lam lấy hai món đầu được $160$, nhưng lấy hai món sau được $220$. Bài toán khi này có cấu trúc con tối ưu và có thể giải bằng quy hoạch động $O(nW)$ quen thuộc nhưng không còn tính chất lựa chọn tham lam nữa.
:::

### Bài tập: [Missing Coin Sum - CSES](https://cses.fi/problemset/task/2183)

Cho 1 tập các đồng xu có mệnh giá $c_1, \dots, c_n$. Tìm mệnh giá nhỏ nhất không trả được bằng một tập con phân biệt của các đồng xu trên. Ví dụ với tập các đồng xu $\{1, 2, 5\}$ thì ta có thể trả được $3 = 1 + 2$ nhưng không có tập con nào trả được $4$, nên đáp án là $4$.

:::spoiler Lời giải
Giả sử $c_1 < c_2 < \dots < c_n$. Ta coi $c_0 = 0$ và $c_{n + 1} = \infty$. Đặt $S_i = \sum_{j = 0}^{i}$. Khi đó ta tìm giá trị $i$ đầu tiên sao cho $S_i + 1 < c_{i + 1}$. Khi đó $S_i + 1$ chính là đáp án.

**Chứng minh:**

*Bước cơ sở:*

Xét đồng xu đầu tiên $c_1$. Ta có $S_0 = 0$. 

1. Nếu $c_1 > 1$: Theo công thức, $S_0 + 1 < c_1 \Rightarrow 1 < c_1$. Đáp án là 1. Điều này đúng vì nếu đồng xu nhỏ nhất lớn hơn 1, ta không thể tạo ra 1. 
2. Nếu $c_1 = 1$: Ta tạo được đoạn $[1, 1]$. Ta tiếp tục xét các đồng xu sau.

*Bước quy nạp:*

Giả sử với $i$ đồng xu đầu tiên, ta đã tạo được mọi giá trị nguyên liên tiếp trong đoạn $[0, S_i]$ (bao gồm 0 là tập rỗng). Xét đồng xu tiếp theo là $c_{i+1}$. Khi thêm $c_{i+1}$ vào, các giá trị mới ta có thể tạo ra là:

$$V_{new} = \{ x + c_{i+1} \mid x \in [0, S_i] \}$$

Trong đó ta tạo thêm được đoạn giá trị: $[c_{i+1}, S_i + c_{i+1}]$. Lúc này, tập hợp tất cả các giá trị có thể tạo được là hợp của hai đoạn:

$$
R_{i+1} = [0, S_i] \cup [c_{i+1}, S_i + c_{i+1}]
$$

Ta xét hai trường hợp của $c_{i+1}$:

1. $c_{i+1} \le S_i + 1$. Khi đó, đoạn thứ hai bắt đầu tại $c_{i+1}$, mà $c_{i+1} \le S_i + 1$. Điều này có nghĩa là đoạn thứ hai sẽ nối tiếp hoặc giao với đoạn thứ nhất. Hợp của chúng sẽ là một đoạn liên tục:

$$[0, S_i + c_{i+1}] = [0, S_{i+1}]$$

$\Rightarrow$ Ta vẫn tạo được mọi giá trị từ $1$ đến $S_{i+1}$ và quy nạp tiếp tục.

2. $c_{i+1} > S_i + 1$. Ta có $S_i + 1$ không nằm trong đoạn $[0, S_i]$ và $S_i + 1$ nhỏ hơn $c_{i+1}$ (theo giả thiết trường hợp này), nên nó cũng không nằm trong đoạn $[c_{i+1}, S_{i+1}]$. Suy ra không có cách nào tạo ra được $S_i + 1$. Theo giả thiết quy nạp, ta đã có cách tạo được hết các giá trị $1 \dots S_i$, nên $S_i + 1$ chính là giá trị nhỏ nhất không thể tạo được. Ta có điều phải chứng minh.
:::


## Exchange Argument - Lập luận hoán đổi

Ở các bài toán cơ bản chúng ta đã biết về thứ tự tham lam đơn giản. Tuy nhiên có những bài toán mà cấu trúc thứ tự của đáp án tối ưu không dễ để nhìn ra ngay. Khi này, ta sẽ đi từ trường hợp đơn giản khi chỉ có $N = 2$ phần tử. Bằng việc hoán đổi 2 phần tử và biến đổi tương đương các đại lượng, ta có thể biện luận được thứ tự phức tạp và tối ưu để xử lý các phần tử. Đây cũng là phương pháp phổ biến để chứng minh tính đúng đắn của thuật toán tham lam.

### Từ hoán đổi kề đến thứ tự toàn cục

Trước khi vào ví dụ, ta phát biểu bổ đề mà mọi lập luận hoán đổi đều dựa vào, và cũng đã dùng ở phần trước.

**Bổ đề.** Giả sử ta có một quan hệ "$x$ nên đứng trước $y$" giữa các phần tử, thoả hai điều kiện: 

1. Nó là một quan hệ thứ tự hợp lệ (strict weak ordering)
2. Trong bất kỳ dãy nào, đổi chỗ hai phần tử **kề nhau** đang đứng sai thứ tự không làm đáp án xấu đi. 

Khi đó dãy đã sắp xếp theo quan hệ này là tối ưu.

**Chứng minh.** Lấy một dãy tối ưu bất kỳ. Nếu nó chưa được sắp xếp, phải tồn tại hai phần tử kề nhau đứng chưa đúng thứ tự (nếu mọi cặp kề đều đúng thứ tự thì theo tính bắc cầu cả dãy đã đúng thứ tự). Ta đổi chỗ cặp đó: theo (2) đáp án không xấu đi, nên dãy mới vẫn tối ưu, và số cặp nghịch thế (tính theo quan hệ) giảm đi đúng một. Lặp lại thao tác trên sau hữu hạn bước ta thu được dãy đã sắp xếp theo quan hệ mà vẫn tối ưu. Ta có điều phải chứng minh.

Để áp dụng Exchange Argument trong các bài toán, ta cần chỉ ra điều kiện để "$x$ trước $y$" tốt hơn "$y$ trước $x$" khi chúng kề nhau, rồi sau đó phải kiểm tra điều kiện đó có phải một quan hệ thứ tự hợp lệ hay không. Điều kiện thứ hai hay bị bỏ qua, và ví dụ dưới đây sẽ minh hoạ điều này.

### Ví dụ: Chia vàng (NOIP Trung Quốc 2012)

Có một ông vua và $N$ ông quan. Ông vua muốn chia thưởng cho các ông quan theo quy tắc sau:

- Ông vua viết lên tay trái số nguyên $A$ và tay phải mình số nguyên $B$. Với mỗi ông quan, ông quan thứ $i$ viết lên tay trái số $a_i$ và tay phải số $b_i$.
- Sau khi viết xong, ông vua và $N$ ông quan xếp thành 1 hàng dọc, ông vua luôn đứng đầu hàng.
- Sau khi xếp hàng, ông quan thứ $i$ sẽ được nhận số vàng bằng tích tất cả số bên tay trái của những người đứng trước ông ta (cả ông vua và ông quan) chia cho số ở tay phải ông ta (làm tròn xuống).

Tìm cách để ông vua xếp thứ tự $N$ ông quan đứng sau mình sao cho **số vàng của ông quan được thưởng nhiều nhất là ít nhất**.

:::spoiler Ý tưởng và lời giải
Gọi $m = \prod a_j$ với $j$ đứng trước $i$, khi này ông quan thứ $i$ nhận được $\dfrac{m}{b_i}$ vàng còn ông quan thứ $i + 1$ nhận được $\dfrac{m \times a_i}{b_{i + 1}}$ vàng.

Nếu ta đảo chỗ hai ông quan $i$ và $i + 1$ thì khi này ông $i$ nhận $\dfrac{m}{b_{i + 1}}$ vàng còn ông $i + 1$ nhận được $\dfrac{m \times a_{i + 1}}{b_i}$ vàng. Những ông quan khác không bị ảnh hưởng, vì tích các số bên tay trái đứng trước họ không đổi.

Thứ tự $(i, i + 1)$ không tệ hơn thứ tự $(i + 1, i)$ khi và chỉ khi:

$$\max \left(\dfrac{m}{b_i}, \dfrac{m \times a_i}{b_{i + 1}} \right) \le \max \left (\dfrac{m}{b_{i + 1}}, \dfrac{m \times a_{i + 1}}{b_i} \right)$$

tương đương với (nhân hai vế với $\frac{b_i b_{i+1}}{m}$):

$$\max(b_{i + 1}, a_i \times b_i) \le \max(b_i, a_{i + 1} \times b_{i + 1})$$

Đến đây, việc dùng luôn bất đẳng thức trên làm hàm so sánh khi cài đặt sắp xếp có thể dẫn đến kết quả sai vì đây **không phải** một quan hệ thứ tự hợp lệ: chẳng hạn với ba ông quan $(1, 2), (1, 12), (2, 3)$, cặp thứ nhất và thứ hai "bằng nhau" theo bất đẳng thức, cặp thứ hai và thứ ba cũng "bằng nhau", nhưng để tối ưu thì $(1, 2)$ lại phải đứng ngay trước $(2, 3)$.

Để giải quyết vấn đề này, ta cần tìm một khoá sắp xếp thực sự ứng với mỗi phân tử. Ta chứng minh bổ đề sau: **sắp xếp theo $a_i b_i$ tăng dần** thì mọi cặp kề nhau đều thoả bất đẳng thức trên. Thật vậy, nếu $a_i b_i \le a_{i+1} b_{i+1}$ thì $a_i b_i \le a_{i+1} b_{i+1} \le \max(b_i, a_{i+1} b_{i+1})$, và $b_{i+1} \le a_{i+1} b_{i+1} \le \max(b_i, a_{i+1} b_{i+1})$ (do $a_{i+1} \ge 1$). Do đó suy ra $\max(b_{i+1}, a_i b_i) \le \max(b_i, a_{i+1} b_{i+1})$ (điều phải chứng minh). 

Tổng kết lại, thứ tự sắp xếp theo $a_i b_i$ tăng dần là tối ưu. Khi cài đặt, ta chỉ cần sắp xếp theo tích $a_i b_i$ rồi duyệt một lượt để tính đáp án.

:::

Trong thực tế, Exchange Argument còn được sử dụng phổ biến trong các bài toán Quy hoạch động, chủ yếu là để tìm thứ tự trong các bài toán về việc chọn một tập con tối ưu mà thứ tự thêm các phần tử sẽ ảnh hưởng đến đáp án. Ta cùng đến với một bài toán như vậy:

### Bài tập: [ABC366F - Maximum Composition](https://atcoder.jp/contests/abc366/tasks/abc366_f)

Cho $N$ hàm tuyến tính $f_i(x) = A_ix + B_i$. Tính giá trị lớn nhất của hàm hợp $f_{p_1}(f_{p_2}(\dots f_{p_K}(1) \dots))$ với $(p_1, \dots, p_K)$ là các bộ $K$ số khác nhau.

Giới hạn: $N \le 2 \times 10^5, K \le \min(N, 10), 1 \le A_i, B_i \le 50$.

:::spoiler Lời giải và chứng minh

**Phần 1: Exchange Argument**

Giả sử ta đã chọn được hàm hợp có $K$ hàm số tối ưu. Ta cần xác định thứ tự áp dụng để đạt giá trị lớn nhất. Xét 2 hàm số $f_i(x) = A_ix + B_i$ và $f_j(x) = A_jx + B_j$ được chọn. Giả sử ta áp dụng chúng liền kề nhau lên giá trị hiện tại $x$:

1. Áp dụng $i$ trước, $j$ sau $f_j(f_i(x)) = A_j(A_ix + B_i) + B_j = A_jA_ix + A_jB_i + B_j$.
2. Áp dụng $j$ trước, $i$ sau $f_i(f_j(x)) = A_i(A_jx + B_j) + B_i = A_iA_jx + A_iB_j + B_i$.

Để thứ tự $i$ trước, $j$ sau tốt hơn, ta cần có:

$$
A_jB_i + B_j > A_iB_j + B_i \iff B_i(A_j - 1) > B_j(A_i - 1)
$$

$\Rightarrow$ Hàm nào có giá trị $\frac{B}{A-1}$ lớn hơn sẽ được ưu tiên áp dụng trước. Ta sẽ sắp xếp các hàm số theo biểu thức trên, qua đó tạo thêm được giả thiết cho bài toán (từ các bộ $K$ bất kì thành các bộ $K$ có chỉ số tăng dần). Khi này ta có thể giải bằng motif Quy hoạch động quen thuộc.

**Phần 2: Quy hoạch động**

Gọi $\texttt{dp}[j]$ là giá trị lớn nhất tạo được với hàm hợp của $j$ hàm số. Duyệt qua danh sách hàm số đã sắp xếp: Với mỗi hàm $f_i(x) = A_ix + B_i$, ta xem xét việc áp dụng hàm này sau khi đã áp dụng $j-1$ hàm trước đó. Công thức chuyển trạng thái như sau:

$$\texttt{dp}[j] = \max(\texttt{dp}[j], A_i \times \texttt{dp}[j-1] + B_i)$$

Khởi tạo: $\texttt{dp}[0] = 1$ (đề bài cho $x = 1$), các vị trí khác $-\infty$.
:::

:::spoiler Cài đặt
```cpp=
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e18;

struct Func {
    int a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<Func> funcs(n);
    for (int i = 0; i < n; ++i) {
        cin >> funcs[i].a >> funcs[i].b;
    }

    // Sắp xếp theo Exchange Argument
    // Hàm nào có độ ưu tiên cao hơn (B/(A-1) lớn hơn) sẽ được xét trước
    sort(funcs.begin(), funcs.end(), [](const Func& x, const Func& y) {
        // So sánh: x.b / (x.a - 1) > y.b / (y.a - 1)
        // Chuyển vế nhân để tránh chia cho 0 và sai số số thực
        return (long long)x.b * (y.a - 1) > (long long)y.b * (x.a - 1);
    });

    // DP: dp[j] = Giá trị lớn nhất của hàm hợp đã có j hàm số
    vector<long long> dp(k + 1, -INF);
    dp[0] = 1; // Giá trị khởi đầu đề bài cho là 1

    // Với mỗi hàm, ta xem xét thêm nó vào hợp của j - 1 hàm đã áp dụng trước đó
    for (const auto& f : funcs) {
        // Duyệt ngược để đảm bảo mỗi hàm chỉ dùng 1 lần cho mỗi trạng thái
        for (int j = k; j >= 1; --j) {
            if (dp[j - 1] > -INF) {
                // Thử áp dụng hàm f vào kết quả của chuỗi j-1 hàm trước đó
                long long next_val = f.a * dp[j - 1] + f.b;
                if (next_val > dp[j]) {
                    dp[j] = next_val;
                }
            }
        }
    }

    cout << dp[k] << "\n";

    return 0;
}
```
:::

##  Regrettable Greedy - Sửa lại lựa chọn

Ta đã biết rằng thuật toán tham lam sẽ không bao giờ xét lại các lựa chọn đã đưa ra. Tuy nhiên, ở cấp độ nâng cao hơn, Regrettable Greedy là một dạng thuật toán **vẫn mang bản chất tham lam** - tại mỗi bước, thuật toán vẫn luôn đưa ra một quyết định tối ưu cục bộ ngay lập tức. Nhưng ngoài ra, nó có một cơ chế cho phép **"hối tiếc" (Regret)**: nếu ở các bước sau, thuật toán nhận ra quyết định tham lam trước đó làm ảnh hưởng đến kết quả toàn cục, nó có một cơ chế đặc biệt cho phép thu hồi một phần quyết định cũ để nhường chỗ cho lựa chọn tốt hơn.

### Ví dụ: [Time Travel](https://codeforces.com/group/7Dn3ObOpau/contest/513385/problem/A)

Cho một mảng các số **nguyên dương**. Tìm cách gán dấu âm cho nhiều phần tử nhất có thể sao cho vẫn đảm bảo **mọi tổng tiền tố** của mảng đều **dương**.

:::spoiler Ý tưởng và lời giải
Khi duyệt qua từng phần tử của mảng, ta ban đầu luôn ưu tiên gán dấu âm cho nó để tăng số lượng phần tử âm, đồng thời đẩy giá trị âm này vào một Priority Queue min (do đó sẽ trả về số âm có giá trị tuyệt đối lớn nhất) và cập nhật tổng tiền tố hiện tại.

Nếu tại bất kỳ bước nào việc đổi dấu vi phạm điều kiện tổng tiền tố dương, ta có thể quay lại, đưa những phần tử ta vừa gán dấu âm trước đó về như cũ. Để tối ưu thì ta sẽ chọn số âm trong Priority Queue đang có giá trị tuyệt đối lớn nhất và đổi lại nó về dương, khi này ta sẽ có nhiều khả năng hơn để gán dấu âm cho các phần tử tiếp theo. Để ý rằng ta chỉ cần đổi đúng một phần tử là đủ: phần tử bị đổi có giá trị tuyệt đối không nhỏ hơn phần tử vừa thêm, nên tổng tiền tố sau khi đổi ít nhất bằng tổng tiền tố ở bước trước, vốn đã dương.

Sau khi duyệt hết mảng, số lượng phần tử còn lại trong Priority Queue chính là số lượng số âm tối đa thỏa mãn đề bài. Độ phức tạp là $\mathcal{O}(N \log N)$.
:::

### Bài tập: [CF865D - Buy Low Sell High](https://codeforces.com/contest/865/problem/D)

Đây cũng là bài [ABC250G - Stonks](https://atcoder.jp/contests/abc250/tasks/abc250_g).

Bạn có thông tin giá cổ phiếu của $N$ ngày tiếp theo. Mỗi ngày bạn có thể chọn bán 1 đơn vị cổ phiếu với giá của ngày hôm đó, hoặc mua tích trữ 1 đơn vị cổ phiếu với giá của ngày hôm đó để bán sau, hoặc không làm gì. Lúc bắt đầu bạn không có cổ phiếu và sau $N$ ngày phải giao dịch được hết cổ phiếu đang có. Hỏi lợi nhuận tối đa thu được là bao nhiêu?

:::spoiler Ý tưởng và lời giải

Trong bài toán này, chúng ta sẽ "thử" giao dịch nếu thấy có lãi, nhưng sẽ lưu lại thông tin để hoàn tác giao dịch này và sửa sai trong tương lai. Ta dựng một Priority Queue thể hiện danh sách quyền mua. Tại ngày $i$ với giá $p_i$, ta làm như sau:

1. Ta luôn coi $p_i$ là một cơ hội mua tiềm năng và thêm vào PQ. Nếu $p_i$ lớn hơn quyền mua thấp nhất hiện có trong quá khứ ($p_{min}$), ta thực hiện khớp lệnh mua tại $p_{min}$ và bán tại $p_i$ để kiếm lời ngay lập tức: $p_i - p_{min}$. Việc ưu tiên chọn $p_{min}$ để khớp lệnh là chiến lược tốt nhất vì nó không chỉ tối đa hóa lợi nhuận tức thời mà còn an toàn hơn về điều kiện giao dịch (vì $p_{min}$ dễ khớp lệnh hơn). Quan trọng nhất, việc "chốt lãi" sớm này không làm mất nghiệm tối ưu toàn cục, bởi bất kỳ lợi ích tiềm năng nào của việc để dành $p_{min}$ cho tương lai đều có thể được bù đắp bởi cơ chế sửa sai ở bước sau.
2. Khi ta quyết định khớp lệnh mua ở $p_{min}$ với lệnh bán ở $p_i$, **ta vẫn đẩy $p_i$ lại vào PQ**. Thao tác này đóng vai trò như một công cụ toán học biến đổi trạng thái từ "vừa bán tại $p_i$" thành một "quyền mua ảo tại $p_i$". Nếu trong tương lai xuất hiện giá bán lời hơn $p_j > p_i$, ta sẽ dùng chính quyền mua ảo này để khớp lệnh (sửa lại lựa chọn). Khi đó, tổng lợi nhuận của chuỗi giao dịch sẽ là tổng đại số: $(p_i - p_{min}) + (p_j - p_i) = p_j - p_{min}$. Tức là việc sửa lại lựa chọn tương đương với việc ta đã đưa ra quyết định lời hơn (bán ở $p_j$) ngay từ đầu mà không vi phạm ràng buộc nào của bài toán.
:::

:::spoiler Cài đặt
```cpp=
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Min-Priority Queue để lưu giá các quyền mua (cũng như để sửa lại lựa chọn)
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    long long total_profit = 0;

    for (int i = 0; i < n; ++i) {
        long long current_price;
        cin >> current_price;

        // Luôn luôn push giá hiện tại vào PQ.
        // Ý nghĩa: Ta luôn có quyền mua cổ phiếu này tại ngày hôm nay.
        pq.push(current_price);

        // Kiểm tra xem có thể bán (hoặc sửa lại lựa chọn) để có lời không
        if (pq.top() < current_price) {
            // Giá thấp nhất trong quá khứ 
            long long buy_price = pq.top();
            
            // Cộng lợi nhuận giả định vào tổng
            total_profit += current_price - buy_price;
            
            // Xóa giá mua đó đi (vì đã được dùng để khớp với lệnh bán này)
            pq.pop();
            
            // Cơ chế sửa lại lựa chọn: Push giá cổ phiếu hiện tại vào lại PQ
            // Ý nghĩa: Ta vừa bán ở 'current_price', nhưng ta trao cho tương lai quyền 
            // "mua lại" chính cổ phiếu này với giá 'current_price' để bán ở mức cao hơn.
            // Về toán học: (p_new - p_old) + (p_future - p_new) = p_future - p_old.
            pq.push(current_price);
        }
    }

    cout << total_profit << endl;

    return 0;
}
```

:::

:::spoiler Đọc thêm: Liên hệ với bài toán Luồng cực đại

Kĩ thuật sửa lại lựa chọn này có liên hệ với bài toán tìm luồng cực đại (và thậm chí là luồng min-cost). Cách làm ngây thơ (và sai) là lặp lại việc tìm một đường đi bất kì từ nguồn đến đích còn sức chứa, rồi đẩy luồng theo đường đó. Một phản ví dụ có thể kể đến là xét đồ thị bốn đỉnh $s, u, v, t$ với các cạnh $s \to u$, $s \to v$, $u \to t$, $v \to t$ đều có sức chứa 1 và thêm cạnh $u \to v$ sức chứa 1. Nếu đường đầu tiên tìm được là $s \to u \to v \to t$, ta đẩy được 1 đơn vị và sau đó không còn đường nào: $s \to u$ đã đầy, $v \to t$ đã đầy. Nhưng luồng cực đại là 2 ($s \to u \to t$ và $s \to v \to t$).

Thuật toán cơ bản và dễ tiếp cận nhất của bài toán luồng cực đại là Ford-Fulkerson sửa điều này bằng cách thêm **cạnh ngược**: mỗi khi đẩy $f$ đơn vị qua cạnh $u \to v$, ta thêm cạnh ngược $v \to u$ với sức chứa $f$. Đường tăng luồng đi qua cạnh ngược có nghĩa là "rút lại" một phần luồng đã đẩy trước đó. Trong ví dụ trên, sau bước đầu ta có đường $s \to v \to u \to t$, trong đó $v \to u$ là cạnh ngược: nó huỷ quyết định đẩy luồng qua $u \to v$, và kết quả là hai đường $s \to u \to t$, $s \to v \to t$ như mong muốn. Toàn bộ mục này là những bài toán mà ta có thể cài đặt một cơ chế "cạnh ngược" như vậy một cách gọn hơn nhiều so với việc dựng đồ thị luồng thật sự.

:::

## Tham lam và tìm kiếm nhị phân

Một kiểu mẫu rất phổ biến khác trong lập trình thi đấu là tham lam không đứng một mình mà đóng vai trò hàm kiểm tra cho tìm kiếm nhị phân. Nếu đáp án có tính đơn điệu -- "làm được với $X$" kéo theo "làm được với mọi $X' \ge X$" -- thì ta có thể giải bài toán bằng tìm kiếm nhị phân trên $X$, với mỗi $X$ cần trả lời nhanh câu hỏi có/không. Câu hỏi có/không này thường dễ hơn hẳn bài toán tìm $X$ tối ưu ban đầu, và tham lam là một trong những công cụ tự nhiên để trả lời nó.

### Ví dụ: [Array Division - CSES](https://cses.fi/alon/task/1085)

Cho mảng $n$ số nguyên dương, chia mảng thành $k$ đoạn liên tiếp sao cho tổng lớn nhất trong các đoạn là nhỏ nhất. In ra tổng nhỏ nhất này.

:::spoiler Lời giải và chứng minh

Ta giải bài toán này bằng tìm kiếm nhị phân đáp án. Với $X$ cố định, câu hỏi là: có chia được thành không quá $k$ đoạn, mỗi đoạn tổng $\le X$ hay không? Ta có thể giải bài toán này bằng tham lam đơn giản: duyệt từ trái sang phải, cứ thêm phần tử vào đoạn hiện tại chừng nào tổng còn $\le X$, nếu không được nữa thì mở đoạn mới. Nếu số đoạn $\le k$ thì trả lời có. (Chia được thành ít đoạn hơn $k$ thì cũng chia được thành đúng $k$ đoạn, bằng cách tách nhỏ một đoạn nào đó.) 

Vì sao tham lam trả lời đúng? Gọi $r_1 < r_2 < \dots$ là các vị trí kết thúc đoạn của tham lam, và $r'_1 < r'_2 < \dots$ là của một cách chia hợp lệ bất kỳ. Ta chứng minh $r_j \ge r'_j$ với mọi $j$ bằng quy nạp: đoạn thứ $j$ của tham lam bắt đầu tại $r_{j-1} + 1 \ge r'_{j-1} + 1$, tức không sớm hơn đoạn thứ $j$ của cách chia kia. Vì các phần tử đều dương, đoạn $[r_{j-1} + 1, r'_j]$ là một phần của đoạn $[r'_{j-1} + 1, r'_j]$ nên có tổng $\le X$, và tham lam kéo dài tối đa nên kết thúc không sớm hơn $r'_j$. Do đó tham lam dùng số đoạn ít nhất trong mọi cách chia hợp lệ; nếu tham lam cần nhiều hơn $k$ đoạn thì không có cách chia mảng thoả mãn.

Độ phức tạp của bài toán là $O(n \log \sum a_i)$.
:::

## Kĩ thuật và lưu ý khi cài đặt

Việc tạo ra cấu trúc thứ tự cho dữ liệu trong thuật toán tham lam có 2 cách phổ biến sau:

1. Sắp xếp (bằng một hàm so sánh nào đó)
2. Sử dụng các cấu trúc dữ liệu duy trì thứ tự sẵn có của C++ STL: `set`, `multiset`, `map`, `priority_queue`,...

### Sắp xếp 

Hàm `std::sort` trong C++ có cú pháp như sau:

```cpp
// ví dụ, với vector s
sort(s.begin(), s.end(), func)   // sắp xếp theo func
sort(s.rbegin(), s.rend(), func) // sắp xếp theo thứ tự ngược lại của func
```

với `func` là hàm so sánh (comparator) tuỳ chọn giữa 2 phần tử bất kì trong mảng. Nếu ta không thiết lập hàm `func` này, thì kiểu dữ liệu mà ta sử dụng phải có định nghĩa phép toán `<` của nó. Chẳng hạn, trong bài toán Chia vàng ở phần Exchange Argument, ta có thể cài đặt như sau:

```cpp=
struct Info {
    int a, b;
    bool operator<(const Info &x) const {
        return 1LL * a * b < 1LL * x.a * x.b;
    } // so sánh phần tử này với một phần tử khác (gọi là x)
};
```

### Điều kiện hợp lệ của hàm so sánh

Hàm so sánh `cmp(x, y)` (đọc là "$x$ phải đứng trước $y$" hay $x < y$) dùng cho `std::sort` và các cấu trúc STL phải là một **thứ tự yếu nghiêm ngặt** (strict weak ordering), tức thoả mãn ba điều kiện:

1. Không phản xạ: `cmp(x, x)` luôn là `false`. Nói riêng, hai phần tử "bằng nhau" thì hàm so sánh **phải trả về `false`**.
2. Bắc cầu: `cmp(x, y)` và `cmp(y, z)` kéo theo `cmp(x, z)`.
3. Quan hệ "không so sánh được" (cả `cmp(x, y)` và `cmp(y, x)` đều `false`) cũng phải thoả mãn tính chất bắc cầu: nếu có `z` sao cho cả `cmp(y, z)` và `cmp(z, y)` đều `false` thì ta cũng phải có cả `cmp(x, z)` và `cmp(z, x)` đều `false`.

Điều kiện thứ ba là điều kiện hay bị quên nhất. Hàm so sánh $\max(b_{i + 1}, a_i \times b_i) \le \max(b_i, a_{i + 1} \times b_{i + 1})$ rút thẳng từ bất đẳng thức của bài Chia vàng vi phạm đúng điều kiện này: với $(a, b) = (1, 2), (1, 12), (2, 3)$, phần tử thứ nhất và thứ hai không so sánh được, thứ hai và thứ ba không so sánh được, nhưng thứ nhất lại nhỏ hơn thứ ba. 

Vi phạm thứ tự yếu nghiêm ngặt có thể gây ra hành vi không xác định (undefined behavior) trong C++: `std::sort` có thể cho thứ tự sai, và trong một số cài đặt thậm chí truy cập ngoài mảng, do đó sẽ khó debug hơn bình thường. Cách phòng tránh tốt nhất là đưa hàm so sánh về dạng so sánh một khoá `f(i) < f(j)` như đã bàn ở mục Exchange Argument.

> Qua kiểm nghiệm của tác giả, khi thử trên các bộ dữ liệu nhỏ và so với vét cạn, hàm so sánh  $\max(b_{i + 1}, a_i \times b_i) \le \max(b_i, a_{i + 1} \times b_{i + 1})$ cho đáp án sai ở khoảng 0.2% số test -- đủ hiếm để qua được các test ví dụ sơ sài, và đủ nhiều để không qua được bộ test chính thức (vốn sẽ được sinh nhiều trường hợp hiểm). Do đó việc viết hàm so sánh sai có thể gây ra lỗi rất khó nhận ra và debug (nhất là khi bạn thi những kì thi mà phải đúng hết test trong 1 bài/subtask thì mới qua được bài/subtask đó).

### Sử dụng STL

Đối với ngôn ngữ C++, ta có thể thiết lập hàm so sánh cho các cấu trúc dữ liệu STL: `set`, `priority_queue`, `map`,... bằng functor-comparator (đối tượng hàm so sánh). Có hai loại chính:

1. `less<T>`: ứng với `operator <`, mặc định các cấu trúc dữ liệu STL sẽ dùng functor này.
2. `greater<T>`: ứng với `operator >`

Chẳng hạn, `priority_queue` bình thường sẽ luôn trả về phần tử lớn nhất, bạn có thể khai báo `priority_queue<int, vector<int>, greater<int>>` để lấy phần tử nhỏ nhất.

Khi khai báo 1 struct, việc định nghĩa phép toán thứ tự `<` hoặc `>` trong struct sẽ giúp ta có thể sử dụng chúng ngay lập tức trong các cấu trúc dữ liệu STL.

Đối với C++11 trở đi, ngoài cách khai báo functor như ở trên, ta có thể khai báo dưới dạng lambda rất gọn và nhúng vào bằng từ khoá `decltype` (declared type). Lưu ý với các chuẩn C++ trước C++20 (từ C++11 đến C++17), ta phải truyền lambda vào constructor khi khai báo cấu trúc dữ liệu do ở các chuẩn đó lambda không có constructor mặc định:

```cpp
// Trước C++20:
auto cmp = [](int a, int b) { return ... };
std::set<int, decltype(cmp)> s(cmp);
std::priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

// Sau C++20:
auto cmp = [](int a, int b) { return ... };
std::set<int, decltype(cmp)> s;
std::priority_queue<int, vector<int>, decltype(cmp)> pq;
```

## Tham lam trong thực chiến

Trong phần này, chúng ta sẽ cùng đào sâu vào 2 bài toán tham lam hay đã xuất hiện trong kì thi ICPC Regional 2024 tại Hà Nội.

### Bài tập: [ICPC 2024 Regional Hanoi bài L: Locomotive Lane Logistics](https://oj.vnoi.info/problem/icpc24_regional_l)

Cho một đường ray có độ dài $s$ và $q$ truy vấn. Mỗi truy vấn có 1 trong 2 dạng:

1. `+ l v`: thêm 1 tàu có độ dài $l$ và vận tốc $v$ vào lịch trình.
2. `- l v`: xoá 1 tàu có độ dài $l$ và vận tốc $v$ khỏi lịch trình, đảm bảo trong lịch trình hiện tại có ít nhất 1 tàu như vậy.

Mỗi con tàu có phần mui và phần đuôi, khoảng cách giữa mui và đuôi của tàu chính là độ dài $l$ của nó. Con tàu sẽ xuất phát với mui chạm vạch xuất phát, đi đều liên tục với vận tốc $v$ về phía vạch kết thúc và chỉ ra khỏi đường ray khi đuôi rời khỏi vạch kết thúc. Mỗi con tàu ta có thể chọn cho nó thời điểm xuất phát là **số thực bất kì**. 

Sau mỗi truy vấn, tính tổng thời gian ít nhất để đưa toàn bộ tàu trong danh sách ra khỏi đường ray mà không xảy ra tai nạn. Tai nạn có thể xảy ra giữa 2 tàu ở thời điểm mui của tàu đi sau đâm vào đuôi của tàu đi trước, vận tốc của tàu đi sau lớn hơn tàu đi trước và tàu đi trước chưa ra khỏi đường ray. In ra đáp án tối ưu (luôn có dạng là số hữu tỉ) theo modulo $998244353$.

Giới hạn: $s \le 10^9, q \le 2 \times 10^5, 1 \le l, v \le 10^6$.

:::spoiler Lời giải

Trước tiên ta có thể rút ra 2 nhận xét tham lam đầu tiên về đáp án tối ưu:

1. Nếu 2 tàu có cùng vận tốc, thì chúng có thể đi nối đuôi nhau như là 1 tàu (vẫn thoả mãn điều kiện không xảy ra tai nạn), nên ta có thể giả sử vận tốc của tất cả các tàu đều khác nhau.
2. Để tối thiểu hoá tổng thời gian, các tàu cần di chuyển nối tiếp nhau khít nhất có thể, tàu chậm sẽ đi trước, rồi sau một khoảng thời gian tối ưu ta sẽ cho tàu nhanh hơn xuất phát và đuổi theo sau. Một cách để chứng minh nhận xét này, là tàu đi sau đã tận dụng triệt để khoảng thời gian tàu đi trước chiếm dụng đường ray để tranh thủ di chuyển được một khoảng cách nhất định.

Tiếp theo đó, bằng việc ngồi nháp toán và chứng minh công thức ta rút ra nhận xét quan trọng nhất của bài toán:

3. Giả sử có 2 tàu $T_1 = (l_1, v_1)$ và $T_ 2 = (l_2, v_2)$ với $v_1 < v_2$. Ta cho $T_1$ đi trước, $T_2$ đi sau và $T_2$ sẽ có xu hướng đuổi kịp. Để tối ưu thời gian, ta căn chỉnh sao cho ngay thời điểm đuôi $T_1$ rời khỏi đường ray thì mui của $T_2$ cũng vừa chạm vạch kết thúc. Theo đó ta có giãn cách thời gian tối ưu giữa 2 tàu:

$$
\dfrac{s + l_1}{v_1} - \dfrac{s}{v_2} = \dfrac{s}{v_1} - \dfrac{s}{v_2} + \dfrac{l_1}{v_1}
$$

4. Áp dụng nhận xét trên cho $n$ tàu, thì tổng thời gian tối ưu là: 
$$
\dfrac{s}{v_1} - \dfrac{s}{v_n} + \sum_{i = 1}^{n - 1} \dfrac{l_i}{v_i} + \dfrac{s + l_n}{v_n} = \dfrac{s}{v_1} + \sum_{i = 1}^{n} \dfrac{l_i}{v_i}
$$

**Chứng minh:** Gọi $T_1$ là tàu chậm nhất. Với các tàu xuất phát trước $T_1$, ta có đuôi của mỗi tàu phải rời vạch xuất phát trước khi mui tàu kế tiếp chạm vạch (nếu không hai tàu chồng lên nhau ngay tại vạch), nên tàu $i \ne 1$ chiếm vạch xuất phát ít nhất $\frac{l_i}{v_i}$, và $T_1$ xuất phát không sớm hơn tổng các $\frac{l_i}{v_i}$ đó. Bản thân $T_1$ cần thêm $\frac{s + l_1}{v_1}$ để ra khỏi đường ray. Cộng lại, tổng thời gian $\ge \frac{s}{v_1} + \sum_{i = 1}^{n} \frac{l_i}{v_i}$ với mọi cách sắp xếp. Các tàu xuất phát sau $T_1$ đều nhanh hơn hoặc bằng nó, mui của chúng luôn nằm sau đuôi $T_1$, nên chúng chỉ băng qua vạch kết thúc sau khi $T_1$ đã ra hẳn; tại vạch kết thúc mỗi lúc chỉ có một tàu băng qua và tàu $i$ chiếm vạch đúng $\frac{l_i}{v_i}$. Vậy nên ta thu được một cách dựng đạt được cận dưới của đáp án, nên công thức của nhận xét là tối ưu.

Để ý rằng chặn dưới không phụ thuộc thứ tự của các tàu khác ngoài $T_1$, nên qua chứng minh ở trên ta thấy rằng thật ra cho tàu nhanh đi trước cũng có thể đạt được đúng giá trị này. Nhận xét "tàu chậm đi trước" chỉ là một cách dựng, không phải điều bắt buộc.

Tổng kết lại, thuật toán cuối cùng của bài chỉ cần duy trì 2 giá trị sau qua các thao tác thêm và xoá tàu khỏi danh sách:
1. Vận tốc $v_1$ của tàu chậm nhất trong danh sách hiện tại, có thể dùng `multiset` hoặc `priority queue`.
2. Tổng $\dfrac{l_i}{v_i}$ của các tàu đang có trong danh sách hiện tại.

Độ phức tạp cho mỗi truy vấn là $\mathcal{O}(\log q)$.

:::

### Bài tập: [ICPC 2024 Regional Hanoi bài K: Kangokutou Exodus](https://oj.vnoi.info/problem/icpc24_regional_k)

Cho một mê cung gồm $n$ hành lang vuông góc liên tiếp nhau, mỗi hành lang có độ dài $l_i$. Bạn đứng ở điểm bắt đầu của hành lang $1$.

Trước khi vượt mê cung. bạn có thể chọn trước độ dài tốc biến $m$ nguyên để di chuyển từ điểm bắt đầu của hành lang $1$ đến điểm kết thúc của hành lang $n$.

Ở mỗi thời điểm nguyên bạn sẽ tốc biến đúng $m$ đơn vị độ dài về phía trước trong $1$ giây, nếu cú tốc biến này không chuẩn (khoảng cách từ điểm bạn tốc biến đến điểm cuối của hành lang hiện tại nhỏ hơn $m$ đơn vị) thì bạn sẽ tốc biến đến điểm cuối của hành lang và bị choáng $1$ giây, điều này áp dụng cả với hành lang cuối. Ngược lại, bạn có thể tốc biến tiếp ngay lập tức mà không bị choáng.

Tính thời gian ngắn nhất có thể để ra khỏi mê cung khi chọn $m$ tối ưu.

Giới hạn: $n \le 10^6, l_i \le 10^9$.

:::spoiler Lời giải

Vì quá trình di chuyển qua các hành lang là độc lập với nhau, ta có thể sắp xếp lại các hành lang theo thứ tự: $l_1 \le l_2 \le \dots \le l_n$.

Chúng ta bắt đầu với một số nhận xét tham lam như sau về đáp án tối ưu:

1. Với $m$ cho trước thì ta có công thức tổng thời gian hoàn thành:

$$ f(m) = \sum_{i = 1}^{n} \left \lceil \frac{l_i}{m} \right \rceil + [l_i \bmod m \ne 0]$$

$[x]$ là kí hiệu Iverson của biểu thức boolean $x$, với $[x] = 1$ nếu $x$ đúng và $0$ nếu $x$ sai.

2. Ta nhận thấy rằng đáp án tối ưu có cận dưới và cận trên hiển nhiên là $n$ và $2n - 1$. Cận dưới xảy ra khi toàn bộ $l_i$ bằng nhau, khi đó ta chọn $m = l_i$, còn cận trên xảy ra khi ta cho $m = l_n$. 
3. Luôn tồn tại $m$ tối ưu là một trong các $l_i$, nên ta chỉ cần xét $m \in \{l_1, l_2, \dots, l_n\}$. Thật vậy, giả sử giá trị $m$ tối ưu là $m_1$ không trùng với bất cứ $l_i$ nào. Khi này với các $l_i < m_1$ thì ta sẽ mất đúng $2$ giây để đi qua, còn với $l_i > m_1$ thì ta sẽ mất ít nhất $2$ giây để đi qua. Do đó $f(m_1) \ge 2n > 2n - 1 \ge f(l_n)$, mâu thuẫn với việc $m_1$ tối ưu. Ta có điều phải chứng minh.

Nhận xét thứ 3 gợi ý rằng chúng ta cần duyệt qua tất cả các $l_i$ khác nhau và tính nhanh được $f(l_i)$. Chúng ta chia mảng thành 3 phần:

1. Phần mà $l_j < l_i$, mỗi $j$ mất $2$ giây.
2. Phần $l_j = l_i$, mỗi $j$ mất $1$ giây.
3. Phần còn lại với mỗi $j$ mất $\left \lceil \frac{l_j}{l_i} \right \rceil + [l_j \bmod l_i \ne 0]$ giây.

Mấu chốt của bài toán là tính phần 3 đủ nhanh khi 2 phần trước ta có thể tính trong $\mathcal{O}(1)$. Và thật ra, cách đủ nhanh lại là một ý tưởng tham lam và đặt cận đơn giản:

```cpp=
#include <bits/stdc++.h>

using namespace std;

// Hàm tính thời gian đi qua hành lang độ dài len với bước nhảy m
// Công thức: ceil(len/m) + (1 nếu len không chia hết cho m)
int calculate_cost(int len, int m) {
  if (len % m == 0) {
    return len / m;
  } else {
    return (len / m) + 2;  // 1 bước cuối + 1 giây choáng
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  // Sắp xếp để gom nhóm các hành lang có cùng độ dài
  // và dễ dàng xử lý các phần tử nhỏ hơn/lớn hơn.
  sort(a.begin(), a.end());

  // Khởi tạo kết quả ban đầu: trường hợp tệ nhất mỗi hành lang tốn 2s
  // (ví dụ chọn m > max(a_i), tất cả đều nhảy quá đà và bị choáng)
  long long min_total_time = 2LL * n;

  for (int i = 0; i < n;) {
    int m = a[i];  // Chọn độ dài bước nhảy m bằng độ dài hành lang hiện tại

    // Tìm vị trí cuối cùng có giá trị bằng a[i]
    // Đoạn [i, j] là các hành lang có độ dài bằng m (tốn 1s)
    int j = i;
    while (j < n && a[j] == m) {
      j++;
    }
    // j lúc này là chỉ số của phần tử đầu tiên > m (hoặc n)

    // Tính chi phí cơ sở cho lần chọn m này:
    // 1. Các hành lang < m: tốn 2s (nhảy quá đà ngay bước 1)
    // 2. Các hành lang = m (từ i đến j-1): tốn 1s
    // 3. Các hành lang > m (từ j đến n-1): giả sử tạm tính tối thiểu là 2s
    //    (Thực tế sẽ >= 2s. Ta sẽ cộng phần chênh lệch sau)
    long long current_time = i * 2 + (j - i) * 1 + (n - j) * 2;

    // Tối ưu: Duyệt các phần tử lớn hơn m từ lớn về bé.
    // Cộng thêm chi phí thực tế chênh lệch so với giả định (2s).
    // Nếu tổng vượt quá kết quả tốt nhất hiện có thì dừng ngay.
    for (int k = n - 1; k >= j; --k) {
      int actual_cost = calculate_cost(a[k], m);
      current_time += (actual_cost - 2);
      if (current_time >= min_total_time) {
        break;
      }
    }

    min_total_time = min(min_total_time, current_time);

    // Chuyển sang nhóm độ dài tiếp theo
    i = j;
  }

  cout << min_total_time << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int tc;
  cin >> tc;
  while (tc--) solve();
  return 0;
}

```

Ý tưởng tóm gọn như sau: Ở một thời điểm bất kì, giá trị của `min_total_time` là ngưỡng quyết định xem `l[i]` hiện tại có tối ưu hơn không. Để có thể quyết định nhanh, ta duyệt qua các giá trị từ lớn đến nhỏ, nếu đến một lúc nào đó `current_time` lớn hơn ngưỡng tối ưu hiện tại thì ta có thể loại luôn `l[i]`.

Độ phức tạp của 2 vòng lặp khi này không phải $\mathcal{O}(n^2)$ mà là $\mathcal{O}(n)$. Thật vậy, xét một độ dài phân biệt $m$ với tần suất $\texttt{freq}(m)$:

1. `current_time` khởi đầu bằng $2n - \texttt{freq}(m)$ (mọi hành lang $> m$ được tạm tính $2$ giây).
2. `min_total_time` luôn $\le 2n - 1$ sau lần xét đầu tiên (nhận xét 2).
3. Mỗi hành lang có độ dài $l > m$ và $l \ne 2m$ tốn ít nhất $3$ giây: nếu $m < l < 2m$ thì $\lceil l/m \rceil = 2$ và không chia hết, nếu $l > 2m$ thì $\lceil l/m \rceil \ge 3$. Mỗi hành lang như vậy cộng thêm ít nhất $1$ vào `current_time`. Hành lang $l = 2m$ tốn đúng $2$ giây, cộng thêm $0$.

Do đó sau khi duyệt qua không quá $\texttt{freq}(m)$ hành lang loại thứ nhất, `current_time` đã đạt `min_total_time` và vòng lặp trong dừng; xen giữa có thể có thêm không quá $\texttt{freq}(2m)$ hành lang loại thứ hai. Vậy với mỗi $m$ phân biệt, vòng lặp trong chạy không quá $\texttt{freq}(m) + \texttt{freq}(2m) + 1$ lần, và tổng đại lượng này trên mọi $m$ phân biệt là $\mathcal{O}(n)$. Độ phức tạp cuối cùng của bài là $\mathcal{O}(n \log n)$ do sắp xếp.

:::

## Lời kết

Tham lam không chỉ là một dạng bài. Nó là một tư tưởng luôn len lỏi trong giải thuật, và có thể xuất hiện bất cứ đâu trong các bài toán, trong một bước, nhiều bước giải hoặc toàn bộ bài toán. Đây thường là phần hay, độc đáo trong các kì thi, thử thách sự nhanh nhạy, kinh nghiệm và sáng tạo của thí sinh, cũng như trí tuệ của người ra đề. Hi vọng bài viết này đã phần nào đó truyền tải được cái hay của tư tưởng tham lam, để các bạn hào hứng chinh phục những bài toán hay hơn và khó hơn trong tương lai.


## Bài tập vận dụng

### Tham lam cơ bản

1. [ICPC SEERC 2023 bài J - Jackpot](https://codeforces.com/gym/105465/problem/J)
2. [CF1896C - Matching Arrays](https://codeforces.com/problemset/problem/1896/C)
3. [CF1779C - Least Prefix Sum](https://codeforces.com/problemset/problem/1779/C)
4. [ICPC 2025 vòng Quốc gia bài F - Feast of Delicacy](https://oj.vnoi.info/problem/icpc25_national_f)

### Exchange Argument

1. [CF632C - The Smallest String Concatenation](https://codeforces.com/problemset/problem/632/C)
2. [ICPC 2025 vòng Quốc gia bài B - Blowing Balloons](https://oj.vnoi.info/problem/icpc25_national_b)
3. [CF1043E - Train Hard, Win Easy](https://codeforces.com/contest/1043/problem/E)
4. [AtCoder - Manga Market](https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_d)
5. [AtCoder - Zabuton](https://atcoder.jp/contests/cf17-final/tasks/cf17_final_d)
6. [Singapore NOI 2022 - Gym Badges](https://oj.uz/problem/view/NOI22_gymbadges)

### Regrettable Greedy

1. [CF1526C2 - Potion](https://codeforces.com/problemset/problem/1526/C2)
2. [CF1974G - Money Buys Less Happiness Now](https://codeforces.com/contest/1974/problem/G)
3. [CF730I - Olympiad in Programming and Sports](https://codeforces.com/problemset/problem/730/I)
4. [CF3D - Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D)

### Bài khó
1. [CF436E - Cardboard Boxes](https://codeforces.com/problemset/problem/436/E)
2. [AGC072A - Rhythm Game](https://atcoder.jp/contests/agc072/tasks/agc072_a)
3. [IOI 2020 ngày 1 bài 3 - Carnival Tickets](https://oj.uz/problem/view/IOI20_tickets)
4. [CF1793E - Velepin and Marketing](https://codeforces.com/problemset/problem/1793/E)
5. [NOI 2019 - Sequence](https://loj.ac/p/3158)
6. [ICPC World Finals 2018 bài C - Conquer the World](https://codeforces.com/gym/102482/problem/C)

## Tài liệu tham khảo / đọc thêm

1. [CP Handbook by Antti Laaksonen - Greedy algorithms](https://cses.fi/book/book.pdf)
2. [How to prove your solution in CP](https://codeforces.com/blog/entry/111849)
3. [USACO Guide | Greedy with Sorting](https://usaco.guide/silver/greedy-sorting?lang=cpp)
4. [Principle of Algorithmic Problem Solving - Greedy](https://usaco.guide/PAPS.pdf#page=153)
5. [Chuyên đề tham lam nâng cao - HKOI 2023](https://assets.hkoi.org/training2023/adv-greedy.pdf)
6. [Lecture 3 - Exchange Argument by Errichto](https://codeforces.com/blog/entry/63533)
7. [Algorithms Live! - Exchange Argument](https://www.youtube.com/watch?v=Oq1seKJvfQU)
8. [Kozen, Zaks - Hệ mệnh giá chuẩn tắc](https://www.cs.cornell.edu/~kozen/Papers/change.pdf)


