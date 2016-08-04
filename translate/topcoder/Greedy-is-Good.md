# Tham lam thì tốt
John Smith đang gặp rắc rối! Anh ấy là một thành viên của **Topcoder** và sau khi học cách để trở thành bậc thầy trong việc đối phối với các bài toán quy hoạch động, anh ấy bắt đầu giải quyết hàng loạt các bài tập. Nhưng chiếc máy tính *"dễ bảo"* của anh bắt đầu trở chứng vào hôm nay. Vào mỗi buổi sáng như thường lệ, John thức dậy vào lúc 10 giờ sáng, uống một cốc cà phê và bắt đầu giải các bài tập trước khi thưởng thức bữa sáng. Mặc dù có thứ gì đó *"sai sai"* so với mọi hôm, nhưng dựa vào kho tàng kiến thức mà anh ấy vừa mới gặt hái được, John đã viết chương trình với một tốc độ thần thánh. Mệt mỏi với việc cấp phát ma trận vào mỗi buổi sáng, chiếc máy tính thông báo rằng: **"Segmentation fault!"**. Dù cho dạ dày còn đang rỗng, song với ý tưởng thông minh của mình, John đã vượt qua rắc rối bằng cách chèn thêm một vòng lặp. Nhưng chiếc máy tính lại gào lên: **"Time limit exceeded!"**.

Thay vì tiếp tục vướng vào mớ rắc rối, John đã có một quyết định tiến bộ hơn. Quá đủ cho việc lập trình! John nói. Anh ấy quyết định sẽ có một kỳ nghỉ như là phần thưởng cho những nỗ lực của mình.

Là một con người tràn trề sinh lực, John muốn dành thời gian nhiều cho cuộc đời của mình. Có quá nhiều thứ mà anh ta muốn làm, nhưng không may là anh ta không thể nào làm hết tất cả chúng được. Thế nên trong lúc ăn sáng, John đã vạch ra một *"Fun plan"* được thể hiện bằng một thời gian biểu cho từng hoạt động như sau:
<table align="center">
<tr><th>Id</th> <th>Hoạt động</th> <th>Thời gian</th></tr>
<tr><td>1</td> <td>Sửa phòng</td> <td>Thứ 2, 22:00 đến thứ 3, 1:00</td></tr>
<tr><td>2</td> <td>Du lịch Hawaii</td> <td>Thứ 3, 6:00 đến thứ 7, 22:00</td></tr>
<tr><td>3</td> <td>Vô địch cuộc thi cờ vua</td> <td>Thứ 3, 11:00 đến thứ 3, 21:00</td></tr>
<tr><td>4</td> <td>Thạm dự nhạc hội Rock</td> <td>Thứ 3, 19:00 đến thứ 3, 23:00</td></tr>
<tr><td>5</td> <td>Chiến thắng cuộc thi Starcraft</td> <td>Thứ 4, 15:00 đến thứ 5, 15:00</td></tr>
<tr><td>6</td> <td>Chơi trò bắn súng nước sơn</td> <td>Thứ 5, 10:00 đến thứ 5, 16:00</td></tr>
<tr><td>7</td> <td>Tham gia kỳ thi SRM trên <strong>Topcoder</strong></td> <td>Thứ 7, 12:00 đến thứ 7, 14:00</td></tr>
<tr><td>8</td> <td>Tắm rửa</td> <td>Thứ 7, 20:30 đến thứ 7, 20:45</td></tr>
<tr><td>9</td> <td>Tổ chức tiệc ngủ</td> <td>Thứ 7, 21:00 đến Chủ nhật, 6:00</td></tr>
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

Trong 10 hành động, ta đã lựa ra được 6 hành động (hoàn toàn không tệ). Giờ thì thuật toán của ta đã chậm lại nhưng nó trở nên đáng tin cậy hơn nếu đây là lựa chọn tốt nhất mà ta có thể thực hiện. Và quả thực, đáp án chính là 6. John rất hài lòng về sự hỗ trợ của chúng ta, nhưng sau khi trở về từ kỳ nghỉ với kế hoạch thông minh này, John đã phải đối mặt với những rắc rối nghiêm trọng khác:
<div align="center">
	<img src="http://community.topcoder.com/i/education/greedyAlg1.gif" alt="" border="0">
