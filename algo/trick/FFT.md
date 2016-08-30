[[_TOC_]]

# FFT

Tác giả: ngmq

Trong bài này chúng ta sẽ tìm hiểu về thuật toán nhân nhanh hai đa thức sử dụng phép biến đổi Fourier nhanh (*Fast Fourier Transform - FFT*) và cách cài đặt của nó. Bài viết này sẽ chỉ nêu chứng minh sơ lược của một vài tính chất được sử dụng. Các chứng minh chi tiết có thể tìm thấy ở mục tài liệu tham khảo phía cuối của bài viết.

# Vài nét lịch sử

Phép biến đổi Fourier (*Fourier Transform*) là một trong số những phát kiến toán học đặc sắc có lịch sử hào hùng, gắn liền với những phát kiến khoa học và chiến tranh quân sự ở thế kỷ 19 và 20. Joseph Fourier (1768-1830) là một nhà khoa học làm việc trong đội quân thám hiểm Ai Cập của Napoleon từ năm 1798. Sau khi cách mạng Pháp kết thúc năm 1799, Fourier trở về Pháp và tham gia xây dựng lại đất nước trong vai trò một giáo sư của đại học École Polytechnique. Trong quá trình làm việc với các công trình xây dựng cầu đường và đóng tàu, ông đặc biệt quan tâm tới bài toán mô tả quá trình truyền dẫn nhiệt trong kim loại, điều dẫn tới sự ra đời của phép biến đổi Fourier liên tục vào năm 1807 trong một báo cáo của ông tại viện hoàng gia Paris. Trong đó, ông mô tả mọi hàm số, kể cả các hàm số không liên tục đều có thể được biểu diễn dưới dạng tổng của một số vô hạn các hàm số lượng giác. Phát biểu này của Fourier gây chấn động và ấn tượng tới mức nhà toán học Pháp cùng thời là Lagrange cho rằng việc nghĩ ra phát kiến này là "gần như không thể" (*nothing short of impossible*) [1]. Trong hơn một trăm năm sau đó phép biến đổi Fourier trở thành một đối tượng nghiên cứu phổ và liện tục được phát triển, hoàn thiện bởi vô số các tên tuổi lớn của toán lý thuyết [2].

Trong khi phiên bản nguyên thủy có lịch sử hoành tráng như vậy, phép biến đổi Fourier nhanh, dù được cho là ra đời trước, lại được quan tâm chậm hơn nhiều. Người ta cho rằng những ý tưởng đầu tiên về biến đổi Fourier nhanh được phát triển bởi nhà toán học Đức Carl Friedrich Gauss (1777 - 1855) vào năm 1805 khi ông cố gắng xác định quỹ đạo của các thiên thạch [3], nhưng ông không công bố kết quả của mình. Mối liên hệ giữa Gauss và phép biến đổi Fourier nhanh chỉ được phát hiện khi các công trình của ông được tập hợp và công bố vào năm 1866. Mặc dù vậy, vào thời đó không có ai quan tâm tới công trình này vì lý thuyết độ phức tạp tính toán chưa phát triển (mãi tới năm 1936 Turing mới phát triển mô hình tính toán đầu tiên, và phải tới năm 1965 thì lịch sử ngành nghiên cứu về độ phức tạp tính toán mới bắt đầu với công trình của Hartmanis và Stearns [4]). Cũng trong năm 1965 hai nhà toán học trong Ban cố vấn khoa học của tổng thống Mỹ Kenedy là James Cooley và John Tukey đã sáng tạo lại phép biến đổi nhanh Fourier trong một nỗ lực nhằm phát hiện các vụ thử hạt nhân của chính quyền Xô Viết [3]. Kể từ thời điểm đó phép biến đổi nhanh Fourier mới chính thức được quan tâm và nghiên cứu ứng dụng trong rất nhiều các lĩnh vực nghiên cứu khác nhau của vật lý, sinh học, điện tử, y tế, điều khiển học...

# Phép nhân hai đa thức

Cho hai đa thức $p(x), q(x)$ có bậc $n, m$ như sau:

