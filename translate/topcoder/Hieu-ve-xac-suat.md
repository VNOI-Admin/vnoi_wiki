#Hiểu về xác suất
Nguồn: supernova trên [topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/understanding-probabilities/) 
 [[_TOC_]]
 
Quả không ngoa khi nói rằng cuộc sống là một phòng thi về xác suất. Ứng dụng chủ yếu của lý thuyết xác suất trong cuộc sống hằng ngày là đo lường rủi ro. Một ví dụ được lấy từ thực tiễn là hãy tưởng tượng bạn sẽ phải đối mặt với một kì kiểm tra có 20 môn và bạn không có đủ thời gian để chuẩn bị chu đáo, bạn chỉ có thể ôn được 15 môn thôi. Khi đưa ra 2 môn bất kì, xác suất mà bạn đã chuẩn bị được cả hai môn là bao nhiêu? 

Cuộc sống là một chuỗi phức tạp các sự kiện và gần như mọi thứ đều có thể được hình dung dưới dạng xác suất. 
Cờ bạc đã trở thành một phần trong cuộc sống của chúng ta, và đây cũng là lĩnh vực mà lý thuyết xác suất được ứng dụng rộng rãi. Mặc dù cờ bạc đã xuất hiện từ thời xa xưa, nhưng đến tận thế kỉ 17, nền tảng toán học của lĩnh vực này mới được đưa ra. Tất cả bắt đầu với một câu hỏi đơn giản của Chevalier de Mï¿½rï¿½ - một nhà quý tộc dùng bài bạc như là một cách để gia tăng khối tài sản kếch sù của mình - gửi đến cho Blaise Pascal. Câu hỏi là có thể nhận được cặp sáu trong 24 lần tung một đôi xí ngầu hay không? 

Đa số các bài toán về xác suất đều được lấy ví dụ từ thực tế. Bạn sẽ được đưa ra tình huống và giải thích về luật chơi của trò chơi. Không khó để nhận ra bài tập nào cần dùng kiến thức về xác suất nhưng giải được chúng là một câu chuyện hoàn toàn khác. Biết cách để tiếp cận những bài toán như vậy là một lợi thế lớn trong các cuộc thi lập trình, và bài viết dưới đây sẽ trang bị những kiến thức nền tảng cho bạn.

##Cơ bản
Làm việc với xác suất cũng tương tự với tiến hành một cuộc thí nghiệm. **Kết quả** (*outcome*)  là kết quả của cuộc thí nghiệm hoặc những trường hợp có bao gồm sự không chắc chắn. Tập hợp của tất cả những kết quả có thể của thí nghiệm mang tính xác suất được gọi là **không gian mẫu** (*sample space*). 

Mỗi kết quả có thể xảy ra được biểu diễn bởi một và chỉ một điểm trong không gian mẫu (thường được kí hiệu bởi $S$). Chúng ta cùng xem xét ví dụ dưới đây:

Tung cục xí ngầu một lần

Không gian mẫu $S = \{1,2,3,4,5,6\} $ 

Tung hai đồng xu 

Không gian mẫu $S = \{ (Sấp, Sấp), (Sấp, Ngửa), (Ngửa, Sấp), (Ngửa, Ngửa) \}$

Ta định nghĩa một **sự kiện** là một tập hợp các kết quả của một thí nghiệm. Do đố, một sự kiện là một tập con của không gian mẫu $S$. Nếu chúng ta đặt sự kiện là $E$, thì chúng ta có thể nói rằng $E ⊆ S$. Nếu một sự kiện chỉ bao gồm một kết quả duy nhất trong không gian  mẫu, ta gọi chúng là sự kiện được. Sự kiện bao gồm nhiều hơn một kết quả được gọi là sự kiện kép.

Cái chúng ta quan tâm nhất là xác suất để một sự kiện nhất định xảy ra, $P(E)$. Theo định nghĩa, $P(E)$ là một số thực trong khoảng từ $0$ đến $1$, trong đó $0$ là sự kiện không có khả năng xảy ra và $1$ là sự kiện chắc chắn xảy ra (hay là toàn bộ không gian mẫu). 

[[/uploads/translate_topcoder_undertstandprobabilities_1.gif]]

