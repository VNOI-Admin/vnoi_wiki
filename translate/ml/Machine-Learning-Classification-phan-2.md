# Machine Learning - Classification - phần 2

**Bài viết chưa hoàn thiện.** **Nguồn:** [Achoum's blog](http://blog.mathieu.guillame-bert.com/2015/07/20/machine-learning-for-dummies-part-2/)

Trong bài viết trước ([link](http://vnoi.info/contributor/translate/ml/Machine-Learning-for-Dummies-part-1)), chúng ta đã cùng tìm hiểu về **Classification**. Chúng ta cũng đã đưa ra vài ví dụ về ứng dụng của nó và cũng đã làm quen với **the Iris dataset**. Nếu có thời gian, bạn nên đọc bài viết đó để có thể hiểu cặn kẽ những nội dung trong bài viết này.

Trở lại câu chuyện về hoa diên vĩ (Iris flower): Chúng ta có một danh sách các bông hoa diên vĩ được mô tả bằng độ dài và độ dày của đài hoa và cánh hoa (**attributes**). Chúng ta cũng đã biết chủng loại của tất cả các bông hoa trừ một cái duy nhất (chúng ta sẽ gọi nó là *"bông diên vĩ bí ẩn"*) và mục tiêu cuối cùng là tìm ra chủng loại của bông diên vĩ bí ẩn này. Với bài toán này, chúng ta giả sử rằng những thuộc tính trên là đặc trưng của chủng loại.

### Giải pháp 1: Quan sát tương đồng (*The same observation solution*)

Giải pháp đầu tiên mà ta thường nghĩ đến trong trường hợp này là tìm kiếm một bông hoa diên vĩ khác với độ dài và độ dày của đài hoa và cánh hoa tương đồng với bông diên vĩ bí ẩn. Nếu có, nhiều khả năng chủng loại của bông hoa này cũng tương đồng với bông hoa bí ẩn. Không may mắn thay, rất hiếm khi chúng ta tìm được hai bông hoa diên vĩ với những thông số giống hệt nhau. Trên thực tế, tìm kiếm một quan sát với các thuộc tính giống hệt hiếm khi là một giải pháp tốt, sẽ luôn có những sự khác biệt dù là rất nhỏ.

### Giải pháp 2: Hàng xóm gần nhất (*The 1-nearest neighbors solution*)

Thay vì tìm kiếm một bông diên vĩ với các giá trị thuộc tính tương đồng, chúng ta sẽ tìm kiếm những bông hoa *gần như* tương đồng với bông hoa bí ẩn. Nếu hai bông diên vĩ có kích thước rất gần giống nhau, chúng trông sẽ rất giống nhau và vì vậy, có thể chúng thuộc cùng một chủng loại.

Tuy nhiên, nếu như có một vài bông diên vĩ thuộc các chủng loại khác nhau nhưng đều có giá trị thuộc tính gần giống với bông diên vĩ bí ẩn, điều đó sẽ gây ra vấn đề. Vì vậy, chúng ta chỉ tìm ra bông diên vĩ *giống nhất* với bông diên vĩ bí ẩn. Điều đó có nghĩa là chúng ta phải định nghĩa chính xác thế nào là hai bông diên vĩ *giống nhau*. Chúng ta cũng phải định nghĩa thế nào là một bông diên vĩ giống bông diên vĩ này *hơn* so với một bông khác.

Giải pháp được sử dụng bởi các nhà nghiên cứu là định nghĩa *khoảng cách* giữa hai bông diên vĩ.  Khoảng cách giữa hai bông diên vĩ càng nhỏ, chúng càng *giống nhau*. Có rất nhiều cách để định nghĩa khoảng cách. Một trong những khoảng cách thường được sử dụng nhất trong Khoa học Máy tính là *khoảng cách Euclide* **(the Euclidean distance)**. Nghe có vẻ nguy hiểm, nhưng thực ra khoảng cách Euclide chính là những gì bạn vẫn thường hiểu về *khoảng cách* hay *đường chim bay*.

Tuy nhiên, mặc dù khoảng cách Euclide giữa hai điểm trên bản đồ rất dễ hiểu, sẽ khó tưởng tượng hơn một chút khi bạn nói đến khoảng cách giữa hai bông hoa diên vĩ.

Để tính khoảng cách Euclide, bạn phải tính tổng bình phương của hiệu các thuộc tính tương đương, rồi lấy căn bậc hai của tổng đó. Hãy áp dụng công thức đó cho hai bông hoa đầu tiên được biểu diễn trong bảng sau:

![translate_ml_iris_table_2](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/table.png)

Khoảng cách giữa hai bông hoa diên vĩ đầu tiên là:

$\sqrt{(6.3 - 6.2)^2 + (2.3 - 3.4)^2 + (4.4 - 5.4)^2 + (1.3 - 2.3)^2} = 1.79$

Khoảng cách giữa bông hoa đầu tiên và bông hoa thứ ba là:

$\sqrt{(6.3 - 5.2)^2 + (2.3 - 3.4)^2 + (4.4 - 1.4)^2 + (1.3 - 0.2)^2} = 3.55$

Giá trị đầu tiên nhỏ hơn ($1.79 < 3.55$), điều này có nghĩa là bông hoa diên vĩ đầu tiên giống bông hoa thứ hai hơn so với bông hoa thứ ba.

Nhờ những bước tính toán và so sánh như trên, bạn có thể tìm ra bông hoa giống bông hoa bí ẩn nhất. Đơn giản là chúng ta chỉ cần tính khoảng cách giữa bông hoa bí ẩn với mỗi bông hoa khác, và tìm bông hoa có khoảng cách nhỏ nhất. Phương pháp tưởng chừng như đơn giản này thực ra lại được sử dụng bởi rất nhiều nhà nghiên cứu. Nó có tên là *Hàng xóm gần nhất* (*The 1-nearest neighbors solution*)

![translate_ml_nearest_neighbor](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/irises.png)
