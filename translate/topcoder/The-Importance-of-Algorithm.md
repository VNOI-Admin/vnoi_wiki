# The Importance of Algorithm

Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/the-importance-of-algorithms/) 


### Mở đầu ###

Bước đầu tiên để hiểu được tầm quan trọng của việc học và hiểu biết về thuật toán đó là sự định nghĩa chính xác "Thuật toán là gì?". Theo như cuốn sách giáo khoa nổi tiếng *Introduction to Algorithms* (Mở đầu về thuật toán), thì "thuật toán" là "bất kì một quá trình tính toán cụ thể nào, trong đó lấy một hay nhiều giá trị làm đầu vào và cho ra một hay nhiều giá trị kết quả". Nói cách khác, thuật toán giống như bản đồ chỉ đường giúp ta giải quyết một vấn đề rõ ràng, cụ thể. Ví dụ, nhiều dòng code để tính dãy Fibonacci là một cách cài đặt của một thuật toán nào đó. Một hàm để cộng hai số cũng là một thuật toán, dù đơn giản.

Một số thuật toán, như thuật để tính dãy Fibonacci, khá trực quan và ta có thể suy ra nhờ vào suy luận logic cũng như kĩ năng giải bài. Tuy vậy, đối với các thuật toán phức tạp, con đường tốt nhất cho hầu hết mọi người là học và sử dụng chúng làm nền tảng để phát triển khả năng tư duy và giải quyết vấn đề.

### Phân tích thời gian thực hiện thuật toán ###

Một trong những yếu tố quan trọng nhất của một thuật toán là việc nó xử lí nhanh hay chậm. Thật dễ dàng để nghĩ ra một thuật để giải một bài toán, nhưng nếu thuật quá chậm ta sẽ phải nghĩ lại từ đầu. Do tốc độ của một thuật tùy thuộc vào tốc độ máy cũng như từng tiểu tiết nhất của cài đặt, các nhà khoa học máy tính thường đề cập đến runtime (thời gian chạy) tương ứng với kích thước input. Ví dụ, nếu input gồm $N$ số, một thuật toán sẽ có runtime tương ứng với $N2$, kí hiệu $O(N2)$. Vậy khi máy tính chạy một cài đặt của thuật toán trên với độ lớn input $N$, chương trình sẽ tốn $C*N2$ giây, với $C$ là một hằng số không ảnh hưởng bởi kích thước input.

Tuy nhiên, thời gian chạy thực tế của nhiều thuật toán phức tạp còn phụ thuộc nhiều yếu tố khác ngoài độ lớn input. Ví dụ, một thuật toán sắp xếp sẽ chạy nhanh hơn nhiều khi được xử lí một dãy số đã sắp xếp sẵn so với khi phải giải quyết một dãy số lộn xộn. Từ đó sinh ra khái niệm thời gian chạy tối đa, hay thời gian chạy trung bình. Thời gian chạy tối đa là thời gian thuật toán cần để xử lí input tồi nhất có thể. Thời gian chạy trung bình là khoảng  trung bình cho mọi input được xử lí. Trong 2 thuật ngữ, thời gian tối đa thường dễ dự đoán hay tính toán hơn nên thường được sử dụng để đánh giá một thuật toán nào đó. Quá trình tính toán runtime có thể phức tạp vì thường ta không thể kiểm tra hết mọi trường hợp. Một số nguồn trên mạng có thể giúp ta ước lượng các giá trị này.

**Ước tính thời gian chạy của các thuật, $N = 100$**

* $O(Log(N))$ -------------------------10^-7 giây
* $O(N)$ --------------------------------10^-6 giây
* $O(N*Log(N))$ ----------------------10^-5 giây
* $O(N^2)$ -----------------------------10^-4 giây
* $O(N^6)$ ------------------------------3 phút
* $O(2^N)$ -----------------------------10^14 năm
* $O(N!)$ -------------------------------10^142 năm