Như đã đề cập, mỗi kết quả khả thi được biểu diễn bởi đúng một điểm trong không gian mẫu. Điều này đưa ta đến công thức:

$P(E) = \frac{\left | E \right |}{\left | S \right |}$

Nói cách khác, ta có thể tính xác suất để một sự kiện xảy ra bằng cách chia số **kết quả ưu thích** (theo sự kiện $E$) cho **tổng số kết quả có thể xảy ra** (theo không gian mẫu $S$). Để diễn tả mối quan hệ giữa các sự kiện, bạn có thể dùng các quy ước từ lý thuyết về tập hợp. Xét trường hợp tung con xí ngầu một lần. Như ta đã thấy trước đó, 
$S = \{1,2,3,4,5,6\}$. Xem xét những sự kiện dưới đây:

 Sự kiện $A =$ 'điểm>3' = $\{4,5,6\} $

 Sự kiện $B = $'điểm là số lẻ' = $ \{1,3,5\}$

 Sự kiện $C =$ 'điểm là 7' = $\varnothing $

 $A∪B =$ 'điểm > 3 hoặc điểm là số lẻ hoặc cả hai' $=\{1, 3, 4, 5, 6\}$

 $A∩B =$ 'điểm > 3 và là số lẻ' $ = \{5\}$

 $A' =$ 'sự kiện A không xảy ra' $= \{1, 2, 3\}$

Tính toán xác suất, ta được

$P(A∪B) = 5/6 $

$P(A∩B) = 1/6 $

$P(A’) = 1 – P(A) = 1 – 1/2 = 1/2 $

$P(C) = 0$

Bước đầu tiên khi giải một bài toán về xác suất là xác định được không gian mẫu. Tiếp theo, bạn sẽ phải xác định số lượng của sự kiện ưa thích. Đây là cách tiếp cận cơ bản, nhưng khi áp dụng, nó có thể thay đổi tùy vào từng bài tập. 

