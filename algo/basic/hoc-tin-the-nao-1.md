# Tôi đã học tin học như thế nào? Phần 1: vòng lặp

Tác giả: Nguyễn Xuân Khánh

> Biển học là vô bờ. Hai chữ “vô bờ” bản thân nó vốn ám chỉ rằng không có đích đến rồi. Bạn rong ruổi trên một con tàu theo năm tháng trên đại dượng tri thức. Vậy thì ý nghĩa của một cuộc sống như vậy nằm ở đâu? Là vẻ đẹp của những hòn đảo bạn ghé thăm, những trải nghiệm về phong ba bão táp của đại dương, những cuộc gặp gỡ duyên phận với những con tàu khác, những cuộc đua và những khi tản mạn.

Năm 2007, tôi nộp đơn thi vào trường Phổ Thông Năng Khiếu-Đại học quốc gia thành phố Hồ Chí Minh. Tôi không hề biết gì về trường này trước đó, chỉ biết rằng học sinh trường này ắt hẳn phải là siêu nhân sau khi tôi xem qua đề tuyển sinh môn toán. Tôi lúc ấy cũng đang học chuyên môn toán. Tôi không biết gì về lập trình dù đã được học được hơn tháng về Pascal (người dạy tôi khi ấy chỉ chép lên bảng code từ sách ra, bảo tôi gõ lại và không giảng gì thêm). Tôi nộp đơn vào lớp chuyên toán của PTNK. Kết qủa là tôi thiếu 0.25 điểm để đậu vào lớp chuyên toán. May mắn thay lớp chuyên Tin của trường vẫn lấy một nửa chỉ tiêu từ số học sinh có nguyện vọng vào lớp toán. Tôi đủ điểm để vào chuyên Tin nhưng tôi cảm thấy rất lo: xa nhà, học ở một trường qúa sức, chuyên một môn học bí ẩn. Tôi nói: “Con không học chuyên Tin đâu!”. Nhưng rồi tôi cũng đi. Mẹ tôi khóc nhiều. Ba tôi chạy khắp nơi để lo chỗ ở, xe cộ, chỗ ăn uống cho tôi ở một thành phố lớn, nhưng lạ.

Ngày đầu tiên tôi bước vào lớp, tôi bị sốc. Bạn tôi đố nhau về toán học và tin học. Đi đâu tôi cũng nghe cái từ “lệ quy”. Bài nào cũng giải được bằng “lệ quy”. Tôi thấy cái từ này sao nó hay, nó đẹp thế. Mãi sau này tôi mới biết là tôi nghe nhầm từ “đệ quy”.

Trường chúng tôi năm ấy nhập học sớm, lớp tôi được học thêm một vài tuần về toán rời rạc trước khi vào chương trình của năm học. Vài tuần đầu, chúng tôi được học cơ bản về ngôn ngữ PASCAL: dùng vòng lặp for để vẽ sao. Rồi tiếp theo là vẽ những hình phức tạp hơn, buộc tôi phải học “đệ quy” và “vòng lặp” mới giải được. Vòng lặp và đệ quy, hai khái niệm rất khó nuốt cho một học sinh chuyên toán như tôi. Dẫu rằng trong toán học vẫn có những công thức truy hồi nhưng tôi thường nghĩ về chúng như một công thức toán hoặc một hàm số, tức là ta cứ thế số vào, trải qua một số công đoạn tính nhất định để ra kết quả. Vòng lặp lại khác, ta làm đi làm lại cùng một thứ, nhưng kết quả của ta biến đổi dần dần rồi đi đến giá trị cuối cùng khi vòng lặp kết thúc. Trong cách hiểu về Toán học của tôi, tôi quan tâm đến bên trong hàm của tôi bao gồm những phép tính gì (cộng trừ nhân chia ra sao), nhưng trong tư duy Tin học mới, tôi có thể xem hàm của tôi như những chiếc hộp đen. Tôi quan tâm nhiều hơn về thứ nó nhận vào (input) và thứ nó trả ra (output). Hãy lấy dãy Fibonacci làm ví dụ:

```
1, 1, 2, 3, 5, 8, ...

```

Giá trị của một số bằng tổng của hai số liền trước nó trừ hai số đầu. Ta tạm gọi $F(n)$ là sô Fibonacci thứ $n$. Tôi rất muốn tính nhanh giá trị của số này.

Trong toán học phổ thông mà tôi được học, tôi sẽ cố gắng tìm ra một công thức tổng quát cho số Fibonacci thứ $N$:

$F(n) = \frac{\phi ^n - \psi ^ n}{\phi - \psi} = \frac{\phi ^n - \psi ^n}{\sqrt{5}}$,

với:

$\phi = \frac{1 + \sqrt{5} }{2}$

Mục đích của điều này là để giảm thiểu số phép tính. Ví dụ tôi muốn tính số thứ 1000 của dãy trên, việc thay giá trị $n = 1000$ và công thức tổng quát trên của dãy sẽ nhanh hơn việc áp dụng số công thức truy hồi:

$F_n = F_{n – 1} + F_{n – 2}$

và tính ra 999 số trước đó!

Khi tôi học toán ở cấp hai, nhìn vào công thức tổng quát của số Fibinacci tôi chỉ thấy một phép trừ, một phép chia, vài phép căn bậc hai và lũy thừa. Tôi trông cậy vào máy tính cầm tay để thực hiện những phép tính đó. Nhưng tôi không để ý rằng thực hiện phép căn bậc hai khó hơn rất nhiều so với phép trừ. “Khó” ở đây không những là về thời gian mà còn về độ chính xác. Giá trị của căn bậc hai của 5 mà máy tính cầm tay hiển thị ra luôn chứa sai số vì chúng ta đều biết rằng đây là một số vô tỉ trong khi độ dài màn hình máy tính thì hữu hạn. Trong công thức tổng quát trên còn chứa nhiều phép tính phức tạp như phép lũy thừa một số thập phân chẳng hạn. Thực tế rất ít người sử dụng công thức ấy vì nó luôn cho sai số. Hãy dùng số nguyên khi còn có thể!

Ngược lại, trong công thức truy hồi, tôi chỉ thấy một phép cộng đơn giản. Tôi gõ ra một hàm số nhận input là hai số nguyên và trả output là tổng của hai số đó. Tôi lại tiếp tục nâng cấp hàm số đó lên thành một quy trình như sau: tôi loại số nhỏ hơn trong input ra khỏi hàm số và thay nó bằng output tôi vừa nhận được. Tôi có một bộ input mới, và từ đó lại tính ra một output mới. Khi tôi chạy quy trình đó, bạn đầu tôi cho vào hai số (1, 1). Tôi lặp lại quy trình nhiều lần (bao nhiêu lần đố bạn?) cho đến khi tôi nhận được số Fibonacci thứ $N$. Nói cách khác, tôi đang sử dụng một vòng lặp:

```
F[0] = 1
F[1] = 1
for n = 2 to 1000:
    F[n] = F[n-1] + F[n-2] 
```

Hãy nhớ lại vì sao tôi lại không dùng công thức này ngay từ đầu? Vì muốn tính số thứ 1000 tôi phải tính tay ra 999 số trước đó. Đấy là khi tôi chưa biết lập trình. Khi tôi biết lập trình, tôi ở trong một tình huống khác hẳn. Tôi chỉ cần gõ một vòng lặp, và gõ **một lần duy nhất**. Máy tính sẽ giúp tôi thực hiện phần tính toán. Bạn có thấy điều khác biệt không? Lần trước công sức tôi bỏ ra là phải ngồi tính tay 1000 giá trị nhưng bây giờ thì chỉ việc ngồi gõ ra một công thức trừu tượng và để máy tính thực hiện phần tính toán với giá trị cụ thể. Điều này đảo ngược lựa chọn của tôi như thế nào? Giờ tôi sẽ thích công thức truy hồi hơn vì nó ngắn hơn để gõ so với công thức tổng quát.

