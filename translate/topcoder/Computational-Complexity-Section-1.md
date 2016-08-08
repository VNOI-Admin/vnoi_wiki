[[_TOC_]]

Nguồn bài: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/computational-complexity-section-1/)

# Giới thiệu
Trong bài viết này tôi sẽ giới thiệu tới các bạn về chủ đề độ phức tạp tính toán. Trước khi đi vào định nghĩa chính xác của các khái niệm, bài viết sẽ giải thích các lý luận đằng sau những khái niệm đó. Tôi cho rằng việc hiểu các lý luận này có thể còn quan trọng hơn bản thân định nghĩa của các khái niệm.

# Tầm quan trọng của những lý luận

## Ví dụ 1
Giả sử bạn được phân công viết một chương trình để xử lý một tập dữ liệu gồm nhiều bản ghi mà công ty của bạn đã thu thập. Bạn cài đặt hai thuật toán và kiểm tra chúng bằng một vài tập dữ liệu khác nhau. Thời gian chạy được thống kê trong bảng 1. 
<table>
<tbody>
<tr>
<td>Số lượng bản ghi</td>
<td>10</td>
<td>20</td>
<td>50</td>
<td>100</td>
<td>1000</td>
<td>5000</td>
</tr>
<tr>
<td>Thuật toán 1</td>
<td>0.00s</td>
<td>0.01s</td>
<td>0.05s</td>
<td>0.47s</td>
<td>23.92s</td>
<td>47min</td>
</tr>
<tr>
<td>Thuật toán 2</td>
<td>0.05s</td>
<td>0.05s</td>
<td>0.06s</td>
<td>0.11s</td>
<td>0.78s</td>
<td>14.22s</td>
</tr>
</tbody>
</table>
Bảng 1: Thời gian chạy của hai thuật toán 1, 2

Từ bảng 1 ta có thể đánh giá một cách không chính thức rằng thuật toán nào tốt hơn (vì thường là ta có thể ước lượng số lượng bản ghi cần xử lý). Với một công ty thì kết luận dựa trên việc chạy thử như vậy có thể chấp nhận được. Nhưng với người lập trình, nó sẽ tốt hơn nếu có thể đánh giá thời gian chạy của hai thuật toán **trước khi** viết code và chạy thử - sau đó chỉ cần cài đặt thuật toán tốt hơn.

Các kỳ thi lập trình cũng đòi hỏi việc đánh giá tương tự: kích cỡ của tập dữ liệu được cho trước trong đề bài. Giả sử ta đã nghĩ ra được một thuật toán. Câu hỏi cần đặt ra trước khi bắt tay vào cài đặt là: thuật toán này có đáng để cài đặt không? Liệu nó có thể chạy trên bộ test lớn nhất trong thời gian cho phép không? Nếu ta có thể nghĩ ra một vài thuật toán khác, nên chọn thuật nào để cài đặt?

Các câu hỏi trên dẫn tới câu hỏi cốt lõi hơn: **Làm sao để so sánh hai thuật toán với nhau?** Quay trở lại ví dụ 1, ta có thể ước lượng rằng khi số bản ghi vượt quá 1000, thuật toán 2 sẽ chạy nhanh hơn nhiều lần thuật toán 1. Nói cách khác, xét trên tất cả các tập dữ liệu có thể, thuật toán 2 sẽ chạy tốt hơn trong hầu hết các trường hợp.

Có thể kết luận được rằng trong hầu hết các trường hợp - cho trước 2 thuật toán, hoặc là một thuật toán gần như luôn luôn tốt hơn, hoặc là cả hai xấp xỉ tốt như nhau. Như vậy, chúng ta sẽ định nghĩa độ tốt của thuật toán dựa vào đánh giá độ hiệu quả chạy trên toàn bộ tập dữ liệu như trên. Đánh giá này sẽ là ý tưởng chính đằng sau các định nghĩa cụ thể mà chúng ta sẽ đề cập về sau.

## Mẹo gộp hai thuật toán
Nếu đối chiếu với hai thuật toán ví dụ 1, không khó để thấy rằng có một thuật toán với thời gian chạy tương tự với chúng trong bảng 2

