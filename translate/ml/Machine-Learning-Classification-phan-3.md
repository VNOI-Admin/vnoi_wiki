# Machine Learning - Classification - phần 3

**Nguồn:** [Achoum's blog](http://blog.mathieu.guillame-bert.com/2015/07/23/machine-learning-for-dummies-part-3/)
**Bài viết chưa hoàn thiện**

Trong hai bài viết trước ([[phần 1|translate/ml/Machine-Learning-Classification-phan-1]]) và ([[phần 2|translate/ml/Machine-Learning-Classification-phan-2]]), chúng ta đã cùng tìm hiểu về **Classification**. Chúng ta cũng đã làm quen với một thuật toán rất nổi tiếng gọi là **k-nearest neighbors**. Nếu có thời gian, bạn nên đọc các bài viết đó để có thể hiểu cặn kẽ những nội dung trong bài viết này, bài viết cuối cùng trong chuỗi bài giới thiệu về **Classification**.

Thuật toán *k-nearest neighbors* mà chúng ta tìm hiểu ở bài viết trước là một thuật toán được sử dụng rất rộng rãi. Tuy nhiên, nó cũng là một thuật toán rất cũ. Cho đến thời điểm này, các nhà nghiên cứu đã và đang phát triển những thuật toán phức tạp và mạnh mẽ hơn nhiều. Thuật toán tiếp theo mà tác giả muốn giới thiệu với các bạn được gọi là **Random Forest**. Đây là một thuật toán khá mới và được coi là một cuộc cách mạng trong *Machine Learning*. *Random Forest* chỉ phức tạp hơn một chút so với *k-nearest neighbors*, nhưng nó hiệu quả hơn nhiều nếu xét trên hiệu năng tính toán của máy tính. Bên cạnh đó, *Random Forest* còn cho kết quả *chính xác* hơn nhiều so với *k-nearest neighbors*. Nghĩa là, khi các nhà nghiên cứu kiểm thử kết quả của hai thuật toán này trên các bộ dữ liệu khác nhau (bao gồm cả *the Iris dataset*), *Random Forest* thường cho kết quả đúng hơn so với *k-nearest neighbors*

Một trong những lí do khiến *Random Forest* hiệu quả hơn so với *k-nearest neigbors* là bởi vì, với *k-nearest neighbors*, tất cả các thuộc tính đều có mức độ quan trọng như nhau. Mặt khác, *Random Forest* có khả năng tìm ra thuộc tính nào quan trọng hơn so với những thuộc tính khác. Trên thực tế, nó còn có thể chỉ ra rằng một số thuộc tính là hoàn toàn vô dụng.

*Random Forest* là một thành viên trong họ thuật toán **decision tree** (cây quyết định). Vậy cây quyết định là gì? Một cây quyết định là một cách đơn giản để biểu diễn một giao thức ????. Nói cách khác, cây quyết định biểu diễn một kế hoạch, trả lời câu hỏi phải làm gì trong một hoàn cảnh nhất định. Ví dụ, cây quyết định được sử dụng trong tổng đài điện thoại để quyết định xem tổng đài viên sẽ trả lời như thế nào dựa trên phản hồi của khách hàng. Nó cũng được sử dụng trong hệ điều hành của bất kì cỗ máy nào mà bạn có thể tưởng tượng (tàu ngầm, bom nguyên tử,...) hay đơn giản, cây quyết định được các bác sĩ sử dụng để chẩn đoán.

Hãy trở lại câu chuyện của chúng ta với một ví dụ đơn giản. Hình ảnh phía dưới minh hoạ một cây quyết định để xác định chủng loại của một con vật. Để đơn giản, chúng ta sẽ chỉ xét một vài chủng loại động vật mà thôi. Giả sử ta có một con vật, hãy thử dùng cây quyết định này để tìm ra chủng loại của nó.

Đường đi bắt đầu từ câu hỏi đầu tiên ở phía trên của cây (bên dưới vòng tròn đỏ). Trả lời câu hỏi đó, và đi tiếp xuống các nút phía dưới của cây tuỳ thuộc vào câu trả lời (có/không với câu hỏi đầu tiên). Lặp lại hành động đó cho đến khi đi tới nút lá (các út màu xanh lá cây). Khi đó, bạn sẽ có câu trả lời.

![translate_ml_decision_tree](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/exampledt.png)

(chú thích trên hình bị sai: 50cm thay vì 50kg)
Ví dụ, bạn bắt gặp một con vật mà bạn không biết nó thuộc chủng loại gì. Câu hỏi đầu tiên là: "Nó có lông không?". Giả sử nó có lông, chúng ta đi tiếp sang nhánh bên phải. Câu hỏi tiếp theo là: "Nó cao bao nhiêu?". Giả sử con vật của chúng ta chỉ cao 30cm. Điều này có nghĩa là chúng ta sẽ đi theo nhánh bên trái. Khi đó, vì chúng ta đã đi đến nút lá, chúng ta biết rằng con vật mà mình đang xét chính là con gà.

Bây giờ chắc bạn đã hiểu phần nào về cây quyết định, hãy trở lại với thuật toán *Random Forest*: Ý tưởng phía sau *Random Forest* khá đơn giản. Thuật toán này sinh một số cây quyết định (thường là vài trăm) và sử dụng chúng. Các câu hỏi của cây quyết định sẽ là câu hỏi về các thuộc tính. Ví dụ: "Cánh hoa có dài hơn 1.7cm hay không?". Câu giá trị ở nút lá sẽ là các lớp (*class*). Sử dụng hàng trăm cây quyết định là bất khả thi với con người, nhưng máy tính có thể làm việc này tương đối dễ dàng.

Đến lúc này chúng ta đã tìm hiểu cách sử dụng một cây quyết định, nhưng vấn đề là làm thế nào để tạo ra nó.

Có hai giải pháp. Cách thứ nhất là hỏi chuyên gia (ví dụ như một nhà nhân chủng học với bài toán phân biệt chủng loại của con vật). Nghe có vẻ hấp dẫn, nhưng không phải khi nào bạn cũng có thể tiếp cận được với chuyên gia trong bài toán của mình. Hơn nữa, bạn có thể sẽ ngạc nhiên rằng ngay cả những chuyên gia giỏi nhất cũng gặp khó khăn trong việc viết ra những kiến thức của mình. Ngay cả khi bạn tìm được một chuyên gia có khả năng đó thì chắc chắn sẽ có những thứ mà họ không biết tới. Ví dụ, nhà nhân chủng học của chúng ta có thể quên mất rằng con đà điểu có thể nhỏ hơn 50kg.

Thay vì sử dụng chuyên gia, các nhà nghiên cứu sử dụng phương án thứ hai: tạo ra một thuật toán tự sinh cây quyết định. Điều kiện duy nhất là phải có vài ví dụ để máy tính có thể tham chiếu. Trong *Iris dataset*, những ví dụ này chính là những bông hoa mà chúng ta đã biết chủng loại. 

Để tạo ra một cây quyết định, thuật toán *Random Forest* luôn bắt đầu bằng một cây rỗng. Một cây quyết định rỗng chỉ có một ô *Start* chỉ thẳng đến câu trả lời (ô xanh lá). Tiếp theo, thuật toán sẽ tìm câu hỏi đầu tiên và bắt đầu xây dựng cây quyết định (trong ví dụ trước, câu hỏi đó là "Nó có lông không?"). Mỗi lần thuật toán tìm được thêm một câu hỏi, nó tạo hai nhánh trên cây quyết định. Khi không còn câu hỏi nào nữa, thuật toán dừng lại và chúng ta có một cây quyết định hoàn chỉnh.

Làm thế nào để tìm ra những câu hỏi tốt nhất cho cây quyết định? Đây là một bước khá phức tạp nhưng ý tưởng đằng sau nó tương đối đơn giản: Ở thời điểm bắt đầu, thuật toán của chúng ta chưa biết phân biệt các chủng loại của các con vật. Nói cách khác, tất cả các con vật được cho chung vào một "cái túi". Để tìm ra câu hỏi tốt nhất, thuật toán thử đưa ra tất cả các câu hỏi có thể (có khi là hàng triệu câu hỏi). Ví dụ: "Nó có bao nhiêu chân?", "Nó có đuôi không?",... Sau đó, với mỗi câu hỏi, thuật toán sẽ đánh giá mức độ hiệu quả mà câu hỏi này giúp phân biệt các chủng loại, hay các *class*. Câu hỏi được chọn không cần thiết phải hoàn hảo, nhưng nó phải tốt hơn những câu hỏi khác. Để tính toán mức độ hiệu quả của câu hỏi, chúng ta sử dụng một độ đo có tên là **information gain**. Chúng ta sẽ không bàn chi tiết về độ đo này, có thể hiểu nôm na nó như một cách để "cho điểm" các câu hỏi. Câu hỏi với *information gain* lớn nhất sẽ được chọn như là câu hỏi tốt nhất để xây dựng cây quyết định.

Hình ảnh phía dưới minh hoạ 4 bước để tạo một cây quyết định đơn giản. Quá trình này sẽ được lặp lại cho tất cả các cây.

![translate_ml_decision_tree_2](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/building-dt.png)

Sau khi thuật toán xây dựng xong các cây quyết định, những cây này sẽ được sử dụng để trả lời câu hỏi (hay phân loại). Trong bài toán về hoa diên vĩ, thuật toán sẽ trả lời câu hỏi: "Chủng loại của bông hoa bí ẩn là gì?".

