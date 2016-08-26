# Viết lời giải chiến thắng trong kì thi

Nguồn: [USACO](http://train.usaco.org/usacotext2?a=VypAlPqkC1a&S=craft)

Một cách tốt để sẵn sàng cho thi đấu là viết một chiến thuật về những gì bạn sẽ làm trong phòng thi. Điều này giúp bạn biết phải làm gì kể cả khi mọi thứ ổn và không ổn. Bằng cách này bạn có thể tiết kiệm thời gian trong phòng thi cho việc giải bài mà thay vì ngồi bối rối không biết làm gì tiếp theo... việc này có tác dụng như chuẩn bị phản ứng cho mọi tình huống.

Việc chuẩn bị tâm lý cũng không kém phần quan trọng.

## Kế hoạch tác chiến trong phòng thi
**TRƯỚC TIÊN** là đọc qua **TẤT CẢ** các bài; viết nháp thuật toán, độ phức tạp, các số, cấu trúc dữ liệu, các chi tiết hiểm,... 

* Brainstorm nhiều thuật toán nhất có thể - sau đó thì chọn cái có vẻ ngu nhất nhưng dùng được!
* **LÀM TOÁN!** (độ phức tạp không gian và thời gian, và thế vào đó những trường hợp lớn nhất có thể)
* Cố gắng chia nhỏ thuật toán - sử dụng các trường hợp đặc biệt (suy biến?).
* Sắp xếp các bài toán: việc nhẹ trước, theo độ khó của bài toán đối với bản thân(từ thấp tới cao: đã làm rồi, dễ, không quen, khó).

*Code* - lần lượt từng bài:

* Quyết định chọn thuật toán.
* Viết test hiểm.
* Viết cấu trúc dữ liệu.
* Code thủ tục input và kiểm tra ( bằng cách viết thêm một thủ tục output để show data?).
* Code thủ tục output và kiểm tra.
* *Làm rõ trong từng bước*: Viết comment miêu tả logic của thuật toán.
* Làm nó chạy được và kiểm tra tính đúng đắn (sử dụng các test cases thông thường).
* Cố gắng chứng minh lời giải của mình là sai - sử dụng các trường hợp đặc biệt.
* Dần dần tối ưu hóa - nhưng chỉ cần vừa đủ, và giữ tất cả các phiên bản (sử dụng các test khó để xác định thời gian chạy thật sự).

## Chiến thuật kiểm soát thời gian và kịch bản "khống chế thiệt hại"
Có kế hoạch cho việc phải làm gì cho những trường hợp (có thể thấy trước được) mà mọi thứ đi theo hướng không ổn; tưởng tượng những vấn đề bạn có thể gặp phải và tính toán mình sẽ phản ứng thế nào. Câu hỏi chính là *"Khi nào nên dành thêm thời gian debug, và khi nào bỏ qua để tiếp tục?"*. Xem xét những gợi ý sau:

* Bạn đã dành bao lâu để debug nó rồi?
* Bạn đang mắc phải bug kiểu gì?
* Có phải thuật toán sai không?
* Có cần thay đổi cấu trúc dữ liệu không?
* Bạn có manh mối nào về cái sai này không?
* Một khoảng thời gian ngắn (20 phút) để debug có thể tốt hơn là làm việc gì đó khác; nhưng bạn có thể sẽ giải được một bài khác trong 45 phút. 
* Khi nào thì quay lại bài đã bỏ qua trước đó, và khi nào thì đổi bài?
* Xét từ thời điểm này trở đi - quên hết những cố gắng trước đó, tập trung vào những điều phía trước: Làm thế nào bạn có thể lấy được nhiều điểm nhất trong một giờ tiếp theo với những gì bạn đang có?

Nên có một checklist cho những gì phải làm trước khi nộp bài:

    Ngừng code 5 phút trước khi hết giờ?
    *   Tắt assert.
    *   Tắt debugging output.

## Tips & Tricks
*   Duyệt trâu khi nào còn có thể.
*   *KISS* (Keep It Simple, Stupid): Đơn giản đồng nghĩa với thông minh!
*   Gợi ý: để ý đến giới hạn dữ liệu ( được viết trong đề).
*   Cứ phung phí ít bộ nhớ nếu điều đó giúp đời thanh thản hơn (nếu như có thể làm vậy).
*   Đừng xóa kết quả sai khi debug, comment nó ra.
*   Tối ưu hóa dần dần, nhưng chỉ vừa đủ là được.
*   Giữ lại tất cả phiên bản!
*   Code để debug:
    *   cách khoảng là tốt,
    *   đặt tên biến có nghĩa,
    *   làm rõ code ở từng bước,
    *   **VIẾT COMMENT TRƯỚC KHI CODE.**
*   Tránh dùng pointer (con trỏ) nếu có thể.
*   Tránh cấp phát bộ nhớ động bừa bãi: cố dùng bộ nhớ tĩnh cho mọi thứ.
*   Cố gắng không dùng số thực; nếu như phải dùng, hãy nhắm mắt cho qua (không bao giờ kiểm tra bằng nhau).
*   Lời khuyên về comments:
    *   Không dài dòng, ghi chú ngắn gọn.
    *   Chỉ dùng giải thích những phép toán ở mức cao: *++i; //tăng giá trị i...* comment này còn hơn là vô dụng
    *   Giải thích những chỗ phức tạp của code.
    *   Phân ranh giới và giải thích những phần có chức năng khác nhau.
    *   Viết cho một người đủ thông minh để hiểu bài toán nhưng không thể hiểu code.
    *   Viết tất cả những điều khiến bạn phải suy nghĩ.
    *   Tất cả những chỗ mà ít nhất một lần khiến bạn tự hỏi *"Cái đó để làm gì thế nhỉ?"*
    *   Luôn luôn comment thứ tự chỉ số của mảng.
*   Giữ một bản ghi về biểu hiện của bản thân trong mỗi contest: những thành công, những sai lầm, và bạn đã có thể làm gì để có kết quả tốt hơn; dùng nó để viết lại và cải thiện game plan của bạn!

## Độ phức tạp

### Những điều cơ bản và các kí hiệu khác
Những khái niệm nền tảng của việc đánh giá độ phức tạp xoay quanh kí hiệu *"O lớn"*, ví dụ: $O(N)$. Kí hiệu $O(N)$ có nghĩa thời gian thực hiện thuật toán hay bộ nhớ sử dụng sẽ gấp đôi khi dữ liệu được gấp đôi. Một thuật toán $O(N^2)$ sẽ chạy chậm hơn bốn lần (hoặc dùng nhiều hơn 4x không gian lưu trữ) khi dữ liệu được gấp đôi. Thuật toán có độ phức tạp hằng số về thời gian hay không gian được kí hiệu là $O(1)$. Khái niệm này được áp dụng cho cả bộ nhớ và thời gian; ở đây chúng ta sẽ tập trung bàn luận về thời gian.

Để tính toán thời gian chạy $O()$ của một chương trình, ta đánh giá các vòng lặp của nó. Vòng lặp lồng nhau nhiều nhất (do đó chạy chậm nhất) quyết định thời gian chạy và sẽ là vòng lặp duy nhất được nhắc đến khi bàn về $O()$. Một chương trình có một vòng lặp đơn và một vòng lặp lồng nhau (giả sử mỗi vòng lặp đơn được thực hiện $N$ lần) là $O(N^2)$, mặc dù còn có một vòng lặp $O(N)$.

Hiển nhiên, đệ quy cũng được xem là vòng lặp và chương trình đệ quy có độ phức tạp $O(b^N)$, $O(N!)$, hay thậm chí là $O(N^N)$.

### Rules of thumb (quy tắc ước lượng)
*   Khi phân tích thuận toán để xác định nó sẽ chạy trong bao lâu với một bộ dữ liệu cho sẵn, điều đầu tiên cần nhớ là: các máy tính hiện đại (từ 2004) có thể xử lí 100 triệu phép tính trên giây. Trong một chương trình có giới hạn thời gian 5 giây, khoảng 500 triệu phép tính có thể được thực hiện. Những chương trình được tối ưu tốt có thể thực hiện gấp đôi hay thậm chí gấp bốn lần con số đó. Những thuật toán phức tạp có thể sẽ chỉ thực hiện được một nửa số đó. Những contest gần đây thường có giới hạn thời gian 1 giây cho những bộ dữ liệu lớn.
*   Tối đa 16MB bộ nhớ
*   $2^{10}$ ~gần bằng~ $10^3$
*   Nếu bạn có $k$ vòng lặp lồng nhau, mỗi vòng lặp thực hiện $N$ lần thì chương trình có độ phức tạp $O(N^k)$.
*   Nếu chương trình của bạn đệ quy với $b$ lần gọi đệ quy ở mỗi cấp và có $l$ cấp thì chương trình có độ phức tạp $O(b^l)$.
*   Ghi nhớ rằng có $N!$ hoán vị, và $2^N$ tập con (hay tổ hợp) của $N$ phần tử khi làm việc với những thuật toán kiểu thế.
*   Độ phức tạp thời gian tốt nhất để sắp xếp $N$ phần tử là $O(N logN)$
*   **PHẢI LÀM TOÁN!** Thế số vào.

#### Ví dụ
Một vòng lặp với $N$ lần duyệt là $O(N)$:
```
sum = 0
for i = sum to n
    sum = sum + i
```
Một vòng lặp kép thường sẽ là $O(N^2)$:
```
for i = 1 to n-1
    for j = i + 1 to n
        if (a[i] > a[j])
            swap(a[i],a[j])
```
Lưu ý rằng mặc dù vòng lặp thực hiện ${N * (N+1)/2}$ lần duyệt câu lệnh ``if``, nó vẫn là $O(N^2)$ vì gấp đô i $N$ vẫn làm gấp bốn lần thời gian thực hiện.

Xét một cây nhị phân cân bằng 4 levels:

![cay-nhi-phan-can-bang-4-cap](https://s-media-cache-ak0.pinimg.com/564x/88/81/a1/8881a15ab475ed5adf771592871565a5.jpg)

Một thuật toán tìm kiếm trên một cây nhị phân thông thường sẽ có độ phức tạp $O(2^N)$.

## Các phương pháp tạo lập lời giải

### Tạo vs. Lọc
Các chương trình tạo ra nhiều kết quả có thể có và sau đó chọn ra những kết quả đúng (tưởng tượng 1 lời giải bài 8 quân hậu) chính là *lọc*. Những lời giải mà được tạo ra mà không cần thử sai chính là *tạo*. Nhìn chung, những bộ lọc dễ code hơn và chạy chậm hơn. Thử làm tính để xem nếu một bộ lọc là đủ tốt hay bạn phải thử tìm ra một bộ tạo.

### Tính Trước
Đôi khi sẽ thuận tiện nếu tạo một bảng hoặc cấu trúc dữ liệu khác cho phép tìm kiếm kết quả đã tính một cách nhanh nhất. Điều này gọi là *tính trước* (và sẽ phải đổi bộ nhớ để lấy thời gian). Có thể tính trước dữ liệu rồi đặt vào chương trình, sau đó gọi khi chương trình chạy, hoặc có thể lưu kết quả trong khi tính. *Ví dụ:*  một chương trình chuyển các kí tự từ chữ in hoa sao chữ thường có thể thực hiện một phép tìm kiếm trên bảng rất nhanh mà không cần điều kiện nào. Các bài toán trong cuộc thi thường sử dụng số nguyên tố - nhiều khi việc tạo ra một danh sách các số nguyên tố để sử dụng sau là một việc làm thực tế.

### Chia Nhỏ (Điều Khó Nhất Trong Các Kì Thi)
Dù có dưới 20 thuật toán cơ bản dùng trong các kì thì lập trình, thử thách của những bài toán yêu cầu kết hợp hai thuật toán để giải lại cực kì đáng sợ. Thử tách những chỉ dẫn của bài toán thành những phần khác nhau để có thể kết hợp một thuật toán với một vòng lặp hoặc với một thuật toán khác và giải độc lập những phần khác nhau của bài toán. Lưu ý rằng đôi khi bạn có thể sử dụng cùng một thuật toán hai lần để giải những phần khác nhau của dữ liệu (một cách độc lập) nhằm cải tiến thời gian chạy.

### Tính Đối Xứng
Nhiều bài toán có tính đối xứng (ví dụ: khoảng các giữa hai điểm thông thường là như nhau theo hai chiều). Tính đối xứng có thể là 2 chiều, 4 chiều, 8 chiều, và hơn thế nữa. Cố gắng tận dụng tính đối xứng để rút ngắn thời gian chạy.
Một ví dụ cụ thể, với tính đối xứng 4 chiều, bạn chỉ cần giải $1/4$ bài toán và viết ra 4 kết quả đối xứng từ một đáp án duy nhất (cẩn thận với trường hợp tự đối xứng, hiển nhiên chỉ cần in ra một hay hai lần).

### Xuôi vs. Ngược
Điều bất ngờ là nhiều bài toán khi được giải ngược sẽ tốt hơn nhiều so với kiểu tiếp cận xuôi. Để ý việc xử lý dữ liệu theo thứ tự ngược hay xây dựng một các tiếp cận mà dữ liệu được nhìn theo thứ tự hay kiểu hình khác với điều dễ thấy.

### Giản Lược Hóa
Một số bài toán có thể được phát biểu lại thành một bài toán mới mà bạn có thể đã gặp rồi hay có thể dễ dàng tìm lời giải hơn so với bài toán gốc; đương nhiên bạn chỉ nên giải bài toán dễ hơn thôi. Một trường hợp khác, tương tự phép quy nạp, một số bài toán chỉ cần thay đổi một chút lời giải của bài toán nhỏ hơn để có thể giải được cả bài toán lớn.