<table>
<tbody>
<tr>
<td>Số lượng bản ghi</td>
<td>10</td>
<td>20</td>
<td>50</td>
<td>100</td>
<td>1000</td>
<td>5000</td>
</tr>
<tr>
<td>Thuật toán 3</td>
<td>$N$ 0.00s</td>
<td>0.01s</td>
<td>0.05s</td>
<td>0.11s</td>
<td>0.78s</td>
<td>14.22s</td>
</tr>
</tbody>
</table>
Bảng 2: Thời gian chạy của thuật toán 3

Ý tưởng của thuât toán 3: nếu số lượng bản ghi nhỏ thì ta áp dụng thuật toán 1, ngược lại áp dụng thuật toán 2.

Ý tưởng tương tự thường được áp dụng vào thực tế. Một ví dụ là trong các hàm sắp xếp *sort()* được cung cấp bởi thư viện của các ngôn ngữ lập trình thường được cài đặt theo thuật toán *QuickSort* với nhiều cải tiến, ví dụ:

+ Nếu số lượng phần tử quá nhỏ, chạy thuật toán sắp xếp chèn *InsertSort* (vì *InsertSort* chạy hơn với tập dữ liệu kích thước nhỏ).
+ Nếu vị trí phần tử chốt không tốt, chuyển sang chạy thuật toán sắp xếp trộn *MergeSort*.

# Thế nào là độ hiệu quả của thuật toán?

## Ví dụ 2

Giả sử bạn có đoạn mã sau:

~~~cpp
for(int i = 0; i < N; i++)
	for(int j = i + 1; j < N; j++)
    	if(A[i] > A[j])
        	swap( A[i], A[j] );
~~~
(Đây thực ra là một cách cài đặt của thuật toán *MinSort*) Giả sử chúng ta được cho một mảng dữ liệu đầu vào (mảng A và số phần tử N), ta có thể tính chính xác số bước chạy của thuật toán trên đầu vào đã cho. Ta thậm chí có thể tính chính xác số lệnh thực thi trong bộ vi xử lý nếu ta muốn(ND: chuyển đoạn mã C++ trên thành mã Assembly). Tuy nhiên, có rất nhiều giá trị mà bộ dữ liệu đầu vào có thể nhận nên việc tính toán số bước như trên với mọi khả năng đầu vào là không thể.

Thực tế trên dẫn ta tới câu hỏi quan trọng hơn: đánh giá quan trọng nhất về độ hiệu quả mà chúng ta cần tới là gì? Thông thường thì đó là tốc độ chạy thuật toán trong **trường hợp xấu nhất** - ta cần tìm ra một đánh giá **cận trên** của tốc độ chạy thuật toán.

Tuy nhiên, thế nào là là trường hợp xấu nhất? Một cách đơn giản để làm cho thuật toán chạy chậm hơn là  tăng kích cỡ đầu vào. Vì cận trên của số phần tử đã bị chặn bởi đề bài, các câu hỏi quan trọng hơn là: tập đầu vào xấu nhất trong các tập có cùng số phần tử là tập nào? Khi tăng kích cỡ tập đầu vào thì độ phức tạp trong trường hợp xấu nhất **tăng như thế nào**?

## Lưu ý về kích cỡ tập đầu vào

Hiểu chính xác thì "kích cỡ tập đầu vào" là đại lượng gì? Theo định nghĩa chính thống, kích cỡ tập đầu vào được viết thành một tập hữu hạn các ký tự (với ít nhất 02 'ký tự'). Trong bài này ta có thể coi tập ký tự đó là các số tự nhiên từ 0 tới 255. Như vậy "kích cỡ tập đầu vào" được tính đúng bằng số bytes của tệp chứa dữ liệu đầu vào (input file).

Thường thì một phần của bộ dữ liệu sẽ là một số (hoặc một vài số), mà kích cỡ của tập đầu vào sẽ tỉ lệ thuận với số này.

Chẳng hạn như trong ví dụ 2, ta có một số tự nhiên $N$ và một mảng với $N$ số integer. Kích cỡ theo đơn vị bytes của file đầu vào sẽ xấp xỉ $5N$ (phụ thuộc vào hệ điều hành và cấu trúc máy tính, nhưng sẽ luôn tuyến tính với $N$).

Trong các trường hợp này, ta có thể chọn số (hoặc các số) đó để biểu diễn kích cỡ tập đầu vào. Vì vậy khi nói về các bài toán có mảng / chuỗi, kích cỡ tập đầu vào là độ dài của mảng / chuỗi đó, khi nói về các bài toán đồ thị ta biểu thị bằng cả hai đại lượng số lượng đỉnh và số lượng cạnh,...

