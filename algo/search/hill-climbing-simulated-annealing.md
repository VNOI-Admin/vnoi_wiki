---
title: Thuật toán Hill Climbing và Simulated Annealing
description: 
published: true
date: 2026-10-29T07:26:01.961Z
tags: 
editor: markdown
dateCreated: 2026-10-29T07:26:01.961Z
---

# Thuật toán Hill Climbing và Simulated Annealing

**Người viết:**

- Võ Khắc Triệu - National University of Singapore.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

**Reviewer:**

- Nguyễn Quang Minh - Michigan State University.

## Giới thiệu về lớp bài toán tối ưu

Lớp **bài toán tối ưu (optimization problem)** là lớp bài toán yêu cầu tìm kiếm **nghiệm tốt nhất** trong các **nghiệm khả thi**. Việc xác định nghiệm tốt nhất thường được dựa trên một hàm chấm điểm $f(x)$ và việc xác định các nghiệm khả thi thường được dựa trên các ràng buộc nào đó trên $x$, ở đây, $x$ có thể là số nguyên, vector, hay bất kì đối tượng toán học nào.

Nói cách khác, gọi $\Omega$ là tập các nghiệm khả thi được xác định dựa trên các ràng buộc được cho, ta cần tìm $\arg \min_{x \in \Omega} f(x)$ hoặc $\arg \max_{x \in \Omega} f(x)$. Trong trường hợp tổng quát, khi ta không biết trước bất kỳ tính chất gì của hàm $f(x)$, nghiệm tốt nhất đơn giản là duyệt tất cả các nghiệm khả thi thuộc tập $\Omega$.

