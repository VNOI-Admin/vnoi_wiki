# Một số kĩ thuật tối ưu hoá thuật toán Quy Hoạch Động

Tác giả: **Lê Anh Đức** - A2K42-PBC

Quy hoạch động (QHĐ) là một lớp thuật toán rất quan trọng và có nhiều ứng dụng trong ngành khoa học máy tính. Trong các cuộc thi Olympic tin học hiện đại, QHĐ luôn là một trong những chủ đề chính. Tuy vậy, theo tôi thấy, tài liệu nâng cao về QHĐ bằng tiếng Việt hiện còn cực kỳ khan hiếm, dẫn đến học sinh/sinh viên Việt Nam bị hạn chế khả năng tiếp cận với những kỹ thuật hiện đại. Trong bài viết này, tôi sẽ trình bày một vài kỹ thuật để tối ưu hóa độ phức tạp của một số thuật toán QHĐ.

[[_TOC_]]

# 1. Đổi biến

Nhiều khi trong trạng thái QHĐ có một thành phần nào đấy với khoảng giá trị quá lớn, trong khi kết quả của hàm lại có khoảng giá trị nhỏ. Trong một vài trường hợp, ta có thể đảo nhãn để giảm số trạng thái.

## Bài tập ví dụ: Longest Common Subsequence (LCS)

### Đề bài
Cho xâu A độ dài m, xâu B độ dài n. Hãy tìm độ dài xâu con chung dài nhất của hai xâu, chú ý là xâu con chung có thể không liên tiếp.

**Giới hạn**

- $m \le 10^6$
- $n \le 5000$
- Các kí tự trong cả hai xâu là các chữ cái tiếng Anh in hoa 'A'..'Z'

**Ví dụ**

```
A = ADBCC
B = ABCD

LCS = ABC
Kết quả = 3
```

### Lời giải

**Thuật toán đơn giản**

Gọi $F(i, j)$ là LCS của hai tiền tố $A_{1..i}$ và $B_{1..j}$.

Khi đó ta có thể maximize $F(i, j)$ theo $F(i-1, j)$ và $F(i, j-1)$.

Nếu $A_i = B_j$ thì ta có thể cập nhật $F(i, j)$ theo $F(i-1, j-1) + 1$.

Kết quả bài toán là $F(m, n)$.

Độ phức tạp của thuật toán này là $O(m*n)$, không khả thi với giới hạn của đề bài.

**Đổi biến**

Đặt $L = min(m, n)$

Để ý rằng trong hàm QHĐ trên, các giá trị của $F(i, j)$ sẽ không vượt quá $L$, trong khi đó chiều thứ hai của trạng thái có thể khá lớn (lên tới $MAXM = 10^6$).

Để tối ưu hóa, ta sẽ đổi biến. Gọi $dp(i, j)$ là vị trí $k$ nhỏ nhất sao cho $LCS(A_{1..i}, B_{1..k}) = j$.

Để tính các giá trị của $dp$, ta sẽ QHĐ theo kiểu cập nhật đi, thay vì đi tìm công thức trực tiếp cho các $dp(i, j)$.

Gọi $nextPos(i, c) = j > i$ nhỏ nhất mà $A_j = c$ (với $c$ là một ký tự từ 'A' đến 'Z').

Mảng $nextPos$ có thể tính trong $T(M*26)$.

Như vậy ta có thể tính các giá trị QHĐ như sau:

- Ban đầu khởi tạo các giá trị $dp(i, j) = \infty$, $dp(0, 0) = 0$.
- For $i$ và $j$ tăng dần, với mỗi giá trị $dp(i, j)$ khác vô cùng:
    - Cập nhật $dp(i+1, j)$ theo $dp(i, j).
    - Gọi $k$ là vị trí xuất hiện tiếp theo của $B_{i+1}$ trong xâu $A$ bắt đầu từ vị trí $dp(i, j)$, tức là $k = nextPos(dp(i, j), B_{i+1})$.
    - Nếu tồn tại $k$, cập nhật $dp(i+1, j+1)$ theo $k$.

Để tính kết quả, ta sẽ chỉ cần tìm $j$ lớn nhất mà tồn tại $dp(i, j)$ khác vô cùng.

```cpp
#include <bits/stdc++.h>

using namespace std;

const int M = 1e6 + 6;
const int N = 5005;

int dp[N][N];

char a[M], b[N];
int nextPos[M][26];
int m, n;

void minimize(int &a, int b) {
    if (a == -1 || a > b) a = b;
}

int main() {
    cin >> a + 1 >> b + 1;
    m = strlen(a + 1); n = strlen(b + 1);
    for (int c = 0; c < 26; ++c)
        for (int i = m - 1; i >= 0; --i)
            nextPos[i][c] = (a[i + 1] - 'A' == c) ? i + 1 : nextPos[i + 1][c];
    int maxLength = min(m, n);
    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) if (dp[i][j] >= 0) {
            minimize(dp[i + 1][j], dp[i][j]);
            int new_value = nextPos[dp[i][j]][b[i + 1] - 'A'];
            if (new_value > 0)
                minimize(dp[i + 1][j + 1], new_value);
        }
    }
    int ans = 0;
    for (int j = maxLength; j > 0; --j) {
        for (int i = j; i <= n; ++i)
            if (dp[i][j] >= 0) ans = j;
        if (ans != 0) break;
    }
    cout << ans << endl;
    return 0;
}
```

## Bài tập ví dụ: Computer (VNOI Marathon 2010)