Với cách tiếp cận đó, kể từ đây cho tới cuối bài viết ta ký hiệu $N$ là kích cỡ tập đầu vào.

Một trường hợp cần lưu ý là khi viết một số $N$ ta chỉ cần $log(N)$ khoảng trống (ví dụ để viết 123456 trong hệ cơ số 10 ta chỉ cần $log_{10}(123456)$ chữ số). Cần phân biệt hai đại lượng này - với thuật toán kiểm tra số nguyên tố đơn giản có độ phức tạp đa thức trên **độ lớn** của số được kiểm tra chứ không phải là trên **số lượng chữ số** của số đó! Nếu bạn chưa từng gặp khái niệm *độ phức tạp đa thức* thì cũng không cần lo lắng vì khái niệm này sẽ được giải thích trong phần sau.

## Tính toán độ hiệu quả của thuật toán như thế nào?
Nhắc lại rằng cho trước một bộ dữ liệu đầu vào, ta có thể đếm số bước thực hiện các phép toán của một thuật toán bằng cách mô phỏng các bước chạy thuật toán đó trên bộ dữ liệu được cho. Giả sử ta tiến hành đếm như vậy với tất cả các bộ dữ liệu có kích thước tối đa $N$. Ký hiệu $f(N)$ là số bước cần thực hiện nhiều nhất (trường hợp xấu nhất). Hàm $f$ được gọi là **độ phức tạp thời gian**, hoặc ngắn gọn **thời gian chạy** của thuật toán.

Nói cách khác, nếu ta có dữ liệu vào với kích cỡ $N$, việc thực hiện thuật toán mất tối đa $f(N)$ bước. 

Quay trở lai thuật toán trong ví dụ 2. Tập đầu vào xấu nhất có $N$ phần tử là tập nào? Nói cách khác, trong số các mảng có $N$ phần tử, mảng nào khiến cho thuật toán phải thực hiện nhiều bước nhất? Từ đoạn mã của thuật toán ta thấy:

+ Bước thứ nhất được thực hiện đúng $N$ lần
+ Bước thứ hai và thứ ba được thực hiện đúng $\frac{N(N-1)}{2}$ lần
+ Bước thứ tư được thực hiện nhiều nhất $\frac{N(N-1)}{2}$ lần

Dễ thấy nếu các phần tử trong mảng $A$ được sắp xếp theo chiều *giảm dần* ngay từ đầu, bước thứ 4 sẽ luôn luôn được thực hiện. Vì vậy thuật toán sẽ chạy trong $\frac{3N(N-1)}{2} + N = 1.5N^2 - 0.5N$ bước. Vì vậy thuật toán trên có số bước tối đa là $f(N) = 1.5N^2 - 0.5N$. 

Có thể thấy rằng việc xác định chính xác hàm $f$ cho các chương trình phức tạp hơn là khá khó khăn. Thêm vào đó, trong nhiều trường hợp dạng chính xác của hàm $f$ là không cần thiết. Trong tính toán trên giá trị $-0.5N$ có thể bỏ qua, vì khi $N$ lớn thì $0.5N$ nhỏ hơn rất nhiều so với $1.5N^2$ và không ảnh hưởng lớn tới thời gian chạy. Mệnh đề "$f(N)$ xấp xỉ bằng $1.5N^2$" cho ta tất cả thông tin mà ta cần. Tiếp theo chúng ta sẽ thấy rằng, khi so sánh thuật toán này với một thuật toán nào đó khác để giải cùng một bài toán, hằng số $1.5$ cũng không thật quan trọng.

Xét hai thuật toán, một có thời gian chạy $N^2$ và một có thời gian chạy $0.0001N^3$. Dễ nhận thấy rằng với $N > 1000$ thì thuật toán đầu tiên chạy nhanh hơn - khi $N$ tăng, khoảng cách về độ hiệu quả giữa hai thuật toán càng trở nên rõ ràng. Trong khi thuật toán đầu tiên có thể giải quyết bài toán với $N = 20 000$ chỉ trong thời gian tính bằng giây, thuật toán thứ hai phải mất tới vài phút trên các máy tính hiện đại.