</div>
Áp dụng thuật toán của ta, John đã tham gia một cuộc hẹn hò chóng vánh, để rồi anh ấy đã bỏ lỡ cả bài thi trong trường lẫn trận đấu bóng rổ của đội anh ấy yêu thích. Là một **Topcoder**, chúng ta cần phải viết ra một chương trình hoàn toàn có thể tin cậy trong vấn đề này. Chỉ cần một trường hợp duy nhất chúng ta không giải quyết được sẽ dẫn tới một thất bại toàn diện.

Những gì mà chúng ta thường làm trong tình huống này là phân tích điều gì đã gây ra lỗi ở lựa chọn đầu tiên và các hành động phù hợp để tránh nó trong tương lai. Giờ ta hãy xét lại kịch bản đầu tiên. Cuộc hẹn hò trùng thời gian với cả việc làm bài thi lẫn trận đấu bóng rổ, trong khi cả trận đấu bóng rổ lẫn làm bài thi chỉ trùng lặp với một minhg cuộc hẹn hò. Vậy thì ý tưởng cũng tự sinh ra từ vấn đề này. Tại sao ta không chọn hoạt động ít bị trùng lặp nhất so với những hoạt động còn lại ? Nghe có vẻ hợp lí - giờ thì một thứ đã đúng hơn rồi đấy ! Giờ ta sẽ thử chứng minh rằng phương pháp này hoàn toàn đúng đắn. Giờ giả sử ta đã lựa chọn hoạt động X, ta se thử kiểm tra xem ta có thể lựa chọn hoạt động A và B (những hoạt động bị trùng lặp với X) thay vì X được hay không. Và A, B cũng không được trùng lặp nhau, nếu không ta cũng không thể tối ưu hóa kết quả. Bây giờ, ta sẽ quay về trường hợp trước đó (X trùng với 2 hoạt động, A và B trùng với 1 hoạt động). Trong trường hợp này, ta sẽ chọn A và B ngay từ đầu tiên. Một trong những cách để phản bác lại giả thiết này chính là cho hoạt động A và B trùng lặp với nhiều hoạt động hơn nữa chứ không chỉ hoạt động X. Nghe nó có vẻ không trực quan cho lắm, nhưng (thật không may) ta vẫn có thể xây dựng trường hợp đó như sau:
<div align="center">
	<img src="http://community.topcoder.com/i/education/greedyAlg2.gif" alt="" border="0">
</div>

Nhưng hoạt động được biểu diễn bằng gạch màu xanh chính là những lựa chọn tối ưu trong thời gian biểu trên. Nhưng hoạt động tô màu đỏ trùng lặp với 2 hoạt động nên nó sẽ được chọn trước. Vẫn còn 4 hoạt động thích hợp khác trước hoạt động đỏ, nhưng chúng đều bị trùng lặp lẫn nhau, thế nên ta chỉ có thể lựa chọn thêm 1 hoạt động. Điều tương tự cũng xảy ra đối với 4 hoạt động sau hoạt động màu đỏ, nhưng ta vẫn chỉ có thể chọn 1. Vậy tổng cộng theo phương pháp này, ta vẫn chỉ có thể chọn 3 hoạt động, trong khi kết quả tối ưu là 4.

