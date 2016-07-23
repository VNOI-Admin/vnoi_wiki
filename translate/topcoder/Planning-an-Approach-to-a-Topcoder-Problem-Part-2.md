# Cách tiếp cận những bài toán trên Topcoder: Phần 2

**Bài viết chưa hoàn thiện**

Bài viết bởi [leadhyena_inran](https://www.topcoder.com/members/leadhyena_inran/). Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/planning-an-approach-to-a-topcoder-problem-part-1/) 

## Tiếp cận từ dưới lên (Bottom Up Programming)
Kỹ thuật này ngược với kỹ thuật chia nhỏ vấn đề ra, và nó nên là kỹ thuật đầu tiên bạn nghĩ tới khi bạn chưa tìm ra hướng giải. Bottom-up programming là quá trình xây dựng dựa trên việc chỉnh sửa và thêm các chức năng vào những hàm cơ bản, cho đến khi nó hoàn chỉnh để giải được bài toán ban đầu. Nhiều lúc bạn sẽ thấy rằng bạn cần một hàm cụ thể nào đó, nếu những hàm đó đã atomic hay dễ để chia nhỏ thì bạn có thể có thể xây dựng thẳng lên từ những hàm cơ bản đó thay vì chia nhỏ ra.

Trong bài MatArith ở phần trước, chương trình con để cộng và nhân ma trận cũng có thể áp dụng kĩ thuật này. Bạn có thể viết một hàm evalMult nhỏ hơn có nhiệm vụ nhân các ma trận với nhau bằng cách xử lí luôn trên string, một hàm evalAdd tương tự để cộng ma trận. 

Nói chung, đây là một chiến thuật khá tốt để xây dựng dần dần lên những chương trình con trước khi giải quyết vấn đề chính của bài toán. Một vài ví dụ là những hàm ngẫu nhiên (randomizer functions), bất kì các cấu trúc dữ liệu nào (data structures), bất kì toán tử nào trong các đối tượng của toán học như ma trận hay số phức. Bạn sẽ thấy rằng bằng việc giải quyết những vấn đề nhỏ đó và đọc lại đề bài, bạn sẽ thấy được bạn cần những gì để làm mọi thứ tốt hơn. Thỉnh thoảng, nếu bạn bị bế tắc với cách này, thì hãy viết một vài dòng atomic code để xem việc chia nhỏ vấn đề ra thì có hợp lí hơn hay không. Như bạn thấy, để tìm được cách tiếp cận đúng thì phải thử để biết cách tiếp cận nào sai trước đã.

Bên cạnh đó, hãy nhớ rằng bất kì dòng code nào bạn viết ra đều phải được kiểm tra trước khi xây dựng lên cao, bởi vì đây là những dòng code đầu tiên bạn viết và bạn sẽ chóng quên khi càng viết lên những phần phía trên. Một mẹo khá hay để tìm lỗi: nó luôn nằm trong những dòng code cũ của bạn, thậm chí cũ là là những dòng vừa code vài phút hoặc vài giây trước.

## Vét cạn (Brute Force)
Bất cứ khi nào đề bài yêu cầu một kết quả tối ưu, thì cách đơn giản nhất để giải quyết vấn đề là thử tất cả các trường hợp xảy ra. Bất cứ khi nào solution đòi hỏi việc tính toán nhiều bước, cách tốt nhất để giải là làm theo từng bước tính toán đó. Bất cứ khi nào bài toán yêu cầu bạn đếm những cách để làm một thứ gì đó trong một điều kiện cho trước, cách tốt nhất là thử tất cả mọi cách và chọn những cách thỏa yêu cầu. Nói cách khác, cách tiếp cận đầu tiên cho các bài toán nên là một cách dễ nhận thấy nhất, cho dù nó có quá tệ đi nữa.

Chiến thuật tiếp cận này gọi là vét cạn (brute force), nó được gọi như vậy bởi vì nó sẽ xét qua tất cả các trường hợp có thể xảy ra để tìm kết quả. Mỗi khi bạn gặp dạng bài toán tối ưu như thế thì đều đầu tiên phải xét đến là test xấu nhất có thể có là gì và liệu 8 giây có đủ thời gian để chạy từng test hay không. Nếu được, brute force có thể dùng được và thường code sẽ ít mắc lỗi hơn. Để dùng kĩ thuật brute force hiệu quả, bạn phải có đủ kiến thức về môi trường lập trình (programming environment) để ước lượng thời gian chạy của chương trình sẽ làm bao lâu, và tất nhiên ước lượng thì có thể sẽ sai. Đây là lúc bạn đưa ra lựa chọn dựa trên sự hiểu biết của mình. Có nhiều trường hợp do không ước lượng đúng nên đã bỏ qua cách brute force đơn giản và tốn thời gian vào debug những cách giải phức tạp, cũng tương tự như việc bị quá thời gian (time limit exceeded) khi không dự đoán được đến trường hợp xấu nhất. 

Nói chung, nếu bạn không thể tìm ra được cách nào khác để giải, thì hãy dùng brute-force. Nếu kết quả chưa đúng, thì tiếp tục tìm cách khác tối ưu hơn. Sau đó chúng ta có thể sử dụng code brute-force để test cho những cách giải khác (vì code brute-force bao giờ khả năng mắc lỗi cũng thấp hơn).

## Sử dụng giải thuật
Sử dụng những giải thuật nổi tiếng và cơ bản cũng là những cách tiếp cận cho những bài toán. Việc này cũng giống như việc đi các nước mở đầu giống nhau khi chơi cờ vậy. Thông thường, cách thử tuần tự các thuật toán để tiếp cận bài toán là một cách làm không hay cho lắm (nó tạo ra lối tư duy lối mòn và nhiều lỗ hổng kiến thức cho các bài toán cơ bản), nhưng nó cũng không phải là một ý tồi nếu sử dụng nó như một atomic code hay dựa vào đó để chia nhỏ vấn đề ra.

Bài này mình không bàn luận nhiều về giải thuật (đã có nhiều sách và tutorials về phần này), mà bàn về việc nên dùng giải thuật như thế nào để xác định cách tiếp cận bài toán. Biết cách sử dụng giải thuật trong trường hợp cơ bản là chưa đủ, hãy cố gắng hiểu thật sâu về nó. Ví dụ, bài CityLink (SRM 170 Div I Med), dùng kết hợp các giải thuật đồ thị (graph algorithm) đơn giản để giải, ngược lại việc code một giải thuật thông thường thì không đủ. Chỉ có hiểu sâu về cách hoạt động của thuật toán mới có thể tìm ra được cách kết hợp các giải thuật với nhau.