### Sắp xếp ###
Thuật toán sắp xếp là một thuật toán rất hay được sử dụng. Cách đơn giản nhất để sắp xếp một nhóm đồ vật là lấy ra món đồ nhỏ nhất và đặt lên đầu. Ta lại lấy ra món đồ nhỏ thứ hai và đặt cạnh món đầu tiên; cứ thế tiếp tục. Không may, độ phức tạp của thuật toán này là $O(N^2)$, tức thời gian chạy của thuật sẽ tương ứng với độ lớn input bình phương. Nếu cần sắp xếp 1 tỉ con số, thuật sẽ cần 10^18 câu lệnh máy tính. Để dễ hình dung thì một chiếc máy tính hiện đại mỗi giây chỉ giải quyết được gần 110 câu lệnh, và sẽ cần nhiều năm mới sắp xếp xong 1 tỉ con số nói trên.

May thay, có nhiều thuật toán sắp xếp khác hiệu quả hơn (như QuickSort, HeapSort, MergeSort,...) đã được phát triển, nhiều thuật có độ phức tạp chỉ $O(N*Log(N))$. Độ phức tạp nhỏ hơn rút ngắn rất nhiều thời gian để sắp xếp 1 tỉ con số, đến mức một chiếc máy tính bình thường nhất cũng thực hiện được. Thay vì 10^18 câu lệnh, máy chỉ phải thực hiện 10^10.


### Đường đi ngắn nhất ###
Thuật toán tìm đường đi ngắn nhất từ một điểm đến một điểm đã được nghiên cứu từ lâu. Ứng dụng của thuật toán này rất nhiều, nhưng tạm thời hãy xét bài toán cơ bản nhất: tìm đường đi ngắn nhất từ A đến B trong một thành phố với số ít con đường và giao lộ. Có rất nhiều thuật toán được phát triển để giải quyết các bài kiểu này, với mỗi phương pháp có ưu nhược riêng. Trước khi tìm hiểu về chúng, hãy xem thử "thuật trâu" - xét hết các khả năng - sẽ mất bao lâu để giải. Đáng tiếc, ta sẽ không sống đủ lâu để biết kết quả từ phương pháp này - cho dù A và B đều ở trong một thị trấn nhỏ. Độ phức tạp của thuật là $O(C*N)$, với $C$ là hằng số. Dù $C$ có nhỏ, $C*N$ sẽ trở nên quá lớn ngay cả với các giá trị trung bình của N.

Một trong những thuật toán nhanh nhất để giải quyết vấn đề này có độ phức tạp $O(EVLog(N))$, với $E$ là số đường, $V$ là số giao lộ. Để dễ hình dung, thuật toán sẽ mất 2 giây để tìm đường đi ngắn nhất trong thành phố có 10000 giao lộ và 20000 con đường. Thuật toán này - Djikstra - khá phức tạp và đòi hỏi sự vận dụng cấu trúc dữ liệu Hàng đợi ưu tiên (Priority Queue). Tuy nhiên trong trường hợp ngay cả Djisktra cũng trở nên quá chậm (tưởng tượng đường đi ngắn nhất từ Bắc Giang đến Cà Mau - có đến hàng triệu giao lộ), các lập trình viên sẽ sử dụng heuristics. Heuristics là các cách giải quyết vấn đề nhanh hơn bằng cách sử dụng những "suy đoán hợp lí" đặc thù cho vấn đề, với cái giá là kết quả không tối ưu (lắm). Chẳng hạn, một số thuật toán có thể chạy nhanh hơn Djisktra trong một số trường hợp - như thuật toán A* - tuy nhiên yêu cầu khoảng cách giữa 2 điểm. Vậy ta có thể sử dụng heuristics, tìm gần đúng giá trị khoảng cách và từ đó cải thiện tốc độ, thay vì trông chờ vào Djisktra vốn đã "bó tay". Phương pháp này không phải lúc nào cũng rút ngắn thời gian chạy của thuật trong trường hợp tệ nhất, nhưng nó hiệu quả với phần lớn trường hợp thực tế.