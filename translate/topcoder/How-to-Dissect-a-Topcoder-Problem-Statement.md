# How to Dissect a Topcoder Problem Statement #

##### Bài viết bởi: [antimatter](https://www.topcoder.com/member-profile/antimatter) #####

Nguồn: [Top Coder](https://www.topcoder.com/community/data-science/data-science-tutorials/how-to-dissect-a-topcoder-problem-statement/)

Đã bao nhiêu lần bạn đăng kí SRM (Single Round Matches), vào phòng khi hệ thống báo, và khi bắt đầu, bạn mở 250... và thấy cực khó hiểu.

Có thể điều ấy chưa bao giờ xảy ra với bạn. Bạn có thể may mắn, hoặc bạn đã là một người thành thục. Tuy nhiên, rất nhiều người đầy kinh nghiệm (vâng, cả nick đỏ) có thể kết thúc trong việc ngồi nhìn bài toán trong một khoảng thời gian dài. Vấn đề này rõ là nghiêm trọng. Làm sao bạn có thể giải bài khi không có bất cứ ý tưởng nào về việc mình đang làm chứ?

May mắn thay, các bài toán trên Topcoder được viết theo một cách đặc biệt. 

Biết được hướng làm của mình quanh các chủ đề khác nhau sẽ giúp bạn hiểu rõ nội dung của bài toán hơn.

### Các mục của đề bài ###

Hãy nhìn vào các thành phần của một bài toán tiêu biểu trê Topcoder. Đầu tiên là phần giới thiệu. Thường thì một đề bài được dẫn dắt bởi mô tả khó hiểu về một tình huống. Phần mô tả này có thể liên quan đến các ý tưởng thực tế hay những tình huống hoặc chỉ là một câu chuyện giả tưởng, để phục vụ cho một vài kì thi. Với đa số bài toán câu chuyện đằng sau nó thường không quan trọng trong việc hiểu bài toán đó.

Tiếp tiếp là mục định nghĩa hàm. Bài toán cho bạn thấy sườn của lời giải mà bạn phải viết : tên class, tên hàm, và kiểu dữ liệu trả về, theo bỏi hàm hoàn chỉnh của bài. Ở mức thấp nhất, bạn cần khai báo một class với tên cho trước, chứa hàm phù hợp với hàm đã cho. Các cú pháp được cho sẽ luôn đúng với loại ngôn ngữ lập trình bạn chọn. 

Đôi lúc lời chú giải sẽ đi theo định nghĩa của hàm. Đó sẽ là những điều quan trọng mà bạn nên nhớ, hoặc đôi khi là một thông tin ngoài lề mà bạn chưa biết tới khi đọc bài này. Nếu có mục chú giải, bạn nên chắc chắn là sẽ đọc nó - nó thường chứa những thông tin cực kì quan trọng.

Mục điều kiện ràng buộc luôn quan trọng nhất. Nó sẽ liệt kê ràng buộc dữ liệu trong Input. Việc này giúp bạn biết rõ về các thông tin quan trọng ví dụ như bao nhiêu bộ nhớ được cấp phát hoặc độ phức tạp thuật toán phải là bao nhiêu.

Và cuối cùng, ta có một set các ví dụ. Những bài toán này có input mẫu để test bài của các bạn. Những dữ liệu cho theo đúng trình tự đề cập, tiếp đến là kết quả và, có thể, là lời giải thích của trường hợp test. 
	
* **Giới thiệu**

	Đề bài thường bắt đầu bằng việc trình bày về bài toán. Nó cung cấp cho bạn một tình huống hoặc một bối cảnh, trước khi được chia thành các phần khó khăn. Thường thì điều này không liên quan nên cứ không quan tâm đến nó nếu cần thiết. Trong một vài trường hợp, việc trình bày có thể dẫn tới các câu không rõ nghĩa nếu nó ràng buộc với nhau - như [MatchMaking](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2911)(SRM 203 Div I Easy / Div II Medium). Bạn cũng nên chú ý rằng với một vài bài toán đơn giản, mở đầu bối cảnh có thể được bỏ qua.

	Các phần còn lại của mục này thường đa dạng từ bài toán này đến bài toán khác, dựa trên phong cách viết của người ra đề.

	Đề sẽ có mô tả về những gì bạn cần làm, trong các bài high-level. Ví dụ như, [UserName](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2913)(SRM 203, Div 2 easy). Yêu cầu của đề bài là cần bạn tìm biến thể đầu tiên của các username cho trước mà chưa được lấy. Để ý rằng bài toán chưa đề cập tới tên hay kiểu biến số, hoặc cấu trúc của input.

	Đề bài cũng sẽ có một mô tả sơ về input. Ở mức thấp, kiểu và tên biến số trong input sẽ được cung cấp, cũng như mối liên hệ và ý nghĩa của chúng. Đôi khi nhiều thông tin về input được cung cấp; điều này chỉ xảy ra với cái bài toán phức tạp.

	Đôi lúc, nhiều thông tin nền cần được cung cấp. Thường thì ở mục này, hoặc đôi khi trong mục Lưu ý.
	
* **Phần định nghĩa**

	Đây là phần chính về mô tả công việc mà topcoder cần bạn làm. Nó cho bạn tên lớp bài toán, phương thức đối với lớp bài toán đó, biến số nên chọn, kết quả trả về, và tên phương thức giải. Như đã đề cập trước đây, cấu trúc cơ bản để sumbit cần viết một class trong đó chứa hàm như yêu cầu đề bài. Cần phải đảm bảo class đó  khai báo public nếu bạn không dùng C++, và hàm cũng khai báo public như trên. 

* **Phần lưu ý và các ràng buộc**

	Phần lưu ý thường không xuất hiện. Nhưng nếu có, HÃY ĐỌC NÓ! Thông thường thì nó sẽ highlight các vấn đề có thể xuất hiện khi đang chạy test, hoặc cung cấp thông tin nền mà bạn có thể chưa biết trước đây. Mục ràng buộc sẽ đưa một list các giới hạn về dữ liệu input. Mục sẽ bao gồm giới hạn của chuỗi, mảng, hoặc là các ký tự, và giá trị của các số. Mục này được check tự động, nên không cần phải lo lắng về việc viết một đoạn code kiểm tra dữ liệu nhập vào. 

	Cẩn thận các giới hạn. Đôi khi nó sẽ giúp bạn tìm ra thuật toán chính xác, hoặc là làm giảm độ khó cho các thuật toán không hiệu quả bằng để chạy đúng thời gian. Sẽ có một sự khác biệt rất lớn giữa input gồm 50 số và 5 số, cả hai đều quan trọng với solution sẽ pass, và dễ hơn cho việc viết code.

* **Các ví dụ**
 
	Mục này là danh sách các test sẽ chống lại lời giải của bạn. Nó cho input (theo đúng quy định) và đáp án, và đôi khi có thêm lời giải thích về test khi cần thiết.

	Nó không thông báo rằng bạn nên test code bạn với tất cả test ví dụ, ít nhất là vậy. Và sẽ có những test thâm độc, hoặc dữ liệu lớn, và đôi khi là những test mà bạn sẽ chẳng bao giờ nghĩ tới khi viết code; sửa các lỗi trước khi bạn sumbit là nên nhất để lời giải của bạn vượt qua hoặc dù nó fail khi đang test. 

	Các ví dụ này không phải lúc nào cũng bao quát! Cẩn thận, đối với một vài bài toán, vượt qua các test ví dụ là gần như vượtqua tất cả các test.

	Đối với các ví dụ khác, dù sao, nó vẫn cố tình (hoặc không) đưa ra các test mà bạn nên biết. Nếu bạn không chắc chắn code bạn đúng, hãy test nhiều, và nghĩ ra các test của chính bạn. Bạn có thể dùng đến nó trong phần challenge.

### Giải một bài toán ###
Bây giờ chúng ta sẽ thử một bài toán, phân tích nó, từng bước một.

Hãy nhìn sơ qua [BettingMoney](http://community.topcoder.com/tc?module=ProblemDetail&rd=4775&pm=2297), vòng SRM 191 Div 2 Easy. Đầu tiên ta phân ra các phần của một bài toán. Trong chính nó, ta có tình huống sau bài toán - đánh bạc. Tiếp theo chúng ta có một chút thông tin nền về việc chính nó cá cược lại. Chúng ta lại có một mô tả về input - các dạng dữ liệu, kiểu biến, và những đại lượng nó đại điện. Sau đó chúng ta có yêu cầu : xác định mạng lưới nhận được gì cho ngày và trả về theo cent.

Cũng chú ý đến hai đoạn giải thích ở cuối bài toán; phần đầu cung cấp một ví dụ của test, và phần thứ hai là một test hoàn chỉnh, cực kì giúp ích cho bạn trong việc hiểu đề bài.

Mục định nghĩa không có gì lôi cuốn, chỉ ở đó để đầy đủ.

Các lưu ý trong bài này rõ ràng bao quát. Trong các phần thông tin nền, bạn có thể sẽ không biết rằng 100 cent = 1 dollar. Và để cho việc làm rõ hơn, thông tin rõ ràng cho thấy kết quả có thể là số âm, và lề của chiến thắng (là cái biến trả về cuối cùng) là tất cả những gì ta cần quan tâm khi quyết định trả tiền.

Các giới hạn được đề cập rõ ràng. Phần input mảng sẽ gồm đúng số phần tử, giữa 1 và 50. (50 là một con số khá lớn đối với truyền thống của topcoder với input). Kết quả cuối cùng sẽ giữa 0 và cùng với kích thước là số âm (nghĩa là,  bạn có một suy nghĩ, rằng ai đo sẽ thắng phần cá cược). Mỗi phần tử của mảng nằm trong khoảng 0 và 5000. Điều này để chắc chắn kiểu dữ liệu integer sẽ đủ để đảm nhiệm.

Cuối cùng, là phần ví dụ. Thường thì đề bài sẽ bao gồm một ví dụ test cùng chú giải, là test số 0. Sau đó là các test khác có chú giải hoặc không. Ta cũng cần lưu ý rằng một test ví dụ có kết quả là số âm, để bổ sung cho phần lưu ý.

### Một bài toán phức tạp hơn ###
Bây giờ hãy nhìn qua [Poetry](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1835), vòng SRM 170 Div 2 Hard. Đối với bài toán này, bạn có thể không thực sự giải được trong thời gian cho phép. Việc này là bình thường - nhấn mạnh rằng bạn cần hiểu đề bài nói gì, dù bạn không thể code nó đúng giờ.

Mục đầu tiên cho bạn biết ngay về việc bạn cần làm - bạn được cho một bài thơ, và bạn phải xác định về kế hoạch gieo vần. Phần còn lại của mục này làm rõ hơn việc đó thật sự là gì, từ dưới lên (từ bài cơ bản đến các bài phức tạp). Nó cho bạn khái niệm một từ hợp pháp là sao và làm sao để lấy từ từ bài thơ, sau đó là về ý nghĩa hai vần - mà phần đuôi nó bằng nhau. Phần đuôi lại được định nghĩa là gì. Sau tất cả, chúng ta tìm ra ý nghĩa về hai dòng trong thơ: từ cuối của chúng nó phải vần với nhau. Cuối cùng, (whew!) chúng ta được biết sao để xây dựng một kế hoạch vần và cấu trúc của kết quả trả về ra sao.

Đây là một bài toán mà nhiều việc cần được định nghĩa trước khi vào trọng tâm của bài, và mỗi khái niệm đều đáng đọc qua ít nhất vài lần, dù bạn không rõ sao chúng nó phù hợp với nhau.

Phần tiếp theo là phần định nghĩa của bài, chỉ để tham khảo. Sau đó là một dòng lưu ý về một điểm có thể bị bỏ qua: một dòng trắng sẽ được dánh dấu là một khoảng cách trong kế hoạch gieo vần.

Phần ràng buộc khá cơ bản như các bài toán topcoder khác: sẽ có từ 1 đến 50 dòng trong bài thơ, mỗi dòng từ 0 tới 50 kí tự. Chỉ khoảng cách và các chữ cái được cho phép, và chỉ có một từ hợp pháp trong bài.

Cuối cùng là một vài ví dụ. Thường, các bài toán thường đánh đố hoặc có một đề bài phức tạp cùng nhiều ví dụ hơn, để làm rõ ít nhất một vài điểm trong đề bài. Nhắc lại, điều này không có nghĩa rằng bạn đúng các test đấy là tương đương bạn có một bài giải đầy đủ và hoàn toàn chính xác, nhưng nó sẽ có cơ hội cao hơn để tìm các lỗi nếu có nhiều ví dụ bạn biết kết quả.

### Try It Yourself ###
Đây là danh sách các bài toán tương tự, được xếp thành các nhóm theo độ khó hiểu. Hãy tự làm trong phòng Arena Practice Rooms. Ngay cả việc bạn không thể giải chúng, ít nhất bạn có thể tìm ra bài toán muốn bạn làm gì khi phân chia thành các phần khác nhau.

### Đề cập đến trong bài viết này ###
- SRM 203 Div 2 Easy - [UserName](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2913)
- SRM 191 Div 2 Easy - [BettingMoney](http://community.topcoder.com/tc?module=ProblemDetail&rd=4775&pm=2297)
- SRM 203 Div 1 Easy - [MatchMaking](http://community.topcoder.com/tc?module=ProblemDetail&rd=5849&pm=2911)
- SRM 170 Div 2 Hard - [Poetry](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1835)

### Các bài tương tự ###
- SRM 146 Div 2 Easy – [Yahtzee](http://community.topcoder.com/tc?module=ProblemDetail&rd=4535&pm=1692)
- SRM 200 Div 2 Easy – [NoOrderOfOperations](http://community.topcoder.com/tc?module=ProblemDetail&rd=5075&pm=2868)
- SRM 185 Div 2 Easy – [PassingGrade](http://community.topcoder.com/tc?module=ProblemDetail&rd=4745&pm=1962)
- SRM 155 Div 2 Easy – [Quipu](http://community.topcoder.com/tc?module=ProblemDetail&rd=4580&pm=1686)
- SRM 147 Div 2 Easy – [CCipher](http://community.topcoder.com/tc?module=ProblemDetail&rd=4540&pm=1667)
- SRM 208 Div 1 Easy – [TallPeople](http://community.topcoder.com/tc?module=ProblemDetail&rd=5854&pm=2923)
- SRM 173 Div 1 Easy – [WordForm](http://community.topcoder.com/tc?module=ProblemDetail&rd=4670&pm=2002)
- SRM 162 Div 1 Easy – [PaperFold](http://community.topcoder.com/tc?module=ProblemDetail&rd=4615&pm=1846)

### Các bài khó hơn ###
- SRM 197 Div 2 Hard – [QuickSums](http://community.topcoder.com/tc?module=ProblemDetail&rd=5072&pm=2829)
- SRM 158 Div 1 Hard – [Jumper](http://community.topcoder.com/tc?module=ProblemDetail&rd=4598&pm=1157)
- SRM 170 Div 1 Easy – [RecurrenceRelation](http://community.topcoder.com/tc?module=ProblemDetail&rd=4655&pm=1915)
- SRM 177 Div 1 Easy – [TickTick](http://community.topcoder.com/tc?module=ProblemDetail&rd=4690&pm=1609)
- SRM 169 Div 2 Hard – [Twain](http://community.topcoder.com/tc?module=ProblemDetail&rd=4650&pm=1876)
- SRM 155 Div 1 Med – [QuipuReader](http://community.topcoder.com/tc?module=ProblemDetail&rd=4580&pm=1694)