Sự khác biệt như trên sẽ luôn xảy ra nếu một trong hai thuật toán có *thời gian chạy* tăng **tiệm cận nhanh hơn** so với *thời gian chạy* của thuật toán còn lại (nói cách khác, khi $N$ đủ lớn để kết quả phép tính giới hạn **lim** của tỷ lệ giữa hai đại lượng này bằng 0 hoặc $\infty$. ND: trong bài này tác giả không nói rõ việc so sánh độ phức tạp theo phép tính giới hạn, chỉ cần hiểu khái niệm **tiệm cận** có nghĩa là **kích cỡ đầu vào đủ lớn**. Như vậy **tiệm cận nhanh hơn** có nghĩa là ** nhanh hơn khi đầu vào đủ lớn**). Bất kể các hằng số nhận giá trị nào, một thuật toán có *thời gian chạy* tỷ lệ (thuận) với $N^2$ sẽ **luôn luôn hiệu quả hơn** một thuật toán khác có *thời gian chạy* tỷ lệ với $N^3$ trong **hầu hết các trường hợp của tập đầu vào**. Nhận định này chính là ý tưởng chủ đạo để xây dựng định nghĩa chính thức của các khái niệm.



# Các khái niệm cơ bản

Gọi $f, g$ là các hàm số dương không giảm trên tập số nguyên dương (lưu ý rằng *hàm thời gian chạy* thỏa mãn điều kiện này). Ta nói rằng "$f(N)$ thuộc $O(g(N))$" (cách đọc: "$f$ thuộc O-lớn của $g$") nếu tồn tại các giá trị $c$ và $N_0$ thỏa mãn điều kiện sau:

$$
\forall N > N_0; f(N) < c.g(N)
$$

Mệnh đề trên có thể diễn dịch như sau: $f(N)$ thuộc $O(g(N))$ nếu với $c$ nào đó toàn bộ đồ thị của hàm $f$ nằm dưới đồ thị của hàm $c.g$. Chú ý rằng điều này có nghĩa là tốc độ tăng của hàm $f$ không vượt quá độ tăng của hàm $g$. (ND: ký hiệu O-lớn là ký hiệu chỉ **tập hợp của các hàm số**, vì vậy ở đây quan hệ giữa $f$ và $O(g(N))$ là *(phần tử) thuộc (tập hợp)*.)

Thay vì viết "$f(N)$ thuộc $O(g(N))$" ta thường viết là "$f(N)$ = $O(g(N))$". Chú ý là dấu "=" không có tính đối xứng - viết "$O(g(N)) = f (N)$" là sai và không có ý nghĩa gì, đồng thời mệnh đề "$g(N) = O(f (N))$" cũng không phải luôn đúng (sẽ được chỉ ra ở phần sau của bài viết).

Định nghĩa trên được biết tới là ký pháp O-lớn và được sử dụng để chỉ ra cận trên của tốc độ tăng của một hàm số.

Xét hàm số $f (N) = 1.5N^2 – 0.5N$ trong ví dụ 2. Ta có thể phát biểu rằng $f (N) = O(N^2)$ (một trường hợp khả dĩ cho các hằng số là $c = 2$ và $N_0 = 0$). Điều này có nghĩa là hàm $f$ **không tăng (tiệm cận) nhanh hơn ** $N^2$.

Lưu ý rằng *thời gian chạy* chính xác của hàm $f$ không cho ta câu trả lời cho câu hỏi "Chương trình trên chạy mất bao lâu trên máy tính?". Nhận định quan trọng rút ra từ ví dụ trên là *thời gian chạy* của hàm $f$ đó là hàm bậc hai. Nếu ta tăng gấp đôi kích cỡ đầu vào, thời gian chạy sẽ tăng xấp xỉ 4 lần thời gian chạy ban đầu, không quan trọng máy tính của ta nhanh như thế nào.

Việc xác định được cận trên $O(N^2)$ của $f(N)$ cũng đưa ta tới cùng nhận định như trên - đảm bảo rằng độ tăng của hàm thời gian chạy tối đa là hàm bậc hai.

Vì vậy, chúng ta sẽ sử dụng ký pháp O-lớn để mô tả độ phức tạp *thời gian* (và đôi khi là cả *bộ nhớ*) của các thuật toán. Với thuật toán trong ví dụ 2 ta sẽ nói "Độ phức tạp thời gian của thuật toán này là $O(N^2)$" hoặc ngắn gọn hơn "Thuật toán này là $O(N^2)$".

Theo cách tương tự ta sẽ định nghĩa $ \Omega$ (Omega-lớn) and $ \Theta$ (Theta-lớn). 

Ta nói rằng $f (N)= \Omega(g(N))$ nếu $g(N) = O(f (N))$, nói cách khác nếu $f$ tăng nhanh hơn hoặc bằng $g$.

Ta nói rằng $f (N) = \Theta(g(N))$ nếu $f (N) = O(g(N))$ và $g(N) = O(f (N))$, nói cách khác nếu cả hai hàm số có độ hiệu quả xấp xỉ bằng nhau.

Dễ dàng nhận thấy là hàm Omega-lớn dùng để chỉ cận dưới và hàm Theta-lớn dùng để chỉ đánh giá chặt (cả hai cận) của một hàm số. Có những đánh giá cận khác tương tự nhưng ít phổ biến hơn.

Một vài mệnh đề sử dụng các ký pháp trên:

+ $1.5N^2 -0.5N = O(N^2)$.
+ $47N log N = O(N^2)$.
+ $N log N + 1 000 047N = \Theta(N log N)$.
+ Tất cả các đa thức bậc $k$ là $O(N^k)$.
+ Độ phức tạp thời gian của thuật toán trong ví dụ 2 là $ \Theta(N^2)$.
+ Nếu một thuật toán thuộc $O(N^2)$, nó cũng thuộc $O(N^5)$.
+ Các thuật toán sắp xếp dựa trên phép so sánh đều là $ \Omega(N log N)$.
+ Thuật toán sắp xếp trộn *MergeSort* chạy trên mảng gồm $N$ phần tử thực hiện xấp xỉ $N log N$ phép so sánh. Vì vậy độ phức tạp thời gian của *MergeSort* là $ \Theta(N log N)$. Nếu mệnh đề trước đó là đúng thì MergeSort tiệm cận thuật toán tối ưu nhất trong các thuật toán sắp xếp dựa trên phép so sánh.
+ Thuật toán trong ví dụ 2 sử dụng $ \Theta(N)$ bytes bộ nhớ.
+ Hàm số cho biết số răng của một người ở một thời điểm xác định là $O(1)$.
+ Một thuật toán quay lui đơn giản giải các bài toán trên bàn cờ vua là $O(1)$ vì cây vị trí mà thuật toán duyệt qua có kích cỡ giới hạn. (Tuy nhiên giá trị hằng số trong $O(1)$ này lại rất lớn)
+ Mệnh đề "Độ phức tạp thời gian của thuật toán này tối thiểu là $O(N^2)$" là vô nghĩa. (Diễn dịch: "Giá trị tối thiểu của độ phức tạp thời gian của thuật toán này tối đa là xấp xỉ hàm bậc hai"). Phát biểu đúng là: "Độ phức tạp thời gian của thuật toán này là $ \Omega(N2)$."

Khi nói về độ phức tạp thời gian/bộ nhớ của một thuật toán, thay vì sử dụng ký pháp Theta-lớn $ \Theta(f (N))$ ta có thể đơn giản chỉ ra tên của lớp hàm chứa hàm $f$. Ví dụ với $f (N) =  \Theta(N)$, ta gọi thuật toán đó là *tuyến tính*. Một vài ví dụ khác:

+ $f (N) = \Theta(log N)$: hàm log
+ $f (N) = \Theta(N^2)$: hàm bậc 2
+ $f (N) = \Theta(N^3)$: hàm bậc 3
+ $f (N) = O(N^k)$ : hàm đa thức
+ $f (N) = \Omega(2^N)$: hàm mũ

Với các bài toán trên đồ thị, độ phức tạp $ \Theta$(N + M) được gọi là "tuyến tính theo độ lớn của đồ thị". 

## Xác định thời gian chạy dựa vào đánh giá cận trên

Với hầu hết các thuật toán thường gặp trong thực tế, giá trị hằng số của $O$ (hoặc $ \Theta$) thường là khá nhỏ. Nếu một thuật toán là $ \Theta(N^2)$, độ phức tạp chính xác là vào khoảng $10N^2$ chứ không phải $10^7N^2$.

Nói cách khác: nếu hằng số là lớn thì thường là các hằng số đó có liên quan tới các đại lượng có sẵn trong đề bài. Trong trường hợp này cách làm thông thường là gán một tên gọi cho hằng số đó và thêm nó vào đánh giá độ phức tạp theo ký pháp, thay vì bỏ qua như ta đã làm với số $1.5$ ở ví dụ 2.

Ví dụ: bài toán yêu cầu đếm số lần xuất hiện của mỗi loại ký tự trong một chuỗi độ dài $N$ ký tự. Thuật toán đơn giản nhất là duyệt cả chuỗi một lần cho mỗi loại ký tự. Kích cỡ bảng chữ cái không thay đổi (ví dụ nhiều nhất là 255 ký tự trong ngôn ngữ C), vì vậy thuật toán là tuyến tính với $N$. Mặc dù vậy, ta nên viết độ phức tạp thời gian là $ \Theta(|S|.N)$, trong đó $S$ là bảng chữ cái được sử dụng (Lưu ý là có một thuật toán tốt hơn giải bài toán này trong $ \Theta(| S| + N)$.

Trong một kỳ thi trên TopCoder, một thuật toán thực thi 1 000 000 000 phép nhân hiếm khi chạy trong giới hạn thời gian cho phép. Thực tế này cộng với quan sát ở trên và một vài kinh nghiệm với các bài toán trên TopCoder giúp ta tổng kết bảng sau:
<table>
<tbody>
<tr>
<th>complexity</th>
<th>maximum N</th>
</tr>
<tr>
<td>$ \Theta(N)$ </td><td>100 000 000</td>
</tr><tr>
<td>$ \Theta$(N log N)$</td><td> 	40 000 000</td>
</tr><tr>
<td>$ \Theta$(N^2)$ </td><td>	10 000</td>
</tr><tr>
<td>$ \Theta$(N^3)$ </td><td>	500</td>
</tr><tr>
<td>$ \Theta$(N^4)$ </td><td>	90</td>
</tr><tr>
<td>$ \Theta$(2^N)$ </td><td>	20</td>
</tr><tr>
<td>$ \Theta$(N!)$ </td><td> 11</td>
</tr>
</tbody>
</table>
Bảng 3: Giá trị $N$ lớn nhất để các thuật toán có độ phức tạp khác nhau chạy trong tối đa 8 giây

# Lưu ý khi phân tích độ phức tạp thuật toán
Thông thường khi trình bày một thuật toán, cách tốt nhất để đánh giá độ phức tạp của nó là ký pháp Theta $\Theta$. Tuy nhiên, trong thực tế thường ta chỉ trình bày cận $O-lớn$ vì ký pháp này dễ viết hơn và phổ biến hơn. Nhắc lại rằng $O-lớn$ chỉ mang ý nghĩa cận trên. Thông thường ta tìm cận trên $O-lớn$ nhỏ nhất có thể.

## Ví dụ 3
Cho một mảng A đã được sắp xếp. Xác định xem liệu có tồn tại 02 phần tử trong mảng mà cách nhau D đơn vị hay không. Xét lời giải sau

~~~cpp
int j = 0;
for(int i = 0; i < N; i++) {
	while ( (j < N-1) && (A[i] - A[j] > D) )
    	j++;
    if (A[i] - A[j] == D) return 1;
}
~~~

Thoạt nhìn ta có thể sẽ đánh giá thuật toán trên có cận $O(N^2)$ - vòng lặp trong cùng chạy $N$ lần, mỗi lần tăng biến $j$ tối đa $N$ lần. Phân tích kỹ hơn, ta thấy rằng cận trên có đánh giá tốt hơn là $O(N)$ - thật ra tổng thể số lần chạy câu lệnh $j$++ trong toàn bộ thuật toán không vượt quá $N$ lần.

Mệnh đề "thuật toán trên là $O(N^2)$" vẫn là một mệnh đề đúng. Tuy nhiên bằng việc nói rằng "thuật toán trên là $O(N)$" ta cung cấp nhiều thông tin hơn về thuật toán đó.

# Kết luận

Chúng ta đã chỉ ra cách viết các cận (trên, dưới) theo độ phức tạp tính toán của thuật toán. Ta cũng đã chứng minh rằng các cận đó là các thuộc tính cơ bản và thường là hiệu quả để đánh giá các thuật toán. 
Trong phần sau chúng ta sẽ phân tích làm thế nào để ước lượng độ phức tạp tính toán của các thuật toán. Như ta đã thấy trong Ví dụ 3 việc phân tích này có thể trở nên khá khó khăn. Một nguyên nhân khác làm cho việc phân tích khó khăn là *các thuật toán đệ quy*. Các vấn đề này sẽ được xử lý trong phần 2 của bài viết.