Problem Link: [COMPUTER - VOJ](http://vn.spoj.com/problems/COMPUTER/).

### Đề bài

Công ty phần mềm XYZ mới mua x máy tính để bàn và y máy tính xách tay. Giá một máy tính để bàn là a đồng còn giá một máy tính xách tay là b đồng. Để tránh sự thắc mắc giữa các phòng bàn, Tổng giám đốc đã đưa ra cách phân bố các máy tính này về n phòng ban như sau:

- Sắp xếp n phòng ban theo thứ tự về mức độ quan trọng của các phòng ban.
- Tiến hành phân bố các máy tính cho các phòng ban bảo đảm nếu phòng ban i có mức độ quan trọng nhỏ hơn mức độ quan trọng của phòng ban j thì tổng giá trị máy tính được phân bố cho phòng ban i không được vượt quá tổng giá trị máy tính được phân bố cho phòng ban j.
- Phòng ban nhận được tổng giá trị máy tính nhỏ nhất là lớn nhất.

Là một lập trình viên giỏi nhưng lại thuộc phòng ban có mức độ quan trọng nhỏ nhất, Thắng muốn chứng tỏ tay nghề của mình với đồng nghiệp nên đã lập trình tính ra ngay được tổng giá trị máy trình mà phòng ban mình nhận được rồi mời bạn tính lại thử xem!

**Yêu cầu**

Cho x, a, y, b, n. Hãy tính tổng giá trị máy tính mà phòng Thắng nhận được.

**Input**

x, a, y, b, n không quá 1000

### Lời giải

Trước hết ta sẽ chặt nhị phân kết quả bài toán. Với mỗi giá trị chặt nhị phân, ta cần kiểm tra xem có tồn tại phương án thỏa mãn hay không.

**Thuật toán sơ khai**

Đặt giá trị cần kiểm tra là v.

Xét các phòng ban theo thứ tự tăng dần về mức độ quan trọng, đánh số từ 1.

Sử dụng một mảng đa chiều để đánh dấu các trạng thái có thể đạt tới. Các giá trị cần quản lí là: chỉ số của phòng ban, đã dùng số máy tính để bàn x, đã dùng số máy tính xách tay y, tổng giá trị máy tính của phòng ban trước đó.

Bắt đầu từ trạng thái (0, 0, 0, 0), ta sử dụng thuật toán loang (BFS). Cuối cùng nếu trạng thái (n, 0, 0, ...) có thể đến được, thì ta sẽ có cách phân hoạch các máy tính vào các phòng ban ứng với giá trị cận dưới v.

Không cần tính toán cụ thể cũng có thể thấy thuật toán này không thể đáp ứng về mặt thời gian (và bộ nhớ) với giới hạn của đề bài.

**Nâng cấp bằng nhận xét**

Nhận xét rằng ta không cần quan tâm tới thứ tự về mức độ quan trọng của các phòng ban. Với một cách phân hoạch các máy tính sao cho mỗi phòng nhận được tổng giá trị không nhỏ hơn v, ta luôn có thể sắp xếp các bộ theo giá trị không giảm ứng với các phòng ban.

Ta có trạng thái QHĐ là $F(i, x, y, value) = true$ nếu có thể phân bổ máy tính cho i phòng ban, đã dùng x máy tính để bàn và y máy tính xách tay, đã gom được tổng giá trị v cho phòng thứ $i+1$. Cách làm này số trạng thái vẫn như trước nhưng ta đã có thể chuyển trạng thái trong $O(1)$. Cụ thể từ $F(i, x, y, value)$ ta chuyển đến $F(i, x+1, y, value+a)$ hoặc $F(i, x, y+1, value+b)$, chú ý là chỉ có thể dùng thêm máy xách tay nếu $x<X$ và dùng thêm máy để bàn nếu $y<Y$, đồng thời nếu giá trị value đủ lớn hơn hoặc bằng v thì ta chuyển sang trạng thái $F(i+1, x, y, 0)$ luôn.

### Đổi biến

Ở bài này, ta có thể dễ dàng đổi biến value ra làm hàm mục tiêu. Nhưng không chỉ có vậy, ta có thể đẩy cả i ra ngoài! Cụ thể, $F(x, y)$ = một cặp số $(i, value)$ lần lượt là số phòng phân bố được và số tiền gom được. Hàm mục tiêu của $F(x, y)$ là một cặp số hoàn toàn có thể so sánh được, trong đó giá trị đầu (i) được ưu tiên so sánh trước.

Cách cập nhật các $F(x, y)$ giống như phần trước, độ phức tạp vẫn là O(1) cho bước chuyển trạng thái, trong khi số trạng thái lúc này là đủ nhỏ đối với giới hạn của đề bài.

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int x, y, a, b, n;

pair<int, int> F[N][N];

pair<int, int> newState(pair<int, int> s, int a, int v) {
    s.second += a;
    if (s.second >= v) {
        ++s.first;
        s.second = 0;
    }
    return s;
}

bool dp(int value) {
    for (int i = 0; i <= x; ++i) for (int j = 0; j <= y; ++j)
        F[i][j] = make_pair(0, 0);
    for (int i = 0; i <= x; ++i) for (int j = 0; j <= y; ++j) {
        if (F[i][j].first == n) return 1;
        if (i < x)
            F[i + 1][j] = max(F[i + 1][j], newState(F[i][j], a, value));
        if (j < y)
            F[i][j + 1] = max(F[i][j + 1], newState(F[i][j], b, value));
    }
    return 0;
}

int solve() {
    int l = 0, r = (a * x + b * y) / n;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (dp(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    cin >> x >> a >> y >> b >> n;
    cout << solve() << endl;
    cin >> x >> a >> y >> b >> n;
    cout << solve() << endl;
    return 0;
}

```

## Bài luyện tập

- [VOJ - BINPACK](http://vn.spoj.com/problems/BINPACK/)