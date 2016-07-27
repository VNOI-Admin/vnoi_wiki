# Tham lam thì tốt
John Smith đang gặp rắc rối! Anh ấy là một thành viên của **Topcoder** và sau khi học cách để trở thành bậc thầy trong việc đối phối với các bài toán quy hoạch động, anh ấy bắt đầu giải quyết hàng loạt các bài tập. Nhưng chiếc máy tính *"dễ bảo"* của anh bắt đầu trở chứng vào hôm nay. Vào mỗi buổi sáng như thường lệ, John thức dậy vào lúc 10 giờ sáng, uống một cốc cà phê và bắt đầu giải các bài tập trước khi thưởng thức bữa sáng. Mặc dù có thứ gì đó *"sai sai"* so với mọi hôm, nhưng dựa vào kho tàng kiến thức mà anh ấy vừa mới gặt hái được, John đã viết chương trình với một tốc độ thần thánh. Mệt mỏi với việc cấp phát ma trận vào mỗi buổi sáng, chiếc máy tính thông báo rằng: **"Segmentation fault!"**. Dù cho dạ dày còn đang rỗng, song với ý tưởng thông minh của mình, John đã vượt qua rắc rối bằng cách chèn thêm một vòng lặp. Nhưng chiếc máy tính lại gào lên: **"Time limit exceeded!"**.

Thay vì tiếp tục vướng vào mớ rắc rối, John đã có một quyết định tiến bộ hơn. Quá đủ cho việc lập trình! John nói. Anh ấy quyết định sẽ có một kỳ nghỉ như là phần thưởng cho những nỗ lực của mình.

Là một con người tràn trề sinh lực, John muốn dành thời gian nhiều cho cuộc đời của mình. Có quá nhiều thứ mà anh ta muốn làm, nhưng không may là anh ta không thể nào làm hết tất cả chúng được. Thế nên trong lúc ăn sáng, John đã vạch ra một *"Fun plan"* được thể hiện bằng một thời gian biểu cho từng hoạt động như sau:
<table>
<tr><th>Id</th> <th>Hoạt động</th> <th>Thời gian</th></tr>
<tr><td>1</td> <td>Sửa phòng</td> <td>Thứ 2, 22:00 đến thứ 3, 1:00</td></tr>
<tr><td>2</td> <td>Du lịch Hawaii</td> <td>Thứ 3, 6:00 đến thứ 7, 22:00</td></tr>
<tr><td>3</td> <td>Vô địch cuộc thi cờ vua</td> <td>Thứ 3, 11:00 đến thứ 3, 21:00</td></tr>
<tr><td>4</td> <td>Thạm dự nhạc hội Rock</td> <td>Thứ 3, 19:00 đến thứ 3, 23:00</td></tr>
<tr><td>5</td> <td>Chiến thắng cuộc thi Starcraft</td> <td>Thứ 4, 15:00 đến thứ 5, 15:00</td></tr>
<tr><td>6</td> <td>Chơi trò bắn súng nước sơn</td> <td>Thứ 5, 10:00 đến thứ 5, 16:00</td></tr>
<tr><td>7</td> <td>Tham gia kỳ thi SRM trên **Topcoder**</td> <td>Thứ 7, 12:00 đến thứ 7, 14:00</td></tr>
<tr><td>8</td> <td>Tắm rửa</td> <td>Thứ 7, 20:30 đến thứ 7, 20:45</td></tr>
<tr><td>9</td> <td>Tổ chức tiệc ngủ</td> <td>Thứ 7, 21:01 đến thứ 7, 23:59</td></tr>
<tr><td>10</td> <td>Tham gia thử thách <i>"All you can eat"</i> và <i>"All you can drink"</i></td> <td>Thứ 7, 21:01 đến thứ 7, 23:59</td></tr>
</table>
Giờ anh ấy muốn thực hiện được tối đa các hoạt động trong thời gian biểu trên. Mặc dù một kế hoạch an toàn thì cần phải có chút lý trí vào đó, nhưng giờ thì hồn anh ấy đã đắm chìm vào kỳ nghỉ rồi.