$$
p(x) = a_0 + a_1 x + a_x x^2 + ... + a_n x^n
$$
$$
q(x) = b_0 + b_1 x + b_x x^2 + ... + b_m x^m
$$

Ta cần tìm tích $c(x)$ của hai đa thức trên, có dạng:
$$
c(x) = p(x)q(x) = c_0 + c_1 x + c_x x^2 + ... + c_{n + m} x^{n + m}
$$

trong đó

$$
c_{j} = \sum_{i=0}^j a_ib_{j-i} \qquad j = 0, 1, ..., n + m
$$

Cách làm theo định nghĩa là ta nhân mỗi hệ số của $p(x)$ với tất cả các hệ số của $q(x)$ rồi cộng các hệ số của cùng tổng số mũ. Vì hai đa thức có $n$ và $m$ hệ số nên cách làm này có độ phức tạp là $O(nm)$. Khi $n$ và $m$ tương đối lớn cỡ $10^3$ hoặc $10^4$ trở lên thì độ phức tạp này là quá lớn để chạy trên máy tính, đặc biệt là các máy tính nhúng đòi hỏi tốc độ tính toán nhanh. Phép biến đổi FFT giúp thực hiện phép nhân nói trên trong độ phức tạp $O(N*logN)$ trong đó $N$ là lũy thừa của $2$ nhỏ nhất lớn hơn $n$ và $m$.
 
# Hai cách biểu diễn đa thức và ma trận Vandermonde

# Nghiệm nguyên thủy

## Công thức Euler

# Phép biến đổi Fourier nhanh

## Biến đổi Fourier rời rạc

## Ma trận Vandermonde của nghiệm nguyên thủy có gì đặc biệt?

## Công thức truy hồi

# Lưu ý về kỹ thuật cài đặt

## Chuẩn hóa bậc đa thức

## Đệ quy

## Khử đệ quy

## Bài tập ví dụ: POST2-VOJ

# Bài tập luyện tập
- [VOJ POST2](http://vn.spoj.com/problems/POST2/)
- [FFT problems on Codeforces](http://codeforces.com/problemset/tags/fft)
- [FFT problems by a2oj.com](https://a2oj.com/Category.jsp?ID=42)

# Tài liệu tham khảo
- [1] Rohit Thummalapalli. Fourier Transform: Nature’s Way of Analyzing Data. *Yale Scientific*, 2010. [Link](http://www.yalescientific.org/2010/12/fourier-transform-natures-way-of-analyzing-data/)
- [2] Alejandro Dominguez. Highlights in the History of the Fourier Transform. IEEE Pulse, 2016. [Link](http://pulse.embs.org/january-2016/highlights-in-the-history-of-the-fourier-transform/) 
- [3] Stefan Woerner. Fast Fourier Transform. *Numerical Analysis Seminar*, Swiss Federal Institute of Technology Zurich, 2008. [Link](http://www2.math.ethz.ch/education/bachelor/seminars/fs2008/nas/woerner.pdf)
- [4] Fortnow and Homer. A Short History of Computational Complexity. *Bulletin of the European
Association for Theoretical Computer Science 80*, June 2003. [Link](http://people.cs.uchicago.edu/~fortnow/beatcs/column80.pdf)
- [Bài toán nhân đa thức, phép biến đổi Fourier nhanh trên csstudyfun.wordpress.com (có chứng minh các tính chất được đề cập trong bài](https://csstudyfun.wordpress.com/2009/01/12/bai-toan-nhan-da-thuc-phep-bien-doi-fourier-nhanh-fast-fourier-transform-fft/)
- [Bài giảng của trường DH Aalto, Phần Lan](https://drive.google.com/open?id=0BxCwa-q7x3eWT3ZfakNHMWVveTg) 
- [Code cài đặt của e-maxx](http://e-maxx.ru/algo/fft_multiply)
- ["Tutorial on FFT — The tough made simple." trên Codeforces (có phần cơ bản về số phức)](http://codeforces.com/blog/entry/43499)