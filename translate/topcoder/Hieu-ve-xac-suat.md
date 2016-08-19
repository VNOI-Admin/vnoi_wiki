# Xác suất

Nguồn: [Understanding Probabilities - Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/understanding-probabilities/)
 [[_TOC_]]

Xác suất là một nhánh của Toán học có rất nhiều ứng dụng trong thực tế, chẳng hạn như trong phân tích giá cả thị trường, chuẩn bị chiến lược trong thi đấu thể thao, dự báo thời tiết.. Bạn có thể đọc thêm về ứng dụng của xác suất trên [[Quora|https://www.quora.com/What-are-the-real-life-applications-of-probability-in-math]].

Đa số các bài toán về xác suất đều được lấy ví dụ từ thực tế. Ví dụ: Kỳ thi sắp đến, có 20 chủ đề cần học và bạn chỉ có đủ thời gian để học 15 chủ đề. Nếu trong bài kiểm tra chỉ có 2 câu hỏi (mỗi câu hỏi về 1 chủ đề), thì xác suất bạn có thể trả lời đc cả 2 câu là bao nhiêu?

Không khó để nhận ra bài tập nào cần dùng kiến thức về xác suất nhưng giải được chúng là một câu chuyện hoàn toàn khác. Biết cách để tiếp cận những bài toán như vậy là một lợi thế lớn trong các cuộc thi lập trình, và bài viết dưới đây sẽ trang bị những kiến thức nền tảng cho bạn.

# Cơ bản

Ta hình dung làm việc với xác suất như tiến hành một cuộc thí nghiệm:

- **Kết quả** (*outcome*) là kết quả của cuộc thí nghiệm hoặc những trường hợp có bao gồm sự không chắc chắn.
- Tập hợp của tất cả những kết quả có thể của thí nghiệm được gọi là **không gian mẫu** (*sample space*), thường được kí hiệu bởi $S$. Mỗi kết quả có thể xảy ra được biểu diễn bởi một và chỉ một điểm trong không gian mẫu.

Chúng ta cùng xem xét ví dụ dưới đây:

- Tung cục xúc sắc một lần
  - Không gian mẫu $S = {1,2,3,4,5,6} $
- Tung hai đồng xu
  - Không gian mẫu $S = { (0, 0), (0, 1), (1, 0), (1, 1) }$ với 0 thể hiện đồng xu sấp và 1 thể hiện đồng xu ngửa.

Ta định nghĩa một **biến cố** (**event**) là một tập hợp các kết quả của một thí nghiệm. Do đó, một biến cố là một tập con của không gian mẫu $S$. Nếu chúng ta đặt biến cố là $E$, thì chúng ta có thể nói rằng $E \subseteq S$. Nếu một biến cố chỉ bao gồm một kết quả duy nhất trong không gian  mẫu, ta vẫn có thể gọi chúng là biến cố. Biến cố bao gồm nhiều hơn một kết quả được gọi là **biến cố kép*** (**compound event**), ví dụ như trong thí nghiệm tung 2 đồng xu ở trên.

Cái chúng ta quan tâm nhất là xác suất để một biến cố nhất định xảy ra, $P(E)$. Theo định nghĩa, $P(E)$ là một số thực trong khoảng từ $0$ đến $1$, trong đó $0$ là biến cố không có khả năng xảy ra và $1$ là biến cố chắc chắn xảy ra (hay là toàn bộ không gian mẫu).

[[/uploads/translate_topcoder_undertstandprobabilities_1.gif]]

- Impossible Event: biến cố chắc chắn ko thể xảy ra
- Certain: biến cố chắc chắn xảy ra
- Even chance: biến cố có xác suất 50-50.

Như đã đề cập, mỗi kết quả khả thi được biểu diễn bởi đúng một điểm trong không gian mẫu. Điều này đưa ta đến công thức:

$P(E) = \frac{\left | E \right |}{\left | S \right |}$

Nói cách khác, ta có thể tính xác suất để một biến cố xảy ra bằng cách chia **số khả năng đúng** (theo biến cố $E$) cho **tổng số kết quả có thể xảy ra** (theo không gian mẫu $S$). Để diễn tả mối quan hệ giữa các biến cố, bạn có thể dùng các quy ước từ lý thuyết về tập hợp. Xét trường hợp tung con xúc sắc một lần. Như trên, ta có $S = \{1,2,3,4,5,6\}$. Xem xét những biến cố dưới đây:

- Biến cố $A$: *điểm > 3*: ${4,5,6}$
- Biến cố $B$: *điểm là số lẻ*: ${1,3,5}$
- Biến cố $C$: *điểm là 7*: $\varnothing $
- $A \cup B$: *điểm > 3* hoặc *điểm là số lẻ*: $={1, 3, 4, 5, 6}$
- $A \cap B$: *điểm > 3* và *là số lẻ*: $ {5}$
- $A'$: *biến cố A không xảy ra*: ${1, 2, 3}$

Xác suất:

- $P(A \cup B) = 5/6$
- $P(A \cap B) = 1/6$
- $P(A’) = 1 – P(A) = 1 – 1/2 = 1/2 $
- $P(C) = 0$

Bước đầu tiên khi giải một bài toán về xác suất là xác định được không gian mẫu. Tiếp theo, bạn sẽ phải xác định số lượng của biến cố thỏa mãn. Đây là cách tiếp cận cơ bản, nhưng khi áp dụng, nó có thể thay đổi tùy vào từng bài tập.

## Ví dụ

[QuizShow (SRM 223, Div 1 – Easy)](https://community.topcoder.com/stat?c=problem_statement&pm=2989&rd=5869).

**Tóm tắt đề bài**

Trong một cuộc thi, bạn đang đấu với 2 người nữa để tiến vào câu hỏi cuối cùng. Mỗi người đang sở hữu một số điểm nhất định giành được từ các câu hỏi trước. Tại câu hỏi này, mỗi người sẽ đưa ra số điểm cược trong khoảng từ 0 đến số điểm đang có, nếu trả lời đúng sẽ được số điểm cược này, trả lời sai sẽ bị trừ đúng bằng số điểm đã cược. Để chiến thắng, bạn phải là người sở hữu số điểm cao nhất sau khi hoàn thành câu hỏi cuối cùng.

Bạn biết điểm hiện tại của cả 3 người (số nguyên không quá $10^4$), và giá trị tiền cược của 2 người kia.

Hỏi bạn nên cược bao nhiêu để xác suất thằng là lớn nhất.

**Phân tích**

Mấu chốt để giải quyết bài toán là xét đến tất cả các khả năng có thể, số lượng này không nhiều. Sau một lúc đánh giá, ta sẽ xác định được không gian mẫu:

```
S = {
  ( người 1 đúng, người 2 sai, bạn sai),
  ( người 1 đúng, người 2 sai, bạn đúng),
  ( người 1 đúng, người 2 đúng, bạn sai),
  ( người 1 đúng, người 2 đúng, bạn đúng),

  ( người 1 sai, người 2 sai, bạn sai),
  ( người 1 sai, người 2 sai, bạn đúng),
  ( người 1 sai, người 2 đúng, bạn sai),
  ( người 1 sai, người 2 đúng, bạn đúng)
}
```

Đề bài yêu cầu bạn tìm số tiền cược để tối đa số kết quả bạn thắng. Để đếm được số kết quả ưa thích cho từng số tiến cược, ta cần xác định xem là cả ba người chơi sẽ kết thúc với bao nhiêu điểm trong 8 trường hợp có thể xảy ra. Ý tưởng được thể hiện trong code dưới đây

```cpp
int wager (vector  scores, int wager1, int wager2)
{
 int best, bet, odds, wage, I, J, K;
 best = 0; bet = 0;

 for (wage = 0; wage <= scores[0]; wage++)
 {
  odds = 0;
  // 'odds' dem so ket qua tot
  for (I = -1; I <= 1; I = I + 2)
   for (J = -1; J <= 1; J = J + 2)
    for (K = -1; K <= 1; K = K + 2)
     if (scores[0] + I * wage > scores[1] + J * wager1  &&
      scores[0] + I * wage > scores[2] + K * wager2) { odds++; }

  //  mot so tien cuoc tot hon duoc tim thay, cap nhat ket qua
  if (odds > best)  { bet = wage ; best = odds; }
 }
 return bet;
}
```

Một bài thú vị khác là [PipeCuts (SRM 233, Div 1 – Easy)](http://community.topcoder.com/stat?c=problem_statement&pm=3994&rd=6532), bài này có thể giải bằng cách tương tự như trên.


## Biến cố độc lập

Xét $n$ biến cố độc lập (*independent events*): $ E_1, E_2, ..., E_n$ . Hai câu hỏi thường gặp sẽ là

1. Xác suất để tất cả biến cố xảy ra?: $P(all)$
2. Xác suất để ít nhất một biến cố trong số chúng xảy ra? $P(any)$

Để trả lời câu hỏi thứ nhất, ta xét biến cố đầu tiên ($E_1$):

- Nếu $E_1$ không xảy ra, giả thuyết không còn đúng nữa.
- Vì vậy, phải chắc rằng $E1$ sẽ xảy ra với xác suất $P(E_1)$. Điều này có nghĩa là có xác suất $P(E_1)$ để ta kiểm tra sự xảy ra của biến cố tiếp theo (gọi là $E_2$).
- Biến cố $E_2$ xảy ra với xác suất là $P(E_2)$, và chúng ta có thể tiếp tục quá trình này tương tự như vậy.

Vì xác suất được định nghĩa là một số thực nằm trong khoảng từ 0 đến 1, ta tổng hợp được xác suất để tất cả các biến cố xảy ra bằng công thức dưới đây:

  $P(all) = P(E_1) \* P(E_2) \* ... \* P(En) $

Cách tốt nhất để trả lời câu hỏi thứ hai là tìm xác suất để không có biến cố nào diễn ra và lấy phần bù.

  $P(any) = 1 - P(E_1') \* P(E_2') \* ... \* P(E_n') $

Những công thức trên được ứng dụng rất nhiều, cần nắm chắc để đi đền phần tiếp theo.

## [BirthdayOdds](http://community.topcoder.com/stat?c=problem_statement&pm=1848&rd=4675)

Một ví dụ điển hình để mô tả nội dung xác suất được bàn luận ở phần trên là [[**Birthday Paradox**]](https://en.wikipedia.org/wiki/Birthday_problem). Người ta đã chứng minh được nếu có ít nhất 23 người trong một căn phòng, hơn 50% xác suất để 2 người bất kì trong số họ sẽ có cùng một ngày sinh nhật. Nó được gọi là nghịch lý về ngày sinh vì nó trái ngược với cảm giác thông thường. Bây giờ, một bài toán đặt ra là tìm số người nhỏ nhất để xác suất có ít nhất người trong số họ cùng ngày sinh nhật là lớn hơn x %. Việc đầu tiên có thể nghĩ đến là giải bài toán ngược: "xác suất để $N$ người ngẫu nhiên có ngày sinh khác nhau?" dễ hơn. Chiến thuật là bắt đầu với một cái phòng rỗng và lần lượt thêm từng người một vào, so sánh ngày sinh của người đó với tất cả những người đã có trong phòng.

```cpp
int minPeople (int minOdds, int days) {
  int nr;
  double target, p;

  target = 1 - (double) minOdds / 100;
  nr = 1;
  p = 1;

  while (p > target) {
    p = p * ( (double) 1 - (double) nr / days);
    nr ++;
  }

  return nr;
}
```

Đôi khi các bài toán về xác suất có thể phức tạp. Như chúng ta đã thấy, 'Birthday Paradox' tạo cảm giác mâu thuẫn với suy nghĩ thông thường của ta. Nhưng nó lại có thể chứng minh tính đúng đắn nhờ vào các các công thức. Công thức có thể hỗ trợ, nhưng để trở nên thành thạo về xác suất bạn cần thêm một vũ khí nữa: "cảm nhận về Toán học". Vũ khí này có được một phần là nhờ bẩm sinh, và một phần học được thông qua luyện tập. Làm [bài kiểm tra](http://teacherlink.org/content/math/interactive/probability/interactivequiz/question1/home.html) này để kiểm tra cảm giác số học của bạn cũng như đối mặt với những hiểu lầm về xác suất.

# Tính xác suất từng bước một

Trong phần dưới đây, chúng ta sẽ tiếp tục thảo luận một vài bài tập trên Topcoder mà trong đó:

> Xác suất của một biến cố bị ảnh hưởng bởi biến cố khác.

Chúng ta có thể hình dung nó như một đồ thị mà trong đó:

- Mỗi nút là một biến cố
- Mỗi cạnh thể hiện sự phụ thuộc giữa các nút.

So sánh này hơi gượng ép, nhưng cách chúng ta tính toán xác suất cho các biến cố rất giống cách chúng ta đi qua các đỉnh của đồ thị: Ta bắt đầu ở gốc - là trạng thái ban đầu và có xác suất là 1. Sau đó, ta xem xét các cạnh kề để đến các khả năng khác nhau kèm theo các xác suất tương ứng.

## [Nested Randomness](http://community.topcoder.com/stat?c=problem_statement&pm=3510&rd=6527)

**Tóm tắt đề bài**:

Hàm `random(N)` trả về một số nguyên ngẫu nhiên trong khoảng từ $0$ đến $N-1$, mỗi số có xác suất được trả lại như nhau và bằng $1/N$.

Giờ xét `random(random(N))`. Để dễ hình dung, ta xét $N=4$:

- `random(N)` trả lại các số nguyên 0 đến 3 với xác suất bằng nhau là $1/4$.
- `random(random(N))`, ta có 4 trường hợp với xác suất bằng nhau (phụ thuộc vào kết quả của hàm `random` bên trong):
  - `random(0)`: được gọi với xác suất $1/4$: báo lỗi
  - `random(1)`: được gọi với xác suất $1/4$: luôn trả về 0
  - `random(2)`: được gọi với xác suất $1/4$: trả về 0 hoặc 1 với xác suất $1/2$.
  - `random(3)`: được gọi với xác suất $1/4$: trả về 0, 1, hoặc 2 với xác suất $1/3$.
- Nếu xét tiếp `random(random(random(N)))`:
  - `random(0)`: được gọi với xác suất $1/4 + 1/8 + 1/12 = 11/24$
  - `random(1)`: được gọi với xác suất $1/8 + 1/12 = 5/24$
  - `random(2)`: được gọi với xác suất $1/12$
- ...

Ta hình dung bằng hình sau:

[[/uploads/translate_topcoder_understandprobabilties_02.gif]]

Code để giải bài này

```cpp
double probability (int N, int nestings, int target) {
  int I, J, K;
  double A[1001], B[2001];
  // A[I] la xac suat de so I xuat hien

  for (I = 0; I < N ; I++)
    A[I] = (double) 1 / N;

  for (K = 2; K ≤ nestings; K++) {
    for (I = 0; I < N; I++)
      B[I] = 0;

    // voi moi I giua 0 den N-1, ta goi ham random(I)
    // theo yeu cau de bai
    for (I = 0; I < N; I++)
      for (J = 0; J < I; J++)
        B[J] +=  (double) A[I] / I;

    for (I = 0; I < N; I++)
      A[I] = B[I];
  }
  return A[target];
}
```

Bài tập tương tự:

- [ChessKnight](http://community.topcoder.com/stat?c=problem_statement&pm=3509&rd=6528),
- [DiceThrows](http://community.topcoder.com/stat?c=problem_statement&pm=4450&rd=7217),
- [RockSkipping](http://community.topcoder.com/stat?c=problem_statement&pm=1954&rd=5006),
- [PointSystem](http://community.topcoder.com/stat?c=problem_statement&pm=1849&rd=4675),
- [VolleyBall](http://community.topcoder.com/stat?c=problem_statement&pm=2959&rd=5880)

## [GeneticCrossover](https://community.topcoder.com/stat?c=problem_statement&pm=2974&rd=5875)

### Khái niệm

Ở bài này có khái niệm về **xác suất có điều kiện** (*conditional probability*):

> Xác suất có điều kiện là xác suất của một biến cố A nào đó, biết rằng một biến cố B khác xảy ra.

Ký hiệu $P(A|B)$, và đọc là "xác suất của A, biết B". Nếu $A$ và $B$ là các biến cố, và $P(B) > 0$, thì xác suất có điều kiện của $A$ nếu biết $B$ là:

$P(A|B) = \frac{P(A \cap B)}{P(B)}$

Tương đương, ta có

$P(A \cap B) = P(A|B) P(B)$


### Phân tích

Bạn được yêu cầu dự đoán về chất lượng của một con vật, dựa trên mã gen mà chúng nhận từ bố mẹ. Dựa vào mô tả đề bài, có hai trường hợp có thể xảy ra: một gen không phụ thuộc vào gen khác, hoặc gen này có phụ thuộc.

Trường hợp thứ nhất, gọi $p$ là xác suất mà gen này là gen trội. Có 4 trường hợp:

- Ít nhất bố hoặc mẹ có hai gen trội ($p = 1$)
- Mỗi bố hoặc mẹ có đúng một gen trội ($p = 0.5$)
- Mỗi bố hoặc mẹ có một gen trội và người còn lại có duy nhất một gen lặn ($p = 0.25$)
- Cả hai bố mẹ có hai gen lặn ($p = 0$)

Giờ ta sẽ xem trường hợp khi một gen phụ thuộc vào một gen khác. Điều này làm bài toán trở nên phức tạp hơn do gen “bố mẹ” có thể lại phụ thuộc vào một gen khác và cứ thế... Để xác định được xác suất mà một gen phụ thộc là gen trội, ta sẽ kiểm tra biến cố mỗi gen trong chuỗi (bắt  đầu gen đang xé) là gen trội. Để gen hiện tại là gen trội, ta cần tất các biến cố như vậy xảy ra. Để thực hiện được điều này, ta lấy tích của xác suất của từng biến cố một trên chuỗi. Thuật toán thực hiện một cách đệ quy, và đây code hoàn chỉnh cho bài tập này:

```cpp
int n, d[200];
double power[200];

// here we determine the characteristic for each gene (in power[I]
// we keep the probability of gene I to be expressed dominantly)
double detchr (string p1a, string p1b, string p2a, string p2b, int nr) {
  double p, p1, p2;
  p = p1 = p2 = 1.0;
  if (p1a[nr] <= 'Z')
    p1 = p1 - 0.5;

  //  is a dominant gene
  if (p1b[nr] <= 'Z')
    p1 = p1 - 0.5;
  if (p2a[nr] <= 'Z')
    p2 = p2 - 0.5;
  if (p2b[nr] <= 'Z')
    p2 = p2 - 0.5;
  p = 1 - p1 * p2;

  if (d[nr] != 1)
    power[nr] = p * detchr (p1a, p1b, p2a, p2b, d[nr]);
  // gene 'nr' is dependent on gene d[nr]
  else power[nr] = p;
  return power[nr];
}

double cross (string p1a, string p1b, string p2a, string p2b,
 vector dom, vector rec, vector dependencies) {
  int I;
  double fitness = 0.0;


  n = rec.size();
  for (I = 0; I < n; i++)
    d[i] = dependencies[i];
  for (I = 0 ;I < n; I++)
    power[i] = -1.0;
  for (I = 0; I < n; i++)
    if (power[I] == -1.0)
      detchr (p1a, p1b, p2a, p2b, i);

  // we check if the dominant character of gene I has
  // not already been computed
  for (I = 0; I <= n; I++)
    fitness = fitness + (double) power[i] * dom[i]-(double) (1-power[i]) * rec[i];
  // we compute the expected 'quality' of an animal based on the
  // probabilities of each gene to be expressed dominantly

  return fitness;
}
```

Bài tương tự: [ProbabilityTree](http://community.topcoder.com/stat?c=problem_statement&pm=2234&rd=4675)

# Thuật toán ngẫu nhiên

Ta gọi những thuật toán ngẫu nhiên là những thuật toán mà nó dùng số được sinh ra một cách ngẫu nhiên để đưa ra quyết định trong quá trình chạy. Không giống như những thuật toán đã xác định trước, với mỗi dữ liệu vào xác định thì sẽ cho ra duy nhất một kết quả ra cũng như thời gian chạy, thuật toán ngẫu nhiên sẽ biểu hiện khác nhau trong mỗi lần chạy. Cơ bản, ta sẽ phân biện hai loại của thuật toán ngẫu nhiên:

1. Thuật toán Monte Carlo: có thể vài lần đưa ra kết quả sai - tuy nhiên xác suất của sai sót là chấp nhật được.
2. Thuật toán Las Vegas: luôn cho kết quả đúng, và điểm khác biệt giữa các lần chạy với cùng một dữ liệu vào là thời gian chạy - ta sẽ nghiên cứu và sự phân phối theo xác suất của thời gian chạy.

Tham khảo [tài liệu](http://www.ews.uiuc.edu/~kumar/lectures/lecture.10.3.pdf) từ College of Engineering at UIUC để xem các các thuật toán này hoạt động.

Mục tiêu chính của thuật toán ngẫu nhiêu là để xây dựng một thuật toán nhanh hơn, cũng có thể đơn giản hơn. Khả năng đơn giản hóa một vấn đề chính là một lợi ích của thuật toán ngẫu nhiên. Nên không lấy làm lạ khi các thuật toán như vậy được đưa ra nghiên cứu rộng rãi và được ứng dụng để giải quyết các vấn đề một cách đơn giản hơn.

Một câu hỏi thú vị được đưa ra là liệu những thuật toán như vậy có ích trong các kì thi lập trình hay không. Khi bạn không nghĩ ra một cách nào để giải, hướng đi hợp lý là thử cài một cách random. Độ tốt của việc random phụ thuộc nhiều vào tính chất của bài toán, và khi có kinh nghiệm cũng như cảm nhận Toán học tốt, bạn có thể đoán được là random có thể chạy đúng được với bài toán hay không. Tham khảo [QueenInterference](http://community.topcoder.com/stat?c=problem_statement&pm=2935&rd=585)

Trong các bài toán tối ưu hóa, nếu số nghiệm tối ưu khá nhiều so với số khả năng có thể xảy ra, một thuật toán random đơn giản như sau cũng có thể có hi vọng chạy đúng:

```cpp
Max = 1000000; attempt = 0;
while (attempt < Max) {
  answer = solve_random (...);
  if (better (answer, optimum))
  // Tìm được kết quả tốt hơn
  {
    optimum = answer;
    cout << "Solution " << answer << " found on step " << attempt << "\n";
  }
  attempt ++;
}
```

# Bài tập luyện tập

ND: Mình không chép lại danh sách bài tập trong bài viết gốc ở Topcoder do sau này tác giả có thể chỉnh sửa hay bổ sung. Các bạn xem cuối [bài viết gốc trên Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/understanding-probabilities/) để luyện tập thêm.