Liệu ta có thể giúp anh ấy có một kỳ nghỉ tuyệt vời? Ta hoàn toàn có thể! Đầu tiên, ta hãy đưa ra một giả định. Là một lập trình viên tỉ mỉ, một khi đã đặt ra kế hoạch, anh ấy buộc phải thực hiện nó. Thế nên, mỗi hoạt động chỉ có hai chọn lựa là có hoặc không. Và với mỗi trường hợp chọn lựa cho hoạt động thứ nhất, ta lại có thêm 2 lựa chọn cho hoạt động thứ 2. Phân tích nhanh ta sẽ thấy được rằng có $2^n$ trường hợp, và trong tình huống này thì đó sẽ là 1024 trường hợp. Với mỗi trường hợp ta sẽ kiểm tra xem nó có thỏa mãn giới hạn về thời gian hay không. Từ đây, việc cho lựa 1 phương  án có nhiều hoạt động nhất sẽ trở nên dễ dàng hơn.Với khá nhiều sự chọn lựa như thế này, John buộc phải nhờ đến sự giúp đỡ của chiếc máy tính đang mệt mỏi. Nhưng điều gì sẽ xảy ra nếu John có tới 50 hoạt động trong danh sách? Thậm chí dùng đến cả chiếc máy tính mạnh mẽ nhất thế giới thì cũng cần đến vài năm để tìm ra câu trả lời. Thế nên, phương án này khá phi thực tế.

Giờ hãy đơn giản hóa vấn đề cũng như niềm tin vào bản năng nền tảng của chúng ta. Một phương án tốt sẽ tạo ra cơ hội thành công ngay khi mà thời cơ đến. Đó là, nếu ta có hai hoạt động và chúng bị trùng về thời gian, ta sẽ ưu tiên lựa chọn hoạt động xảy ra trước nhằm tiết kiệm thời gian. Ví dụ trong trường hợp anh ta bắt đầu buổi tối đầu tiên bằng việc sửa chữa phòng. Buổi sáng, anh ấy sẽ bắt một chuyến bay. Và chưa đầy một ngày nhưng anh ấy đã thực hiện được 2 hoạt động. Thật tuyệt vời! Nhưng thật ra, đó chỉ lại **lựa chọn tốt nhất** lúc này thôi. Và bây giờ thì ta có gì, 5 ngày ăn chơi ở Hawaii và cho đến tận tối thứ 7 thì anh ấy vẫn chỉ thực hiện được 2 hoạt động. Hãy nghĩ xem trong 5 ngày đó anh ta đã có thể thực hiện được những gì. Mặc dù đơn giản và thực thi rất nhanh, song rất không may là thuật toán này lại không chính xác.

Ta vẫn không cần phải xét tất cả các trường hợp, hãy thử một mánh khóe khác. Giờ ta sẽ bỏ những hoạt động tiêu tốn nhiều thời gian như đi du lịch Hawaii bằng cách lựa chọn những hoạt động tốn ít thời gian nhất và kiểm tra xem nó có hợp lí với những hoạt động đã chọn trước đó chưa rồi tiếp tục quá trình. Theo như thời gian biểu ở trên thì hoạt động đầu tiện được chọn lựa sẽ là tắm. Với thời gian chỉ 15 phút, đây chính là **lựa chọn cục bộ tối ưu**. và giờ điều mà ta cần biết đó là có thể giữ được **tối ưu cục bộ** khi mà những hoạt động thích hợp khác được chọn lựa. Thời gian biểu của John sẽ như sau:

* Đi tắm (15 phút).
* Tham gia vào kỳ thi SRM trên Topcoder (2 tiếng).
* Tham gia thử thách *"All you can eat"* và *"All you can drink"* (2 tiếng 58 phút).
* Sửa phòng (3 tiếng).
* Tham nhạc buổi hòa nhạc Rock (4 tiếng).
* Chơi bắn súng nước sơn (6 tiếng).

Trong 10 hành động, ta đã lựa ra được 6 hành động (hoàn toàn không tệ). Giờ thì thuật toán của ta đã chậm lại nhưng nó trở nên đáng tin cậy hơn nếu đây là lựa chọn tốt nhất mà ta có thể thực hiện. Và quả thực, đáp án chính là 6. John rất hài lòng về sự hỗ trợ của chúng ta, nhưng sau khi trở về từ kỳ nghỉ với kế hoạch thông minh của chúng ta, John đã phải đối mặt với những rắc rối nghiêm trọng khác:

