# Kĩ năng đọc đề Topcoder

**Tác giả**: [antimatter](https://www.topcoder.com/member-profile/antimatter)

**Nguồn**: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/how-to-dissect-a-topcoder-problem-statement/)

# Về Topcoder

[Topcoder](https://topcoder.com) là một trang web tổ chức các kỳ thi thuật toán lâu đời và có uy tín nhất. Với hàng nghìn đề bài từ các kỳ thi đã diễn ra, Topcoder là một nguồn để luyện tập rất hiệu quả.

Bạn có thể vào [Web Arena](https://arena.topcoder.com) để tìm các bài cũ của Topcoder và làm bài.

# Giới thiệu

Đã bao nhiêu lần bạn đăng kí SRM (Topcoder Single Round Matches), vào phòng thi khi hệ thống báo, và khi bắt đầu, bạn mở 250... và thấy cực khó hiểu.

Có thể điều ấy chưa bao giờ xảy ra với bạn. Bạn có thể may mắn, hoặc bạn đã có kĩ năng đọc đề vô địch. Tuy nhiên, rất nhiều người đầy kinh nghiệm (vâng, cả nick đỏ) có thể bó tay ngồi nhìn đề mà không hiểu gì. Vấn đề này rõ là nghiêm trọng. Làm sao bạn có thể giải bài khi không có bất cứ ý tưởng nào về việc mình đang làm chứ?

May mắn thay, các bài toán trên Topcoder được viết theo một cách đặc biệt.

Biết được hướng làm của mình quanh các chủ đề khác nhau sẽ giúp bạn hiểu rõ nội dung của bài toán hơn.

## Các mục của đề bài

### Mục đề bài (Problem Statement)

Đề bài thường bắt đầu bằng việc trình bày về bài toán, thông qua một câu chuyện thực tế hoặc một câu chuyện mà tác giả tưởng tượng ra. Thường thì ta có thể bỏ qua những chi tiết rườm rà đó. Nhưng không phải lúc nào ta cũng có thể bỏ qua những câu chuyện đó vì nó có thể có liên quan rất chặt chẽ, ví dụ như trong bài [MatchMaking](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2911)(SRM 203 Div I Easy / Div II Medium).

Mục này thường đa dạng từ bài toán này đến bài toán khác, dựa trên phong cách viết của người ra đề. Đề bài cũng có thể chứa thêm nhiều thứ như:

- Mô tả về những gì bạn cần làm một cách tổng quan. Ví dụ như, [UserName](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2913)(SRM 203, Div 2 easy). Yêu cầu của đề bài là cần bạn tìm biến thể đầu tiên của các username cho trước mà chưa được lấy. Để ý rằng bài toán chưa đề cập tới tên hay kiểu biến số, hoặc cấu trúc của input.

- Mô tả sơ về input, ví dụ như kiểu và tên biến trong input, cũng như mối liên hệ và ý nghĩa của chúng.

### Định nghĩa hàm (Definition)

Tiếp đến là phần địch nghĩa hàm. Đây là phần đặc biệt chỉ có trong các đề Topcoder. Ví dụ:

```
Definition

Class:             QuipuReader
Method:            readKnots
Parameters:        String[]
Returns:           int[]
Method signature:  int[] readKnots(String[] knots)
(be sure your method is public)

```

Để nộp bài lên Topcoder, bạn không cần viết chương trình đầy đủ, mà chỉ cần viết 1 class, trong đó có 1 public method. Kiểu dữ liệu trả về và định nghĩa của hàm phải đúng theo yêu cầu của đề bài. Chú ý là khác với hầu hết các trang web khác, bạn không cần phải đọc input / viết output.

Ví dụ:

**Java**

```java
public class QuipuReader {
    public int[] readKnots(String[] knots) {
        // code
    }
}
```

**C++**

```cpp
class QuipuReader {
public:
vector<int> readKnots(vector<string> knots) {
    // code
}
```

Chú ý rằng phần định nghĩa hàm sẽ phụ thuộc vào ngôn ngữ mặc định của bạn.

### Phần chú giải (Notes)

Phần lưu ý không phải lúc nào cũng xuất hiện. Nhưng nếu có, HÃY ĐỌC NÓ! Thông thường thì nó sẽ nhấn mạnh các trường hợp hiểm, hoặc cung cấp thêm những thông tin mà có thể chưa được nhắc tới trong phần Đề bài.

### Điều kiện rằng buộc (Constraints)

Mục điều kiện ràng buộc luôn quan trọng nhất. Nó sẽ liệt kê ràng buộc dữ liệu trong Input. Việc này giúp bạn biết rõ về các thông tin quan trọng ví dụ như bao nhiêu bộ nhớ được cấp phát hoặc độ phức tạp thuật toán phải là bao nhiêu.

Cẩn thận các giới hạn. Đôi khi nó sẽ giúp bạn tìm ra thuật toán chính xác, hoặc là làm giảm độ khó cho các thuật toán không hiệu quả bằng để chạy đúng thời gian. Sẽ có một sự khác biệt rất lớn giữa input gồm 50 số và 5 số, cả hai đều quan trọng với solution sẽ pass, và dễ hơn cho việc viết code.

### Ví dụ (Examples)

Mục này là danh sách các test bạn có thể chạy thử. Nó cho input (theo đúng quy định) và đáp án, và đôi khi có thêm lời giải thích về test khi cần thiết.

Thông thường bạn nên test code của mình với tất cả các test ví dụ. Trong đó thường sẽ có những test hiểm, những trường hợp mà có thể bạn chưa từng nghĩ đến, và một test ngẫu nhiên lớn. Chú ý rằng để được điểm của bài sau khi kỳ thi kết thúc, code của bạn phải chạy đúng với tất cả các test được Topcoder chuẩn bị từ trước (thường số test có thể là 100 - 200).

Các ví dụ này không phải lúc nào cũng bao quát hết trường hợp! Code bạn chạy đúng với các test ví dụ không có nghĩa là nó đúng. Vì vậy hãy test nhiều, và nghĩ ra các test của chính bạn. Chú ý rằng sau **Coding Phase**, Topcoder còn có phần **Challenge Phase** - bạn có thể dùng các test của bạn để bắt lỗi sai trong code người khác và được thêm điểm.


# Bài toán ví dụ

Bây giờ chúng ta sẽ thử một bài toán, phân tích nó, từng bước một.

Hãy đọc đề [BettingMoney](http://community.topcoder.com/tc?module=ProblemDetail&rd=4775&pm=2297), vòng SRM 191 Div 2 Easy. Đầu tiên ta phân ra các phần của đề bài. Bài toán nói về chủ đề đánh bạc và một số thông tin về nó. Chúng ta lại có một mô tả về input - các dạng dữ liệu, kiểu biến, và những đại lượng nó đại điện. Sau đó chúng ta có yêu cầu: xác định lãi tối đa của 1 ngày.

Chú ý hai đoạn giải thích ở cuối bài toán: đoạn đầu cung cấp một ví dụ của test, và đoạn thứ hai là một test hoàn chỉnh, cực kì giúp ích cho bạn trong việc hiểu đề bài.

Phần chú giải trong bài này cung cấp thêm nhiều thông tin:

- Trong các phần đề bài, bạn có thể sẽ không biết rằng 100 cent = 1 dollar.
- Kết quả có thể là số âm
- Tiền lãi thu được là tất cả những gì ta cần quan tâm khi đặt cược.

Các giới hạn được đề cập rõ ràng. Phần input mảng sẽ gồm đúng số phần tử, giữa 1 và 50. (50 là một con số khá lớn đối với truyền thống của topcoder với input). Kết quả cuối cùng sẽ giữa 0 và cùng với kích thước là số âm (nghĩa là,  bạn có một suy nghĩ, rằng ai đo sẽ thắng phần cá cược). Mỗi phần tử của mảng nằm trong khoảng 0 và 5000. Điều này để chắc chắn kiểu dữ liệu integer sẽ đủ để giải quyết bài toán.

Cuối cùng, là phần ví dụ. Thường thì đề bài sẽ bao gồm một ví dụ test cùng chú giải, là test số 0. Sau đó là các test khác có chú giải hoặc không. Ta cũng cần lưu ý rằng một test ví dụ có kết quả là số âm, để bổ sung cho phần lưu ý.

# Một bài toán phức tạp hơn

Bây giờ hãy nhìn qua [Poetry](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1835), vòng SRM 170 Div 2 Hard. Đối với bài toán này, bạn rất khó để giải được trong thời gian cho phép, nhưng chúng ta hãy cùng thử nghiên cứu đề bài.

Mục đầu tiên cho bạn biết ngay về việc bạn cần làm - bạn được cho một bài thơ, và bạn phải xác định về cách gieo vần. Phần còn lại của mục này làm rõ hơn về các cách gieo vần.

Đây là một bài toán mà có rất nhiều định nghĩa, và với mỗi định nghĩa bạn nên đọc qua ít nhất vài lần, để có thể hiểu rõ được mỗi liên hệ giữa chúng.

Sau đó là một dòng lưu ý về một điểm có thể bị bỏ qua: một dòng trắng sẽ được dánh dấu là một khoảng cách trong cách gieo vần.

Phần ràng buộc khá cơ bản như các bài toán topcoder khác: sẽ có từ 1 đến 50 dòng trong bài thơ, mỗi dòng từ 0 tới 50 kí tự. Chỉ khoảng cách và các chữ cái được cho phép, và chỉ có một từ hợp pháp trong bài.

Cuối cùng là một vài ví dụ. Thường, các bài toán thường đánh đố hoặc có một đề bài phức tạp cùng nhiều ví dụ hơn, để làm rõ ít nhất một vài điểm trong đề bài. Nhắc lại, điều này không có nghĩa rằng bạn đúng các test đấy là tương đương bạn có một bài giải đầy đủ và hoàn toàn chính xác, nhưng nó sẽ có cơ hội cao hơn để tìm các lỗi nếu có nhiều ví dụ bạn biết kết quả.

# Bài tập luyện tập

Đây là danh sách các bài toán tương tự, được xếp thành các nhóm theo độ khó hiểu. Hãy tự làm trong phòng Arena Practice Rooms. Ngay cả việc bạn không thể giải chúng, ít nhất bạn có thể tìm ra bài toán muốn bạn làm gì khi phân chia thành các phần khác nhau.

## Đề cập đến trong bài viết này

- SRM 203 Div 2 Easy - [UserName](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2913)
- SRM 191 Div 2 Easy - [BettingMoney](http://community.topcoder.com/tc?module=ProblemDetail&rd=4775&pm=2297)
- SRM 203 Div 1 Easy - [MatchMaking](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2911)
- SRM 170 Div 2 Hard - [Poetry](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1835)

## Các bài tương tự

- SRM 146 Div 2 Easy – [Yahtzee](http://community.topcoder.com/tc?module=ProblemDetail&rd=4535&pm=1692)
- SRM 200 Div 2 Easy – [NoOrderOfOperations](http://community.topcoder.com/tc?module=ProblemDetail&rd=5075&pm=2868)
- SRM 185 Div 2 Easy – [PassingGrade](http://community.topcoder.com/tc?module=ProblemDetail&rd=4745&pm=1962)
- SRM 155 Div 2 Easy – [Quipu](http://community.topcoder.com/tc?module=ProblemDetail&rd=4580&pm=1686)
- SRM 147 Div 2 Easy – [CCipher](http://community.topcoder.com/tc?module=ProblemDetail&rd=4540&pm=1667)
- SRM 208 Div 1 Easy – [TallPeople](http://community.topcoder.com/tc?module=ProblemDetail&rd=5854&pm=2923)
- SRM 173 Div 1 Easy – [WordForm](http://community.topcoder.com/tc?module=ProblemDetail&rd=4670&pm=2002)
- SRM 162 Div 1 Easy – [PaperFold](http://community.topcoder.com/tc?module=ProblemDetail&rd=4615&pm=1846)

## Các bài khó hơn

- SRM 197 Div 2 Hard – [QuickSums](http://community.topcoder.com/tc?module=ProblemDetail&rd=5072&pm=2829)
- SRM 158 Div 1 Hard – [Jumper](http://community.topcoder.com/tc?module=ProblemDetail&rd=4598&pm=1157)
- SRM 170 Div 1 Easy – [RecurrenceRelation](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1915)
- SRM 177 Div 1 Easy – [TickTick](http://community.topcoder.com/tc?module=ProblemDetail&rd=4690&pm=1609)
- SRM 169 Div 2 Hard – [Twain](http://community.topcoder.com/tc?module=ProblemDetail&rd=4650&pm=1876)
- SRM 155 Div 1 Med – [QuipuReader](http://community.topcoder.com/tc?module=ProblemDetail&rd=4580&pm=1694)
