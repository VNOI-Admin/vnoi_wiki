 [[_TOC_]]
 
Quả không ngoa khi nói rằng cuộc sống là một phòng thi về xác suất. Ứng dụng chủ yếu của lý thuyết về xác suất trong cuộc sống hằng ngày là đo lường rủi ro. Một ví dụ được lấy từ thực tiễn là hãy tưởng tượng bạn sẽ phải đối mặt với một kì kiểm tra có 20 môn và bạn không có đủ thời gian để chuẩn bị chu đáo, bạn chỉ có thể ôn được 15 môn thôi. Khi đưa ra 2 môn bất kì, xác suất mà bạn đã chuẩn bị được cả hai môn là bao nhiêu?  Cuộc sống là một chuỗi phức tạp các sự kiện và gần như mọi thứ đều có thể được hình dung dưới dạng xác suất. 
Cờ bạc đã trở thành một phần trong cuộc sống của chúng ta, và đây cũng là lĩnh vực mà lý thuyết xác suất được ứng dụng rộng rãi. Mặc dù cờ bạc đã xuất hiện từ thời xa xưa, nhưng đến tận thế kỉ 17, nền tảng toán học của lĩnh vực này mới được đưa ra. Tất cả bắt đầu với một câu hỏi đơn giản của Chevalier de Mï¿½rï¿½ - một nhà quý tộc dùng bài bạc như là một cách để gia tăng khối tài sản kếch sù của mình - gửi đến cho Blaise Pascal. Câu hỏi là có thể nhận được cặp sáu trong 24 lần tung một đôi xí ngầu hay không? 
Đa số các bài toán về xác suất đều được lấy ví dụ từ thực tế. Bạn sẽ được đưa ra tình huống và giải thích về luật chơi của trò chơi. Không khó để nhận ra bài tập nào cần dùng kiến thức về xác suất nhưng giải được chúng là một câu chuyện hoàn toàn khác. Biết cách để tiếp cận những bài toán như vậy là một lợi thế lớn trong các cuộc thi lập trình, và bài viết dưới đây sẽ trang bị những kiến thức nền tảng cho bạn.

#Cơ bản
Làm việc với xác suất cũng tương tự với tiến hành một cuộc thí nghiệm. **Kết quả** (*outcome*)  là kết quả của cuộc thí nghiệm hoặc những trường hợp có bao gồm sự không chắc chắn. Tập hợp của tất cả những kết quả có thể của thí nghiệm mang tính xác suất được gọi là **không gian mẫu** (*sample space*). 

Mỗi kết quả có thể xảy ra được biểu diễn bởi một và chỉ một điểm trong không gian mẫu (thường được kí hiệu bởi $S$). Chúng ta cùng xem xét ví dụ dưới đây:
'''
Tung cục xí ngầu một lần
Không gian mẫu $S = {1,2,3,4,5,6}$ 

Tung hai đồng xu 
Không gian mẫu $S = { (Sấp, Sấp), (Sấp, Ngửa), (Ngửa, Sấp), (Ngửa, Ngửa) }$
'''
Ta định nghĩa một **sự kiện** là một tập hợp các kết quả của một thí nghiệm. Do đố, một sự kiện là một tập con của không gian mẫu $S$. Nếu chúng ta đặt sựu kiện là $E$, thì chúng ta có thể nói rằng $E ⊆ S$. Nếu một sự kiện chỉ bao gồm một kết quả duy nhất trong không gian  mẫu, ta gọi chúng là sự kiện được. Sự kiện bao gồm nhiều hơn một kết quả được gọi là sự kiện kép.

Cái chúng ta quan tâm nhất là xác suất để một sự kiện nhất định xảy ra, $P(E)$. Theo định nghĩa, $P(E)$ là một số thực trong khoảng từ $0$ đến $1$, trong đó $0$ là sự kiện không có khả năng xảy ra và $1$ là sự kiện chắc chắn xảy ra (hay là toàn bộ không gian mẫu). 

[[/uploads/translate_topcoder_undertstandprobabilities_1.gif]]
 