Tổng quát lại, ta thấy được rằng mỗi đáp án của chúng ta đều tồn tại một thiếu sót. Có vẻ như chúng ta đang đối mặt với một vấn đề hóc búa. Nhưng thật ra, vấn đề này vẫn có một cách giải quyết đẹp đẽ, và không hề phức tạp. Nếu ta xem xét các hình trên một cách kỹ lưỡng hơn nữa, ta sẽ thấy được rằng hoạt động màu xanh nằm ở góc trái dưới là là hoạt động duy nhất hoàn thành trước *"timeline"* được biểu diễn bằng đường vẽ dọc màu đỏ. Vậy, nếu lựa chọn 1 hoạt động đơn lẻ, ta sẽ chọn hoạt động kết thúc đầu tiên (tại thời điểm **t1**), lúc đó toàn bộ khoảng thời gian còn lại sẽ trống để ta có thể chọn các hoạt động khác. Nếu chúng ta chọn bất kỳ hoạt động nào khác, thì khoảng thời gian còn lại sẽ ngắn đi. Điều này là hiển nhiên, bởi vì khi ta kết thúc với bất kỳ một hoạt động nào khác thì luôn luôn **t2** > **t1**. Trong trường hợp đầu tiên, ta sẽ có toàn bộ thời gian từ **t1** đến khi kết thúc và bao gồm luôn khoảng từ **t2** đến kết thúc. Bởi vậy mà nó cũng không có khuyết điểm trong việc lựa chọn hoạt động kết thúc sớm. Và nó còn có một ưu điểm đó là ta hoàn toàn có thể chèn thêm một hoạt đồng bất kỳ vào giữa **t1** và **t2** và kết thúc trước khi hoạt động của **t2** bắt đầu.

Được biết tới với tên gọi **"Lựa chọn hoạt động"**, đây là bài toán cơ sở sử dụng **"Phương pháp Tham lam"**. Giống như là một gã tham lam luôn muốn chiếm lấy nhiều nhất, thường xuyên nhất mà hắn ta có thể, trong trường hợp này, ở mỗi bước ta sẽ chọn lựa một hoạt động kết thúc đầu tiên và mỗi lần đều không có hoạt động đang trong tiến trình. Và có một sự thật đó là ta luôn luôn áp dụng phương pháp tham lam cho mỗi bước trong cuộc đời của mình. Khi ta đi mua sắm hoặc đi xe hơi, ta đều luôn lựa chọn phương án tốt nhất tại thời điểm hiện tại. Thật ra, phương pháp tham lam có 2 công thức chung:
* Tính lựa chọn tối ưu: Từ những kết quả tối ưu cục bộ ta có thể đi đến kết quả tối ưu toàn cục mà không cần phải xem xét lại các kết quả.
* Tính tối ưu từ bài toán nhỏ: Kết quả tối ưu có được xác định bằng các kết quả tối ưu từ bài toán nhỏ hơn.

Đoạn mã giả dưới đây diễn ta cách lựa chọn tối ưu các hoạt động bằng thuật toán tham lam mà ta vừa chứng minh phía trên:

```
Đặt N là số hoạt động và 
{I} là hoạt động thứ I  ( 1 <= I <= N )

Với mỗi {I}, xét S[I] và F[I] lần lượt là thời gian bắt đầu và kết thúc của hoạt động đó.
Sắp xếp lại các hoạt động theo thứ tự tăng dần của thời gian kết thúc.
- Có nghĩa là, với I < J ta phải có F [I] <= F [J]

//  A là tập hợp các hoạt động được chọn
A = {1}
//  J là hoạt động cuối cùng được chọn
J = 1
For I = 2  to N
// ta có thể chọn I nếu nó là hoạt động cuối cùng
// việc chọn lựa đã hoàn thành
      If S [I] >= F [J]
// lựa chọn hoạt động 'I'
                A = A + {I}
// hoạt động 'I' giờ trở thành hoạt động cuối cùng được lựa chọn
                J = I
      Endif
Endfor

Return A
```

Sau khi áp dụng thuật toán trên, *"Fun plan"* của Johnny sẽ như thế này:

* Xóa hết mọi lỗi và đi tắm.

* Thứ 3 để đánh cờ và chiến thắng.

* Cả ngày để chơi Starcraft, có vẻ vui đây.

* Hai ngày tiếp theo để nghỉ ngơi.

* Và vào ngày cuối cùng, lấy một ít điểm rating từ **Topcoder**, tắm rửa, tận hưởng bữa ăn *"sâu bọ"* và những ly rượu hảo hạng.

Vấn đề của John Smith đã được giải quyết, tuy nhiên đây chỉ là một ví dụ mà Tham lam có thể hoạt động. Một vài vấn đề thật sự khác đến từ **Topcoder** sẽ giúp bạn hiểu rõ hơn về khái niệm này. Trước khi tiếp tục, có lẽ bạn cần phải luyện tập thêm chút ít nữa với những gì mà bạn vừa đọc, bằng bài tập tương tự với *Lựa chọn hành động*, tên là [Boxing ](http://www.topcoder.com/stat?c=problem_statement&pm=2977&rd=5880)

**BioScore**

Đối với bài tập này, bạn sẽ được yêu cầu làm tối đa hóa số điểm trung bình của các cặp tương đồng. Từ đáp án tối ưu cần tìm, ta có thể xem nó như một gợi ý nhằm giúp ta tìm ra phương án thích hợp. Thường thì, đối với dạng bài toán này, ta sẽ sử dụng phương pháp *quy hoạch động* để giải quyết, nhưng trong một vài trường hợp thì chiến lược **Tham lam** vẫn hoàn toàn có thể được sử dụng.

Việc đầu tiên mà ta cần làm là *xây dựng một ma trận cho biết số lần lặp* (**ma trận tần số**). Đây là một công việc khá nhẹ nhàng khi mà ta chỉ cần ghép từng cặp ký tự ở hai chuỗi tạo thành một *axit nucleic* rồi đếm số lần xuất hiện của chúng (AA, AC, AG, AT, CA, CC, CG, CT, GA, GC, GG, GT, TA, TC, TG, TT). Từng loại *axit nucleic* sẽ được xem như một phần tử trong ma trận và giá trị của nó chính là số lần xuất hiện của nó. Ví dụ, hãy xét bộ {"ACTAGAGAC", "AAAAAAAAA", "TAGTCATAC", "GCAGCATTC"} được sử dụng ở ví dụ thứ 2.

![Ví dụ](http://community.topcoder.com/i/education/greedyAlg3.gif)

Ở góc phải - dưới của hình minh họa trên, ta có thể thấy kết quả của ma trận tần số đối với bộ đã cho. Tạm gọi nó là F. Giờ việc mà ta cần làm là tìm ra một ma trận S khác sao cho tổng của các tích số của 16 loại *axit nucleic* **$F[i, j]*S[i, j]$** $(1 <= i, j <= 4)$ là lớn nhất.

Giờ ta xét từng điều kiện cho ma trận cần tìm:

**1) Tổng của 16 phần tử bằng $0$:**

Đây là một điều kiện khá phổ biến. Bởi tất cả các phần tử của **F** đều dương (em nghĩ là không âm chứ?), nên các điểm cuối cùng có xu hướng tăng khi ta tăng phần tử của **S**. Nhưng bởi vì tống của chúng phải bằng $0$, thế nên khi ta tăng giá trị 1 phần tử lên thì ta sẽ phải giảm đi giá trị của 1 phần tử khác. Thử thách ở điều kiện này chính là phải tìm ra một sự phân bố tối ưu.

**2) Giá trị mỗi phần tử chỉ nằm trong khoảng từ -10 đến 10 ($S[i, j] \in [-10, 10]$)**

Lại một điều kiện phổ biến khác! Với điều kiện này, khoảng tìm kiếm của chúng ta đã được thu hẹp đi rất nhiều, song vẫn còn khá nhiều lựa chọn cho ta.

**3) Mỗi phần tử đối xứng phải có giá trị bằng nhau ($score(x, y) = score(y, x)$)**

Bởi vì tính đối xứng, ta phải quy định cho các điểm cho các cặp như "AC" và "CA" bằng nhau. Như là một hệ quả, ta đã vô tình đếm số lần xuất hiện của chúng. Đối với ví dụ trên, ta đã có tần số của tập hợp các cặp như sau:

<table align="center">
<tr><td>AA: 14</td> <td>CC: 4</td> <td>GG: 0</td> <td>TT: 1   </td></tr>
<tr><td>AC+CA: 11</td> <td>AG+GA: 10</td> <td>AT+TA: 10</td> <td></td> </tr>
<tr><td>CG+GC: 2</td> <td>TC+CT: 0</td> <td></td> <td></td></tr>
<tr><td>GT+TG: 3</td> <td></td> <td></td> <td></td></tr>
</table>

Từ trực giác ta có thể thấy ngay đến phương án như sau: đã sẽ gán điểm số càng cao đối với cặp xuất hiện càng nhiều lần. Tuy nhiên, ta lại bị ràng buộc rằng tổng các phần tử phải bằng 0, một vấn đề khác lại nảy sinh. Những cặp như AA, CC, GG, TT chỉ xuất hiện một lần trong ma trận nên số điểm của chúng sẽ ít hơn so với tổng điểm.

**4) Các phần tử trên đường chéo phải dương ($score(x, x) > 0$)**

Sự khác biệt giữa các phần tử trên đường chéo và các phần tử còn lại ngày càng lớn. Nhìn chung, ta có hai loại phần tử:
bốn phần tử trên đường chéo (các phần tử đại diện cho AA, CC, GG, TT) và sáu phần tử không nằm trên đường chéo (các phần tử đại diện cho AC + CA, AG + GA, AT + TA, CG + GC, CT + TC, GT +TG). Mỗi nhóm trên sẽ có các cấu hình khác nhau, tùy thuộc vào cách mà ta đặt giá trị cho chúng.

Đơn giản hóa vấn đề, **với mỗi cấu hình ta đặt nhóm thứ nhất, ta sẽ tìm ra đáp án tối ưu cho nhóm thứ hai**. Bởi vì tất cả các phần tử ở nhóm thứ hai đều có chung tính chất, ta sẽ sử dụng **phương pháp Tham lam** để tìm kết quả tối ưu cho nhóm thứ hai. Nhưng vì mỗi giá trị ở nhóm thứ nhất đều có thể chọn trong khoảng $[1, 10]$, nên giá trị tổng mà ta tìm kiếm ở nhóm hai cần phải được tính toán lại. Không khó để nhận ra tổng của nhóm thứ nhất có thể là bất kỳ số nào trong khoảng $[4, 40]$. Như một hệ quả, dựa vào việc ta chọn tổng ở nhóm một, ta có thể suy ra được tổng của nhóm hai sẽ trong khoảng $[-20, -2]$ (*chúng ta không được quên rằng nhóm hai đối xứng, xuất hiện hai lần trong ma trận nên giá trị phải nhân đôi lên*).

Và giờ, ta đã đến được **cốt lõi của vấn đề**. Lời giải cho cả vấn đề này chính là việc tìm được giá trị điểm tối ưu cho nhóm thứ hai. Nếu vấn đề quả thật là **lựa chọn tham lam** và **tối ưu hóa cục bộ**, ta hoàn toàn có thể lấy một phần tử ra, gắn cho nó giá trị tối ưu và thực hiện tương tự với các phần tử còn lại.

**Ta có được khẳng định như sau: Nếu ta luôn luôn gán giá trị lớn nhất có thể cho phần tử xuất hiện nhiều lần nhất trong một nhóm, và cuối cùng ta sẽ thu được kết quả lớn nhất có thể cho toàn nhóm đó.** 

Việc đầu tiên mà ta cần làm là sắp xếp lại sáu phần tử này trong ma trận **F**. Giờ, ta sẽ thực sự tính toán các giá trị tương ứng trong S. Tổng điểm tối thiểu mà ta đạt được là $-20$, một ý nghĩ chợt lóe lên trong ta, hai giá trị đầu tiên sẽ được gắn bằng $10$ (kể cả 4 giá trị còn lại ta có gán $-10$ đi chăng nữa thì ta vẫn thu về được giá trị $-20$). Ta biến rằng số điểm cuối cùng sẽ nhỏ hơn $0$. Bởi vì ta muốn tối đa hóa số điểm của phần tử đầu tiên nên ba phần tử còn lại sẽ là $-10$ (trong trường hợp tốt nhất, điểm tổng sẽ là $-2$ và lúc đó, ta sẽ điền số điểm như sau: $[10, 10, 8, -10, -10, -10]$). Cuối cùng, giá trị của phần tử thứ ba sẽ được xác định dựa vào lựa chon của ta cho nhóm thứ nhất. Đối với giá trị lớn nhất là $10$, ta sẽ trừ đi phần nửa của tổng số điểm của nhóm thứ nhất (ta lưu ý rằng tổng nói trên buộc phải là số chẵn).

Giờ thì ta cần phải chứng minh rằng phương pháp của mình là đúng. Cách chứng mình này cũng không quá phức tạp. Nhằm mục đích để tổng của **S** là một hằng số, ta chỉ có thể giảm các cặp có số lần xuất hiện nhiều hơn tăng những cặp có số lần xuất hiện ít hơn. Gọi **f1** và **f2** lần lượt là số lần xuất hiện của của hai cặp và $f1 >= f2$. Ta có $f1 * s1 + f2 * s2 = X$, với X là tổng tối đa mà ta đạt được. Bằng **giả định Tham lam** của ta, $s1 >= s2$. Vì tổng $s1+s2$ là một hằng số, tổng trên sẽ biến đổi thành $f1 * (s1-a) + f2 * (s2-a) = Y$ với a là số dương ($a > 0$). Ta tìm ra được rằng $Y-X = a * (f2-f1)$. Bởi vì $f1 >= f2$ nên khoảng cách này luôn dương. Vì Y có thể lựa chọn tùy ý, ta có thể kết thúc *lựa chọn Tham lam* ban đầu bằng việc luôn cho Y số điểm lớn nhất.

Ta áp dụng thuật toán trên cho mỗi cấu hình của các phần tử trong nhóm đầu tiên và lưu lại kết quả tốt nhất. 

Phương pháp biểu diễn: Thay vì phải dùng tới hai ma trận **F** và **S**, **ta có thể dùng một mảng đề lưu đồng thời cả cả số lần lặp lẫn số điểm tương ứng**. 4 phần tử đầu tiên của mảng **F** sẽ thể hiện tần số của các cặp AA, CC, GG, TT. 6 phần tử tiếp theo sẽ lưu số lần lặp của các cặp có thể sinh ra và được sắp xếp giảm dần dựa vào tần số  $(F[5] >= F[6] >= F[7] >= F[8] >= F[9] >= F[10])$. **S** sẽ là một mảng có 10 phần tử mà $S[i]$ chính là số điểm mà ta phân bổ cho cặp $i$. 

Ý tưởng chính của thuật toán trên sẽ được minh họa trong đoạn mã giả dưới đây:

```
Best = -Infinity
For S [1] = 1 to 10
      For S [2] = 1 to 10
            For S [3] = 1 to 10
                  For S [4] = 1 to 10
                        If  (S [1] + S [2] + S [3] + S [4]) mod 2 = 0
                             S [5] = S[6] = 10
                             S [7] = 10 - (S [1] + S [2] + S [3] + S[4]) / 2
                             S [8] = S [9] = S [10] = -10
//  biến Best sẽ lưu lại giá trị trung bình lớn nhất
                             Best = max (Best , score (F,S))
//  kết quả tốt nhất thu được đến lúc này
                       Endif
                 Endfor
           Endfor
      Endfor
Endfor
Return Best
```

Đối với mảng lưu điểm đã cho (trong trường hợp của chúng ta là mảng **S**), ta sẽ tính kết quả cuối cùng bằng việc chỉ tính tổng của tích $F[I] * S[I] ( 1 <= I <=10)$ và chia nó cho $N * (N-1) / 2$ để thu được kết quả trung bình.
