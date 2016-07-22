# Cách tiếp cận những bài toán trên Topcoder : Phần 1

Bài viết bởi [leadhyena_inran](https://www.topcoder.com/members/leadhyena_inran/). Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/planning-an-approach-to-a-topcoder-problem-part-1/) 

Việc tìm ra những cách tiếp cận bài toán là một nghệ thuật, nó có thể gây khó khăn cho cả những coder kì cựu nhất cũng như những người mới vào. Để tìm ra cách giải phù hợp, chúng ta phải dùng tổ hợp nhiều phép tính toán, đệ quy, cũng như cảm nhận bằng trực giác, bằng sự sáng tạo và thậm chí là may mắn. Cảm giác bất lực trước những bài khó thường làm chúng ta nản chí, và có thể bỏ cuộc giữa chừng. Tuy nhiên, nếu có gắng thì mọi việc đều có thể thực hiện được. Bởi lí do đó, bài hướng dẫn này sẽ đưa ra những kĩ năng để giúp các bạn chọn những hướng tiếp cận rõ ràng cho những bài toán như vậy.

## Tư duy theo lối mòn (Pattern Mining and Wrong Mindset)
Chúng ta rất dễ hướng các suy nghĩ vào việc tìm giải thuật dựa trên từng dạng của đề bài. Với những người đã làm khá nhiều bài tập, họ sẽ nhận ra được dạng của những bài toán khác nhau, và khi đọc thấy một bài toán nào đó quen thuộc, thì suy nghĩ hiện ra ngay tức khắc trong đầu là : “Ồ, đây là dạng bài X, nên sử dụng thuật toán này, áp dụng kĩ thuật này”. Cách này khá hữu ích đối với những người hay tham gia các cuộc thi hàng tuần như Single Round Matches. Hoặc nếu chưa thể giải được, thì họ sẽ tập trung vào luyện tập với những dạng đề bài này để khiến nó trở  thành một dạng bài quen thuộc.

Tuy nhiên, cách tiếp cận này cũng có nhược điểm khá lớn. Có những lúc ta sẽ nhận dạng sai dạng bài (tệ hơn là ta nhận ra điều đó khi đã code hoàn chỉnh), hay bị ảnh hưởng bởi việc không thể tìm được sự tương đương với các bài đã làm trước đây, dẫn đến việc bị bế tắc. Có những trường hợp mà những coder có kinh nghiệm vẫn không giải được những bài toán cơ bản bởi vì họ bị ảnh hưởng bởi cách tiếp cận này.

Tư duy lối mòn khuyến khích suy nghĩ “biết tuốt mọi thứ”, trong khi đều này trong thực tế là không thể. Hãy đừng quan tâm quá nhiều những gì bạn đã học và bằng cách học lại những kĩ năng tư duy cần thiết để tiếp cận một bài toán, thì rating của bạn sẽ có thể tăng lên đáng kể.

## Coding Kata
Đây là thử thách đầu tiên: hãy chọn bất cứ bài tập nào trong Practice Rooms mà bạn chưa làm. Hốt nó, cho dù phải mất bao nhiêu thời gian, và hoàn thành nó (có thể sử dụng editorial nếu không còn tìm ra được hướng đi nào nữa). Sau khi làm xong (accepted), hãy xem bạn mất bao nhiêu thời gian để giải. Tiếp theo, xóa hết code và **gõ** lại lần nữa, check thời gian sau khi làm xong. Tiếp tục lần thứ 3 như thế.

Thời gian hoàn thành lần đầu tiên là thời gian để giải bài toán khi bạn không có bất cứ hướng suy nghĩ hay cách tiếp cận nào về bài toán. Thời gian hoàn thành lần thứ 2 là thời gian lần đầu tiên trừ đi thời gian bạn dùng để đọc và hiểu đề (đừng quá ngạc nhiên với số lỗi bạn lặp lại ở lần này). Còn thời gian hoàn thành lần cuối là thời gian bạn có thể giải được trong lúc thi thật nếu tìm thấy được cách tiếp cận đúng ngay sau khi đọc đề bài. Việc giải bài với thời gian của lần cuối cùng hoàn toàn có thể làm được (thậm chí không cần khả năng gõ phím nhanh). Nhưng điều mà bạn cũng nhận ra ở lần giải thứ 3 là cảm giác bạn đã biết trước chiến thuật, nên code thế nào, dễ bị bug nhất ở những đoạn nào, …. Đó là cảm giác để có được một cách tiếp cận đúng.

Người ta thường gọi những cuộc tập trận là kata khi nó diễn ra theo đúng kịch bản, thường là giả vờ phòng thủ trước kẻ địch. Cách luyện tập này có vẻ không có hiệu quả gì mấy, bởi vì nó không giống như môi trường chiến tranh thực sự. Hơn thế nữa, cách làm này dường như đang khuyến khích cách tư duy theo lối mòn như đã nói ở trên. Nhưng thật ra, chỉ sau khi code lại một bài 3 lần trong một khoảng thời gian liên tục mới có thể thấy được lợi ích của nó. Kata luyện cho người ta những kinh nghiệm lên kế hoạch, tinh thần kỷ luật, cách code, debug và submit hiệu quả.

## Chiến thuật định hướng giải bài(Approach Tactics)
Bây giờ bạn đã biết việc định hướng giải bài nó như thế nào và nó bao gồm những gì, bạn sẽ nhận ra rằng trước đây bạn đã biết khá nhiều cách để tiếp cận một bài toán. Dạng như “ Tôi dùng DP(dynamic programming) cho bài đó”, “Tôi có thể dùng greedy để giải bài này không ?”, “Đừng nói với tôi rằng brute-force có thể ăn bài này”. Thật ra bạn đang dùng sai những từ ngữ ở đây, vì bạn không thể phân loại mỗi bài tập chỉ với greedy hay brute-force. Có rất rất nhiều dạng bài tập, và cũng rất nhiều cách tiếp cận, và thậm chí với mỗi hướng tiếp cận có thể tồn tại rất nhiều cách thể hiện khác nhau. Cách dùng từ như vậy chỉ tổng quát được những bước đi lớn để đến được đáp án.

Một số bài editorial có hướng dẫn chi tiết từ các hướng tiếp cận bài toán cho đến đáp án hoàn chỉnh. Lần tham gia contest tiếp theo, bạn hãy thử tìm một bài viết tốt, tìm các bước tiếp cận cụ thể của bài toán mà tác giả đã chỉ ra. Bạn sẽ bắt đầu chú ý rằng có một tính chất nào đó của bài toán sẽ gợi ra cho bạn một cách tiếp cận, hay những cách biến đổi, chuyển hướng, phân tích, ... làm bạn đến gần hơn với đáp án, hay ít nhất sẽ cho thấy rằng cách tiếp cận hiện tại là sai. Khi tìm một cách tiếp cận, hãy thử tất cả những hướng đi bạn có, bởi vì đó là những thứ quen thuộc và có sẵn trong đầu rồi. Nó giống như việc bạn đang thuyết phục bản thân rằng những hướng tiếp cận đó là đúng.

Những coder có kiến thức toán cơ bản tốt sẽ có thể biết được hướng suy nghĩ này, bởi vì những hướng tiếp cận đó rất giống với kĩ năng chứng minh toán học. Với những người chơi cờ họ sẽ dùng chiến thuật giống như xét các nước cờ tiếp theo để xem sự việc sẽ xảy ra như thế nào. Những người thiết kế ứng dụng có thể ứng dụng những cách tiếp cận giống như khi đang làm việc với design patterns. Việc làm cách tiếp cận cho bài toán tương tự với rất nhiều công việc thường ngày.

Để luyện tập cách tư duy, hãy chọn một cách tiếp cận bạn thấy phú hợp nhất và luyện tập theo cách tiếp cận đó. Sau đó hãy viết một bài phân tích dựa trên những gì bạn đã làm, càng chi tiết càng tốt, để những người khác có thể biết được cách bạn suy nghĩ như thế nào. Việc viết lại như thế không chỉ giúp bạn hiểu rõ hơn cách tiếp cận của mình, mà còn tìm ra được những sai lầm của bản thân và cải thiện nó. Hãy nhớ rằng, rất khó để cải thiện được những điều mà bạn còn chưa hiểu. 

## Chia nhỏ vấn đề
Hãy bàn về một trong những cách tiếp cận phổ biến nhất: chia nhỏ vấn đề ra, còn được gọi là tiếp cận từ trên xuống (top-down programming). Ý tưởng cơ bản ở đây là code của bạn phải được thực hiện theo thứ tự, nên hãy bắt đầu bằng việc suy nghĩ xem hàm main sẽ cần những gì trước khi xây dựng những hàm con. Điều này cho phép bạn thấy được tổng thể chương trình, cũng như chia nhỏ vấn đề từ những thứ phức tạp cho đến đơn giản.

Một ví dụ áp dụng cách tiếp cận này. Round 2, MatArith, topcoder Invitational 2002, bài toán yêu cần bạn phải tính giá trị biểu thức có sử dụng ma trận. Để có được những con số chúng ta phải parse nó ra (vì đó là string), tính toán dựa trên đó, và trả ngược về string. Nên bạn cần một hàm print, một hàm parse và một hàm calc (để xử lí toán học). Không cần suy nghĩ quá phức tạp, Nếu chúng ta có đủ 3 hàm đó thì vấn đề sẽ được giải quyết chỉ trong 1 dòng code:
```cpp
public String[] calculate(String[] A, String[] B, String[] C, String eval){
   return print(calc(parse(A),parse(B),parse(C),eval));
}
```

Cái hay của các tiếp cận này là tạo ra một hệ thống cấp bậc cấp hàm con, hàm trên sẽ dựa vào kết quả của hàm dưới để chạy. Bây giờ công việc đã được chia làm 3 phần: tạo hàm parse, hàm print, và hàm tính toán. Nếu bạn chia bài toán thành những bài toán con đủ nhỏ, bạn sẽ không phải tốn nhiều thời gian vào việc suy nghĩ cho những bước không đơn giản, bởi vì nó sẽ trở nên atomic (sẽ được đề cập phía dưới). Thay vào đó chúng ta có thể tập trung vào hàm cộng và hàm nhân ma trận hay hàm đọc dữ liệu vào sao cho chính xác. 

Cách tiếp cận này có thể ứng dụng khá hiệu quả vào những bài toán đệ quy. Toàn bộ ý tưởng của đệ quy đó là chia vấn đề lớn thành những vấn đề nhỏ hơn nhưng giống chính xác với vấn đề gốc, vậy chúng ta chỉ cần giải được một 1 vấn đề gốc là xong. Cách tiếp cận này cũng được sử dụng rất phổ biến trong lập trình hàm (functional programming). Có khá nhiều bài viết đã bàn sâu về vấn đề này, nhưng ý tưởng cơ bản chính là nếu ta chia nhỏ bài toán một cách đúng đắn, chương trình sẽ tự động gửi tham số qua mỗi lời gọi hàm, không cần thiết lưu trữ dữ liệu giữa các bước. Nhưng có một nhược điểm là sẽ khó debug hơn.