:::spoiler Chú thích
Ta chỉ xét các phương pháp trên máy tính truyền thống chạy trên bit, trên thực tế, [thuật toán Dürr--Høyer](https://arxiv.org/abs/quant-ph/9607014) đã có thể giải quyết bài toán này trong độ phức tạp $\mathcal{O}(\sqrt{|\Omega|})$ trên máy tính lượng tử.
:::

Tuy nhiên, khi $\Omega$ là một tập liên tục hoặc một tập rời rạc có kích thước lớn, cách làm này rõ ràng là quá tệ. Do đó, ta thường xét bài toán với các hàm $f(x)$ có các tính chất đặc biệt (như tính [liên tục](https://vi.wikipedia.org/wiki/H%C3%A0m_li%C3%AAn_t%E1%BB%A5c), [khả vi](https://vi.wikipedia.org/wiki/H%C3%A0m_s%E1%BB%91_kh%E1%BA%A3_vi),...) để đưa ra một phương pháp tốt hơn.

Ví dụ, cho $\Omega = \mathbb{R}$ và hàm sau:

$$
f(x) = \frac{1}{4} x^4 - \frac{2}{3} x^3 - \frac{1}{2} x^2 + 2x + 1
$$

Sử dụng tính khả vi của hàm $f(x)$ trên $\mathbb{R}$, ta hoàn toàn có thể tìm điểm cực tiểu bằng cách giải phương trình $f'(x) = 0$. Hàm số đạt giá trị cực tiểu tại $x = -1$.

![example_function.png](/algo/search/example_function.png)
<center>
    <i>Đồ thị hàm số được cho</i>
</center>

:::spoiler Lời giải chi tiết
Ta tính đạo hàm:

$$
f'(x) = x^3 - 2x^2 - x + 2
$$

Giải phương trình bậc $x^3 - 2x^2 - x + 2 = 0$ ta được $3$ nghiệm là $x_0 = -1$, $x_1 = 1$ và $x_2 = 2$. Thử giá trị của hàm $f(x)$ tại ba điểm này, ta tìm được giá trị cực tiểu.
:::

Có thể thấy, ta vừa sử dụng tính chất đặc biệt của hàm $f(x)$ để giảm số điểm cần thử từ vô hạn điểm thành $3$ điểm!

Tất nhiên, trên thực tế, các hàm cần tối ưu thường không phải các hàm đa thức đẹp như thế này. Thậm chí, đối với một số hàm nhất định, việc tìm một cực trị toàn cục gần như là bất khả thi. Trong các trường hợp như vậy, ta thường chấp nhận một lời giải *đủ tốt* để không làm mất đi ý nghĩa của bài toán tối ưu để đổi lại tốc độ cho thuật toán. Ta thường gọi chung các phương pháp như vậy là phương pháp [heuristic](https://en.wikipedia.org/wiki/Heuristic).

Trong bài viết này, chúng ta sẽ cùng tìm hiểu một thuật toán heuristic kinh điển đó là **Hill Climbing**, cùng với cải tiến trực tiếp của nó là thuật toán **Simulated Annealing**.

## Hill Climbing trên hàm một biến

Hill Climbing là cách gọi chung các thuật toán tìm kiếm cục bộ được dùng để tìm kiếm các cực trị cục bộ/toàn cục trên một hàm số $f(\mathbf{x})$ nào đó bằng cách xuất phát từ một nghiệm ngẫu nhiên, rồi liên tục di chuyển đến một nghiệm tốt hơn trong số các *nghiệm lân cận*.

Về định nghĩa là vậy, nhưng việc áp dụng Hill Climbing với hiệu quả tốt nhất trong từng bài toán và từng trường hợp cụ thể lại đòi hỏi sự khéo léo của người thiết kế thuật toán, ví dụ như cách xác định nghiệm lân cận, cách xây dựng hàm $f(\mathbf{x})$ dựa trên bài toán được cho,...

Để hiểu hơn về Hill Climbing cơ bản, ta cùng đến với một vài ví dụ cơ bản sử dụng kĩ thuật Hill Climbing trong các trường hợp khác nhau. Trong phần này, ta sẽ tập trung vào các hàm mục tiêu chỉ có một tham số.

### Hàm một biến liên tục có 1 cực trị

#### Bài toán: [Codeforces 578C -- Weakness and Poorness](https://codeforces.com/contest/578/problem/C)

> Ta định nghĩa một hàm chi phí $\texttt{cost}(b)$ của một dãy số $b$ gồm $m$ phần tử là giá trị tuyệt đối lớn nhất trong số các tổng đoạn con liên tiếp của dãy $b$. Nói cách khác, ta có:
>
> $$
> \texttt{cost}(b) = \max_{1 \leq l \leq r \leq m} \left| \sum_{l \leq i \leq r} b_i \right|
> $$
>
> Cho dãy $a$ gồm $n$ phần tử, tìm một số thực $x$ sao cho giá trị khi cộng mọi giá trị của dãy $a$ lên $x$ đơn vị, giá trị $\texttt{cost}(a)$ nhận được là nhỏ nhất.

Giới hạn:

- $1 \leq n \leq 2 \cdot 10^5$.
- $|a_i| \leq 10^4$.

*Lưu ý, phát biểu bài toán ở bài viết này có đôi chút khác biệt so với bài toán gốc. Tính chất của bài toán vẫn được giữ nguyên*

#### Phân tích

Nếu viết hàm $\texttt{cost}$ lại dưới dạng $\texttt{cost}_a(x)$, ta có thể chứng minh rằng đây là một hàm lồi có giá trị cực tiểu tại $x_\min \in [-\max a; -\min a]$, gọi là $[x_L; x_R]$.

Trên thực tế, ta hoàn toàn có thể tận dụng tính chất này để đưa ra các lời giải hình học bao lồi có độ phức tạp $\mathcal{O}(n)$. Tuy nhiên, trong bài viết này, ta sẽ cùng nghiên cứu lời giải sử dụng kỹ thuật Hill Climbing có độ phức tạp lớn hơn.

#### Áp dụng kỹ thuật Hill Climbing

Nhìn vào đồ thị của một hàm lồi, ta có thể nghĩ đến một lời giải vô cùng đơn giản: Nếu vị trí hiện tại nằm bên phải điểm cực tiểu, ta nhảy sang trái; ngược lại, ta nhảy sang phải. Đến một thời điểm nào đó, kết quả sẽ hội tụ về điểm cực tiểu.

Tuy nhiên, để chọn khoảng cách cho "bước nhảy" nêu trên, ta cần tính toán đến hai vấn đề có thể xảy ra: khoảng cách quá nhỏ hoặc khoảng cách quá lớn.

- Khi chọn khoảng cách quá nhỏ, tất nhiên tốc độ hội tụ của thuật toán sẽ là cực kỳ thấp. Giả sử khoảng cách giữa nghiệm hiện tại và nghiệm tối ưu là $10^3$ đơn vị, nếu ta chọn khoảng cách nhảy là $\delta = 10^{-3}$, ta sẽ cần đến $10^6$ bước nhảy!
- Khi chọn khoảng cách quá lớn, ta sẽ có thể bỏ qua điểm cực tiểu, các nghiệm được chọn chỉ xuất hiện quanh điểm cực tiểu mà không nhảy vào điểm cực tiểu. Giả sử khoảng cách giữa nghiệm hiện tại và nghiệm tối ưu là $10$ đơn vị, nếu ta chọn khoảng cách nhảy là $\delta = 100$, ta sẽ không thể nhảy vào điểm cực tiểu được.

Một giải pháp có thể giải quyết được vấn đề của cả hai trong trường hợp này là: Bắt đầu với một khoảng cách tương đối lớn, sau đó giảm dần xuống một khoảng cách nhỏ để "rà" được vị trí của điểm cực tiểu.

Cách làm này khá tương đồng với kỹ thuật nhảy nhị phân (binary lifting). Hoặc lấy một ví dụ thực tế: khi chạy xe trên một con đường để tìm một số nhà cụ thể, ta thường chạy nhanh để lướt qua nhiều căn nhà khi chắc chắn rằng vị trí cần tìm còn xa, sau đó giảm tốc độ khi đã gần đến số nhà cần tìm.

#### Thuật toán: Thiết kế hàm chọn nghiệm

Như vậy, ta có một thuật toán Hill Climbing trên không gian 1 chiều vô cùng đơn giản như sau:

- Bắt đầu với một nghiệm ngẫu nhiên $x_0$ trong khoảng $[x_L; x_R]$ và một bước nhảy tương đối lớn. Trong phần cài đặt, mình chọn $\delta = \frac{x_R - x_L}{2}$.
- Lặp lại thao tác cập nhật nghiệm bằng cách nhảy đến nghiệm có chi phí thấp nhất trong ba nghiệm $x - \delta$, $x$ hay $x + \delta$. Sau mỗi bước cập nhật, ta giảm $\delta$ đi một nửa.

Trong trường hợp tổng quát, ta có thể gọi $\lambda$, thường được gọi là *cooldown*, là hệ số để điều chỉnh $\delta$ (bằng cách gán $\delta \leftarrow \delta \cdot \lambda$). Trong bài toán này, ta chọn $\lambda = 0.5$.

Quá trình này được lặp lại đến khi $\delta$ đủ nhỏ (thường sẽ được xác định dựa trên sai số tối thiểu được cho phép của bài toán). Tuy nhiên, ta thường cố định trước số lần lặp $T$; trong bài toán này, mình chọn $T = 200$ là một giá trị cực kì an toàn mà vẫn đảm bảo hiệu quả về mặt thời gian.

#### Thuật toán: Hàm chi phí

Để tính hàm chi phí, ta dựa vào nhận xét để cực đại hóa một giá trị tuyệt đối $|a|$, ta cần cực đại hóa $\max(a, -a)$. Do đó, ta cần tính hai giá trị sau:

$$
S_1 = \max_{1 \leq l \leq r \leq n} \left( \sum_{l \leq i \leq r} a_i + x \right), \quad S_2 = \min_{1 \leq l \leq r \leq n} \left( \sum_{l \leq i \leq r} a_i + x \right)
$$

Cả hai giá trị đều có thể được tính trong $\mathcal{O}(n)$ bằng cách sử dụng prefix sum khá đơn giản và dễ cài đặt. Cuối cùng, ta có $\texttt{cost}_a(x) = \max(S_1, -S_2)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const int mn = 2e5 + 5;
const double oo = 1e14;
int a[mn], n;

double calcCost (double x) {
    double minValue = oo, maxValue = -oo;
    double prf = 0, minPrf = 0, maxPrf = 0;

    for (int i = 1; i <= n; i++) {
        prf += a[i] + x;
        minValue = min(minValue, prf - maxPrf);
        maxValue = max(maxValue, prf - minPrf);
        minPrf = min(minPrf, prf);
        maxPrf = max(maxPrf, prf);
    }
    return max(maxValue, -minValue);
}

mt19937 rng(21);

double randDouble (double L, double R) {
    return uniform_real_distribution<double>(L, R)(rng);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    double xMin = -*max_element(a + 1, a + 1 + n);
    double xMax = -*min_element(a + 1, a + 1 + n);

    double xCur = randDouble(xMin, xMax), step = (xMax - xMin) / 2.0;
    double curCost = calcCost(xCur);

    int iterations = 200;
    for (int i = 0; i < iterations; i++, step /= 2.0) {
        double leftCost = calcCost(xCur - step), rightCost = calcCost(xCur + step);
        if (min(leftCost, rightCost) < curCost) { // tìm ra lời giải mới tốt hơn lời giải hiện tại
            if (leftCost < rightCost)
                xCur -= step, curCost = leftCost;
            else xCur += step, curCost = rightCost;
        }
    }

    cout << fixed << setprecision(6) << curCost << "\n";

    return 0;
}
```
:::

#### Visualization

Để hiểu rõ hơn về cách hoạt động của Hill Climbing, ta sẽ nghiên cứu quá trình chuyển trạng thái của Hill Climbing để giải quyết bài toán tìm cực tiểu của hàm $f(x) = x^2 + 5\sin x$. Ta có thể dùng Hill Climbing giống như bài trên, tuy nhiên trong phần cài đặt bên dưới, giá trị cooldown được sử dụng là $\lambda = 0.9$ thay vì $\lambda = 0.5$.

Sau đây là một hoạt ảnh mô phỏng quá trình chuyển trạng thái của Hill Climbing:

![hill_climbing_example_1-ezgif.com-cut (2) (1)](https://hackmd.io/_uploads/H1YYgpXhWg.gif)

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct State {
    // Put your solution representation here
    double x;

    State() {x = 0;}
    State(double x): x(x){}

    void print(){
        cout << fixed << setprecision(6) << x << endl;
    }
};

double evaluate(const State &s) {
    double ans = x * x + 5 * sin(x);

    return -ans;
}

State random_neighbor(const State &cur, double range) {
    // Modify one small part of the current state

    State nxt = cur;
    if (rng() % 2 == 0) return State(nxt.x - range); 
    return State(nxt.x + range);
}

State random_state() {
    return State();
}

State hill_climbing(int max_iters, int max_sideways = 0) {
    State cur = random_state();
    double cur_score = evaluate(cur);

    State best = cur;
    double best_score = cur_score;

    int sideways = 0;
    double range = 1e9;
    double cooldown = 0.9;

    for (int iter = 0; iter < max_iters; iter++) {
        State nxt = random_neighbor(cur, range);
        range *= cooldown;
        double nxt_score = evaluate(nxt);

        cerr << nxt.x << ": " << nxt_score << '\n';

        if (nxt_score > cur_score) {
            cur = nxt;
            cur_score = nxt_score;
            sideways = 0;
        } else if (nxt_score == cur_score && sideways < max_sideways) {
            cur = nxt;
            cur_score = nxt_score;
            sideways++;
        }

        if (cur_score > best_score) {
            best = cur;
            best_score = cur_score;
        }
    }

    return best;
}

State hill_climbing_with_restarts(int restarts, int max_iters, int max_sideways = 0) {
    State best_overall;
    double best_score = -1e100;
    bool has_answer = false;

    for (int r = 0; r < restarts; r++) {
        State candidate = hill_climbing(max_iters, max_sideways);
        double score = evaluate(candidate);

        if (!has_answer || score > best_score) {
            best_overall = candidate;
            best_score = score;
            has_answer = true;
        }
    }

    return best_overall;
}

int main() {
    int restarts = 1;
    int max_iters = 1000;
    int max_sideways = 50;

    State ans = hill_climbing_with_restarts(restarts, max_iters, max_sideways);

    cout << "Best score = " << evaluate(ans) << '\n';

    // Print answer
    ans.print();

    return 0;
}
```
:::

### Hàm một biến liên tục tổng quát

Phát triển từ ý tưởng trên, ta có thể cải tiến thuật toán Hill Climbing cho các hàm liên tục nói chung. Để hiểu rõ hơn, ta nghiên cứu bài toán minh họa như sau.

#### Bài toán: Tìm đường tròn lớn nhất không cắt đoạn thẳng.

> Trên mặt phẳng $Oxy$, cho $n$ đoạn thẳng và số nguyên $L$. Tìm một đường tròn có tâm $(x_C, 0)$ nằm trên tục hoành có bán kính lớn nhất sao cho $0 \leq x_C \leq L$ và miền trong của đường tròn không chứa bất kỳ phần nào của $N$ đoạn thẳng. Lưu ý, các đường thẳng vẫn được phép tiếp xúc hình tròn.

Giới hạn:
- $1 \leq n \leq 2000$.
- Các tọa độ được cho là số nguyên không quá $10^9$.

#### Phân tích

Sử dụng hình học, ta hoàn toàn có thể tìm được bán kinh lớn nhất của một hình tròn được cố định tâm tại điểm $(x_C, 0)$ nào đó. Tuy nhiên, vấn đề lớn nhất của bài toán là tìm được vị trí đặt tâm đường tròn một cách tối ưu.

Ta có thể mô hình hóa bài toán lại thành tìm giá trị cực đại của hàm $f(x)$ với $x$ là hoành độ của tâm đường tròn và $f(x)$ là hàm tính bán kính lớn nhất khi đặt tâm tại $(x, 0)$.

#### Áp dụng kỹ thuật Hill Climbing

Dễ thấy rằng $f(x)$ là một hàm liên tục, tương đối phù hợp cho việc sử dụng Hill Climbing. Tuy nhiên, khác với ví dụ trước, hàm này không có tính chất của hàm lồi nên các cực trị có thể nằm rải rác trên khoảng $[0; L]$.

Nếu áp dụng kỹ thuật Hill Climbing giống như ví dụ trước, ta có thể rất dễ bị "nhảy sai" ở các bước đầu tiên khi $\delta$ còn lớn. Ví dụ, trong trường hợp sau:

![local_max_vs_hill_climbing.png](/algo/search/local_max_vs_hill_climbing.png)
*Lưu ý: Đây chỉ là hàm minh họa có tính chất tương đương, không phải hàm có được từ bài toán nêu trên.*

Một phương pháp có thể khắc phục điểm yếu trên một cách hiệu quả đó là ta thực hiện quá trình Hill Climbing $B$ lần với nhiều vị trí bắt đầu $x_0$ khác nhau. Bằng cách rải điều các điểm $x_0$ trên khoảng $[0; L]$ và chỉ tìm kiếm trên một khoảng nhỏ $\left[x_0 - \frac{L}{B}; x_0 + \frac{L}{B}\right]$, số điểm cực đại trong vùng tìm kiếm của một lần chạy Hill Climbing sẽ giảm đi một cách đáng kể. Khi đó, việc áp dụng Hill Climbing sẽ là hiệu quả hơn.

<!--chia khoảng tìm kiếm $[0; L]$ thành $B$ khoảng nhỏ hơn. Khi đó, mỗi khoảng nhỏ chỉ chứa một số ít các điểm cực đại và ta có thể áp dụng kỹ thuật Hill Climbing như đã tìm hiểu.-->

Với giới hạn của bài toán này, ta có thể tìm ra giá trị đủ tốt với $B = 100$ và $T = 50$.

Việc thiết kế hàm tìm bán kính lớn nhất là một bài tập hình học 2D nên sẽ không được đào sâu trong khuôn khổ bài viết, xin được nhường lại như một bài tập cho các bạn đọc.

## Hill Climbing trên hàm nhiều biến

### Hàm liên tục nhiều biến

#### Bài toán

> Trên hệ trục tọa độ $Oxy$, cho $n$ đoạn thẳng. Tìm một điểm $(x_0, y_0)$ sao cho tổng khoảng cách giữa điểm này và $n$ đoạn thẳng là nhỏ nhất.

Giới hạn:
- $1 \leq n \leq 150$.
- Các tọa độ được cho là số nguyên không âm không quá $100$.

#### Phân tích

Gọi $f(x, y)$ là tổng khoảng cách nếu ta chọn điểm $(x, y)$. Ta có thể dễ dàng tính giá trị của hàm trong $\mathcal{O}(n)$. Bài toán bây giờ là chọn điểm $(x, y)$ sao cho $f(x, y)$ được cực tiểu hóa.

#### Áp dụng kỹ thuật Hill Climbing

Với không gian 2 chiều hoặc nhiều hơn, tại một điểm $\mathbf{x}$ bất kỳ với một khoảng cách $\delta$ cố định, ta không chỉ có 2 điểm trái và phải nữa, mà là rất nhiều điểm cùng có khoảng cách $\delta$.

Lúc này, việc chọn nghiệm lân cận sẽ được thực hiện một cách linh động hơn. Một trong các lựa chọn phổ biến là thử nhảy đến một trong bốn hướng Đông, Tây, Nam, Bắc. Trong không gian $k$ chiều, ta có $2k$ hướng nhảy cần thử.

#### Cài đặt

:::spoiler Cài đặt
```cpp=
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

vector<pii> verticalLines[110], horizontalLines[110];

double sq (double a) {
    return a * a;
}

double euclideDistance (double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

double cost (double x0, double y0) {
    double ans = 0;
    for (int x = 0; x <= 100; x++) {
        for (auto [a, b] : verticalLines[x]) {
            if (a <= y0 && y0 <= b) ans += abs(x0 - x);
            else ans += min(euclideDistance(x, a, x0, y0), euclideDistance(x, b, x0, y0));
        }
    }
    for (int y = 0; y <= 100; y++) {
        for (auto [a, b] : horizontalLines[y]) {
            if (a <= x0 && x0 <= b) ans += abs(y0 - y);
            else ans += min(euclideDistance(a, y, x0, y0), euclideDistance(b, y, x0, y0));
        }
    }
    return ans;
}

const int ITERATIONS = 25;
const int TRYTIME = 1000;

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, -1, 0, 1};

void hillClimbing (double x, double y, double &optX, double &optY, double &optCost) {
    double R = 50.0, curCost = cost(x, y);
    for (int iteration = 0; iteration < ITERATIONS; iteration++) {
        vector<double> tryCost(4);
        for (int k = 0; k < 4; k++)
            tryCost[k] = cost(x + dr[k] * R, y + dc[k] * R);
        
        if (*min_element(tryCost.begin(), tryCost.end()) < curCost) {
            int bestDirection = min_element(tryCost.begin(), tryCost.end()) - tryCost.begin();
            curCost = tryCost[bestDirection];
            x += dr[bestDirection] * R;
            y += dc[bestDirection] * R;
        }

        R /= 2.0;
    }

    if (curCost < optCost)
        optCost = curCost, optX = x, optY = y;
}

mt19937 rng(21);

double randRange (double L, double R) {
    return uniform_real_distribution<double>(L, R)(rng);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2)
            verticalLines[x1].emplace_back(min(y1, y2), max(y1, y2));
        if (y1 == y2)
            horizontalLines[y1].emplace_back(min(x1, x2), max(x1, x2));
    }

    double optX = 0, optY = 0, optCost = cost(0, 0);
    for (int tryTime = 0; tryTime < TRYTIME; tryTime++) {
        double x0 = randRange(0, 100), y0 = randRange(0, 100);
        hillClimbing(x0, y0, optX, optY, optCost);
    }

    cout << fixed << setprecision(6) << optX << " " << optY << " " << optCost << "\n";

    return 0;
}
```
:::

### Hàm rời rạc nhiều biến

#### Bài toán: [Kattis - Travelling Salesman Problem](https://open.kattis.com/problems/tsp)

> Trên hệ trục tọa độ $Oxy$, cho $n$ điểm $(x_i, y_i)$. Tìm một hoán vị của $n$ điểm được cho sao cho tổng khoảng cách Euclide giữa hai điểm liên tiếp trong hoán vị là nhỏ nhất.

Giới hạn:
- $1 \leq N \leq 1000$.
- Các tọa độ được cho là số thực có giá trị tuyệt đối không quá $10^6$.

#### Phân tích

Khác với các ví dụ trên hàm liên tục như trên, không gian mẫu trong bài toán này là một tập rời rạc chứ không phải $\mathbb{R}^n$. Do đó, ta cần một định nghĩa mới cho việc tìm kiếm nghiệm lân cận, thay vì sử dụng khoảng cách nhảy $\delta$.

#### Phương pháp xác định nghiệm lân cận

##### Phương pháp 1

Một cách xác định nghiệm lân cận dễ thấy đó là từ nghiệm (hoán vị) hiện tại, ta hoán đổi hai vị trí bất kỳ để tạo ra nghiệm lân cận. Tuy nhiên, hạn chế của cách làm này khá giống với trường hợp chọn $\delta$ quá nhỏ trên hàm liên tục. Nguyên nhân là vì với cách tạo nghiệm lân cận như vậy, ta phải mất $\mathcal{O}(n^2)$ bước nhảy để đến được nghiệm tối ưu, giả sử ta luôn biết hướng đi tốt nhất.

:::spoiler Chứng minh
Ta có thể chứng minh rằng số bước đi để di chuyển từ một nghiệm cho trước đến nghiệm tối ưu bằng thao tác sinh nghiệm lận cận như trên tương đương với số thao tác hoán đổi trong thuật toán Bubbble sort để sắp xếp một dãy số. Có thể chứng minh rằng giá trị này cũng bằng số hoán vị của dãy số cần sắp xếp nên kết quả cần tìm là $\mathcal{O}(n^2)$.
:::

Như vậy, chưa tính đến việc kỹ thuật Hill Climbing cần thực hiện nhiều bước nhảy tệ trước khi chọn được đường đi tốt, ta đã cần khoảng $10^6$ bước nhảy để đến được nghiệm tối ưu. Do đó, cho dù có tối ưu một bước nhảy xuống $\mathcal{O}(1)$ thì phương pháp xác định nghiệm lân cận này khiến thuật toán hội tụ cực kì chậm.

##### Phương pháp 2

Nếu ta tập trung vào việc xử lý điểm yếu hội tụ chậm của phương pháp trên, ta có thể nghĩ đến việc hoán đổi hai vị trí bất kỳ thay vì hai vị trí liên tiếp. Trên thực tế, đây là một phương pháp khả quan khi cho phép di chuyển từ một nghiệm bất kỳ đến nghiệm tối ưu trong $\mathcal{O}(n)$ bước nhảy.

Tuy nhiên, ta có thể thấy rằng một phép biến đổi như thế này sẽ làm thay đổi đến $4$ cạnh trong đường đi hiện tại. Điều này có thể làm cho thuật toán nhảy sang các nghiệm "quá xa" khi đã gần với nghiệm tốt.

![changes_1.png](/algo/search/changes_1.png)
*Sự thay đổi của đường đi khi thay đổi vị trí của điểm $2$ và $5$ trong phương pháp 2.*

##### Phương pháp 3

Để khắc phục điểm yếu của các hai cách tiếp cận trên, ta có phương pháp xác định nghiệm lân cận thường dùng trong bài toán Travelling Salesman như sau: Chọn hai giá trị $i, j$ sao cho $1 \leq i < j \leq n$, sau đó, ta đảo ngược đoạn con $a_i, a_{i+1}, a_{i+2}, \dots, a_j$.

![changes_2.png](/algo/search/changes_2.png)
*Sự thay đổi của đường đi khi thay đổi vị trí của điểm $2$ và $5$ trong phương pháp 3.*

Có thể thấy, phép biến đổi này đáp ứng được 2 tiêu chí: sự thay đổi của đường đi chỉ diễn ra trong $2$ cạnh và cho phép di chuyển từ một nghiệm bất kỳ đến nghiệm tối ưu trong $\mathcal{O}(n)$. Trên thực tế, phương pháp này còn được biến đến với tên gọi [2-opt](https://en.wikipedia.org/wiki/2-opt), là phương pháp được chính minh là hiệu quả khi áp dụng các thuật toán tìm kiếm cục bộ như Hill Climbing để giải quyết TSP.

:::spoiler Chứng minh
Để chứng minh rằng cách xác định nghiệm lân cận này cho phép di chuyển từ một nghiệm bất kỳ đến nghiệm tối ưu trong $\mathcal{O}(n)$, ta chứng minh rằng một dãy số bất kỳ có thể được sắp xếp trong tối đa $n$ phép đảo ngược đoạn con.

Với một dãy $a$ độ dài $n$, gọi $p$ là vị trí của phần tử nhỏ nhất. Ta chọn đảo ngược đoạn con $a_1, a_2, \dots, a_p$ rồi tiếp tục quá trình này với dãy $a_2, a_3, \dots, a_n$.
:::

Để chọn hai vị trí $i, j$, ta có thể sinh ngẫu nhiên một cặp số hoặc duyệt tất cả cặp số thỏa mãn.

##### So sánh

Sau đây là kết quả của 3 phương pháp sinh nghiệm lân cận (không sử dụng các tối ưu khác) khi giải bài tập minh họa trên nền tảng Kattis:

|  | Phương pháp 1 | Phương pháp 2 | Phương pháp 3 |
| :-: | :-: | :-: | :-: |
| Điểm số | $1.00636$ | $1.124928$ | $6.853663$ |

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
double x[1010], y[1010];
int n;

mt19937 rng(21);

int rr (int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

double sq (double a) {
    return abs(a) * abs(a);
}

double euclideDistance (int i, int j) {
    return sqrt(sq(x[i] - x[j]) + sq(y[i] - y[j]));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    if (n == 1) return cout << 0 << "\n", 0;
    if (n == 2) return cout << "0\n1\n", 0;

    vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&] (int i, int j) {
        return (abs(x[i] - x[j]) < eps ? y[i] < y[j] : x[i] < x[j]);
    });

    double currentCost = 0;
    for (int i = 1; i < n; i++)
        currentCost += euclideDistance(ord[i - 1], ord[i]);

    int ITERATIONS = 20'000'000;
    for (int itr = 0; itr < ITERATIONS; itr++) {
        int i = rr(0, n - 1), j = rr(0, n - 1);
        if (i == j) continue;
        if (i > j) swap(i, j);

        function<float(int,int)> contrib = [&] (int i, int j) {
            double sum = 0;
            if (i - 1 >= 0) sum += euclideDistance(ord[i - 1], ord[i]);
            if (j + 1 < n) sum += euclideDistance(ord[j], ord[j + 1]);
            return sum;
        };
        double delta = -contrib(i, j);
        swap(ord[i], ord[j]);
        delta += contrib(i, j);
        swap(ord[i], ord[j]);

        if (delta < -eps) { // reduce current cost
            currentCost += delta;
            reverse(ord.begin() + i, ord.begin() + j + 1);
        }
    }
    
    // cout << currentCost << "\n";
    for (int u : ord) cout << u << "\n";

    return 0;
}
```
:::

## Xử lý "đồng bằng" trên hàm mục tiêu

### Ý tưởng chung

Trong một vài trường hợp, hàm mục tiêu có thể chứa những khoảng mà giá trị của nó là hằng số, đặc biệt là các hàm $f: \mathbb{R} \rightarrow \mathbb{Z}$. Điều này làm cho việc sử dụng Hill Climbing gặp bất lợi lớn.

![problem_with_hill_climbing.png](/algo/search/problem_with_hill_climbing.png)
*Hill Climbing gặp bất lợi trên các vùng "đồng bằng" của hàm mục tiêu*

Cách xử lý trong các trường hợp như vậy là chỉnh sửa hàm mục tiêu. Cụ thể, ta cần thiết kế lại một hàm $g$ có cùng tập xác định với hàm $f$ sao cho:

- Với hai điểm $\mathbf{x}_1, \mathbf{x}_2$ thuộc tập xác định của $f$ thỏa $f(\mathbf{x}_1) < f(\mathbf{x}_2)$, ta cần đảm bảo $g(\mathbf{x}_1) < g(\mathbf{x}_2)$.
- Với hai điểm $\mathbf{x}_1, \mathbf{x}_2$ thuộc tập xác định của $f$ thỏa $f(\mathbf{x}_1) = f(\mathbf{x}_2)$, ta cần dựa vào tính chất khác của bài toán để xác định thứ tự lớn bé của $g(\mathbf{x}_1), g(\mathbf{x}_2)$ và chưa thể hiện trên hàm $f$ ban đầu.

Nói cách khác, hàm $g$ đóng vai trò như một "tie-breaker" ở các vùng mà hàm $f$ trả ra giá trị hằng số. Ví dụ, nhìn vào đồ thị sau, ta có thể thấy mặc dù có cùng giá trị, một vài điểm trên hàm $f$ rõ ràng là "tốt" hơn những điểm còn lại, ta có thể thiết kế hàm $g$ như sau:

![geogebra-export-3.png](/algo/search/geogebra-export-3.png)

Để làm được điều đó, ta thường sử dụng một trong hai cách:
- Lưu $g(\textbf{x})$ dưới dạng cặp số $(f(\textbf{x}), r)$, giá trị của $r$ do ta tự định nghĩa.
- Với hàm $f: \mathbb{R} \rightarrow \mathbb{Z}$, ta có thể định nghĩa $g: \mathbb{R} \rightarrow \mathbb{R}$ bằng cách thêm phần thập phân vào giá trị của $f(\mathbf{x})$.

### Ví dụ minh họa

#### Bài toán: [JOI Spring Camp 2007/2008 - Belt](https://www.acmicpc.net/problem/24144)

> Trên hệ trục tọa độ $Oxy$, cho $n$ điểm $(x_i, y_i)$ có tọa độ nguyên và một số thực $d$. Tìm một đường thẳng sao cho số điểm có khoảng cách đến đường thẳng là không quá $d$ được cực đại hóa.

Giới hạn:

- $1 \leq n \leq 1000$.
- $10^{-3} \leq d \leq 10^4$.
- $-1000 \leq x_i, y_i \leq 1000$.

*Lưu ý, giới hạn thời gian là $10$ giây.*

#### Lời giải

Như một bài hình học thông thường, ta nhận thấy rằng nếu cố định hệ số góc của đường thẳng, ta hoàn toàn có thể chọn vị trí tối ưu cho đường thẳng đó. Ví dụ, với đường thẳng nằm dọc, ta có thể sắp xếp các điểm theo $x$ sử dụng hai con trỏ để tìm đoạn con dài nhất mà hiệu giữa phần tử cuối và đầu là không quá $2d$. Tương tự với đường thẳng nằm ngang, ta giải quyết bài toán theo $y$.

Tổng quát hơn, với một hệ số gốc cho trước, ta chọn một đường thẳng bất kỳ rồi tính khoảng cách từ đường thẳng này đến các điểm. Lưu ý rằng với các điểm nằm dưới đường thẳng, ta sẽ đặt thêm dấu âm. Sau đó, ta cũng sắp xếp các điểm và giải bài toán hai con trỏ như trên.

Như vậy, ta gọi $f(\theta)$ là số điểm nhiều nhất nằm cách đường thẳng có hệ số góc $\theta$ không quá $d$ đơn vị. Rõ ràng, đây là hàm $f: \mathbb{R} \rightarrow \mathbb{Z}$ nên vô cùng bất lợi cho việc thực hiện Hill Climbing.

Để xử lý các vùng "đồng bằng" gây cản trở thuật toán, ta quan sát rằng nếu hai điểm $\theta_1$ và $\theta_2$ liền kề đều cho ra cùng giá trị $f$, ta cần kiểm tra xem điểm nào cho ra trạng thái gần với trạng thái có thể tăng giá trị $f$ hơn.

Đối với bài toán này, trong các đoạn $[L; R]$ tối ưu khi thực hiện hai con trỏ, ta lưu lại giá trị $\min(v_{R+1} - v_L, v_R - v_{L-1})$ rồi dùng giá trị này làm giá trị thứ hai để so sánh khi hàm mục tiêu cho ra cùng giá trị. Ngoài ra, vẫn còn nhiều cách thiết kế hàm khác cũng cho ra cùng tác dụng khi Hill Climbing.

#### Cài đặt

Với bài tập này, mình chọn $B = 300$, $T = 30$ và $\lambda = 0.5$ là đủ để giải quyết được toàn bộ testcase chính thức của tác giả bài tập.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Point {
    T x, y;

    Point() : x(0), y(0) {}
    Point (T x, T y) : x(x), y(y) {}

    friend T dot (Point a, Point b) { return a.x * b.x + a.y * b.y; }
    friend T cross (Point a, Point b) { return a.x * b.y - a.y * b.x; }

    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }

    bool operator == (const Point &o) const { return x == o.x && y == o.y; }
    bool operator != (const Point &o) const { return x != o.x || y != o.y; }

    friend istream& operator >> (istream &inp, Point &p) { return inp >> p.x >> p.y, inp; }
    friend ostream& operator << (ostream &ouf, const Point &p) { return ouf << "(" << p.x << ", " << p.y << ")", ouf; }
};

template<typename T>
struct Line {
    T A, B, C;

    Line() : A(0), B(0), C(0) {}
    Line (T A, T B, T C) : A(A), B(B), C(C) {}
    Line (Point<T> a, Point<T> b) : A(b.y - a.y), B(a.x - b.x), C(cross(a, b)) {}

    long double toPoint (const Point<T> &point) {
        long double numer = A * point.x + B * point.y - C;
        long double denom = sqrt(A * A + B * B);
        return numer / denom;
    }
};

const long double INF = 1e9;
const long double pi = acos(-1);
const int ROUND = 300;
const int ITERATIONS = 30;
const long double INTERVAL = 2 * pi / ROUND;
const long double COOLDOWN = 0.5;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // nhập input
    int n; long double d; cin >> n >> d;
    vector<Point<long double>> points(n);
    for (Point<long double> &point : points) cin >> point;

    // thiết kế hàm mục tiêu
    using Cost = pair<int, long double>;
    function<Cost(long double)> f = [&] (long double angle) {
        Line<long double> line(sin(angle), -cos(angle), 0);
        vector<long double> coord(n);
        for (int i = 0; i < n; i++)
            coord[i] = line.toPoint(points[i]);
        sort(coord.begin(), coord.end());

        long double nextCost = INF;
        function<void(int, int)> updateNextCost = [&] (int l, int r) {
            if (r + 1 < n) nextCost = min(nextCost, coord[r + 1] - coord[l]);
            if (l - 1 >= 0) nextCost = min(nextCost, coord[r] - coord[l - 1]);
        };

        int ans = 0, optL = 0, optR = 0;
        for (int l = 0, r = 0; l < n; l++) {
            while (r + 1 < n && coord[r + 1] - coord[l] <= 2 * d) r++;
            if (r - l + 1 >= ans) {
                if (r - l + 1 > ans)
                    ans = r - l + 1, optL = l, optR = r, nextCost = INF;
                updateNextCost(l, r);
            }
        }

        return make_pair(ans, -nextCost);
    };

    // tìm hệ số góc tối ưu bằng Hill Climbing
    Cost ans = {0, 0};
    for (int round = 0; round < ROUND; round++) {
        long double x = round * INTERVAL, step = INTERVAL;
        Cost curCost = f(x);
        for (int itr = 0; itr < ITERATIONS; itr++, step *= COOLDOWN) {
            Cost leftCost = f(x - step), rightCost = f(x + step);
            if (max(leftCost, rightCost) > curCost) {
                if (leftCost > rightCost) x -= step, curCost = leftCost;
                else x += step, curCost = rightCost;
            }
        }
        ans = max(ans, curCost);
    }

    cout << ans.first << "\n";

    return 0;
}
```
:::

## Simulated Annealing: Cải tiến Hill Climbing

Có thể thấy khi áp dụng Hill Climbing cho các hàm có nhiều cực trị, ta cần thực hiện thuật toán nhiều lần và rải $x_0$ ở các vị trí khác nhau. Bởi vì Hill Climing có một điểm yếu lớn là nó sẽ rơi vào **cực trị cục bộ (local optimum)** rất nhanh.

Tuy nhiên, khi phải giải quyết các hàm phức tạp, cách tiếp cận này không thể đảm bảo thuật toán sẽ tìm được một cực trị đủ tốt.

**Simulated Annealing** ra đời là để giải quyết vấn đề này. Ý tưởng chính của nó là cho phép Hill Climbing nhảy tới trạng thái **tệ hơn** trạng thái hiện tại (với một xác suất nhất định), để có thể tiến tới cực trị toàn cục (global optimum) tốt hơn.

![Hill_Climbing_with_Simulated_Annealing (1)](https://hackmd.io/_uploads/rkO0js7hWx.gif)
*Hoạt ảnh minh họa quá trình tìm kiếm bằng Simulated Annealing.*

Tuy nhiên, giống như bài toán chọn độ dài của bước nhảy của Hill Climbing, Simulated Annealing cũng phải có chiến lược chọn xác suất để cho phép thuật toán đi tới trạng thái tệ hơn để cân bằng việc tìm kiếm cực trị tốt và tiến đến cực trị đã nhảy đến được.

Cách tiếp cận của Simulated Annealing sẽ là cho phép thuật toán nhảy tới các trạng thái tệ hơn với xác suất cao ở những lượt đầu tiên của thuật toán, sau đó dần siết chặt việc nhảy tới các trạng thái tệ hơn. Ta có thể hình dung rằng thuật toán sẽ được tự do thăm dò hàm số trong các lượt đầu tiên và sẽ tập trung vào việc tiến đến cực trị đã nhảy đến được trong các lượt sau. Càng về cuối chương trình, Simulated Annealing sẽ càng trở về giống với Hill Climbing.

### Nhiệt độ (temperature)

Để xác định việc có cho phép thuật toán nhảy tới trạng thái tệ hơn hay không, Simulated Annealing sử dụng một đại lượng $T$, gọi là *nhiệt độ*, khi $T$ càng lớn thì bước nhảy càng "tệ" càng dễ được chấp nhận hơn.

Cụ thể hơn, giả sử ta cần cực tiểu hóa hàm mục tiêu $f(x)$, Simulated Annealing sẽ cho phép chuyển từ trạng thái $\texttt{current}$ đến trạng thái $\texttt{neighbor}$ với xác suất:

$$
\min\left(1.0, \exp \left( -\frac{f(\texttt{neighbor}) - f(\texttt{current})}{T} \right) \right)
$$

Với $\exp(x)$ là hàm $e^x$, $e$ là hằng số Euler và có giá trị xấp xỉ $2.71828$.

<!--[Sẽ thử up hoạt ảnh này thẳng lên VNOI Wiki vì quá 1MB](https://drive.google.com/file/d/1Xlhxrx4BdGJhkq-jWSgJ-BCDlNCNSBoD/view?usp=sharing)
*Hoạt ảnh minh họa hàm xác suất khi $T$ giảm từ $100$ về $0.1$. Ta có thể thấy hàm suy biến về một hàm rẻ nhánh thông thường khi $T$ tiến về $0$.*-->

Khi cài đặt, ta sử dụng một biến ngẫu nhiên $U$ phân phối đều trên khoảng $[0; 1]$. Khi đó, ta định nghĩa hàm $P(\texttt{current}, \texttt{neighbor})$ để quyết định việc thuật toán nhảy từ trạng thái $\texttt{current}$ đến trạng thái $\texttt{neighbor}$ như sau:

$$
P(\texttt{current}, \texttt{neighbor}) =
\begin{cases}
\text{True} & \text{if } U \le \exp\left(-\dfrac{f(\texttt{neighbor}) - f(\texttt{current})}{T}\right)\\[6pt]
\text{False} & \text{otherwise}
\end{cases}
$$

<!--Simulated Annealing giới thiệu khái niệm temperature, với temperature $T$ càng lớn thì bước nhảy "tệ" càng dễ được chấp nhận hơn.-->

<!--Cụ thể hơn, giả sử ta cần tối thiểu hóa $f(x)$, xét hai trạng thái là $f(cur)$ và $f(new)$, ta sẽ có một hàm đánh giá $P(f(cur), f(new), T)$, có dạng:

$$
P(f(cur), f(new), T)=
\begin{cases}
\text{True} & \text{if } U_{[0,1]} \le \exp\left(-\dfrac{f(new) - f(cur)}{T}\right)\\[6pt]
\text{False} & \text{otherwise}
\end{cases}
$$

Với:
- $U_{[0, 1]}$ là biến ngẫu nhiên phân phối đều trên đoạn $[0,1]$ (chọn một số thực trong đoạn $[0, 1]$ một cách ngẫu nhiên).
- $exp(x)$ là $e^x$, với $e$ là hằng số Euler $(\approx 2,71828)$.-->

Nếu hàm đánh giá trả về $\text{True}$, ta sẽ nhảy qua trạng thái $\texttt{neighbor}$.

Ta sẽ thấy được:
- Nếu $f(\texttt{neighbor}) \leq f(\texttt{current})$, hàm đánh giá sẽ luôn trả về $\text{True}$, vì $e^x \geq 1$ với mọi $x \geq 0$. Do đó, hàm $e^x$ luôn cho ra giá trị lớn hơn hoặc bằng $U$.
- Nếu $f(\texttt{neighbor}) < f(\texttt{current})$, nếu $T$ càng lớn thì hàm đánh giá sẽ càng dễ trả về $\text{True}$ hơn, và ngược lại.

Tương tự với khi làm các bài toán Hill Climbing trên hình học, ta có thể cho $T$ ban đầu to và sau đó giảm dần $T$ để "rà" điểm tối ưu. Việc thiết kế công thức xác định giá trị $T$ theo thời gian được thực hiện tùy vào bài toán. Thông thường, ta có thể cho $T$ giảm tuyến tính từ $T_0$ đến $T_1$ (với $T_0 \gg T_1$).

### Ví dụ minh họa

#### Bài toán: [Kattis - Travelling Salesman Problem](https://open.kattis.com/problems/tsp)

Quay lại với bài toán TSP, ta sẽ thử làm phép so sánh độ hiệu quả giữa Hill Climbing và Simulated Annealing với phương pháp lựa chọn nghiệm lân cận thứ 3 trong các phương pháp được trình bày ở phần trước:

|  | Hill Climbing | Simulated Annealing | 
| :-: | :-: | :-: |
| Điểm số | $6.853663$ | $34.657407$ | 

Như các bạn có thể thấy, Simulated Annealing tỏ ra hoàn toàn vượt trội so với Hill Climbing.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int randNum(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

double randDouble(double l, double r) {
  return uniform_real_distribution<double>(l, r)(rng);
}

const double MAX_TIME = 1.895;
double START_TEMP = 1000.0;
const double END_TEMP = 0.01;
double RATIO = END_TEMP / START_TEMP;
const int N = 1005;
int n;
double dist[N][N];
int perm[N], bestPerm[N];
double x[N], y[N];

inline void cal_temp(){
    vector <double> v;
    vector <int> p;
    for(int i = 0; i < n; ++i) p.push_back(i);
    double ave = 0, ans = 0;
    for(int test = 1; test <= 200; ++test){
        shuffle(p.begin() + 1, p.end(), rng);
        double fp = dist[p[n - 1]][p[0]];
        for (int i = 0; i + 1 < n; ++i) {
            fp += dist[p[i]][p[i + 1]];
        }
        v.push_back(fp);
        ave += fp;
    }
    ave /= 200;
    for(double d : v){
        ans += (d - ave) * (d - ave);
    }
    START_TEMP = sqrt(ans / 200);
    RATIO = END_TEMP / START_TEMP;
}

void solve() {
  iota(perm, perm + n, 0);
  shuffle(perm + 1, perm + n, rng);

  double prevScore = dist[perm[n - 1]][perm[0]];
  for (int i = 0; i + 1 < n; ++i) {
    prevScore += dist[perm[i]][perm[i + 1]];
  }
  double bestScore = prevScore;
  copy(perm, perm + n, bestPerm);
  
  double elapsedTime = 1.0 * clock() / CLOCKS_PER_SEC;
  double elaspedFrac = elapsedTime / MAX_TIME;
  double temp = START_TEMP * pow(RATIO, elaspedFrac);
  int iter = 0;
  while (true) {
    iter++;
    if ((iter & 127) == 0) {
      elapsedTime = 1.0 * clock() / CLOCKS_PER_SEC;
      elaspedFrac = elapsedTime / MAX_TIME;
      temp = START_TEMP * pow(RATIO, elaspedFrac);
    }
    if (elapsedTime > MAX_TIME) {
      break;
    }
    
    int l = randNum(1, n - 2), r = randNum(l + 2, n);
    int v1 = perm[l - 1], v2 = perm[l];
    int v3 = perm[r - 1], v4 = (r < n ? perm[r] : perm[0]);
    double scoreDelta = dist[v1][v3] + dist[v2][v4] - dist[v1][v2] - dist[v3][v4];
    double newScore = prevScore + scoreDelta;
    if (scoreDelta < 0 || exp(-scoreDelta / temp) >= randDouble(0.0, 1.0)) {
      prevScore = newScore;
      reverse(perm + l, perm + r);
    }
    if (newScore < bestScore) {
      bestScore = newScore;
      copy(perm, perm + n, bestPerm);
    }
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
  }
  if (n == 1){
    cout << 0 << '\n';
    return 0;
  }
  if (n == 2){
    cout << "0\n1\n";
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);
    }
  }
  cal_temp();
  solve();
  for (int i = 0; i < n; ++i) {
    cout << bestPerm[i] << '\n';
  }
}
```
::::::

Để đạt được hiệu quả tối ưu cho Simulated Annealing, bạn đọc có thể sử dụng một số mẹo cài đặt như sau:

- Cố định `START_TEMP` và `END_TEMP` trước khi chạy, trong đó:
    - `START_TEMP` là **độ lệch chuẩn** của $n$ ($\approx 200$) trạng thái ngẫu nhiên.
    - `END_TEMP` có thể để trong khoảng $[10^{-6}; 10^{-2}]$.
- Luôn cố định thời gian chạy cho một lần Simulated Annealing.
    - Temperature $T$ sẽ giảm dần trên từ `END_TEMP` về `START_TEMP`.
    - Gọi hàm thời gian (hàm `clock()`) một lần mỗi $128$ iteration, vì hàm này chạy tương đối lâu so với các phép toán cộng, trừ, nhân, chia, hay truy cập mảng $\mathcal{O}(1)$ thông thường.

## Phụ lục

### Bài tập ứng dụng

- [Học sinh giỏi Quốc gia năm học 2025-2026, Bài 6, Cắm trại](https://oj.vnoi.info/problem/voi26_camp)
- [USACO, Subsequence Reversal](https://usaco.org/index.php?page=viewproblem2&cpid=698)
- [Codeforces Deltix Round, Summer 2021, H, DIY Tree](https://codeforces.com/contest/1556/problem/H)
- [AtCoder Introduction to Heuristics Contest, A, AtCoder Contest Scheduling](https://atcoder.jp/contests/intro-heuristics/tasks/intro_heuristics_a)
- [Codeforces Round 375, E, One-way Reform](https://codeforces.com/contest/723/problem/E)
- [VM 2014, bài 19, Sudoku](https://oj.vnoi.info/problem/vmsudoku)
- [VM 2015, bài 03, Cắt đồ thị](https://oj.vnoi.info/problem/vmcut)
- [VNOJ, Rước đuốc Olympic](https://oj.vnoi.info/problem/torch)
- [Olympic Sinh viên 2023, Siêu cúp, Bài 3, Giao hàng](https://oj.vnoi.info/problem/olp_sc23_shipper)
- [Kì thi chọn Đội tuyển Quốc gia (TST) 2023, Bài 5](https://oj.vnoi.info/problem/tst23_e)

### Tài liệu tham khảo

- [Nguyễn Tiến Trung Kiên (kc97ble). Kĩ thuật leo đồi.](https://sites.google.com/site/kc97ble/3-k%C4%A9-n%C4%83ng/k%C4%A9-thu%E1%BA%ADt-leo-%C4%91%E1%BB%93i?authuser=0)
- [Nhiều tác giả. Simulated Annealing (CP-Algorithms).](https://cp-algorithms.com/num_methods/simulated_annealing.html)
- [Matthias Englert, Heiko Roglin. Smoothed Analysis of the 2-Opt Algorithm for the General TSP](http://www.roeglin.org/publications/2Opt-General.pdf)