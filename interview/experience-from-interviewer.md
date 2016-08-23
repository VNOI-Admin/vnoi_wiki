# Kinh nghiệm phỏng vấn - Góc nhìn từ người phỏng vấn

**Tác giả**: Nguyễn *RR* Thành Trung

# Mở đầu

Ở Garena Singapore, mình được làm nhiệm vụ phỏng vấn các ứng viên nộp đơn vào vị trí Software Engineer. Quy trình phỏng vấn của Garena có thể nói là khá đơn giản, sau khi hồ sơ qua được vòng duyệt hồ sơ, thí sinh phải trải qua:

- Một bài kiểm tra trên giấy nếu thí sinh ở Singapore.
- 2 vòng phỏng vấn kiến thức cơ bản như thuật toán, kĩ năng code, hệ điều hành, mạng máy tính, database, ... Mình thường đi phỏng vấn ở vòng này.
  - Trong thời gian mình làm ở Garena, công ty có phỏng vấn rất nhiều người từ Việt Nam qua. Mình sẽ phỏng vấn qua Skype bằng tiếng Việt. Sau đó có thêm 1 vòng phỏng vấn bằng tiếng Anh nữa. Tuy nhiên quan điểm của công ty mình là kiến thức và kĩ năng quan trọng hơn ngôn ngữ, nên tiếng Anh của bạn kém 1 chút cũng không sao (miễn đừng kém quá). Điều này hoàn toàn khác với một số công ty như Google.
  - Vì phỏng vấn qua Skype, thí sinh ngồi phỏng vấn qua máy tính, và code luôn trực tiếp qua online editor.
- Nếu vị trí có tính chất đặc biệt như lập trình Android / iOS, frontend, thì thí sinh sẽ phải trải qua thêm 1 vòng phỏng vấn nữa.

Trong bài viết này, mình muốn chia sẻ về việc phỏng vấn từ góc nhìn của người *phía bên kia chiến tuyến*.

# Mục đích phỏng vấn

Theo quan điểm của mình, một cuộc phỏng vấn là một cuộc tìm hiểu lẫn nhau của ứng viên và công ty:

- Trong suốt quá trình phỏng vấn, người phỏng vấn sẽ cố gắng tìm hiểu kiến thức, kĩ năng cũng như tính cách của bạn, để xem có phù hợp với công ty hay không. Dù bạn có giỏi nhưng tính cách không phù hợp thì cũng chắc chắn không được nhận.
- Ngược lại, là ứng viên, bạn cũng cần tìm hiểu công ty. Mình thường đánh giá rất thấp những ứng viên chỉ biết trả lời những gì được hỏi, và không có chút gì muốn tìm hiểu về công ty.

# Nội dung phỏng vấn

Như đã nói ở trên, nội dung phỏng vấn gồm rất nhiều phần:

- Thuật toán
- Kĩ năng code
- Hệ điều hành
- Mạng máy tính
- Database

Tùy theo người phỏng vấn, họ sẽ hỏi các phần ở các độ sâu khác nhau, tuy nhiên thuật toán và kĩ năng code luôn là phần quan trọng nhất. Cá nhân mình thì chỉ giỏi về thuật toán và code, nên mình thường chỉ hỏi tập trung vào 2 phần đó, và các phần khác mình hỏi rất đơn giản.

## Thuật toán và Kĩ năng code

Thông thường mình sẽ nhìn vào Resume của ứng viên để chọn câu hỏi. Thường sau khi nhìn hồ sơ mình chia thành 3 nhóm:

1. Nhóm chưa từng tham gia Competitive Programming
2. Nhóm đã từng tham gia Competitive Programming: đã từng thi những giải như HSG cấp tỉnh, quốc gia hoặc Tin học trẻ
3. Nhóm có rất nhiều kinh nghiệm Competitive Programming: thường là mình đã từng nghe tên hoặc đã biết.

### Ai + Aj = S

Với nhóm 1 và 2 (và thỉnh thoảng là nhóm 3), mình hỏi cùng 1 câu hỏi như sau:

> Cho mảng A gồm N phần tử và một số nguyên S. Đếm số cặp (i, j) mà A(i) + A(j) = S
> Ví dụ:
> A = [1, 5, 2, 4, 3]
> S = 6
> return 2

Sau khi nghe xong câu hỏi thì thường bạn sẽ phải nói cho mình cách làm, sau khi mình thấy hợp lý thì bạn có thể bắt đầu code. Câu hỏi này thường có vài cách làm:

1. Cách hiển nhiên $O(N^2)$: Dùng 2 vòng `for` để đếm. Gọi biến chạy của 2 vòng `for` là `i` và `j`, thì để tránh đếm trùng, `j` phải bắt đầu từ `i+1`. Nghe có vẻ đơn giản, nhưng khi mình phỏng vấn nhóm 1 thì có rất nhiều bạn không làm được.
2. Cách "trâu bò" $O(N \* logN)$: Sắp xếp lại rồi chặt nhị phân để đếm. Cách này có nhược điểm là dễ bị đếm trùng. Để khắc phục thì có thể dùng rời rạc hóa. Tuy nhiên cách cài đặt này thường không được mình đánh giá cao do nó phức tạp hơn mức cần thiết.
3. Cách "chuẩn" $O(N)$: Dùng [[hash table|algo/data-structures/hash-table]] để lưu lại các phần tử của dãy, vừa lưu vừa đếm.

Khi ứng viên trả lời, mình đánh giá theo nhiều tiêu chí:

- Giải thích thuật toán: Bạn có hiểu rõ là mình đang làm gì không?
- Cẩn thận: Bạn có tránh được các trường hợp lỗi không (chẳng hạn nếu làm theo cách 2 thì dễ bị đếm lặp và bạn có nhận ra không?).
- Thuật toán: Tìm theo cách làm của bạn, mình có thể hỏi sâu thêm về thuật toán. Ví dụ:
  - Nếu làm theo cách 2, mình sẽ hỏi bạn có biết thuật toán sắp xếp nào không? Độ phức tạp? Cách cài đặt?
  - Nếu làm theo cách 3, mình sẽ hỏi bạn có biết cài đặt hash table hay không? Độ phức tạp?
- Cài đặt: Cách cài đặt của bạn có dễ hiểu không? Có xét đủ hết các trường hợp hay không?
- Debug: Sau khi code xong bạn có thể chạy thử code của mình. Nếu code sai, mình sẽ quan sát xem bạn debug như nào? Kĩ năng debug có tốt không?

Mình dùng đi dùng lại 1 câu hỏi vì như vậy mình sẽ nắm được rất rõ các cách trả lời khác nhau và các lỗi bạn đã gặp phải. Tuy nhiên tùy ngẫu hứng mình sẽ có thể hỏi thêm các chi tiết khác nhau, ví dụ:

- Nếu bạn dùng C++: Nếu dùng hàm `sort`, bạn có biết `sort` của C++ dùng thuật toán gì không? Nếu dùng `vector`, bạn có biết độ phức tạp mỗi thao tác là bao nhiêu không?
- Nếu bạn dùng Python: Bạn có biết trong Python 2 có hàm `range` và `xrange` không? Bạn có biết nó khác gì nhau không?

Thường những câu hỏi này mình hỏi khá ngẫu hứng và trong trường hợp không trả lời được, bạn cũng không cần lo lắng.

### Count Palindrome

Với nhóm 3, thường mình sẽ hỏi câu như sau:

> Cho 1 xâu S. Đếm số substring của S là Palindrome

Bài này cũng có 2 cách làm chính với độ phức tạp $O(N^2)$:

1. Quy hoạch động
2. Xét tâm của Palindrome và duyệt sang 2 bên.

Thỉnh thoảng, với nhóm 1 hoặc 2, nếu bạn trả lời câu trước quá kém và mình thấy còn thời gian, mình sẽ cho "gỡ gạc" bằng câu này, tuy nhiên mình chỉ yêu cầu làm cách duyệt toàn bộ với độ phức tạp $O(N^3)$ là đủ.

Đánh giá của mình cũng dựa trên những tiêu chí như phần trên.

## Hệ điều hành

Phần này mình thường không hỏi nhiều. Mình thường sẽ bắt đầu bằng câu hỏi:

> Thread và Process giống và khác nhau thế nào?

Sau đó, tùy theo cách bạn trả lời hoặc tâm trạng của mình lúc đó, mình có thể hỏi thêm 1 số phần khác như:

- Thread Communication và Process Communication
- Lock, Semaphore
- Context Switch

Mình không giỏi về hệ điều hành nên thường yêu cầu không cao. Bạn trả lời được những ý cơ bản là đạt yêu cầu của mình.

## Mạng máy tính

Phần này mình cũng thường không hỏi nhiều. Mình thường bắt đầu bằng câu hỏi:

> UDP và TCP khác nhau thế nào?

Sau đó, mình có thể hỏi thêm 1 số phần khác như:

- TCP handshake
- Congestion control

Mình không giỏi về phần nên thường yêu cầu không cao. Bạn trả lời được những ý cơ bản là đạt yêu cầu của mình.

# Những lỗi cần tránh

Ở Garena mình được đánh giá là một trong những người phỏng vấn khó tính nhất. Với những người khó tính như mình, có một số lỗi mà bạn cần tránh trong suốt quá trình phỏng vấn:

- Dùng Google mà không nói với mình: Mình đã từng gặp trường hợp sau khi mình vừa nói câu hỏi, thí sinh xin phép suy nghĩ nhưng sau đó mình lại nghe thấy nhiều tiếng gõ phím và click chuột (chú ý mình phỏng vấn qua Skype nên mới có trường hợp như vậy). Mình đoán bạn đó đang Google để tìm lời giải, và trường hợp như vậy gần như chắc chắn sẽ bị đánh trượt.
- Đến muộn lúc phỏng vấn: Nếu bạn vào muộn không quá 5 phút thì thường mình cũng không có vấn đề gì, tuy nhiên nếu bạn đến quá muộn mà không có lý do phù hợp thì mình sẽ đánh giá là bạn không có sự chuẩn bị cẩn thận cho cuộc phỏng vấn.
- Chém gió quá nhiều trong Resume: Nếu bạn viết bất kỳ cái gì vào Resume, mình có thể sẽ hỏi. Nếu bạn không trả lời được những kiến thức cơ bản, mình sẽ đánh giá rất thấp. Ví dụ bạn viết vào Resume là biết dùng git, nhưng không thể giải thích được `git commit` là gì.
- Xin đổi câu hỏi với câu thuật toán / code: Đã có trường hợp sau khi mình nói đề, thí sinh không suy nghĩ nhiều mà xin đổi câu hỏi luôn. Vì thuật toán và kỹ năng code là câu hỏi quan trọng, nên thông thường mình sẽ đổi câu hỏi khó hơn.
- Thể hiện không có tinh thần học hỏi. Ví dụ ứng viên không muốn học ngôn ngữ lập trình mới. Đối với Software Engineer mình thấy đây là điều tối kị, vì công nghệ thay đổi liên tục mỗi ngày và bạn phải không ngừng học hỏi. Ngược lại, cũng đã có trường hợp mình đánh đỗ ứng viên vì mình thấy bạn đó có tinh thần học hỏi rất tốt mặc dù kiến thức không tốt lắm.