Máy tính làm tốt những việc con người làm không tốt, và ngược lại. Con người có thể làm những việc phức tạp nhưng ở tốc độ thấp; còn máy tính lại có thể làm những việc đơn giản nhưng ở tốc độ cao và có thể lặp lại nhiều lần mà không biết chán. Học thuật toán tức là kết hợp sự sắp đặt khéo léo của con người với tốc độ và sự bền bỉ của máy tính. Học thuật toán không phải là học ngôn ngữ lập trình, không phải là học Pascal, học C, học Java. Học thuật toán tức là nghĩ về quá trình chuyển động, sự thay đổi trạng thái của các thành phần trong suốt một quá trình, bản chất cũng giống y như học Vật lý, Sinh học, Hóa học vậy. Ngôn ngữ lập trình chỉ là phụ trợ. Tôi viết vòng lặp ở trên không phải theo một ngôn ngữ lập trình nào cả. Bạn có thể tạo ra một ngôn ngữ lập trình mang tên bạn. Bạn cũng có thể làm nó chạy được vòng lặp tôi viết ở trên.

Quay lại vấn đề, tại sao tôi lại nói vòng lặp là một trong những khái niệm quan trọng nhất. Có hai lý do. Thứ nhất là tôi cảm thấy tư duy của Tin học, của lập trình, tinh túy nhất ở những thuật toán mà ta chỉ thấy có một quá trình được lặp đi lặp lại mãi, và bất ngờ cuối cùng chúng ta lại được kết quả nhưng mong muốn. Thuật toán Euclid tìm ước chung lớn nhất của hai số, thuật toán chia nhị phân tìm giá trị nhỏ nhất của một hàm số lồi là một số ví dụ. Thực tế thì khá khó tìm được một thuật toán mà không có vòng lặp. Bạn có thể tưởng tượng sự vận hành của thuật toán như một ván cờ: bàn cờ là một thứ cố định và các quân cờ sẽ di chuyển, số lượng quân cờ sẽ ít dần đi theo thời gian đến khi đạt được trạng thái kết thúc là chiếu bí. Lý do thứ hai, việc lặp một quá trình như trong vòng lặp mở ra một lối tư duy mới trong việc giải quyết một vấn đề. Không nhất thiết rằng bạn phải ngay tính ra kết quả của bài toán ngay lập tức. Bạn thử tính lần thứ nhất, đáp số có thể sai, nhưng lặp lại dần thì kết quả sẽ đi gần hơn đến đáp án. Đầu óc bạn sẽ phải làm quen với những thứ trừu tượng có giá trị luôn luôn thay đổi (biến số), và bạn phải nhẩm lấy sự vận động của chúng. Cũng cùng là một dòng lệnh đó nhưng vỡi những giá trị khác nhau sẽ tạo ra những kết quả khác nhau.

Lúc mới học tin, tôi thấy hứng thú với lối tư duy mới này. Tôi thấy nó giúp tôi tiếp cận gần hơn với những gì đang xảy ra trong cuộc sống. Nếu như lúc trước tôi chỉ biết bấm máy tính thì bây giờ tôi đã biết quan tâm xem nó thực hiện những phép tính thế nào. Hiểu thêm về thế giới xung quanh làm tôi thấy hạnh phúc. Mọi môn học khác đều có cái hay của nó và đều có thể dẫn tôi đến cái cảm giác đó nhưng tôi đến với Tin học là một cái duyên. Vì thế khi bảo tôi nói ra lý do cần phải học Tin học, tôi không nghĩ ra lý do nào. Một ngày nọ tôi ăn được một món ngon, thế là tôi là về quyết định học cách nấu món đó. Chỉ vậy thôi.