Lấy bài  [ QuizShow (SRM 223, Div 1 – Easy) ](https://community.topcoder.com/stat?c=problem_statement&pm=2989&rd=5869) làm ví dụ. 

ND: Mình xin tóm tắt lại đề bài. Trong một cuộc thi, bạn đang đấu với 2 người nữa và tiến vào câu hỏi cuối cùng. Mỗi người đang sở hữu một số điểm nhất định giành được từ các câu hỏi trước. Tại câu hỏi này, mỗi người sẽ đưa ra số điểm cược trong khoảng từ 0 đến số điểm đang có, nếu trả lời đúng sẽ được số điểm cược này, trả lời sai sẽ bị trừ đúng bằng số điểm đã cược. Để chiến thắng, bạn phải là người sở hữu số điểm cao nhất sau khi hoàn thành câu hỏi cuối cùng. Hỏi bạn nên cược bao nhiêu để xác suất thằng là lớn nhất (nếu có nhiều cách cược để đạt được xác suất thắng lớn nhất, được ra số điểm cược nhỏ nhất).

Mấu chốt để giải quyết bài toán là xét đến tất cả các khả năng có thể, số lượng này không nhiều lớn. Sau một lúc đánh giá, ta sẽ xác định được không gian mẫu:

S= {( người 1 đúng, người 2 sai, bạn sai),

( người 1 đúng, người 2 sai, bạn đúng),

( người 1 đúng, người 2 đúng, bạn sai).

( người 1 đúng, người 2 đúng, bạn đúng),

( người 1 sai, người 2 sai, bạn sai),

( người 1 sai, người 2 sai, bạn đúng),

( người 1 sai, người 2 đúng, bạn sai).

( người 1 sai, người 2 đúng, bạn đúng)} 

Đề bài yêu cầu bạn tìm số tiền cược để tối đa số kết quả ưu thích (bạn thắng). Để đếm được số kết quả ưa thích cho từng số tiến cược, ta cần xác định xem là cả ba người chơi sẽ kết thúc với bao nhiêu điểm trong 8 trường hợp có thể xảy ra. Ý tưởng được thể hiện trong code dưới đây

```cpp
int wager (vector  scores, int wager1, int wager2)
{
 int best, bet, odds, wage, I, J, K;
 best = 0; bet = 0;

 for (wage = 0; wage ≤ scores[0]; wage++)
 {
  odds = 0;
  //  'odds' dem so ket qua ua thich
  for (I = -1; I ≤ 1; I = I + 2)
   for (J = -1; J ≤ 1; J = J + 2)
    for (K = -1; K ≤ 1; K = K + 2)
     if (scores[0] + I * wage > scores[1] + J * wager1  &&
      scores[0] + I * wage > scores[2] + K * wager2)   { odds++; }
  if (odds > best)  { bet = wage ; best = odds; }
  //  mot so tien cuoc tot hon duoc tim thay
 }
 return bet;
}
```
Một bài thú vị khá để bắt đầu là [PipeCuts (SRM 233, Div 1 – Easy)](http://community.topcoder.com/stat?c=problem_statement&pm=3994&rd=6532), bài này có thể giải bằng cách tương tự như trên. Có một số lượng hữu hạn các kết quả, và công việc của bạn là xem xét từng cái một.

Xét n sự kiện độc lập (*independent events*): $ E1, E2, ..., En $ . Hai câu hỏi thường gặp sẽ là 

1. Xác suất để tất cả sự kiện xảy ra?

2. Xác suất để ít nhất một sự kiện trong số chúng xảy ra?

Để trả lời câu hỏi thứ nhất, ta sẽ liên hệ đến sự xảy ra của sự kiện thứ nhất ($E1$). Nếu $E1$ không xảy ra, giả thuyết không còn đúng nữa. Vì vậy, phải chắc rằng $E1$ sẽ xảy ra với xác suất $P(E1)$. Điều này có nghĩ là có xác suất $P(E1)$ để ta kiểm tra sự xảy ra của sự kiện tiếp theo (gọi là $E2$). Sự kiện $E2$ xảy ra với xác suất là $P(E2)$, và chúng ta có thể tiếp tục quá trình này tương tự như vậy. Vì xác suất được định nghĩa  là một số thực nằm trong khoảng từ 0 đến 1, ta tổng hợp được xác suất để tất cả các sự kiện xảy ra bằng công thức dưới đây:

$ P(tất cả sự kiện) = P(E1) * P(E2) * ... * P(En) $

Cách tốt nhất để trả lời câu hỏi thứ hai là tìm xác suất để không có sự kiện nào dễ ra và lấy phần bù.

$ P(ít nhất một sự kiện xảy ra) = 1 - P(E1') * P(E2') * ... * P(En') $

Những công thức trên được ứng dụng rất nhiều, cần nắm chắc để đi đền phần tiếp theo.

### [BirthdayOdds](http://community.topcoder.com/stat?c=problem_statement&pm=1848&rd=4675)
Một ví dụ điển hình để mô tả nội dung xác suất được bàn luận ở phần trên là "Birthday Paradox". Nó đã được chứng minh rằng nếu có ít nhất 23 người trong một căn phòng, hơn 50% xác suất để 2 người bất kì trong số họ sẽ có cùng một ngày sinh nhật. Dù đây không phải phải là một nghịch lý xảy ra ngoài cuộc sống, nhưng là một nghịch lý được chứng minh bằng toán học dù hơi trái ngược với suy nghĩ thông thường. Bây giờ, một bài toán đặt ra là tìm số người nhỏ nhất để xác suất có ít nhất người trong số họ cùng ngày sinh nhật là lớn hơn x %. Việc đầu tiên có thể nghĩ đến là giải bài toán ngược: "xác suất để N người ngẫu nhiên có ngày sinh khác nhau?" dễ hơn. Chiến thuật là bắt đầu với một cái phòng rỗng và lần lượt thêm từng người một vào, so sánh ngày sinh của người đó với tất cả những người đã có trong phòng.

```
int minPeople (int minOdds, int days)
{
 int nr;
 double target, p;

 target = 1 - (double) minOdds / 100;
 nr = 1;
 p = 1;

 while (p > target)
 {
  p = p * ( (double) 1 - (double) nr / days);
  nr ++;
 }

 return nr;
}
```

Đôi khi các bài toán về xác suất có thể phức tạp. Như chúng ta đã thấy, 'Birthday Paradox' tạo cảm giác mâu thuẫn với suy nghĩ thông thường của ta. Nhưng nó lại có thể chứng minh tính đúng đắn nhờ vào các các công thức. Công thức có thể hỗ trợ, nhưng để trở nên thành thạo về xác suất bạn cần thêm một nguyên liệu nữa: "cảm giác về số học". Đây là một phần bẩm sinh, và một phần học được thông qua luyện tập. Làm [bài kiểm tra](http://teacherlink.org/content/math/interactive/probability/interactivequiz/question1/home.html) này để kiểm tra cảm giác số học của bạn cũng như đối mặt với những hiểu lầm về xác suất.

##Tính xác suất của các sự kiện lần lượt nhau
Trong phần dưới đây, chúng ta sẽ thảo luận một vài bài tập thực tế trên topcoder mà trong đó sự xảy ra của sự kiện này bị ảnh hưởng bị sự kiện trước. Chúng ta có thể nghĩ nó như một đồ thị mà trong đố mỗi nút là một sự kiện và cạnh là sự phụ thuộc giữa chúng. Có thể đây là một sự so sánh hơi ép buộc, nhưng cách chúng ta tính toán xác suất cho các sự kiện khác nhau rất giống cách chúng ta đi qua các đỉnh của đồ thị. Ta bắt đầu ở gốc, là trạng thái ban đầu và có xác suất là 1. Sau đó, ta sẽ xem xác các khả năng khác nhau kèm theo các xác suất tương ứng.

###[Nested  Randomness](http://community.topcoder.com/stat?c=problem_statement&pm=3510&rd=6527)
Bài toán này nhìn có vẻ rắc rối, nhưng khi đã nghĩ ra được cách giải, thì việc còn lại chỉ là việc vài ba dòng code. Yêu cầu đề bài có thể tóm tắt lại như sau: hàm random($N$) được gọi sẽ trả về một số nguyên ngẫu nhiên trong khoảng từ $0$ đến $N-1$, xác suất để được trả về của mỗi số là bằng $1/N$. Nếu ta dùng tất cả các kết quả có thể xảy ra làm dữ liệu nhập vào cho bước kết tiếp, chúng ta có thể xác định được tất cả các kết quả mà random(random($N$)) có thể đưa ra. Để hiểu rõ hơn, ta sẽ viết tường minh ra với $N=4$

- Sau lần gọi thứ nhất, tất cả các số nguyên có cùng một xác suất để xảy ra, $1/4$ .

- Trong lần gọi thứ hai, xác suất sẽ $1/4$ cho các hàm sau được gọi: random($0$), random($1$), random($2$), và random($3$). Gọi random($0$) sẽ báo lỗi, random($1$) trả về $0$, random($2$) trả về $0$ hoặc $1$ (từng trường hợp với xác suất $1/2$) và random($3$) trả về $0$,$1$, hoặc $2$.

- Do đó, trong lần gọi thứ ba, random($0$) sẽ có xác suất $1/4 + 1/8 + 1/12$ để được gọi, random($1$) có xác suất $1/8 + 1/12$ để được gọi và random($2$) có xác suất $1/12$ để được gọi.

- Tương tự, trong lần gọi thứ tư, hàm random($0$) sẽ có xác suất $1/4$ bị gọi, trong khi xác suất của random($1$) là $1/24$.

- Trong lần gọi thứ năm, ta chỉ thể gọi random($0$), và bị báo lỗi. Toàn bộ tiến trình được mô tả trên ảnh.

[[/uploads/translate_topcoder_understandprobabilties_02.gif]]

Code để giải bài này
```cpp
double probability (int N, int nestings, int target)
{
 int I, J, K;
 double A[1001], B[2001];
 // A[I] la xac suat de so I xuat hien

 for (I = 0; I < N ; I++)  A[I] = (double) 1 / N;
 for (K = 2; K ≤ nestings; K++)
 {
  for (I = 0; I < N; I++)  B[I] = 0;
  // voi moi I giua 0 den N-1, ta goi ham random(I)
  // theo yeu cau de bai
  for (I = 0; I < N; I++)
   for (J = 0; J < I; J++)
    B[J] +=  (double) A[I] / I;
    for (I = 0; I < N; I++)  A[I] = B[I];
 }
  return A[target];
}
```
Nếu đã nắm được ý tưởng của bài này, chắc chắn bạn sẽ muốn thử:
[ChessKnight](http://community.topcoder.com/stat?c=problem_statement&pm=3509&rd=6528), 
[DiceThrows](http://community.topcoder.com/stat?c=problem_statement&pm=4450&rd=7217),
[RockSkipping](http://community.topcoder.com/stat?c=problem_statement&pm=1954&rd=5006),
[PointSystem](http://community.topcoder.com/stat?c=problem_statement&pm=1849&rd=4675),
[VolleyBall](http://community.topcoder.com/stat?c=problem_statement&pm=2959&rd=5880)

Giờ ta sẽ đi đến một ví dụ khác, [GeneticCrossover](https://community.topcoder.com/stat?c=problem_statement&pm=2974&rd=5875), giới thiệu về **xác suất có điều kiện** (*conditional probability*). Trong này, bạn được yêu cầu dự đoán về chất lượng của một con vật, dựa trên mã gen mà chúng nhận từ bố mẹ. Dự vào mô tả đề bài, có hai trường hợp có thể xảy ra: một gen không phụ thuộc vào gen khác, hoặc gen này có phụ thuộc. 

Trường hợp thứ nhất, gọi p là xác suất mà gen này là gen trội. Có 4 trường hợp để xem xét

- Ít nhất bố hoặc mẹ có hai gen trội ( $p = 1$)

- Mỗi bố hoặc mẹ có đúng một gen trội ( $ p = 0.5 $ )

- Mỗi bố hoặc mẹ có một gen trội và người còn lại có duy nhất một gen lặn  ( $ p = 0.25 $ )

- Cả hai bố mẹ có hai gen lặn ( $ p = 0 $ )

Giờ ta sẽ xem trường hợp khi một gen phụ thuộc vào một gen khác. Điều này làm bài toán trở nên phức tạp hơn do gen “bố mẹ” có thể lại phụ thuộc vào một gen khác và cứ thế…. Để xác định được xác suất mà một gen phụ thộc là gen trội, ta sẽ kiểm tra sự kiện mỗi gen trong chuỗi (bắt đầu gen đang xé) là gen trội. Để gen hiện tại là gen trội, ta cần tất các sự kiện như vậy xảy ra. Để thực hiện được điều này, ta lấy tích của xác suất của từng sự kiện một trên chuỗi. Thuật toán thực hiện một cách đệ quy, và đây code hoàn chỉnh cho bài tập này:
```cpp
int n, d[200];
double power[200];

// here we determine the characteristic for each gene (in power[I]
// we keep the probability of gene I to be expressed dominantly)
double detchr (string p1a, string p1b, string p2a, string p2b, int nr)
{
 double p, p1, p2;
 p = p1 = p2 = 1.0;
 if (p1a[nr] ≤ 'Z')  p1 = p1 - 0.5;
 //  is a dominant gene
 if (p1b[nr] ≤ 'Z')  p1 = p1 - 0.5;
 if (p2a[nr] ≤ 'Z')  p2 = p2 - 0.5;
 if (p2b[nr] ≤ 'Z')  p2 = p2 - 0.5;
 p = 1 - p1 * p2;

 if (d[nr] != 1) power[nr] = p * detchr (p1a, p1b, p2a, p2b, d[nr]);
 // gene 'nr' is dependent on gene d[nr]
    else power[nr] = p;
 return power[nr];
}

double cross (string p1a, string p1b, string p2a, string p2b,
 vector dom, vector rec, vector dependencies)
{
  int I;
 double fitness = 0.0;

 n = rec.size();
 for (I = 0; I < n; i++) d[i] = dependencies[i];
 for (I = 0 ;I < n; I++) power[i] = -1.0;
 for (I = 0; I < n; i++)
  if (power[I] == -1.0) detchr (p1a, p1b, p2a, p2b, i);
  // we check if the dominant character of gene I has
  // not already been computed
 for (I = 0; I ≤ n; I++)
  fitness=fitness+(double) power[i]*dom[i]-(double) (1-power[i])*rec[i];
  // we compute the expected 'quality' of an animal based on the
  // probabilities of each gene to be expressed dominantly

 return fitness;
}
```
Xem thêm : [Cây xác suất](http://community.topcoder.com/stat?c=problem_statement&pm=2234&rd=4675)

##Thuật toán ngẫu nhiên

Ta gọi những thuật toán ngẫu nhiên là những thuật toán mà nó dùng số được sinh ra một cách ngẫu nhiên để đưa ra quyết định trong quá trình chạy. Không giống như những thuật toán đã xác định trước, với mỗi dữ liệu vào xác định thì sẽ cho ra duy nhất một kết quả ra cũng như thời gian chạy, thuật toán ngẫu nhiên sẽ biểu hiện khác nhau trong mỗi lần chạy. Cơ bản, ta sẽ phân biện hai loại của thuật toán ngẫu nhiên:

1. Thuật toán Monte Carlo: có thể vài lần đưa ra kết quả sai - tuy nhiên xác suất của sai sót là chấp nhật được. 

2. Thuật toán Las Vegas: luôn cho kết quả đúng, và điểm khác biệt giữa các lần chạy với cùng một dữ liệu vào là thời gian chạy - ta sẽ nghiên cứu và sự phân phối theo xác suất của thời gian chạy.

Tham khảo [tài liệu](http://www.ews.uiuc.edu/~kumar/lectures/lecture.10.3.pdf) từ College of Engineering at UIUC để xem các các thuật toán này hoạt động.

Mục tiêu chính của thuật toán ngẫu nhiêu là để xây dựng một thuật toán nhanh hơn, cũng có thể đơn giản hơn. Khả năng đơn giản hóa một vấn đề chính là một lợi ích của thuật toán ngẫu nhiên. Nên không lấy làm lạ khi các thuật toán như vậy được đưa ra nghiên cứu rộng rãi và được ứng dụng để giải quyết các vấn đề một cách đơn giản hơn.
Một câu hỏi thú vị được đưa ra là liệu những thuật toán như vậy có ích trong các kì thi lập trình hay không. Một vài bài tập có thể có nhiều cách giải tối ưu. Cách làm điển hình của các thuật toán là kiểm tra từng cái một theo thứ tự được đưa ra. Nhưng không chắc rằng các kết quả tối ưu được phân bố đồng đều trong vùng kết quả. Trong điều kiện này, các thuật toán được định nghĩa sẵn có thể không tìm được kết quả đủ nhanh, và lợi thế của thuật toán ngẫu nhiên là nó kiểm tra không theo một trình tự nhất định nào, và đặc biệt trong trường hợp những kết quả tối ưu nằm gần nhau, nó hoạt động hiệu quả hơn. Tham khảo [QueenInterference trên topcode](http://community.topcoder.com/stat?c=problem_statement&pm=2935&rd=585)

Thuật toán ngẫu nhiên cụ thể có ích khi đối mặt với những kẻ tấn công cố tình nhập dữ liệu xấu để làm khó thuật toán. Những thuật toán này thường dùng rộng rãi trong mật mã học, nhưng đôi khi cũng có ích trong các cuộc thi lập trình. Nhiều lúc thuật toán của bạn hiệu quả trong đa số hoàn cảnh, nhưng lại có các trường hợp suy biến mất nhiều thời gian để ra đáp án. Đặc biệt trên các trình chấm không cho điểm theo test mà trả kết quả theo cả bộ dữ liệu (như topcoder), dù thuật toán đúng đi nữa, thì nó còn cần phải đủ nhanh với tất cả các bộ dữ liệu; ngược lại, bạn sẽ mất toàn bộ điểm.

####”Ngẫu nhiên” có thực sự là một giải pháp?

Trong đa số công việc tối ưu, tỉ lệ giữa kết quả tối ưu và tổng số kết quả là không đáng kể. Một cách đơn giản, nhưng không thông minh cho lắm, là tạo một ví dụ khác và xem thuật toán hoạt động thế nào. Chạy thử như thế thường nhanh và có thể đưa bạn đến những manh mối để giải quyết bài toán.
```cpp
Max = 1000000; attempt = 0;
while (attempt < Max)
{
 answer = solve_random (...);
 if (better (answer, optimum))
 // we found a better solution
 {
  optimum = answer;
  cout << "Solution " << answer << " found on step " << attempt << "\n";
 }
 attempt ++;
}
```
## Bài tập rèn luyện

ND: Mình không chép lại danh sách bài tập trong bài viết gốc ở topcoder do sau này tác giả có thể chỉnh sửa hay bổ sung. Các bạn xem cuối [bài viết gốc trên topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/understanding-probabilities/) để luyện tập thêm.






