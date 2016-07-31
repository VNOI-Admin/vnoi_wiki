# Machine Learning - Classification - phần 1

**Nguồn**: [Achoum's blog](http://blog.mathieu.guillame-bert.com/2015/07/12/introduction-to-machine-learning/)

Có thể bạn đã nghe đến cụm từ **Machine Learning** (hay **Data Mining**, **Big Data**, **Data Science**,...) nhưng bạn chưa bao giờ hiểu ý nghĩa thực sự của chúng là gì. Có thể tất cả những gì bạn biết là "À! Đó là những thuật ngữ trong Toán học và Tin học", và ...thế là hết. Có thể bạn phải sử dụng những phần mềm dựa trên Machine Learning trong công việc nhưng với bạn, chúng hoạt động như là ma thuật vậy.

Nếu bạn vẫn đang còn tò mò, thì Machine Learning được dùng trong hầu hết mọi lĩnh vực. Ví dụ, Machine Learning được sử dụng bởi các ngân hàng để phát hiện gian lận và dự đoán rủi ro, được dùng bởi nhà quản lí email để phát hiện thư rác. Các bác sĩ dùng Machine Learning để hỗ trợ chẩn đoán, các nhà sinh học ứng dụng Machine Learning trong việc phân tích DNA. Chúng ta cũng đang tiếp xúc với nó hàng ngày khi Google/Bing/Yahoo đều sử dụng Machine Learning để xử lý mỗi khi bạn gõ lệnh tìm kiếm.

Mục tiêu của tác giả với chuỗi bài viết này là giúp các bạn có một hiểu biết sơ lược về Machine Learning và một cái nhìn trực quan về cách mà kỹ thuật này hoạt động. Thay vì nêu ra một đống lý thuyết, bài viết này sẽ chủ yếu dựa trên các ví dụ. Để đọc hiểu bài viết này, bạn không cần phải là một nhà khoa học máy tính; thậm chí, bạn không cần phải biết bất cứ điều gì liên quan đến máy tính và toán học.

Chuỗi bài viết trong chủ đề này gồm có 3 bài. Bài viết đầu tiên sẽ giới thiệu về một trong những nhiệm vụ chính của Machine Learning: **Phân loại** (**Classification**). Bài viết thứ hai trình bày và minh hoạ hai kỹ thuật quan trọng của Machine Learning được áp dụng trong bài toán phân loại: một trong số đó tuy rất đơn giản nhưng được sử dụng rộng rãi, cái còn lại là một kỹ thuật rất mới. Cuối cùng, bài viết thứ ba sẽ nói về cách các nhà khoa học máy tính đánh giá chất lượng của một kỹ thuật trong Machine Learning.

# Định nghĩa

Thật sự không dễ để có thể đưa ra một định nghĩa chính xác của Machine Learning. Nói một cách nôm na, Machine Learning là các chương trình giúp đưa ra dự đoán hoặc giúp người dùng hiểu về các hiện tượng phức tạp.

Machine Learning là một chủ đề rộng lớn với rất nhiều chủ đề con. Thay vì cố gắng đưa ra những định nghĩa chung chung, bài viết sẽ chỉ tập trung vào một chủ đề duy nhất: Phân loại **(Classification)**. Bài toán phân loại chỉ là một trong rất nhiều chủ đề của Machine Learning, nhưng là một trong những chủ đề quan trọng nhất. Khi người ta nói đến Machine Learning, thông thường họ nói đến bài toán phân loại (nếu họ không chỉ rõ chủ đề khác).

# Phân loại (Classification)

Ý tưởng của bài toán phân loại bắt đầu như sau: Chúng ta có một danh sách các *quan sát* (*observation*). Một *quan sát* là một khái niệm chung chung. Với Machine Learning, một quan sát thường là sự mô tả một đối tượng trong một trạng thái nào đó. Để hiểu rõ hơn, hãy xét một ví dụ rất phổ biến trong Machine Learning: hoa diên vĩ (Iris flowers). Giả sử một quan sát là sự mô tả một bông hoa. Với mỗi bông hoa, chúng ta có bốn thông số: độ dày và chiều dài của đài hoa (sepal) và cánh hoa (petal). Trên thực tế, ví dụ về hoa diên vĩ nổi tiếng với cái tên **the Iris dataset** và đây là bộ dữ liệu được sử dụng rất rộng rãi trong giới nghiên cứu Machine Learning để tìm hiểu về các thuật toán phân loại.

![translate_ml_iris_with_labels](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/iris_with_labels.jpg)

Bốn thông số của mỗi bông hoa được gọi là các *thuộc tính* (*attributes*). Trong Machine Learning, một quan sát đơn thuần chỉ là một danh sách các thuộc tính. Khi so sánh các quan sát, thực ra chúng ta so sánh các thuộc tính. Ví dụ: *"Bông hoa này có cánh hoa dài hơn bông hoa kia"*. Các thuộc tính có thể đại diện cho những thứ rất khác nhau. Ví dụ: độ dài của máy bay, thời gian của cơn bão, nhiệt độ của căn phòng, màu sắc của bức tường,... Nói chung, các thuộc tính thường được chia thành hai loại: thuộc tính dạng số (numbers) và thuộc tính dạng thể loại (categories). Sự khác biệt của hai loại thuộc tính này không quá nghiêm ngặt, nhưng thông thường, khi thuộc tính có thể so sánh được (`>` hoặc `<`), ta coi nó là thuộc tính dạng số (ví dụ như độ dài của cánh hoa diên vĩ), ngược lại chúng ta coi nó là thuộc tính dạng thể loại (ví dụ như màu sắc của một bông hoa hay chủng loại của một chú chó). 

Ngoài ra, với mỗi quan sát (hay với mỗi bông hoa diên vĩ), chúng ta có một **lớp** (**class**). Một lớp là một thông tin bổ sung về một quan sát. Trong ví dụ về hoa diên vĩ, ta giả sử rằng lớp của một bông hoa diên vĩ chính là loài của nó. Trong ví dụ này, chúng ta chỉ quan tâm ba loài hoa diên vĩ: **Setosa**, **Versicolour** và **Viginica**.

Tóm lại, chúng ta có một tập hợp các quan sát (các bông hoa diên vĩ). Với mỗi quan sát, chúng ta có một số các thuộc tính và một lớp. Bảng dưới đây minh hoạ một tập hợp các quan sát trong ví dụ về hoa diên vĩ. Một bảng kiểu này thường được gọi là một **dataset** hay bộ dữ liệu.

![translate_ml_iris_table](http://blog.mathieu.guillame-bert.com/wp-content/uploads/2015/07/table.png)

Giả sử rằng chúng ta có 150 quan sát như vậy (tương ứng với 150 bông hoa diên vĩ). Tuy nhiên, với quan sát cuối cùng (hay bông hoa diên vĩ cuối cùng), chúng ta không biết lớp của nó là gì (hay không biết bông hoa thuộc loài gì). Chúng ta có thể tự hỏi: Liệu loài hoa có liên quan đến kích thước của cánh hoa và đài hoa không? Có chăng một loài hoa có cánh hoa dài hơn so với các loài diên vĩ khác? Nói cách khác, liệu chúng ta có thể sử dụng 149 bông hoa diên vĩ mà chúng ta đã biết lớp của nó, và tìm ra lớp của bông hoa cuối cùng không? Đó chính xác là bài toán phân loại. Diễn đạt theo cách khác, bài toán phân loại có thể mô tả như sau:

*Giả sử chúng ta có một tập hợp các quan sát được đánh nhãn (hay các quan sát mà chúng ta đã biết lớp của nó) và một quan sát chưa được đánh nhãn. Làm thế nào để tìm ra lớp của quan sát đó?*

Trong thực tế, dĩ nhiên các kỹ thuật phân loại không chỉ được dùng để phân loại hoa. Các ngân hàng sử dụng nó để phân loại khách hàng (ví dụ: liệu khách hàng có hoàn lại nợ tín dụng hay không?). Các bệnh viện ứng dụng nó để phân loại bệnh nhân, các công ty bảo hiểm dùng trong việc phân loại các thân chủ của mình... Phân loại còn có thể được sử dụng ở một mức độ sâu sắc hơn. Ví dụ, các loại camera hiện đại dùng **classification** để nhận diện khuôn mặt, dịch vụ bưu điện sử dụng nó trong việc nhận dạng địa chỉ viết tay. Các thương gia dự đoán thị trường bằng các thuật toán phân loại, trong khi những nhà khí tượng sử dụng nó để dự báo thời tiết.

Điểm khác biệt chính giữa những ví dụ trên chính là các thuộc tính. Với khách hàng của các ngân hàng, thuộc tính là thu nhập hàng tháng, điểm tín dụng, số lần sử dụng thẻ gần đây,... Với bệnh nhân thì thuộc tính là giới tính, nhịp tim, huyết áp,... Với các bức ảnh, thuộc tính chính là giá trị màu của từng điểm ảnh.

Trong bài viết tiếp theo, tác giả sẽ trình bày cách giải bài toán phân loại. Chính xác hơn, tác giả sẽ trình bày hai thuật toán phân loại được sử dụng rộng rãi mà bất cứ nhà nghiên cứu về Machine Learning nào cũng biết.

Hẹn gặp lại các bạn trong bài viết tiếp theo. 